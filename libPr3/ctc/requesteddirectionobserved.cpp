#include "requesteddirectionobserved.h"
#include "ctcconstants.h"

/**
 * This object ONLY maintains ONE property: _mRequestedDirection.  Ergo no need
 * to call "addPropertyChangeListener" form with the "propertyName" variant.
 */
///*public*/ class RequestedDirectionObserved {

    /*public*/ RequestedDirectionObserved::RequestedDirectionObserved(QObject* parent) : QObject(parent) { _mRequestedDirection = CTCConstants::OUTOFCORRESPONDENCE; }    // Obviously nothing could have registered with us YET!
    /*public*/ void RequestedDirectionObserved::addPropertyChangeListener(PropertyChangeListener* pcl) { _mPropertyChangeSupport->addPropertyChangeListener(pcl); }
    /*public*/ void RequestedDirectionObserved::removePropertyChangeListener(PropertyChangeListener* pcl) { _mPropertyChangeSupport->removePropertyChangeListener(pcl); }
    /*public*/ void RequestedDirectionObserved::setRequestedDirection(int newRequestedDirection) {
        _mRequestedDirection = newRequestedDirection;   // In case user directly asks us instead of using the following values:
        _mPropertyChangeSupport->firePropertyChange(PROPERTY, this->_mRequestedDirection, newRequestedDirection);  // Per documentation: NO event fired if NO change in value!
    }
    /*public*/ int RequestedDirectionObserved::getRequestedDirection() { return _mRequestedDirection; }

/*private*/ /*final*/ /*static*/ QString RequestedDirectionObserved::PROPERTY = "RequestedDirection";  // NOI18N  NEVER pass "null" for propertyName, there is a bug relating to this (for safety!)
