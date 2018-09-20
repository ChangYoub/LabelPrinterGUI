#ifndef CORRECTIONDIALOG_H
#define CORRECTIONDIALOG_H

#include <QDialog>

#define CORRECT_DIALOG_SIZE             QSize(300, 200)
#define POS_VALUE_SPIN_BOX_SIZE         QSize(100, 20)
#define POS_VALUE_SAVE_BTN_SIZE         QSize(70, 22)
#define CORRECT_DIALOG_VLAYOUT_MARGINS  QMargins(20, 20, 20, 10)

#define CORRECT_DIALOG_TITLE_TEXT       "위치보정"
#define X_POS_TITLE_TEXT                "X POS :"
#define Y_POS_TITLE_TEXT                "Y POS :"
#define CORRECT_DIALOG_SAVE_BTN_TEXT    "저장"

class QSpinBox;

class CorrectionDialog : public QDialog
{
    Q_OBJECT
public:
    CorrectionDialog(QWidget *parent = 0);

public:
    static CorrectionDialog *getInstance();

public:
    int getPosX(void) const;
    int getPosY(void) const;

private:
    void setSystemMenu(void);
    void setWorkSheet(void);

private:    
    QSpinBox *m_pXPosVal;
    QSpinBox *m_pYPosVal;

private:
    bool m_bMoving;
    QPoint m_pointLastMousePos;

private Q_SLOTS:
    void slotSaveClick(void);

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void showEvent(QShowEvent *);
};

#endif // CORRECTIONDIALOG_H
