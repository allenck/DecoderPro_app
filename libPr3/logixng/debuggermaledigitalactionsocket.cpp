#include "debuggermaledigitalactionsocket.h"
#include "defaultmaledigitalactionsocket.h"

/**
 *
 * @author daniel
 */
///*public*/  class DebuggerMaleDigitalActionSocket extends AbstractDebuggerMaleSocket implements MaleDigitalActionSocket {

    /*public*/  DebuggerMaleDigitalActionSocket::DebuggerMaleDigitalActionSocket(BaseManager/*<MaleDigitalActionSocket>*/* manager, MaleDigitalActionSocket *maleSocket, QObject *parent)
      : AbstractDebuggerMaleSocket(manager, maleSocket,parent)
    {
        //super(manager, maleSocket);
        setObjectName("DebuggerMaleDigitalActionSocket");
        setProperty("AdapterName","jmri.jmrit.logixng.tools.debugger.configurexml.DebuggerMaleDigitalActionSocketXml");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleDigitalActionSocket::getBeforeInfo() {
        return tr("DigitalAction_InfoBefore");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerMaleDigitalActionSocket::getAfterInfo() {
        return tr("DigitalAction_InfoAfter");
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalActionSocket::execute() /*throws JmriException */{
        before();
        ((MaleDigitalActionSocket*)getObject()->bself())->execute();
        after();
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalActionSocket::setState(int s) /*throws JmriException*/ {
        ((MaleDigitalActionSocket*)getObject()->bself())->setState(s);
    }

    //@Override
    /*public*/  int DebuggerMaleDigitalActionSocket::getState() {
        return ((MaleDigitalActionSocket*)getObject()->bself())->getState();
    }

    //@Override
    /*public*/  QString DebuggerMaleDigitalActionSocket::describeState(int state) {
        return ((MaleDigitalActionSocket*)getObject()->bself())->describeState(state);
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalActionSocket::setProperty(QString key, QVariant value) {
        ((MaleDigitalActionSocket*)getObject()->bself())->setProperty(key, value);
    }

    //@Override
    /*public*/  QVariant DebuggerMaleDigitalActionSocket::getProperty(QString key) {
        return ((MaleDigitalActionSocket*)getObject()->bself())->getProperty(key);
    }

    //@Override
    /*public*/  void DebuggerMaleDigitalActionSocket::removeProperty(QString key) {
        ((MaleDigitalActionSocket*)getObject()->bself())->removeProperty(key);
    }

    //@Override
    /*public*/  QSet<QString> DebuggerMaleDigitalActionSocket::getPropertyKeys() {
        return ((MaleDigitalActionSocket*)getObject()->bself())->getPropertyKeys();
    }

    //@Override
    /*public*/  QString DebuggerMaleDigitalActionSocket::getBeanType() {
        return ((MaleDigitalActionSocket*)getObject()->bself())->getBeanType();
    }

    //@Override
    /*public*/  int DebuggerMaleDigitalActionSocket::compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) {
        return ((DefaultMaleDigitalActionSocket*)getObject()->bself())->compareSystemNameSuffix(suffix1, suffix2, n2);
    }

    /*public*/  QString DebuggerMaleDigitalActionSocket::getClassName()
    {
     return "jmri.jmrit.logixng.tools.debugger.DebuggerMaleDigitalActionSocket";
    }
