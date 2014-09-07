/****************************************************************************
** Meta object code from reading C++ file 'CExperimentsDraftsDlg.h'
**
** Created: Mon 28. Sep 15:33:27 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gui/CExperimentsDraftsDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CExperimentsDraftsDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CExperimentsDraftsDlg[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      36,   23,   22,   22, 0x05,
      70,   23,   22,   22, 0x05,
     112,  110,   22,   22, 0x05,
     142,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     174,  170,   22,   22, 0x0a,
     208,  110,   22,   22, 0x0a,
     237,  110,   22,   22, 0x09,
     279,  110,   22,   22, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CExperimentsDraftsDlg[] = {
    "CExperimentsDraftsDlg\0\0dataForDraft\0"
    "emitDataForDraft(QVector<float>&)\0"
    "emitShowRobotRoute(CExplorationResult&)\0"
    ",\0emitLocationSelected(int,int)\0"
    "emitLocationNrSelected(int)\0pKB\0"
    "setKnowlegdeBase(CKnowlegdeBase*)\0"
    "setLocationSelected(int,int)\0"
    "slotTreeItemClicked(QTreeWidgetItem*,int)\0"
    "slotTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
};

const QMetaObject CExperimentsDraftsDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CExperimentsDraftsDlg,
      qt_meta_data_CExperimentsDraftsDlg, 0 }
};

const QMetaObject *CExperimentsDraftsDlg::metaObject() const
{
    return &staticMetaObject;
}

void *CExperimentsDraftsDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CExperimentsDraftsDlg))
        return static_cast<void*>(const_cast< CExperimentsDraftsDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int CExperimentsDraftsDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: emitDataForDraft((*reinterpret_cast< QVector<float>(*)>(_a[1]))); break;
        case 1: emitShowRobotRoute((*reinterpret_cast< CExplorationResult(*)>(_a[1]))); break;
        case 2: emitLocationSelected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: emitLocationNrSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setKnowlegdeBase((*reinterpret_cast< CKnowlegdeBase*(*)>(_a[1]))); break;
        case 5: setLocationSelected((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: slotTreeItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: slotTreeItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CExperimentsDraftsDlg::emitDataForDraft(QVector<float> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CExperimentsDraftsDlg::emitShowRobotRoute(CExplorationResult & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CExperimentsDraftsDlg::emitLocationSelected(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CExperimentsDraftsDlg::emitLocationNrSelected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
