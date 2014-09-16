#include <QApplication>
#include <QApplication> 
#include <QWidget>
#include <QPushButton>
#include <QFont>

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   QWidget box;
   box.resize(200, 120);
   QPushButton quitBtn("Quit", &box);
   quitBtn.resize(100, 50);
   quitBtn.move(50, 30);
   quitBtn.setFont( QFont("Times", 18, QFont::Bold) );
   QObject::connect( &quitBtn, SIGNAL(clicked( )), &app, SLOT(quit( )) );
   box.show();
   return app.exec();
}

