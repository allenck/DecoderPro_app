#ifndef ABSTRACTSHUTDOWNTASK_H
#define ABSTRACTSHUTDOWNTASK_H
#include "shutdowntask.h"
#include "javaqt_global.h"
#include "propertychangeevent.h"

class Logger;
class JAVAQTSHARED_EXPORT AbstractShutDownTask : /*public QObject,*/ public ShutDownTask
{
    Q_OBJECT
  //Q_INTERFACES(ShutDownTask)
public:
    //explicit AbstractShutDownTask(QObject *parent = 0);
    /*public*/ AbstractShutDownTask(QString name,QObject *parent = 0);
    /*public*/ bool isShutdownAllowed()override;
    /*public*/ bool call()override;
    /*public*/ /*final*/ bool execute() /*final*/ override; // should be final but Python doesn't like it!
    /*public*/ QString getName()override;
    /*public*/ bool isParallel()override;
    /*public*/ bool isComplete()override;
    /*public*/ bool isDoRun();
    /*public*/ void setDoRun(bool flag);

    //QObject* self() {return (QObject*)this;}
signals:
    
public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
  static Logger* log;

    QString mName;
    QObject *parent;
    /*private*/ bool doRun = false;
};

#endif // ABSTRACTSHUTDOWNTASK_H
