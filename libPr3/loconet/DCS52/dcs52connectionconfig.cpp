#include "dcs52connectionconfig.h"
#include "usbdcs52adapter.h"
/**
 * Definition of objects to handle configuring a DCS52 USB layout connection via a
 * PR2Adapter object.
 * <p>
 * Copied from loconet.pr3.ConnectionConfig.java
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003, 2008, 2010
 * @author B. Milhaupt Copyright (C) 2019
 */

//public class ConnectionConfig extends jmri.jmrix.AbstractSerialConnectionConfig {

    /**
     * Ctor for an object being created during load process; Swing init is
     * deferred.
     *
     * @param p the SerialPortAdapter to associate with this connection
     */
    /*public*/ DCS52ConnectionConfig::DCS52ConnectionConfig(SerialPortAdapter* p, QObject* parent)
      : AbstractSerialConnectionConfig(p, parent)
    {
        //super(p);
    }

    /**
     * Ctor for a connection configuration with no preexisting adapter.
     * {@link #setInstance()} will fill the adapter member.
     */
    /*public*/ DCS52ConnectionConfig::DCS52ConnectionConfig(QObject* parent)
     : AbstractSerialConnectionConfig(parent)
    {
        //super();
    }

    //@Override
    /*public*/ QString DCS52ConnectionConfig::name() {
        return "DCS52 USB Interface"; // NOI18N
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ void DCS52ConnectionConfig::setInstance() {
        if (adapter == nullptr) {
            adapter = new UsbDcs52Adapter();
        }
    }
