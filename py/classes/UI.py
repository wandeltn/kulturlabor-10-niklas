import RPi.GPIO as GPIO
import luma.core.render
from PIL import Image
from luma.core.interface.serial import spi
from luma.oled.device import ssd1306

SPRITEMAP_MENU_PATH: str = ""
BUTTON_A_GPIO: int = 21
BUTTON_B_GPIO: int = 20
BUTTON_C_GPIO: int = 16


class Screen(object):
    def __init__(self):
        self.display_content = Image.new("L", (128, 64))
        self.render_list: list[object]

    def draw(self) -> None: 
        pass

active_screen: Screen

class DisplayMenu(object):
    def __init__(self, spritemap_index: int, position: tuple[int, int]):
        spritemap = Image.open(SPRITEMAP_MENU_PATH).convert("L")
        self.sprite_selected = spritemap.crop()


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
        
        
UI = UserInput()
