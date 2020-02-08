#include "locobufferiiconnectionconfig.h"
#include "locobufferiiadapter.h"

/**
 * Definition of objects to handle configuring a LocoBuffer-II layout
 * connection via a LocoBufferIIAdapter object.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
 */
//public class ConnectionConfig extends jmri.jmrix.AbstractSerialConnectionConfig {

    /**
     * Ctor for an object being created during load process; Swing init is
     * deferred.
     * @param p the SerialPortAdapter to associate with this connection
     */
    /*public*/ LocoBufferIIConnectionConfig::LocoBufferIIConnectionConfig(SerialPortAdapter* p, QObject* parent)
      : AbstractSerialConnectionConfig(p, parent)
    {
        //super(p);
    }

    /**
     * Ctor for a connection configuration with no preexisting adapter.
     * {@link #setInstance()} will fill the adapter member.
     */
    /*public*/ LocoBufferIIConnectionConfig::LocoBufferIIConnectionConfig(QObject* parent)
      : AbstractSerialConnectionConfig(parent)
    {
        //super();
    }

    //@Override
    /*public*/ QString LocoBufferIIConnectionConfig::name() {
        return "LocoNet LocoBuffer-II"; // NOI18N
    }

    /*public*/ bool LocoBufferIIConnectionConfig::isOptList2Advanced() {
        return false;
    }

    //@Override
    /*protected*/ void LocoBufferIIConnectionConfig::setInstance() {
        if (adapter == nullptr) {
            adapter = new LocoBufferIIAdapter();
        }
    }
