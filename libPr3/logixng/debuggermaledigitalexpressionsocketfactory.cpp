#include "debuggermaledigitalexpressionsocketfactory.h"
#include "instancemanager.h"
#include "defaultlogixngpreferences.h"
#include "maledigitalexpressionsocket.h"
#include "debuggermaledigitalexpressionsocket.h"
#include "abstractmalesocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleDigitalExpressionSocketFactory.class)
//public class DebuggerMaleDigitalExpressionSocketFactory implements MaleDigitalExpressionSocketFactory {

    //@Override
    /*public*/ /*MaleDigitalExpressionSocket*/AbstractMaleSocket *DebuggerMaleDigitalExpressionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager, /*MaleDigitalExpressionSocket*/AbstractMaleSocket *maleSocket) {

        if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleDigitalExpressionSocket(manager, (MaleDigitalExpressionSocket*)maleSocket->bself());
    }
