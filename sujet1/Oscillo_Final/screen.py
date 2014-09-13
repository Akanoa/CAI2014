# -*- coding: utf-8 -*-
from Tkinter import Tk, Canvas, ALL, LAST
from threading import Thread
import time

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

        self.listCurve = []

        self.configure(bg=background, bd=2, relief="sunken")
        self.bind("<Configure>", self.resize)
        self.t = Thread(None, self.plot_signal) 
        self.launch = True
        self.t.start()

    def resize(self, event):
        """retaillage  en cas de reconfiguration de fenetre"""
        # print("Screen.resize()")
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


    def plot_signal(self):
        """affichage d'un signal au fur et à mesure du temps ( fonction threadée)

        name : nom du signal (X,Y,X-Y)
        signal : liste des couples (temps,elongation) ou (elongation X, elongation Y)
        """

        TIME_TO_DRAW = 10.0  #NUMBER OF SECONDS TO DRAW THE GRAPH
        currentIndex = 0
        deleteOK = False
        tts = 1.0
        while self.launch:
            if len(self.listCurve) > 1:
                for i in range(len (self.listCurve) -1):

                    #if self.listCurve[i][0] != "XY":
                    # print "Curve ",i , " " , self.listCurve[i][0], " currentIndex", currentIndex , " maxIndex ", len(self.listCurve[i][1])
                    #if there is already a portion of the 
                    # print "longueur liste parties " , len(self.listCurve[i][4]), " longueur nombre element courbe ", len(self.listCurve[i][1]) ," ListCurveDraw ", self.listCurve[i][4]
                    if len(self.listCurve[i][4]) > 0 and deleteOK:
                        #If whe are at the end of the array, delete the first index
                        if currentIndex == (len(self.listCurve[i][1]) -1):
                            self.delete(self.listCurve[i][4][0])
                            # print "We are at the end of the array, delete first element"
                        else:
                            if currentIndex+1 !=  len(self.listCurve[i][4]):
                                # print "deleting element " ,currentIndex+1
                                self.delete(self.listCurve[i][4][currentIndex+1])
                            

                    #Create line if checkbox is selected
                    if self.listCurve[i][2] == 1 :
                        #create line only if we are not at the end of the array
                        if currentIndex != len(self.listCurve[i][1]) -1:
                            # print "Will draw curve" , currentIndex
                            plot = [(x*self.width, y*self.height + self.height/2) for (x, y) in [self.listCurve[i][1][currentIndex],self.listCurve[i][1][currentIndex+1]]]
                            # print "using array " , plot

                            if deleteOK == False :
                                # print "append section"
                                self.listCurve[i][4].append(self.create_line(plot, fill=self.listCurve[i][3], smooth=1, width=3))
                            if deleteOK == True :
                                # print "change Section"
                                self.listCurve[i][4][currentIndex] = self.create_line(plot, fill=self.listCurve[i][3], smooth=1, width=3)

                            if (self.listCurve[i][5]):
                                self.delete(self.listCurve[i][5])

                            r = 5
                            x = plot[1][0]
                            y = plot[1][1]
                            self.listCurve[i][5] = self.create_oval(x-r, y-r, x+r, y+r, fill=self.listCurve[i][3])


                #THEN increase index
                if currentIndex == (len(self.listCurve[i][1]) -1):
                    currentIndex = 0
                    deleteOK = True
                else :
                    currentIndex = currentIndex +1
            
                tts = 10.0/(len(self.listCurve[i][1]))
            # print "Time to sleep :" ,tts
            time.sleep(tts)
            
        #print self.listCurve

    def show_curve(self, name= None, show = None):
        """
            Permet d'afficher/Cacher une courbe sélectionnée
        """
        if name != None and show != None:
            for i in range(len (self.listCurve) -1):
                if self.listCurve[i][0] == name:
                    self.listCurve[i][2] = show
                    #self.plot_signal()

    def change_signal (self, name=None, signal = None, color = None):
        """
            permet d'ajouter une courbe à la liste des courbes de l'écran, ou Met à jour la courbe si celle-ci n'existe pas
            
            Structure utilisée:
            On ajoute à listCurve ( variable de classe ) une courbe représentée par un tableau :
            [nom,signal,show,couleur]   ---> intègre donc respectivement le nom du signal, les coordonnées de chaque sample, le fait que la courbe est affichée ou non, et enfin la couleur de la courbe
        """
        search = False
        if (signal and name  and color):
            for i in range(len (self.listCurve) -1):
                if self.listCurve[i][0] == name:
                   self.listCurve[i][1] = signal
                   self.listCurve[i][3] = color
                   search = True

            if search == False :    #If not found, then we need to append to the list ( new curve )
                self.listCurve.append([name,signal,1,color,[],0])

        #self.plot_signal()


    def stop_draw(self):
        """
        permet d'arreter le dessin en plaçant la variable launch à false et en attendant la fin de thread
        """
        self.launch = False

if __name__ == "__main__":
    root = Tk()
    screen = Screen(root)
    screen.plot_signal("X", [(0, 0), (100, 100)])
    screen.pack()
    root.mainloop()
