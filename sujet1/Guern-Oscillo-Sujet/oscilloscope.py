#!/usr/bin/python
# -*- coding: utf-8 -*-
from Tkinter import Tk, Frame
from screen import Screen
from timebase import TimeBase
from vibration import Vibration
from menuBar import MenuBar
import cPickle

class Oscilloscope(Frame):
    def __init__(self, parent=None, width=800, height=800):
        """
        Proprietes :
          -  un ecran (classe Screen)
          -  vibrations harmoniques (classe Vibration)
          -  base de temps (classe TimeBase)
        Methodes :
          -  get_time(self) : demander le temps de la base de temps
          -  update_time(self, time) : calcul de vibration si mise  a jour base de temps
          -  draw_curve(self, name, curve) : demander affichage d'une courbe
        """
        Frame.__init__(self)
        self.time = 0
        self.master.title("Oscilloscope")
        self.screen = Screen(parent=self)
        self.time_base = TimeBase(parent=self)
        self.vib_X = Vibration(parent=self, color="blue")

        self.curveX = None

        self.menuBar = MenuBar(self)

        self.menuBar.pack()
        self.screen.pack()
        self.vib_X.pack()
        self.time_base.pack()

        self.configure(width=width, height=height)

    def get_time(self):
        """
        Retour : valeur courante de la base de temps
        """
        return self.time_base.get_time()

    def update_time(self, time):
        """
        Si modification base de temps : calcul vibration
        """
        if self.time != time:
            self.time = time
            self.curveX = self.vib_X.compute(a=self.vib_X.scale_A.get(), f=self.vib_X.scale_F.get(), p=self.vib_X.scale_P.get(), timeBase=self.get_time())
            self.draw_curve("X", self.curveX)

    def draw_curve(self, name="X", curve=None):
        """
        demande d'affichage de courbe
        """
        self.screen.draw_curve(name, curve)

    #########
    #event

    def exit(self):
        """
        Quitte le programme en demandant si l'on veut sauvegarder son programme 
        """
        
        self.quit()

    def save(self):
        """
        Sauvegarde la courbe dans un fichier
        """
        data = cPickle.dump(self.curveX)
        print "sauvegarde du fichier"
        print data

if __name__ == "__main__":
    root = Tk()
    oscillo = Oscilloscope(root)
    root.mainloop()
