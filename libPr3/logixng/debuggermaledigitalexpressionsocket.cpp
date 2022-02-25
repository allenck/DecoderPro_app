#include "debuggermaledigitalexpressionsocket.h"

/**
 *
 * @author daniel
 */
///*public*/  class DebuggerMaleDigitalExpressionSocket extends AbstractDebuggerMaleSocket implements MaleDigitalExpressionSocket {



    /*public*/  DebuggerMaleDigitalExpressionSocket::DebuggerMaleDigitalExpressionSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager,
                                                    MaleDigitalExpressionSocket* maleSocket, QObject* parent)
     : AbstractDebuggerMaleSocket(manager, maleSocket, parent) {
        //super(manager, maleSocket);
        setObjectName("DebuggerMaleDigitalExpressionSocket");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DebuggerMaleDigitalExpressionSocket::notifyChangedResult(bool oldResult, bool newResult) {
        ((MaleDigitalExpressionSocket*)getObject()->bself())->notifyChangedResult(oldResult, newResult);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleDigitalExpressionSocket::getBeforeInfo() {
        return tr("");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleDigitalExpressionSocket::getAfterInfo() {
        return tr("Return value %1").arg(_lastResult ? tr("True") : tr("False"));
    }

    //@Override
    /*public*/  bool DebuggerMaleDigitalExpressionSocket::evaluate() /*throws JmriException*/ {
        before();
        _lastResult = ((MaleDigitalExpressionSocket*)getObject()->bself())->evaluate();
        after();
        return _lastResult;
    }

    //@Override
    /*public*/  bool DebuggerMaleDigitalExpressionSocket::getLastResult() {
        return ((MaleDigitalExpressionSocket*)getObject()->bself())->getLastResult();
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalExpressionSocket::setState(int s) /*throws JmriException*/ {
        ((MaleDigitalExpressionSocket*)getObject()->bself())->setState(s);
    }

    //@Override
    /*public*/  int DebuggerMaleDigitalExpressionSocket::getState() {
        return ((MaleDigitalExpressionSocket*)getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DebuggerMaleDigitalExpressionSocket::describeState(int state) {
        return ((MaleDigitalExpressionSocket*)getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalExpressionSocket::setProperty(QString key, QVariant value) {
        ((MaleDigitalExpressionSocket*)getObject()->bself())->setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DebuggerMaleDigitalExpressionSocket::getProperty(QString key) {
        return ((MaleDigitalExpressionSocket*)getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalExpressionSocket::removeProperty(QString key) {
        ((MaleDigitalExpressionSocket*)getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DebuggerMaleDigitalExpressionSocket::getPropertyKeys() {
        return ((MaleDigitalExpressionSocket*)getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DebuggerMaleDigitalExpressionSocket::getBeanType() {
        return ((MaleDigitalExpressionSocket*)getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DebuggerMaleDigitalExpressionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
        return ((MaleDigitalExpressionSocket*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }
