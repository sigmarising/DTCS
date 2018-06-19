#ifndef GETREPORT_H
#define GETREPORT_H

#include <QWidget>
#include "login.h"
#include "MASTER.h"
#include <QDialog>
#include <QApplication>
#include <QMouseEvent>
#include "stylesheet.h"


extern MASTER MY_MASTER;

namespace Ui {
class GetReport;
}

class GetReport : public QWidget
{
    Q_OBJECT

public:
    explicit GetReport(QWidget *parent = 0);
    void showIT();
    ~GetReport();
     void setAreaMovable(const QRect rt);

private:
    Ui::GetReport *ui;
    QRect m_areaMovable;//可移动的窗口区域
    bool m_bPressed;//鼠标按下的标志(不区分左右)
    QPoint m_qtPress;//鼠标按下的初始位置
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void on_quit_clicked();
};

#endif // GETREPORT_H
