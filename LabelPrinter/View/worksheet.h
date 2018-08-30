#ifndef WORKSHEET_H
#define WORKSHEET_H

#include <QWidget>

#define BTN_AREA_HEIGHT             60
#define PRINTER_BTN_SIZE            QSize(90, 59)
#define PRINTER_BTN_TEXT            QString("Printer")
#define PRINTER_BTN_TOOLTIP         "Ctrl+p"
#define BTN_AREA_MARGIN             QMargins(1, 0, 1, 0)

#define LABEL_TABLE_SIZE            QSize(420, 200)
#define TABLE_ROW_MAX               5
#define TABLE_COLUMN_MAX            4
#define TABLE_SIZE_CORRE            17
#define INPUT_COLUMN_MAX            6

#define TABLE_FONT_NAME             "Khmer"
#define TABLE_FONT_SIZE             10
#define FONT_TAG_START              QString("<font color='#707070'>")
#define FONT_TAG_END                QString("</font>")
#define TABLE_TITLE0_LABEL_TEXT     QString(FONT_TAG_START+"수주번호"+FONT_TAG_END)
#define TABLE_TITLE1_LABEL_TEXT     QString(FONT_TAG_START+"품목코드"+FONT_TAG_END)
#define TABLE_TITLE2_LABEL_TEXT     QString(FONT_TAG_START+"품 명"+FONT_TAG_END)
#define TABLE_TITLE3_LABEL_TEXT     QString(FONT_TAG_START+"규 격"+FONT_TAG_END)
#define TABLE_TITLE4_LABEL_TEXT     QString(FONT_TAG_START+"수량"+FONT_TAG_END)
#define TABLE_TITLE5_LABEL_TEXT     QString(FONT_TAG_START+"S/N"+FONT_TAG_END)
#define TABLE_LABEL_MARGINS         QMargins(0, 3, 0, 0)
#define TIP_LABEL_TEXT              "※ 주의)  입력하는 텍스트 길이가 길 경우 인쇄물의 텍스트가 잘릴 수 있습니다."

class QTableWidget;

class Worksheet : public QWidget
{
    Q_OBJECT
public:
    explicit Worksheet(QWidget *parent = 0);

public:
    void reSizeView(const int, const int);
    QString getTableText(const int);
    int getTabalColumnMax(void);
    void clearTableFocus(void);

private:
    QWidget *m_btnArea;
    QWidget *m_tableArea;
    QTableWidget *m_pLabelTable;    

private:
    void setBtnLayout(void);
    void setTableLayout(void);
    void setTable(const QString, const QString, const QString, const QString, const QString, const QString);

private Q_SLOTS:
    void slotPrintBtnClick(void);

protected:
    virtual void keyPressEvent(QKeyEvent *);
};

#endif // WORKSHEET_H
