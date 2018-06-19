#include "thread_one.h"
#include <QMutex>

QMutex mutex1;

Thread_one::Thread_one()
{

}
void Thread_one::run()
{
    timer = new QTimer();
    timer->setInterval(100);
    connect(timer,&QTimer::timeout,this,&Thread_one::timeoutSlot);
    timer->start();
    this->exec();
}
void Thread_one::timeoutSlot()
{

    mutex1.lock();
    TSLAVE->f_status_update();
    mutex1.unlock();
}
