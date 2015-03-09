/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DiskAnalyst/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[39];
    char stringdata[729];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 13),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 12),
QT_MOC_LITERAL(4, 39, 13),
QT_MOC_LITERAL(5, 53, 12),
QT_MOC_LITERAL(6, 66, 12),
QT_MOC_LITERAL(7, 79, 20),
QT_MOC_LITERAL(8, 100, 15),
QT_MOC_LITERAL(9, 116, 11),
QT_MOC_LITERAL(10, 128, 16),
QT_MOC_LITERAL(11, 145, 14),
QT_MOC_LITERAL(12, 160, 17),
QT_MOC_LITERAL(13, 178, 16),
QT_MOC_LITERAL(14, 195, 12),
QT_MOC_LITERAL(15, 208, 15),
QT_MOC_LITERAL(16, 224, 18),
QT_MOC_LITERAL(17, 243, 17),
QT_MOC_LITERAL(18, 261, 35),
QT_MOC_LITERAL(19, 297, 29),
QT_MOC_LITERAL(20, 327, 5),
QT_MOC_LITERAL(21, 333, 24),
QT_MOC_LITERAL(22, 358, 26),
QT_MOC_LITERAL(23, 385, 32),
QT_MOC_LITERAL(24, 418, 35),
QT_MOC_LITERAL(25, 454, 27),
QT_MOC_LITERAL(26, 482, 21),
QT_MOC_LITERAL(27, 504, 40),
QT_MOC_LITERAL(28, 545, 38),
QT_MOC_LITERAL(29, 584, 17),
QT_MOC_LITERAL(30, 602, 14),
QT_MOC_LITERAL(31, 617, 16),
QT_MOC_LITERAL(32, 634, 10),
QT_MOC_LITERAL(33, 645, 12),
QT_MOC_LITERAL(34, 658, 17),
QT_MOC_LITERAL(35, 676, 17),
QT_MOC_LITERAL(36, 694, 15),
QT_MOC_LITERAL(37, 710, 13),
QT_MOC_LITERAL(38, 724, 4)
    },
    "MainWindow\0startAnalysis\0\0stopAnalysis\0"
    "startScanning\0stopScanning\0startHashing\0"
    "DirectoryEntriesList\0DirectoryEntry*\0"
    "stopHashing\0analyzeDirectory\0"
    "launchTerminal\0launchDupeChecker\0"
    "analysisComplete\0scanComplete\0"
    "hashingComplete\0DuplicateEntryList\0"
    "treeMenuRequested\0on_actionAnalyzeDirectory_triggered\0"
    "on_twgDirViewer_doubleClicked\0index\0"
    "on_twgDirViewer_expanded\0"
    "on_actionRefresh_triggered\0"
    "on_actionOpen_Terminal_triggered\0"
    "on_actionExploreDirectory_triggered\0"
    "on_actionSettings_triggered\0"
    "on_actionUp_triggered\0"
    "on_actionDuplicateFilesChecker_triggered\0"
    "on_actionSelectRootDirectory_triggered\0"
    "exposeObjectsToJS\0setCurrentPath\0"
    "setDirectoryJson\0navigateTo\0stopAnalyzer\0"
    "stopDupesAnalyzer\0stopDupesChecking\0"
    "onDupesProgress\0openDirectory\0path"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  174,    2, 0x06 /* Public */,
       3,    1,  181,    2, 0x06 /* Public */,
       4,    3,  184,    2, 0x06 /* Public */,
       5,    1,  191,    2, 0x06 /* Public */,
       6,    2,  194,    2, 0x06 /* Public */,
       9,    1,  199,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  202,    2, 0x08 /* Private */,
      11,    1,  205,    2, 0x08 /* Private */,
      12,    1,  208,    2, 0x08 /* Private */,
      13,    0,  211,    2, 0x08 /* Private */,
      14,    0,  212,    2, 0x08 /* Private */,
      15,    1,  213,    2, 0x08 /* Private */,
      17,    1,  216,    2, 0x08 /* Private */,
      18,    0,  219,    2, 0x08 /* Private */,
      19,    1,  220,    2, 0x08 /* Private */,
      21,    1,  223,    2, 0x08 /* Private */,
      22,    0,  226,    2, 0x08 /* Private */,
      23,    0,  227,    2, 0x08 /* Private */,
      24,    0,  228,    2, 0x08 /* Private */,
      25,    0,  229,    2, 0x08 /* Private */,
      26,    0,  230,    2, 0x08 /* Private */,
      27,    0,  231,    2, 0x08 /* Private */,
      28,    0,  232,    2, 0x08 /* Private */,
      29,    0,  233,    2, 0x0a /* Public */,
      30,    1,  234,    2, 0x0a /* Public */,
      31,    2,  237,    2, 0x0a /* Public */,
      32,    1,  242,    2, 0x0a /* Public */,
      33,    0,  245,    2, 0x0a /* Public */,
      34,    0,  246,    2, 0x0a /* Public */,
      35,    0,  247,    2, 0x0a /* Public */,
      36,    1,  248,    2, 0x0a /* Public */,
      37,    1,  251,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 8,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   20,
    QMetaType::Void, QMetaType::QModelIndex,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,   38,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->startAnalysis((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->stopAnalysis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->startScanning((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->stopScanning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->startHashing((*reinterpret_cast< DirectoryEntriesList(*)>(_a[1])),(*reinterpret_cast< DirectoryEntry*(*)>(_a[2]))); break;
        case 5: _t->stopHashing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->analyzeDirectory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->launchTerminal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->launchDupeChecker((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->analysisComplete(); break;
        case 10: _t->scanComplete(); break;
        case 11: _t->hashingComplete((*reinterpret_cast< DuplicateEntryList(*)>(_a[1]))); break;
        case 12: _t->treeMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 13: _t->on_actionAnalyzeDirectory_triggered(); break;
        case 14: _t->on_twgDirViewer_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 15: _t->on_twgDirViewer_expanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 16: _t->on_actionRefresh_triggered(); break;
        case 17: _t->on_actionOpen_Terminal_triggered(); break;
        case 18: _t->on_actionExploreDirectory_triggered(); break;
        case 19: _t->on_actionSettings_triggered(); break;
        case 20: _t->on_actionUp_triggered(); break;
        case 21: _t->on_actionDuplicateFilesChecker_triggered(); break;
        case 22: _t->on_actionSelectRootDirectory_triggered(); break;
        case 23: _t->exposeObjectsToJS(); break;
        case 24: _t->setCurrentPath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->setDirectoryJson((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 26: _t->navigateTo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->stopAnalyzer(); break;
        case 28: _t->stopDupesAnalyzer(); break;
        case 29: _t->stopDupesChecking(); break;
        case 30: _t->onDupesProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->openDirectory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QString , QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startAnalysis)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopAnalysis)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)(QString , QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startScanning)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopScanning)) {
                *result = 3;
            }
        }
        {
            typedef void (MainWindow::*_t)(DirectoryEntriesList , DirectoryEntry * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::startHashing)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stopHashing)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startAnalysis(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::stopAnalysis(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::startScanning(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::stopScanning(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::startHashing(DirectoryEntriesList _t1, DirectoryEntry * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::stopHashing(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
