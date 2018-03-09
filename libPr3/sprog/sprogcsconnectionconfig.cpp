#include "sprogcsconnectionconfig.h"
#include "sprogcsserialdriveradapter.h"

using namespace Sprog;
/**
 * Definition of objects to handle configuring a layout connection via an SPROG
 * SerialDriverAdapter object.
 *
 * @author Andrew Crosland Copyright (C) 2006
  */
///*public*/ class ConnectionConfig extends jmri.jmrix.AbstractSerialConnectionConfig {

/**
 * Ctor for an object being created during load process; Swing init is
 * deferred.
 */
/*public*/ SprogCSConnectionConfig::SprogCSConnectionConfig(SerialPortAdapter* p, QObject* parent)
 : AbstractSerialConnectionConfig(p, parent)
{
    //super(p);
}

/**
 * Ctor for a functional Swing object with no prexisting adapter
 */
/*public*/ SprogCSConnectionConfig::SprogCSConnectionConfig(QObject* parent) : AbstractSerialConnectionConfig(parent)
{
    //super();
}

//@Override
/*public*/ QString SprogCSConnectionConfig::name() {
    return tr("SPROG Command Station");
}

//@Override
/*public*/ QString SprogCSConnectionConfig::getManufacturer() {
    return adapter->getManufacturer();
}

//@Override
/*public*/ void SprogCSConnectionConfig::setManufacturer(QString manu) {
    adapter->setManufacturer(manu);
}
/*
 * //@Override
 protected QVector<QString> getPortFriendlyNames() {
 System.out.println("Port names called");
 Vector<String> portNameVector = new Vector<String>();
 if(System.getProperty("os.name").toLowerCase().contains("windows")){
 portNameVector.add("SPROG");
 }
 System.out.println("Port names called" + portNameVector);
 return portNameVector;
 }*/

//@Override
/*protected*/ QStringList SprogCSConnectionConfig::getPortFriendlyNames() {
#ifdef OS_WIN
        return QStringList() << "SPROG";
#endif
    return QStringList();
}

//@Override
/*protected*/ void SprogCSConnectionConfig::setInstance() {
    if(adapter == NULL ) {
       adapter = new SprogCSSerialDriverAdapter();
    }
}
