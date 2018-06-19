#include "thread_one.h"

thread_one::thread_one()
{

}

void thread_one::run()
{
    timer_1 = new QTimer();
    timer_1-> setInterval(1000);
    connect(timer_1,&QTimer::timeout,this,&thread_one::timeoutSlot);
    timer_1->start();
    this->exec();
}
void thread_one::timeoutSlot()
{
    if(MY_MASTER.f_get_switch()==SWITCH_ON)
         bool temp = MY_MASTER.f_request_handle();
    //qDebug()<<"in 2"<<endl;
}
