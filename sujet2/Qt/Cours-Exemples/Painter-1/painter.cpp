#include <QDebug>
#include "painter.h"

MyPainter::MyPainter(void) {
 _buffer = new QPixmap(this->size());
 _buffer->fill(Qt::white);
// _rubberBand = NULL;
_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
}

MyPainter::~MyPainter(void) {
 delete _buffer;
 delete _rubberBand;
}

void MyPainter::mousePressEvent(QMouseEvent *event) {
  qDebug() << "MyPainter::mousePressEvent(QMouseEvent *event)";
  _startPoint = _endPoint = event->pos();
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
 QPainter paintBuffer(_buffer);

 QPen pen;
 pen.setStyle(Qt::DashDotLine);
 pen.setWidth(3);
// pen.setBrush(Qt::green);
 paintBuffer.setPen(pen);
 QBrush brush(Qt::DiagCrossPattern);
// paintBuffer.setBackground(QBrush(Qt::cyan));
 paintWindow.setBrush(brush);
 paintBuffer.setBrush(brush);

/*
QRegion r1(QRect(100, 100, 200, 80), QRegion::Ellipse);
QRegion r2(QRect(100, 120, 90, 30));
QRegion r3 = r1.intersected(r2);
paintWindow.setClipRegion(r3);
*/
  
/*
 paintBuffer.save();
 paintBuffer.translate(100,100);
 paintBuffer.rotate (45);
 paintBuffer.drawText(0, 0, "DU TEXTE EN DIAGONALE...");
 paintBuffer.restore();
 paintBuffer.drawLine(10,10,100,100); 
*/

 QTransform transform;
 transform.translate(50, 50);
 transform.rotate(45);
 transform.scale(0.5, 1.0);
 paintWindow.setTransform(transform);
 paintWindow.setFont(QFont("Helvetica", 24));
 paintWindow.setPen(QPen(Qt::black, 1));
 paintWindow.drawText(20, 10, "Transformation"); 
 paintWindow.drawPixmap(0,0, *_buffer);
 paintWindow.drawLine(_startPoint,_endPoint);
 paintBuffer.drawLine(_startPoint,_endPoint);

 paintWindow.drawEllipse(QRectF(_startPoint,_endPoint));
 paintBuffer.end();
 paintWindow.end();
}

