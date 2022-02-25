#include "debuggermaleanalogactionsocketfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "debuggermaleanalogactionsocket.h"
/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleAnalogActionSocketFactory.class)
//public class DebuggerMaleAnalogActionSocketFactory implements MaleAnalogActionSocketFactory {

    //@Override
    /*public*/ MaleAnalogActionSocket* DebuggerMaleAnalogActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, MaleAnalogActionSocket* maleSocket) {

        if (! ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleAnalogActionSocket(manager, maleSocket);
    }
