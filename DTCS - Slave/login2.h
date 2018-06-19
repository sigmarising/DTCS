#ifndef LOGIN2_H
#define LOGIN2_H

#include <QDialog>
#include "SLAVE.h"
#include <QMessageBox>
#include <QApplication>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "stylesheet.h"

namespace Ui {
class login2;
}

class login2 : public QDialog
{
    Q_OBJECT

public:
    explicit login2(QWidget *parent = 0);
    ~login2();
    void setAreaMovable(const QRect rt);

private slots:
    void on_login_clicked();

    void on_quit_clicked();

private:
    Ui::login2 *ui;
    QRect m_areaMovable;//可移动的窗口区域
    bool m_bPressed;//鼠标按下的标志(不区分左右)
    QPoint m_qtPress;//鼠标按下的初始位置
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

};

#endif // LOGIN2_H
