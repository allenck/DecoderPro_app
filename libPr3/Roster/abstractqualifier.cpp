#include "abstractqualifier.h"

//AbstractQualifier::AbstractQualifier(QObject *parent) :
//    Qualifier(parent)
//{
//}
/**
 * Watches a specific Variable to qualify others.
 *
 * @author			Bob Jacobsen   Copyright (C) 2010
 * @version			$Revision: 18542 $
 *
 */
// /*public*/ abstract class AbstractQualifier implements Qualifier, java.beans.PropertyChangeListener {

/*public*/ AbstractQualifier::AbstractQualifier(VariableValue* watchedVal, QObject *parent) : Qualifier()
{
 this->watchedVal = watchedVal;

 // set up listener
 if (watchedVal != NULL)
 {
  watchedVal->addPropertyChangeListener((PropertyChangeListener*)this);
  connect(watchedVal->prop, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
 // subclass ctors are required to qualify on initial value of variable
 // to get initial qualification state right after listener was added.
}

/**
 * Process property change from the qualifier Variable (one being watched).
 * <p>
 * Follows changes "Value" property, which it assumes is an Integer.
 */
/*public*/ void AbstractQualifier::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("Value"))
  processValueChangeEvent(e);
}

/**
 * Process Value property change from the qualifier Variable (one being watched).
 */
void AbstractQualifier::processValueChangeEvent(PropertyChangeEvent* e)
{
 bool oldAvailableValue = currentAvailableState();
 // watched value change, check if this changes state of qualified (output) object
 bool newAvailableValue = availableStateFromEvent(e);

 if (oldAvailableValue != newAvailableValue)
  setWatchedAvailable(newAvailableValue);
}

/**
 * Calculate whether this PropertyChangeEvent
 * means that the qualified Object should be set Available or not.
 */
/*protected*/ bool AbstractQualifier::availableStateFromEvent(PropertyChangeEvent* e) {
    return availableStateFromValue(e->getNewValue().toInt());
}

/**
 * Calculate whether the current value of qualifier Variable
 * means that the qualified object should be set Available or not.
 */
/*abstract*/ bool AbstractQualifier::availableStateFromValue(int ) { return false;}
//abstract bool currentDesiredState();


/*protected*/ void AbstractQualifier::setWatchedAvailable(bool enable) {
    //qualifiedVal->setAvailable(enable);
}

///*public*/ void AbstractQualifier::update(int value) {
//    setWatchedAvailable(availableStateFromValue(value));
//}
/**
 * Retrieve the current "available" state from the qualified Object.
 */

/*abstract*/ /*protected*/ bool AbstractQualifier::currentAvailableState() {return false;}

/**
 * Calculate whether the current value of qualifier Variable
 * means that the qualified object should be set Available or not.
 */
/*abstract*/ /*public*/ bool AbstractQualifier::currentDesiredState() {return false;}
