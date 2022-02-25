#include "debuggermalestringexpressionsocketfactory.h"
#include "malestringexpressionsocket.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "debuggermalestringexpressionsocket.h"
/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleStringExpressionSocketFactory.class)
//public class DebuggerMaleStringExpressionSocketFactory implements MaleStringExpressionSocketFactory {

    //@Override
    /*public*/ MaleStringExpressionSocket* encapsulateMaleSocket(BaseManager/*<MaleStringExpressionSocket>*/* manager, MaleStringExpressionSocket* maleSocket) {

        if (! ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleStringExpressionSocket(manager, maleSocket);
    }
