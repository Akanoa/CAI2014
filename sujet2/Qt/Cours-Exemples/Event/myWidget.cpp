#include <QDebug>
#include <QEvent>
#include <QPainter>
#include "myWidget.h"

void MyWidget::mousePressEvent(QMouseEvent* e) {
 if (e->button() == Qt::LeftButton) {
   // TO DO
   update();
 }
}

void MyWidget::paintEvent(QPaintEvent* e) {
 qDebug() << "MyWidget::paintEvent()";
 QWidget::paintEvent(e);
 QPainter painter(this);
 painter.drawLine(50, 10, 100, 20);
}

