#ifndef ABSTRACTPOWERMANAGER_H
#define ABSTRACTPOWERMANAGER_H
#include "powermanager.h"
#include "systemconnectionmemo.h"
#include "propertychangesupport.h"
#include <QMutex>

class LIBPR3SHARED_EXPORT AbstractPowerManager : public PowerManager
{
    Q_OBJECT
public:
 explicit AbstractPowerManager(SystemConnectionMemo * memo, QObject *parent = 0);
 QString getUserName();
 virtual void removePropertyChangeListener(PropertyChangeListener* l);
 virtual /*public synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
 //PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);

signals:
 //void propertyChange(QString p, QVariant old, QVariant n);
 void propertyChange(PropertyChangeEvent*);
public slots:
private:
 QString userName;
 QMutex mutex;
protected:
 void firePropertyChange(QString p, QVariant old, QVariant n);

 friend class PowerPane;
 friend class ThrottleWindow;
 friend class ListThrottles;
 friend class RosterFrame;
};

#endif // ABSTRACTPOWERMANAGER_H
