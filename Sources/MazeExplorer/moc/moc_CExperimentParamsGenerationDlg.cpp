/****************************************************************************
** Meta object code from reading C++ file 'CExperimentParamsGenerationDlg.h'
**
** Created: Mon 28. Sep 15:33:26 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gui/CExperimentParamsGenerationDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CExperimentParamsGenerationDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CExperimentParamsGenerationDlg[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      34,   32,   31,   31, 0x05,
      57,   31,   31,   31, 0x05,

 // slots: signature, parameters, type, tag, flags
      86,   31,   31,   31, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CExperimentParamsGenerationDlg[] = {
    "CExperimentParamsGenerationDlg\0\0,\0"
    "setMazeLimits(int,int)\0"
    "generateMaze(CMazeSettings&)\0"
    "onGenerateMaze(bool)\0"
};

const QMetaObject CExperimentParamsGenerationDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CExperimentParamsGenerationDlg,
      qt_meta_data_CExperimentParamsGenerationDlg, 0 }
};

const QMetaObject *CExperimentParamsGenerationDlg::metaObject() const
{
    return &staticMetaObject;
}

void *CExperimentParamsGenerationDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CExperimentParamsGenerationDlg))
        return static_cast<void*>(const_cast< CExperimentParamsGenerationDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int CExperimentParamsGenerationDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setMazeLimits((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: generateMaze((*reinterpret_cast< CMazeSettings(*)>(_a[1]))); break;
        case 2: onGenerateMaze((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CExperimentParamsGenerationDlg::setMazeLimits(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CExperimentParamsGenerationDlg::generateMaze(CMazeSettings & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
