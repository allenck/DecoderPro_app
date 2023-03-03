#ifndef EXPRESSIONCLOCK_H
#define EXPRESSIONCLOCK_H

#include "abstractdigitalexpression.h"
#include "is_isnot_enum.h"
#include "timertask.h"

class TimerTask;
class Timebase;
class ExpressionClock : public AbstractDigitalExpression, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
    Q_INVOKABLE explicit ExpressionClock(QString sys, QString user, QObject *parent = nullptr);
    ~ExpressionClock() {}
    class Type
    {
    public:
        enum VAL {FastClock, SystemClock};
        static QString toString(VAL v)
        {
            switch (v)
            {
            case FastClock: return tr("Fast clock");
            case SystemClock: return tr("System clock");
            }
            throw IllegalArgumentException();
        }
        static VAL valueOf(QString s)
        {
            if(s == tr("Fast clock")) return FastClock;
            return SystemClock;
        }
        static QList<VAL> values(){return {FastClock, SystemClock};}
    };

    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ override;
    /*public*/ Category getCategory()override;
    /*public*/ void set_Is_IsNot(Is_IsNot_Enum::VAL is_IsNot);
    /*public*/ Is_IsNot_Enum::VAL get_Is_IsNot();
    /*public*/ void setType(Type::VAL type) ;
    /*public*/ Type::VAL getType();
    /*public*/ void setRange(int beginTime, int endTime);
    /*public*/ int getBeginTime();
    /*public*/ int getEndTime();
    /*public*/ static QString formatTime(int minutes);
    /*public*/ bool evaluate()override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */override;
    /*public*/ int getChildCount()override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe()override;

    QObject* bself() override {return this;}
    QObject* pself() override {return this;}


    /*public*/ void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef) override{
        AbstractNamedBean::addPropertyChangeListener(listener, name, listenerRef);
    }
    /*public*/ void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                              QString name, QString listenerRef) override{
        AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
    }
    /*public*/ void updateListenerRef(/*@Nonnull*/ PropertyChangeListener* l, QString newName) override{
        AbstractNamedBean::updateListenerRef(l,newName);
    }
    /*public*/ int getNumPropertyChangeListeners() override{
        return AbstractNamedBean::getNumPropertyChangeListeners();
    }
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name) override
    {
       return AbstractNamedBean::getPropertyChangeListenersByReference(name);
    }
    /*public*/ virtual QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l)override{
        return AbstractNamedBean::getListenerRef(l);
    }
    /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override{
        return AbstractNamedBean::vetoableChange(evt);
    }

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt)override;

private:
    static Logger* log;
    /*private*/ Is_IsNot_Enum::VAL _is_IsNot = Is_IsNot_Enum::Is;
    /*private*/ Type::VAL _type = Type::FastClock;
    /*private*/ Timebase* _fastClock;
    /*private*/ int _beginTime = 0;
    /*private*/ int _endTime = 0;

    TimerTask* timerTask = nullptr;
    /*private*/ int milisInAMinute = 60000;
    /*private*/ void scheduleTimer();

    friend class EC_TimerTask;
};

class EC_TimerTask : public TimerTask
{
    Q_OBJECT
    ExpressionClock* ec;
public:
    EC_TimerTask(ExpressionClock* ec) {this->ec = ec;}
    //@Override
    /*public*/ void run() {
        ec->propertyChange(nullptr);
    }
};

#endif // EXPRESSIONCLOCK_H
