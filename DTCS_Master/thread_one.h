#ifndef THREAD_ONE_H
#define THREAD_ONE_H

#include <QThread>
#include <QString>
#include <QTimer>
#include <QDebug>
#include "login.h"

extern MASTER MY_MASTER;

class thread_one:public QThread
{
public:
    thread_one();
    virtual void run();
    QTimer * timer_1;
public slots:
    void timeoutSlot();
};

#endif // THREAD_ONE_H
