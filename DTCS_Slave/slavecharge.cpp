#include "slavecharge.h"
#include "ui_slavecharge.h"

Slavecharge::Slavecharge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slavecharge)
{
    ui->setupUi(this);

    if(g_season == SEASON_SUMMER)
    {
        ui->season->setText("SUMMER");
        g_season = SEASON_WINTER;
        ui->label_8->setText("WINTER");
    }
    else
    {
        ui->season->setText("WINTER");
        g_season = SEASON_SUMMER;
        ui->label_8->setText("SUMMER");
    }

    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//北京透明
    m_areaMovable = geometry();
    m_bPressed = false;

    ui->season->setStyleSheet(BUTTON_STYLESHEET2(QPushButton,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1"));
    ui->WUP->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6"));
    ui->WDN->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6"));
    ui->TPU->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1"));
    ui->TPD->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1"));
    ui->onoff->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996"));
    ui->quit->setStyleSheet("QPushButton{image: url(:/imgs/X2.png); background-color: rgb(255, 255, 255,0);\
            border-style:none;padding:10px;border-radius:19px;color:#FFFFFF}QPushButton:Hover{background-color: #EC7064;color:#FFF5E7;image: url(:/imgs/X2.png);}\
              QPushButton:Press{background-color:#DC2D1A;color: #F5A996};image: url(:/imgs/X2.png);");
    ui->label_6->setStyleSheet("image:url(:/imgs/bg5.png)");

}

Slavecharge::~Slavecharge()
{
    theThreadOne.exit();
    theThreadTwo.exit();
    QTime reachtime = QTime::currentTime().addMSecs(40);
    while(QTime::currentTime() < reachtime)
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);

    delete ui;
}


void Slavecharge::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_qtPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_qtPress);
    }
}
void Slavecharge::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(pos() + e->pos() - m_qtPress);
    }
}
void Slavecharge::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}

void Slavecharge::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}

void Slavecharge::startThread()
{
    theThreadOne.start();
    theThreadTwo.start();
    QTimer * timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Slavecharge::showstatus);
    timer->start(10);
}
void Slavecharge::showstatus()
{
    //ui->of->setText(QString::number(TSLAVE->f_get_switch()));
    if(TSLAVE->f_get_switch() == SWITCH_OFF)
    {
        ui->TPD->setEnabled(false);
        ui->TPU->setEnabled(false);
        ui->WDN->setEnabled(false);
        ui->WUP->setEnabled(false);
    }else
    {
        ui->TPD->setEnabled(true);
        ui->TPU->setEnabled(true);
        ui->WDN->setEnabled(true);
        ui->WUP->setEnabled(true);
    }
    ui->label->setText("Room:" + QString::number(TSLAVE->f_get_roomID()));
    int target = TSLAVE->f_get_temp_target();
    if(target <= 25)
        ui->WorkModel->setText("COLD WIND");
    else
        ui->WorkModel->setText("WARM WIND");
    ui->showAmount->display(QString::number(TSLAVE->f_get_Amount(),10,1));
    ui->showEnergy->display(QString::number(TSLAVE->f_get_Energy(),10,1));
    ui->tempNow->display(QString::number(TSLAVE->f_get_temp_now(),10,1));
    ui->showTemp->display(QString::number(TSLAVE->f_get_temp_target()));
    ui->showWind->display(QString::number(TSLAVE->f_get_wind()));
  //  qDebug()<<"Show"<<endl;
}

void Slavecharge::on_onoff_clicked()
{
    if(this->onoff)
    {
        if(TSLAVE->f_switch_off())
        {
            ui->onoff->setText("OFF/on");
            this->onoff = false;
            ui->TPD->setEnabled(false);
            ui->TPU->setEnabled(false);
            ui->WDN->setEnabled(false);
            ui->WUP->setEnabled(false);
        }

    }
    else
    {
        if(TSLAVE->f_switch_on())
        {
            ui->onoff->setText("ON/off");
            this->onoff = true;
            ui->TPD->setEnabled(true);
            ui->TPU->setEnabled(true);
            ui->WDN->setEnabled(true);
            ui->WUP->setEnabled(true);
        }
    }

   // ui->show->setText(QString::number(TSLAVE->f_get_switch()));
}

void Slavecharge::on_TPU_clicked()
{
    delete Ttimer;
    Ttimer = new QTimer(this);
    this->tempchange ++;
    connect(this->Ttimer,&QTimer::timeout,this,&Slavecharge::resquest);
    Ttimer->start(1000);

}


void Slavecharge::on_TPD_clicked()
{
    delete Ttimer;
    Ttimer = new QTimer(this);
    this->tempchange --;
    connect(this->Ttimer,&QTimer::timeout,this,&Slavecharge::resquest);
    Ttimer->start(1000);
}


void Slavecharge::on_WUP_clicked()
{
    qDebug()<<"Clicked"<<endl;
    delete Ttimer;
    Ttimer = new QTimer(this);
    this->windchange ++;
    connect(this->Ttimer,&QTimer::timeout,this,&Slavecharge::resquest);
    Ttimer->start(1000);
    qDebug()<<"WindUp"<<endl;
}



void Slavecharge::on_WDN_clicked()
{
    delete Ttimer;
    Ttimer = new QTimer(this);
    this->windchange --;
    connect(this->Ttimer,&QTimer::timeout,this,&Slavecharge::resquest);
    Ttimer->start(1000);
}

void Slavecharge::resquest()
{
    delete Ttimer;
    qDebug()<<"in"<<endl;
    int windS = TSLAVE->f_get_wind();
        qDebug()<<"get wind"<<endl;
    int tempC = TSLAVE->f_get_temp_target();
        qDebug()<<"get temp"<<endl;
    windS+=this->windchange;
    tempC+=this->tempchange;
    if(TSLAVE->f_adjust_temp(tempC) )
    {
        QMessageBox message(QMessageBox::NoIcon,"ok","tempC");
        message.exec();
    }
    if(TSLAVE->f_adjust_wind(windS))
    {
        QMessageBox message(QMessageBox::NoIcon,"ok","windC");
        message.exec();
    }
    this->windchange = 0;
    this->tempchange = 0;

    Ttimer = new QTimer(this);
}

void Slavecharge::on_quit_clicked()
{
    this->close();
}

void Slavecharge::on_season_clicked()
{
    if(g_season == SEASON_SUMMER)
    {
        ui->season->setText("SUMMER");
        g_season = SEASON_WINTER;
        ui->label_8->setText("WINTER");
    }
    else
    {
        ui->season->setText("WINTER");
        g_season = SEASON_SUMMER;
        ui->label_8->setText("SUMMER");
    }

}
