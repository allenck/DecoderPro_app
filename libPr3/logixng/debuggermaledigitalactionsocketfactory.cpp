#include "debuggermaledigitalactionsocketfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "debuggermaledigitalactionsocket.h"
#include "defaultlogixngpreferences.h"
/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleDigitalActionSocketFactory.class)
//public class DebuggerMaleDigitalActionSocketFactory implements MaleDigitalActionSocketFactory {

    //@Override
    /*public*/ NamedBean *DebuggerMaleDigitalActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleDigitalActionSocket>*/* manager, NamedBean *maleSocket) {

        if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }
        QString sys = maleSocket->getSystemName();
        return new DebuggerMaleDigitalActionSocket(manager, (NamedBean*)maleSocket);
    }
