/****************************************************************************
** Meta object code from reading C++ file 'gameengine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../game_engine/gameengine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameengine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GameEngine_t {
    QByteArrayData data[9];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameEngine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameEngine_t qt_meta_stringdata_GameEngine = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GameEngine"
QT_MOC_LITERAL(1, 11, 11), // "dump_result"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "initGame"
QT_MOC_LITERAL(4, 33, 4), // "argv"
QT_MOC_LITERAL(5, 38, 6), // "doTurn"
QT_MOC_LITERAL(6, 45, 14), // "get_cell_color"
QT_MOC_LITERAL(7, 60, 3), // "idx"
QT_MOC_LITERAL(8, 64, 16) // "get_cell_task_id"

    },
    "GameEngine\0dump_result\0\0initGame\0argv\0"
    "doTurn\0get_cell_color\0idx\0get_cell_task_id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameEngine[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    1,   40,    2, 0x02 /* Public */,
       5,    0,   43,    2, 0x02 /* Public */,
       6,    1,   44,    2, 0x02 /* Public */,
       8,    1,   47,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,    7,
    QMetaType::QString, QMetaType::Int,    7,

       0        // eod
};

void GameEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameEngine *_t = static_cast<GameEngine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dump_result(); break;
        case 1: _t->initGame((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->doTurn(); break;
        case 3: { QString _r = _t->get_cell_color((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->get_cell_task_id((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

const QMetaObject GameEngine::staticMetaObject = {
    { &QQuickItem::staticMetaObject, qt_meta_stringdata_GameEngine.data,
      qt_meta_data_GameEngine,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GameEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GameEngine.stringdata0))
        return static_cast<void*>(this);
    return QQuickItem::qt_metacast(_clname);
}

int GameEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
