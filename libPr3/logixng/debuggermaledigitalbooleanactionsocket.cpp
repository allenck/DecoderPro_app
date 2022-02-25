#include "debuggermaledigitalbooleanactionsocket.h"


/**
 *
 * @author daniel
 */
///*public*/  class DebuggerMaleDigitalBooleanActionSocket extends AbstractDebuggerMaleSocket implements MaleDigitalBooleanActionSocket {


    /*public*/  DebuggerMaleDigitalBooleanActionSocket::DebuggerMaleDigitalBooleanActionSocket(
         BaseManager/*<MaleDigitalBooleanActionSocket>*/* manager,
         MaleDigitalBooleanActionSocket* maleSocket, QObject* parent)
      : AbstractDebuggerMaleSocket(manager, maleSocket, parent)
    {
        //super(manager, maleSocket);
        setObjectName("DebuggerMaleDigitalBooleanActionSocket");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleDigitalBooleanActionSocket::getBeforeInfo() {
        return tr("Execute. Has changed to true: %1. Has changed to false: %2").arg(
                _nextHasChangedToTrue ? tr("True") : tr("False"),
                _nextHasChangedToFalse ? tr("True") : tr("False"));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleDigitalBooleanActionSocket::getAfterInfo() {
        return tr(" ");
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalBooleanActionSocket::execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/ {
        _nextHasChangedToTrue = hasChangedToTrue;
        _nextHasChangedToFalse = hasChangedToFalse;
        before();
        ((MaleDigitalBooleanActionSocket*)getObject()->bself())->execute(hasChangedToTrue, hasChangedToFalse);
        after();
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalBooleanActionSocket::setState(int s) /*throws JmriException*/ {
        ((MaleDigitalBooleanActionSocket*)getObject()->bself())->setState(s);
    }

    //@Override
    /*public*/  int DebuggerMaleDigitalBooleanActionSocket::getState() {
        return ((MaleDigitalBooleanActionSocket*)getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DebuggerMaleDigitalBooleanActionSocket::describeState(int state) {
        return ((MaleDigitalBooleanActionSocket*)getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalBooleanActionSocket::setProperty(QString key, QVariant value) {
        ((MaleDigitalBooleanActionSocket*)getObject()->bself())->setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DebuggerMaleDigitalBooleanActionSocket::getProperty(QString key) {
        return ((MaleDigitalBooleanActionSocket*)getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalBooleanActionSocket::removeProperty(QString key) {
        ((MaleDigitalBooleanActionSocket*)getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DebuggerMaleDigitalBooleanActionSocket::getPropertyKeys() {
        return ((MaleDigitalBooleanActionSocket*)getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DebuggerMaleDigitalBooleanActionSocket::getBeanType() {
        return ((MaleDigitalBooleanActionSocket*)getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DebuggerMaleDigitalBooleanActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
        return ((MaleDigitalBooleanActionSocket*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }
