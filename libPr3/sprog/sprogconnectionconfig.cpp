#include "sprogconnectionconfig.h"
#include <QSysInfo>
#include "serialdriveradapter.h"

using namespace Sprog;
/**
 * Definition of objects to handle configuring a layout connection via an SPROG
 * SerialDriverAdapter object.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003
  */
///*public*/ class ConnectionConfig extends jmri.jmrix.AbstractSerialConnectionConfig {

/**
 * Ctor for an object being created during load process; Swing init is
 * deferred.
 */
/*public*/ SprogConnectionConfig::SprogConnectionConfig(SerialPortAdapter* p, QObject* parent) : AbstractSerialConnectionConfig(p, parent)
{
    //super(p);
}

/**
 * Ctor for a functional Swing object with no prexisting adapter
 */
/*public*/ SprogConnectionConfig::SprogConnectionConfig(QObject* parent) : AbstractSerialConnectionConfig(parent)
{
    //super();
}

//@Override
/*public*/ QString SprogConnectionConfig::name() {
    return "SPROG";
}

//@Override
/*protected*/ QStringList SprogConnectionConfig::getPortFriendlyNames() {
#ifdef Q_OS_WIN
 QStringList l = QStringList() << "SPROG";
 return l;
#endif
    return QStringList();
}

//@Override
/*protected*/ void SprogConnectionConfig::setInstance() {
    if(adapter == NULL) {
       adapter = new SerialDriverAdapter();
    }
}
