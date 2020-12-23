#include "nbhsignal.h"
#include "projectscommonsubs.h"
#include "ctcmanager.h"
#include "instancemanager.h"
#include "signalmastmanager.h"
#include "signalheadmanager.h"
#include "otherdata.h"
#include "loggerfactory.h"
#include "ctcmanager.h"

/**
 * Provide access to both signal masts and signal heads for the CTC system.
 * <p>
 * This class combines the NBHAbstractSignalCommon, NBHSignalMast and NBHSignalHead
 * classes.  OtherData _mSignalSystemType determines whether masts or heads are enabled.
 * @author Dave Sand Copyright (C) 2020
 */
// /*public*/ class NBHSignal {

//  Standard sane return values for the types indicated:
    /*public*/ /*static*/ /*final*/ QObject* NBHSignal::DEFAULT_OBJECT_RV = nullptr;       // For any function that returns something derived from Java's Object.
    /*public*/ /*static*/ /*final*/ bool NBHSignal::DEFAULT_BOOLEAN_RV = false;    // For any function that returns bool.
    /*public*/ /*static*/ /*final*/ int NBHSignal::DEFAULT_INT_RV = 0;                // For any function that returns int.
    /*public*/ /*static*/ /*final*/ QString NBHSignal::DEFAULT_STRING_RV = "UNKNOWN";  // NOI18N  For any function that returns String.


    /**
     * Create the named bean handle for either a signal mast or signal head.
     * @param signal The signal name.
     */
    /*public*/ NBHSignal::NBHSignal(QString signal, QObject *parent) :QObject(parent) {
        isSignalMast = setSignalType();
        if (!ProjectsCommonSubs::isNullOrEmptyString(signal)) {
            if (isSignalMast) {
                // Cannot use a constant Instance manager reference due to the dynamic nature of tests.
                SignalMast* signalMast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(signal);
                if (signalMast != nullptr) {
                    _mNamedBeanHandleSignalMast = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signal, signalMast);
                    QString temp = getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DANGER);
                    if (temp == nullptr) temp = "Stop"; // NOI18N // Safety
                    _mDangerAppearance = temp;
                    _mNamedBeanHandleSignalHead = nullptr;
                    if (valid()) ((CtcManager*)InstanceManager::getDefault("CtcManager"))->putNBHSignal(signal, this);
                    return;
                }
            } else {
                // Cannot use a constant Instance manager reference due to the dynamic nature of tests.
                SignalHead* signalHead = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(signal);
                if (signalHead != nullptr) {
                    _mNamedBeanHandleSignalHead = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(signal, signalHead);
                    _mDangerAppearance = "Stop";            // NOI18N // Never used, just required for "/*final*/"
                    _mNamedBeanHandleSignalMast = nullptr;
                    if (valid()) ((CtcManager*)InstanceManager::getDefault("CtcManager"))->putNBHSignal(signal, this);
                     return;
                }
            }
        }
        _mDangerAppearance = "Stop";            // NOI18N // Never used, just required for "/*final*/"
        _mNamedBeanHandleSignalMast = nullptr;
        _mNamedBeanHandleSignalHead = nullptr;
    }

    /**
     * Set signal type using {@link OtherData#_mSignalSystemType}.
     * @return true for mast, false if head.
     */
    /*private*/ bool NBHSignal::setSignalType() {
        OtherData* otherData = ((CtcManager*)InstanceManager::getDefault("CtcManager"))->getOtherData();
        return otherData->_mSignalSystemType == OtherData::SIGNAL_SYSTEM_TYPE::SIGNALMAST ? true : false;

    }

    /*public*/ bool NBHSignal::valid() {
        return _mNamedBeanHandleSignalMast != nullptr || _mNamedBeanHandleSignalHead != nullptr;
    }  // For those that want to know the internal state.

    /*public*/ QObject* NBHSignal::getBean() {
        if (!valid()) return nullptr;
        return isSignalMast ? (QObject*)_mNamedBeanHandleSignalMast->getBean() : (QObject*)_mNamedBeanHandleSignalHead->getBean();
    }

    /*public*/ QObject* NBHSignal::getBeanHandle() {
        if (!valid()) return nullptr;
        return isSignalMast ? (QObject*)_mNamedBeanHandleSignalMast : (QObject*)_mNamedBeanHandleSignalHead;
    }

    /**
     * @return The signal's handle name.
     */
    /*public*/ QString NBHSignal::getHandleName() {
        if (!valid()) return nullptr;
        return isSignalMast ? _mNamedBeanHandleSignalMast->getName() : _mNamedBeanHandleSignalHead->getName();
    }

    /*public*/ QString NBHSignal::getDisplayName() {
        if (isSignalMast) {
            if (_mNamedBeanHandleSignalMast == nullptr) return DEFAULT_STRING_RV;
            return _mNamedBeanHandleSignalMast->getBean()->getDisplayName();
        } else {
            if (_mNamedBeanHandleSignalHead == nullptr) return DEFAULT_STRING_RV;
            return _mNamedBeanHandleSignalHead->getBean()->getDisplayName();
        }
    }

    /*public*/ bool NBHSignal::isDanger() {
        if (getHeld()) return true;     // Safety.  Problem in signal head, maybe same problem here?
        return isSignalMast ? getAspect() == (_mDangerAppearance) : SignalHead::RED == getAppearance();
    }

    /*public*/ void NBHSignal::setCTCHeld(bool held) {
        setHeld(held);
    }

    /*public*/ bool NBHSignal::getHeld() {
        if (isSignalMast) {
            if (_mNamedBeanHandleSignalMast == nullptr) return DEFAULT_BOOLEAN_RV;
            return _mNamedBeanHandleSignalMast->getBean()->getHeld();
        } else {
            if (_mNamedBeanHandleSignalHead == nullptr) return DEFAULT_BOOLEAN_RV;
            return _mNamedBeanHandleSignalHead->getBean()->getHeld();
        }
    }

    /*public*/ void NBHSignal::setHeld(bool newHeld) {
        if (isSignalMast) {
            if (_mNamedBeanHandleSignalMast == nullptr) return;
            _mNamedBeanHandleSignalMast->getBean()->setHeld(newHeld);
            if (newHeld) {
                _mNamedBeanHandleSignalMast->getBean()->setPermissiveSmlDisabled(true);
            }
        } else {
            if (_mNamedBeanHandleSignalHead == nullptr) return;
            _mNamedBeanHandleSignalHead->getBean()->setHeld(newHeld);
        }
    }

    /*public*/ void NBHSignal::allowPermissiveSML() {
        _mNamedBeanHandleSignalMast->getBean()->setPermissiveSmlDisabled(false);
    }

    /*public*/ void NBHSignal::addPropertyChangeListener(PropertyChangeListener* l) {
        if (isSignalMast) {
            if (_mNamedBeanHandleSignalMast == nullptr) return;
            _mNamedBeanHandleSignalMast->getBean()->addPropertyChangeListener(l);
        } else {
            if (_mNamedBeanHandleSignalHead == nullptr) return;
            _mNamedBeanHandleSignalHead->getBean()->addPropertyChangeListener(l);
        }
    }

    /*public*/ void NBHSignal::removePropertyChangeListener(PropertyChangeListener* l) {
        if (isSignalMast) {
            if (_mNamedBeanHandleSignalMast == nullptr) return;
            _mNamedBeanHandleSignalMast->getBean()->removePropertyChangeListener(l);
        } else {
            if (_mNamedBeanHandleSignalHead == nullptr) return;
            _mNamedBeanHandleSignalHead->getBean()->removePropertyChangeListener(l);
        }
    }

    /**
     *
     * Function to insure that a non null aspect value is always returned to the caller.
     *
     * Background (regarding the value contained in "_mDangerAppearance"):
     * In this objects constructor, "_mDangerAppearance" is set to getAppearanceMap().getSpecificAppearance(SignalAppearanceMap.DANGER).
     * If "...getSpecificAppearance..." returns "null" (undocumented in JMRI documents as of 9/18/2019),
     * "_mDangerAppearance" is set to "Stop" for safety.
     * So "_mDangerAppearance" will NEVER be null for use as follows:
     *
     * SignalMast.getAspect() can return "null" (undocumented in JMRI documents as of 9/18/2019) if (for instance) the signal has no
     * rules (i.e. no "Discover" done yet, or the signal is shown on the screen as a big red "X").
     * In this case, we return "_mDangerAppearance".
     *
     * @return  Return a guaranteed non null aspect name.
     */
    /*public*/ QString NBHSignal::getAspect() {
        if (!isSignalMast) log->info(tr("NBHSignal: getAspect called by signal head")/*, new Exception("traceback")*/);
        if (_mNamedBeanHandleSignalMast == nullptr) return DEFAULT_STRING_RV;
        QString returnAspect = _mNamedBeanHandleSignalMast->getBean()->getAspect();
        if (returnAspect == nullptr) return _mDangerAppearance;    // Safety
        return returnAspect;
    }

    /*public*/ SignalAppearanceMap* NBHSignal::getAppearanceMap() {
        if (!isSignalMast) log->info(tr("NBHSignal: getAppearanceMap called by signal head")/*, new Exception("traceback")*/);
        if (_mNamedBeanHandleSignalMast == nullptr) return nullptr;
        return _mNamedBeanHandleSignalMast->getBean()->getAppearanceMap();
    }

    /*public*/ int NBHSignal::getAppearance() {
        if (isSignalMast) log->info(tr("NBHSignal: getAppearance called by signal mast")/*, new Exception("traceback")*/);
        if (_mNamedBeanHandleSignalHead == nullptr) return DEFAULT_INT_RV;
        return _mNamedBeanHandleSignalHead->getBean()->getAppearance();
    }

    /*public*/ void NBHSignal::setAppearance(int newAppearance) {
        if (isSignalMast) log->info(tr("NBHSignal: setAppearance called by signal mast")/*, new Exception("traceback")*/);
        if (_mNamedBeanHandleSignalHead == nullptr) return;
        _mNamedBeanHandleSignalHead->getBean()->setAppearance(newAppearance);
    }

    /**
     * Get an array of appearance indexes valid for the mast type.
     *
     * @return array of appearance state values available on this mast type
     */
    /*public*/ QVector<int> NBHSignal::getValidStates() {
        if (isSignalMast) log->info(tr("NBHSignal: getValidStates called by signal mast")/*, new Exception("traceback")*/);
        if (_mNamedBeanHandleSignalHead == nullptr) return QVector<int>();
        return _mNamedBeanHandleSignalHead->getBean()->getValidStates();
    }

    /**
     * Get an array of non-localized appearance keys valid for the mast type.
     * For GUI application consider using (capitalized) {@link #getValidStateNames()}
     *
     * @return array of translated appearance names available on this mast type
     */
    /*public*/ QVector<QString> NBHSignal::getValidStateKeys() {
        if (isSignalMast) log->info(tr("NBHSignal: getValidStateKeys called by signal mast")/*, new Exception("traceback")*/);
        if (_mNamedBeanHandleSignalHead == nullptr) return QVector<QString>();
        return _mNamedBeanHandleSignalHead->getBean()->getValidStateKeys();
    }

    /**
     * Get an array of localized appearance descriptions valid for the mast type.
     * For persistance and comparison consider using {@link #getValidStateKeys()}
     *
     * @return array of translated appearance names
     */
    /*public*/ QVector<QString> NBHSignal::getValidStateNames() {
        if (isSignalMast) log->info(tr("NBHSignal: getValidStateNames called by signal mast")/*, new Exception("traceback")*/);
        if (_mNamedBeanHandleSignalHead == nullptr) return QVector<QString>();
        return _mNamedBeanHandleSignalHead->getBean()->getValidStateNames();
    }

    /*private*/ /*static*/ /*final*/ Logger* NBHSignal::log = LoggerFactory::getLogger("NBHSignal");
