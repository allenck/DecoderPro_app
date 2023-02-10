#include "debuggermalestringactionsocketfactory.h"
#include "instancemanager.h"
#include "defaultlogixngpreferences.h"
#include "debuggermalestringactionsocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleStringActionSocketFactory.class)
//public class DebuggerMaleStringActionSocketFactory implements MaleStringActionSocketFactory {

    //@Override
    /*public*/ /*MaleStringActionSocket*/AbstractMaleSocket *DebuggerMaleStringActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleStringActionSocket>*/* manager, /*MaleStringActionSocket*/AbstractMaleSocket *maleSocket) {

        if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleStringActionSocket(manager, (MaleStringActionSocket*)maleSocket->bself());
    }
