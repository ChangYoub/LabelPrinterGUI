#ifndef PRINTER_H
#define PRINTER_H

#include <QObject>
#include <windows.h>
#include <winspool.h>

#define PRINTER_TITLE_FONT_SIZE                 25.5
#define PRINTER_ITEM_INFO_FONT_SIZE             24
#define PRINTER_ITEM_INFO_HIGH_LIGHT_FONT_SIZE  27

#define PRINTER_TABLE_POS_X                     31
#define PRINTER_TABLE_POS_Y                     26

#define PRITER_DRIVER_NAME                      "ZDesigner ZT410-203dpi ZPL"
#define PRINTER_CODEC                           "EUC-KR"
#define SOFTWARE_CODEC                          "UTF-8"

#define PRINTER_TABLE_CELL_TEXT1                "수주번호"
#define PRINTER_TABLE_CELL_TEXT2                "품목코드"
#define PRINTER_TABLE_CELL_TEXT3                "품    명"
#define PRINTER_TABLE_CELL_TEXT4                "규    격"
#define PRINTER_TABLE_CELL_TEXT5                "수 량"
#define PRINTER_TABLE_CELL_TEXT6                "S/N"

class Printer : public QObject
{
    Q_OBJECT
public:
    Printer(QObject *parent = 0);

public:
    enum barcodeTableRowText
    {
        BARCODE_ROW1_TEXT,
        BARCODE_ROW2_TEXT,
        BARCODE_ROW3_TEXT,
        BARCODE_ROW4_TEXT,
        BARCODE_ROW5_TEXT,
        BARCODE_ROW6_TEXT,
    };
    Q_ENUMS(barcodeTableRowText)

public:
    static Printer *getInstance(void);

public:
    bool printStart(const int, const int);
    void setRowText(const QString, const barcodeTableRowText);

private:
    QString m_barcodeRow1Str;
    QString m_barcodeRow2Str;
    QString m_barcodeRow3Str;
    QString m_barcodeRow4Str;
    QString m_barcodeRow5Str;
    QString m_barcodeRow6Str;

private:
    bool rawDataToPrinter(LPSTR, LPBYTE, DWORD);
    bool rawDataToPrinter(QString, QStringList *);
};

#endif // PRINTER_H
