/****************************************************************************
** Meta object code from reading C++ file 'CExperimentParamsDlg.h'
**
** Created: Mon 28. Sep 15:33:26 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gui/CExperimentParamsDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CExperimentParamsDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CExperimentParamsDlg[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      24,   22,   21,   21, 0x05,
      50,   22,   21,   21, 0x05,
      77,   21,   21,   21, 0x05,
     119,   21,   21,   21, 0x05,
     168,  148,   21,   21, 0x05,
     212,  206,   21,   21, 0x05,
     232,   21,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
     268,  255,   21,   21, 0x0a,
     299,  148,   21,   21, 0x0a,
     343,   22,   21,   21, 0x0a,
     371,   22,   21,   21, 0x0a,
     400,   22,   21,   21, 0x0a,
     429,   21,   21,   21, 0x0a,
     453,   21,   21,   21, 0x0a,
     476,   21,   21,   21, 0x09,
     500,   21,   21,   21, 0x09,
     520,   21,   21,   21, 0x09,
     541,   21,   21,   21, 0x09,
     562,   21,   21,   21, 0x09,
     597,   22,   21,   21, 0x09,
     629,   21,   21,   21, 0x09,
     677,   21,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CExperimentParamsDlg[] = {
    "CExperimentParamsDlg\0\0,\0"
    "setStartPosition(int,int)\0"
    "setFinishPosition(int,int)\0"
    "setFinishPosition(vector<pair<int,int> >)\0"
    "generateMaze(CMazeSettings&)\0"
    "cExperimentSettings\0"
    "startExperiment(CExperimentSettings&)\0"
    "cMaze\0getMazeData(CMaze&)\0"
    "setStartDirection(int)\0cMazeSetings\0"
    "setMazeSetings(CMazeSettings&)\0"
    "setExperimentSettings(CExperimentSettings&)\0"
    "onNewStartPosition(int,int)\0"
    "onNewFinishPosition(int,int)\0"
    "onAddFinishPosition(int,int)\0"
    "resetExperimentStatus()\0nextStepInExperiment()\0"
    "onSpinBoxStartSignals()\0processExperiment()\0"
    "openDialogLoadFile()\0openDialogSaveFile()\0"
    "onGenerateMazeWrap(CMazeSettings&)\0"
    "onSetStartPositionWrap(int,int)\0"
    "onSetFinishPositionWrap(vector<pair<int,int> >)\0"
    "onSetStartDirectionWrap(int)\0"
};

const QMetaObject CExperimentParamsDlg::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_CExperimentParamsDlg,
      qt_meta_data_CExperimentParamsDlg, 0 }
};

const QMetaObject *CExperimentParamsDlg::metaObject() const
{
    return &staticMetaObject;
}

void *CExperimentParamsDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CExperimentParamsDlg))
        return static_cast<void*>(const_cast< CExperimentParamsDlg*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int CExperimentParamsDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setStartPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: setFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: setFinishPosition((*reinterpret_cast< vector<pair<int,int> >(*)>(_a[1]))); break;
        case 3: generateMaze((*reinterpret_cast< CMazeSettings(*)>(_a[1]))); break;
        case 4: startExperiment((*reinterpret_cast< CExperimentSettings(*)>(_a[1]))); break;
        case 5: getMazeData((*reinterpret_cast< CMaze(*)>(_a[1]))); break;
        case 6: setStartDirection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setMazeSetings((*reinterpret_cast< CMazeSettings(*)>(_a[1]))); break;
        case 8: setExperimentSettings((*reinterpret_cast< CExperimentSettings(*)>(_a[1]))); break;
        case 9: onNewStartPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: onNewFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: onAddFinishPosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: resetExperimentStatus(); break;
        case 13: nextStepInExperiment(); break;
        case 14: onSpinBoxStartSignals(); break;
        case 15: processExperiment(); break;
        case 16: openDialogLoadFile(); break;
        case 17: openDialogSaveFile(); break;
        case 18: onGenerateMazeWrap((*reinterpret_cast< CMazeSettings(*)>(_a[1]))); break;
        case 19: onSetStartPositionWrap((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 20: onSetFinishPositionWrap((*reinterpret_cast< vector<pair<int,int> >(*)>(_a[1]))); break;
        case 21: onSetStartDirectionWrap((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void CExperimentParamsDlg::setStartPosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CExperimentParamsDlg::setFinishPosition(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CExperimentParamsDlg::setFinishPosition(vector<pair<int,int> > _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CExperimentParamsDlg::generateMaze(CMazeSettings & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CExperimentParamsDlg::startExperiment(CExperimentSettings & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CExperimentParamsDlg::getMazeData(CMaze & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CExperimentParamsDlg::setStartDirection(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
