# -*- coding: utf-8 -*-
from Tkinter import Tk, Frame, Menubutton,Menu,Frame,Button, RIGHT,LEFT
import tkFileDialog
import tkMessageBox
import Tkconstants
 
class MenuBar(Frame):
    """
    Barre de menu de l'oscilloscope.
    Contient toutes les actions possibles, telles qu'enregistrer etc
    """
    def __init__(self,parent=None, width = 800, height = 50):
        """
        Initialise / crée le menu
        """
        Frame.__init__(self,borderwidth=2)

        #Vars
        self.parent = parent
        self.fileOpened = None

        mbuttonFile = Menubutton(self,text='Fichier')
        #mbuttonFile.grid(row=0, column=0)
        mbuttonFile.pack(side=LEFT)
        menuFile=Menu(mbuttonFile)
        menuFile.add_command(label='Nouveau',command=self.new)
        menuFile.add_separator()
        menuFile.add_command(label='Sauvegarder',command=self.save)
        menuFile.add_command(label='Sauvegarder sous...',command=self.saveAs)
        menuFile.add_command(label='Charger...',command=self.load)
        menuFile.add_separator()
        menuFile.add_command(label='Quitter',command=self.exit)
        mbuttonFile.configure(menu=menuFile)

        mbuttonHelp = Menubutton(self,text='Aide')
        #mbuttonHelp.grid(row=0, column=1)
        mbuttonHelp.pack(side=RIGHT)
        menuHelp = Menu(mbuttonHelp)
        menuHelp.add_command(label='Aide',command=self.infos)
        menuHelp.add_command(label='A propos',command=self.aPropos)
        mbuttonHelp.configure(menu=menuHelp)

        # define options for opening or saving a file
        self.file_opt = options = {}
        options['defaultextension'] = '.txt'
        options['filetypes'] = [('text files', '.txt'),('all files', '.*')]
        options['initialdir'] = 'C:\\'
        options['initialfile'] = 'myfile.txt'
        options['parent'] = parent
        options['title'] = 'Choissisez le fichier'
 
 
    def new(self):
        """
        Remise à zéro des données
        """
        #TODO
        result = tkMessageBox.askquestion("Nouveau signal?", "Etes vous sur de vouloir generer un nouveau signal?", icon='warning')
        if result == 'yes':
            print "Deleted"
        else:
            print "I'm Not Deleted Yet"
 
 
    def save(self):
        """
        Sauvegarde des donnees dans un fichier par defaut ( ou celui selectionné si applicable)
        """

        if self.fileOpened == None:
            fd = open("save.txt", "w")
        else:
            fd = open(self.fileOpened, "w")

        with fd:
            fd.write("#########################################################################\n")
            fd.write("# Chaque ligne correspond aux paramètres d'une courbe\n")
            fd.write("# En suivant la convention suivante:\n")
            fd.write("# amplitude;frequence;phase;base_de_temps\n")
            fd.write("# Puis la base de temps\n")
            fd.write("# base_de_temps\n")
            fd.write("##########################################################################\n")
            #sauvegarde de la courbe X
            print self.parent.signal_controlX.get_parameter()
            fd.write(";".join(self.parent.signal_controlX.get_parameter())+"\n")
            fd.write(";".join(self.parent.signal_controlY.get_parameter())+"\n")
            fd.write(str(self.parent.get_time())+"\n")

    def saveAs(self):
        """
        Sauvegarde des donnees dans un fichier selectionne
        """

        self.file_opt['title'] = 'Choissisez le fichier ou vous voulez sauvegarder les donnees'
        self.fileOpened = self.askForFileToWrite()
        self.save()

    def load(self):
        """
        Charge des donnees depuis un fichier
        """
        self.file_opt['title'] = 'Choissisez le fichier depuis lequel vous souhaitez charger les donnees'
        fd = self.askForFileToRead()

        #TODO
        datas = fd.readlines()[7:10]
        x_parameters = [int(e) for e in datas[0].split(";")]
        y_parameters = [int(e) for e in datas[1].split(";")]
        self.parent.signal_controlX.set_parameter(*x_parameters)
        self.parent.signal_controlX.set_parameter(*y_parameters)
        self.parent.time_control.scale.set(int(datas[2]))

    def exit(self):
        """
        Quitte l'application
        """
        result = tkMessageBox.askquestion("Quitter l'application?", "Etes vous sur de vouloir quitter l'application?", icon='warning')
        if result == 'yes':
            exit(0)

    def infos(self):
        """
        Ouvre la boite de dialogue d'informations
        """
        tkMessageBox.showinfo("Aide", "Logiciel permettant de simuler le fonctionnement d'un oscilloscope ( simple )")
    def aPropos(self):
        """
        Ouvre la boite de dialogue d'a Propos
        """
        tkMessageBox.showinfo("A propos", "Crée par\n Yannick GUERN - y0guern@enib.fr \n&\nSimon TENEAU - s0teneau@enib.fr \nLabo 1 - CAI - 2014\nENIB")

    def askForFileToWrite(self):
        """
        Open a dialog that ask to user where he wants to save the data
        Returns an opened file in write mode.
        """
        return tkFileDialog.asksaveasfilename(**self.file_opt)

    def askForFileToRead(self):
        """
        Open a dialog that ask to user where he wants to load the data
        Returns an opened file in read mode.
        """
        return tkFileDialog.askopenfile(mode='r', **self.file_opt)
 
if __name__ == "__main__":
    root = Tk()
    menuBar = MenuBar(root)
    menuBar.pack()
    root.mainloop()
