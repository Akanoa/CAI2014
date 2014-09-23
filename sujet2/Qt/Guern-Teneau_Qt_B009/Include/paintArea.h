#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QColor>

class PaintArea : public QWidget
{
  Q_OBJECT  

  public:
    PaintArea(QWidget *parent = 0);
    QPixmap* getBuffer();
	void setEnterState(bool);
    void setEscapeState(bool);
  public slots:
    void setCurrentTool(int);
    void setCurrentColor(QColor);
    void setFillColor(QColor);
    void setFilled(bool);
  protected :
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent* evt);
    void paintEvent(QPaintEvent*);
  private :
   QPoint  _startPoint,_endPoint;
   QPixmap *_buffer;
   int _currentTool;
   QColor _currentColor, _fillColor;
   bool _release;
   bool _enterState;
   bool _escapeState;
   QPixmap *_bufferForm;
   bool _filled;
};
#endif

