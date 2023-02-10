#include "debuggermalestringexpressionsocketfactory.h"
#include "malestringexpressionsocket.h"
#include "instancemanager.h"
#include "defaultlogixngpreferences.h"
#include "debuggermalestringexpressionsocket.h"
/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleStringExpressionSocketFactory.class)
//public class DebuggerMaleStringExpressionSocketFactory implements MaleStringExpressionSocketFactory {

    //@Override
    /*public*/ /*MaleStringExpressionSocket*/AbstractMaleSocket *DebuggerMaleStringExpressionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleStringExpressionSocket>*/* manager, /*MaleStringExpressionSocket*/AbstractMaleSocket *maleSocket) {

        if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleStringExpressionSocket(manager, (MaleStringExpressionSocket*)maleSocket->bself());
    }
