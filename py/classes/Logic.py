import time
import threading


class Logic(object):
    def __init__(self) -> None:
        self.times_pooped = 0
        self.next_pooping_interval = time.time()
        self.cause_pooping()
    
    def startTimer(self, interval: float, function: type) -> threading.Timer:
        print("DEBUG: started timer for: " + str(function.__name__))
        return threading.Timer(interval - time.time(), function).start()

    def cause_pooping(self) -> None:
        print("DEBUG: Pooped")

        self.next_pooping_interval += 2
        self.times_pooped += 1
        self.startTimer(self.next_pooping_interval, self.cause_pooping)


logic = Logic()
