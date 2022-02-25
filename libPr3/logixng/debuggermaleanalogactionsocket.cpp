#include "debuggermaleanalogactionsocket.h"
#include "maleanalogactionsocket.h"

/**
 *
 * @author daniel
 */
///*public*/  class DebuggerMaleAnalogActionSocket extends AbstractDebuggerMaleSocket implements MaleAnalogActionSocket {


    /*public*/  DebuggerMaleAnalogActionSocket::DebuggerMaleAnalogActionSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, MaleAnalogActionSocket* maleSocket, QObject* parent)
      : AbstractDebuggerMaleSocket(manager, maleSocket, parent)
    {
        //super(manager, maleSocket);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleAnalogActionSocket::getBeforeInfo() {
        return tr("Set value %1").arg(_nextValue);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleAnalogActionSocket::getAfterInfo() {
        return tr(" ");
    }

    //@Override
    /*public*/  void DebuggerMaleAnalogActionSocket::setValue(double value) /*throws JmriException*/ {
        _nextValue = value;
        before();
        ((MaleAnalogActionSocket*)getObject()->bself())->setValue(_nextValue);
        after();
    }

    //@Override
    /*public*/  void DebuggerMaleAnalogActionSocket::setState(int s) /*throws JmriException*/ {
        ((MaleAnalogActionSocket*)getObject()->bself())->setState(s);
    }

    //@Override
    /*public*/  int DebuggerMaleAnalogActionSocket::getState() {
        return ((MaleAnalogActionSocket*)getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DebuggerMaleAnalogActionSocket::describeState(int state) {
        return ((MaleAnalogActionSocket*)getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  void DebuggerMaleAnalogActionSocket::setProperty(QString key, QVariant value) {
        ((MaleAnalogActionSocket*)getObject()->bself())->setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DebuggerMaleAnalogActionSocket::getProperty(QString key) {
        return ((MaleAnalogActionSocket*)getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DebuggerMaleAnalogActionSocket::removeProperty(QString key) {
        ((MaleAnalogActionSocket*)getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DebuggerMaleAnalogActionSocket::getPropertyKeys() {
        return ((MaleAnalogActionSocket*)getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DebuggerMaleAnalogActionSocket::getBeanType() {
        return ((MaleAnalogActionSocket*)getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DebuggerMaleAnalogActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
        return ((MaleAnalogActionSocket*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }

