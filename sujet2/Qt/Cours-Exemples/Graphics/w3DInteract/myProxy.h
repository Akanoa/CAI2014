#include <QGraphicsProxyWidget>
#include <QPointF>

class MyProxy : public QGraphicsProxyWidget
{
public:
    MyProxy();

    qreal rotY();
    void setRotY(qreal rotation);

    QPointF center();

private:
    qreal _rotY; // enregistre la rotation autour de l'axe Y
    QPointF _center; // contient la position du centre du widget
};

