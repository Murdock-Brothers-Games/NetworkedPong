#include "sleepthread.h"

SleepThread::SleepThread(QObject *parent) :
    QThread(parent)
{
}
void SleepThread::msleep(unsigned long msec)
{
    QThread::msleep(msec);
}

void SleepThread::usleep(unsigned long usec)
{
    QThread::usleep(usec);
}

void SleepThread::run()
{
    //Don't care.
}
