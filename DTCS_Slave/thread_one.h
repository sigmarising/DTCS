#ifndef THREAD_ONE_H
#define THREAD_ONE_H

#include "SLAVE.h"
#include <QTimer>
#include <QString>
#include <QThread>
#include <QDebug>
#include <QDialog>
#include "login2.h"

extern SLAVE * TSLAVE;

class Thread_one : public QThread
{
public:
    Thread_one();
    virtual void run();
    QTimer * timer;
public slots:
    void timeoutSlot();
};

#endif // THREAD_ONE_H
