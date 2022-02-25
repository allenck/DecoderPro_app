#include "debuggermalestringactionsocket.h"

/**
 *
 * @author daniel
 */
///*public*/  class DebuggerMaleStringActionSocket extends AbstractDebuggerMaleSocket implements MaleStringActionSocket {


    /*public*/  DebuggerMaleStringActionSocket::DebuggerMaleStringActionSocket(BaseManager/*<MaleStringActionSocket>*/* manager,
                                               MaleStringActionSocket* maleSocket, QObject *parent)
     : AbstractDebuggerMaleSocket(manager, maleSocket, parent)
    {
        //super(manager, maleSocket);
     setObjectName("DebuggerMaleStringActionSocket");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleStringActionSocket::getBeforeInfo() {
        return tr("Set string \"%1\"").arg(_nextValue);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleStringActionSocket::getAfterInfo() {
        return tr("");
    }

    //@Override
    /*public*/  void DebuggerMaleStringActionSocket::setValue(/*@Nonnull*/ QString value) /*throws JmriException*/ {
        _nextValue = value;
        before();
        ((MaleStringActionSocket*)getObject()->bself())->setValue(_nextValue);
        after();
    }

    //@Override
    /*public*/  void DebuggerMaleStringActionSocket::setState(int s) /*throws JmriException */{
        ((MaleStringActionSocket*)getObject()->bself())->setState(s);
    }

    //@Override
    /*public*/  int DebuggerMaleStringActionSocket::getState() {
        return ((MaleStringActionSocket*)getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DebuggerMaleStringActionSocket::describeState(int state) {
        return ((MaleStringActionSocket*)getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  void DebuggerMaleStringActionSocket::setProperty(QString key, QVariant value) {
        ((MaleStringActionSocket*)getObject()->bself())->setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DebuggerMaleStringActionSocket::getProperty(QString key) {
        return ((MaleStringActionSocket*)getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DebuggerMaleStringActionSocket::removeProperty(QString key) {
        ((MaleStringActionSocket*)getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DebuggerMaleStringActionSocket::getPropertyKeys() {
        return ((MaleStringActionSocket*)getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DebuggerMaleStringActionSocket::getBeanType() {
        return ((MaleStringActionSocket*)getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DebuggerMaleStringActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
        return ((MaleStringActionSocket*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }
