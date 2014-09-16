#include <QDebug>
#include "rubberband.h"

MyPainter::MyPainter(void) {
// _buffer = new QPixmap(this->size());
 _buffer.fill(Qt::white);
// _rubberBand = NULL;
}

MyPainter::~MyPainter(void) {
// delete _buffer;
}

void MyPainter::mousePressEvent(QMouseEvent *event) {
  qDebug() << "MyPainter::mousePressEvent(QMouseEvent *event)";
  _startPoint = _endPoint = event->pos();
/*
  if (_rubberBand == NULL) {
   	qDebug() << "if (! _rubberBand)";
        _rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
  }
*/
  _mouse = 0;
  _rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
  _rubberBand->setGeometry(QRect(_startPoint, QSize()));
  _rubberBand->show();
 }

void MyPainter::mouseMoveEvent(QMouseEvent *event) {
 qDebug() << "MyPainter::mouseMoveEvent(QMouseEvent *event)";
 _mouse = 1;
 _rubberBand->setGeometry(QRect(_startPoint, event->pos()).normalized());
}

void MyPainter::mouseReleaseEvent(QMouseEvent *event) {
 _rubberBand->hide();
 _endPoint = event->pos();
 _mouse = 2;
 update();
}

void MyPainter::paintEvent(QPaintEvent* evt) {
 QPainter paintWindow(this);
 QPainter paintBuffer(&_buffer);
 if (_mouse==0)  {
//   paintWindow.drawPixmap(0,0, *_buffer);
}
/*
 QPainter::CompositionMode mode = paintBuffer.compositionMode();
 paintBuffer.setRenderHint(QPainter::Antialiasing);
 cerr << "renderHint" << paintBuffer.testRenderHint(QPainter::Antialiasing);
*/
 if (_mouse==1)  {
  /*
  cerr << paintWindow.compositionMode();
  paintWindow.setCompositionMode(QPainter::CompositionMode_Xor);
  vide :
  ------ 
  RasterOp_NotSource
  RasterOp_SourceOrDestination
  RasterOp_NotSourceAndDestination,RasterOp_NotSourceOrNotDestination
  RasterOp_SourceXorDestination
  trainee :
  ---------
  RasterOp_SourceAndDestination, 
  RasterOp_SourceAndNotDestination, RasterOp_NotSourceAndNotDestination
  RasterOp_NotSourceXorDestination, RasterOp_NotSourceXorDestination
  paintBuffer.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
  paintBuffer.drawLine(_startPoint,_endPoint);
  paintWindow.drawLine(_startPoint,_endPoint);
  */
 }
 if (_mouse==2) {
//  paintBuffer.setCompositionMode(paintWindow.compositionMode());
   paintWindow.drawPixmap(0,0, _buffer);
   paintWindow.drawLine(_startPoint,_endPoint);
   paintBuffer.drawLine(_startPoint,_endPoint);
 }
 paintBuffer.end();
 paintWindow.end();
}

