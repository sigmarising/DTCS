#ifndef THREAD_TWO_H
#define THREAD_TWO_H


#include <QThread>
#include <QString>
#include <QTimer>
#include <QDebug>
#include "login.h"

extern MASTER MY_MASTER;

class thread_two:public QThread
{
public:
    thread_two();
    virtual void run();
    QTimer * timer_1;
public slots:
    void timeoutSlot();
};


#endif // THREAD_TWO_H
