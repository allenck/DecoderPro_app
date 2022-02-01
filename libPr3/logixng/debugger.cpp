#include "debugger.h"
#include "exceptions.h"
/**
 * LogixNG Debugger
 * <P>
 * This class is _not_ thread safe. It must be called on the thread that is
 * used for the conditionalNG that the debugger is activated for.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/  class Debugger : public PropertyChangeProvider {

    /*public*/  /*static*/ /*final*/ QString Debugger::STEP_BEFORE = "StepBefore";
    /*public*/  /*static*/ /*final*/ QString Debugger::STEP_AFTER = "StepAfter";
    /*
    Breakpoint before/after - Always stop
    Step over -
    Step into -
    */

    /*public*/  void Debugger::activateDebugger(ConditionalNG* conditionalNG) {
        if (_debugConditionalNG != nullptr) {
            throw new IllegalStateException("Debugger is already active");
        }
        _debugConditionalNG = conditionalNG;
    }

    /*public*/  void Debugger::deActivateDebugger() {
        _debugConditionalNG = nullptr;
    }

    /*public*/  bool Debugger::isDebuggerActive() {
        return _debugConditionalNG != nullptr;
    }

    /*public*/  ConditionalNG* Debugger::getDebugConditionalNG() {
        return _debugConditionalNG;
    }

    /*public*/  void Debugger::setBreak(bool value) {
        _break = value;
    }

    /*public*/  bool Debugger::getBreak() {
        return _break;
    }

    //@OverridingMethodsMustInvokeSuper
    /*protected*/ void Debugger::firePropertyChange(QString p, QVariant old, QVariant n) {
        _pcs->firePropertyChange(p, old, n);
    }

    //@Override
    /*public*/  void Debugger::addPropertyChangeListener(PropertyChangeListener* listener) {
        _pcs->addPropertyChangeListener(listener);
    }

    //@Override
    /*public*/  void Debugger::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
        _pcs->addPropertyChangeListener(propertyName, listener);
    }

    //@Override
    /*public*/  QVector<PropertyChangeListener*> Debugger::getPropertyChangeListeners() const{
        return _pcs->getPropertyChangeListeners();
    }

    //@Override
    /*public*/  QVector<PropertyChangeListener*> Debugger::getPropertyChangeListeners(QString propertyName) {
        return _pcs->getPropertyChangeListeners(propertyName);
    }

    //@Override
    /*public*/  void Debugger::removePropertyChangeListener(PropertyChangeListener* listener) {
        _pcs->removePropertyChangeListener(listener);
    }

    //@Override
    /*public*/  void Debugger::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
        _pcs->removePropertyChangeListener(propertyName, listener);
    }
