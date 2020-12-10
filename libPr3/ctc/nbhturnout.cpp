#include "nbhturnout.h"
#include "turnout.h"
#include "instancemanager.h"
#include "ctcmanager.h"
#include "projectscommonsubs.h"

/**
 * This object additionally supports "inverted feedback", so that when someone
 * calls "getKnownState", (typically my own code in this CTC project) we return
 * the "adjusted" value based upon "inverted feedback".
 * @author Gregory J. Bedlek Copyright (C) 2018, 2019, 2020
 * Prefix NBH = Named Bean Handler....
 */

///*public*/ class NBHTurnout {

//  Special case sane return values:
    /*public*/ /*static*/ /*final*/ int NBHTurnout::DEFAULT_TURNOUT_STATE_RV = Turnout::CLOSED;  // A valid state, just "B.S.".
//  Standard sane return values for the types indicated:
//  /*public*/ static /*final*/ Object DEFAULT_OBJECT_RV = null;       // For any function that returns something derived from Java's Object.
//  /*public*/ static /*final*/ boolean DEFAULT_BOOLEAN_RV = false;    // For any function that returns boolean.
    /*public*/ /*static*/ /*final*/ int NBHTurnout::DEFAULT_INT_RV = 0;                // For any function that returns int.
//  /*public*/ static /*final*/ long DEFAULT_LONG_RV = 0;              // For any function that returns long.
//  /*public*/ static /*final*/ float DEFAULT_FLOAT_RV = (float)0.0;   // For any function that returns float.
//  /*public*/ static /*final*/ String DEFAULT_STRING_RV = "UNKNOWN";  // NOI18N  For any function that returns String.


    /*public*/ NBHTurnout::NBHTurnout(QString module, QString userIdentifier, QString parameter, QString turnout, bool FeedbackDifferent, QObject* parent) : QObject(parent){
        _mUserIdentifier = userIdentifier;
        _mParameter = parameter;
        _mFeedbackDifferent = FeedbackDifferent;
        Turnout* tempTurnout = getSafeExistingJMRITurnout(module, _mUserIdentifier, _mParameter, turnout);
        if (tempTurnout != nullptr) {
            _mNamedBeanHandleTurnout = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turnout, tempTurnout);
        } else {
            _mNamedBeanHandleTurnout = nullptr;
        }
        if (valid()) ((CtcManager*)InstanceManager::getDefault("CtcManager"))->putNBHTurnout(turnout, this);
    }

// Special constructor to create a NBHTurnout with a null NamedBeanHandle.  Used to initialize turnout fields.
    /*public*/ NBHTurnout::NBHTurnout(QString module, QString userIdentifier, QString parameter, QObject* parent) : QObject(parent) {
        _mUserIdentifier = userIdentifier;
        _mParameter = parameter;
        _mFeedbackDifferent = false;
        _mNamedBeanHandleTurnout = nullptr;
        if (valid()) ((CtcManager*)InstanceManager::getDefault("CtcManager"))->putNBHTurnout("dummy", this);
    }

    /*public*/ bool NBHTurnout::valid() { return _mNamedBeanHandleTurnout != nullptr; }  // For those that want to know the internal state.

    /*public*/ Turnout* NBHTurnout::getBean() {
        if (valid()) return _mNamedBeanHandleTurnout->getBean();
        return nullptr;
    }

    /*public*/ NamedBeanHandle<Turnout *> *NBHTurnout::getBeanHandle() {
        if (valid()) return _mNamedBeanHandleTurnout;
        return nullptr;
    }


    /*private*/ /*static*/ Turnout* NBHTurnout::getSafeExistingJMRITurnout(QString module, QString userIdentifier, QString parameter, QString turnout) {
        try { return getExistingJMRITurnout(module, userIdentifier, parameter, turnout); } catch (CTCException e) { e.logError(); }
        return nullptr;
    }
//  turnout is NOT optional and cannot be null.  Raises Exception in ALL error cases.
    /*static*/ /*private*/ Turnout* NBHTurnout::getExistingJMRITurnout(QString module, QString userIdentifier, QString parameter, QString turnout) throw (CTCException) {
        if (!ProjectsCommonSubs::isNullOrEmptyString(turnout)) {
            // Cannot use a constant Instance manager reference due to the dynamic nature of tests.
            Turnout* returnValue = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getTurnout(turnout);
            if (returnValue == nullptr) { throw new CTCException(module, userIdentifier, parameter, tr("Turnout does not exist:") + " " + turnout); }    // NOI18N
            return returnValue;
        } else { throw CTCException(module, userIdentifier, parameter, tr("Required turnout missing")); }    // NOI18N
    }

    /*public*/ int NBHTurnout::getKnownState() {
        if (_mNamedBeanHandleTurnout == nullptr) return DEFAULT_TURNOUT_STATE_RV;
        int knownState = _mNamedBeanHandleTurnout->getBean()->getKnownState();
        if (!_mFeedbackDifferent) { // Normal:
            return knownState;
        } else { // Reversed:
            return knownState == Turnout::CLOSED ? Turnout::THROWN : Turnout::CLOSED;
        }
    }

    /*public*/ void NBHTurnout::setCommandedState(int s) {
        if (_mNamedBeanHandleTurnout == nullptr) return;
        _mNamedBeanHandleTurnout->getBean()->setCommandedState(s);
    }

    /*public*/ int NBHTurnout::getFeedbackMode() {
        if (_mNamedBeanHandleTurnout == nullptr) return DEFAULT_INT_RV;
        return _mNamedBeanHandleTurnout->getBean()->getFeedbackMode();
    }

    /*public*/ void NBHTurnout::addPropertyChangeListener(PropertyChangeListener* propertyChangeListener) {
        if (_mNamedBeanHandleTurnout == nullptr) return;
        _mNamedBeanHandleTurnout->getBean()->addPropertyChangeListener(propertyChangeListener);
        _mArrayListOfPropertyChangeListeners.append(propertyChangeListener);
    }

    /*public*/ void NBHTurnout::removePropertyChangeListener(PropertyChangeListener* propertyChangeListener) {
        if (_mNamedBeanHandleTurnout == nullptr) return;
        _mNamedBeanHandleTurnout->getBean()->removePropertyChangeListener(propertyChangeListener);
        _mArrayListOfPropertyChangeListeners.removeOne(propertyChangeListener);
    }

    /**
     * @return The turnout's handle name.
     */
    /*public*/ QString NBHTurnout::getHandleName() {
        return valid() ? _mNamedBeanHandleTurnout->getName() : "";
    }

    /**
     * For Unit testing only.
     * @return Returns the present number of property change listeners registered with us so far.
     */
    /*public*/ int NBHTurnout::testingGetCountOfPropertyChangeListenersRegistered() {
        return _mArrayListOfPropertyChangeListeners.size();
    }
