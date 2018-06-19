#ifndef USERIN_H
#define USERIN_H

#include <QWidget>
#include "MASTER.h"
#include "login.h"
#include <QDialog>
#include <QApplication>
#include <QMouseEvent>
#include "stylesheet.h"

extern MASTER MY_MASTER;

namespace Ui {
class userin;
}

class userin : public QWidget
{
    Q_OBJECT

public:
    explicit userin(QWidget *parent = 0);
    ~userin();
    void setAreaMovable(const QRect rt);

private slots:
    void on_in_clicked();

    void on_quit_clicked();

private:
    Ui::userin *ui;
    QRect m_areaMovable;//可移动的窗口区域
    bool m_bPressed;//鼠标按下的标志(不区分左右)
    QPoint m_qtPress;//鼠标按下的初始位置
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // USERIN_H
