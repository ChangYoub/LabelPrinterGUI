#include "correctiondialog.h"
#include "stylesheet.h"
#include "global.h"
#include "Component/Xml/xml.h"
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QKeyEvent>
#include <QSpinBox>
#include <QCoreApplication>

#include <QDebug>

Q_GLOBAL_STATIC(CorrectionDialog, _CorrectionDialog)


CorrectionDialog::CorrectionDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setModal(true);
    this->setFixedSize(CORRECT_DIALOG_SIZE);
    this->setStyleSheet(CORRECT_DIALOG_QSS);
    setSystemMenu();
    setWorkSheet();
}

CorrectionDialog *CorrectionDialog::getInstance(void)
{
    return _CorrectionDialog();
}


void CorrectionDialog::setSystemMenu(void)
{
    /* 상단 시스템 메뉴 바 위젯 */
    m_pSysTemWidget = new QWidget(this);
    m_pSysTemWidget->resize(QSize(this->width(), SYSTEM_BAR_HEIGHT));
    m_pSysTemWidget->setStyleSheet(SYSTEM_MENU_QSS);

    /* 왼쪽 상단 회사로고 아이콘 */
    QLabel *pLogoIcon = new QLabel(m_pSysTemWidget);
    pLogoIcon->setFixedWidth(LOGO_ICON_WIDTH);
    pLogoIcon->setStyleSheet(LABEL_LOGO_ICON_QSS);

    QLabel *pTitleText = new QLabel(CORRECT_DIALOG_TITLE_TEXT, m_pSysTemWidget);
    pTitleText->setStyleSheet(LABEL_TITLE_TEXT_QSS);

    /* 프로그램 종료 버튼 */
    QPushButton *pQuitBtn = new QPushButton(m_pSysTemWidget);
    pQuitBtn->setFocusPolicy(Qt::NoFocus);
    pQuitBtn->setFixedSize(SYSTEM_BAR_BTN_SIZE);
    pQuitBtn->setIcon(X_MARK_ICON_PATH);
    pQuitBtn->setIconSize(SYSTEM_BAR_BTN_ICON_SIZE);
    pQuitBtn->setStyleSheet(SYSTEM_MENU_QUIT_BTN_QSS);

    /* 수평 레이아웃 설정 */
    QHBoxLayout * pSysTemLayout = new QHBoxLayout;
    pSysTemLayout->setAlignment(Qt::AlignRight);
    pSysTemLayout->setContentsMargins(SYSTEN_BAR_LAYOUT_MARGIN);
    pSysTemLayout->setSpacing(0);
    pSysTemLayout->addWidget(pLogoIcon, 0, Qt::AlignLeft);
    pSysTemLayout->addSpacing(7);
    pSysTemLayout->addWidget(pTitleText, 1, Qt::AlignLeft);
    pSysTemLayout->addWidget(pQuitBtn);
    m_pSysTemWidget->setLayout(pSysTemLayout);

    QObject::connect(pQuitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void CorrectionDialog::setWorkSheet(void)
{
    QWidget *worksheet = new QWidget(this);
    worksheet->setGeometry(this->x(), SYSTEM_BAR_HEIGHT, this->width(), this->height()-SYSTEM_BAR_HEIGHT);
    worksheet->setStyleSheet(CORRECT_DIALOG_WIDGET_QSS);

    QLabel *xText = new QLabel(this);
    xText->setText(X_POS_TITLE_TEXT);
    xText->setStyleSheet(CORRECT_DIALOG_LABEL_QSS);

    m_pXPosVal = new QSpinBox(this);
    m_pXPosVal->setFixedSize(POS_VALUE_SPIN_BOX_SIZE);
    m_pXPosVal->setStyleSheet(POS_SPIN_BOX_QSS);
    m_pXPosVal->setValue(Xml::getInstance()->getXmlPosX());

    QLabel *yText = new QLabel(this);
    yText->setText(Y_POS_TITLE_TEXT);
    yText->setStyleSheet(CORRECT_DIALOG_LABEL_QSS);

    m_pYPosVal = new QSpinBox(this);
    m_pYPosVal->setFixedSize(POS_VALUE_SPIN_BOX_SIZE);
    m_pYPosVal->setStyleSheet(POS_SPIN_BOX_QSS);
    m_pYPosVal->setValue(Xml::getInstance()->getXmlPosY());

    QGridLayout *pGridLayout = new QGridLayout;
    pGridLayout->setAlignment(Qt::AlignCenter);
    pGridLayout->addWidget(xText,   0, 0);
    pGridLayout->addWidget(m_pXPosVal, 0, 1);
    pGridLayout->addWidget(yText,   1, 0);
    pGridLayout->addWidget(m_pYPosVal, 1, 1);

    QPushButton *pSaveBtn = new QPushButton(CORRECT_DIALOG_SAVE_BTN_TEXT, this);
    pSaveBtn->setFixedSize(POS_VALUE_SAVE_BTN_SIZE);
    pSaveBtn->setStyleSheet(DIALOG_SAVE_BTN_QSS);

    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->setContentsMargins(CORRECT_DIALOG_VLAYOUT_MARGINS);
    pVLayout->addSpacing(8);
    pVLayout->addLayout(pGridLayout);
    pVLayout->addWidget(pSaveBtn, 0, Qt::AlignRight);
    this->setLayout(pVLayout);

    QObject::connect(pSaveBtn,  SIGNAL(clicked()), this, SLOT(slotSaveClick()));
}

int CorrectionDialog::getPosX(void) const
{
    return m_pXPosVal->value();
}

int CorrectionDialog::getPosY(void) const
{
    return m_pYPosVal->value();
}

void CorrectionDialog::slotSaveClick(void)
{
    Xml::getInstance()->writeXmlPos(QString::number(m_pXPosVal->value()), QString::number(m_pYPosVal->value()));
    this->close();
}

void CorrectionDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S) {
        emit slotSaveClick();
    }
    else if(event->key() == Qt::Key_Escape) {
        this->close();
    }
}

void CorrectionDialog::showEvent(QShowEvent *)
{
    m_pXPosVal->setValue(Xml::getInstance()->getXmlPosX());
    m_pYPosVal->setValue(Xml::getInstance()->getXmlPosY());
}

/*!
 * \brief CorrectionDialog::mousePressEvent
 * \param event
 * Mouse Press Event
 */
void CorrectionDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bMoving = true;
        m_pointLastMousePos = event->pos();
    }
}

/*!
 * \brief CorrectionDialog::mouseMoveEvent
 * \param event
 * Mouse Move Event
 */
void CorrectionDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons().testFlag(Qt::LeftButton) && m_bMoving)
    {
        if (m_pointLastMousePos.y() < MOUSE_MOVE_AREA)
        {
            this->move(this->pos() + (event->pos() - m_pointLastMousePos));
        }
    }
}

/*!
 * \brief CorrectionDialog::mouseReleaseEvent
 * \param event
 * Mouse Release Event
 */
void CorrectionDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bMoving = false;
    }
}
