#include <QApplication>
#include <QtGui>

class MainWindow : public QMainWindow
{
Q_OBJECT
  public:
    MainWindow();
  protected :
  private :
   void _createMenus(void);
   void _createToolbars(void);
   void _createActions(void);
   void _connectActions(void);
   void _connectSignals(void);

   QMenu *_fileMenu;
   QMenu *_alignMenu;
   QMenu *_popupMenu;
   QToolBar *_toolBar;
   QMenu *_editMenu;
   QMenu *_helpMenu;
 
   QAction *_newAction;
   QAction *_exitAction;

   QAction *_aboutAction;
   QAction *_aboutQtAction;

   QActionGroup* _alignGA;
   QAction *_leftAlignAction;
   QAction *_rightAlignAction;
   QAction *_justifyAction;
   QAction *_centerAction;

  private slots :
     void _newFile();
     void _exit();
     void _leftAlign();
     void _rightAlign();
     void _justify();
     void _center();
     void _about();
     void _aboutQt();
};

