#ifndef VERDIALOG_H
#define VERDIALOG_H

#include <QDialog>

#define VER_MSG_LABEL_HEIGHT        170
#define VER_DIALOG_VLAYOUT_MARGINS  QMargins(10, 10, 10, 10)
#define VER_DIALOG_SIZE             QSize(350, 250)

#define VER_DIALOG_TITLE_TEXT       "버전정보"
#define VER_DIALOG_MSG_TITLE        "Zebera Printer Support Software.\n"\
                                    "Version 0.0.2"
#define VER_DIALOG_MSG              "Copyright © 2018 Layer System Co., Ltd\n"\
                                    "All Rights Reserved.\n"\
                                    "Build info Qt 5.8.0 MinGW 32bit GPL license.\n"\
                                    "Program by Chang Youb Lim\n"\
                                    "Technical support Email Kerberos1057@gmail.com"

class VerDialog : public QDialog
{
    Q_OBJECT
public:
    VerDialog(QWidget *parent = 0);

private:
    bool m_bMoving;
    QPoint m_pointLastMousePos;

private:
    void setSystemMenu(void);
    void setWorkSheet(void);

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
};

#endif // VERDIALOG_H
