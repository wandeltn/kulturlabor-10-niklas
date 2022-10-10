import math
import time
import threading
import random
from typing import Callable 
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
        display.paste(self.sprite, self.position)
        

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
    
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        return display
          
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
             
            
class SubDisplayMenu(DisplayItem):
    def __init__(self, text_render_list: list[str], x_axis_offset: int= 0):
        super().__init__()
        self.text_render_list: list[str] = text_render_list
        self.x_axis_offset: int = x_axis_offset
        
        self.text_image = Image.new("L", (128, 64))
        self.clear_text_image: Image.Image = self.text_image.copy()
        
    def render(self, display: Image.Image, menu_position: int):
        self.text_image = self.clear_text_image.copy()
        display_draw: ImageDraw.ImageDraw = ImageDraw.Draw(self.text_image)
        display_draw = active_screen.get_current_stats(display_draw)
                
        list_index = 0
        for food_item in self.text_render_list:
            if list_index == menu_position:
                display_draw.text(
                    (50, (list_index * 8) - 1 + self.x_axis_offset),        # position of text
                    "» " + food_item,                                       # text to be added
                    (255))
            else:
                display_draw.text(
                (50, (list_index * 8) - 1 + self.x_axis_offset),            # position of text
                    "  " + food_item,                                       # text to be added
                    (255))                                                  # color of the text
            list_index += 1
        
        display.paste(self.text_image)

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
        
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        display.text((0, 55), str(logic_class.calories_intake_value), (255))
        return display
    
    def on_button_B_pressed(self):
        if self.menu_position <= 6:
            global logic_class
            logic_class.calories_intake_value += list(self.food_items_dict.values())[self.menu_position]
            if __debug__:
                print("added calories: " + str(list(self.food_items_dict.values())[self.menu_position]))
        else:
            global active_screen
            active_screen = main_screen
    
            
class SubScreenLight(BaseScreen):
    def __init__(self):
        super().__init__()
        self.options_list: dict[str, Callable] = {
            "Turn on": self.light_turn_on,
            "Turn off": self.light_turn_off,
            "Exit": self.exit
        }
        
        self.menu_position = 0
        self.max_menu_position = 2
        
        self.render_list.append(SubDisplayMenu(list(self.options_list.keys()), 24))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (16, 0, 32, 16), (0, 16)))

    def light_turn_on(self):
        global logic_class
        logic_class.light_on = True
    
    def light_turn_off(self):
        global logic_class
        logic_class.light_on = False
    
    def exit(self):
        global active_screen
        active_screen = main_screen
        
    def on_button_B_pressed(self):
        action = list(self.options_list.values())[self.menu_position]
        action()
        

class SubScreenPlay(BaseScreen):
    def __init__(self):
        super().__init__()
        
        """
        first int in value  -> happyness_value to be added
        second int in value -> healthyness of activity
        """
        self.options_list: dict[str, tuple[int, int]] = {       
            "Soccer": (5, 5),
            "Badminton": (5, 5),
            "Icehockey": (5, 5),
            "Chess": (5, 0),
            "Cards": (5, 0),
            "Exit": (0, 0)
        }
        
        self.menu_position = 0
        self.max_menu_position = 5
        
        self.render_list.append(SubDisplayMenu(list(self.options_list.keys()), 8))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (16, 0, 32, 16), (0, 32)))
        
    def on_button_B_pressed(self):
        if self.menu_position <= 4:
            global logic_class
            logic_class.sickness_value -= list(self.options_list.values())[self.menu_position][0]
            logic_class.happyness_value += list(self.options_list.values())[self.menu_position][1]
        else:
            global active_screen
            active_screen = main_screen
            
class SubScreenMedicine(BaseScreen):
    def __init__(self):      
        super().__init__()
        
        self.options_list: dict[str, int] = {
            "Vaccination": 10,
            "Medicine": 10, 
            "Doctor": 5,
            "Exit": 0
        }
        self.menu_position = 0
        self.max_menu_position = 3
        
        self.render_list.append(SubDisplayMenu(list(self.options_list.keys()), 16))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (32, 0, 48, 16), (0, 48)))

    def on_button_B_pressed(self):
        global logic_class
        if self.menu_position <= 2:
            logic_class.sickness_value -= list(self.options_list.values())[self.menu_position]
        else:
            global active_screen
            active_screen = main_screen


class SubScreenPoop(BaseScreen):
    def __init__(self):
        super().__init__()
        
        self.options_list: dict[str, Callable] = {
            "Clear poop": self.clear_poop_from_screen,
            "Exit": self.exit
        }
        self.menu_position = 0
        self.max_menu_position = 1
        
        self.render_list.append(SubDisplayMenu(list(self.options_list.keys()), 24))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (48, 0, 64, 16), (112, 0)))
        
    def clear_poop_from_screen(self):
        global main_screen
        main_screen.poop_display_bar.poop_on_screen = 0
        
    def exit(self):
        global active_screen
        active_screen = main_screen
        
    def on_button_B_pressed(self):
        action = list(self.options_list.values())[self.menu_position]
        action()


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
        elif self.menu_position == 1:
            active_screen = SubScreenLight()
        elif self.menu_position == 2:
            active_screen = SubScreenPlay()
        elif self.menu_position == 3:
            active_screen = SubScreenMedicine()
        elif self.menu_position == 4:
            active_screen = SubScreenPoop()
               
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
        self.care_errors: int = 0
        self.birthday_time: float = time.time()
        
        self.calories_intake_value: int = 2000
        self.last_calorie_needed: int = 2000
        self.sickness_value: int = 0
        self.happyness_value: int = 50
        self.weight_in_stones: int = 50
        
        self.sleeping: bool = False
        self.light_on: bool = True
            
        # set up pooping timer interval
        self.next_pooping_interval = time.time()
        self.cause_pooping()

        # set up hunger timer interval
        self.next_hunger_interval = time.time()
        self.cause_hunger()
        
        # set up sickness timer interval
        self.next_sickness_interval = time.time()
        self.cause_sickness()
        
        # set up next weigth check
        self.next_weight_check_interval = time.time()
        self.update_weight()
        
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
            print("DEBUG: hunger value increased to: " + str(self.calories_intake_value))
        
        self.calories_intake_value -= round(self.get_polynomial_value())
        
        self.next_hunger_interval += 40
        threading.Timer(self.next_hunger_interval - time.time(), self.cause_hunger).start()
    
    def cause_sickness(self) -> None:
        if main_screen.poop_display_bar.poop_on_screen >= 3:
        # add random sickness: more poop -> more sickness
            if random.randint(1, 10) > main_screen.poop_display_bar.poop_on_screen:
                self.sickness_value += math.floor(main_screen.poop_display_bar.poop_on_screen / 2)
        elif random.randint(1, 30) == 30:
            self.sickness_value += 5
        self.next_sickness_interval += 1
        threading.Timer(self.next_sickness_interval - time.time(), self.cause_sickness).start()
        
    def update_weight(self) -> None:
        if self.last_calorie_needed - 1500 >= self.calories_intake_value:
            self.weight_in_stones -= (self.last_calorie_needed - self.calories_intake_value) // 1500
        elif self.last_calorie_needed + 1500 <= self.calories_intake_value:
            self.weight_in_stones += (self.calories_intake_value - self.last_calorie_needed) // 1500 
            
        self.next_weight_check_interval += 60
        threading.Timer(self.next_weight_check_interval - time.time(), self.update_weight).start()

logic_class: Logic = Logic()


test_image: Image.Image = Image.new("1", (128, 64))


active_screen: BaseScreen = main_screen

UI = UserInput()

regulator: framerate_regulator = framerate_regulator(fps= 60)


while True:
    with regulator:
        active_screen.render()
        