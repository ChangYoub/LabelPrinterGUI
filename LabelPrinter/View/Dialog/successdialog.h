#ifndef SUCESSDIALOG_H
#define SUCESSDIALOG_H

#include <QDialog>

#define SUCCESS_DIALOG_ICON_WIDTH       50
#define SUCCESS_DIALOG_SIZE             QSize(300, 150)
#define SUCCESS_DIALOG_HLAYOUT_MARGINS  QMargins(10, 0, 0, 0)
#define SUCCESS_DIALOG_TITLE_TEXT       "Printer"

class QLabel;

class SuccessDialog : public QDialog
{
    Q_OBJECT
public:
    SuccessDialog(QWidget *parent = 0);

public:
    void setMsg(const QString);
    void setIcon(bool);

public:
    QLabel *m_pMsg;
    QPushButton *m_pOkBtn;

private:
    bool m_bMoving;
    QPoint m_pointLastMousePos;
    QLabel *m_pIconLable;

private:
    void setSystemMenu(void);
    void setWorkSheet(void);

protected:
    virtual void closeEvent (QCloseEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
};

#endif // SUCESSDIALOG_H
