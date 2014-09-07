/****************************************************************************
** Meta object code from reading C++ file 'CEnviroment.h'
**
** Created: Mon 28. Sep 15:33:25 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Experiment/CEnviroment.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CEnviroment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CEnviroment[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      20,   13,   12,   12, 0x05,
      55,   12,   12,   12, 0x05,
      89,   85,   12,   12, 0x05,
     131,   12,   12,   12, 0x05,
     146,  144,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     190,  169,   12,   12, 0x0a,
     241,  230,   12,   12, 0x0a,
     268,   12,   12,   12, 0x0a,
     296,  283,   12,   12, 0x0a,
     332,  322,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CEnviroment[] = {
    "CEnviroment\0\0lRoute\0"
    "robotFinished(CExplorationResult&)\0"
    "nextExplorationInExperiment()\0pKB\0"
    "setExploredKnowlegdeBase(CKnowlegdeBase*)\0"
    "redrawMaze()\0,\0setMazeLimits(int,int)\0"
    "m_ExperimentSettings\0"
    "onStartExperiment(CExperimentSettings&)\0"
    "scanResult\0onRobotScan(CScanResults*)\0"
    "onRobotMoved()\0bRight,bBack\0"
    "onRobotRotated(bool,bool)\0bIfInExit\0"
    "onRobotIfInExit(bool&)\0"
};

const QMetaObject CEnviroment::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CEnviroment,
      qt_meta_data_CEnviroment, 0 }
};

const QMetaObject *CEnviroment::metaObject() const
{
    return &staticMetaObject;
}

void *CEnviroment::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEnviroment))
        return static_cast<void*>(const_cast< CEnviroment*>(this));
    return QObject::qt_metacast(_clname);
}

int CEnviroment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: robotFinished((*reinterpret_cast< CExplorationResult(*)>(_a[1]))); break;
        case 1: nextExplorationInExperiment(); break;
        case 2: setExploredKnowlegdeBase((*reinterpret_cast< CKnowlegdeBase*(*)>(_a[1]))); break;
        case 3: redrawMaze(); break;
        case 4: setMazeLimits((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: onStartExperiment((*reinterpret_cast< CExperimentSettings(*)>(_a[1]))); break;
        case 6: onRobotScan((*reinterpret_cast< CScanResults*(*)>(_a[1]))); break;
        case 7: onRobotMoved(); break;
        case 8: onRobotRotated((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 9: onRobotIfInExit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CEnviroment::robotFinished(CExplorationResult & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CEnviroment::nextExplorationInExperiment()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CEnviroment::setExploredKnowlegdeBase(CKnowlegdeBase * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CEnviroment::redrawMaze()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void CEnviroment::setMazeLimits(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
