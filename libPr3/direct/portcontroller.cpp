#include "portcontroller.h"
#include "otherconnectiontypelist.h"

/*
 * Identifying class representing a direct-drive communications port.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2004
 */
//public abstract class PortController extends jmri.jmrix.AbstractSerialPortController {
    // base class. Implementations will provide InputStream and OutputStream
    // objects to TrafficController classes, who in turn will deal in messages.

    /*protected*/ PortController::PortController(DirectSystemConnectionMemo* memo, QObject *parent) : AbstractSerialPortController(memo, parent){
        //super(memo);
        this->manufacturerName = OtherConnectionTypeList::OTHER;
    }

    /*protected*/ PortController::PortController(QObject *parent) : AbstractSerialPortController(new DirectSystemConnectionMemo(), parent) {
        //this(new DirectSystemConnectionMemo());
    }

