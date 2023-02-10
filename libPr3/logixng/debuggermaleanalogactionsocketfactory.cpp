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
/*public*/ AbstractMaleSocket* DebuggerMaleAnalogActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, AbstractMaleSocket* maleSocket) {

    if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
        return maleSocket;
    }

    return new DebuggerMaleAnalogActionSocket(manager, (MaleAnalogActionSocket*)maleSocket->bself());
}
