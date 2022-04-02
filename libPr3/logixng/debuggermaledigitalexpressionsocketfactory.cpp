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
    /*public*/ /*MaleDigitalExpressionSocket*/MaleSocket *DebuggerMaleDigitalExpressionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager, /*MaleDigitalExpressionSocket*/MaleSocket *maleSocket) {

        if (! ((LogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }

        return new DebuggerMaleDigitalExpressionSocket(manager, (MaleDigitalExpressionSocket*)maleSocket->bself());
    }
