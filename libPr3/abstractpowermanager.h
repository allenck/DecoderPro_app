#ifndef ABSTRACTPOWERMANAGER_H
#define ABSTRACTPOWERMANAGER_H
#include "powermanager.h"
#include "systemconnectionmemo.h"
#include "swingpropertychangesupport.h"
#include <QMutex>

class LIBPR3SHARED_EXPORT AbstractPowerManager : public PowerManager
{
    Q_OBJECT
public:
 explicit AbstractPowerManager(SystemConnectionMemo * memo, QObject *parent = 0);
 QString getUserName();
 void removePropertyChangeListener(PropertyChangeListener* l);
 /*public synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
 void addPropertyChangeListener(QString propertyName, PropertyChangeListener* l);
 void removePropertyChangeListener(QString propertyName, PropertyChangeListener* l);

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
