#include <iostream>
using namespace std;
#include "myPainter.h"

MyPainter::MyPainter(void) {
 _buffer = new QPixmap(this->size());
 _buffer->fill(Qt::white);
}

MyPainter::~MyPainter(void) {
}

/*
void MyPainter::drawing(QPaintDevice* fenetre) {
 QPainter paintWindow(fenetre);
 paintWindow.drawLine(_startPoint,_endPoint);
}
*/

void MyPainter::mousePressEvent(QMouseEvent* evt) {
 cerr << "MyPainter::mousePressEvent()"<< endl;
 _mouse=0;
 if (evt->button() == Qt::LeftButton) {
   cerr << "evt->pos() :" << evt->pos().x() << "," << evt->pos().y()  << endl;
   _startPoint = evt->pos();
   _endPoint = evt->pos();
 }
}
void MyPainter::mouseMoveEvent(QMouseEvent* evt) {
 _mouse=1;
// update();
 _endPoint = evt->pos();
 update();

}

void MyPainter::mouseReleaseEvent(QMouseEvent* evt) {
 if (evt->button() == Qt::LeftButton) {
   _mouse=2;
   update();
 }
}

void MyPainter::paintEvent(QPaintEvent* evt) {
 QPainter paintWindow(this);
 QPainter paintBuffer(_buffer);
// paintWindow.drawPixmap(0,0, *_buffer);
 if (_mouse==0)  {
//   paintWindow.drawPixmap(0,0, *_buffer);
}
// QPainter::CompositionMode mode = paintBuffer.compositionMode();
// paintBuffer.setRenderHint(QPainter::Antialiasing);
// cerr << "renderHint" << paintBuffer.testRenderHint(QPainter::Antialiasing);
 if (_mouse==1)  {
 //  cerr << paintWindow.compositionMode();
 //  paintWindow.setCompositionMode(QPainter::CompositionMode_Xor);
// vide : 
// RasterOp_NotSource
// RasterOp_SourceOrDestination
// RasterOp_NotSourceAndDestination,RasterOp_NotSourceOrNotDestination
// RasterOp_SourceXorDestination
// trainee : 
// RasterOp_SourceAndDestination, 
// RasterOp_SourceAndNotDestination, RasterOp_NotSourceAndNotDestinationRasterOp_NotSourceXorDestination
// RasterOp_NotSourceXorDestination
  paintBuffer.setCompositionMode(QPainter::RasterOp_NotSourceXorDestination);
  paintBuffer.drawLine(_startPoint,_endPoint);
  paintWindow.drawLine(_startPoint,_endPoint);
 }
 if (_mouse==2) {
//  paintBuffer.setCompositionMode(paintWindow.compositionMode());
   paintWindow.drawPixmap(0,0, *_buffer);
 }
 paintBuffer.end();
 paintWindow.end();
}

