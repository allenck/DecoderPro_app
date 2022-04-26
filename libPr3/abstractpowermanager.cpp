#include "abstractpowermanager.h"
#include "systemconnectionmemo.h"
#include <QString>
#include <QStringList>
AbstractPowerManager::AbstractPowerManager(SystemConnectionMemo * memo, QObject *parent) :
    PowerManager(parent)
{
 pcs = new SwingPropertyChangeSupport(this, nullptr);
 this->userName = memo->getUserName();
}
//public AbstractPowerManager(jmri.jmrix.SystemConnectionMemo memo) {
//		this.userName = memo.getUserName();
//	}
QString AbstractPowerManager::getUserName() { return userName; }

// to hear of changes
/*public synchronized*/
void AbstractPowerManager::addPropertyChangeListener(PropertyChangeListener* l)
{
 QMutexLocker locker(&mutex);
 pcs->SwingPropertyChangeSupport::addPropertyChangeListener(l);
}
void AbstractPowerManager::addPropertyChangeListener(QString propertyName, PropertyChangeListener* l)
{
 QMutexLocker locker(&mutex);
 pcs->SwingPropertyChangeSupport::addPropertyChangeListener(propertyName, l);
}

void AbstractPowerManager::firePropertyChange(QString p, QVariant old, QVariant n)
{  pcs->firePropertyChange(p,old,n);}

void AbstractPowerManager::removePropertyChangeListener(PropertyChangeListener* l)
{
 pcs->removePropertyChangeListener(l);
}
void AbstractPowerManager::removePropertyChangeListener(QString propertyName, PropertyChangeListener* l)
{
 pcs->removePropertyChangeListener(propertyName,l);
}
