#!/usr/bin/python
# -*- coding: utf-8 -*-

from Tkinter import Tk, Frame

from screen import Screen
from timebase import TimeBase
from generator import Generator
from menuBar import MenuBar

class Oscilloscope(Frame):
    """ Oscilloscope 

    time : valeur de la base de temps
    signaux : liste de couples, (temps,elongation) ou (elongation X, elongation Y)  de signaux
    screen : ecran de visualisation de signaux
    time_control : controle de la base de temps
    signal_control : controle d'un signal
    """
    def __init__(self, parent=None, width=800, height=800):
        """ initialisation

        parent : une application
        width,height : dimension de l'oscilloscpe
        """
        Frame.__init__(self)
        self.master.title("Oscilloscope")
        # Modele
        self.time = 0
        self.signal = None
        # Vues
        self.menuBar         = MenuBar(parent=self)
        self.screen          = Screen(parent=self)
        self.frame = Frame(master=self)
        # Controleurs
        self.time_control = TimeBase(parent=self)
        self.signal_controlX = Generator(parent=self, name="X", color="red")
        self.signal_controlY = Generator(parent=self, name="Y", color="blue")
        # Affichage Vues, Controleurs
        self.menuBar.pack()
        self.screen.pack()

        self.signal_controlX.pack(side="left")
        self.signal_controlY.pack(side="left")
        self.time_control.pack()

        self.configure(width=width, height=height)

    def get_time(self):
        """valeur courante de la base de temps."""
        return self.time_control.get_time()

    def update_time(self, time):
        """demande de calcul de signal si modification de la base de temps"""
        if self.time != time:
            self.time = time
            self.signal_controlX.update_signal(None)
            self.signal_controlY.update_signal(None)

    def set_signal(self, name="X", signal=None):
        """ demande d'affichage de signal

        name : nom de la courbe (X,Y, X-Y)
        signal : liste des couples (temps,elongation) ou (elongation X, elongation Y)
        """
        print("Base de Temps :", self.get_time())
        msdiv = self.get_time()
        if signal :
            signal = signal[0:(len(signal)/msdiv) + 1]
            signal = map(lambda (x, y): (x*msdiv, y), signal)
            self.screen.plot_signal(name, signal)
        return signal


if __name__ == "__main__":
    root = Tk()
    oscillo = Oscilloscope(root)
    root.mainloop()
