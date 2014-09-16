#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include <QLCDNumber>
#include <QSlider>
class MyWidget : public QWidget
{
   Q_OBJECT
   public:
        MyWidget( QWidget *parent = 0 );
   private :
        QLCDNumber *_pLcd;
        QSlider *_pSlider;
};
#endif

