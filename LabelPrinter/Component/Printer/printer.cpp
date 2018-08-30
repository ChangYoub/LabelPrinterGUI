#include "printer.h"

#include <QTextCodec>
#include <QPrinter>
#include <QPrintDialog>

Q_GLOBAL_STATIC(Printer, _Printer)

Printer::Printer(QObject *parent) : QObject(parent){
}

Printer *Printer::getInstance(void)
{
    return _Printer();
}

bool Printer::printStart(const int x, const int y)
{
    bool printState = true;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(PRINTER_CODEC));
    QString printerName = PRITER_DRIVER_NAME;
    QString lpData = "^XA"
                     "SEE:UHANGUL.DAT^FS"
                     "^CW1,E:KFONT3.FNT^CI26^FS"
                     "^FO" + QString::number(x + 60)  + "," + QString::number(y + 32) + "^A1N," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "^FD" + PRINTER_TABLE_CELL_TEXT1 + "^FS"
                     "^FO" + QString::number(x + 60)  + "," + QString::number(y + 104) + "^A1N," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "^FD" + PRINTER_TABLE_CELL_TEXT2 + "^FS"
                     "^FO" + QString::number(x + 60)  + "," + QString::number(y + 174) + "^A1N," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "^FD" + PRINTER_TABLE_CELL_TEXT3 + "^FS"
                     "^FO" + QString::number(x + 60)  + "," + QString::number(y + 244) + "^A1N," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "^FD" + PRINTER_TABLE_CELL_TEXT4 + "^FS"
                     "^FO" + QString::number(x + 23)  + "," + QString::number(y + 313) + "^A1N," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "^FD" + PRINTER_TABLE_CELL_TEXT5 + "^FS"
                     "^FO" + QString::number(x + 253) + "," + QString::number(y + 313) + "^A1N," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "," + QString::number(PRINTER_TITLE_FONT_SIZE)     + "^FD" + PRINTER_TABLE_CELL_TEXT6 + "^FS"
                     "^FO" + QString::number(x + 235) + "," + QString::number(y + 32)  + "^A1N," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "^FD" + m_barcodeRow1Str + "^FS"
                     "^FO" + QString::number(x + 235) + "," + QString::number(y + 104) + "^A1N," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "^FD" + m_barcodeRow2Str + "^FS"
                     "^FO" + QString::number(x + 235) + "," + QString::number(y + 174) + "^A1N," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "^FD" + m_barcodeRow3Str + "^FS"
                     "^FO" + QString::number(x + 235) + "," + QString::number(y + 244) + "^A1N," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "^FD" + m_barcodeRow4Str + "^FS"
                     "^FO" + QString::number(x + 130) + "," + QString::number(y + 313) + "^A1N," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "^FD" + m_barcodeRow5Str + "^FS"
                     "^FO" + QString::number(x + 350) + "," + QString::number(y + 313) + "^A1N," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "," + QString::number(PRINTER_ITEM_INFO_FONT_SIZE) + "^FD" + m_barcodeRow6Str + "^FS"
                     "^FO" + QString::number(x)       + "," + QString::number(y)       + "^GB586,0,5^FS"     /* 맨위 가로 */
                     "^FO" + QString::number(x)       + "," + QString::number(y + 353) + "^GB586,0,5^FS"     /* 맨아래 가로 */
                     "^FO" + QString::number(x)       + "," + QString::number(y)       + "^GB0,358,5^FS"     /* 좌측 세로 */
                     "^FO" + QString::number(x + 585) + "," + QString::number(y)       + "^GB0,358,5^FS"     /* 우측 세로 */
                     "^FO" + QString::number(x)       + "," + QString::number(y + 76)  + "^GB586,0,5^FS"     /* 수주번호 아래 가로 */
                     "^FO" + QString::number(x + 110) + "," + QString::number(y + 290) + "^GB0,65,5^FS"      /* 수량 우측 세로 */
                     "^FO" + QString::number(x + 330) + "," + QString::number(y + 290) + "^GB0,65,5^FS"      /* S/N 우측 세로 */
                     "^FO" + QString::number(x + 220) + "," + QString::number(y)       + "^GB0,358,5^FS"     /* TITLE 우측 세로 */
                     "^FO" + QString::number(x)       + "," + QString::number(y + 147) + "^GB586,0,5^FS"     /* QR 아래 가로 */
                     "^FO" + QString::number(x)       + "," + QString::number(y + 217) + "^GB586,0,5^FS"     /* 품번 아래 가로 */
                     "^FO" + QString::number(x)       + "," + QString::number(y + 286) + "^GB586,0,5^FS"     /* 위치 아래 가로 */
                     "^PQ1,0,1,Y"
                     "^XZ";

    long dwCount = lpData.toLocal8Bit().length();
    printState = rawDataToPrinter((char*)printerName.toLocal8Bit().data(),
                                  (unsigned char*)lpData.toLocal8Bit().data(),
                                  dwCount);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName(SOFTWARE_CODEC));

    return printState;
}

/*!
 * \brief Printer::setRowText
 * \param const QString str, const barcodeTableRowText rowNum
 * Row Text Setting
 */
void Printer::setRowText(const QString str, const barcodeTableRowText rowNum)
{
    switch(rowNum)
    {
        case Printer::BARCODE_ROW1_TEXT:
            m_barcodeRow1Str = str;
            break;

        case Printer::BARCODE_ROW2_TEXT:
            m_barcodeRow2Str = str;
            break;

        case Printer::BARCODE_ROW3_TEXT:
            m_barcodeRow3Str = str;
            break;

        case Printer::BARCODE_ROW4_TEXT:
            m_barcodeRow4Str = str;
            break;

        case Printer::BARCODE_ROW5_TEXT:
            m_barcodeRow5Str = str;
            break;

        case Printer::BARCODE_ROW6_TEXT:
            m_barcodeRow6Str = str;
            break;

        default:
            break;
    }
}

/*!
 * \brief Printer::rawDataToPrinter
 * \param LPSTR szPrinterName, LPBYTE lpData, DWORD dwCount
 * Raw Data To Printer
 */
bool Printer::rawDataToPrinter(LPSTR szPrinterName, LPBYTE lpData, DWORD dwCount)
{
    HANDLE hPrinter;
    DOC_INFO_1A DocInfo;
    DWORD dwJob;
    DWORD dwBytesWritten;

    /* Need a handle to the printer. */
    if(!OpenPrinterA(szPrinterName, &hPrinter, NULL))
    {
        return FALSE;
    }
    /* Fill in the structure with info about this "document." */
    DocInfo.pDocName = (LPSTR)"Zebra";
    DocInfo.pOutputFile = NULL;
    DocInfo.pDatatype = (LPSTR)"RAW";

    /* Inform the spooler the document is beginning. */
    if((dwJob = StartDocPrinterA(hPrinter, 1, (PBYTE)&DocInfo)) == 0)
    {
        ClosePrinter(hPrinter);
        return FALSE;
    }

    if(!StartPagePrinter(hPrinter))
    {
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return FALSE;
    }

    if(!WritePrinter(hPrinter, lpData, dwCount, &dwBytesWritten))
    {
        EndPagePrinter(hPrinter);
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return FALSE;
    }

    if(!EndPagePrinter(hPrinter))
    {
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return FALSE;
    }

    if(!EndDocPrinter(hPrinter))
    {
        ClosePrinter(hPrinter);
        return FALSE;
    }

    ClosePrinter(hPrinter);

    if(dwBytesWritten != dwCount)
        return FALSE;
    else
        return TRUE;
}

/*!
 * \brief Printer::rawDataToPrinter
 * \param QString printerName, QStringList *barcode
 * Raw Data To Printer
 */
bool Printer::rawDataToPrinter(QString printerName, QStringList *barcode)
{
    HANDLE hPrinter;
    DOC_INFO_1A DocInfo;
    DWORD dwJob;
    DWORD dwBytesWritten;
    LPSTR szPrinterName;
    long dwCount;

    if(!(barcode->length() > 0))
    {
        return false;
    }

    szPrinterName = (char*)printerName.toLocal8Bit().data();

    if(!OpenPrinterA(szPrinterName, &hPrinter, NULL))
    {
        return false;
    }

    DocInfo.pDocName = (LPSTR)"Zebra";
    DocInfo.pOutputFile = NULL;
    DocInfo.pDatatype = (LPSTR)"RAW";

    if((dwJob = StartDocPrinterA(hPrinter,1, (PBYTE)&DocInfo)) == 0)
    {
        ClosePrinter(hPrinter);
        return false;
    }

    if(!StartPagePrinter(hPrinter))
    {
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);
        return false;
    }

    foreach(QString str, *barcode)
    {
        dwCount = str.toLocal8Bit().length();
        if(!WritePrinter(hPrinter, (unsigned char *)str.toLocal8Bit().data(), dwCount, &dwBytesWritten))
        {
            EndPagePrinter(hPrinter);
            EndDocPrinter(hPrinter);
            ClosePrinter(hPrinter);

            return false;
        }

        if(dwBytesWritten != (DWORD)dwCount)
        {
            EndPagePrinter(hPrinter);
            EndDocPrinter(hPrinter);
            ClosePrinter(hPrinter);

            return false;
        }
    }

    if(!EndPagePrinter(hPrinter))
    {
        EndDocPrinter(hPrinter);
        ClosePrinter(hPrinter);

        return FALSE;
    }

    if(!EndDocPrinter(hPrinter))
    {
        ClosePrinter(hPrinter);
        return FALSE;
    }

    ClosePrinter(hPrinter);

    return true;
}
