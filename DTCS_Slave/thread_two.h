#ifndef THREAD_TWO_H
#define THREAD_TWO_H

#include "SLAVE.h"
#include <QTimer>
#include <QString>
#include <QThread>
#include <QDebug>
#include <QDialog>
#include "login2.h"

extern SLAVE * TSLAVE;

class thread_two:public QThread
{
public:
    thread_two();
    virtual void run();
    QTimer * timer;
public slots:
    void timeoutSlot();
};

#endif // THREAD_TWO_H
