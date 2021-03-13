#include "thread.h"

Thread::Thread(QObject *runnable, QString name, QObject* parent) : QThread(parent)
{
 setObjectName(name);
 runnable->moveToThread(this);
 connect(this, SIGNAL(started()), this, SLOT(run()));
 connect(runnable, SIGNAL(finished()), this, SLOT(quit()));
 connect(runnable, SIGNAL(finished()), runnable, SLOT(deleteLater()));
 connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}
