/****************************************************************************
** Meta object code from reading C++ file 'CExperimentParamsMazeDlg.h'
**
** Created: Mon 28. Sep 15:33:26 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gui/CExperimentParamsMazeDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CExperimentParamsMazeDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CExperimentParamsMazeDlg[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      28,   26,   25,   25, 0x05,
      54,   26,   25,   25, 0x05,
      81,   25,   25,   25, 0x05,
     124,   25,   25,   25, 0x05,

 // slots: signature, parameters, type, tag, flags
     147,   25,   25,   25, 0x09,
     171,   25,   25,   25, 0x09,
     217,  210,   25,   25, 0x09,
     241,   26,   25,   25, 0x0a,
     269,   26,   25,   25, 0x0a,
     298,   26,   25,   25, 0x0a,
     327,   26,   25,   25, 0x0a,
     353,   25,   25,   25, 0x0a,
     376,   25,   25,   25, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CExperimentParamsMazeDlg[] = {
    "CExperimentParamsMazeDlg\0\0,\0"
    "setStartPosition(int,int)\0"
    "setFinishPosition(int,int)\0"
    "setFinishPositions(vector<pair<int,int> >)\0"
    "setStartDirection(int)\0onSpinBoxStartSignals()\0"
    "onFinishPostionChanged(QStandardItem*)\0"
    "iIndex\0onDirectionChanged(int)\0"
    "onNewStartPosition(int,int)\0"
    "onNewFinishPosition(int,int)\0"
    "onAddFinishPosition(int,int)\0"
    "onMazeSizeChange(int,int)\0"
    "onButtonAddFinishPos()\0onButtonRemFinishPos()\0"
};

const QMetaObject CExperimentParamsMazeDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CExperimentParamsMazeDlg,
      qt_meta_data_CExperimentParamsMazeDlg, 0 }
};

const QMetaObject *CExperimentParamsMazeDlg::metaObject() const
{
    return &staticMetaObject;
}

void *CExperimentParamsMazeDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CExperimentParamsMazeDlg))
        return static_cast<void*>(const_cast< CExperimentParamsMazeDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int CExperimentParamsMazeDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setStartPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: setFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: setFinishPositions((*reinterpret_cast< vector<pair<int,int> >(*)>(_a[1]))); break;
        case 3: setStartDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: onSpinBoxStartSignals(); break;
        case 5: onFinishPostionChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 6: onDirectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: onNewStartPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: onNewFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: onAddFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: onMazeSizeChange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: onButtonAddFinishPos(); break;
        case 12: onButtonRemFinishPos(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CExperimentParamsMazeDlg::setStartPosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CExperimentParamsMazeDlg::setFinishPosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CExperimentParamsMazeDlg::setFinishPositions(vector<pair<int,int> > _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CExperimentParamsMazeDlg::setStartDirection(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
