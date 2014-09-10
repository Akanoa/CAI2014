# -*- coding: utf-8 -*-
from Tkinter import Tk, Canvas, ALL, LAST

class Screen(Canvas):
    """ visualisation grille + signal

    signal_X, ... : identifiants des signaux  (pour mise a jour de l'affichage)
    color_X, ... : couleur d'affichage des siganux
    """
    def __init__(self, parent=None, width=800, height=800, background="white"):
        """ initialisation

        parent : un Oscilloscope
        width,height : dimension de l'ecran
        background : fond d'ecran
        """
        Canvas.__init__(self)
        self.parent = parent

        self.width = width
        self.height = height
        self.signal_X = None
        self.color_X = "red"

        self.configure(bg=background, bd=2, relief="sunken")
        self.bind("<Configure>", self.resize)

    def resize(self, event):
        """retaillage  en cas de reconfiguration de fenetre"""
        print("Screen.resize()")
        if event:
            self.width = event.width
            self.height = event.height
            self.draw_grid()

    def draw_grid(self, nX=10, nY=10):
        """representation des carreaux de la grille

        nX : pas horizontal
        nY : pas vertical
        """
        self.delete(ALL)

        #draw axis
        #hor
        self.create_line(10, self.height/2, self.width-5, self.height/2, arrow=LAST)
        #vert
        self.create_line(10, self.height-5,10,5,arrow=LAST)


        sizeOneStepW = self.width/nX
        sizeOneStepH = self.height/nY
        #draw grid hor
        for t in range(1,nX+2):
            actualWidth= t*sizeOneStepW
            self.create_line(10+actualWidth,10,10+actualWidth,self.height-5)

        #draw grid hor
        for t in range(1,nY/2+2):
            actualHeight= t*sizeOneStepH
            self.create_line(10, self.height/2 + actualHeight, self.width-5, self.height/2 + actualHeight)
            self.create_line(10, self.height/2 - actualHeight, self.width-5, self.height/2 - actualHeight)

    def plot_signal(self, name, signal=None):
        """affichage d'un signal

        name : nom du signal (X,Y,X-Y)
        signal : liste des couples (temps,elongation) ou (elongation X, elongation Y)
        """
        if signal and len(signal) > 1:
            if name == "X":
                if self.signal_X > -1:
                    self.delete(self.signal_X)
                plot = [(x*self.width, y*self.height + self.height/2) for (x, y) in signal]
                self.signal_X = self.create_line(plot, fill=self.color_X, smooth=1, width=3)

if __name__ == "__main__":
    root = Tk()
    screen = Screen(root)
    screen.plot_signal("X", [(0, 0), (100, 100)])
    screen.pack()
    root.mainloop()
