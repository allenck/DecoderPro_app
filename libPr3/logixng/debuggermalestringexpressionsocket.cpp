#include "debuggermalestringexpressionsocket.h"

/**
 *
 * @author daniel
 */
// /*public*/  class DebuggerMaleStringExpressionSocket extends AbstractDebuggerMaleSocket implements MaleStringExpressionSocket {


    /*public*/  DebuggerMaleStringExpressionSocket::DebuggerMaleStringExpressionSocket(BaseManager/*<MaleStringExpressionSocket>*/* manager,
                                                                                       MaleStringExpressionSocket* maleSocket, QObject *parent)
      : AbstractDebuggerMaleSocket(manager, maleSocket, parent)
    {
        //super(manager, maleSocket);
        setObjectName("DebuggerMaleStringExpressionSocket");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleStringExpressionSocket::getBeforeInfo() {
        return tr("");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleStringExpressionSocket::getAfterInfo() {
        return tr("Return value %1").arg(_lastResult);
    }

    //@Override
    /*public*/  QString DebuggerMaleStringExpressionSocket::evaluate() /*throws JmriException*/ {
        before();
        _lastResult = ((MaleStringExpressionSocket*)getObject()->bself())->evaluate();
        after();
        return _lastResult;
    }

    //@Override
    /*public*/  void DebuggerMaleStringExpressionSocket::setState(int s) /*throws JmriException*/ {
        ((MaleStringExpressionSocket*)getObject()->bself())->setState(s);
    }

    //@Override
    /*public*/  int DebuggerMaleStringExpressionSocket::getState() {
        return ((MaleStringExpressionSocket*)getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DebuggerMaleStringExpressionSocket::describeState(int state) {
        return ((MaleStringExpressionSocket*)getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  void DebuggerMaleStringExpressionSocket::setProperty(QString key, QVariant value) {
        ((MaleStringExpressionSocket*)getObject()->bself())->setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DebuggerMaleStringExpressionSocket::getProperty(QString key) {
        return ((MaleStringExpressionSocket*)getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DebuggerMaleStringExpressionSocket::removeProperty(QString key) {
        ((MaleStringExpressionSocket*)getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DebuggerMaleStringExpressionSocket::getPropertyKeys() {
        return ((MaleStringExpressionSocket*)getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DebuggerMaleStringExpressionSocket::getBeanType() {
        return ((MaleStringExpressionSocket*)getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DebuggerMaleStringExpressionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
        return ((MaleStringExpressionSocket*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }

    //@Override
    /*public*/  void DebuggerMaleStringExpressionSocket::setTriggerOnChange(bool triggerOnChange) {
        ((MaleStringExpressionSocket*)getObject()->bself())->setTriggerOnChange(triggerOnChange);
    }

    //@Override
    /*public*/  bool DebuggerMaleStringExpressionSocket::getTriggerOnChange() {
        return ((MaleStringExpressionSocket*)getObject()->bself())->getTriggerOnChange();
    }
