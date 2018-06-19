#include "login.h"
#include "ui_login.h"
#include "MASTER.h"

MASTER MY_MASTER;

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//北京透明
    m_areaMovable = geometry();
    m_bPressed = false;


    ui->Login->setStyleSheet(QString(BUTTON_STYLESHEET(QPushButton,"#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB")));
    ui->quit->setStyleSheet("QPushButton{image: url(:/imgs/X2.png); background-color: rgb(255, 255, 255,0);\
            border-style:none;padding:10px;border-radius:19px;color:#FFFFFF}QPushButton:Hover{background-color: #EC7064;color:#FFF5E7;image: url(:/imgs/X2.png);}\
              QPushButton:Press{background-color:#DC2D1A;color: #F5A996};image: url(:/imgs/X2.png);");
    ui->PSD ->setStyleSheet(QString(TXT_STYLESHEET(QLineEdit,"#DCE4EC", "#3498DB")));
    ui->label_2->setStyleSheet("image:url(:/imgs/logoin2.png)");

}

login::~login()
{
    this->close();
    delete ui;
}

void login::on_Login_clicked()
{
    QString PassWords = ui->PSD->text();
    if(PassWords == "admin")
    {
        accept();
    }
    else{
        QMessageBox message(QMessageBox::NoIcon,"Wrong","Wrong Password");
        message.exec();
        ui->PSD->clear();
    }
}

void login::on_quit_clicked()
{
    this->close();
}

void login::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_qtPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_qtPress);
    }
}
void login::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(pos() + e->pos() - m_qtPress);
    }
}
void login::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}
void login::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}

