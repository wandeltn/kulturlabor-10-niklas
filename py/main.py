import math
from re import T
import time
import threading
import random 
import RPi.GPIO as GPIO
from PIL import Image, ImageOps, ImageDraw, ImageFont
from luma.core.interface.serial import spi
from luma.oled.device import ssd1306
from luma.core.sprite_system import framerate_regulator


SPRITEMAP_MENU_PATH: str = "/home/pi/Downloads/py/img/image.png"
SPRITEMAP_POOP_PATH: str = "/home/pi/Downloads/py/img/poop_menu_icon.png"
SPRITEMAP_STONE_PATH: str = "/home/pi/Downloads/py/img/stone_icon.png"
SPRITEMAP_EGG_PATH: str = "/home/pi/Downloads/py/img/spritemap_egg_stage.png"

BUTTON_A_GPIO: int = 21
BUTTON_B_GPIO: int = 20
BUTTON_C_GPIO: int = 16

serial: spi = spi()
device: ssd1306 = ssd1306(serial)

class DisplayItem(object):
    def __init__(self):
        self.selected: bool = False
        
    def render(self, image: Image.Image, menu_position: int) -> None:
        pass
    
class DisplaySprite(DisplayItem):
    def __init__(self, path: str, spritemap_position: tuple[int, int, int, int], display_position: tuple[int, int]):
        super().__init__()
        spritemap: Image.Image = Image.open(path)
        self.sprite: Image.Image = spritemap.crop(spritemap_position)
        
        self.position = display_position 
        
    def render(self, display: Image.Image, _menu_position: int):
        display.paste(self.sprite)
        

class DisplayMenu(DisplayItem):
    def __init__(self, spritemap_index: int):
        super().__init__()
        self.spritemap_index = spritemap_index
        
        spritemap = Image.open(SPRITEMAP_MENU_PATH).convert("L")
        self.sprite_unselected: Image.Image = spritemap.crop((spritemap_index * 16, 0, (spritemap_index + 1) * 16, 16))
        self.sprite_selected: Image.Image = ImageOps.invert(self.sprite_unselected)

        self.position_X: int = (spritemap_index // 4) * 112
        self.position_Y: int = (spritemap_index % 4) * 16
       
    def render(self, display: Image.Image, menu_position: int):
        if self.spritemap_index == menu_position:
            display.paste(self.sprite_selected, (self.position_X, self.position_Y))
        else:
            display.paste(self.sprite_unselected, (self.position_X, self.position_Y))
    
class DisplayPoopBar(DisplayItem):
    def __init__(self):
        super().__init__()
        self.poop_on_screen: int = 0
        
        spritemap: Image.Image = Image.open(SPRITEMAP_POOP_PATH).convert("L")
        self.sprite_unselected: Image.Image = spritemap.crop((0, 0, 5 ,6))
        self.sprite_selected: Image.Image = spritemap.crop((5, 0, 10, 6))
    
    def render(self, display: Image.Image, _menu_position: int):
        for poop_index in range(self.poop_on_screen):
            if self.selected:
                display.paste(self.sprite_selected, (106, poop_index * 8))
            else:
                display.paste(self.sprite_unselected, (106, poop_index * 8))
            

class DisplayStoneBar(DisplayItem):
    def __init__(self, stones_on_screen: int = 4):
        super().__init__()
        self.sprite: Image.Image = Image.open(SPRITEMAP_STONE_PATH)
        
        self.stones_on_screen: int = stones_on_screen
    
    def render(self, display: Image.Image, _menu_position: int):
        for stone_index in range(self.stones_on_screen):
            display.paste(self.sprite, (17, stone_index * 8))
            

class DisplayTamaItem(DisplayItem):
    def __init__(self):
        self.evolution_state: int = 1
        self.evolution_state_spritemap_index_X: int = 1
        self.evolution_state_spritemap_index_Y: int = 1
        
        self.time_until_next_update: int = -30
        
        self.position_X: int = 30
        self.position_Y: int = 0
        self.facing_right: bool = False
        
        spritemap: Image.Image = Image.open(SPRITEMAP_EGG_PATH)
        
        self.sprite_0: Image.Image = spritemap.crop((
            self.evolution_state_spritemap_index_X * 48,
            self.evolution_state_spritemap_index_Y * 48,
            (self.evolution_state_spritemap_index_X + 1) * 48,
            (self.evolution_state_spritemap_index_Y + 1) * 48))
        
    def get_next_sprite_position(self):
        MAX_VALUE_CHANGE: int = 3
        # position_X
        if self.position_X - 26 <= 0:
            change_position_X = random.randint(0, MAX_VALUE_CHANGE)
        elif self.position_X >= 55:
            change_position_X = random.randint(MAX_VALUE_CHANGE * -1, 0)
        else:
            change_position_X = random.randint(MAX_VALUE_CHANGE * -1, MAX_VALUE_CHANGE)
        if change_position_X:
            self.facing_right = True
        else:
            self.facing_right = False
            
        self.position_X += change_position_X
            
        # position_Y 
        if self.position_Y <= 0:
            self.position_Y += random.randint(0, MAX_VALUE_CHANGE)
        elif self.position_Y >= 16:
            self.position_Y += random.randint(MAX_VALUE_CHANGE * -1, 0)
        else:
            self.position_Y += random.randint(MAX_VALUE_CHANGE * -1, MAX_VALUE_CHANGE)
            
    def render(self, display: Image.Image, _menu_position: int):
        if self.evolution_state:                            # do not update in egg state
            if self.time_until_next_update == 0:            # wait until every 60th frame until position update
                self.time_until_next_update = -30
                self.get_next_sprite_position()
                
            if self.facing_right:
                display.paste(self.sprite_0, (self.position_X, self.position_Y))
            else:
                display.paste(ImageOps.mirror(self.sprite_0), (self.position_X, self.position_Y))
            self.time_until_next_update += 1
        else:
            display.paste(self.sprite_0, (self.position_X, self.position_Y))
                   
        
class BaseScreen(object):
    def __init__(self):
        self.display_content: Image.Image = Image.new("1", (128, 64))
        self.display_content_clear = self.display_content.copy()
        self.render_list: list[DisplayItem] = []
        self.menu_position: int = 0
        self.max_menu_position: int = 0
        
    def on_menu_position_changed(self) -> None:
        pass
          
    def render(self) -> None: 
        self.display_content = self.display_content_clear.copy()
        for display_item in self.render_list:
            display_item.render(self.display_content, self.menu_position)
            
        device.display(self.display_content)
            
    def on_button_A_pressed(self):
        if self.menu_position >= self.max_menu_position:
            self.menu_position = 0
        else:
            self.menu_position += 1
        self.on_menu_position_changed()
                
    def on_button_B_pressed(self):
        pass
                
    def on_button_C_pressed(self):
        if self.menu_position <= 0:
            self.menu_position = self.max_menu_position
        else:
            self.menu_position -= 1
        self.on_menu_position_changed()
             
class SubScreenHunger(BaseScreen):
    def __init__(self):
        super().__init__()
        self.food_items_dict: dict[str, int] = {
            "Burger": 1000,
            "Pasta": 1000,
            "Muffin": 1000,
            "Broccoli": 1000,
            "Salad": 1000,
            "Sushi": 1000,
            "Crepes": 1000,
            "Exit": 0
        }
        
        self.max_menu_position = 7
        self.render_list.append(SubDisplayMenu(list(self.food_items_dict)))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (0, 0, 16, 16), (0, 0)))
    
    def on_button_B_pressed(self):
        pass
            
class SubDisplayMenu(DisplayItem):
    def __init__(self, text_render_list: list[str]):
        super().__init__()
        self.text_render_list: list[str] = text_render_list
        
        self.text_image = Image.new("L", (128, 64))
        self.clear_text_image: Image.Image = self.text_image.copy()
        
    def render(self, display: Image.Image, menu_position: int):
        self.text_image = self.clear_text_image.copy()
        display_draw: ImageDraw.ImageDraw = ImageDraw.Draw(self.text_image)
        
        list_index = 0
        for food_item in self.text_render_list:
            if list_index == menu_position:
                display_draw.text(
                    (50, (list_index * 8) - 1),                  # position of text
                    "» " + food_item,                                        # text to be added
                    (255))
            else:
                display_draw.text(
                    (50, (list_index * 8) - 1),                             # position of text
                    "  " + food_item,                                       # text to be added
                    (255))                                                  # color of the text
            list_index += 1
        
        display.paste(self.text_image)



class MainScreen(BaseScreen):
    def __init__(self):
        super().__init__()
        self.poop_index_list: list[int] = []
        self.stone_display_bar: DisplayStoneBar = DisplayStoneBar()
        self.poop_display_bar: DisplayPoopBar = DisplayPoopBar()
        self.tama_display_item: DisplayTamaItem = DisplayTamaItem()
        
        for i in range(0, 8):
            self.render_list.append(DisplayMenu(i))
            
        self.max_menu_position = len(self.render_list) - 1
        
        self.render_list.append(self.poop_display_bar)
        self.render_list.append(self.stone_display_bar)
        self.render_list.append(self.tama_display_item)
        
    def submenu_dispatcher(self) -> None:
        global active_screen
        
        if self.menu_position == 0:
            active_screen = SubScreenHunger()
               
    def on_button_B_pressed(self):
        self.submenu_dispatcher()
            
            
main_screen: MainScreen = MainScreen()
            
                
class UserInput(object):
    def __init__(self) -> None:
        self.set_button_interrupt()
    
    def button_pressed_callback(self, channel):
        print("Button pressed!" + str(channel))

        if channel == BUTTON_A_GPIO:
            active_screen.on_button_A_pressed()
        elif channel == BUTTON_B_GPIO:
            active_screen.on_button_B_pressed()
        elif channel == BUTTON_C_GPIO:
            active_screen.on_button_C_pressed()
        else:
            raise Exception("Invalid button channel in interrupt")

    def set_button_interrupt(self) -> None:
        button_bouncetime = 150
        
        # add interupt for button A
        GPIO.setmode(GPIO.BCM)# type: ignore
        GPIO.setup(BUTTON_A_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)# type: ignore
        GPIO.add_event_detect(BUTTON_A_GPIO, GPIO.FALLING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)# type: ignore

        # add interupt for button B
        GPIO.setmode(GPIO.BCM)# type: ignore
        GPIO.setup(BUTTON_B_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)# type: ignore
        GPIO.add_event_detect(BUTTON_B_GPIO, GPIO.FALLING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)# type: ignore

        # add interupt for button C
        GPIO.setmode(GPIO.BCM)# type: ignore
        GPIO.setup(BUTTON_C_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)# type: ignore
        GPIO.add_event_detect(BUTTON_C_GPIO, GPIO.FALLING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)# type: ignore
        


class Logic(object):
    def __init__(self) -> None:
        self.birthday_time: float = time.time()
        self.sickness_value: int = 0
        self.care_errors: int = 0
            
        # set up pooping timer interval
        self.next_pooping_interval = time.time()
        self.cause_pooping()

        # set up hunger timer interval
        self.next_hunger_interval = time.time()
        self.cause_hunger()
        
        # set up sickness timer interval
        self.next_sickness_interval = time.time()
        self.cause_sickness()
        
    def get_polynomial_value(self) -> float:
        terms: list[float] = [
        9.9999999999997874e+002,
        5.9151704397609030e-003,
        -5.5089670016536930e-009,
        1.3956521653067459e-015
        ]
        t = 1
        result = 0
        for c in terms:
            result += c * t
            t *= (time.time() - self.birthday_time)
        return result
    
    def cause_pooping(self) -> None:
        if __debug__:
            print("DEBUG: Pooped")
        global main_screen    
        
        main_screen.poop_display_bar.poop_on_screen += 1
        
        self.next_pooping_interval += 30
        pooping_timer: threading.Timer = threading.Timer(self.next_pooping_interval - time.time(), self.cause_pooping)
        pooping_timer.start()


    def cause_hunger(self) -> None:
        if __debug__:
            print("DEBUG: hunger value increased by 1000")
        
        # Hunger value change still to be implemented

        self.next_hunger_interval += 5
        threading.Timer(self.next_hunger_interval - time.time(), self.cause_hunger).start()

    def add_sickness(self, amount: int) -> int:
        self.sickness_value += amount
        return self.sickness_value
    
    def cause_sickness(self) -> None:
        if main_screen.poop_display_bar.poop_on_screen >= 3:
        # add random sickness: more poop -> more sickness
            if random.randint(1, 10) > main_screen.poop_display_bar.poop_on_screen:
                self.add_sickness(math.floor(main_screen.poop_display_bar.poop_on_screen / 2))
        elif random.randint(1, 30) == 30:
            self.add_sickness(5)
        self.next_sickness_interval += 1
        threading.Timer(self.next_sickness_interval - time.time(), self.cause_sickness).start()

logic_class: Logic = Logic()


test_image: Image.Image = Image.new("1", (128, 64))


active_screen: BaseScreen = main_screen

UI = UserInput()

regulator: framerate_regulator = framerate_regulator(fps= 60)


while True:
    with regulator:
        active_screen.render()
        