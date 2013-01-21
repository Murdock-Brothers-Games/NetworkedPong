#ifndef SLEEPTHREAD_H
#define SLEEPTHREAD_H

#include <QThread>

class SleepThread : public QThread
{
    Q_OBJECT
public:
    SleepThread(QObject *parent = 0);

    static void msleep(unsigned long msec);

    static void usleep(unsigned long usec);

    void run();
    
signals:
    
public slots:
    
};

#endif // SLEEPTHREAD_H
