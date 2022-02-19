#include "abstractdebuggermalesocket.h"
#include "vptr.h"

/**
 * Abstract debugger male socket
 * @author Daniel Bergqvist 2020
 */
///*public*/  abstract class AbstractDebuggerMaleSocket extends AbstractMaleSocket {



    /*public*/  AbstractDebuggerMaleSocket::AbstractDebuggerMaleSocket(BaseManager/*<? extends MaleSocket>*/* manager, MaleSocket* maleSocket, QObject* parent)
      :  AbstractMaleSocket(manager, (Base*)maleSocket, parent){
    }

    /**
     * Get information about this action/expression before it is executed or
     * evaluated.
     * @return an information string
     */
    /*public*/  /*abstract*/ QString getBeforeInfo();

    /**
     * Get information about this action/expression after it is executed or
     * evaluated.
     * @return an information string
     */
    /*public*/  /*abstract*/ QString getAfterInfo();

    /*protected*/ bool AbstractDebuggerMaleSocket::isDebuggerActive() {
        return _debugger->isDebuggerActive()
                && (_debugger->getDebugConditionalNG() == this->getConditionalNG());
    }

    /*protected*/ void AbstractDebuggerMaleSocket::before() {
        _lastDoBreak = _debugger->getBreak();
        if (isDebuggerActive() && (_debugger->getBreak() || _breakpointBefore)) {
//            System.out.format("Before: %s%n", getLongDescription());
            _debugger->firePropertyChange(Debugger::STEP_BEFORE, QVariant(), VPtr<AbstractDebuggerMaleSocket>::asQVariant(this));
            _debugger->setBreak(_stepInto);
        }
    }

    /*protected*/ void AbstractDebuggerMaleSocket::after() {
        if (isDebuggerActive()) {
            _debugger->setBreak(_lastDoBreak);
            if (_debugger->getBreak() || _breakpointAfter) {
//                System.out.format("After: %s%n", getLongDescription());
                _debugger->firePropertyChange(Debugger::STEP_AFTER, QVariant(), VPtr<AbstractDebuggerMaleSocket>::asQVariant(this));
            }
        }
    }

    /*public*/  void AbstractDebuggerMaleSocket::setStepInto(bool value) {
        _stepInto = value;
    }

    /*public*/  void AbstractDebuggerMaleSocket::setBreakpointBefore(bool value) {
        _breakpointBefore = value;
    }

    /*public*/  bool AbstractDebuggerMaleSocket::getBreakpointBefore() {
        return _breakpointBefore;
    }

    /*public*/  void AbstractDebuggerMaleSocket::setBreakpointAfter(bool value) {
        _breakpointAfter = value;
    }

    /*public*/  bool AbstractDebuggerMaleSocket::getBreakpointAfter() {
        return _breakpointAfter;
    }

    //@Override
    /*protected*/ /*final*/ void AbstractDebuggerMaleSocket::registerListenersForThisClass() {
        ((MaleSocket*)getObject()->bself())->registerListeners();
    }

    //@Override
    /*protected*/ /*final*/ void AbstractDebuggerMaleSocket::unregisterListenersForThisClass() {
        ((MaleSocket*)getObject()->bself())->unregisterListeners();
    }

    //@Override
    /*protected*/ /*final*/ void AbstractDebuggerMaleSocket::disposeMe() {
        ((MaleSocket*)getObject()->bself())->dispose();
    }

    //@Override
    /*public*/  /*final*/ void AbstractDebuggerMaleSocket::setEnabled(bool enable) {
        ((MaleSocket*)getObject()->bself())->setEnabled(enable);
    }

    //@Override
    /*public*/  void AbstractDebuggerMaleSocket::setEnabledFlag(bool enable) {
        ((MaleSocket*)getObject()->bself())->setEnabledFlag(enable);
    }

    //@Override
    /*public*/  /*final*/ bool AbstractDebuggerMaleSocket::isEnabled() {
        return ((MaleSocket*)getObject()->bself())->isEnabled();
    }

    //@Override
    /*public*/  /*final*/ void AbstractDebuggerMaleSocket::setDebugConfig(DebugConfig* config) {
        ((MaleSocket*)getObject()->bself())->setDebugConfig(config);
    }

    //@Override
    /*public*/  /*final*/ MaleSocket::DebugConfig* AbstractDebuggerMaleSocket::getDebugConfig() {
        return ((MaleSocket*)getObject()->bself())->getDebugConfig();
    }

    //@Override
    /*public*/  /*final*/ MaleSocket::DebugConfig* AbstractDebuggerMaleSocket::createDebugConfig() {
        return ((MaleSocket*)getObject()->bself())->createDebugConfig();
    }

    //@Override
    /*public*/  /*final*/ QString AbstractDebuggerMaleSocket::getComment() {
        return ((MaleSocket*)getObject()->bself())->getComment();
    }

    //@Override
    /*public*/  /*final*/ void AbstractDebuggerMaleSocket::setComment(QString comment) {
        ((MaleSocket*)getObject()->bself())->setComment(comment);
    }

    //@Override
    /*public*/  void AbstractDebuggerMaleSocket::setParent(Base* parent) {
        AbstractMaleSocket::setParent(parent);
        ((MaleSocket*)getObject()->bself())->Base::setParent(this);
    }


