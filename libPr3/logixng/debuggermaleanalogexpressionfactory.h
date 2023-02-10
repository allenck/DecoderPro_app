#ifndef DEBUGGERMALEANALOGEXPRESSIONFACTORY_H
#define DEBUGGERMALEANALOGEXPRESSIONFACTORY_H
#include "defaultfemaleanalogexpressionsocketfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "debuggermaleanalogexpressionsocket.h"
#include "defaultfemaleanalogexpressionsocketfactory.h"
#include "maleanalogexpressionsocketfactory.h"
#include "defaultlogixngpreferences.h"
#include "instancemanager.h"
#include "debuggermaleanalogexpressionsocket.h"
#include "abstractmalesocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleAnalogExpressionSocketFactory.class)
/*public*/ class DebuggerMaleAnalogExpressionSocketFactory : public MaleAnalogExpressionSocketFactory {

  Q_INTERFACES(MaleAnalogExpressionSocketFactory)
    //@Override
    /*public*/ AbstractMaleSocket* encapsulateMaleSocket(BaseManager/*<MaleAnalogExpressionSocket>*/* manager, AbstractMaleSocket* maleSocket)override {

        if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleAnalogExpressionSocket(manager, maleSocket);
    }

};
Q_DECLARE_INTERFACE(DebuggerMaleAnalogExpressionSocketFactory, "DebuggerMaleAnalogExpressionSocketFactory")
#endif // DEBUGGERMALEANALOGEXPRESSIONFACTORY_H
