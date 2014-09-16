#include <QApplication>
#include <QWidget>
#include "myDialog.h"

int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    QWidget *w = new QWidget();
    MyDialog dlg(w);
    dlg.show();
    w->show();
    return a.exec();
}

