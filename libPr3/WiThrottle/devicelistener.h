#ifndef DEVICELISTENER_H
#define DEVICELISTENER_H
#include "eventlistener.h"
#include "deviceserver.h"

/**
 * WiThrottle Interface to let a class know of device status changes.
 *
 * @author Brett Hoffman Copyright (C) 2009
 * @author Created by Brett Hoffman on:
 * @author 11/18/09.
 */


/*public*/ /*interface*/ class DeviceListener : public  EventListener {
 Q_OBJECT

public slots:
    /**
     * A new device has connected.
     *
     */
    /*public*/ virtual void notifyDeviceConnected(WiDevice* /*device*/) {}

    /**
     * A device has quit and needs to be removed.
     *
     */
    /*public*/ virtual void notifyDeviceDisconnected(WiDevice* /*device*/) {}

    /**
     * A device has changed its address.
     *
     */
    /*public*/ virtual void notifyDeviceAddressChanged(WiDevice* /*device*/) {}

    /**
     * Some info (name, UDID) about the device has changed. Also used to detect
     * duplicate of same device.
     *
     */
    /*public*/ virtual void notifyDeviceInfoChanged(WiDevice* /*device*/) {}

};

#endif // DEVICELISTENER_H
