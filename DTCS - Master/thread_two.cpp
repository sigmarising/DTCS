#include "thread_two.h"

thread_two::thread_two()
{

}

void thread_two::run()
{
    timer_1 = new QTimer();
    timer_1-> setInterval(MY_MASTER.f_get_frequent());
    connect(timer_1,&QTimer::timeout,this,&thread_two::timeoutSlot);
    timer_1->start();
    this->exec();
}
void thread_two::timeoutSlot()
{
    MY_MASTER.f_money_calculate(100);//qDebug()<<"money"<<endl;
    MY_MASTER.f_update_slave_status();//qDebug()<<"Update"<<endl;
    //  qDebug()<<"in 1"<<endl;
}
