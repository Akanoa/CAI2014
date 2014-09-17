/****************************************************************************
** Meta object code from reading C++ file 'paintArea.h'
**
** Created: Wed 17. Sep 19:33:47 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Guern-Teneau_Qt_B009/Include/paintArea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paintArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PaintArea[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      31,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PaintArea[] = {
    "PaintArea\0\0setCurrentTool(int)\0"
    "setCurrentColor(QColor)\0"
};

const QMetaObject PaintArea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PaintArea,
      qt_meta_data_PaintArea, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PaintArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PaintArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PaintArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PaintArea))
        return static_cast<void*>(const_cast< PaintArea*>(this));
    return QWidget::qt_metacast(_clname);
}

int PaintArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setCurrentTool((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setCurrentColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
