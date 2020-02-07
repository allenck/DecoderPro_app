#include "pr2connectionconfig.h"
#include "pr2adapter.h"

/**
 * Definition of objects to handle configuring an PR2 layout connection via a
 * PR2Adapter object.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
  */
// /*public*/ class ConnectionConfig extends jmri.jmrix.AbstractSerialConnectionConfig {

/**
 * Ctor for an object being created during load process; Swing init is
 * deferred.
 */
/*public*/ Pr2ConnectionConfig::Pr2ConnectionConfig(SerialPortAdapter* p, QObject* parent)
 : AbstractSerialConnectionConfig(p, parent){
    //super(p);
}

/**
 * Ctor for a functional Swing object with no prexisting adapter
 */
/*public*/ Pr2ConnectionConfig::Pr2ConnectionConfig(QObject* parent)
 : AbstractSerialConnectionConfig(parent)
{
    //super();
}

//@Override
/*public*/ QString Pr2ConnectionConfig::name() {
    return "LocoNet PR2"; // NOI18N
}

//@Override
/*protected*/ void Pr2ConnectionConfig::setInstance() {
    if (adapter == nullptr) {
        adapter = new PR2Adapter();
    }
}

