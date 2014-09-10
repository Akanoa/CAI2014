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
        self.signal_Y = None
        self.color_Y = "blue"
        self.signal_XY = None
        self.color_XY = "green"

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

        #constants
        PADDING_LEFT = PADDING_RIGHT = PADDING_TOP = PADDING_BOTTOM = 10
        LANDMARK_SIZE = 5

        #dimensions
        screenW  = (self.width-PADDING_RIGHT-PADDING_LEFT)
        screenH  = (self.height-PADDING_TOP-PADDING_BOTTOM)
        sizeStepW = screenW/nX
        sizeStepH = screenH/nY

        #draw frame
        self.create_rectangle(PADDING_LEFT, PADDING_BOTTOM, self.width-PADDING_RIGHT, self.height-PADDING_BOTTOM)

        #draw axis
        self.create_line(PADDING_LEFT, self.height/2, self.width-PADDING_RIGHT, self.height/2, width=1.5) 
        self.create_line(self.width/2, PADDING_TOP,self.width/2, self.height-PADDING_BOTTOM, width=1.5)

        #draw landmarks
        #hor
        for t in range(nX/2):
            width = t*sizeStepW
            self.create_line(self.width/2+width, self.height/2+LANDMARK_SIZE ,self.width/2+width, self.height/2-LANDMARK_SIZE)
            self.create_line(self.width/2-width, self.height/2+LANDMARK_SIZE ,self.width/2-width, self.height/2-LANDMARK_SIZE)

        #ver
        for t in range(nY/2):
            height = t*sizeStepH
            self.create_line(self.width/2-LANDMARK_SIZE, self.height/2+height,self.width/2+LANDMARK_SIZE, self.height/2+height)
            self.create_line(self.width/2-LANDMARK_SIZE, self.height/2-height,self.width/2+LANDMARK_SIZE, self.height/2-height) 


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
            if name == "Y":
                if self.signal_Y > -1:
                    self.delete(self.signal_Y)
                plot = [(x*self.width, y*self.height + self.height/2) for (x, y) in signal]
                self.signal_Y = self.create_line(plot, fill=self.color_Y, smooth=1, width=3)
            if name == "XY":
                if self.signal_XY > -1:
                    self.delete(self.signal_XY)
                plot = [(x*self.width, y*self.height + self.height/2) for (x, y) in signal]
                self.signal_XY = self.create_line(plot, fill=self.color_XY, smooth=1, width=3)

if __name__ == "__main__":
    root = Tk()
    screen = Screen(root)
    screen.plot_signal("X", [(0, 0), (100, 100)])
    screen.pack()
    root.mainloop()
