#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QString>
#include <QTimer>
#include "maincharge.h"

extern MASTER MY_MASTER;

class Thread1 : public QThread
{
    Q_OBJECT
public:
    Thread1();
    virtual void run();
    QTimer * timer_1;
public slots:
    void timeoutSlot();
};
void Thread1::run()
{
    timer_1 = new QTimer();
    timer_1-> setInterval(1000);
    connect(timer_1,&QTimer::timeout,this,&Thread1::timeoutSlot);
    timer_1->start();
    this->exec();
}
void Thread1::timeoutSlot()
{
    MY_MASTER.f_request_handle();
    qDebug()<<"in thread"<<endl;
}

Thread1::Thread1(){}


#endif // THREAD_H
