#include <QApplication>
#include <QWidget>
#include "myWidget.h"

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
//   QWidget box;
//   box.resize(200, 120);
   MyWidget dessin;
   dessin.resize(300, 50);
   dessin.move(10, 30);
   dessin.show();
//   box.show();
   return app.exec();
}

