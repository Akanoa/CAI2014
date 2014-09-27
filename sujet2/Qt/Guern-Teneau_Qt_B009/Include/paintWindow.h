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
#include <QFontDialog>
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
   void stylePenMapped(int digit);
   void capPenMapped(int digit);
   void joinPenMapped(int digit);
   void widthPenMapped(int digit);
   void styleBrushMapped(int digit);
  public slots :
    void quit(void);
    void showPopUp(QPoint value);
  private slots :
    void _newFile(void);
    void _save(void);
    void _saveAs(void);
    void _open(void);
    void _changePenColor(void);
    void _changeBrushColor(void);
    void _changeFont();
    void _about(void);
    void _aboutQt(void);
    void _undo(void);
    void _clear(void);
  private :
   void _createMenus(void);
   void _createToolBars(void);
   void _createActions(void);
   void _connectActions(void);
   void _connectSignals(void);
   void _createAndSetMappers(void);

 protected :
   void keyPressEvent( QKeyEvent *event );
   void closeEvent (QCloseEvent *);

   // client
   PaintArea *_area;
   QScrollArea* _scrolledArea;
   // menus
   QToolBar *_toolBar, *_editToolBar, *_toolsToolBar, *_stylePenToolBar, *_capPenToolBar, *_joinPenToolBar, *_widthPenToolBar, *_styleBrushToolBar;
   QMenu *_fileMenu, *_editMenu, *_toolMenu,*_styleMenu, *_helpMenu, *_popUpMenu ;
   //SubMenus
   QMenu *_penSubMenu, *_brushSubMenu,*_linePenSubMenu,*_lineCapSubMenu,*_lineJoinSubMenu, *_widthPenSubMenu, *_fillBrushSubMenu;
   // actions
   QAction *_newAct, *_openAct, *_saveAct, *_saveAsAct, *_exitAct, *_aboutAct, *_aboutQtAct;
   QActionGroup *_toolsQag, *_stylePenQag, *_capPenQag, *_joinPenQag, *_widthPenQag, *_styleBrushQag;
   QAction *_freehandAct, *_lineAct, *_rectAct, *_elipsisAct, *_polyAct, *_textAct;
   QAction *_colorPenAct, *_colorBrushAct, *_fontAct;
   //Actions stylePen
   QAction *_solidStylePenAct,*_dashStylePenAct, *_dotStylePenAct, *_dashdotStylePenAct, *_dashdotnotStylePenAct, *_noneStylePenAct;
   //Actions capPen
   QAction *_flatCapPenAct, *_squareCapPenAct, *_roundCapPenAct;
   //Action JoinPen
   QAction *_miterJoinPenAct, *_bevelJoinPenAct, *_roundJoinPenAct;
   //Action width
   QAction *_widthMinAct, *_widthSel1Act, *_widthSel2Act, *_widthSel3Act, *_widthMaxAct;
    //Action stylebrush
   QAction *_lineargradientStyleBrushAct, *_radialgradientStyleBrushAct, *_conicalgradientStyleBrushAct, *_textureStyleBrushAct, *_solidStyleBrushAct, *_horizontalStyleBrushAct, *_verticalStyleBrushAct, *_crossStyleBrushAct, *_backwarddiagonalStyleBrushAct, *_forwarddiagonalStyleBrushAct, *_diagonalcrossStyleBrushAct, *_dense1StyleBrushAct, *_dense2StyleBrushAct, *_dense3StyleBrushAct, *_dense4StyleBrushAct, *_dense5StyleBrushAct, *_dense6StyleBrushAct, *_dense7StyleBrushAct, *_noneStyleBrushAct;

   //Others actions
   QAction *_undoAction, *_clearAction;
   // mapping 
   QSignalMapper *_signalMapper, *_signalMapperStylePen, *_signalMapperCapPen , *_signalMapperJoinPen, *_signalMapperWidthPen, *_signalMapperStyleBrush;
   //Filename
   QString *_savefilename;
   QColor _colorPen;
};
#endif

