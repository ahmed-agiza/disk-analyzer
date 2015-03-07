/****************************************************************************
** Meta object code from reading C++ file 'directoryanalyzer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DiskAnalyst/directoryanalyzer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'directoryanalyzer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DirectoryAnalyzer_t {
    QByteArrayData data[10];
    char stringdata[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DirectoryAnalyzer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DirectoryAnalyzer_t qt_meta_stringdata_DirectoryAnalyzer = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 16),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 13),
QT_MOC_LITERAL(4, 50, 9),
QT_MOC_LITERAL(5, 60, 4),
QT_MOC_LITERAL(6, 65, 5),
QT_MOC_LITERAL(7, 71, 10),
QT_MOC_LITERAL(8, 82, 5),
QT_MOC_LITERAL(9, 88, 15)
    },
    "DirectoryAnalyzer\0analysisComplete\0\0"
    "startAnalysis\0directory\0name\0flags\0"
    "setStopped\0value\0setAnalysisDone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DirectoryAnalyzer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   40,    2, 0x0a /* Public */,
       3,    2,   47,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   52,    2, 0x0a /* Public */,
       9,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    4,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void DirectoryAnalyzer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DirectoryAnalyzer *_t = static_cast<DirectoryAnalyzer *>(_o);
        switch (_id) {
        case 0: _t->analysisComplete(); break;
        case 1: _t->startAnalysis((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->startAnalysis((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->setStopped((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setAnalysisDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DirectoryAnalyzer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DirectoryAnalyzer::analysisComplete)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject DirectoryAnalyzer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DirectoryAnalyzer.data,
      qt_meta_data_DirectoryAnalyzer,  qt_static_metacall, 0, 0}
};


const QMetaObject *DirectoryAnalyzer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DirectoryAnalyzer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DirectoryAnalyzer.stringdata))
        return static_cast<void*>(const_cast< DirectoryAnalyzer*>(this));
    return QObject::qt_metacast(_clname);
}

int DirectoryAnalyzer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DirectoryAnalyzer::analysisComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
