import RPi.GPIO as GPIO

BUTTON_A_GPIO = 21
BUTTON_B_GPIO = 20
BUTTON_C_GPIO = 16


class UserInput(object):
    def __init__(self) -> None:
        pass
    
    def button_pressed_callback(channel):
        print("Button pressed!")


    def set_button_interupt(self) -> None:
        button_bouncetime = 100
        
        # add interupt for button A
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(BUTTON_A_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.add_event_detect(BUTTON_A_GPIO, GPIO.FALLING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)

        # add interupt for button B
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(BUTTON_B_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.add_event_detect(BUTTON_B_GPIO, GPIO.FALLING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)

        # add interupt for button C
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(BUTTON_C_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.add_event_detect(BUTTON_C_GPIO, GPIO.FALLING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)
        



