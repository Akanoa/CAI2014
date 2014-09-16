#include <iostream>
#include <QApplication>
// #include <QtGUI>
#include <QPushButton>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>

using namespace std;

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   
   QGraphicsScene scene;
 
// Items
    QGraphicsRectItem *rect = scene.addRect(QRectF(0, 0, 100, 100));
// Widget + proxy
    QPushButton *bouton = new QPushButton("Un bouton");
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    proxy->setWidget(bouton);
    scene.addItem(proxy);
//    scene.setSceneRect(-150, -150, 300, 300);

// Matrice de transformation

    QTransform matrix;
    matrix.rotate(45);
    matrix.translate(100, 100);
//    matrix.scale(1,2);
    proxy->setTransform(matrix);

/*
   cerr << "proxy->x() : " << proxy->x()  << endl;
   cerr << "proxy->y() : " << proxy->y()  << endl;
   proxy->setTransform(matrix);
*/
    QGraphicsView view(&scene);
    view.show();
   
   return app.exec();
}
