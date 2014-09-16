#include <QApplication>
#include <QApplication> 
#include <QWidget>
#include <QLabel>
#include <QFont>

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   QWidget box;
   box.resize(200, 120);
   QLabel hello("Hello Statique !", &box);
   hello.resize(300, 50);
   hello.move(10, 30);
   hello.setFont( QFont("Times", 18, QFont::Bold) );
   box.show();
   return app.exec();
}

