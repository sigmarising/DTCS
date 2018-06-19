#include "userin.h"
#include "ui_userin.h"

userin::userin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userin)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//北京透明
    m_areaMovable = geometry();
    m_bPressed = false;

    ui->label_3->setStyleSheet("image: url(E:/DTCS-master/imgs/user.png);");
    ui->in->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996"));
    ui->quit->setStyleSheet("QPushButton{image: url(E:/DTCS-master/imgs/X2.png); background-color: rgb(255, 255, 255,0);\
            border-style:none;padding:10px;border-radius:19px;color:#FFFFFF}QPushButton:Hover{background-color: #EC7064;color:#FFF5E7;image: url(E:/DTCS-master/imgs/X2.png);}\
              QPushButton:Press{background-color:#DC2D1A;color: #F5A996};image: url(E:/DTCS-master/imgs/X2.png);");
    ui->roomid->setStyleSheet(QString(TXT_STYLESHEET(QLineEdit,"#DCE4EC", "#3498DB")));
    ui->userid ->setStyleSheet(QString(TXT_STYLESHEET(QLineEdit,"#DCE4EC", "#3498DB")));
}

userin::~userin()
{
    delete ui;
}

void userin::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_qtPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_qtPress);
    }
}
void userin::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(pos() + e->pos() - m_qtPress);
    }
}
void userin::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}

void userin::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}

void userin::on_in_clicked()
{
    QString roomid = ui->roomid->text();
    QString userid = ui->userid->text();
    if(roomid!=""&&userid!="")
    {
        if(MY_MASTER.f_user_in((roomid.toInt()),(userid.toStdString())))
        {
            QMessageBox message(QMessageBox::NoIcon,"Ok","user in");
            message.exec();
            this->close();
        }else
        {
            QMessageBox message(QMessageBox::NoIcon,"Wrong","noChange");
            message.exec();
            ui->roomid->clear();
            ui->userid->clear();
        }
    }else
    {
        QMessageBox message(QMessageBox::NoIcon,"Wrong","Don't be empty");
        message.exec();
        ui->roomid->clear();
        ui->userid->clear();
    }


}

void userin::on_quit_clicked()
{
    this->close();
}
