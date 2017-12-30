#ifndef ABSTRACTSHUTDOWNTASK_H
#define ABSTRACTSHUTDOWNTASK_H
#include "shutdowntask.h"
#include "javaqt_global.h"
class JAVAQTSHARED_EXPORT AbstractShutDownTask : public ShutDownTask
{
    Q_OBJECT
public:
    //explicit AbstractShutDownTask(QObject *parent = 0);
    /*public*/ AbstractShutDownTask(QString name,QObject *parent = 0);
    /*public*/ QString getName();

signals:
    
public slots:
private:
    QString mName;
    QObject *parent;
};

#endif // ABSTRACTSHUTDOWNTASK_H
