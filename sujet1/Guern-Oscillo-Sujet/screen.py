# -*- coding: utf-8 -*-
from Tkinter import Tk, Canvas, LAST, ALL


class Screen(Canvas):
    def __init__(self, parent=None, width=800, height=800, background="white"):
        """
        Description :
          visualisation grille + signal
        Proprietes :
          - un parent (classe Oscilloscope)
          - les dimensions (largeur,hauteur)
          - les identifiants de courbes (pour mettre a jour l'affichage)
        Methodes :
          - resize(self, event) : retaillage en cas de reconfiguration de la fenetre
          - draw_grid(self,nX, nY) :  affichage des carreaux de la grille
          - draw_curve(self,name,curve) : affichage d'une courbe
        """
        Canvas.__init__(self)
        self.configure(bg=background, bd=2, relief="sunken")
        self.parent = parent
        self.width = width
        self.height = height
        self.curve_X_id = None
        self.color = "red"
        self.bind("<Configure>", self.resize)

    def resize(self, event):
        """
        evenement de retaillage de fenetre
        """
        print("Screen.resize()")
        if event:
            self.width = event.width
            self.height = event.height
            self.draw_grid()

    def draw_grid(self, nX=10, nY=10):
        """
       calcul des carreaux (nX*nY) de la grille
       """
        print("Screen.draw_grid('%d','%d')" % (nX, nY))

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



        print("Screen.draw_grid('%d','%d')" % (nX, nY))

    def draw_curve(self, name, curve=None):
        """
        affichage de la courbe
        """
        print("Screen.draw_curve() :", curve)
        if curve and len(curve) > 1:
            if name == "X":
                if self.curve_X_id > -1:
                    self.delete(self.curve_X_id)

                widthOscillo = self.width
                heightOscillo = self.height

                step = (widthOscillo-10)/1000.


                curve2 = [(10+e[0]*step, heightOscillo/2-e[1]*heightOscillo/10) for e in curve]

                self.curve_X_id = self.create_line(curve2, fill=self.color, smooth=1, width=3)

if __name__ == "__main__":
    root = Tk()
    screen = Screen(root)
    screen.draw_curve("X", [(0, 0), (100, 100)])
    screen.pack()
    root.mainloop()
