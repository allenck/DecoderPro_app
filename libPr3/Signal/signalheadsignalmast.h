#ifndef SIGNALHEADSIGNALMAST_H
#define SIGNALHEADSIGNALMAST_H
#include "abstractsignalmast.h"
#include <QThread>
#include "namedbeanhandle.h"
#include "signalhead.h"
#include "defaultsignalhead.h"
#include <QThread>
#include "runnable.h"

//class NamedBeanHandle;
class SignalMast;
class SignalHead;
class Runnable;
class LIBPR3SHARED_EXPORT SignalHeadSignalMast : public AbstractSignalMast
{
    Q_OBJECT
public:
    //explicit SignalHeadSignalMast(QObject *parent = 0);
    /*public*/ SignalHeadSignalMast(QString systemName, QString userName="", QObject *parent = 0);
    ~SignalHeadSignalMast() {dispose();}
    void configureFromName(QString systemName);
    void configureHeads(QStringList parts, int start) ;
    /*public*/ void setAspect(QString aspect) ;
    /*public*/ void setHeld(bool state);
    /*public*/ void setLit(bool state);
    /*public*/ QList<NamedBeanHandle<SignalHead*>* >* getHeadsUsed();
    /*public*/ void setAppearances(QString aspect);
    /*public*/ static QList<SignalHead*>* getSignalHeadsUsed();
    /*public*/ static QString isHeadUsed(SignalHead* head);
    /*public*/ QString className();
signals:

public slots:
private:
    Logger*log;
    QList<NamedBeanHandle<SignalHead*>* >* heads;
    /*private*/ void setDelayedAppearances(/*final*/ QHash<SignalHead*, int>* delaySet, /*final*/ int delay);
    QStringList splitParens(QString in);
public:
    class Runnable1 : public Runnable
    {
     //Q_OBJECT
    public:
        Runnable1(QHash<SignalHead*, int>* /*thrDelayedSet*/, int /*thrDelay*/, SignalHeadSignalMast* owner) : Runnable()
        {
         this->owner = owner;
        }
        SignalHeadSignalMast* owner;
        QHash<SignalHead*, int>* thrDelayedSet;
        int thrDelay;
        void run()
        {
         owner->setDelayedAppearances(thrDelayedSet, thrDelay);
        }
    };
    class Runnable2 : public Runnable
    {
    public:
        Runnable2(QHash<SignalHead*, int>* delaySet, SignalHead* thrHead , int delay, SignalHeadSignalMast* owner) : Runnable()
        {
         this->delaySet = delaySet;
         this->thrHead = thrHead;
         this->delay = delay;
         this->owner = owner;
         log = new Logger("Runnable2");
        }
        QHash<SignalHead*, int>* delaySet;
        SignalHead* thrHead;
        SignalHeadSignalMast* owner;
        int delay;

        /*public*/ void run()
        {
         try
         {
          ((DefaultSignalHead*)thrHead)->setAppearance(delaySet->value(thrHead));
          if (log->isDebugEnabled()) log->debug("Setting "+thrHead->getSystemName()+" to "+
                   ((DefaultSignalHead*)thrHead)->getAppearanceName(delaySet->value(thrHead)));
          QThread::msleep(delay);
         }
         catch (InterruptedException ex)
         {
          QThread::currentThread()->exit(1);
         }
        }
    private:
        Logger* log;
    };

};

#endif // SIGNALHEADSIGNALMAST_H
