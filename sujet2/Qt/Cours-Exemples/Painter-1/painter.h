#ifndef MY_PAINTER
#define MY_PAINTER

#include <QEvent>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QRubberBand>

class MyPainter : public QWidget {
public:
 MyPainter(void);
//   MyWidget(QWidget * w) {}
 virtual ~MyPainter(void);

protected:
 void mousePressEvent(QMouseEvent*);
 void mouseMoveEvent(QMouseEvent*);
 void mouseReleaseEvent(QMouseEvent*);
 void drawing(QPaintDevice*);
 void drawingBuffer(QPainter *);
 void paintEvent(QPaintEvent*);
private :
// QPainter *_painter;
 QPoint _startPoint, _endPoint;
 QPixmap *_buffer;
 int _mouse;
 QPainter *_paintBuffer;
 QRubberBand *_rubberBand;
};
#endif
