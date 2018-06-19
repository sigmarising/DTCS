#ifndef ROOM_H
#define ROOM_H

#include <QDialog>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QApplication>

namespace Ui {
class Room;
}

class Room : public QDialog
{
    Q_OBJECT

public:
    explicit Room(QWidget *parent = 0);
    ~Room();
     void setAreaMovable(const QRect rt);

private slots:
    void on_go_clicked();

    void on_quit_clicked();

private:
    Ui::Room *ui;
    QRect m_areaMovable;//可移动的窗口区域
    bool m_bPressed;//鼠标按下的标志(不区分左右)
    QPoint m_qtPress;//鼠标按下的初始位置
protected:
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

};

#endif // ROOM_H
