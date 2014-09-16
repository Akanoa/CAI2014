#include <QVBoxLayout>
#include "myWidget.h"

MyWidget::MyWidget( QWidget *parent ) : QWidget( parent )
{
   _pLcd = new QLCDNumber( this );
   _pSlider = new QSlider( Qt::Horizontal, this );  
   QVBoxLayout *mainLayout = new QVBoxLayout; 
   mainLayout->addWidget(_pLcd); 
   mainLayout->addWidget(_pSlider); 
   setLayout(mainLayout);
   connect(_pSlider, SIGNAL(valueChanged(int)), _pLcd, SLOT(display(int)) );
}

