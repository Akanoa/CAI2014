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
  _scrolledArea = new QScrollArea();
  _scrolledArea->resize(this->width(),this->height());
   _area = new PaintArea(_scrolledArea);
  _scrolledArea->setWidget(_area);
  _scrolledArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  _scrolledArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  _scrolledArea->setWidgetResizable(true);
  this->setCentralWidget(_scrolledArea);

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
 _editMenu = menubar->addMenu(tr("&Edit"));
 _toolMenu = menubar->addMenu(tr("&Tools"));
 _styleMenu = menubar->addMenu("&Style");
 _helpMenu = menubar->addMenu( tr("&Help") );

 //Create Submenus
 _penSubMenu = _styleMenu->addMenu( tr("&Pen") );
 _linePenSubMenu = _penSubMenu->addMenu( tr("&Line") );
 _widthPenSubMenu = _penSubMenu->addMenu( tr("&Width"));
 _brushSubMenu = _styleMenu->addMenu( tr("&Brush") );
 _fillBrushSubMenu = _brushSubMenu->addMenu(tr("&Type") );
 //_fillBrushSubMenu = _brushSubMenu->addMenu( tr("&Fill") );

 //Create PopUp
 _popUpMenu = new QMenu();
 _popUpMenu->addMenu(_editMenu);
 _popUpMenu->addMenu(_toolMenu);
 _popUpMenu->addMenu(_styleMenu);
}
//--------------------------------------------------------------------------------
void PaintWindow::_createToolBars(void) {
 _toolBar=addToolBar( tr("File") ); 
 _editToolBar=addToolBar( tr("Edit") );

 _toolsToolBar = new QToolBar( tr("Tools"));
 _toolsToolBar->setOrientation(Qt::Vertical);
 addToolBar(Qt::LeftToolBarArea ,_toolsToolBar);

 _styleToolBar = new QToolBar( tr("Style"));
 _styleToolBar->setOrientation(Qt::Vertical);
 addToolBar(Qt::RightToolBarArea ,_styleToolBar);
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
  _saveAct->setToolTip(tr("Save in defaultFile or choosen file."));
  _saveAct->setStatusTip(tr("Save in defaultFile or choosen file."));
  _saveAct->setData(QVariant("_saveAct data"));

  _saveAsAct = new QAction(QIcon(":/Images/save_as.png"), tr("Save as"), this);
  _saveAsAct->setShortcut(tr("Ctrl+Shift+S"));
  _saveAsAct->setToolTip(tr("Choose the file where you want to save your draw..."));
  _saveAsAct->setStatusTip(tr("Choose the file where you want to save your draw..."));
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
  _freehandAct->setToolTip(tr("Freehand"));
  _freehandAct->setStatusTip(tr("Freehand"));
  _freehandAct->setIcon(QIcon(":/Images/tool_pen.png"));
  _freehandAct->setData(QVariant("_freehandAct data"));

  _lineAct = new QAction(tr("&Line"), this);
  _lineAct->setToolTip(tr("Line"));
  _lineAct->setStatusTip(tr("Line"));
  _lineAct->setIcon(QIcon(":/Images/tool_line.png"));
  _lineAct->setData(QVariant("_lineAct data"));

  _rectAct = new QAction(tr("&Rectangle"), this);
  _rectAct->setToolTip(tr("Rectangle"));
  _rectAct->setStatusTip(tr("Rectangle Selection"));
  _rectAct->setIcon(QIcon(":/Images/tool_rectangle.png"));
  _rectAct->setData(QVariant("_rectAct data"));

  _elipsisAct = new QAction(tr("&Elipsis"), this);
  _elipsisAct->setToolTip(tr("Ellipse"));
  _elipsisAct->setStatusTip(tr("Ellipse Selection"));
  _elipsisAct->setIcon(QIcon(":/Images/tool_ellipse.png"));
  _elipsisAct->setData(QVariant("_elipsisAct data"));

  _polyAct = new QAction(tr("&Polygon"), this);
  _polyAct->setToolTip(tr("Polygon"));
  _polyAct->setStatusTip(tr("Polygon"));
  _polyAct->setIcon(QIcon(":/Images/tool_polygon.png"));
  _polyAct->setData(QVariant("_polyAct data"));

  _textAct = new QAction(tr("&Text"), this);
  _textAct->setToolTip(tr("Text"));
  _textAct->setStatusTip(tr("Text"));
  _textAct->setIcon(QIcon(":/Images/tool_font.png"));
  _textAct->setData(QVariant("_fontAct data"));

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
  _fontAct->setIcon(QIcon(":/Images/tool_font.png"));
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
  _undoAction = new QAction(tr("&Undo"), this);
  _undoAction->setShortcut(tr("Ctrl+z"));
  _undoAction->setToolTip(tr("Undo"));
  _undoAction->setStatusTip(tr("Undo"));
  _undoAction->setIcon(QIcon(":/Images/undo.png"));
  _undoAction->setData(QVariant("_colorBrushAct data"));

  _clearAction = new QAction(tr("&Clear"), this);
  _clearAction->setShortcut(tr("Ctrl+F"));
  _clearAction->setToolTip(tr("Clear"));
  _clearAction->setStatusTip(tr("Clear"));
  _clearAction->setIcon(QIcon(":/Images/clear.png"));
  _clearAction->setData(QVariant("_clearAction data"));

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
 _toolBar->insertSeparator(_openAct);
 _toolBar->addAction(_openAct);
 _toolBar->addAction(_saveAct);
 _toolBar->addAction(_saveAsAct);
 _toolBar->insertSeparator(_exitAct);
 _toolBar->addAction(_exitAct);

 _editMenu->addAction(_undoAction);
 _editMenu->addAction(_clearAction);

 _editToolBar->addAction(_undoAction);
 _editToolBar->addAction(_clearAction);

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

 _toolsToolBar->addAction(_freehandAct);
 _toolsToolBar->addAction(_lineAct);
 _toolsToolBar->addAction(_rectAct);
 _toolsToolBar->addAction(_elipsisAct);
 _toolsToolBar->addAction(_polyAct);
 _toolsToolBar->insertSeparator(_textAct);
 _toolsToolBar->addAction(_textAct);

 _penSubMenu->addAction(_colorPenAct);
 _brushSubMenu->addAction(_colorBrushAct);
 _brushSubMenu->addAction(_fillBrushAct);

 _styleMenu->addAction(_fontAct);

 /*
 _styleToolBar->addAction(_penSubMenu);
 _styleToolBar->addAction(_colorBrushAct);
 _styleToolBar->addAction(_brushSubMenu);
 _styleToolBar->insertSeparator(_fontAct);
 _styleToolBar->addAction(_fontAct);
 */

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
 connect(_fontAct, SIGNAL(triggered()), this, SLOT(_changeFont()));

 connect(_aboutAct, SIGNAL(triggered()),this, SLOT(_about()));
 connect(_aboutQtAct,SIGNAL(triggered()),this, SLOT(_aboutQt()));

 connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
 connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)));
 connect(_fillBrushAct, SIGNAL(toggled(bool)), _area, SLOT(setFilled(bool)));

 connect(_undoAction, SIGNAL(triggered()), this, SLOT(_undo()));
 connect(_clearAction, SIGNAL(triggered()), this, SLOT(_clear()));

 //pop-up
 connect(_area,SIGNAL(popUpAsked(QPoint)), this, SLOT(showPopUp(QPoint)));
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
 QMessageBox msgBox;
 msgBox.setIcon(QMessageBox::Warning);
 msgBox.setText("Le document a été modifié. Vous voulez ouvrir un nouveau fichier.");
 msgBox.setInformativeText("Voulez-vous enregistrer les changements ?");
 msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Ignore);
 msgBox.setDefaultButton(QMessageBox::Save);
 int ret = msgBox.exec();

 switch (ret) {
    case QMessageBox::Save:
        // Clic sur Enregistrer
        _saveAs();
        break;
    case QMessageBox::Ignore:
        // Clic sur nouveau sans enregistrer
        _area->clearDrawArea();
        break;
    case QMessageBox::Cancel:
        // Clic sur Annuler
        //DO NOTHING
        break;
    default:
        // ne doit pas se produire
        break;
    }
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
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Le document a été modifié. et vous aller quitter le programme.");
    msgBox.setInformativeText("Voulez-vous enregistrer les changements ?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
       case QMessageBox::Save:
           // Clic sur Enregistrer
           _saveAs();
           break;
       case QMessageBox::Discard:
           // Clic sur fermer sans enregistrer
           exit(0);
           break;
       case QMessageBox::Cancel:
           // Clic sur Annuler
           //DO NOTHING
           break;
       default:
           // ne doit pas se produire
           break;
     }
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


void PaintWindow::_undo(void)  {
 qDebug() << "undoPaintWindow";
 _area->undo();
}

void PaintWindow::_clear(){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("You have clicked on the clear option, this will delete all yours modifications");
    msgBox.setInformativeText("Do your really want to clear the screen?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret) {
       case QMessageBox::Yes:
            qDebug() << "clearWindow";
            _area->clearDrawArea();
           break;
       case QMessageBox::No:
            //TONOTHING
           break;
       default:
           break;
       }
}

void PaintWindow::keyPressEvent( QKeyEvent * event )
{
    qDebug() << "key pressed event " << event->key();
    switch ( event->key() )
    {
        case (16777220): // enter main  ()
            qDebug() << "Main enter ";
            _area->setEnterState(true);
            if(_area->getEditing())_area->setEndEdition();
            break;
        case(16777221): //enter numpad
             qDebug() << "numpad enter ";
            _area->setEnterState(true);
            if(_area->getEditing())_area->setEndEdition();
            break;
        case(16777216): //escape
             qDebug() << "escape";
            _area->setEscapeState(true);
            break;
    }

    if(_area->getEditing())
    {
      _area->setCurrentText(event->text());
      update();
    }
}


void PaintWindow::_changeFont()
{
  bool ok;
  QFont font = QFontDialog::getFont(
                 &ok, QFont("Helvetica [Cronyx]", 10), this);
  if (ok) {
     _area->setFont(font);
  } else {
    _area->setFont(QFont("Helvetica [Cronyx]", 10));
  }
}

void PaintWindow::closeEvent(QCloseEvent *event)
{
    quit();
    event->ignore();
}

void PaintWindow::showPopUp(QPoint value)
{
       qDebug() << "show pop up " << value;
       _popUpMenu->exec(value);
}
