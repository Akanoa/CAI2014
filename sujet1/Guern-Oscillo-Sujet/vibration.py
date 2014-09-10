# -*- coding: utf-8 -*-
from Tkinter import Tk, Frame, Scale
from math import cos, sin, pi


class Vibration(Frame):
    def __init__(self, parent, name="X", color="red"):
        """
        Description :
          Calcul d'une vibration harmonique du type : e=a*sin(2*pi*f*t+p)
        Proprietes :
          -  un parent (classe Oscilloscope)
          -  controleurs d'amplitude, frequence, phase (classe Scale)
        Methodes :
          - update_vibration(self, event) : callback si modification de controleurs
          - compute(self,a,f,p) : calcul de vibration harmonique
        """
        Frame.__init__(self)
        self.configure(bd=1, relief="sunken")
        self.parent = parent
        self.name = name
        self.scale_A = Scale(self, length=300, orient="horizontal",
                label=name + " Amplitude", showvalue=1, from_=0, to=10,
                tickinterval=1, command=self.update_vibration)

        self.scale_P = Scale(self, length=300, orient="horizontal",
                label=name + " Phase", showvalue=1, from_=0, to=90,
                tickinterval=20, command=self.update_vibration)

        self.scale_F = Scale(self, length=300, orient="horizontal",
                label=name + " Fréquence", showvalue=1, from_=0, to=100,
                tickinterval=10, command=self.update_vibration)

        self.scale_A.pack(expand="yes", fill="both")
        self.scale_P.pack(expand="yes", fill="both")
        self.scale_F.pack(expand="yes", fill="both")

    def update_vibration(self, event):
        """
        mise  a jour de courbe si modifications (amplitude, frequence, phase)
        """
        print("Vibration.update_vibration()")
        print("Amplitude :", self.scale_A.get())
        curve = self.compute(self.scale_A.get(), self.scale_F.get(),self.scale_P.get(), self.parent.get_time())
        if not isinstance(self.parent, Tk):
            self.parent.draw_curve(self.name, curve)

    def compute(self, a=0, f=0, p=0, timeBase=1):
        """
        Calcul de l'elongation en fonction de base de temps, amplitude, frequence, phase
        """
        curve = []
        print("Vibration.compute()")
        if not isinstance(self.parent, Tk):
            print("Base de Temps :", timeBase)
            #t = self.parent.get_time()
            #curve.append((self.scale_A.get() + 10*t, self.scale_A.get() + 10*t))
            #curve.append((self.scale_A.get() + 20*t, self.scale_A.get() + 20*t))
            # calcul des points de la courbe en fct de la base de temps (cf poly)

            for t in range(0, 1001, 5):
                e = a*sin(2*pi*f*t/1000*timeBase-p)
                x = t
                y = e
                curve.append((x,y))
        return curve

if __name__ == "__main__":
    root = Tk()
    Vibration(root).pack()
    root.mainloop()
