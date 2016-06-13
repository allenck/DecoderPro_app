#ifndef SLEEPERTHREAD_H
#define SLEEPERTHREAD_H

#include <QThread>
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT SleeperThread : public QThread
{
    Q_OBJECT
public:
    explicit SleeperThread(QObject *parent = 0);
    static void msleep(unsigned long msecs);

signals:

public slots:

};

#endif // SLEEPERTHREAD_H
