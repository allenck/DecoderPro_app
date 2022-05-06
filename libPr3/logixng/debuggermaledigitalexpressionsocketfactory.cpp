#include "debuggermaledigitalexpressionsocketfactory.h"
#include "instancemanager.h"
#include "defaultlogixngpreferences.h"
#include "maledigitalexpressionsocket.h"
#include "debuggermaledigitalexpressionsocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleDigitalExpressionSocketFactory.class)
//public class DebuggerMaleDigitalExpressionSocketFactory implements MaleDigitalExpressionSocketFactory {

    //@Override
    /*public*/ /*MaleDigitalExpressionSocket*/MaleSocket *DebuggerMaleDigitalExpressionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager, /*MaleDigitalExpressionSocket*/MaleSocket *maleSocket) {

        if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleDigitalExpressionSocket(manager, (MaleDigitalExpressionSocket*)maleSocket->bself());
    }
