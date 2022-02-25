#include "debuggermaledigitalbooleanactionsocketfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "debuggermaledigitalbooleanactionsocket.h"
/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleDigitalBooleanActionSocketFactory.class)
//public class DebuggerMaleDigitalBooleanActionSocketFactory implements MaleDigitalBooleanActionSocketFactory {

    //@Override
    /*public*/ MaleDigitalBooleanActionSocket* DebuggerMaleDigitalBooleanActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleDigitalBooleanActionSocket>*/* manager, MaleDigitalBooleanActionSocket* maleSocket) {

        if (! ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleDigitalBooleanActionSocket(manager, maleSocket);
    }

