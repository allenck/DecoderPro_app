#include "debuggermalestringactionsocketfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "debuggermalestringactionsocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleStringActionSocketFactory.class)
//public class DebuggerMaleStringActionSocketFactory implements MaleStringActionSocketFactory {

    //@Override
    /*public*/ MaleStringActionSocket* DebuggerMaleStringActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleStringActionSocket>*/* manager, MaleStringActionSocket* maleSocket) {

        if (! ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleStringActionSocket(manager, maleSocket);
    }
