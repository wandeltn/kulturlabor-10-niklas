import math
import time
import threading
import random
from typing import Callable 
import RPi.GPIO as GPIO #type: ignore
from PIL import Image, ImageOps, ImageDraw, ImageFont
from luma.core.interface.serial import spi
from luma.oled.device import ssd1306
from luma.core.sprite_system import framerate_regulator


SPRITEMAP_MENU_PATH: str = "/home/pi/Downloads/py/img/image.png"
SPRITEMAP_POOP_PATH: str = "/home/pi/Downloads/py/img/poop_menu_icon.png"
SPRITEMAP_STONE_PATH: str = "/home/pi/Downloads/py/img/stone_icon.png"
SPRITEMAP_EGG_PATH: str = "/home/pi/Downloads/py/img/spritemap_egg_stage.png"
PIXEL_FONT_PATH: str = "/home/pi/Downloads/py/img/slkscre.ttf"

BASE_PATH: str = "/home/pi/Downloads/py/img/"
SPRITEMAP_EVOLUTION_STAGES: list[str] = [
    BASE_PATH + "spritemap_egg_stage.png",
    BASE_PATH + "spritemap_baby_stage.png",
    BASE_PATH + "spritemap_teen_stage.png",
    BASE_PATH + "spritemap_adult_stage_test.png",
    BASE_PATH + "spritemap_senior_stage.png"
]

BUTTON_A_GPIO: int = 21
BUTTON_B_GPIO: int = 20
BUTTON_C_GPIO: int = 16

serial: spi = spi()
device: ssd1306 = ssd1306(serial)

class DisplayItem(object):
    """
    Base Class for any item to be displayed by iteration over the render function. Should NOT be created by instancing this class.
    """
    def __init__(self):
        self.selected: bool = False
        
    def render(self, image: Image.Image, menu_position: int) -> None:
        pass
    
    
class DisplaySprite(DisplayItem):
    """display a chosen sprite on a given locaiton on the screen

    Args:
        DisplayItem (DisplayItem): A displayable subclass of the DisplayItem parent
    """
    def __init__(self, path: str, spritemap_position: tuple[int, int, int, int], display_position: tuple[int, int]):
        """Initialize the DisplaySprite class. The class is a subclass of the DisplayItem class, this makes this a displayable class

        Args:
            path (str): path of where to find the spritemap to display a section of
            spritemap_position (tuple[int, int, int, int]): where to find the image to sisplay on the spritemap. Upper left and lower right corners
            display_position (tuple[int, int]): where to paste the cut image on the display
        """
        super().__init__()
        spritemap: Image.Image = Image.open(path)
        self.sprite: Image.Image = spritemap.crop(spritemap_position)
        
        self.position = display_position 
        
    def render(self, display: Image.Image, _menu_position: int):
        """paste the finished, cut image onto the chosen locaiton on the screen

        Args:
            display (Image.Image): Image on whisch to paste the image
            _menu_position (int): not used
        """
        display.paste(self.sprite, self.position)
        
        
class DisplayVerticalValueBar(DisplayItem):
    def __init__(self, position: tuple[int, int, int, int], fill_height: int):
        """Initialize the VerticalValueBar, this will build a class which will display a vertical progressbar onto the display on call of the render method

        Args:
            position (tuple[int, int, int, int]): where to paste the ValueBar on the display
            fill_height (int): until which y position on the screen to fill the ValueBar
        """
        self.position: tuple[int, int, int, int] = position
        self.fill_height: int = fill_height
    
    def render(self, display: Image.Image, _menu_position):
        """render the ValueBar onto the given Image

        Args:
            display (Image.Image): the image for the ValueBar to be displayed on
            _menu_position (int): not used in this context
        """
        display_draw = ImageDraw.Draw(display)
        display_draw.rectangle(self.position, "black", "white")
        display_draw.rectangle((self.position[0], self.fill_height) + (self.position[2], self.position[3]), "white", "white")
        
        
class DisplayHorizontalValueBar(DisplayItem):
    def __init__(self, position: tuple[int, int, int, int], fill_height: int):
        """Initialize the VerticalValueBar, this will build a class which will display a vertical progressbar onto the display on call of the render method

        Args:
            position (tuple[int, int, int, int]): where on the screen the ValueBar schould be rendered to. Upper left corner
            fill_height (int): until which x value to fill the ValueBar to
        """
        self.position: tuple[int, int, int, int] = position
        self.fill_height: int = fill_height
    
    def render(self, display: Image.Image, _menu_position: int):
        """render the ValueBar to the given Image

        Args:
            display (Image.Image): the image for the ValueBar to be displayed on
            _menu_position (int): not used in this context
        """
        display_draw = ImageDraw.Draw(display)
        display_draw.rectangle(self.position, "black", "white")
        display_draw.rectangle((self.position[0], self.position[1]) + (self.fill_height, self.position[3]), "white", "white")
        

class DisplayMenu(DisplayItem):
    def __init__(self, spritemap_index: int):
        """generate a main menu item to be navigated over by the buttons

        Args:
            spritemap_index (int): which item of the spritemap to display, hereby also giving the position of the image
        """
        super().__init__()
        self.spritemap_index = spritemap_index
        
        spritemap = Image.open(SPRITEMAP_MENU_PATH).convert("L")
        self.sprite_unselected: Image.Image = spritemap.crop((spritemap_index * 16, 0, (spritemap_index + 1) * 16, 16))
        self.sprite_selected: Image.Image = ImageOps.invert(self.sprite_unselected)

        self.position_X: int = (spritemap_index // 4) * 112
        self.position_Y: int = (spritemap_index % 4) * 16
       
    def render(self, display: Image.Image, menu_position: int):
        """render the single item in the given position, also checking if has to display as inverted

        Args:
            display (Image.Image): Image to paste the menu item to
            menu_position (int): which item of the menu is currently selected, given to display as inverted as needed
        """
        if self.spritemap_index == menu_position:
            display.paste(self.sprite_selected, (self.position_X, self.position_Y))
        else:
            display.paste(self.sprite_unselected, (self.position_X, self.position_Y))
    
    
class DisplayPoopBar(DisplayItem):
    def __init__(self):
        """generate a poop menu bar on the right side of the screen, also saves how many poop images to display
        """
        super().__init__()
        self.poop_on_screen: int = 0
        
        spritemap: Image.Image = Image.open(SPRITEMAP_POOP_PATH).convert("L")
        self.sprite_unselected: Image.Image = spritemap.crop((0, 0, 5 ,6))
        self.sprite_selected: Image.Image = spritemap.crop((5, 0, 10, 6))
    
    def render(self, display: Image.Image, _menu_position: int):
        """render the correct amount of poop images to the screen

        Args:
            display (Image.Image): the screen to paste the images to
            _menu_position (int): not used in this context
        """
        for poop_index in range(self.poop_on_screen):
            if self.selected:
                display.paste(self.sprite_selected, (106, poop_index * 8))
            else:
                display.paste(self.sprite_unselected, (106, poop_index * 8))
            

class DisplayStoneBar(DisplayItem):
    def __init__(self, stones_on_screen: int = 4):
        """generate a stone menu bar on the left of the screen to show the weight of the tama

        Args:
            stones_on_screen (int, optional): how many stones to start displaying with, before gathering the data. Defaults to 4.
        """
        super().__init__()
        self.sprite: Image.Image = Image.open(SPRITEMAP_STONE_PATH)
        
        self.stones_on_screen: int = stones_on_screen
    
    def render(self, display: Image.Image, _menu_position: int):
        """render the correct amount of stones to the screen

        Args:
            display (Image.Image): the screen to paste the stones to
            _menu_position (int): not used in this context
        """
        global logic_class
        self.stones_on_screen = round((logic_class.weight_value / 100) * 8)
        for stone_index in range(self.stones_on_screen):
            display.paste(self.sprite, (17, stone_index * 8))
            

class DisplayTamaItem(DisplayItem):
    """Generate the main tama in the middle of the main menu

    Args:
        DisplayItem (DisplayItem): Subclass of the displayable DisplayItem class, therefore can be rendered
    """
    def __init__(self):
        """generate the tama by openign the spritemap. Also sets the first evolution timer
        """
        self.evolution_state: int = 0
        
        self.time_until_next_update: int = -30
        
        self.position_X: int = 30
        self.position_Y: int = 0
        self.facing_right: bool = False
        
        spritemap: Image.Image = Image.open(SPRITEMAP_EVOLUTION_STAGES[self.evolution_state])
        
        self.sprite_0: Image.Image = spritemap.crop((0, 0, 48, 48))
        
        threading.Timer(3600, self.evolve).start()
        
    def evolve(self) -> None:
        """random rvolution stage advance of the tama
        TODO: Weighted evolution based on care errors
        """
        spritemap: Image.Image
        position_X: int = 0
        position_Y: int = 0
        
        spritemap = Image.open(SPRITEMAP_EVOLUTION_STAGES[self.evolution_state])
        width, height = spritemap.size
    
        position_X = random.randint(0, (width // 48))
        position_Y = random.randint(0, (height // 96))
        
        self.sprite_0: Image.Image = spritemap.crop((
            position_X * 48,
            position_Y * 48,
            (position_X + 1) * 48,
            (position_Y + 1) * 48))
        
        self.evolution_state += 1
        if self.evolution_state <= 4:
            global logic_class    
            threading.Timer((logic_class.get_polynomial_value() * 30), self.evolve).start()
        
        
    def get_next_sprite_position(self):
        """generate the next random position within the bounding boxes for the tama to move to
        """
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
        """render the tama in the randomly generated position on the screen

        Args:
            display (Image.Image): screen to render the tama to
            _menu_position (int): not used in this context
        """
        if self.evolution_state:                            # do not update in egg state
            if self.time_until_next_update == 0:            # wait until every 30th frame until position update
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
    """BaseClass for all classes containing a user interactable menu. NOT to be created as own instance

    Args:
        object (object): doesnt inherit anything special
    """
    def __init__(self):
        """create the base properties of a menu screen
        """
        self.display_content: Image.Image = Image.new("1", (128, 64))
        self.display_content_clear = self.display_content.copy()
        self.render_list: list[DisplayItem] = []
        self.menu_position: int = 0
        self.max_menu_position: int = 0
        
    def on_menu_position_changed(self) -> None:
        """the event called when the menu position is changed
        """
        pass
    
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        """draw the current stats onto the screen, overridden by subclass

        Args:
            display (ImageDraw.ImageDraw): display to write the stats to

        Returns:
            ImageDraw.ImageDraw: finished display containing the stats
        """
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
    
    def exit(self):
        global active_screen
        active_screen = main_screen
             
            
class SubDisplayMenu(DisplayItem):
    """Baseclass for all the submenus in the UI

    Args:
        DisplayItem (DisplayItem): can not be rendered onto the screen in the render_list
    """
    def __init__(self, text_render_list: list[str], y_axis_offset: int= 0, x_axis_offset: int= 0):
        """generate the new image for the screen

        Args:
            text_render_list (list[str]): list of options the user can navigate through
            y_axis_offset (int, optional): y axis offset of the menu. Defaults to 0.
            x_axis_offset (int, optional): x axis offset of the menu. Defaults to 0.
        """
        super().__init__()
        self.text_render_list: list[str] = text_render_list
        self.y_axis_offset: int = y_axis_offset
        self.x_axis_offset: int = x_axis_offset
        
        self.text_image = Image.new("L", (128, 64))
        self.clear_text_image: Image.Image = self.text_image.copy()
        
    def render(self, display: Image.Image, menu_position: int):
        """display the submenu onto the display

        Args:
            display (Image.Image): screen to render the submenu to
            menu_position (int): which item in the list is to be displayed highlighted
        """
        self.text_image = self.clear_text_image.copy()
        display_draw: ImageDraw.ImageDraw = ImageDraw.Draw(self.text_image)
        display_draw = active_screen.get_current_stats(display_draw)
                
        list_index = 0
        for food_item in self.text_render_list:
            if list_index == menu_position:
                display_draw.text(
                    (25 + self.x_axis_offset, (list_index * 8) - 1 + self.y_axis_offset),        # position of text
                    "» " + food_item,                                       # text to be added
                    (255))
            else:
                display_draw.text(
                    (25 + self.x_axis_offset, (list_index * 8) - 1 + self.y_axis_offset),            # position of text
                    "  " + food_item,                                       # text to be added
                    (255))                                                  # color of the text
            list_index += 1
        
        display.paste(self.text_image)


class SubScreenHunger(BaseScreen):
    """Subscreen to select item for the tama to eat

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """set up options to be rendered as selectables on screen
        """
        super().__init__()
        self.food_items_dict: dict[str, tuple[int, int]] = {
            "Burger": (520, -2),
            "Pasta": (280, -1),
            "Muffin": (440, -2),
            "Broccoli": (30, 2),
            "Salad": (235, 3),
            "Sushi": (150, 0),
            "Crepes": (180, 2),
            "Exit": (0, 0)
        }
        
        self.max_menu_position = 7
        self.render_list.append(SubDisplayMenu(list(self.food_items_dict)))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (0, 0, 16, 16), (0, 0)))
        
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        """get the current hunger value to be displayed in the bottom left corner of the screen

        Args:
            display (ImageDraw.ImageDraw): display to write the value to

        Returns:
            ImageDraw.ImageDraw: New display with the new text on it
        """
        display.text((0, 55), str(logic_class.calories_intake_value), (255))
        return display
    
    def on_button_B_pressed(self):
        """handle what to do when the middle button is pressed
        TODO: animation or delay after eating to prevent over feeding
        """
        if self.menu_position <= 6:
            global logic_class
            logic_class.calories_intake_value += list(self.food_items_dict.values())[self.menu_position][0]
            logic_class.diet_health_counter += list(self.food_items_dict.values())[self.menu_position][1]
            logic_class.healthyness_value += logic_class.diet_health_counter
        else:
            global active_screen
            active_screen = main_screen
    
            
class SubScreenLight(BaseScreen):
    """Subscreen for the user to select the status of the light to enable the tama to sleep

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """initialize the light menu options
        """
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
        """turn the light_on variable to True
        """
        global logic_class
        logic_class.light_on = True
    
    def light_turn_off(self):
        """turn the light_on variable to False
        """
        global logic_class
        logic_class.light_on = False
        
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        """display the current status of the light in the botton left corner of the screen

        Args:
            display (ImageDraw.ImageDraw): the screen for the text to be rendered to

        Returns:
            ImageDraw.ImageDraw: the new image containing the new text
        """
        display.text((0, 55), " " + str(logic_class.light_on), (255))
        return display
        
    def on_button_B_pressed(self):
        """execute the assgned funtction in case of pressing the middle button
        """
        action = list(self.options_list.values())[self.menu_position]
        action()
        

class SubScreenPlay(BaseScreen):
    """subscreen to manage the happyness of the tama

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """define the menu options and other required information
        """
        super().__init__()
        
        # first int in value  -> happyness_value to be added
        # second int in value -> healthyness of activity
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
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (32, 0, 48, 16), (0, 32)))
    
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        """print current happyness in the bottom left corner of the screen

        Args:
            display (ImageDraw.ImageDraw): the display on which to paste the stats

        Returns:
            ImageDraw.ImageDraw: finished display containing the stats
        """
        display.text((0, 0), " " + str(logic_class.happyness_value), (255))
        return display
        
    def on_button_B_pressed(self):
        """add the specified happyness value of the selected menu item
        """
        if self.menu_position <= 4:
            global logic_class
            logic_class.happyness_value += list(self.options_list.values())[self.menu_position][0]
            logic_class.healthyness_value -= list(self.options_list.values())[self.menu_position][1]
        else:
            global active_screen
            active_screen = main_screen

   
class SubScreenMedicine(BaseScreen):
    """sub screen to manage the sickness of the tama

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """define the menu options and other required information
        """
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
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (48, 0, 64, 16), (0, 48)))
        
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        """write the current helath info in the top left corner of the screen

        Args:
            display (ImageDraw.ImageDraw): display on which to write the stats

        Returns:
            ImageDraw.ImageDraw: finished display containing the stats
        """
        display.text((0, 0), " " + str(logic_class.healthyness_value), (255))
        return display

    def on_button_B_pressed(self):
        """add the health value of the selected menu item
        """
        global logic_class
        if self.menu_position <= 2:
            logic_class.healthyness_value += list(self.options_list.values())[self.menu_position]
        else:
            global active_screen
            active_screen = main_screen


class SubScreenPoop(BaseScreen):
    """subscreen to manage the amount of poop icons on screen

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """define the menu options and other required information
        """
        super().__init__()
        
        self.options_list: dict[str, Callable] = {
            "Clear poop": self.clear_poop_from_screen,
            "Exit": self.exit
        }
        self.menu_position = 0
        self.max_menu_position = 1
        
        self.render_list.append(SubDisplayMenu(list(self.options_list.keys()), 24, -22))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (64, 0, 80, 16), (112, 0)))
        
    def clear_poop_from_screen(self):
        """clear all poop icons from screen
        """
        global main_screen
        main_screen.poop_display_bar.poop_on_screen = 0
        
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        """write the current amount of poop icons on screen in the lower right corner of the screen

        Args:
            display (ImageDraw.ImageDraw): display on which to write the stats

        Returns:
            ImageDraw.ImageDraw: finished display containing the stats
        """
        display.text((120, 55),str(main_screen.poop_display_bar.poop_on_screen) + " ", (255))
        return display
        
    def on_button_B_pressed(self):
        """call the assigned funtction of the selected menu item
        """
        action = list(self.options_list.values())[self.menu_position]
        action()
        
        
class SubScreenHealth(BaseScreen):
    """subscreen to view the current helath status of the tama

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """define the menu items and collect font file
        """
        super().__init__()

        self.options_list: dict[str, Callable] = {
            "Exit": self.exit
        }

        self.menu_position = 0
        self.max_menu_position = 0
        self.font = ImageFont.truetype(PIXEL_FONT_PATH, 8)
        
        self.render_list.append(SubDisplayMenu(list(self.options_list.keys()), 55, -22))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (80, 0, 96, 16), (112, 16)))
        
    def on_button_B_pressed(self):
        """execute the assigned function of the selected menu item.
        Always defaults to exiting to the main screen
        """
        action = list(self.options_list.values())[self.menu_position]
        action()

    def render(self) -> None: 
        """render four horizontal valueBars to represent the current stats of the tama
        """
        self.display_content = self.display_content_clear.copy()
        for display_item in self.render_list:
            display_item.render(self.display_content, self.menu_position)
            
        index: int = 0
        logic_class_summary: dict[str, int] = logic_class.get_stats_summary()
        display_draw: ImageDraw.ImageDraw = ImageDraw.Draw(self.display_content)
        for display_item in logic_class_summary:
            display_draw.text((5, index * 14), str(display_item), (255), font=self.font)
            render_item: DisplayHorizontalValueBar = DisplayHorizontalValueBar((2, (index * 14) + 8, 102, (index * 14) + 12), logic_class_summary[display_item])
            render_item.render(self.display_content, self.menu_position)
            index += 1
            
        device.display(self.display_content)


class SubScreenDicipline(BaseScreen):
    """subscreen to manage the dicipline of the tama

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """define the menu items and other reqired info
        """
        super().__init__()       
        
        self.options_list: dict[str, int] = {
            "Time together": 1,
            "Set expectations": 1, 
            "Use concequences": 2,
            "Do an activity": 2,
            "Exit": 0
        }
        
        self.menu_position = 0
        self.max_menu_position = 4
        
        self.render_list.append(SubDisplayMenu(list(self.options_list.keys()), 12, -22))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (96, 0, 112, 16), (112, 32)))
        
    def get_current_stats(self, display: ImageDraw.ImageDraw) -> ImageDraw.ImageDraw:
        """write the current dicipline value into the upper right corner of the screen

        Args:
            display (ImageDraw.ImageDraw): display to write the stats to

        Returns:
            ImageDraw.ImageDraw: finished display containing the stats
        """
        display.text((110, 0),str(logic_class.dicipline_value) + " ", (255))
        return display

    def on_button_B_pressed(self):
        """add the corresponding dicipline value of the selected menu item to the dicipline value
        """
        global logic_class
        if self.menu_position <= 3:
            logic_class.dicipline_value += list(self.options_list.values())[self.menu_position]
        else:
            global active_screen
            active_screen = main_screen
            
            
class SubScreenAttention(BaseScreen):
    """subscreen to manage the attention of the tama
    TODO: currently doesnt have a purpose

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """define the selectable menu items and other required info
        """
        super().__init__()
        
        self.options_list: dict[str, Callable] = {
            "Exit": self.exit
        }
        
        self.menu_position = 0
        self.max_menu_position = len(self.options_list) - 1
        x_text_position_offset: int = (64 - (len(self.options_list) * 8)) // 2
        self.render_list.append(SubDisplayMenu(list(self.options_list.keys()), x_text_position_offset, -22))
        self.render_list.append(DisplaySprite(SPRITEMAP_MENU_PATH, (112, 0, 128, 16), (112, 48)))
        
        
    def on_button_B_pressed(self):
        """execute the assigned function of the selected menu item, currently defaults to exiting to the main screen
        """
        action = list(self.options_list.values())[self.menu_position]
        action()
    

class MainScreen(BaseScreen):
    """Main screen of the tamagotchi. From here all submenus can be accessed by navigiting using the buttons

    Args:
        BaseScreen (BaseScreen): can be natively be rendered in the render_list
    """
    def __init__(self):
        """initialize the status classes and render the menu items
        """
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
        """display the assigned submenu determined by the position of the menu cursor
        """
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
        elif self.menu_position == 5:
            active_screen = SubScreenHealth()
        elif self.menu_position == 6:
            active_screen = SubScreenDicipline()
        elif self.menu_position == 7:
            active_screen = SubScreenAttention()
               
    def on_button_B_pressed(self):
        self.submenu_dispatcher()
            
            
main_screen: MainScreen = MainScreen()
"""main screen, to be written in the active_screen to be shown on screen
"""            
                
class UserInput(object):
    """gather the pressing of the buttons and call the designated functions 

    Args:
        object (object): no specific parent functions
    """
    def __init__(self) -> None:
        """set the interrupts to be called on button pressed
        """
        self.set_button_interrupt()
    
    def button_pressed_callback(self, channel):
        """funciton to be called when any button is pressed

        Args:
            channel (int): GPIO pin number of the button pressed

        Raises:
            Exception: Exception raised if the GPIO pin given is not recognized
        """
        print("Button pressed!" + str(channel))
        
        global logic_class
        logic_class.turn_on_screen()

        if channel == BUTTON_A_GPIO:
            active_screen.on_button_A_pressed()
        elif channel == BUTTON_B_GPIO:
            active_screen.on_button_B_pressed()
        elif channel == BUTTON_C_GPIO:
            active_screen.on_button_C_pressed()
        else:
            raise Exception("Invalid button channel in interrupt")

    def set_button_interrupt(self) -> None:
        """set the button interrupts to be called on button pressed
        """
        button_bouncetime = 150
        """time after button press to ignore a second press as this might be called because of button malfunction
        """
        
        # add interupt for button A
        GPIO.setmode(GPIO.BCM)# type: ignore
        GPIO.setup(BUTTON_A_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)# type: ignore
        GPIO.add_event_detect(BUTTON_A_GPIO, GPIO.RISING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)# type: ignore

        # add interupt for button B
        GPIO.setmode(GPIO.BCM)# type: ignore
        GPIO.setup(BUTTON_B_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)# type: ignore
        GPIO.add_event_detect(BUTTON_B_GPIO, GPIO.RISING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)# type: ignore

        # add interupt for button C
        GPIO.setmode(GPIO.BCM)# type: ignore
        GPIO.setup(BUTTON_C_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)# type: ignore
        GPIO.add_event_detect(BUTTON_C_GPIO, GPIO.RISING, callback=self.button_pressed_callback, bouncetime=button_bouncetime)# type: ignore
        


class Logic(object):
    """class to handle the status and logic of the tama

    Args:
        object (object): does not inherit any specific functions
    """
    def __init__(self) -> None:
        """initialze the interrupts and the enviroment variables of the tama
        """
        self.care_errors: int = 0
        """how many times the player has disregarded the needs of the tama
        """
        self.birthday_time: float = time.time()
        """time when the tama was created
        """
        self.diet_health_counter: int = 0
        """counter of how much health is going to be added or subtracted when the tama eats.
        Gets less if the tama does not eat healthy, and vice versa
        """
        
        self.calories_intake_value: int = 0
        """how many calories the tama needs to survive.
        Negative values means it has to eat more if it doesnt it will lose in weght. 
        Positive values over a specific value means it will gain in weight.
        """
        self.healthyness_value: int = 50
        """health value of the tama, if it sinks to low the tama will die
        """
        self.happyness_value: int = 50
        """happyness value of the tama, sinks over time. If not maintained at acceptable level tama will die
        """
        self.weight_value: int = 50
        """weight of the tama, displayed as stones in the main menu
        If it sinks to low or rises to high the tama will die
        """
        self.dicipline_value: int = 50
        """dicipline value of the tama, this effects the evolution of the tama.
        A lower value is better.
        """
        
        self.sleeping: bool = False
        """saves if the tama is currently sleeping
        """
        self.light_on: bool = True
        """saves if the light is turned on oround the tama, this will effect its sleeping quality
        """
        self.screen_on: bool = False
        """saves if the screen is supposed to be rendered or it is in power saving mode
        """
        
        self.screen_sleep_time: int = 20
        """the duration idle until the screen turns off and goes into power saving mode
        """
        self.next_screen_timeout_interval: float = time.time()
        """set the time at which the screen will turn off
        """
        timer = threading.Timer(self.next_screen_timeout_interval - time.time(), self.turn_off_screen)
        self.screen_sleep_timer: threading.Timer = timer
        """save the async timer to cancel it on button pressed
        """
            
        # set up pooping timer interval
        self.next_pooping_interval = time.time()
        """the time at which the tama will add poop to the screen
        """
        self.cause_pooping()
        
        # set up hunger timer interval
        self.next_hunger_interval = time.time()
        """the time at which the tama will have more hunger
        """
        self.cause_hunger()
        
        # set up sickness timer interval
        self.next_sickness_interval = time.time()
        """the time at which the tama will have the next chance of getting sick
        """
        self.cause_sickness()
        
        # set up next weigth check
        self.next_weight_check_interval = time.time()
        """the time at which the tama will check to gain or lose in weight
        """
        self.cause_update_weight()
        
        # set up logging timer interval
        self.next_log_to_csv_interval = time.time()
        self.write_status_to_csv()
        
    def get_polynomial_value(self) -> float:
        """get the value of the polynomial curve to gather values for:
        1. hunger
        2. poop
        3. next evolution stage

        Returns:
            float: get the point on the y axis corresponding to the x axis being the age in seconds after the birth of the tama
        """
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
        """add poop to the screen
        
        Also set the next time this function shall be called
        """
        
        global main_screen    
        
        main_screen.poop_display_bar.poop_on_screen += 1
        
        self.next_pooping_interval += 30
        pooping_timer: threading.Timer = threading.Timer(self.next_pooping_interval - time.time(), self.cause_pooping)
        pooping_timer.start()


    def cause_hunger(self) -> None:
        """add hunger to the hunger_value. 
        
        Also set the next time this function shall be called
        """
        
        self.calories_intake_value -= round(self.get_polynomial_value())
        
        self.next_hunger_interval += 40
        threading.Timer(self.next_hunger_interval - time.time(), self.cause_hunger).start()
    
    def cause_sickness(self) -> None:
        """randomly add sickness to the tama, this value is affected by the amount of poop on screen. 
        
        Also set the next time this funtion shall be called
        """
        if main_screen.poop_display_bar.poop_on_screen >= 3:
        # add random sickness: more poop -> more sickness
            if random.randint(1, 10) < main_screen.poop_display_bar.poop_on_screen:
                self.healthyness_value += math.floor(main_screen.poop_display_bar.poop_on_screen / 2)
        elif random.randint(1, 30) == 30:
            self.healthyness_value += 5
        self.next_sickness_interval += 1
        threading.Timer(self.next_sickness_interval - time.time(), self.cause_sickness).start()
        
    def cause_update_weight(self) -> None:
        """update the weight of the tama.
        
        Weight change has a tolorance of +- 500
        """
        if -500 >= self.calories_intake_value:
            self.weight_value += self.calories_intake_value // 1500
        elif 500 <= self.calories_intake_value:
            self.weight_value += self.calories_intake_value // 1500 
            
        self.next_weight_check_interval += 1
        threading.Timer(self.next_weight_check_interval - time.time(), self.cause_update_weight).start()
        
    def set_screen_timeout(self) -> threading.Timer:
        """set the timeout to turn off the screen and set the screen to power saving

        Returns:
            threading.Timer: returns the thread of the timer for it to be cancelled on button pressed
        """
        timer: threading.Timer = threading.Timer(self.next_screen_timeout_interval - time.time(), self.turn_off_screen)
        timer.start()
        return timer
        
    def turn_off_screen(self) -> None:
        """turn off the screen and stop the rendering of new frames to the screen
        
        Used as power saving mode, also preserves the lifetime of the display
        """
        if self.screen_on:
            global device
            device.hide()
            self.screen_on = False
        
    def turn_on_screen(self) -> None:
        """bring back the display from power saving mode and start to render new frames again
        
        Also set new time to turn off the display again
        """
        self.screen_sleep_timer.cancel()
        self.next_screen_timeout_interval = time.time() + self.screen_sleep_time
        timer: threading.Timer = threading.Timer(self.next_screen_timeout_interval - time.time(), self.turn_off_screen)
        timer.start()
        self.screen_sleep_timer = timer
        
        if not self.screen_on:
            self.screen_on = True
            global device
            device.show()
                
    def get_stats_summary(self) -> dict[str, int]:
        """get a current summary of all important stats of the tama

        Returns:
            dict[str, int]: dictionary of 'Name of the property' (human readable) : value as int
        """
        return {
            "Healthyness": self.healthyness_value,
            "Happyness": self.happyness_value,
            "Weight": self.weight_value,
            "Dicipline": self.dicipline_value
        }

    def write_status_to_csv(self) -> None:
        global main_screen
        with open("/home/pi/Downloads/logs/log.csv", "a") as log_file:
            log_file.write(
                str(time.time()) + ", " +
                str(self.birthday_time)                          + ", " +
                str(self.care_errors)                            + ", " +
                str(main_screen.poop_display_bar.poop_on_screen) + ", " +
                str(self.diet_health_counter)                    + ", " +
                str(self.calories_intake_value)                  + ", " +
                str(self.healthyness_value)                      + ", " +
                str(self.happyness_value)                        + ", " +
                str(self.weight_value)                           + ", " +
                str(self.dicipline_value)                        + ", " +
                str(self.sleeping)                               + ", " +
                str(self.light_on)                               + ", " +
                str(self.screen_on)                              + ", " +
                ""                                               + ", " +
                str(self.next_pooping_interval)                  + ", " +
                str(self.next_hunger_interval)                   + ", " +
                str(self.next_sickness_interval)                 + ", " +
                str(self.next_weight_check_interval)             + ", " +
                "\n"
            )
        self.next_log_to_csv_interval += 5
        timer: threading.Timer = threading.Timer(self.next_log_to_csv_interval - time.time(), self.write_status_to_csv)
        timer.start()



with open("/home/pi/Downloads/logs/log.csv", "w") as log_file:
    log_file.write(
        "Current Time" + ", " +
        "Birthday Time" + ", " +
        "Care errors" + ", " +
        "poop on screen" + ", " +
        "diet heath counter" + ", " +
        "calories intake value" + ", " +
        "health value" + ", " +
        "happyness value" + ", " +
        "weight value" + ", " +
        "dicipline value" + ", " +
        "sleeping" + ", " +
        "light on" + ", " +
        "screen on" + ", " +
        ""  + ", " +
        "next pooping interval" + ", " +
        "next hunger interval" + ", " +
        "next sickness interval" + ", " +
        "next weight check interval" + ", " +
        "\n"
    )

logic_class: Logic = Logic()

active_screen: BaseScreen = main_screen

UI = UserInput()

regulator: framerate_regulator = framerate_regulator(fps= 30)


while True:
    with regulator:
        if logic_class.screen_on:
            active_screen.render()



Euch trotzdem viel Spaß und einen schönen Urlaub ;-)
