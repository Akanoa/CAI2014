#include <QApplication>
#include <QtGui>
class MyMainWindow : public QMainWindow
{
   public:
      MyMainWindow()
      {
        QMenu *fileMenu = new QMenu(tr("&Fichier"), this);
        QMenu *fileSubMenu = fileMenu->addMenu(QString::fromUtf8("&New"));
        fileSubMenu->addAction("Painter");
        fileSubMenu->addAction("Graphic Items");
        fileMenu->addSeparator();
        fileMenu->addAction(tr("&Quitter"), qApp,
                           SLOT(quit()));
//                            SLOT(quit()),QKeySequence::Quit);
        menuBar()->addMenu(fileMenu);
        QMenu *editMenu = new QMenu(QString::fromUtf8("&Édition"), this);
        QAction *actionEdit = new QAction(QString::fromUtf8("Gras"), this);
        actionEdit->setCheckable(true);
        actionEdit->setChecked(true);
        editMenu->addAction(actionEdit);
        menuBar()->addMenu(editMenu);
        QMenu *helpMenu = new QMenu(tr("&Aide"), this);
        menuBar()->addMenu(helpMenu);
        QAction *actionHelp = new QAction(QString::fromUtf8("À propos de Qt"), this);
        helpMenu->addAction(actionHelp);
        actionHelp->setShortcut(QKeySequence(Qt::Key_F1)); //ou :
      //actionHelp->setShortcut(QKeySequence(QKeySequence::HelpContents));
        connect(actionHelp, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

        _popup = new QMenu( tr("&Édition"), this);
        _popup->addAction(actionEdit);
       }
     // mousePressEvent : popup + check action
     void mousePressEvent(QMouseEvent *e)
     {
         if(e->button() == Qt::RightButton)
           {
                 _popup->exec(QCursor::pos());
           }
     
     }
   private :
      QMenu* _popup;
};

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MyMainWindow myMainWindow;
  myMainWindow.show();
  return app.exec();
}

