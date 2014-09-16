#include <QApplication>
#include <QWidget>
#include "myPainter.h"

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
//   QWidget box;
//   box.resize(200, 120);
   MyPainter dessin;
   dessin.resize(300, 50);
   dessin.move(10, 30);
   dessin.show();
//   box.show();
   return app.exec();
}

