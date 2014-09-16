#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "myProxy.h"

class MyScene : public QGraphicsScene
{
public:
    MyScene();
    void mouseMoveEvent(QGraphicsSceneMouseEvent*e);

private:
    MyProxy *_proxy;
};

