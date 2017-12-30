#include "defaultpowermanager.h"
#include "propertychangelistener.h"
#include "propertychangesupport.h"

//DefaultPowerManager::DefaultPowerManager()
//{

//}
/**
 * Default implementation for controlling layout power
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2008, 2010
 */
// /*public*/ class DefaultPowerManager implements PowerManager {

/*public*/ DefaultPowerManager::DefaultPowerManager() : PowerManager()
{
 // to hear of changes
 pcs = new PropertyChangeSupport(this);
 power = UNKNOWN;

}

//@Override
/*public*/ void DefaultPowerManager::setPower(int v) {
    int oldvalue = power;
    power = v; // make change immediately in this implementation
    firePropertyChange("Power", oldvalue, power);
}

//@Override
/*public*/ QString DefaultPowerManager::getUserName() {
    return "Internal";
}

//@Override
/*public*/ int DefaultPowerManager::getPower() {
    return power;
}

// to free resources when no longer used
//@Override
/*public*/ void DefaultPowerManager::dispose() //throws JmriException
{
}

//@Override
/*public*/ /*synchronized*/ void DefaultPowerManager::addPropertyChangeListener(PropertyChangeListener* l) {
    //pcs->addPropertyChangeListener(l);
    connect(pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*protected*/ void DefaultPowerManager::firePropertyChange(QString p, QVariant old, QVariant n) {
    pcs->firePropertyChange(p, old, n);
}

//@Override
/*public*/ /*synchronized*/ void DefaultPowerManager::removePropertyChangeListener(PropertyChangeListener* l) {
    //pcs.removePropertyChangeListener(l);
 disconnect(pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));

}
