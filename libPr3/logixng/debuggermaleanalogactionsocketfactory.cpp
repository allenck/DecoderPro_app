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
/*public*/ NamedBean* DebuggerMaleAnalogActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, NamedBean* maleSocket) {

    if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
        return maleSocket;
    }

    return new DebuggerMaleAnalogActionSocket(manager, (AbstractBase*)maleSocket->self());
}
