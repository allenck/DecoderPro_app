#include "debuggermaleanalogactionsocketfactory.h"
#include "instancemanager.h"
#include "defaultlogixngpreferences.h"
#include "debuggermaleanalogactionsocket.h"
/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleAnalogActionSocketFactory.class)
//public class DebuggerMaleAnalogActionSocketFactory implements MaleAnalogActionSocketFactory {

//@Override
/*public*/ MaleSocket* DebuggerMaleAnalogActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, MaleSocket* maleSocket) {

    if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
        return maleSocket;
    }

    return new DebuggerMaleAnalogActionSocket(manager, (MaleAnalogActionSocket*)maleSocket->bself());
}
