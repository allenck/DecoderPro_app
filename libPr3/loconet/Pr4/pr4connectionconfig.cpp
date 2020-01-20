#include "pr4connectionconfig.h"
#include "pr4adapter.h"
/**
 * Definition of objects to handle configuring a PR4 layout connection via a
 * PR2Adapter object.
 * <p>
 * Copied from loconet.pr3.ConnectionConfig
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003, 2008, 2010
 * @author B. Milhaupt Copyright (C) 2019
 */

///*public*/ class ConnectionConfig extends jmri.jmrix.AbstractSerialConnectionConfig {

/**
 * Ctor for an object being created during load process; Swing init is
 * deferred.
 *
 * @param p   Serial port adapter for the connection
 */
/*public*/ PR4ConnectionConfig::PR4ConnectionConfig(SerialPortAdapter* p, QObject* parent)
 : AbstractSerialConnectionConfig(p, parent) {
    //super(p);
}

/**
 * Ctor for a connection configuration with no preexisting adapter.
 * {@link #setInstance()} will fill the adapter member.
 */
/*public*/ PR4ConnectionConfig::PR4ConnectionConfig(QObject* parent) : AbstractSerialConnectionConfig(parent) {
    //super();
}

/**
 * Get the connection type name.
 *
 * @return Connection type name
 */
//@Override
/*public*/ QString PR4ConnectionConfig::name() {
    return "LocoNet PR4"; // NOI18N
}

/**
 * Is Option List 2 Advanced?
 * @return bool, always false
 */
/*public*/ bool PR4ConnectionConfig::isOptList2Advanced() {
    return false;
}

//@Override
/*protected*/ QStringList PR4ConnectionConfig::getPortFriendlyNames() {
//    if (SystemType.isWindows())
//    {
//        return new QStringList{"Communications Port"}; // NOI18N
//    }
    return  QStringList();
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void PR4ConnectionConfig::setInstance() {
    if (adapter == nullptr) {
        adapter = new PR4Adapter();
    }
}
