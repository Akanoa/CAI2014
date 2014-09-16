#include <QDebug>
#include "sigslot.h"

int main(int argc, char* argv[]) {
SigSlot a, b;

QObject::connect(&a, SIGNAL(valueChanged(int)), &b, SLOT(setValue(int)));
b.setValue( 10 );
qDebug() << a.value(); // 0 or 10 ?
a.setValue( 100 );
qDebug() << b.value(); // 10 or 100 ?
}

