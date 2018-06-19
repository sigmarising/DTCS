#include "thread_two.h"

QMutex mutex2;
thread_two::thread_two()
{

}
void thread_two::run()
{
    timer = new QTimer();
    timer->setInterval(100);
    connect(timer,&QTimer::timeout,this,&thread_two::timeoutSlot);
    timer->start();
    this->exec();
}
void thread_two::timeoutSlot()
{
    mutex2.lock();
    TSLAVE->f_tempnow_progress(100);
    TSLAVE->f_check_and_auto_adjust();
    mutex2.unlock();
}
