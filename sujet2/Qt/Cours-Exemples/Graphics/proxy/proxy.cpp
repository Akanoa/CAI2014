#include <QApplication>
// #include <QtGUI>
#include <QPushButton>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   
   QGraphicsScene scene;
 
// Items
    QGraphicsRectItem *rect = scene.addRect(QRectF(0, 0, 100, 100));
// Widget + proxyproxy->setPos(150, 200);
    QPushButton *bouton = new QPushButton("Un bouton dans la scene");
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    proxy->setWidget(bouton);
    scene.addItem(proxy);
// transformations apres addItem()
    scene.setSceneRect(-150, -150, 300, 300);
    proxy->setPos(-100, -100);
    proxy->setScale(2);
//    proxy->setRotation(45);

    QGraphicsView view(&scene);
    view.show();
   
   return app.exec();
}
