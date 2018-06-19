#include "maincharge.h"
#include "ui_maincharge.h"
#include "MASTER.h"


MainCharge::MainCharge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainCharge)
{  
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//北京透明
    m_areaMovable = geometry();
    m_bPressed = false;

    ui->label->setStyleSheet("image: url(E:/DTCS-master/imgs/Mbg3.png);");
    ui->userinout ->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6"));
    ui->userout->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6"));
    ui->modelC->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1"));
    ui->report->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1"));
    ui->onoff->setStyleSheet(BUTTON_STYLESHEET(QPushButton,"#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996"));
    ui->quit->setStyleSheet("QPushButton{image: url(E:/DTCS-master/imgs/X2.png); background-color: rgb(255, 255, 255,0);\
            border-style:none;padding:10px;border-radius:19px;color:#FFFFFF}QPushButton:Hover{background-color: #EC7064;color:#FFF5E7;image: url(E:/DTCS-master/imgs/X2.png);}\
              QPushButton:Press{background-color:#DC2D1A;color: #F5A996};image: url(E:/DTCS-master/imgs/X2.png);");
    ui->theFre->setStyleSheet(QString(TXT_STYLESHEET(QLineEdit,"#DCE4EC", "#3498DB")));
    ui->themodel->setStyleSheet(QString(TXT_STYLESHEET(QLineEdit,"#DCE4EC", "#3498DB")));
    ui->status->setStyleSheet(QString((TXTs_STYLESHEET(QTextEdit,"#DCE4EC", "#3498DB"))));
    this->statuShow();
}

MainCharge::~MainCharge()
{ 
    thread_1.exit();
    thread_2.exit();
    QTime reachtime = QTime::currentTime().addMSecs(40);
    while(QTime::currentTime() < reachtime)
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    delete ui;
}


void MainCharge::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_qtPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_qtPress);
    }
}
void MainCharge::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(pos() + e->pos() - m_qtPress);
    }
}
void MainCharge::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}

void MainCharge::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}


void MainCharge::threadstart()
{
    thread_1.start();
    thread_2.start();
    QTimer * theTimer = new QTimer(this);
    connect(theTimer,&QTimer::timeout,this,&MainCharge::autoRefresh);
    theTimer->start(1000);
}

void MainCharge::on_quit_clicked()
{
    this->close();
}

void MainCharge::statuShow()
{
    int model = MY_MASTER.f_get_mode();
    int fre = MY_MASTER.f_get_frequent();
    QString mode = QString::number(model,10);
    QString Frequency = QString::number(fre,10);
    ui->theFre->setText(Frequency);
    if(model == 0)
    {
        ui->themodel->setText("Mode Cold");
    }
    else
    {
        ui->themodel->setText("Mode Hot");
    }
    if(this->onff)
    {
        ui->onoff->setText("ON/off");
    }
    else
    {
        ui->onoff->setText("OFF/on");
    }

    QString allstatues = "|Room_id\t|wind_speed\t|temp_target\t|temp_now\t|energy\t|amount\n";

    int i = MY_MASTER.m_miniDB.size();
    for(int j = 0 ; j < i ; j ++)
    {
        int mid = MY_MASTER.m_miniDB[j].m_id;
        int mwindspeed = MY_MASTER.m_miniDB[j].m_wind_speed;
        int mtemptarget = MY_MASTER.m_miniDB[j].m_temp_target;
        int mtempnow = MY_MASTER.m_miniDB[j].m_temp_now;
        double menergy = MY_MASTER.m_miniDB[j].m_energy;
        double mamount = MY_MASTER.m_miniDB[j].m_amount;

        QString i1 = QString::number(mid,10);
        QString i2 = QString::number(mwindspeed,10);
        QString i3 = QString::number(mtemptarget,10);
        QString i4 = QString::number(mtempnow,10);
        QString i5 = QString::number(menergy,10,3);
        QString i6 = QString::number(mamount,10,3);

        allstatues.append("|"+i1+"\t|"+i2+"\t|"+i3+"\t|"+i4+"\t|"+i5+"\t|"+i6+"\n");
    ui->status->setText(allstatues);

    }
    ui->status->setText(allstatues);
}

void MainCharge::on_modelC_clicked()
{
    if(this->model)
    {

        this->model = false;
        if(MY_MASTER.f_set_mode(this->model)&&MY_MASTER.f_set_frequent_ms((ui->theFre->text().toInt())))
        {
            QMessageBox message(QMessageBox::NoIcon,"OK","Model Change Success");
            message.exec();

        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon,"WRONG","Change Failed");
            message.exec();
            this->model = true;
        }

    }
    else
    {
        this->model = true;
        if(MY_MASTER.f_set_mode(this->model)&&MY_MASTER.f_set_frequent_ms((ui->theFre->text().toInt())))
        {
            QMessageBox message(QMessageBox::NoIcon,"OK","Model Change Success");
            message.exec();

        }
        else
        {
            QMessageBox message(QMessageBox::NoIcon,"WRONG","Change Failed");
            message.exec();
            this->model = false;
        }
    }

   this->statuShow();
}

void MainCharge::on_onoff_clicked()
{
    if(this->onff)
        if(MY_MASTER.f_set_switch_off())
        {
            this->onff = false;
            ui->onoff->setText("OFF/on");
        }else
        {
            QMessageBox message(QMessageBox::NoIcon,"Wrong","Check Your Connect");
            message.exec();
        }
    else
    {

        if(MY_MASTER.f_set_switch_on())
        {
            this->onff = true;
            ui->onoff->setText("ON/off");
        }else{
            QMessageBox message(QMessageBox::NoIcon,"Wrong","Check Your Connect");
            message.exec();
        }
    }
}

void MainCharge::on_userinout_clicked()
{
    this->User_in.show();
}



void MainCharge::on_userout_clicked()
{
    this->User_Out.show();
}

void MainCharge::on_report_clicked()
{
    qDebug()<<"in"<<endl;
    if(MY_MASTER.f_report())
    {
        qDebug()<<MY_MASTER.m_Report.v_Week.size();
         this->TheReport.show();
          TheReport.showIT();
    }
}
void MainCharge::autoRefresh()
{
    QString allstatues = "|Room_id\t|wind_speed\t|temp_target\t|temp_now\t|energy\t|amount\n";

    int i = MY_MASTER.m_miniDB.size();
    for(int j = 0 ; j < i ; j ++)
    {
        int mid = MY_MASTER.m_miniDB[j].m_id;
        int mwindspeed = MY_MASTER.m_miniDB[j].m_wind_speed;
        int mtemptarget = MY_MASTER.m_miniDB[j].m_temp_target;
        int mtempnow = MY_MASTER.m_miniDB[j].m_temp_now;
        double menergy = MY_MASTER.m_miniDB[j].m_energy;
        double mamount = MY_MASTER.m_miniDB[j].m_amount;

        QString i1 = QString::number(mid,10);
        QString i2 = QString::number(mwindspeed,10);
        QString i3 = QString::number(mtemptarget,10);
        QString i4 = QString::number(mtempnow,10);
        QString i5 = QString::number(menergy,10,3);
        QString i6 = QString::number(mamount,10,3);

        allstatues.append("|"+i1+"\t|"+i2+"\t|"+i3+"\t|"+i4+"\t|"+i5+"\t|"+i6+"\n");
    ui->status->setText(allstatues);

    }
    ui->status->setText(allstatues);
}
