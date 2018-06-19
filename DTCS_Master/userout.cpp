#include "userout.h"
#include "ui_userout.h"

userout::userout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userout)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//北京透明
    m_areaMovable = geometry();
    m_bPressed = false;

    ui->label_2->setStyleSheet("image: url(:/imgs/user.png);");
    ui->user_out->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996"));
    ui->quit->setStyleSheet("QPushButton{image: url(:/imgs/X2.png); background-color: rgb(255, 255, 255,0);\
            border-style:none;padding:10px;border-radius:19px;color:#FFFFFF}QPushButton:Hover{background-color: #EC7064;color:#FFF5E7;image: url(:/imgs/X2.png);}\
              QPushButton:Press{background-color:#DC2D1A;color: #F5A996};image: url(:/imgs/X2.png);");
    ui->roomid->setStyleSheet(QString(TXT_STYLESHEET(QLineEdit,"#DCE4EC", "#3498DB")));
}

userout::~userout()
{
    delete ui;
}

void userout::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_qtPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_qtPress);
    }
}
void userout::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(pos() + e->pos() - m_qtPress);
    }
}
void userout::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}

void userout::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}
void userout::on_user_out_clicked()
{
    int roomid = ui->roomid->text().toInt();
    if(ui->roomid->text()!="")
    {
        if(MY_MASTER.f_user_out(roomid))
        {
            QMessageBox message(QMessageBox::NoIcon,"Ok","Uesr Out");
            message.exec();
            this->close();
        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon,"Wrong","Out Failed");
            message.exec();
            ui->roomid->clear();
        }
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon,"Wrong","Empty Roomid");
        message.exec();
    }

}

void userout::on_quit_clicked()
{
    this->close();
}
