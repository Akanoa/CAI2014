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

  _createAndSetMappers();

  _savefilename = new QString("");

  _connectSignals();

  /*
    INITIALISATION PART
   */
    _lineAct->setChecked(true);
    _solidStylePenAct->setChecked(true);
    _squareCapPenAct->setChecked(true);
    _bevelJoinPenAct->setChecked(true);
    _widthMinAct->setChecked(true);
    _noneStyleBrushAct->setChecked(true);


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
 _lineCapSubMenu = _penSubMenu->addMenu( tr("&Cap") );
 _lineJoinSubMenu = _penSubMenu->addMenu( tr("&Join") );
 _widthPenSubMenu = _penSubMenu->addMenu( tr("&Width"));
 _brushSubMenu = _styleMenu->addMenu( tr("&Brush") );
 _fillBrushSubMenu = _brushSubMenu->addMenu(tr("&Type") );

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
 //_toolsToolBar->setOrientation(Qt::Vertical);
 addToolBar(Qt::TopToolBarArea ,_toolsToolBar);

 _stylePenToolBar = new QToolBar( tr("Style Pen"));
 _stylePenToolBar->setOrientation(Qt::Vertical);
 addToolBar(Qt::LeftToolBarArea ,_stylePenToolBar);

 _capPenToolBar = new QToolBar( tr("Cap Pen"));
 _capPenToolBar->setOrientation(Qt::Vertical);
 addToolBar(Qt::LeftToolBarArea ,_capPenToolBar);

 _joinPenToolBar = new QToolBar( tr("Join Pen"));
 _joinPenToolBar->setOrientation(Qt::Vertical);
 addToolBar(Qt::LeftToolBarArea ,_joinPenToolBar);

 _widthPenToolBar = new QToolBar( tr("Width Pen"));
 _widthPenToolBar->setOrientation(Qt::Vertical);
 addToolBar(Qt::LeftToolBarArea ,_widthPenToolBar);

 _styleBrushToolBar = new QToolBar( tr("Brush Style"));
 _styleBrushToolBar->setOrientation(Qt::Vertical);
 addToolBar(Qt::RightToolBarArea ,_styleBrushToolBar);
}
//--------------------------------------------------------------------------------
void PaintWindow::_createActions(void)
{
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

     //penSubMenu submenu
    _colorPenAct = new QAction(tr("&Color..."), this);
    _colorPenAct->setToolTip(tr("Pen Color"));
    _colorPenAct->setStatusTip(tr("Pen Color"));
    _colorPenAct->setIcon(QIcon(":/Images/colorize.png"));
    _colorPenAct->setData(QVariant("_colorPenAct data"));

    //stylePen submenu
    _solidStylePenAct = new QAction(tr("&Solid"), this);
    _solidStylePenAct->setToolTip(tr("Style Pen Solid"));
    _solidStylePenAct->setStatusTip(tr("Style Pen Solid"));
    _solidStylePenAct->setIcon(QIcon(":/Images/colorize.png"));
    _solidStylePenAct->setData(QVariant("_solidStylePenAct data"));

    _dashStylePenAct = new QAction(tr("&Dash"), this);
    _dashStylePenAct->setToolTip(tr("Style Pen Dash"));
    _dashStylePenAct->setStatusTip(tr("Style Pen Dash"));
    _dashStylePenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dashStylePenAct->setData(QVariant("_dashStylePenAct data"));

    _dotStylePenAct = new QAction(tr("&Dot"), this);
    _dotStylePenAct->setToolTip(tr("Style Pen Dot"));
    _dotStylePenAct->setStatusTip(tr("Style Pen Dot"));
    _dotStylePenAct->setIcon(QIcon(":/Images/tool_line.png"));
    _dotStylePenAct->setData(QVariant("_dotStylePenAct data"));

    _dashdotStylePenAct = new QAction(tr("&Dash dot"), this);
    _dashdotStylePenAct->setToolTip(tr("Style Pen dash dot"));
    _dashdotStylePenAct->setStatusTip(tr("Style Pen dash dot"));
    _dashdotStylePenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dashdotStylePenAct->setData(QVariant("_dashdotStylePenAct data"));

    _dashdotnotStylePenAct = new QAction(tr("&Dash dot not "), this);
    _dashdotnotStylePenAct->setToolTip(tr("Style Pen dash dot not"));
    _dashdotnotStylePenAct->setStatusTip(tr("Style Pen dash dot not"));
    _dashdotnotStylePenAct->setIcon(QIcon(":/Images/colorize.png"));
    _dashdotnotStylePenAct->setData(QVariant("_dashdotnotStylePenAct data"));

    _noneStylePenAct = new QAction(tr("&None"), this);
    _noneStylePenAct->setToolTip(tr("Style Pen none"));
    _noneStylePenAct->setStatusTip(tr("Style Pen none"));
    _noneStylePenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _noneStylePenAct->setData(QVariant("_noneStylePenAct data"));

    _solidStylePenAct->setCheckable(true);
    _dashStylePenAct->setCheckable(true);
    _dotStylePenAct->setCheckable(true);
    _dashdotStylePenAct->setCheckable(true);
    _dashdotnotStylePenAct->setCheckable(true);
    _noneStylePenAct->setCheckable(true);

    //CapSubMenu
    _flatCapPenAct = new QAction(tr("&Flat"), this);
    _flatCapPenAct->setToolTip(tr("Style cap flat"));
    _flatCapPenAct->setStatusTip(tr("Style cap flat"));
    _flatCapPenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _flatCapPenAct->setData(QVariant("_flatCapPenAct data"));

    _squareCapPenAct = new QAction(tr("&Square"), this);
    _squareCapPenAct->setToolTip(tr("Style cap square"));
    _squareCapPenAct->setStatusTip(tr("Style cap square"));
    _squareCapPenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _squareCapPenAct->setData(QVariant("_squareCapPenAct data"));

    _roundCapPenAct = new QAction(tr("&Round"), this);
    _roundCapPenAct->setToolTip(tr("Style cap Round"));
    _roundCapPenAct->setStatusTip(tr("Style cap Round"));
    _roundCapPenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _roundCapPenAct->setData(QVariant("_roundCapPenAct data"));

    _flatCapPenAct->setCheckable(true);
    _squareCapPenAct->setCheckable(true);
    _roundCapPenAct->setCheckable(true);

    //joinSubMenu
    _miterJoinPenAct = new QAction(tr("&Miter"), this);
    _miterJoinPenAct->setToolTip(tr("Style Join Miter"));
    _miterJoinPenAct->setStatusTip(tr("Style Join Miter"));
    _miterJoinPenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _miterJoinPenAct->setData(QVariant("_miterJoinPenAct data"));

    _bevelJoinPenAct = new QAction(tr("&Bevel"), this);
    _bevelJoinPenAct->setToolTip(tr("Style Join bevel"));
    _bevelJoinPenAct->setStatusTip(tr("Style Join bevel"));
    _bevelJoinPenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _bevelJoinPenAct->setData(QVariant("_bevelJoinPenAct data"));

    _roundJoinPenAct = new QAction(tr("&round"), this);
    _roundJoinPenAct->setToolTip(tr("Style Join round"));
    _roundJoinPenAct->setStatusTip(tr("Style Join round"));
    _roundJoinPenAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _roundJoinPenAct->setData(QVariant("_roundJoinPenAct data"));

    _miterJoinPenAct->setCheckable(true);
    _bevelJoinPenAct->setCheckable(true);
    _roundJoinPenAct->setCheckable(true);

    /* WidthSubmenu */
    _widthMinAct = new QAction(tr("&Size Min"), this);
    _widthMinAct->setToolTip(tr("Size minimum"));
    _widthMinAct->setStatusTip(tr("Size minimum"));
    _widthMinAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _widthMinAct->setData(QVariant("_widthMinAct data"));

    _widthSel1Act = new QAction(tr("&Size selector 1"), this);
    _widthSel1Act->setToolTip(tr("Size selector 1"));
    _widthSel1Act->setStatusTip(tr("Size selector 1"));
    _widthSel1Act->setIcon(QIcon(":/Images/tool_pen.png"));
    _widthSel1Act->setData(QVariant("_widthSel1Act data"));

    _widthSel2Act = new QAction(tr("&Size selector 2"), this);
    _widthSel2Act->setToolTip(tr("Size selector 2"));
    _widthSel2Act->setStatusTip(tr("Size selector 2"));
    _widthSel2Act->setIcon(QIcon(":/Images/tool_pen.png"));
    _widthSel2Act->setData(QVariant("_widthSel2Act data"));

    _widthSel3Act = new QAction(tr("&Size selector 3"), this);
    _widthSel3Act->setToolTip(tr("Size selector 3"));
    _widthSel3Act->setStatusTip(tr("Size selector 3"));
    _widthSel3Act->setIcon(QIcon(":/Images/tool_pen.png"));
    _widthSel3Act->setData(QVariant("_widthSel3Act data"));

    _widthMaxAct = new QAction(tr("&Size Max"), this);
    _widthMaxAct->setToolTip(tr("Size maximum"));
    _widthMaxAct->setStatusTip(tr("Size maximum"));
    _widthMaxAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _widthMaxAct->setData(QVariant("_widthMaxAct data"));

    _widthMinAct->setCheckable(true);
    _widthSel1Act->setCheckable(true);
    _widthSel2Act->setCheckable(true);
    _widthSel3Act->setCheckable(true);
    _widthMaxAct->setCheckable(true);

    //fillBrushSubMenu
    _lineargradientStyleBrushAct = new QAction(tr("&Linear Gradient"), this);
    _lineargradientStyleBrushAct->setToolTip(tr("Style brush linearGradient"));
    _lineargradientStyleBrushAct->setStatusTip(tr("Style brush lineardGradient"));
    _lineargradientStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _lineargradientStyleBrushAct->setData(QVariant("_lineargradientStyleBrushAct data"));

    _radialgradientStyleBrushAct = new QAction(tr("&Radial Gradient"), this);
    _radialgradientStyleBrushAct->setToolTip(tr("Style brush radial gradient"));
    _radialgradientStyleBrushAct->setStatusTip(tr("Style brush radial gradient"));
    _radialgradientStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _radialgradientStyleBrushAct->setData(QVariant("_radialgradientStyleBrushAct data"));

    _conicalgradientStyleBrushAct = new QAction(tr("&Conical gradient"), this);
    _conicalgradientStyleBrushAct->setToolTip(tr("Style brush conical gradient"));
    _conicalgradientStyleBrushAct->setStatusTip(tr("Style brush conical gradient"));
    _conicalgradientStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _conicalgradientStyleBrushAct->setData(QVariant("_conicalgradientStyleBrushAct data"));

    _textureStyleBrushAct = new QAction(tr("&Texture"), this);
    _textureStyleBrushAct->setToolTip(tr("Style brush texture"));
    _textureStyleBrushAct->setStatusTip(tr("Style brush texture"));
    _textureStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _textureStyleBrushAct->setData(QVariant("_textureStyleBrushAct data"));

    _solidStyleBrushAct = new QAction(tr("&Solid"), this);
    _solidStyleBrushAct->setToolTip(tr("Style brush solid"));
    _solidStyleBrushAct->setStatusTip(tr("Style brush solid"));
    _solidStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _solidStyleBrushAct->setData(QVariant("_solidStyleBrushAct data"));

    _horizontalStyleBrushAct = new QAction(tr("&Horizontal"), this);
    _horizontalStyleBrushAct->setToolTip(tr("Style brush horizontal"));
    _horizontalStyleBrushAct->setStatusTip(tr("Style brush horizontal"));
    _horizontalStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _horizontalStyleBrushAct->setData(QVariant("_horizontalStyleBrushAct data"));

    _verticalStyleBrushAct = new QAction(tr("&Vertical"), this);
    _verticalStyleBrushAct->setToolTip(tr("Style brush vertical"));
    _verticalStyleBrushAct->setStatusTip(tr("Style brush vertical"));
    _verticalStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _verticalStyleBrushAct->setData(QVariant("_verticalStyleBrushAct data"));

    _crossStyleBrushAct = new QAction(tr("&Cross"), this);
    _crossStyleBrushAct->setToolTip(tr("Style brush Cross"));
    _crossStyleBrushAct->setStatusTip(tr("Style brush Cross"));
    _crossStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _crossStyleBrushAct->setData(QVariant("_crossStyleBrushAct data"));

    _backwarddiagonalStyleBrushAct = new QAction(tr("&Backward Diagonal"), this);
    _backwarddiagonalStyleBrushAct->setToolTip(tr("Style brush Backward Diagonal"));
    _backwarddiagonalStyleBrushAct->setStatusTip(tr("Style brush Backward Diagonal"));
    _backwarddiagonalStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _backwarddiagonalStyleBrushAct->setData(QVariant("_backwarddiagonalStyleBrushAct data"));

    _forwarddiagonalStyleBrushAct = new QAction(tr("&Forward Diagonal"), this);
    _forwarddiagonalStyleBrushAct->setToolTip(tr("Style brush forward diagonal"));
    _forwarddiagonalStyleBrushAct->setStatusTip(tr("Style brush Forward Diagonal"));
    _forwarddiagonalStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _forwarddiagonalStyleBrushAct->setData(QVariant("_forwarddiagonalStyleBrushAct data"));

    _diagonalcrossStyleBrushAct = new QAction(tr("&Diagonal Cross"), this);
    _diagonalcrossStyleBrushAct->setToolTip(tr("Style brush Diagonal Cross"));
    _diagonalcrossStyleBrushAct->setStatusTip(tr("Style brush diagonal Cross"));
    _diagonalcrossStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _diagonalcrossStyleBrushAct->setData(QVariant("_diagonalcrossStyleBrushAct data"));

    _dense1StyleBrushAct = new QAction(tr("&Dense 1"), this);
    _dense1StyleBrushAct->setToolTip(tr("Style brush Dense1"));
    _dense1StyleBrushAct->setStatusTip(tr("Style brush Dense1"));
    _dense1StyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dense1StyleBrushAct->setData(QVariant("_dense1StyleBrushAct data"));

    _dense2StyleBrushAct = new QAction(tr("&Dense2"), this);
    _dense2StyleBrushAct->setToolTip(tr("Style brush Dense2"));
    _dense2StyleBrushAct->setStatusTip(tr("Style brush Dense2"));
    _dense2StyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dense2StyleBrushAct->setData(QVariant("_dense2StyleBrushAct data"));

    _dense3StyleBrushAct = new QAction(tr("&Dense3"), this);
    _dense3StyleBrushAct->setToolTip(tr("Style brush Dense3"));
    _dense3StyleBrushAct->setStatusTip(tr("Style brush Dense3"));
    _dense3StyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dense3StyleBrushAct->setData(QVariant("_dense3StyleBrushAct data"));

    _dense4StyleBrushAct = new QAction(tr("&Dense4"), this);
    _dense4StyleBrushAct->setToolTip(tr("Style brush Dense4"));
    _dense4StyleBrushAct->setStatusTip(tr("Style brush Dense4"));
    _dense4StyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dense4StyleBrushAct->setData(QVariant("_dense4StyleBrushAct data"));

    _dense5StyleBrushAct = new QAction(tr("&Dense5"), this);
    _dense5StyleBrushAct->setToolTip(tr("Style brush Dense5"));
    _dense5StyleBrushAct->setStatusTip(tr("Style brush Dense5"));
    _dense5StyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dense5StyleBrushAct->setData(QVariant("_dense5StyleBrushAct data"));

    _dense6StyleBrushAct = new QAction(tr("&Dense6"), this);
    _dense6StyleBrushAct->setToolTip(tr("Style brush Dense6"));
    _dense6StyleBrushAct->setStatusTip(tr("Style brush Dense6"));
    _dense6StyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dense6StyleBrushAct->setData(QVariant("_dense6StyleBrushAct data"));

    _dense7StyleBrushAct = new QAction(tr("&Dense7"), this);
    _dense7StyleBrushAct->setToolTip(tr("Style brush Dense7"));
    _dense7StyleBrushAct->setStatusTip(tr("Style brush Dense7"));
    _dense7StyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _dense7StyleBrushAct->setData(QVariant("_dense7StyleBrushAct data"));

    _noneStyleBrushAct = new QAction(tr("&None"), this);
    _noneStyleBrushAct->setToolTip(tr("Style brush None"));
    _noneStyleBrushAct->setStatusTip(tr("Style brush None"));
    _noneStyleBrushAct->setIcon(QIcon(":/Images/tool_pen.png"));
    _noneStyleBrushAct->setData(QVariant("_noneStyleBrushAct data"));

    _lineargradientStyleBrushAct->setCheckable(true);
    _radialgradientStyleBrushAct->setCheckable(true);
    _conicalgradientStyleBrushAct->setCheckable(true);
    _textureStyleBrushAct->setCheckable(true);
    _solidStyleBrushAct->setCheckable(true);
    _horizontalStyleBrushAct->setCheckable(true);
    _verticalStyleBrushAct->setCheckable(true);
    _crossStyleBrushAct->setCheckable(true);
    _backwarddiagonalStyleBrushAct->setCheckable(true);
    _forwarddiagonalStyleBrushAct->setCheckable(true);
    _diagonalcrossStyleBrushAct->setCheckable(true);
    _dense1StyleBrushAct->setCheckable(true);
    _dense2StyleBrushAct->setCheckable(true);
    _dense3StyleBrushAct->setCheckable(true);
    _dense4StyleBrushAct->setCheckable(true);
    _dense5StyleBrushAct->setCheckable(true);
    _dense6StyleBrushAct->setCheckable(true);
    _dense7StyleBrushAct->setCheckable(true);
    _noneStyleBrushAct->setCheckable(true);

    _colorBrushAct = new QAction(tr("&Color...."), this);
    _colorBrushAct->setToolTip(tr("Set Brush's color"));
    _colorBrushAct->setStatusTip(tr("Set Brush's color"));
    _colorBrushAct->setIcon(QIcon(":/Images/colorize.png"));
    _colorBrushAct->setData(QVariant("_colorBrushAct data"));

    //_editMenu
    _undoAction = new QAction(tr("&Undo"), this);
    _undoAction->setShortcut(tr("Ctrl+z"));
    _undoAction->setToolTip(tr("Undo"));
    _undoAction->setStatusTip(tr("Undo"));
    _undoAction->setIcon(QIcon(":/Images/undo.png"));
    _undoAction->setData(QVariant("_undoAction data"));

    _clearAction = new QAction(tr("&Clear"), this);
    _clearAction->setShortcut(tr("Ctrl+F"));
    _clearAction->setToolTip(tr("Clear"));
    _clearAction->setStatusTip(tr("Clear"));
    _clearAction->setIcon(QIcon(":/Images/clear.png"));
    _clearAction->setData(QVariant("_clearAction data"));

    //Action groups init
    _toolsQag = new QActionGroup( this );
    _stylePenQag = new QActionGroup( this );
    _capPenQag = new QActionGroup( this );
    _joinPenQag = new QActionGroup( this );
    _widthPenQag = new QActionGroup( this );
    _styleBrushQag = new QActionGroup( this );
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

 _linePenSubMenu->addAction(_solidStylePenAct);
 _linePenSubMenu->addAction(_dashStylePenAct);
 _linePenSubMenu->addAction(_dotStylePenAct);
 _linePenSubMenu->addAction(_dashdotStylePenAct);
 _linePenSubMenu->addAction(_dashdotnotStylePenAct);
 _linePenSubMenu->addAction(_noneStylePenAct);

 _stylePenToolBar->addAction(_solidStylePenAct);
 _stylePenToolBar->addAction(_dashStylePenAct);
 _stylePenToolBar->addAction(_dotStylePenAct);
 _stylePenToolBar->addAction(_dashdotStylePenAct);
 _stylePenToolBar->addAction(_dashdotnotStylePenAct);
 _stylePenToolBar->addAction(_noneStylePenAct);

 _lineCapSubMenu->addAction(_flatCapPenAct);
 _lineCapSubMenu->addAction(_squareCapPenAct);
 _lineCapSubMenu->addAction(_roundCapPenAct);

 _capPenToolBar->addAction(_flatCapPenAct);
 _capPenToolBar->addAction(_squareCapPenAct);
 _capPenToolBar->addAction(_roundCapPenAct);

 _lineJoinSubMenu->addAction(_miterJoinPenAct);
 _lineJoinSubMenu->addAction(_bevelJoinPenAct);
 _lineJoinSubMenu->addAction(_roundJoinPenAct);

 _joinPenToolBar->addAction(_miterJoinPenAct);
 _joinPenToolBar->addAction(_bevelJoinPenAct);
 _joinPenToolBar->addAction(_roundJoinPenAct);

 _widthPenSubMenu->addAction(_widthMinAct);
 _widthPenSubMenu->addAction(_widthSel1Act);
 _widthPenSubMenu->addAction(_widthSel2Act);
 _widthPenSubMenu->addAction(_widthSel3Act);
 _widthPenSubMenu->addAction(_widthMaxAct);

 _widthPenToolBar->addAction(_widthMinAct);
 _widthPenToolBar->addAction(_widthSel1Act);
 _widthPenToolBar->addAction(_widthSel2Act);
 _widthPenToolBar->addAction(_widthSel3Act);
 _widthPenToolBar->addAction(_widthMaxAct);

 _brushSubMenu->addAction(_colorBrushAct);

 _fillBrushSubMenu->addAction(_lineargradientStyleBrushAct);
 _fillBrushSubMenu->addAction(_radialgradientStyleBrushAct);
 _fillBrushSubMenu->addAction(_conicalgradientStyleBrushAct);
 _fillBrushSubMenu->addAction(_textureStyleBrushAct);
 _fillBrushSubMenu->addAction(_solidStyleBrushAct);
 _fillBrushSubMenu->addAction(_horizontalStyleBrushAct);
 _fillBrushSubMenu->addAction(_verticalStyleBrushAct);
 _fillBrushSubMenu->addAction(_crossStyleBrushAct);
 _fillBrushSubMenu->addAction(_backwarddiagonalStyleBrushAct);
 _fillBrushSubMenu->addAction(_forwarddiagonalStyleBrushAct);
 _fillBrushSubMenu->addAction(_diagonalcrossStyleBrushAct);
 _fillBrushSubMenu->addAction(_dense1StyleBrushAct);
 _fillBrushSubMenu->addAction(_dense2StyleBrushAct);
 _fillBrushSubMenu->addAction(_dense3StyleBrushAct);
 _fillBrushSubMenu->addAction(_dense4StyleBrushAct);
 _fillBrushSubMenu->addAction(_dense5StyleBrushAct);
 _fillBrushSubMenu->addAction(_dense6StyleBrushAct);
 _fillBrushSubMenu->addAction(_dense7StyleBrushAct);
 _fillBrushSubMenu->addAction(_noneStyleBrushAct);

 _styleBrushToolBar->addAction(_lineargradientStyleBrushAct);
 _styleBrushToolBar->addAction(_radialgradientStyleBrushAct);
 _styleBrushToolBar->addAction(_conicalgradientStyleBrushAct);
 _styleBrushToolBar->addAction(_textureStyleBrushAct);
 _styleBrushToolBar->addAction(_solidStyleBrushAct);
 _styleBrushToolBar->addAction(_horizontalStyleBrushAct);
 _styleBrushToolBar->addAction(_verticalStyleBrushAct);
 _styleBrushToolBar->addAction(_crossStyleBrushAct);
 _styleBrushToolBar->addAction(_backwarddiagonalStyleBrushAct);
 _styleBrushToolBar->addAction(_forwarddiagonalStyleBrushAct);
 _styleBrushToolBar->addAction(_diagonalcrossStyleBrushAct);
 _styleBrushToolBar->addAction(_dense1StyleBrushAct);
 _styleBrushToolBar->addAction(_dense2StyleBrushAct);
 _styleBrushToolBar->addAction(_dense3StyleBrushAct);
 _styleBrushToolBar->addAction(_dense4StyleBrushAct);
 _styleBrushToolBar->addAction(_dense5StyleBrushAct);
 _styleBrushToolBar->addAction(_dense6StyleBrushAct);
 _styleBrushToolBar->addAction(_dense7StyleBrushAct);
 _styleBrushToolBar->addAction(_noneStyleBrushAct);

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

 /* SET QActionsGROUP */
 _toolsQag->addAction(_freehandAct);
 _toolsQag->addAction(_lineAct);
 _toolsQag->addAction(_rectAct);
 _toolsQag->addAction(_elipsisAct);
 _toolsQag->addAction(_polyAct);
 _toolsQag->addAction(_textAct);

 _stylePenQag->addAction(_solidStylePenAct);
 _stylePenQag->addAction(_dashStylePenAct);
 _stylePenQag->addAction(_dotStylePenAct);
 _stylePenQag->addAction(_dashdotStylePenAct);
 _stylePenQag->addAction(_dashdotnotStylePenAct);
 _stylePenQag->addAction(_noneStylePenAct);

 _capPenQag->addAction(_flatCapPenAct);
 _capPenQag->addAction(_squareCapPenAct);
 _capPenQag->addAction(_roundCapPenAct);

 _joinPenQag->addAction(_miterJoinPenAct);
 _joinPenQag->addAction(_bevelJoinPenAct);
 _joinPenQag->addAction(_roundJoinPenAct);

 _widthPenQag->addAction(_widthMinAct);
 _widthPenQag->addAction(_widthSel1Act);
 _widthPenQag->addAction(_widthSel2Act);
 _widthPenQag->addAction(_widthSel3Act);
 _widthPenQag->addAction(_widthMaxAct);

 _styleBrushQag->addAction(_lineargradientStyleBrushAct);
 _styleBrushQag->addAction(_radialgradientStyleBrushAct);
 _styleBrushQag->addAction(_conicalgradientStyleBrushAct);
 _styleBrushQag->addAction(_textureStyleBrushAct);
 _styleBrushQag->addAction(_solidStyleBrushAct);
 _styleBrushQag->addAction(_horizontalStyleBrushAct);
 _styleBrushQag->addAction(_verticalStyleBrushAct);
 _styleBrushQag->addAction(_crossStyleBrushAct);
 _styleBrushQag->addAction(_backwarddiagonalStyleBrushAct);
 _styleBrushQag->addAction(_forwarddiagonalStyleBrushAct);
 _styleBrushQag->addAction(_diagonalcrossStyleBrushAct);
 _styleBrushQag->addAction(_dense1StyleBrushAct);
 _styleBrushQag->addAction(_dense2StyleBrushAct);
 _styleBrushQag->addAction(_dense3StyleBrushAct);
 _styleBrushQag->addAction(_dense4StyleBrushAct);
 _styleBrushQag->addAction(_dense5StyleBrushAct);
 _styleBrushQag->addAction(_dense6StyleBrushAct);
 _styleBrushQag->addAction(_dense7StyleBrushAct);
 _styleBrushQag->addAction(_noneStyleBrushAct);

}

//--------------------------------------------------------------------------------
void PaintWindow::_connectSignals(void) {

 connect(_newAct, SIGNAL(triggered()), this,SLOT(_newFile( )) );
 connect(_exitAct,SIGNAL(activated()), this, SLOT(quit()));
 connect(_saveAct, SIGNAL(triggered()), this, SLOT(_save()));
 connect(_saveAsAct, SIGNAL(triggered()), this, SLOT(_saveAs()));
 connect(_openAct, SIGNAL(triggered()), this, SLOT(_open()));

 /*----CONNECT MAPPERS------*/
 //select form
 connect(_freehandAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_lineAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_rectAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_elipsisAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_polyAct,SIGNAL(activated()),_signalMapper, SLOT(map()));
 connect(_textAct,SIGNAL(activated()),_signalMapper, SLOT(map()));

 connect(_signalMapper,SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
 connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)));

 //stylePen
 connect(_solidStylePenAct,SIGNAL(activated()),_signalMapperStylePen, SLOT(map()));
 connect(_dashStylePenAct,SIGNAL(activated()),_signalMapperStylePen, SLOT(map()));
 connect(_dotStylePenAct,SIGNAL(activated()),_signalMapperStylePen, SLOT(map()));
 connect(_dashdotStylePenAct,SIGNAL(activated()),_signalMapperStylePen, SLOT(map()));
 connect(_dashdotnotStylePenAct,SIGNAL(activated()),_signalMapperStylePen, SLOT(map()));
 connect(_noneStylePenAct,SIGNAL(activated()),_signalMapperStylePen, SLOT(map()));

 connect(_signalMapperStylePen,SIGNAL(mapped(int)), this, SIGNAL(stylePenMapped(int)));
 connect(this, SIGNAL(stylePenMapped(int)), _area, SLOT(setCurrentStylePen(int)));

 //capPen
 connect(_flatCapPenAct,SIGNAL(activated()),_signalMapperCapPen, SLOT(map()));
 connect(_squareCapPenAct,SIGNAL(activated()),_signalMapperCapPen, SLOT(map()));
 connect(_roundCapPenAct,SIGNAL(activated()),_signalMapperCapPen, SLOT(map()));

 connect(_signalMapperCapPen,SIGNAL(mapped(int)), this, SIGNAL(capPenMapped(int)));
 connect(this, SIGNAL(capPenMapped(int)), _area, SLOT(setCurrentCapPen(int)));

 //JoinPen
 connect(_miterJoinPenAct,SIGNAL(activated()),_signalMapperJoinPen, SLOT(map()));
 connect(_bevelJoinPenAct,SIGNAL(activated()),_signalMapperJoinPen, SLOT(map()));
 connect(_roundJoinPenAct,SIGNAL(activated()),_signalMapperJoinPen, SLOT(map()));

 connect(_signalMapperJoinPen,SIGNAL(mapped(int)), this, SIGNAL(joinPenMapped(int)));
 connect(this, SIGNAL(joinPenMapped(int)), _area, SLOT(setCurrentJoinPen(int)));

 //WidthPen
 connect(_widthMinAct,SIGNAL(activated()),_signalMapperWidthPen, SLOT(map()));
 connect(_widthSel1Act,SIGNAL(activated()),_signalMapperWidthPen, SLOT(map()));
 connect(_widthSel2Act,SIGNAL(activated()),_signalMapperWidthPen, SLOT(map()));
 connect(_widthSel3Act,SIGNAL(activated()),_signalMapperWidthPen, SLOT(map()));
 connect(_widthMaxAct,SIGNAL(activated()),_signalMapperWidthPen, SLOT(map()));

 connect(_signalMapperWidthPen,SIGNAL(mapped(int)), this, SIGNAL(widthPenMapped(int)));
 connect(this, SIGNAL(widthPenMapped(int)), _area, SLOT(setCurrentWidthPen(int)));

 //brushStyle
 connect(_lineargradientStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_radialgradientStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_conicalgradientStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_textureStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_solidStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_horizontalStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_verticalStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_crossStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_backwarddiagonalStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_forwarddiagonalStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_diagonalcrossStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_dense1StyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_dense2StyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_dense3StyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_dense4StyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_dense5StyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_dense6StyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_dense7StyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));
 connect(_noneStyleBrushAct,SIGNAL(activated()),_signalMapperStyleBrush, SLOT(map()));

 connect(_signalMapperStyleBrush,SIGNAL(mapped(int)), this, SIGNAL(styleBrushMapped(int)));
 connect(this, SIGNAL(styleBrushMapped(int)), _area, SLOT(setCurrentStyleBrush(int)));

 /* ------ */

 connect(_colorPenAct,SIGNAL(triggered()),this, SLOT(_changePenColor()));
 connect(_colorBrushAct,SIGNAL(triggered()),this, SLOT(_changeBrushColor()));

 connect(_aboutAct, SIGNAL(triggered()),this, SLOT(_about()));
 connect(_aboutQtAct,SIGNAL(triggered()),this, SLOT(_aboutQt()));

 connect(_undoAction, SIGNAL(triggered()), this, SLOT(_undo()));
 connect(_clearAction, SIGNAL(triggered()), this, SLOT(_clear()));

 //pop-up
 connect(_area,SIGNAL(popUpAsked(QPoint)), this, SLOT(showPopUp(QPoint)));
}

void PaintWindow::_createAndSetMappers(void)
{
    _signalMapper = new QSignalMapper(this);
    _signalMapper->setMapping(_freehandAct, TOOLS_ID_FREEHAND);
    _signalMapper->setMapping(_lineAct, TOOLS_ID_LINE);
    _signalMapper->setMapping(_rectAct, TOOLS_ID_RECTANGLE);
    _signalMapper->setMapping(_elipsisAct, TOOLS_ID_CIRCLE);
    _signalMapper->setMapping(_polyAct, TOOLS_ID_POLYGON);
    _signalMapper->setMapping(_textAct, TOOLS_ID_TEXT);

    _signalMapperStylePen = new QSignalMapper(this);
    _signalMapperStylePen->setMapping(_solidStylePenAct, STYLE_PEN_ID_SOLID);
    _signalMapperStylePen->setMapping(_dashStylePenAct, STYLE_PEN_ID_DASH);
    _signalMapperStylePen->setMapping(_dotStylePenAct, STYLE_PEN_ID_DOT);
    _signalMapperStylePen->setMapping(_dashdotStylePenAct, STYLE_PEN_ID_DASHDOT);
    _signalMapperStylePen->setMapping(_dashdotnotStylePenAct, STYLE_PEN_ID_DASHDOTNOT);
    _signalMapperStylePen->setMapping(_noneStylePenAct, STYLE_PEN_ID_NONE),

    _signalMapperCapPen = new QSignalMapper(this);
    _signalMapperCapPen->setMapping(_flatCapPenAct, CAP_PEN_ID_FLAT);
    _signalMapperCapPen->setMapping(_squareCapPenAct, CAP_PEN_ID_SQUARE);
    _signalMapperCapPen->setMapping(_roundCapPenAct, CAP_PEN_ID_ROUND);

    _signalMapperJoinPen = new QSignalMapper(this);
    _signalMapperJoinPen->setMapping(_miterJoinPenAct, JOIN_PEN_ID_MITER);
    _signalMapperJoinPen->setMapping(_bevelJoinPenAct, JOIN_PEN_ID_BEVEL);
    _signalMapperJoinPen->setMapping(_roundJoinPenAct, JOIN_PEN_ID_ROUND);

    _signalMapperWidthPen = new QSignalMapper(this);
    _signalMapperWidthPen->setMapping(_widthMinAct, WIDTH_PEN_ID_MIN);
    _signalMapperWidthPen->setMapping(_widthSel1Act, WIDTH_PEN_ID_SEL1);
    _signalMapperWidthPen->setMapping(_widthSel2Act, WIDTH_PEN_ID_SEL2);
    _signalMapperWidthPen->setMapping(_widthSel3Act, WIDTH_PEN_ID_SEL3);
    _signalMapperWidthPen->setMapping(_widthMaxAct, WIDTH_PEN_ID_MAX);

    _signalMapperStyleBrush = new QSignalMapper(this);
    _signalMapperStyleBrush->setMapping(_lineargradientStyleBrushAct, STYLE_BRUSH_ID_LINEARGRADIENT);
    _signalMapperStyleBrush->setMapping(_radialgradientStyleBrushAct, STYLE_BRUSH_ID_RADIALGRADIENT);
    _signalMapperStyleBrush->setMapping(_conicalgradientStyleBrushAct, STYLE_BRUSH_ID_CONICALGRADIENT);
    _signalMapperStyleBrush->setMapping(_textureStyleBrushAct, STYLE_BRUSH_ID_TEXTURE);
    _signalMapperStyleBrush->setMapping(_solidStyleBrushAct, STYLE_BRUSH_ID_SOLID);
    _signalMapperStyleBrush->setMapping(_horizontalStyleBrushAct, STYLE_BRUSH_ID_HORIZONTAL);
    _signalMapperStyleBrush->setMapping(_verticalStyleBrushAct, STYLE_BRUSH_ID_VERTICAL);
    _signalMapperStyleBrush->setMapping(_crossStyleBrushAct, STYLE_BRUSH_ID_CROSS);
    _signalMapperStyleBrush->setMapping(_backwarddiagonalStyleBrushAct, STYLE_BRUSH_ID_BACKWARDDIAGONAL);
    _signalMapperStyleBrush->setMapping(_forwarddiagonalStyleBrushAct, STYLE_BRUSH_ID_FORWARDDIAGONAL);
    _signalMapperStyleBrush->setMapping(_diagonalcrossStyleBrushAct, STYLE_BRUSH_ID_DIAGONALCROSS);
    _signalMapperStyleBrush->setMapping(_dense1StyleBrushAct, STYLE_BRUSH_ID_DENSE1);
    _signalMapperStyleBrush->setMapping(_dense2StyleBrushAct, STYLE_BRUSH_ID_DENSE2);
    _signalMapperStyleBrush->setMapping(_dense3StyleBrushAct, STYLE_BRUSH_ID_DENSE3);
    _signalMapperStyleBrush->setMapping(_dense4StyleBrushAct, STYLE_BRUSH_ID_DENSE4);
    _signalMapperStyleBrush->setMapping(_dense5StyleBrushAct, STYLE_BRUSH_ID_DENSE5);
    _signalMapperStyleBrush->setMapping(_dense6StyleBrushAct, STYLE_BRUSH_ID_DENSE6);
    _signalMapperStyleBrush->setMapping(_dense7StyleBrushAct, STYLE_BRUSH_ID_DENSE7);
    _signalMapperStyleBrush->setMapping(_noneStyleBrushAct, STYLE_BRUSH_ID_NONE);

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
