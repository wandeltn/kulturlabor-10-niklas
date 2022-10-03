import time
import threading
import random
import math
import random

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


logic: Logic = Logic()