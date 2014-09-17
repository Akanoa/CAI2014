#include "enums.h"
#include "paintWindow.h"

//--------------------------------------------------------------------------------
PaintWindow::PaintWindow(QWidget *parent) : QMainWindow(parent) {
   qDebug() << "PaintWindow::PaintWindow(QWidget *parent)";
   qDebug() << "Date: " << QDate::currentDate();

   _createMenus();
   _createActions();
   _createToolBars();
   _connectActions();

  _area = new PaintArea(this);
   setCentralWidget(_area);

  _signalMapper = new QSignalMapper(this);
  _signalMapper->setMapping(_freehandAct, TOOLS_ID_FREEHAND);
  _signalMapper->setMapping(_lineAct, TOOLS_ID_LINE);
  _signalMapper->setMapping(_rectAct, TOOLS_ID_RECTANGLE);
  _signalMapper->setMapping(_elipsisAct, TOOLS_ID_CIRCLE);
  _signalMapper->setMapping(_polyAct, TOOLS_ID_POLYGON);
  _signalMapper->setMapping(_textAct, TOOLS_ID_TEXT);

  _savefilename = new QString("");

  _connectSignals();
}
//--------------------------------------------------------------------------------
void PaintWindow::_createMenus(void) {
 QMenuBar* menubar = menuBar(); 
 statusBar()->showMessage("Ready");
 _fileMenu = menubar->addMenu( tr("&File") );
 _toolMenu = menubar->addMenu(tr("&Tools"));
 _styleMenu = menubar->addMenu("&Style");
 _helpMenu = menubar->addMenu( tr("&Help") );

 //Create Submenus
 _penSubMenu = _styleMenu->addMenu( tr("&Pen") );
 _linePenSubMenu = _penSubMenu->addMenu( tr("&Line") );
 _widthPenSubMenu = _penSubMenu->addMenu( tr("&Width"));
 _brushSubMenu = _styleMenu->addMenu( tr("&Brush") );
 //_fillBrushSubMenu = _brushSubMenu->addMenu( tr("&Fill") );
}
//--------------------------------------------------------------------------------
void PaintWindow::_createToolBars(void) {
 _toolBar=addToolBar( tr("File") ); 
}
//--------------------------------------------------------------------------------
void PaintWindow::_createActions(void) {

  _newAct = new QAction(QIcon(":/Images/new.png"), tr("&New..."), this);
  _newAct->setIcon(QIcon(":/Images/new.png"));
  _newAct->setShortcut(tr("Ctrl+N"));
  _newAct->setToolTip(tr("New file tooltip"));
  _newAct->setStatusTip(tr("New file status"));
  _newAct->setData(QVariant("_newAct data"));

  _openAct = new QAction(QIcon(":/Images/open.png"), tr("&Open..."), this);
  _openAct->setIcon(QIcon(":/Images/open.png"));
  _openAct->setShortcut(tr("Ctrl+O"));
  _openAct->setToolTip(tr("Open file tooltip"));
  _openAct->setStatusTip(tr("Open file status"));
  _openAct->setData(QVariant("_openAct data"));

  _saveAct = new QAction(QIcon(":/Images/save.png"), tr("&Save"), this);
  _saveAct->setShortcut(tr("Ctrl+S"));
  _saveAct->setToolTip(tr("Sauvegarde dans un fichier par défaut"));
  _saveAct->setStatusTip(tr("Sauvegarde..."));
  _saveAct->setData(QVariant("_saveAct data"));

  _saveAsAct = new QAction(QIcon(":/Images/save.png"), tr("Save as"), this);
  _saveAsAct->setShortcut(tr("Ctrl+Shift+S"));
  _saveAsAct->setToolTip(tr("Sauvegarde dans un fichier"));
  _saveAsAct->setStatusTip(tr("Sauvegarde..."));
  _saveAsAct->setData(QVariant("_saveAsAct data"));

  _exitAct = new QAction(tr("&Exit..."), this);
  _exitAct->setShortcut(tr("Ctrl+q"));
  _exitAct->setToolTip(tr("Exit"));
  _exitAct->setStatusTip(tr("Exit"));
  _exitAct->setIcon(QIcon(":/Images/exit.png"));
  _exitAct->setData(QVariant("_quitAct data"));

  _aboutAct    = new QAction(tr("&About Us.."), this);
  _aboutQtAct    = new QAction(tr("&About Qt.."), this);

  _toolsQag = new QActionGroup( this );

  _freehandAct = new QAction(tr("&Freehand"),  this);
  _lineAct = new QAction(tr("&Line"), this);
  _rectAct = new QAction(tr("&Rectangle"), this);
  _elipsisAct = new QAction(tr("&Elipsis"), this);
  _polyAct = new QAction(tr("&Polygon"), this);
  _textAct = new QAction(tr("&Text"), this);

  _freehandAct->setCheckable(true);
  _lineAct->setCheckable(true);
  _rectAct->setCheckable(true);
  _polyAct->setCheckable(true);
  _elipsisAct->setCheckable(true);
  _textAct->setCheckable(true);

   //Style Menu
  _fontAct = new QAction(tr("&Font..."), this);
  _fontAct->setToolTip(tr("Font"));
  _fontAct->setStatusTip(tr("Font Selection"));
  _fontAct->setIcon(QIcon(":/Images/colorize.png"));
  _fontAct->setData(QVariant("_fontAct data"));
     //linePen submenu
  _colorPenAct = new QAction(tr("&Couleur..."), this);
  _colorPenAct->setToolTip(tr("Pen Color"));
  _colorPenAct->setStatusTip(tr("Pen Color"));
  _colorPenAct->setIcon(QIcon(":/Images/colorize.png"));
  _colorPenAct->setData(QVariant("_colorPenAct data"));

  _colorBrushAct = new QAction(tr("&Couleur..."), this);
  _colorBrushAct->setToolTip(tr("Brush Color"));
  _colorBrushAct->setStatusTip(tr("Brush Color"));
  _colorBrushAct->setIcon(QIcon(":/Images/colorize.png"));
  _colorBrushAct->setData(QVariant("_colorBrushAct data"));

    //WidthSubmenu

    //FillSubmenu
  _fillBrushAct= new QAction(tr("&Fill"),  this);

  _fillBrushAct->setCheckable(true);
}
//--------------------------------------------------------------------------------
void PaintWindow::_connectActions(void) {
 _fileMenu->addAction(_newAct);
 _fileMenu->insertSeparator(_openAct);
 _fileMenu->addAction(_openAct);
 _fileMenu->addAction(_saveAct);
 _fileMenu->addAction(_saveAsAct);
 _fileMenu->insertSeparator(_exitAct);
 _fileMenu->addAction(_exitAct);

 _toolBar->addAction(_newAct);
 _toolBar->addAction(_exitAct);

 _toolsQag->addAction(_freehandAct);
 _toolsQag->addAction(_lineAct);
 _toolsQag->addAction(_rectAct);
 _toolsQag->addAction(_elipsisAct);
 _toolsQag->addAction(_polyAct);
 _toolsQag->addAction(_textAct);

 _toolMenu->addAction(_freehandAct);
 _toolMenu->addAction(_lineAct);
 _toolMenu->addAction(_rectAct);
 _toolMenu->addAction(_elipsisAct);
 _toolMenu->addAction(_polyAct);
 _toolMenu->insertSeparator(_textAct);
 _toolMenu->addAction(_textAct);

 _penSubMenu->addAction(_colorPenAct);
 _brushSubMenu->addAction(_colorBrushAct);
 _brushSubMenu->addAction(_fillBrushAct);

 _styleMenu->addAction(_fontAct);

 _helpMenu->addAction(_aboutAct);
 _helpMenu->addAction(_aboutQtAct);
}

//--------------------------------------------------------------------------------
void PaintWindow::_connectSignals(void) {

 connect(_newAct, SIGNAL(triggered()), this,SLOT(_newFile( )) );
 connect(_exitAct,SIGNAL(activated()), this, SLOT(quit()));
 connect(_saveAct, SIGNAL(triggered()), this, SLOT(_save()));
 connect(_saveAsAct, SIGNAL(triggered()), this, SLOT(_saveAs()));
 connect(_openAct, SIGNAL(triggered()), this, SLOT(_open()));

 connect(_freehandAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_lineAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_rectAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_elipsisAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_polyAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_textAct,SIGNAL(activated()),_signalMapper, SLOT(map()));

 connect(_colorPenAct,SIGNAL(triggered()),this, SLOT(_changePenColor()));
 connect(_colorBrushAct,SIGNAL(triggered()),this, SLOT(_changeBrushColor()));

 connect(_aboutAct, SIGNAL(triggered()),this, SLOT(_about()));
 connect(_aboutQtAct,SIGNAL(triggered()),this, SLOT(_aboutQt()));

 connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
 connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)));
 connect(_fillBrushAct, SIGNAL(toggled(bool)), _area, SLOT(setFilled(bool)));
}
//--------------------------------------------------------------------------------
void PaintWindow::_about(void) {
 QMessageBox::information( this,"About Us","Yannick GUERN\nSimon TENEAU\n\nCAI Labo 2 2014","Retour vers l'application' !");
}

void PaintWindow::_aboutQt(void) {
 QMessageBox::aboutQt(this);
}
//--------------------------------------------------------------------------------
void PaintWindow::_newFile(void)  {
 qDebug() << "PaintWindow::_newFile(void)";
}

void PaintWindow::_save(void){

  if(_savefilename->isEmpty())
  {
    *_savefilename = QFileDialog::getSaveFileName(this, tr("Save File"), QString());
  }

  QFile file(*_savefilename);
  file.open(QIODevice::WriteOnly);

  _area->getBuffer()->save(&file, "PNG");

}

void PaintWindow::_saveAs(void){

  *_savefilename = QFileDialog::getSaveFileName(this, tr("Save File"), QString());

  QFile file(*_savefilename);
  file.open(QIODevice::WriteOnly);

  _area->getBuffer()->save(&file, "PNG");

}

void PaintWindow::_open(void){
  QString openfilename = QFileDialog::getOpenFileName(this, tr("Open File"), QString());
  // QByteArray ba;
  // QFile file(openfilename);
  // ba = file.readAll();
  // qDebug() << _area->getBuffer()->loadFromData(ba);
  qDebug() << _area->getBuffer()->load(openfilename);
  _area->update();
}

void PaintWindow::quit(void)  {
  exit(0);
}

//--------------------------------------------------------------------------------
void PaintWindow::_changePenColor(void)  {
 qDebug() << "PaintWindow::_changePenColor(void)";
 _area->setCurrentColor(QColorDialog::getColor(Qt::white, this));
 qDebug() << _colorPen;
}

void PaintWindow::_changeBrushColor(void)  {
 _area->setFillColor(QColorDialog::getColor(Qt::white, this));
}



void PaintWindow::keyPressEvent( QKeyEvent * event )
{
    qDebug() << "key pressed event " << event->key();
    switch ( event->key() )
    {
        case (16777220): // enter main  ()
            qDebug() << "Main enter ";
            _area->setEnterState(true);
            break;
        case(16777221): //enter numpad
             qDebug() << "numpad enter ";
            _area->setEnterState(true);
            break;
        case(16777216): //escape
             qDebug() << "escape";
            _area->setEscapeState(true);
            break;
    }
}
