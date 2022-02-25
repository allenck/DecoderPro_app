#include "debuggermaledigitalexpressionsocketfactory.h"
#include "instancemanager.h"
#include "logixngpreferences.h"
#include "maledigitalexpressionsocket.h"
#include "debuggermaledigitalexpressionsocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleDigitalExpressionSocketFactory.class)
//public class DebuggerMaleDigitalExpressionSocketFactory implements MaleDigitalExpressionSocketFactory {

    //@Override
    /*public*/ MaleDigitalExpressionSocket* encapsulateMaleSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager, MaleDigitalExpressionSocket* maleSocket) {

        if (! ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleDigitalExpressionSocket(manager, maleSocket);
    }
