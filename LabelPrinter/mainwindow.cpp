#include "mainwindow.h"
#include "global.h"
#include "stylesheet.h"
#include "View/worksheet.h"
#include "View/Dialog/correctiondialog.h"
#include "Component/Xml/xml.h"
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QApplication>
#include <QKeyEvent>
#include <windows.h>
#include <windowsx.h>
#include <QStackedWidget>
#include <QAction>
#include <QMenuBar>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Xml::getInstance()->createSettingXml();
    m_pCorreDialog = new CorrectionDialog(this);
    this->setStyleSheet(DEFAULT_QSS);
    setWindoswSize();
    setSystemMenu();
    setMenuBarWidget();

    /* 메인 스텍위젯 설정 */
    m_pStackWidget = new QStackedWidget(this);
    m_worksheet = new Worksheet;
    m_pStackWidget->setGeometry(this->x(), (SYSTEM_BAR_HEIGHT+MENU_BAR_HEIGHT), this->width(), this->height() - (SYSTEM_BAR_HEIGHT+MENU_BAR_HEIGHT));
    m_pStackWidget->addWidget(m_worksheet);
    m_pStackWidget->setStyleSheet(STACK_WIDGET_QSS);
}

MainWindow::~MainWindow() {
}

void MainWindow::setWindoswSize(void)
{
    this->setMaximumSize(MAIN_WINDOW_SIZE);
    this->setMinimumSize(MAIN_MIN_SIZE);
    this->resize(MAIN_WINDOW_SIZE);
}

void MainWindow::setSystemMenu(void)
{
    /* 상단 시스템 메뉴 바 위젯 */
    m_pSysTemWidget = new QWidget(this);
    m_pSysTemWidget->resize(QSize(this->width(), SYSTEM_BAR_HEIGHT));
    m_pSysTemWidget->setStyleSheet(SYSTEM_MENU_QSS);

    /* 왼쪽 상단 회사로고 아이콘 */
    QLabel *pLogoIcon = new QLabel(m_pSysTemWidget);
    pLogoIcon->setFixedWidth(LOGO_ICON_WIDTH);
    pLogoIcon->setStyleSheet(LABEL_LOGO_ICON_QSS);

    /* 왼쪽 상단 회사로고 텍스트 */
    QLabel *pLogoText = new QLabel(SYSTEM_BAR_LOGO_LABLE_TEXT, m_pSysTemWidget);
    pLogoText->setStyleSheet(LABEL_LOGO_TEXT_QSS);

    /* 윈도우 최소화 버튼 */
    QPushButton *pMinWindowBtn = new QPushButton(this);
    pMinWindowBtn->setFocusPolicy(Qt::NoFocus);
    pMinWindowBtn->setFixedSize(SYSTEM_BAR_BTN_SIZE);
    pMinWindowBtn->setIcon(MINUS_ICON_PATH);
    pMinWindowBtn->setIconSize(SYSTEM_BAR_BTN_ICON_SIZE);
    pMinWindowBtn->setStyleSheet(SYSTEM_MENU_BTN_QSS);

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
    pSysTemLayout->addWidget(pLogoIcon, 1, Qt::AlignLeft);
    pSysTemLayout->addWidget(pLogoText, 20, Qt::AlignLeft);
    pSysTemLayout->addWidget(pMinWindowBtn);
    pSysTemLayout->addWidget(pQuitBtn);
    m_pSysTemWidget->setLayout(pSysTemLayout);

    QObject::connect(pMinWindowBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
    QObject::connect(pQuitBtn, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MainWindow::setMenuBarWidget(void)
{
    m_pMeunBarWidget = new QWidget(this);
    m_pMeunBarWidget->setGeometry(0, MENU_BAR_HEIGHT,this->width(), MENU_BAR_HEIGHT);
    m_pMeunBarWidget->setStyleSheet(SYSTEM_MENU_BAR_QSS);

    m_pMenuBar = new QMenuBar;
    m_pMenuBar->setStyleSheet(MENU_BAR_QSS);

    QMenu *pCorretionMenu = new QMenu(CORRE_MENU_TEXT, m_pMenuBar);
    pCorretionMenu->setFocusPolicy(Qt::NoFocus);
    pCorretionMenu->setStyleSheet(MENU_ITEM_QSS);

    m_pSlotCorre = new QAction(MENU_ACTION_CORRE_TEXT, this);
    m_pSlotCorre->setShortcut(QKeySequence::Copy);
    pCorretionMenu->addAction(m_pSlotCorre);

    QMenu *pSaveMenu = new QMenu(SAVE_MENU_TEXT, m_pMenuBar);
    pSaveMenu->setFocusPolicy(Qt::NoFocus);
    pSaveMenu->setStyleSheet(MENU_ITEM_QSS);

    m_pSlotSave = new QAction(MENU_ACTION_SAVE_TEXT, this);
    m_pSlotSave->setShortcut(QKeySequence::Save);
    pSaveMenu->addAction(m_pSlotSave);

    m_pMenuBar->addMenu(pCorretionMenu);
    m_pMenuBar->addMenu(pSaveMenu);

    QHBoxLayout *pHLayout = new QHBoxLayout(m_pMeunBarWidget);
    pHLayout->setContentsMargins(QMargins(10, 0, 0, 0));
    pHLayout->addWidget(m_pMenuBar, 0, Qt::AlignLeft|Qt::AlignVCenter);
    m_pMeunBarWidget->setLayout(pHLayout);

    QObject::connect(m_pSlotCorre, SIGNAL(triggered()), this, SLOT(slotCorreAction()));
    QObject::connect(m_pSlotSave, SIGNAL(triggered()), this, SLOT(slotSaveAction()));
}

void MainWindow::slotCorreAction(void)
{
    int centerX = this->geometry().center().x() - (m_pCorreDialog->width()/2);
    int centerY = this->geometry().center().y() - (m_pCorreDialog->height()/2);
    CorrectionDialog::getInstance()->move(centerX, centerY);
    CorrectionDialog::getInstance()->show();
}

void MainWindow::slotSaveAction(void)
{
    QStringList tableText;

    m_worksheet->clearTableFocus();

    for(int i = 0; m_worksheet->getTabalColumnMax() > i; i++) {
        if(m_worksheet->getTableText(i).isEmpty() == true) {
            tableText.append(XML_DEFAULT_VALUE);
        }
        else {
            tableText.append(m_worksheet->getTableText(i));
        }
    }

    Xml::getInstance()->writeXmlTableText(tableText);
}
/*!
 * \brief MainWindow::resizeEvent
 * \param event
 * Main Window resize Event
 */
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(event->type() == QResizeEvent::Resize)
    {
        m_pSysTemWidget->resize(QSize(this->width(), SYSTEM_BAR_HEIGHT));
        m_pMeunBarWidget->resize(QSize(this->width(), MENU_BAR_HEIGHT));
        m_pStackWidget->resize(this->width(), this->height()-(SYSTEM_BAR_HEIGHT+MENU_BAR_HEIGHT));
        m_worksheet->reSizeView(this->width(), this->height()-(SYSTEM_BAR_HEIGHT+MENU_BAR_HEIGHT));
    }
}

/*!
 * \brief MainWindow::nativeEvent
 * \param eventType, message, result
 * Main Window Size Setup Event
 */
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    MSG *msg = (MSG *)message;
    HWND hwnd = isVisible() ? (HWND)winId() : NULL;
    LPARAM lparam = msg->lParam;
    const LONG border_width = 4;
    RECT winrect;
    long x, y;

    switch (msg->message)
    {
        case WM_NCCALCSIZE:
            result = 0;
            return true;

        case WM_NCHITTEST:
            GetWindowRect(hwnd, &winrect);
            x = GET_X_LPARAM(lparam);
            y = GET_Y_LPARAM(lparam);
            if (x >= winrect.left  && x < winrect.left + border_width &&
                y < winrect.bottom && y >= winrect.bottom - border_width)
                *result = HTBOTTOMLEFT;
            else if (x < winrect.right  && x >= winrect.right - border_width &&
                     y < winrect.bottom && y >= winrect.bottom - border_width)
                *result = HTBOTTOMRIGHT;
            else if (x >= winrect.left && x < winrect.left + border_width &&
                     y >= winrect.top  && y < winrect.top + border_width)
                *result = HTTOPLEFT;
            else if (x < winrect.right && x >= winrect.right - border_width &&
                     y >= winrect.top  && y < winrect.top + border_width)
                *result = HTTOPRIGHT;
            else if (x >= winrect.left && x < winrect.left + border_width)
                *result = HTLEFT;
            else if (x < winrect.right && x >= winrect.right - border_width)
                *result = HTRIGHT;
            else if (y < winrect.bottom && y >= winrect.bottom - border_width)
                *result = HTBOTTOM;
            else if (y >= winrect.top && y < winrect.top + border_width)
                *result = HTTOP;
            else
                break;
            return true;
    }

    return QMainWindow::nativeEvent(eventType, message, result);
}

/*!
 * \brief MainWindow::mousePressEvent
 * \param event
 * Mouse Press Event
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bMoving = true;
        m_pointLastMousePos = event->pos();
    }
}

/*!
 * \brief MainWindow::mouseMoveEvent
 * \param event
 * Mouse Move Event
 */
void MainWindow::mouseMoveEvent(QMouseEvent *event)
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
 * \brief MainWindow::mouseReleaseEvent
 * \param event
 * Mouse Release Event
 */
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bMoving = false;
    }
}
