#include "propertychangelistenerscaffold.h"

/**
 * Test utility class that allows verification for beans PropertyChange events.
 *
 * @author Balazs Racz Copyright (C) 2017
 * @author Paul Bender Copyright (C) 2018
 */

// /*public*/ class PropertyChangeListenerScaffold implements PropertyChangeListener {


/*public*/ PropertyChangeListenerScaffold::PropertyChangeListenerScaffold(QObject *parent)
: PropertyChangeListener(parent) {
   propertyChanged = false;
   callCount = 0;
   lastChange = "";
   lastValue = QVariant();
}

/*public*/ void PropertyChangeListenerScaffold::resetPropertyChanged(){
   propertyChanged = false;
   callCount = 0;
}

/*public*/ bool PropertyChangeListenerScaffold::getPropertyChanged(){
   return propertyChanged;
}

/*public*/ int PropertyChangeListenerScaffold::getCallCount(){
   return callCount;
}

/*public*/ QString PropertyChangeListenerScaffold::getLastProperty(){
   return lastChange;
}

/*public*/ QVariant PropertyChangeListenerScaffold::getLastValue(){
   return lastValue;
}

/*public*/ void PropertyChangeListenerScaffold::onChange(QString property, QVariant newValue){
   lastChange = property;
   lastValue = newValue;
}

//@Override
/*public*/ void PropertyChangeListenerScaffold::propertyChange(PropertyChangeEvent* propertyChangeEvent) {
   propertyChanged = true;
   onChange(propertyChangeEvent->getPropertyName(), propertyChangeEvent->getNewValue());
   callCount++;
}

