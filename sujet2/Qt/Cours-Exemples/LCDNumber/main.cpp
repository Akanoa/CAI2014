#include <QApplication>
#include <QSlider>
#include <QLCDNumber>

int main( int argc, char **argv ) {
    QApplication app( argc, argv );
    QWidget mw;
    mw.setGeometry(10, 10, 200, 100);
    QSlider numSlider(Qt::Horizontal, &mw);
    numSlider.setGeometry(10, 10, 150, 30);
    numSlider.setValue(50);
    numSlider.setMinimum(0);
    numSlider.setMaximum(10.0);
    QLCDNumber numLCD( 2, &mw );
    numLCD.setGeometry(60, 50, 50, 50);
    numLCD.display(50);
    QObject::connect( &numSlider, SIGNAL(sliderMoved(int)), 
                      &numLCD, SLOT(display(int)) );
     mw.show();
    return app.exec( );

}
