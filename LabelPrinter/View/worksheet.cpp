#include "worksheet.h"
#include "stylesheet.h"
#include "global.h"
#include "Component/Printer/printer.h"
#include "Component/Xml/xml.h"
#include "View/Dialog/correctiondialog.h"
#include <QPushButton>
#include <QBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLabel>

#include <QDebug>

Worksheet::Worksheet(QWidget *parent):QWidget(parent)
{
    QString strList[INPUT_COLUMN_MAX];
    QString strCheck;
    setBtnLayout();
    setTableLayout();
    for(int i = 0; i < INPUT_COLUMN_MAX; i++) {
        strCheck = Xml::getInstance()->getXmlTableText(i);
        if(strCheck != XML_DEFAULT_VALUE) {
            strList[i] = strCheck;
        }
    }
    setTable(strList[0], strList[1], strList[2], strList[3], strList[4], strList[5]);
}

void Worksheet::setBtnLayout(void)
{
    m_btnArea = new QWidget(this);
    m_btnArea->setStyleSheet(BTN_AREA_WIDGET_QSS);

    QPushButton *printerBtn = new QPushButton(this);
    printerBtn->setFixedSize(PRINTER_BTN_SIZE);
    printerBtn->setCursor(Qt::PointingHandCursor);
    printerBtn->setFocusPolicy(Qt::NoFocus);
    printerBtn->setText(PRINTER_BTN_TEXT);
    printerBtn->setToolTip(PRINTER_BTN_TOOLTIP);
    printerBtn->setStyleSheet(PRINTER_BTN_ICON_QSS);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(BTN_AREA_MARGIN);
    hLayout->setAlignment(Qt::AlignRight);
    hLayout->addWidget(printerBtn);
    m_btnArea->setLayout(hLayout);

    QObject::connect(printerBtn,  SIGNAL(clicked()), this, SLOT(slotPrintBtnClick()));
}

void Worksheet::setTableLayout(void)
{
    m_tableArea = new QWidget(this);
    m_tableArea->setGeometry(this->x(), BTN_AREA_HEIGHT, this->width(), this->height()-BTN_AREA_HEIGHT);
    m_tableArea->setStyleSheet(DEFAULT_QSS);

    m_pLabelTable = new QTableWidget(m_tableArea);
    m_pLabelTable->setFixedSize(LABEL_TABLE_SIZE);
    m_pLabelTable->setRowCount(TABLE_ROW_MAX);
    m_pLabelTable->setColumnCount(4);
    m_pLabelTable->horizontalHeader()->hide();
    m_pLabelTable->verticalHeader()->hide();
    m_pLabelTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pLabelTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pLabelTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pLabelTable->setFocusPolicy(Qt::NoFocus);
    m_pLabelTable->setTextElideMode(Qt::ElideNone);
    m_pLabelTable->setWordWrap(false);
    m_pLabelTable->setShowGrid(false);
    m_pLabelTable->setStyleSheet(TABLE_QSS);

    int columnWidth = (m_pLabelTable->width()/TABLE_COLUMN_MAX);
    int rowHeight = (m_pLabelTable->height()/TABLE_ROW_MAX);

    m_pLabelTable->setColumnWidth(0, columnWidth-TABLE_SIZE_CORRE);
    m_pLabelTable->setColumnWidth(1, columnWidth-TABLE_SIZE_CORRE);
    m_pLabelTable->setColumnWidth(2, columnWidth+TABLE_SIZE_CORRE-30);
    m_pLabelTable->setColumnWidth(3, columnWidth+TABLE_SIZE_CORRE+30-1);
    for(int i = 0; m_pLabelTable->rowCount() > i; i++) {
        if(i == (m_pLabelTable->rowCount()-1)) {
            m_pLabelTable->setRowHeight(i, rowHeight-1);
        }
        else {
            m_pLabelTable->setRowHeight(i, rowHeight);
        }
    }

    m_pLabelTable->setSpan(0, 0, 1, 2);
    m_pLabelTable->setSpan(0, 2, 1, 2);
    m_pLabelTable->setSpan(1, 0, 1, 2);
    m_pLabelTable->setSpan(1, 2, 1, 2);
    m_pLabelTable->setSpan(2, 0, 1, 2);
    m_pLabelTable->setSpan(2, 2, 1, 2);
    m_pLabelTable->setSpan(3, 0, 1, 2);
    m_pLabelTable->setSpan(3, 2, 1, 2);

    QFont font(TABLE_FONT_NAME, TABLE_FONT_SIZE, QFont::Bold);

    QLabel *titleLabel0 =new QLabel(TABLE_TITLE0_LABEL_TEXT, this);
    titleLabel0->setContentsMargins(TABLE_LABEL_MARGINS);
    titleLabel0->setAlignment(Qt::AlignCenter);
    titleLabel0->setFont(font);

    QLabel *titleLabel1 =new QLabel(TABLE_TITLE1_LABEL_TEXT, this);
    titleLabel1->setContentsMargins(TABLE_LABEL_MARGINS);
    titleLabel1->setAlignment(Qt::AlignCenter);
    titleLabel1->setFont(font);

    QLabel *titleLabel2 =new QLabel(TABLE_TITLE2_LABEL_TEXT, this);
    titleLabel2->setContentsMargins(TABLE_LABEL_MARGINS);
    titleLabel2->setAlignment(Qt::AlignCenter);
    titleLabel2->setFont(font);

    QLabel *titleLabel3 =new QLabel(TABLE_TITLE3_LABEL_TEXT, this);
    titleLabel3->setContentsMargins(TABLE_LABEL_MARGINS);
    titleLabel3->setAlignment(Qt::AlignCenter);
    titleLabel3->setFont(font);

    QLabel *titleLabel4 =new QLabel(TABLE_TITLE4_LABEL_TEXT, this);
    titleLabel4->setContentsMargins(TABLE_LABEL_MARGINS);
    titleLabel4->setAlignment(Qt::AlignCenter);
    titleLabel4->setFont(font);

    QLabel *titleLabel5 =new QLabel(TABLE_TITLE5_LABEL_TEXT, this);
    titleLabel5->setContentsMargins(TABLE_LABEL_MARGINS);
    titleLabel5->setAlignment(Qt::AlignCenter);
    titleLabel5->setFont(font);

    m_pLabelTable->setCellWidget(0, 0, titleLabel0);
    m_pLabelTable->setCellWidget(1, 0, titleLabel1);
    m_pLabelTable->setCellWidget(2, 0, titleLabel2);
    m_pLabelTable->setCellWidget(3, 0, titleLabel3);
    m_pLabelTable->setCellWidget(4, 0, titleLabel4);
    m_pLabelTable->setCellWidget(4, 2, titleLabel5);

    QLabel *tipText = new QLabel;
    tipText->setText(TIP_LABEL_TEXT);
    tipText->setStyleSheet(TIP_LABEL_TEXT_QSS);

    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->addSpacing(20);
    pVLayout->addWidget(m_pLabelTable, 0, Qt::AlignCenter);
    pVLayout->addWidget(tipText, 0, Qt::AlignCenter);
    m_tableArea->setLayout(pVLayout);
}

void Worksheet::setTable(const QString stNumber,   const QString strCode,
                         const QString strName,    const QString strSpec,
                         const QString strQuantity, const QString strSn)
{
    QFont font(TABLE_FONT_NAME, TABLE_FONT_SIZE);

    QTableWidgetItem *titleText0 = new QTableWidgetItem();
    m_pLabelTable->setItem(0, 0, titleText0);
    titleText0->setFont(font);
    titleText0->setFlags(Qt::ItemIsEditable);

    QTableWidgetItem *itemText1 = new QTableWidgetItem();
    m_pLabelTable->setItem(0, 2, itemText1);
    itemText1->setFont(font);
    itemText1->setText(stNumber);

    QTableWidgetItem *titleText1 = new QTableWidgetItem();
    m_pLabelTable->setItem(1, 0, titleText1);
    titleText1->setFont(font);
    titleText1->setFlags(Qt::ItemIsEditable);

    QTableWidgetItem *itemText2 = new QTableWidgetItem();
    m_pLabelTable->setItem(1, 2, itemText2);
    itemText2->setFont(font);
    itemText2->setText(strCode);

    QTableWidgetItem *titleText2 = new QTableWidgetItem();
    m_pLabelTable->setItem(2, 0, titleText2);
    titleText2->setFont(font);
    titleText2->setFlags(Qt::ItemIsEditable);

    QTableWidgetItem *itemText3 = new QTableWidgetItem();
    m_pLabelTable->setItem(2, 2, itemText3);
    itemText3->setFont(font);
    itemText3->setText(strName);

    QTableWidgetItem *titleText3 = new QTableWidgetItem();
    m_pLabelTable->setItem(3, 0, titleText3);
    titleText3->setFont(font);
    titleText3->setFlags(Qt::ItemIsEditable);

    QTableWidgetItem *itemText4 = new QTableWidgetItem();
    m_pLabelTable->setItem(3, 2, itemText4);
    itemText4->setFont(font);
    itemText4->setText(strSpec);

    QTableWidgetItem *titleText4 = new QTableWidgetItem();
    m_pLabelTable->setItem(4, 0, titleText4);
    titleText4->setFont(font);
    titleText4->setFlags(Qt::ItemIsEditable);

    QTableWidgetItem *itemText5 = new QTableWidgetItem();
    m_pLabelTable->setItem(4, 1, itemText5);
    itemText5->setFont(font);
    itemText5->setText(strQuantity);

    QTableWidgetItem *titleText5 = new QTableWidgetItem();
    m_pLabelTable->setItem(4, 2, titleText5);
    titleText5->setFont(font);
    titleText5->setFlags(Qt::ItemIsEditable);

    QTableWidgetItem *itemText6 = new QTableWidgetItem();
    m_pLabelTable->setItem(4, 3, itemText6);
    itemText6->setFont(font);
    itemText6->setText(strSn);
}

int Worksheet::getTabalColumnMax(void)
{
    return INPUT_COLUMN_MAX;
}

QString Worksheet::getTableText(const int index)
{
    QString tempString;
    switch(index)
    {
        case 0:
            tempString = m_pLabelTable->item(0, 2)->text();
            break;

        case 1:
            tempString = m_pLabelTable->item(1, 2)->text();
            break;

        case 2:
            tempString = m_pLabelTable->item(2, 2)->text();
            break;

        case 3:
            tempString = m_pLabelTable->item(3, 2)->text();
            break;

        case 4:
            tempString = m_pLabelTable->item(4, 1)->text();
            break;

        case 5:
            tempString = m_pLabelTable->item(4, 3)->text();
            break;

        default: break;
    }

    return tempString;
}

void Worksheet::reSizeView(const int width, const int height)
{
    this->resize(width, height);
    m_btnArea->resize(width, BTN_AREA_HEIGHT);
    m_tableArea->resize(width, height-m_btnArea->height());
}

void Worksheet::clearTableFocus(void)
{
    m_pLabelTable->setDisabled(true);
    m_pLabelTable->setDisabled(false);
}

void Worksheet::slotPrintBtnClick(void)
{
    Printer::getInstance()->setRowText(m_pLabelTable->item(0, 2)->text(),Printer::BARCODE_ROW1_TEXT);
    Printer::getInstance()->setRowText(m_pLabelTable->item(1, 2)->text(),Printer::BARCODE_ROW2_TEXT);
    Printer::getInstance()->setRowText(m_pLabelTable->item(2, 2)->text(),Printer::BARCODE_ROW3_TEXT);
    Printer::getInstance()->setRowText(m_pLabelTable->item(3, 2)->text(),Printer::BARCODE_ROW4_TEXT);
    Printer::getInstance()->setRowText(m_pLabelTable->item(4, 1)->text(),Printer::BARCODE_ROW5_TEXT);
    Printer::getInstance()->setRowText(m_pLabelTable->item(4, 3)->text(),Printer::BARCODE_ROW6_TEXT);
    qDebug() << CorrectionDialog::getInstance()->getPosX();
    qDebug() << CorrectionDialog::getInstance()->getPosY();
}

void Worksheet::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_P)
    {
        emit slotPrintBtnClick();
    }
}
