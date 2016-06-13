#include "sleeperthread.h"

SleeperThread::SleeperThread(QObject *parent) :
    QThread(parent)
{
 setObjectName("SleeperThread");
}
/*static*/ void SleeperThread::msleep(unsigned long msecs)
{
 QThread::msleep(msecs);
}
