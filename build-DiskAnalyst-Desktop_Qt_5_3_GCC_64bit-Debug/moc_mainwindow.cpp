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
    QByteArrayData data[52];
    char stringdata[988];
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
QT_MOC_LITERAL(3, 26, 14),
QT_MOC_LITERAL(4, 41, 12),
QT_MOC_LITERAL(5, 54, 13),
QT_MOC_LITERAL(6, 68, 12),
QT_MOC_LITERAL(7, 81, 12),
QT_MOC_LITERAL(8, 94, 20),
QT_MOC_LITERAL(9, 115, 15),
QT_MOC_LITERAL(10, 131, 11),
QT_MOC_LITERAL(11, 143, 16),
QT_MOC_LITERAL(12, 160, 14),
QT_MOC_LITERAL(13, 175, 17),
QT_MOC_LITERAL(14, 193, 16),
QT_MOC_LITERAL(15, 210, 12),
QT_MOC_LITERAL(16, 223, 15),
QT_MOC_LITERAL(17, 239, 18),
QT_MOC_LITERAL(18, 258, 17),
QT_MOC_LITERAL(19, 276, 16),
QT_MOC_LITERAL(20, 293, 20),
QT_MOC_LITERAL(21, 314, 17),
QT_MOC_LITERAL(22, 332, 20),
QT_MOC_LITERAL(23, 353, 35),
QT_MOC_LITERAL(24, 389, 29),
QT_MOC_LITERAL(25, 419, 5),
QT_MOC_LITERAL(26, 425, 24),
QT_MOC_LITERAL(27, 450, 26),
QT_MOC_LITERAL(28, 477, 32),
QT_MOC_LITERAL(29, 510, 35),
QT_MOC_LITERAL(30, 546, 27),
QT_MOC_LITERAL(31, 574, 21),
QT_MOC_LITERAL(32, 596, 40),
QT_MOC_LITERAL(33, 637, 38),
QT_MOC_LITERAL(34, 676, 24),
QT_MOC_LITERAL(35, 701, 26),
QT_MOC_LITERAL(36, 728, 24),
QT_MOC_LITERAL(37, 753, 24),
QT_MOC_LITERAL(38, 778, 22),
QT_MOC_LITERAL(39, 801, 7),
QT_MOC_LITERAL(40, 809, 24),
QT_MOC_LITERAL(41, 834, 17),
QT_MOC_LITERAL(42, 852, 14),
QT_MOC_LITERAL(43, 867, 16),
QT_MOC_LITERAL(44, 884, 10),
QT_MOC_LITERAL(45, 895, 12),
QT_MOC_LITERAL(46, 908, 17),
QT_MOC_LITERAL(47, 926, 17),
QT_MOC_LITERAL(48, 944, 15),
QT_MOC_LITERAL(49, 960, 13),
QT_MOC_LITERAL(50, 974, 4),
QT_MOC_LITERAL(51, 979, 8)
    },
    "MainWindow\0startAnalysis\0\0AnalysisTarget\0"
    "stopAnalysis\0startScanning\0stopScanning\0"
    "startHashing\0DirectoryEntriesList\0"
    "DirectoryEntry*\0stopHashing\0"
    "analyzeDirectory\0launchTerminal\0"
    "launchDupeChecker\0analysisComplete\0"
    "scanComplete\0hashingComplete\0"
    "DuplicateEntryList\0treeMenuRequested\0"
    "listLargestFiles\0listLargestExtension\0"
    "listLargestGroups\0refreshChartsButtons\0"
    "on_actionAnalyzeDirectory_triggered\0"
    "on_twgDirViewer_doubleClicked\0index\0"
    "on_twgDirViewer_expanded\0"
    "on_actionRefresh_triggered\0"
    "on_actionOpen_Terminal_triggered\0"
    "on_actionExploreDirectory_triggered\0"
    "on_actionSettings_triggered\0"
    "on_actionUp_triggered\0"
    "on_actionDuplicateFilesChecker_triggered\0"
    "on_actionSelectRootDirectory_triggered\0"
    "on_actionAbout_triggered\0"
    "on_btnLargestFiles_clicked\0"
    "on_btnExtensions_clicked\0"
    "on_btnSizeGroups_clicked\0"
    "on_btnBarChart_clicked\0checked\0"
    "on_btnDoughChart_clicked\0exposeObjectsToJS\0"
    "setCurrentPath\0setDirectoryJson\0"
    "navigateTo\0stopAnalyzer\0stopDupesAnalyzer\0"
    "stopDupesChecking\0onDupesProgress\0"
    "openDirectory\0path\0statFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  229,    2, 0x06 /* Public */,
       4,    1,  238,    2, 0x06 /* Public */,
       5,    4,  241,    2, 0x06 /* Public */,
       6,    1,  250,    2, 0x06 /* Public */,
       7,    2,  253,    2, 0x06 /* Public */,
      10,    1,  258,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,  261,    2, 0x08 /* Private */,
      12,    1,  264,    2, 0x08 /* Private */,
      13,    1,  267,    2, 0x08 /* Private */,
      14,    1,  270,    2, 0x08 /* Private */,
      15,    0,  273,    2, 0x08 /* Private */,
      16,    1,  274,    2, 0x08 /* Private */,
      18,    1,  277,    2, 0x08 /* Private */,
      19,    1,  280,    2, 0x08 /* Private */,
      20,    1,  283,    2, 0x08 /* Private */,
      21,    1,  286,    2, 0x08 /* Private */,
      22,    0,  289,    2, 0x08 /* Private */,
      23,    0,  290,    2, 0x08 /* Private */,
      24,    1,  291,    2, 0x08 /* Private */,
      26,    1,  294,    2, 0x08 /* Private */,
      27,    0,  297,    2, 0x08 /* Private */,
      28,    0,  298,    2, 0x08 /* Private */,
      29,    0,  299,    2, 0x08 /* Private */,
      30,    0,  300,    2, 0x08 /* Private */,
      31,    0,  301,    2, 0x08 /* Private */,
      32,    0,  302,    2, 0x08 /* Private */,
      33,    0,  303,    2, 0x08 /* Private */,
      34,    0,  304,    2, 0x08 /* Private */,
      35,    0,  305,    2, 0x08 /* Private */,
      36,    0,  306,    2, 0x08 /* Private */,
      37,    0,  307,    2, 0x08 /* Private */,
      38,    1,  308,    2, 0x08 /* Private */,
      40,    1,  311,    2, 0x08 /* Private */,
      41,    0,  314,    2, 0x0a /* Public */,
      42,    1,  315,    2, 0x0a /* Public */,
      43,    2,  318,    2, 0x0a /* Public */,
      44,    1,  323,    2, 0x0a /* Public */,
      45,    0,  326,    2, 0x0a /* Public */,
      46,    0,  327,    2, 0x0a /* Public */,
      47,    0,  328,    2, 0x0a /* Public */,
      48,    1,  329,    2, 0x0a /* Public */,
      49,    1,  332,    2, 0x0a /* Public */,
      51,    1,  335,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, 0x80000000 | 3,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, 0x80000000 | 3,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 9,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   25,
    QMetaType::Void, QMetaType::QModelIndex,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   39,
    QMetaType::Void, QMetaType::Bool,   39,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->startAnalysis((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< AnalysisTarget(*)>(_a[4]))); break;
        case 1: _t->stopAnalysis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->startScanning((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< AnalysisTarget(*)>(_a[4]))); break;
        case 3: _t->stopScanning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->startHashing((*reinterpret_cast< DirectoryEntriesList(*)>(_a[1])),(*reinterpret_cast< DirectoryEntry*(*)>(_a[2]))); break;
        case 5: _t->stopHashing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->analyzeDirectory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->launchTerminal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->launchDupeChecker((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->analysisComplete((*reinterpret_cast< AnalysisTarget(*)>(_a[1]))); break;
        case 10: _t->scanComplete(); break;
        case 11: _t->hashingComplete((*reinterpret_cast< DuplicateEntryList(*)>(_a[1]))); break;
        case 12: _t->treeMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 13: _t->listLargestFiles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->listLargestExtension((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->listLargestGroups((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->refreshChartsButtons(); break;
        case 17: _t->on_actionAnalyzeDirectory_triggered(); break;
        case 18: _t->on_twgDirViewer_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 19: _t->on_twgDirViewer_expanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 20: _t->on_actionRefresh_triggered(); break;
        case 21: _t->on_actionOpen_Terminal_triggered(); break;
        case 22: _t->on_actionExploreDirectory_triggered(); break;
        case 23: _t->on_actionSettings_triggered(); break;
        case 24: _t->on_actionUp_triggered(); break;
        case 25: _t->on_actionDuplicateFilesChecker_triggered(); break;
        case 26: _t->on_actionSelectRootDirectory_triggered(); break;
        case 27: _t->on_actionAbout_triggered(); break;
        case 28: _t->on_btnLargestFiles_clicked(); break;
        case 29: _t->on_btnExtensions_clicked(); break;
        case 30: _t->on_btnSizeGroups_clicked(); break;
        case 31: _t->on_btnBarChart_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->on_btnDoughChart_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->exposeObjectsToJS(); break;
        case 34: _t->setCurrentPath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 35: _t->setDirectoryJson((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 36: _t->navigateTo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 37: _t->stopAnalyzer(); break;
        case 38: _t->stopDupesAnalyzer(); break;
        case 39: _t->stopDupesChecking(); break;
        case 40: _t->onDupesProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->openDirectory((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 42: _t->statFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QString , QString , int , AnalysisTarget );
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
            typedef void (MainWindow::*_t)(QString , QString , int , AnalysisTarget );
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
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::startAnalysis(QString _t1, QString _t2, int _t3, AnalysisTarget _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::stopAnalysis(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::startScanning(QString _t1, QString _t2, int _t3, AnalysisTarget _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
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
