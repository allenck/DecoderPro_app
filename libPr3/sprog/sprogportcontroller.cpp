#include "sprogportcontroller.h"

using namespace Sprog;
/*
 * Identifying class representing a SPROG communications port.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2008
 */
///*public*/ abstract class SprogPortController extends jmri.jmrix.AbstractSerialPortController {

// Base class. Implementations will provide InputStream and OutputStream
// objects to SprogTrafficController classes, who in turn will deal in messages.
/*protected*/ SprogPortController::SprogPortController(SprogSystemConnectionMemo* connectionMemo, QObject* parent) : AbstractSerialPortController(connectionMemo, parent) {
    //super(connectionMemo);
}

//@Override
/*public*/ SprogSystemConnectionMemo* SprogPortController::getSystemConnectionMemo() {
    return (SprogSystemConnectionMemo*) AbstractSerialPortController::getSystemConnectionMemo();
}
