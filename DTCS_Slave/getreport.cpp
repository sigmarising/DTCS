#include "getreport.h"
#include "ui_getreport.h"
#include <QStandardItemModel>


GetReport::GetReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetReport)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//北京透明
    m_areaMovable = geometry();
    m_bPressed = false;

    ui->quit->setStyleSheet("QPushButton{image: url(E:/DTCS-master/imgs/X2.png); background-color: rgb(255, 255, 255,0);\
            border-style:none;padding:10px;border-radius:19px;color:#FFFFFF}QPushButton:Hover{background-color: #EC7064;color:#FFF5E7;image: url(E:/DTCS-master/imgs/X2.png);}\
              QPushButton:Press{background-color:#DC2D1A;color: #F5A996};image: url(E:/DTCS-master/imgs/X2.png);");
    ui->label->setStyleSheet("image: url(E:/DTCS-master/imgs/report.png);");
    ui->treeView->setStyleSheet(QString(TXTs_STYLESHEET(QTreeView,"#DCE4EC", "#3498DB")));

}

GetReport::~GetReport()
{
    delete ui;
}


void GetReport::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_qtPress = e->pos();
        m_bPressed = m_areaMovable.contains(m_qtPress);
    }
}
void GetReport::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        move(pos() + e->pos() - m_qtPress);
    }
}
void GetReport::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
}

void GetReport::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}

void GetReport::showIT()
{

    QStandardItemModel * model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QString("Reports")<<QString("Message"));

    QStandardItem* mR = new QStandardItem(QString("MonthRPT"));
    model->appendRow(mR);
    QString out1 = "Amount : "+QString::number(MY_MASTER.m_Report.get_Amount())+"\nEnergy : "+QString::number(MY_MASTER.m_Report.get_Energy());
    model->setItem(model->indexFromItem(mR).row(),1,new QStandardItem(out1));
//    qDebug()<<"THE"+MY_MASTER.m_Report.v_Week.size();

    for(int i = 0 ; i < MY_MASTER.m_Report.v_Week.size() ; i++)
    {
        //qDebug()<<i;
        QStandardItem * wR = new QStandardItem(QString("Week_" + QString::number(i) + " RPT"));
        mR->appendRow(wR);
        for(int j = 0 ; j <MY_MASTER.m_Report.v_Week[i].v_Day.size() ; j ++)
        {
           // QString out2 ="Amount : " + QString::number(MY_MASTER.m_Report.v_Week[i].get_Amount()) + "\nEngry : "+ QString::number(MY_MASTER.m_Report.v_Week[i].get_Energy());
            QString out2 = "Day " + MY_MASTER.m_Report.v_Week[i].v_Day[j].get_Day().toString() + " RPT";
            QStandardItem * dR = new QStandardItem(out2);
            wR->appendRow(dR);
            for(int k = 0 ; k < MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room.size();k++)
            {
                QString out3 = "RoomId : " + QString::number(MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].get_RoomID())+ " RPT";
                QStandardItem * rR = new QStandardItem(out3);
                dR->appendRow(rR);
                for(int l = 0 ; l <MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].v_Record.size(); l ++)
                {
                    QString out3 = "Record_" + QString::number(l) + " RPT";
                    QStandardItem * rdR = new QStandardItem(out3);
                    rR->appendRow(rdR);
                    QString out4 ="Amount : " + QString::number( MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].v_Record[l].get_Amount())
                            +"\nEnergy : " +  QString::number( MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].v_Record[l].get_Energy()) +
                            "\nStart Time : "  + (MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].v_Record[l].get_Time_Start()).toString()
                            + "\nEnd Time : " + (MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].v_Record[l].get_Time_End()).toString() +
                            "\nStart Temp : " + QString::number( MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].v_Record[l].get_Temp_Start())
                            + "\nEnd Temp : " + QString::number( MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].v_Record[l].get_Temp_End())
                            + "\nTarget Temp : " + QString::number( MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].v_Record[l].get_Temp_Target());
                    rR->setChild(rdR->index().row(),1,new QStandardItem(out4));

                }
                QString out5 = "SWith Time : " + QString::number(MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].get_SwitchTimes())
                        +"\nAmount : "+QString::number(MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].get_Amount())+
                         "\nEnergy : "+QString::number(MY_MASTER.m_Report.v_Week[i].v_Day[j].v_Room[k].get_Energy());
                dR->setChild(rR->index().row(),1,new QStandardItem(out5));
            }
            QString out6 = "Amount : " + QString::number(MY_MASTER.m_Report.v_Week[i].v_Day[j].get_Amount())+
                    "\nEnergy : " + QString::number(MY_MASTER.m_Report.v_Week[i].v_Day[j].get_Energy());
            wR->setChild(dR->index().row(),1,new QStandardItem(out6));

        }
        QString out7 = "Day start : " + MY_MASTER.m_Report.v_Week[i].get_Day_Start().toString() +
                    "\nDay End : " + MY_MASTER.m_Report.v_Week[i].get_Day_End().toString() +
                    "\nAmount : " +QString::number( MY_MASTER.m_Report.v_Week[i].get_Amount())+
                    "\nEnergy : " +QString::number(MY_MASTER.m_Report.v_Week[i].get_Energy());
        mR->setChild(wR->index().row(),1,new QStandardItem(out7));
    }

    ui->treeView->setModel(model);
}

void GetReport::on_quit_clicked()
{
    this->close();
}
