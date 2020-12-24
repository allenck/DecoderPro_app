#ifndef ABSTRACTSHUTDOWNTASK_H
#define ABSTRACTSHUTDOWNTASK_H
#include "shutdowntask.h"
#include "javaqt_global.h"
class JAVAQTSHARED_EXPORT AbstractShutDownTask : /*public QObject,*/ public ShutDownTask
{
    Q_OBJECT
  //Q_INTERFACES(ShutDownTask)
public:
    //explicit AbstractShutDownTask(QObject *parent = 0);
    /*public*/ AbstractShutDownTask(QString name,QObject *parent = 0);
    /*public*/ QString getName();
  //QObject* self() {return (QObject*)this;}
signals:
    
public slots:
private:
    QString mName;
    QObject *parent;
};

#endif // ABSTRACTSHUTDOWNTASK_H
