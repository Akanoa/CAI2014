#include <QDesktopWidget>
#include <QApplication>
#include <QTextCodec>

#include "paintWindow.h"

void center(QWidget &widget)
{
  int x, y;
  int screenWidth;
  int screenHeight;

  int WIDTH = 1000;
  int HEIGHT = 500;

  QDesktopWidget *desktop = QApplication::desktop();

  screenWidth = desktop->width();
  screenHeight = desktop->height();

  x = (screenWidth - WIDTH) / 2;
  y = (screenHeight - HEIGHT) / 2;

  widget.setGeometry(x, y, WIDTH, HEIGHT);
}


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);  
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));


  PaintWindow window;

  window.setWindowTitle("Make your Draw 2014");
  window.show();
  center(window);

  return app.exec();
}

