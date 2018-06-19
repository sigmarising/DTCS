#ifndef MAINCHARGE_H
#define MAINCHARGE_H

#include <QWidget>
#include "MASTER.h"
#include <QThread>
#include <QTimer>
#include <QApplication>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "stylesheet.h"


#include "thread_one.h"
#include "thread_two.h"
#include "login.h"
#include "Public_Define.h"
#include "userin.h"
#include "userout.h"
#include "getreport.h"


extern MASTER MY_MASTER;

namespace Ui {
class MainCharge;
}

class MainCharge : public QWidget
{
    Q_OBJECT

public:
    explicit MainCharge(QWidget *parent = 0);
    thread_one thread_1;
    thread_two thread_2;
    void statuShow();
    bool onff = false;
    void threadstart();
    bool model = false;
    void setAreaMovable(const QRect rt);

    ~MainCharge();

private slots:
    void on_quit_clicked();

    void on_modelC_clicked();

    void on_onoff_clicked();

    void on_userinout_clicked();

    void on_userout_clicked();

    void on_report_clicked();
    void autoRefresh();

private:
    Ui::MainCharge *ui;
    userin User_in;
    userout User_Out;
    GetReport TheReport;
    QRect m_areaMovable;//可移动的窗口区域
    bool m_bPressed;//鼠标按下的标志(不区分左右)
    QPoint m_qtPress;//鼠标按下的初始位置
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);




};

#endif // MAINCHARGE_H
