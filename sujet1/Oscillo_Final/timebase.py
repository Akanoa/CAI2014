# -*- coding: utf-8 -*-
from Tkinter import Tk, Frame, Scale


class TimeBase(Frame):
    """controleur pour la base de temps

    scale : controle de la valeur de la base de temps
    """
    def __init__(self, parent=None):
        """ initialisation

        parent : oscilloscope
        """
        Frame.__init__(self)
        self.configure(bd=1, relief="sunken")
        self.parent = parent
        self.scale = Scale(self, length=300, orient="horizontal",
                label="Temps", showvalue=1, from_=1, to=10,
                tickinterval=1, command=self.update_time_base)
        self.scale.pack(expand="yes", fill="both")

    def get_time(self):
        """valeur courante de la base de temps"""
        return self.scale.get()

    def update_time_base(self, event):
        """mise a jour de la base de temps"""
        #print("TimeBase.update_time_base()")
        #print("Base de temps : ", self.scale.get())
        if not isinstance(self.parent, Tk):
            self.parent.update_time(self.scale.get())


if __name__ == "__main__":
    root = Tk()
    TimeBase(root).pack()
    root.mainloop()
