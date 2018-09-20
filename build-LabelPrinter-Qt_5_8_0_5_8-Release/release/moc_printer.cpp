/****************************************************************************
** Meta object code from reading C++ file 'printer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LabelPrinter/Component/Printer/printer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'printer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Printer_t {
    QByteArrayData data[8];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Printer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Printer_t qt_meta_stringdata_Printer = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Printer"
QT_MOC_LITERAL(1, 8, 19), // "barcodeTableRowText"
QT_MOC_LITERAL(2, 28, 17), // "BARCODE_ROW1_TEXT"
QT_MOC_LITERAL(3, 46, 17), // "BARCODE_ROW2_TEXT"
QT_MOC_LITERAL(4, 64, 17), // "BARCODE_ROW3_TEXT"
QT_MOC_LITERAL(5, 82, 17), // "BARCODE_ROW4_TEXT"
QT_MOC_LITERAL(6, 100, 17), // "BARCODE_ROW5_TEXT"
QT_MOC_LITERAL(7, 118, 17) // "BARCODE_ROW6_TEXT"

    },
    "Printer\0barcodeTableRowText\0"
    "BARCODE_ROW1_TEXT\0BARCODE_ROW2_TEXT\0"
    "BARCODE_ROW3_TEXT\0BARCODE_ROW4_TEXT\0"
    "BARCODE_ROW5_TEXT\0BARCODE_ROW6_TEXT"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Printer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,    6,   18,

 // enum data: key, value
       2, uint(Printer::BARCODE_ROW1_TEXT),
       3, uint(Printer::BARCODE_ROW2_TEXT),
       4, uint(Printer::BARCODE_ROW3_TEXT),
       5, uint(Printer::BARCODE_ROW4_TEXT),
       6, uint(Printer::BARCODE_ROW5_TEXT),
       7, uint(Printer::BARCODE_ROW6_TEXT),

       0        // eod
};

void Printer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Printer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Printer.data,
      qt_meta_data_Printer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Printer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Printer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Printer.stringdata0))
        return static_cast<void*>(const_cast< Printer*>(this));
    return QObject::qt_metacast(_clname);
}

int Printer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
