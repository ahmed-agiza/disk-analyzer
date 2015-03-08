/****************************************************************************
** Meta object code from reading C++ file 'dupesdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DiskAnalyst/dupesdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dupesdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DupesDialog_t {
    QByteArrayData data[8];
    char stringdata[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DupesDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DupesDialog_t qt_meta_stringdata_DupesDialog = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 10),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 8),
QT_MOC_LITERAL(4, 33, 10),
QT_MOC_LITERAL(5, 44, 16),
QT_MOC_LITERAL(6, 61, 24),
QT_MOC_LITERAL(7, 86, 5)
    },
    "DupesDialog\0deleteFile\0\0filePath\0"
    "openFolder\0refreshTableView\0"
    "on_tblDuplicates_clicked\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DupesDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       5,    0,   40,    2, 0x08 /* Private */,
       6,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Int, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,

       0        // eod
};

void DupesDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DupesDialog *_t = static_cast<DupesDialog *>(_o);
        switch (_id) {
        case 0: { int _r = _t->deleteFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: _t->openFolder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->refreshTableView(); break;
        case 3: _t->on_tblDuplicates_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DupesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DupesDialog.data,
      qt_meta_data_DupesDialog,  qt_static_metacall, 0, 0}
};


const QMetaObject *DupesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DupesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DupesDialog.stringdata))
        return static_cast<void*>(const_cast< DupesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DupesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
