#ifndef ABSTRACTPOWERMANAGER_H
#define ABSTRACTPOWERMANAGER_H
#include "powermanager.h"
#include "systemconnectionmemo.h"
#include "swingpropertychangesupport.h"
#include <QMutex>
#include "swingpropertychangesupport.h"
#include "QDateTime"

class LIBPR3SHARED_EXPORT AbstractPowerManager : public SwingPropertyChangeSupport,  public PowerManager
{
  Q_OBJECT
  Q_INTERFACES(PowerManager )
public:
 explicit AbstractPowerManager(SystemConnectionMemo * memo, QObject *parent = 0);
  /*public*/ int getPower()override;
  /*public*/ void setPower(int state)override;
  /*public*/ QString getUserName()override;
// virtual void removePropertyChangeListener(PropertyChangeListener* l);
// virtual /*public synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
 //SwingPropertyChangeSupport* pcs;// = new SwingPropertyChangeSupport(this, nullptr);

signals:
 //void propertyChange(QString p, QVariant old, QVariant n);
 void propertyChange(PropertyChangeEvent*);
public slots:
private:
 QString userName;
 QMutex mutex;
 /*private*/ /*Instant*/qint64 lastOn;

protected:
 void firePowerPropertyChange(int old, int current) ;
 /*protected*/ /*final*/ SystemConnectionMemo* memo = nullptr;
 /**
  * Note that all changes must fire a property change with the old and new values
  */
 /*protected*/ int power = UNKNOWN;

 friend class PowerPane;
 friend class ThrottleWindow;
 friend class ListThrottles;
 friend class RosterFrame;
 friend class TimeKeeper;
};

// a class for listening for power state changes
    /*public*/ class TimeKeeper : public QObject, public PropertyChangeListener {
  Q_OBJECT
  AbstractPowerManager* mgr;
 public:
  TimeKeeper(AbstractPowerManager* mgr)  {this->mgr = mgr;}
  QObject* pself() override{return(QObject*)this;}
 public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e) override{
        if (mgr->POWER == (e->getPropertyName())) {
            int newPowerState = mgr->getPower();
            if (newPowerState != mgr->power) {
                mgr->power = newPowerState;
                if (newPowerState == mgr->ON) {
                    mgr->lastOn = /*Instant.now()*/QDateTime::currentSecsSinceEpoch();
                }
            }
        }
    }
};
#endif // ABSTRACTPOWERMANAGER_H
