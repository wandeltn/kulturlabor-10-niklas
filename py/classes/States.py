import math
import random


class States(object):
    def __init__(self) -> None:
        self._poop_on_screen: int = 0
        self._sickness_value: int = 0
        self._care_errors: int = 0
    
    @property
    def get_poop_on_screen(self) -> int:
        return self._poop_on_screen

    @get_poop_on_screen.setter
    def add_poop_to_screen(self, amount: int) -> int:
        self.add_poop_to_screen += amount

        return self._poop_on_screen

    @property
    def get_sickness_value(self) -> int:
        return self._sickness_value

    @get_sickness_value.setter
    def add_sickness(self, amount: int) -> int:
        self._sickness_value += amount

        return self._sickness_value



