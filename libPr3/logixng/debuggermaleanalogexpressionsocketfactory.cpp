#include "debuggermaleanalogexpressionsocketfactory.h"
#include "maleanalogexpressionsocket.h"
#include "instancemanager.h"
#include "defaultlogixngpreferences.h"
#include "debuggermaleanalogexpressionsocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleAnalogExpressionSocketFactory.class)
//public class DebuggerMaleAnalogExpressionSocketFactory implements MaleAnalogExpressionSocketFactory {

    //@Override
    /*public*/ MaleSocket *DebuggerMaleAnalogExpressionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleAnalogExpressionSocket>*/* manager, MaleSocket *maleSocket) {

        if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }
        return new DebuggerMaleAnalogExpressionSocket(manager, maleSocket);
    }

