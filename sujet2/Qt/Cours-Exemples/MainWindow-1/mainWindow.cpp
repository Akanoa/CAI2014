#include <QtDebug>
#include "mainWindow.h"

MainWindow::MainWindow(void) {
 _createActions();
 _createMenus();
 _createToolbars();
 _connectActions();
 _connectSignals(); 

 QDockWidget *dockWidget = new QDockWidget(tr("Dock Widget"), this);
 dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                 Qt::RightDockWidgetArea);
// dockWidget->setWidget(dockWidgetContents);
 addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
 QTextEdit* text = new QTextEdit(this);
 setCentralWidget( text );
}

void MainWindow::_createMenus(void) {
 QMenuBar* menubar = menuBar( );         // QMainWindow method
 _fileMenu = menubar->addMenu( tr("&File") );
 _alignMenu = menubar->addMenu( tr("&Alignement") );
 _helpMenu = menubar->addMenu( tr("&Help") );
}

void MainWindow::_createToolbars(void) {
  _toolBar = addToolBar( tr("File") );
}

void MainWindow::_createActions(void) {
 _newAction = new QAction( QIcon(":/images/new.png"), tr("&New..."), this );
 _newAction->setShortcut( tr("Ctrl+N") );
 _newAction->setToolTip( tr("New file") );
 _newAction->setStatusTip( tr("New file") );

 _newAction->setData(QVariant("new Action data to process"));

 _leftAlignAction = new QAction(tr("&Left Align"), this);
 _leftAlignAction->setCheckable(true);
 _leftAlignAction->setShortcut(tr("Ctrl+L"));
 _leftAlignAction->setStatusTip(tr("Left align the selected text"));
 _rightAlignAction = new QAction(tr("&Right Align"), this);
 _rightAlignAction->setCheckable(true);
 _rightAlignAction->setShortcut(tr("Ctrl+R"));
 _rightAlignAction->setStatusTip(tr("Right align the selected text"));

 _justifyAction = new QAction(tr("&Justify"), this);
 _justifyAction->setCheckable(true);
 _justifyAction->setShortcut(tr("Ctrl+J"));
 _justifyAction->setStatusTip(tr("Justify the selected text"));

 _centerAction = new QAction(tr("&Center"), this);
 _centerAction->setCheckable(true);
 _centerAction->setShortcut(tr("Ctrl+E"));
 _centerAction->setStatusTip(tr("Center the selected text"));

 _alignGA = new QActionGroup(this);
 _alignGA->addAction(_leftAlignAction);
 _alignGA->addAction(_rightAlignAction);
 _alignGA->addAction(_justifyAction);
 _alignGA->addAction(_centerAction);
 _leftAlignAction->setChecked(true);

 _aboutAction = new QAction(tr("&About"), this);
 _aboutAction->setShortcut(tr("Ctrl+H"));
 _aboutAction->setStatusTip(tr("I' need somebody"));
 _aboutQtAction = new QAction(tr("&About Qt"), this);
 _aboutQtAction->setStatusTip(tr("Thank's a lot, you're so cute !"));
}
void MainWindow::_connectActions(void) {
 _fileMenu->addAction( _newAction );
 _alignMenu->addAction(_leftAlignAction);
 _alignMenu->addAction(_rightAlignAction);
 _alignMenu->addAction(_justifyAction);
 _alignMenu->addAction(_centerAction);
 _toolBar->addAction(_newAction);
 _helpMenu->addAction(_aboutAction);
 _helpMenu->addAction(_aboutQtAction);
}

void MainWindow::_connectSignals(void) {
 connect( _newAction, SIGNAL(triggered( )), this, SLOT(_newFile( )) );
 connect(_leftAlignAction, SIGNAL(triggered()), this, SLOT(_leftAlign()));
 connect(_rightAlignAction, SIGNAL(triggered()), this, SLOT(_rightAlign()));
 connect(_justifyAction, SIGNAL(triggered()), this, SLOT(_justify()));
 connect(_centerAction, SIGNAL(triggered()), this, SLOT(_center()));
 connect(_aboutAction, SIGNAL(triggered()), this, SLOT(_about()));
 connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(_aboutQt()));
}

void MainWindow::_newFile(void) {
 qDebug() << "Date: " << QDate::currentDate();
 qDebug() << "MainWindow::newFile(void)";
 QString str = _newAction->data().toString();
 qDebug() << str ;
}

void MainWindow::_exit(void) {
qDebug()<< "MainWindow::_exit(void)" ;
}
void MainWindow::_leftAlign() {
 qDebug()<< "MainWindow::_leftAlign()" ;
 
}
void MainWindow::_rightAlign() {
 qDebug()<< "MainWindow::_rightAlign() " ;
 
}
void MainWindow::_justify() {
 qDebug()<< "MainWindow::_justify()" ;
 
}
void MainWindow::_center() {
 qDebug()<< "MainWindow::_center()" ;
 
}
void MainWindow::_about() {
 qDebug()<< "MainWindow::_aboutUs()" ;
 QMessageBox::information( this,
                           "Editeur graphique Version 0.1",
                           "ENIB module CIA, Copyright 2012 : \n Albert Dupond- Alfred Dupont",
                           "Go back to work !");
}
void MainWindow::_aboutQt() {
 qDebug()<< "MainWindow::_aboutQt()" ;
 QMessageBox::aboutQt( this, "A propos de Qt");
 
}


