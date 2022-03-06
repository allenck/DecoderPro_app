#include "debuggermaleanalogexpressionsocket.h"
#include "basemanager.h"
#include "maleanalogexpressionsocket.h"
/**
 *
 * @author daniel
 */
// /*public*/  class DebuggerMaleAnalogExpressionSocket extends AbstractDebuggerMaleSocket implements MaleAnalogExpressionSocket {


    /*public*/  DebuggerMaleAnalogExpressionSocket::DebuggerMaleAnalogExpressionSocket(BaseManager/*<MaleAnalogExpressionSocket>*/* manager,
                                                   NamedBean* maleSocket, QObject* parent)
     : AbstractDebuggerMaleSocket(manager, maleSocket, parent)
    {
        //super(manager, maleSocket);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleAnalogExpressionSocket::getBeforeInfo() {
        return tr("Before %1").arg(_lastResult);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleAnalogExpressionSocket::getAfterInfo() {
        return tr("Return value %1").arg(_lastResult);
    }

    //@Override
    /*public*/  double DebuggerMaleAnalogExpressionSocket::evaluate() /*throws JmriException*/ {
        before();
        _lastResult = ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->evaluate();
        after();
        return _lastResult;
    }

    //@Override
    /*public*/  void DebuggerMaleAnalogExpressionSocket::setState(int s) /*throws JmriException*/ {
        ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->setState(s);
    }

    //@Override
    /*public*/  int DebuggerMaleAnalogExpressionSocket::getState() {
        return ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DebuggerMaleAnalogExpressionSocket::describeState(int state) {
        return ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  void DebuggerMaleAnalogExpressionSocket::setProperty(QString key, QVariant value) {
        ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->NamedBean::setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DebuggerMaleAnalogExpressionSocket::getProperty(QString key) {
        return ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DebuggerMaleAnalogExpressionSocket::removeProperty(QString key) {
        ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DebuggerMaleAnalogExpressionSocket::getPropertyKeys() {
        return ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DebuggerMaleAnalogExpressionSocket::getBeanType() {
        return ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DebuggerMaleAnalogExpressionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
        return ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }

    //@Override
    /*public*/  void DebuggerMaleAnalogExpressionSocket::setTriggerOnChange(bool triggerOnChange) {
        ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->setTriggerOnChange(triggerOnChange);
    }

    //@Override
    /*public*/  bool DebuggerMaleAnalogExpressionSocket::getTriggerOnChange() {
        return ((MaleAnalogExpressionSocket*)AbstractMaleSocket::getObject()->bself())->getTriggerOnChange();
    }
