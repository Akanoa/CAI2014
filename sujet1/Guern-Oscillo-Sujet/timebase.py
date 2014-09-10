# -*- coding: utf-8 -*-
from Tkinter import Tk, Frame, Scale


class TimeBase(Frame):
    def __init__(self, parent=None):
        """
        Description :
          Creation d'un controleur pour la base de temps
        Proprietes :
          - un parent (classe Oscilloscope)
          - controleur de la base de temps (classe Scale)
        Methodes :
          - update_time_base(self, event) : callback de demande de mise a jour sur l'oscilloscope
          - get_time(self) : observateur sur la valeur de la base de temps
        """
        Frame.__init__(self)
        self.configure(bd=1, relief="sunken")
        self.parent = parent
        self.scale_T = Scale(self, length=300, orient="horizontal",
                label="Temps", showvalue=1, from_=1, to=10,
                tickinterval=1, command=self.update_time_base)
        self.scale_T.pack(expand="yes", fill="both")

    def update_time_base(self, event):
        """
        Mise a jour de la base de temps
        """
        print("TimeBase.update_time_base()")
        print("Base de temps : ", self.scale_T.get())
        if not isinstance(self.parent, Tk):
            self.parent.update_time(self.scale_T.get())

    def get_time(self):
        """
        Retour :  valeur courante de la base de temps
        """
        return self.scale_T.get()

if __name__ == "__main__":
    root = Tk()
    TimeBase(root).pack()
    root.mainloop()
