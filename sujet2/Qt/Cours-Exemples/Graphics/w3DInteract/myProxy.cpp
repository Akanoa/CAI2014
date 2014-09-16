#include "myProxy.h"

MyProxy::MyProxy()
{
  _rotY = 0.0;
  _center = QPointF(0,0);
}

qreal
MyProxy::rotY()
{
  return _rotY;
}

void
MyProxy::setRotY(qreal rotation)
{
  _rotY = rotation;
}

QPointF
MyProxy::center()
{
  return _center;
}

