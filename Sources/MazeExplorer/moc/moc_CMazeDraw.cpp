/****************************************************************************
** Meta object code from reading C++ file 'CMazeDraw.h'
**
** Created: Mon 28. Sep 15:33:27 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gui/CMazeDraw.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CMazeDraw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CMazeDraw[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      17,   11,   10,   10, 0x05,
      47,   37,   10,   10, 0x05,
      75,   37,   10,   10, 0x05,
     104,   37,   10,   10, 0x05,
     135,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
     162,  153,   10,   10, 0x0a,
     182,   37,   10,   10, 0x0a,
     208,   37,   10,   10, 0x0a,
     235,   37,   10,   10, 0x0a,
     272,  265,   10,   10, 0x0a,
     311,  309,   10,   10, 0x0a,
     335,   10,   10,   10, 0x0a,
     355,   10,   10,   10, 0x0a,
     404,  399,   10,   10, 0x0a,
     434,   10,   10,   10, 0x09,
     459,   10,   10,   10, 0x09,
     485,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CMazeDraw[] = {
    "CMazeDraw\0\0index\0SelectRoutePos(int)\0"
    "posX,posY\0onNewStartPosition(int,int)\0"
    "onNewFinishPosition(int,int)\0"
    "setNextFinishPosition(int,int)\0"
    "clearRobotRoute()\0mazeData\0"
    "setMazeData(CMaze&)\0setStartPosition(int,int)\0"
    "setFinishPosition(int,int)\0"
    "setNewFinishPosition(int,int)\0lRoute\0"
    "onSetRobotRoute(CExplorationResult&)\0"
    ",\0onCellSelected(int,int)\0onClearRobotRoute()\0"
    "onSetFinishPosition(vector<pair<int,int> >)\0"
    "iDir\0onSetRobotStartDirection(int)\0"
    "onMenuSetStartPosition()\0"
    "onMenuSetFinishPosition()\0"
    "onMenuSetNextFinishPosition()\0"
};

const QMetaObject CMazeDraw::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CMazeDraw,
      qt_meta_data_CMazeDraw, 0 }
};

const QMetaObject *CMazeDraw::metaObject() const
{
    return &staticMetaObject;
}

void *CMazeDraw::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMazeDraw))
        return static_cast<void*>(const_cast< CMazeDraw*>(this));
    return QWidget::qt_metacast(_clname);
}

int CMazeDraw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: SelectRoutePos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: onNewStartPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: onNewFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: setNextFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: clearRobotRoute(); break;
        case 5: setMazeData((*reinterpret_cast< CMaze(*)>(_a[1]))); break;
        case 6: setStartPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: setFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: setNewFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: onSetRobotRoute((*reinterpret_cast< CExplorationResult(*)>(_a[1]))); break;
        case 10: onCellSelected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: onClearRobotRoute(); break;
        case 12: onSetFinishPosition((*reinterpret_cast< vector<pair<int,int> >(*)>(_a[1]))); break;
        case 13: onSetRobotStartDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: onMenuSetStartPosition(); break;
        case 15: onMenuSetFinishPosition(); break;
        case 16: onMenuSetNextFinishPosition(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void CMazeDraw::SelectRoutePos(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CMazeDraw::onNewStartPosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CMazeDraw::onNewFinishPosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CMazeDraw::setNextFinishPosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CMazeDraw::clearRobotRoute()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
