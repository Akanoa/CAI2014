#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

int main(int argc, char **argv)
{
   QApplication app(argc, argv);
   
   QGraphicsScene scene;
 
   QGraphicsRectItem *rect = scene.addRect(QRectF(0, 0, 100, 100));
   rect->setFlag(QGraphicsItem::ItemIsMovable);
   QGraphicsView view(&scene);

   view.show();
   
   return app.exec();
}
