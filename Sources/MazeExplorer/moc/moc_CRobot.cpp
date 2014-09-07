/****************************************************************************
** Meta object code from reading C++ file 'CRobot.h'
**
** Created: Mon 28. Sep 15:33:25 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Experiment/CRobot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CRobot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CRobot[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      34,   21,    7,    7, 0x05,
      64,   57,    7,    7, 0x05,
     113,  103,    7,    7, 0x05,
     134,    7,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_CRobot[] = {
    "CRobot\0\0robotMoved()\0bRight,bBack\0"
    "robotRotate(bool,bool)\0lRoute\0"
    "robotFinished(QList<QPair<int,bool> >)\0"
    "bIsInExit\0checkIfInExit(bool&)\0"
    "robotScans(CScanResults*)\0"
};

const QMetaObject CRobot::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CRobot,
      qt_meta_data_CRobot, 0 }
};

const QMetaObject *CRobot::metaObject() const
{
    return &staticMetaObject;
}

void *CRobot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CRobot))
        return static_cast<void*>(const_cast< CRobot*>(this));
    return QObject::qt_metacast(_clname);
}

int CRobot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: robotMoved(); break;
        case 1: robotRotate((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: robotFinished((*reinterpret_cast< QList<QPair<int,bool> >(*)>(_a[1]))); break;
        case 3: checkIfInExit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: robotScans((*reinterpret_cast< CScanResults*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CRobot::robotMoved()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CRobot::robotRotate(bool _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CRobot::robotFinished(QList<QPair<int,bool> > _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CRobot::checkIfInExit(bool & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CRobot::robotScans(CScanResults * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
