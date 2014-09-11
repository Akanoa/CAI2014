#!/usr/bin/python
# -*- coding: utf-8 -*-

from Tkinter import Tk, Frame, IntVar, Checkbutton,ACTIVE

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
        # # Vues
        # self.menuBar         = MenuBar(parent=self)
        # self.screen          = Screen(parent=self)
        # self.frame = Frame(master=self)
        # # Controleurs
        # self.time_control = TimeBase(parent=self)
        # self.signal_controlX = Generator(parent=self, name="X", color="red")
        # self.signal_controlY = Generator(parent=self, name="Y", color="blue")
        # # Affichage Vues, Controleurs
        # self.menuBar.pack()
        # self.screen.pack()

        # self.signal_controlX.pack(side="left")
        # self.signal_controlY.pack(side="left")
        # self.time_control.pack()

        # Vues
        self.menuBar          = MenuBar(parent=self)
        self.screenT          = Screen(parent=self)
        self.screenXY         = Screen(parent=self)
        # Controleurs
        self.signal_controlX = Generator(parent=self, name="X", color="red")
        self.signal_controlY = Generator(parent=self, name="Y", color="blue")
        self.signal_controlXY = Generator(parent=self, name="XY", color="blue")
        self.time_control = TimeBase(parent=self)
        self.varX  = IntVar()
        self.varY  = IntVar()
        self.varXY = IntVar()
        self.showX = Checkbutton(parent, text="X", variable=self.varX, command=lambda: self.update_show("X"))
        self.showY = Checkbutton(parent, text="Y", variable=self.varY, command=lambda: self.update_show("Y"))
        self.showXY = Checkbutton(parent, text="XY", variable=self.varXY, command=lambda: self.update_show("XY"))
        self.varX.set(1)
        self.varY.set(1)
        self.varXY.set(1)

        # Affichage Vues, Controleurs
        self.menuBar.grid(column=0, row=0)
        self.screenT.grid(column=0,row=1)
        self.screenXY.grid(column=1,row=1)
        self.signal_controlX.grid(column=0, row=2)
        self.signal_controlY.grid(column=0, row=3)
        self.time_control.grid(column=0, row=4)

        self.showX.grid(column=1, row=2)
        self.showY.grid(column=1, row=3)
        self.showXY.grid(column=1, row=4)

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

    def set_signal(self, name="X", signal=None , color =None):
        """ demande d'affichage de signal

        name : nom de la courbe (X,Y, X-Y)
        signal : liste des couples (temps,elongation) ou (elongation X, elongation Y)
        """
        print("Base de Temps :", self.get_time())
        msdiv = self.get_time()
        if signal :
            signal = signal[0:(len(signal)/msdiv) + 1]
            signal = map(lambda (x, y): (x*msdiv, y), signal)

            #Search if the signal need to be shown
            self.screenT.change_signal(name, signal,color)

            listCurveScreenT = self.screenT.listCurve
            listCurveX = listCurveScreenT[0]
            listCurveY = listCurveScreenT[1]

            curveXY= []
            for i in range(len(listCurveX)-1):
                curveXY.append((listCurveX[1][i][1]+0.05,listCurveY[1][i][1]))
            self.screenXY.change_signal("XY", curveXY, "green")
        return signal

    def update_show(self, name= None):
        """
        Function de test check Box
        """
        print "EtatX", self.varX.get(), " EtatY" , self.varY.get(), " EtatY" , self.varXY.get()
        print name

        if name == "X":
            self.screenT.show_curve(name, self.varX.get())
        elif name =="Y":
            self.screenT.show_curve(name, self.varY.get())
        elif name =="XY":
            self.screenXY.show_curve(name, self.varXY.get())
        #self.signal_controlX.update_signal(None)
        #self.signal_controlY.update_signal(None)

if __name__ == "__main__":
    root = Tk()
    oscillo = Oscilloscope(root)
    root.mainloop()
