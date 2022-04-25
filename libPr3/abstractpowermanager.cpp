#include "abstractpowermanager.h"
#include "systemconnectionmemo.h"
#include <QString>
#include <QStringList>
AbstractPowerManager::AbstractPowerManager(SystemConnectionMemo * memo, QObject *parent) :
    SwingPropertyChangeSupport(this, parent)
{
// pcs = new SwingPropertyChangeSupport(this, nullptr);
 //this->userName = memo->getUserName();
 this->memo = memo;
 TimeKeeper* tk = new TimeKeeper(this);
 this->SwingPropertyChangeSupport::addPropertyChangeListener(tk);
}
//public AbstractPowerManager(jmri.jmrix.SystemConnectionMemo memo) {
//		this.userName = memo.getUserName();
//	}
    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ int AbstractPowerManager::getPower() {
        return power;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void AbstractPowerManager::setPower(int state)  {
        int old = power;
        power = state;
        firePowerPropertyChange(old, power);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*final*/ QString AbstractPowerManager::getUserName() {
        return memo->getUserName();
    }

/**
 * Fires a {@link java.beans.PropertyChangeEvent} for the power state using
 * both property names "power" and "Power".
 *
 * @param old the old power state
 * @param current the new power state
 */
//@SuppressWarnings("deprecation")
/*protected*/ /*final*/ void AbstractPowerManager::firePowerPropertyChange(int old, int current) {
    SwingPropertyChangeSupport::firePropertyChange(POWER, old, current);
    SwingPropertyChangeSupport::firePropertyChange(POWER_OPN, old, current);
}
