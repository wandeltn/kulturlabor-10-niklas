import math
import time
import threading
import random 
import RPi.GPIO as GPIO
from PIL import Image, ImageOps
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

serial = spi()
device = ssd1306(serial)

class DisplayItem(object):
    def __init__(self):
        self.selected: bool = False
        
    def render(self, image: Image.Image) -> None:
        pass
    

class DisplayMenu(DisplayItem):
    def __init__(self, spritemap_index: int):
        super().__init__()
        
        spritemap = Image.open(SPRITEMAP_MENU_PATH).convert("L")
        self.sprite_unselected: Image.Image = spritemap.crop((spritemap_index * 16, 0, (spritemap_index + 1) * 16, 16))
        self.sprite_selected: Image.Image = ImageOps.invert(self.sprite_unselected)

        self.position_X: int = (spritemap_index // 4) * 112
        self.position_Y: int = (spritemap_index % 4) * 16
       
    def render(self, display: Image.Image):
        if self.selected:
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
    
    def render(self, display: Image.Image):
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
    
    def render(self, display: Image.Image):
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
        
        spritemap: Image.Image = Image.open(SPRITEMAP_EGG_PATH)
        
        self.sprite_0: Image.Image = spritemap.crop((
            self.evolution_state_spritemap_index_X * 48,
            self.evolution_state_spritemap_index_Y * 48,
            (self.evolution_state_spritemap_index_X + 1) * 48,
            (self.evolution_state_spritemap_index_Y + 1) * 48))
    
    def render(self, display: Image.Image):
        if self.evolution_state:                            # do not update in egg state
            if self.time_until_next_update == 0:            # wait until every 60th frame until position update
                self.time_until_next_update = -60
                
                change_position_X = random.randint(-2, 2)
                self.position_X += change_position_X
                self.position_Y += random.randint(-2, 2)
                if change_position_X:                      # change orientation of image if travelling to right
                    display.paste(ImageOps.mirror(self.sprite_0), (self.position_X, self.position_Y))
                else:
                    display.paste(self.sprite_0, (self.position_X, self.position_Y))
            else:
                self.time_until_next_update += 1
        else:
            display.paste(self.sprite_0, (self.position_X, self.position_Y))
        
        
class BaseScreen(object):
    def __init__(self):
        self.display_content: Image.Image = Image.new("1", (128, 64))
        self.render_list: list[DisplayItem] = []
        self.menu_position: int = 0
        self.max_menu_position: int
          
    def render(self) -> None: 
        for display_item in self.render_list:
            display_item.render(self.display_content)
            
        device.display(self.display_content)
            
    def on_button_A_pressed(self):
        pass
                
    def on_button_B_pressed(self):
        pass
                
    def on_button_C_pressed(self):
        pass
                      

class MainScreen(BaseScreen):
    def __init__(self):
        super().__init__()
        self.max_menu_position = 7
        self.poop_index_list: list[int] = []
        self.stone_display_bar: DisplayStoneBar = DisplayStoneBar()
        self.poop_display_bar: DisplayPoopBar = DisplayPoopBar()
        self.tama_display_item: DisplayTamaItem = DisplayTamaItem()
        
        for i in range(0, 8):
            self.render_list.append(DisplayMenu(i))
        
        self.render_list.append(self.poop_display_bar)
        self.render_list.append(self.stone_display_bar)
        self.render_list.append(self.tama_display_item)

    def on_button_A_pressed(self):
        self.render_list[self.menu_position].selected = False
        if self.menu_position >= self.max_menu_position:
            self.menu_position = 0
        else:
            self.menu_position += 1
        self.render_list[self.menu_position].selected = True
    
    def on_button_B_pressed(self):
        pass
    
    def on_button_C_pressed(self):
        self.render_list[self.menu_position].selected = False
        if self.menu_position <= 0:
            self.menu_position = self.max_menu_position
        else:
            self.menu_position -= 1
        self.render_list[self.menu_position].selected = True
            
            
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
        
  
# poop_on_screen incrementer / setter

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
        
        self.next_pooping_interval += 5
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