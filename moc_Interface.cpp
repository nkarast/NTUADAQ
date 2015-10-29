/****************************************************************************
** Meta object code from reading C++ file 'Interface.h'
**
** Created: Mon Oct 3 13:18:33 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/Interface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRootCanvas[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QRootCanvas[] = {
    "QRootCanvas\0"
};

const QMetaObject QRootCanvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QRootCanvas,
      qt_meta_data_QRootCanvas, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRootCanvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRootCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRootCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRootCanvas))
        return static_cast<void*>(const_cast< QRootCanvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int QRootCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_Interface[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      36,   30,   10,   10, 0x0a,
      65,   10,   10,   10, 0x0a,
      86,   30,   10,   10, 0x0a,
     113,   10,   10,   10, 0x0a,
     134,   10,   10,   10, 0x0a,
     161,  154,   10,   10, 0x0a,
     186,   10,   10,   10, 0x0a,
     203,   10,   10,   10, 0x0a,
     218,   10,   10,   10, 0x0a,
     234,   10,   10,   10, 0x0a,
     257,   10,   10,   10, 0x0a,
     271,   10,   10,   10, 0x0a,
     282,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Interface[] = {
    "Interface\0\0unlockExpertMode()\0state\0"
    "unlockGateGeneratorConf(int)\0"
    "resetDefaultConfig()\0enableMaxNumberEvents(int)\0"
    "applyConfiguration()\0loadConfiguration()\0"
    "newVal\0changeNumberOfCrams(int)\0"
    "startDAQThread()\0stopDAQCycle()\0"
    "initializeDAQ()\0cancelInitialization()\0"
    "setupCanvas()\0clicked1()\0handle_root_events()\0"
};

const QMetaObject Interface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Interface,
      qt_meta_data_Interface, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Interface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Interface))
        return static_cast<void*>(const_cast< Interface*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: unlockExpertMode(); break;
        case 1: unlockGateGeneratorConf((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: resetDefaultConfig(); break;
        case 3: enableMaxNumberEvents((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: applyConfiguration(); break;
        case 5: loadConfiguration(); break;
        case 6: changeNumberOfCrams((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: startDAQThread(); break;
        case 8: stopDAQCycle(); break;
        case 9: initializeDAQ(); break;
        case 10: cancelInitialization(); break;
        case 11: setupCanvas(); break;
        case 12: clicked1(); break;
        case 13: handle_root_events(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
