# -*- coding: utf-8 -*-
from Tkinter import Tk, Frame, Scale
from math import cos, sin, pi


class Generator(Frame):
    """calcul d'une vibration harmonique du type : e=a*sin(2*pi*f*t+p)

    scale_A : controleur d'amplitude
    """
    def __init__(self, parent, name="X",color="red"):
        """ initialisation

        parent : un oscilloscope
        name : nom du signal
        """
        Frame.__init__(self)
        self.configure(bd=1, relief="sunken", background = color)
        self.parent = parent
        self.name = name
        self.color = color
        self.scale_A = Scale(self, length=300, orient="horizontal",
                label=name + " Amplitude", showvalue=1, from_=0, to=10,
                tickinterval=1, command=self.update_signal)

        self.scale_P = Scale(self, length=300, orient="horizontal",
                label=name + " Phase", showvalue=1, from_=0, to=90,
                tickinterval=20, command=self.update_signal)

        self.scale_F = Scale(self, length=300, orient="horizontal",
                label=name + " Fréquence", showvalue=1, from_=0, to=100,
                tickinterval=10, command=self.update_signal)

        self.scale_A.pack(expand="yes", fill="both")
        self.scale_P.pack(expand="yes", fill="both")
        self.scale_F.pack(expand="yes", fill="both")

    def update_signal(self, event):
        """mise a jour de courbe si modifications (amplitude, frequence, phase)."""
        #print("Vibration.update_signal()")
        #print("Amplitude :", self.scale_A.get())
        scaling=0.05
        amp = scaling*self.scale_A.get()
        fre = scaling*self.scale_F.get()
        pha = scaling*self.scale_P.get()
        signal = self.generate_signal(a=amp, f=fre, p=pha)
        if not isinstance(self.parent, Tk):
            self.parent.set_signal(self.name, signal, self.color)
        return signal

    def generate_signal(self, a=1.0, f=2.0, p=0):
        """Calcul de l'elongation, amplitude, frequence et phase sur une periode."""
        signal = []
        samples = 100
        for t in range(0, samples):
            samples = float(samples)
            e = a * sin((2*pi*f*(t/samples)) - p)
            signal.append((t/samples,e))
        return signal

    def get_parameter(self):
        """
        Récupère les valeurs des paramètres de la courbe et les renvoie sous forme d'un tuple
        """
        return [str(self.scale_A.get()), str(self.scale_F.get()), str(self.scale_P.get())]

    def set_parameter(self, amp=1.0, freq=2.0, phase=0):
        """
        Modifie les valeurs des paramètres de la courbe
        """
        self.scale_A.set(amp)
        self.scale_F.set(freq)
        self.scale_P.set(phase)

if __name__ == "__main__":
    root = Tk()
    Generator(root).pack()
    root.mainloop()
