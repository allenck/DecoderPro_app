#ifndef ACTIONTHROTTLE_H
#define ACTIONTHROTTLE_H

#include "abstractdigitalaction.h"
#include "dccthrottle.h"
#include "femalesocketlistener.h"
#include "locoaddress.h"
#include "throttle.h"
#include "throttlelistener.h"
#include "threadingutil.h"

class DccThrottle;
class ThrottleListener;
class FemaleAnalogExpressionSocket;
class FemaleDigitalExpressionSocket;
class ActionThrottle : public AbstractDigitalAction, public FemaleSocketListener
{
    Q_OBJECT
    Q_INTERFACES(FemaleSocketListener)
 public:
    explicit ActionThrottle(QString sys, QString user,QObject *parent = nullptr);
    enum SOCKET {
    LOCO_ADDRESS_SOCKET = 0,
    LOCO_SPEED_SOCKET = 1,
    LOCO_DIRECTION_SOCKET = 2
    };
    /*public*/ Base* getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws JmriException*/ override;

    /*public*/ Category getCategory()override;
    /*public*/ void execute() /*throws JmriException*/override;
    /*public*/ FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
    /*public*/ int getChildCount() override;
    /*public*/ void connected(FemaleSocket* socket)override;
    /*public*/ void disconnected(FemaleSocket* socket) override;
    /*public*/ QString getShortDescription(QLocale locale)override;
    /*public*/ QString getLongDescription(QLocale locale)override;
    /*public*/ FemaleAnalogExpressionSocket* getLocoAddressSocket();
    /*public*/ QString getLocoAddressSocketSystemName() ;
    /*public*/ void setLocoAddressSocketSystemName(QString systemName) ;
    /*public*/ FemaleAnalogExpressionSocket* getLocoSpeedSocket();
    /*public*/ QString getLocoSpeedSocketSystemName();
    /*public*/ void setLocoSpeedSocketSystemName(QString systemName);
    /*public*/ FemaleDigitalExpressionSocket* getLocoDirectionSocket() ;
    /*public*/ QString getLocoDirectionSocketSystemName() ;
    /*public*/ void setLocoDirectionSocketSystemName(QString systemName) ;
    /*public*/ void setup()override;
    /*public*/ void registerListenersForThisClass()override;
    /*public*/ void unregisterListenersForThisClass()override;
    /*public*/ void disposeMe() override;

    QObject* bself() override{return this;}

    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ PropertyChangeListener* listener, QString name, QString listenerRef)override{
     AbstractNamedBean::addPropertyChangeListener(listener, name,listenerRef);
    }
    /*public*/  void addPropertyChangeListener(/*@Nonnull*/ QString propertyName, /*@Nonnull*/ PropertyChangeListener* listener,
                                                      QString name, QString listenerRef) override {
     AbstractNamedBean::addPropertyChangeListener(propertyName, listener, name, listenerRef);
    }
    /*public*/ void updateListenerRef(PropertyChangeListener* l, QString newName) override {AbstractNamedBean::updateListenerRef(l, newName);}
    /*public*/ void vetoableChange(/*@Nonnull*/ PropertyChangeEvent* evt) override {AbstractNamedBean::vetoableChange(evt);}
    /*public*/ QString getListenerRef(/*@Nonnull*/ PropertyChangeListener* l) override {return  AbstractNamedBean::getListenerRef(l);}
    /*public*/ QList<QString> getListenerRefs() override {return AbstractNamedBean::getListenerRefs();}
    /*public*/ int getNumPropertyChangeListeners() override {return  AbstractNamedBean::getNumPropertyChangeListeners();}
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListenersByReference(/*@Nonnull*/ QString name)override {
     return AbstractNamedBean::getPropertyChangeListenersByReference(name);
    }

 private:
    static Logger* log;
    // The throttle if we have one or if a request is sent, null otherwise
    /*private*/ DccThrottle* _throttle;
    /*private*/ ThrottleListener* _throttleListener;

    /*private*/ QString _locoAddressSocketSystemName;
    /*private*/ QString _locoSpeedSocketSystemName;
    /*private*/ QString _locoDirectionSocketSystemName;
    /*private*/ /*final*/ FemaleAnalogExpressionSocket* _locoAddressSocket;
    /*private*/ /*final*/ FemaleAnalogExpressionSocket* _locoSpeedSocket;
    /*private*/ /*final*/ FemaleDigitalExpressionSocket* _locoDirectionSocket;
    bool _isActive = false;
    /*private*/ void executeConditionalNG();

    friend class AT_ThrottleListener;
};

class AT_ThrottleListener : public QObject, public ThrottleListener
{
    Q_OBJECT
    ActionThrottle* actionThrottle;
    public:
    AT_ThrottleListener(ActionThrottle* actionThrottle) {this->actionThrottle = actionThrottle;}
    //@Override
    /*public*/ void notifyThrottleFound(DccThrottle* t) {
        actionThrottle->_throttle = t;
        actionThrottle->executeConditionalNG();
    }

    //@Override
    /*public*/ void notifyFailedThrottleRequest(LocoAddress* address, QString reason) {
        actionThrottle->log->warn(tr("loco %1 cannot be aquired").arg(address->getNumber()));
    }

    //@Override
    /*public*/ void notifyDecisionRequired(LocoAddress* address, ThrottleListener::DecisionType question) {
        actionThrottle->log->warn(tr("Loco %1 cannot be aquired. Decision required.").arg(address->getNumber()));
    }

    QObject* self() override{return this;}
};

class AT_ThreadingUtil : public ThreadingUtil
{
    Q_OBJECT
  DccThrottle* throttle;
  float spd;
  bool fwd;
public:
  AT_ThreadingUtil(DccThrottle* throttle, float spd, bool fwd) {this->throttle = throttle; this->spd=spd; this->fwd = fwd;}
  void runOnLayoutWithJmriException()
  {
    throttle->setSpeedSetting(spd);
    throttle->setIsForward(fwd);
  };

};

#endif // ACTIONTHROTTLE_H
