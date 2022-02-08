#ifndef DEBUGGERMALEANALOGEXPRESSIONFACTORY_H
#define DEBUGGERMALEANALOGEXPRESSIONFACTORY_H
#include "defaultfemaleanalogexpressionsocketfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "debuggermaleanalogexpressionsocket.h"
#include "defaultfemaleanalogexpressionsocketfactory.h"
#include "maleanalogexpressionsocketfactory.h"
/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleAnalogExpressionSocketFactory.class)
/*public*/ class DebuggerMaleAnalogExpressionSocketFactory : public MaleAnalogExpressionSocketFactory {

    //@Override
    public MaleAnalogExpressionSocket encapsulateMaleSocket(BaseManager<MaleAnalogExpressionSocket> manager, MaleAnalogExpressionSocket maleSocket) {

        if (! ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleAnalogExpressionSocket(manager, maleSocket);
    }

};
#endif // DEBUGGERMALEANALOGEXPRESSIONFACTORY_H
