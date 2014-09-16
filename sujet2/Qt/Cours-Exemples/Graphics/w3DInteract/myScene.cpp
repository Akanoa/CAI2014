#include <QPushButton>
#include <QtWebKit/QWebView>
#include "myScene.h"

MyScene::MyScene() : QGraphicsScene()
{
    this->setSceneRect(0,0,1000,800);
//    this->setSceneRect(-150, -150, 300, 300);
    QWebView *web = new QWebView();
    web->load(QUrl("http://www.developpez.com"));
    _proxy = new MyProxy();
    _proxy->setWidget(web);
    this->addItem(_proxy);
        QTransform matrix;
        _proxy->setRotY(45);
        matrix.rotate(_proxy->rotY(), Qt::ZAxis);
        matrix.translate(-_proxy->widget()->width()/2, - _proxy->widget()->height()/2);
        _proxy->setTransform(matrix);
}

void
MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent*e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        QPointF delta(e->scenePos() - e->lastScenePos());
        qreal rotation = delta.x();
        _proxy->setRotY(rotation + _proxy->rotY());
		
    }
       QTransform matrix;
        matrix.rotate(_proxy->rotY(), Qt::ZAxis);
        matrix.translate(-_proxy->widget()->width()/2, - _proxy->widget()->height()/2);
        _proxy->setTransform(matrix);
}

