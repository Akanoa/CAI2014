from Tkinter import Frame, Menubutton, Menu

class MenuBar(Frame):
    def __init__(self, parent=None):
         Frame.__init__(self, borderwidth=2)
         mButtonFile = Menubutton(self, text="Fichier")
         mButtonFile.pack()
         menuFile = Menu(mButtonFile)

         menuFile.add_command(label="Quitter", command=parent.quit)
         menuFile.add_command(label="Sauvegarder", command=parent.save)
         mButtonFile.configure(menu=menuFile)

