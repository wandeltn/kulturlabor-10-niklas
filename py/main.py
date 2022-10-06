import math
from random import random
import threading
import RPi.GPIO as GPIO
import luma.core.render
from PIL import Image, ImageOps
from luma.core.interface.serial import spi
from luma.oled.device import ssd1306
import time


SPRITEMAP_MENU_PATH: str = "/home/pi/Downloads/py/image.png"
BUTTON_A_GPIO: int = 21
BUTTON_B_GPIO: int = 20
BUTTON_C_GPIO: int = 16
            

class DisplayItem(object):
    def render(self, image: Image.Image):
        pass

class DisplayMenu(DisplayItem):
    def __init__(self, spritemap_index: int):
        self.selected: bool = False
        
        spritemap = Image.open(SPRITEMAP_MENU_PATH).convert("L")
        self.sprite_unselected: Image.Image = spritemap.crop((spritemap_index * 16, 0, (spritemap_index + 1) * 16, 16))
        self.sprite_selected: Image.Image = ImageOps.invert(self.sprite_unselected)

        self.position_X = (spritemap_index // 4) * 112
        self.position_Y = (spritemap_index % 4) * 16
       
    def render(self, display: Image.Image):
        if self.selected:
            display.paste(self.sprite_selected, (self.position_X, self.position_Y))
        else:
            display.paste(self.sprite_unselected, (self.position_X, self.position_Y))
    
class BaseScreen(object):
    def __init__(self):
        self.display_content: Image.Image = Image.new("1", (128, 64))
        self.render_list: list[DisplayItem]

    def draw(self) -> None: 
        for display_item in self.render_list:
            display_item.render(self.display_content)

class MainScreen(BaseScreen):
    def __init__(self):
        super()        

class UserInput(object):
    def __init__(self) -> None:
        self.set_button_interrupt()
    
    def button_pressed_callback(self, _caller, channel):
        print("Button pressed!" + str(channel))


    def set_button_interrupt(self) -> None:
        button_bouncetime = 100
        
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
        
poop_on_screen: int = 0
sickness_value: int = 0
care_errors: int = 0
  
# poop_on_screen incrementer / setter
def add_poop_to_screen(amount: int) -> int:
    global poop_on_screen
    poop_on_screen += amount
    return poop_on_screen

# sickness_value incrementer / setter
def add_sickness(amount: int) -> int:
    global sickness_value
    sickness_value += amount
    return sickness_value

class Logic(object):
    def __init__(self) -> None:
        # set up pooping timer interval
        self.next_pooping_interval = time.time()
        self.cause_pooping()

        # set up hunger timer interval
        self.next_hunger_interval = time.time()
        self.cause_hunger()
        
        # set up sickness timer interval
        self.next_sickness_interval = time.time()
        self.cause_sickness()

    def cause_pooping(self) -> None:
        if __debug__:
            print("DEBUG: Pooped")

        self.next_pooping_interval += 2
        timer_pooping: object = threading.Timer(self.next_pooping_interval - time.time(), self.cause_pooping).run

    def cause_hunger(self) -> None:
        if __debug__:
            print("DEBUG: hunger value increased by 1")
        
        # Hunger value change still to be implemented

        self.next_hunger_interval += 5
        timer_hunger: object = threading.Timer(self.next_hunger_interval - time.time(), self.cause_hunger).run()

    def cause_sickness(self) -> None:
        global poop_on_screen
        global care_errors
        if poop_on_screen >= 3:
        # add random sickness: more poop -> more sickness
            if random.randint(1, 10) > poop_on_screen:
                add_sickness(math.floor(poop_on_screen / 2))
        elif random.randint(1, 30) == 30:
            add_sickness(5)
        self.next_sickness_interval += 1
        timer_sickness: object = threading.Timer(self.next_sickness_interval - time.time(), self.cause_sickness).run()
        if __debug__:
            print("DEBUG: set sickness interval")





serial = spi()
device = ssd1306(serial)
active_screen: BaseScreen

test_image: Image.Image = Image.new("1", (128, 64))


while True:
    for i in 0, 1, 2, 3, 4, 5, 6, 7:
        menu_item: DisplayMenu = DisplayMenu(i)
        menu_item.render(test_image)
    device.display(test_image)

UI = UserInput()
