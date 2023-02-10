#include "debuggermaledigitalactionsocketfactory.h"
#include "instancemanager.h"
#include "debuggermaledigitalactionsocket.h"
#include "defaultlogixngpreferences.h"
#include "abstractmalesocket.h"

/**
 *
 * @author daniel
 */
//@ServiceProvider(service = MaleDigitalActionSocketFactory.class)
//public class DebuggerMaleDigitalActionSocketFactory implements MaleDigitalActionSocketFactory {

    //@Override
    /*public*/ AbstractMaleSocket *DebuggerMaleDigitalActionSocketFactory::encapsulateMaleSocket(BaseManager/*<MaleDigitalActionSocket>*/* manager, AbstractMaleSocket *maleSocket) {

        if (! ((DefaultLogixNGPreferences*)InstanceManager::getDefault("LogixNGPreferences"))->getInstallDebugger()) {
            return maleSocket;
        }
        QString sys = maleSocket->getSystemName();
        return new DebuggerMaleDigitalActionSocket(manager, (MaleDigitalActionSocket*)maleSocket->bself());
    }
