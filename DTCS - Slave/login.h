#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include "MASTER.h"
#include <QApplication>
#include <QMouseEvent>
#include "stylesheet.h"



namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    void setAreaMovable(const QRect rt);

private slots:
    void on_Login_clicked();

    void on_quit_clicked();

private:
    Ui::login *ui;
    QRect m_areaMovable;//可移动的窗口区域
    bool m_bPressed;//鼠标按下的标志(不区分左右)
    QPoint m_qtPress;//鼠标按下的初始位置
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // LOGIN_H
