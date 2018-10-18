#include "verdialog.h"
#include "stylesheet.h"
#include "global.h"

#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QKeyEvent>

VerDialog::VerDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setModal(true);
    this->setFixedSize(VER_DIALOG_SIZE);
    this->setStyleSheet(DIALOG_QSS);
    setSystemMenu();
    setWorkSheet();
}

void VerDialog::setSystemMenu(void)
{
    /* 상단 시스템 메뉴 바 위젯 */
    QWidget *pSysTemWidget = new QWidget(this);
    pSysTemWidget->resize(QSize(this->width(), SYSTEM_BAR_HEIGHT));
    pSysTemWidget->setStyleSheet(SYSTEM_MENU_QSS);

    /* 왼쪽 상단 회사로고 아이콘 */
    QLabel *pLogoIcon = new QLabel(pSysTemWidget);
    pLogoIcon->setFixedWidth(LOGO_ICON_WIDTH);
    pLogoIcon->setStyleSheet(LABEL_LOGO_ICON_QSS);

    QLabel *pTitleText = new QLabel(VER_DIALOG_TITLE_TEXT, pSysTemWidget);
    pTitleText->setStyleSheet(LABEL_TITLE_TEXT_QSS);

    /* 프로그램 종료 버튼 */
    QPushButton *pQuitBtn = new QPushButton(pSysTemWidget);
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
    pSysTemWidget->setLayout(pSysTemLayout);

    QObject::connect(pQuitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void VerDialog::setWorkSheet(void)
{
    QWidget *worksheet = new QWidget(this);
    worksheet->setGeometry(this->x(), SYSTEM_BAR_HEIGHT, this->width(), this->height()-SYSTEM_BAR_HEIGHT);
    worksheet->setStyleSheet(DIALOG_WIDGET_QSS);

    QLabel *titleMsg = new QLabel(worksheet);
    titleMsg->setAlignment(Qt::AlignCenter);
    titleMsg->setText(VER_DIALOG_MSG_TITLE);
    titleMsg->setStyleSheet(VER_DIALOG_TITLE_LABEL_QSS);

    QLabel *msg = new QLabel(worksheet);
    msg->setFixedHeight(VER_MSG_LABEL_HEIGHT);
    msg->setAlignment(Qt::AlignCenter);
    msg->setText(VER_DIALOG_MSG);
    msg->setStyleSheet(VER_DIALOG_MSG_LABEL_QSS);

    QVBoxLayout *pVLayout = new QVBoxLayout;
    pVLayout->setContentsMargins(VER_DIALOG_VLAYOUT_MARGINS);
    pVLayout->setSpacing(0);
    pVLayout->addWidget(titleMsg, 0, Qt::AlignCenter);
    pVLayout->addWidget(msg);

    worksheet->setLayout(pVLayout);
}

void VerDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        case Qt::Key_Space:
        case Qt::Key_Escape:
            this->close();
            break;
    }
}

void VerDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bMoving = true;
        m_pointLastMousePos = event->pos();
    }
}

void VerDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons().testFlag(Qt::LeftButton) && m_bMoving)
    {
        if (m_pointLastMousePos.y() < MOUSE_MOVE_AREA)
        {
            this->move(this->pos() + (event->pos() - m_pointLastMousePos));
        }
    }
}

void VerDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bMoving = false;
    }
}

