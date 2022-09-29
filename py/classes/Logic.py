import time
import threading


class Logic(object):
    def __init__(self) -> None:
        # set up pooping timer interval
        self.next_pooping_interval = time.time()
        self.cause_pooping()

        # set up hunger timer interval
        self.next_hunger_interval = time.time()
        self.cause_hunger()
    
    def start_timer(self, interval: float, function: type) -> threading.Timer:
        if __debug__:
            print("DEBUG: started timer for: " + str(function.__name__))

        return threading.Timer(interval - time.time(), function).start()

    def cause_pooping(self) -> None:
        if __debug__:
            print("DEBUG: Pooped")

        self.next_pooping_interval += 2
        self.start_timer(self.next_pooping_interval, self.cause_pooping)

    def cause_hunger(self) -> None:
        if __debug__:
            print("DEBUG: hunger value increased by 1")
        
        # Hunger value change still to be implemented

        self.next_hunger_interval += 5
        self.start_timer(self.next_hunger_interval, self.cause_hunger)
