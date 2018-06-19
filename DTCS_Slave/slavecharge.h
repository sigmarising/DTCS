#ifndef SLAVECHARGE_H
#define SLAVECHARGE_H

#include <QWidget>
#include <QApplication>
#include <QMouseEvent>

#include "room.h"
#include "thread_one.h"
#include "thread_two.h"
#include "login2.h"

extern SLAVE * TSLAVE;

namespace Ui {
class Slavecharge;
}

class Slavecharge : public QWidget
{
    Q_OBJECT

public:
    explicit Slavecharge(QWidget *parent = 0);
    Thread_one theThreadOne;
    thread_two theThreadTwo;
    login2 T_login2;
    void startThread();
    bool onoff = false;
     QTimer * Ttimer = NULL;
     int tempchange = 0;
     int windchange = 0;

     void setAreaMovable(const QRect rt);

    ~Slavecharge();
public slots:
    void showstatus();
    void resquest();

private slots:
    void on_onoff_clicked();

    void on_TPU_clicked();

    void on_TPD_clicked();

    void on_WUP_clicked();

    void on_WDN_clicked();

    void on_quit_clicked();

    void on_season_clicked();

private:
    Ui::Slavecharge *ui;
    QRect m_areaMovable;//可移动的窗口区域
    bool m_bPressed;//鼠标按下的标志(不区分左右)
    QPoint m_qtPress;//鼠标按下的初始位置
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // SLAVECHARGE_H
