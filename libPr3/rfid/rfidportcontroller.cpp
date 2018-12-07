#include "rfidportcontroller.h"

/**
 * Abstract base for classes representing a communications port
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2006, 2007, 2008
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
///*public*/ abstract class RfidPortController extends jmri.jmrix.AbstractSerialPortController {
// base class. Implementations will provide InputStream and OutputStream
// objects to SerialTrafficController classes, who in turn will deal in messages.

/*protected*/ RfidPortController::RfidPortController(RfidSystemConnectionMemo* connectionMemo, QObject *parent) : AbstractSerialPortController((SystemConnectionMemo*)connectionMemo, parent){
    //super(connectionMemo);
}

//@Override
/*public*/ SystemConnectionMemo *RfidPortController::getSystemConnectionMemo() {
    return AbstractSerialPortController::getSystemConnectionMemo();
}

