#include "debuggermaledigitalactionsocketfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "debuggermaledigitalactionsocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleDigitalActionSocketFactory.class)
//public class DebuggerMaleDigitalActionSocketFactory implements MaleDigitalActionSocketFactory {

    //@Override
    /*public*/ MaleDigitalActionSocket* encapsulateMaleSocket(BaseManager/*<MaleDigitalActionSocket>*/* manager, MaleDigitalActionSocket* maleSocket) {

        if (! ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleDigitalActionSocket(manager, maleSocket);
    }
