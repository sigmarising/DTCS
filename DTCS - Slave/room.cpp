#include "room.h"
#include "ui_room.h"
#include "stylesheet.h"

int TheRoomId;

Room::Room(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Room)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//北京透明
    m_areaMovable = geometry();
    m_bPressed = false;

    ui->go->setStyleSheet(QString(BUTTON_STYLESHEET(QPushButton,"#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB")));
    ui->quit->setStyleSheet("QPushButton{image: url(:/imgs/X2.png); background-color: rgb(255, 255, 255,0);\
            border-style:none;padding:10px;border-radius:19px;color:#FFFFFF}QPushButton:Hover{background-color: #EC7064;color:#FFF5E7;image: url(:/imgs/X2.png);}\
              QPushButton:Press{background-color:#DC2D1A;color: #F5A996};image: url(:/imgs/X2.png);");
    ui->roomid->setStyleSheet(QString(TXT_STYLESHEET(QLineEdit,"#DCE4EC", "#3498DB")));
    ui->label_2->setStyleSheet("image:url(:/imgs/logoin2.png)");
}

Room::~Room()
{
    delete ui;
}

void Room::on_go_clicked()
{
    QString RoomNumber = ui->roomid->text();
    TheRoomId = RoomNumber.toInt();
    accept();
}

void Room::on_quit_clicked()
{
    this->close();
}
void Room::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_qtPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_qtPress);
    }
}
void Room::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(pos() + e->pos() - m_qtPress);
    }
}
void Room::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}
void Room::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}
