/****************************************************************************
** Meta object code from reading C++ file 'CSpinBoxDelegate.h'
**
** Created: Mon 28. Sep 15:33:27 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Gui/CSpinBoxDelegate.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CSpinBoxDelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSpinBoxDelegate[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_CSpinBoxDelegate[] = {
    "CSpinBoxDelegate\0"
};

const QMetaObject CSpinBoxDelegate::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_CSpinBoxDelegate,
      qt_meta_data_CSpinBoxDelegate, 0 }
};

const QMetaObject *CSpinBoxDelegate::metaObject() const
{
    return &staticMetaObject;
}

void *CSpinBoxDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSpinBoxDelegate))
        return static_cast<void*>(const_cast< CSpinBoxDelegate*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int CSpinBoxDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
