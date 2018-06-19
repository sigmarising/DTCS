#ifndef USEROUT_H
#define USEROUT_H

#include <QWidget>
#include "login.h"
#include "MASTER.h"
#include <QDialog>
#include <QApplication>
#include <QMouseEvent>
#include "stylesheet.h"


extern MASTER MY_MASTER;

namespace Ui {
class userout;
}

class userout : public QWidget
{
    Q_OBJECT

public:
    explicit userout(QWidget *parent = 0);
    ~userout();
    void setAreaMovable(const QRect rt);

private slots:
    void on_user_out_clicked();

    void on_quit_clicked();

private:
    Ui::userout *ui;
    QRect m_areaMovable;//可移动的窗口区域
    bool m_bPressed;//鼠标按下的标志(不区分左右)
    QPoint m_qtPress;//鼠标按下的初始位置
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // USEROUT_H
