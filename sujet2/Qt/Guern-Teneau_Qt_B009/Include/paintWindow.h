#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QActionGroup>
#include <QIcon>
#include <QMessageBox>
#include <QScrollArea>
#include <QSignalMapper>
#include <QFileDialog>
#include <QColorDialog>
#include <QKeyEvent>

#include <QDebug>
#include <QDate>

#include "paintArea.h"


class PaintWindow : public QMainWindow
{
  Q_OBJECT  
  public:
    PaintWindow(QWidget *parent = 0);
  signals:
   void toolMapped(int digit);
  public slots :
    void quit(void);
  private slots :
    void _newFile(void);
    void _save(void);
    void _saveAs(void);
    void _open(void);
    void _changePenColor(void);
    void _changeBrushColor(void);
    void _about(void);
    void _aboutQt(void);
  private :
   void _createMenus(void);
   void _createToolBars(void);
   void _createActions(void);
   void _connectActions(void);
   void _connectSignals(void);

 protected :
   void keyPressEvent( QKeyEvent *event );

   // client
   PaintArea *_area;
   // menus
   QToolBar *_toolBar;
   QMenu *_fileMenu, *_toolMenu,*_styleMenu, *_helpMenu ;
   //SubMenus
   QMenu *_penSubMenu, *_brushSubMenu,*_linePenSubMenu, *_widthPenSubMenu, *_fillBrushSubMenu;
   // actions
   QAction *_newAct, *_openAct, *_saveAct, *_saveAsAct, *_exitAct, *_aboutAct, *_aboutQtAct;
   QActionGroup *_toolsQag;
   QAction *_freehandAct, *_lineAct, *_rectAct, *_elipsisAct, *_polyAct, *_textAct;
   QAction *_colorPenAct, *_colorBrushAct, *_fontAct, *_fillBrushAct;
   // mapping 
   QSignalMapper *_signalMapper;
   //Filename
   QString *_savefilename;
   QColor _colorPen;
};
#endif

