#include "jmriclientportcontroller.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclienttrafficcontroller.h"

//JMRIClientPortController::JMRIClientPortController()
//{

//}
/**
 * Abstract base for classes representing a JMRIClient communications port
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2008, 2010
 * @author Paul Bender Copyright (C) 2010
  */
// /*public*/ abstract class JMRIClientPortController extends jmri.jmrix.AbstractNetworkPortController {

// base class. Implementations will provide InputStream and OutputStream
// objects to JMRIClientTrafficController classes, who in turn will deal in messages.
/*protected*/ JMRIClientPortController::JMRIClientPortController(JMRIClientSystemConnectionMemo* connectionMemo)
 : AbstractNetworkPortController(connectionMemo){
    //super(connectionMemo);
    allowConnectionRecovery=true;
    setConnectionTimeout(30000);
}

//@Override
/*public*/ SystemConnectionMemo* JMRIClientPortController::getSystemConnectionMemo() {
    return (JMRIClientSystemConnectionMemo*) AbstractNetworkPortController::getSystemConnectionMemo();
}

//@Override
/*protected*/ void JMRIClientPortController::resetupConnection() {
   // reconnect the port to the traffic controller.
   ((JMRIClientSystemConnectionMemo*)getSystemConnectionMemo())->getJMRIClientTrafficController()->connectPort(this);
   // notify the memo that we've restarted, so it can ask the associated
   // managers to refresh status
   ((JMRIClientSystemConnectionMemo*)getSystemConnectionMemo())->requestAllStatus();
}


