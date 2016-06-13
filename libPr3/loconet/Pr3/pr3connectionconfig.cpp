#include "pr3connectionconfig.h"
#include "pr3adapter.h"


Pr3ConnectionConfig::Pr3ConnectionConfig(QObject *parent) :
    AbstractSerialConnectionConfig(parent)
{
}
/**
 * Definition of objects to handle configuring a PR3 layout connection
 * via a PR2Adapter object.
 *
 * @author      Bob Jacobsen   Copyright (C) 2001, 2003, 2008, 2010
 * @version	$Revision: 21848 $
 */
// /*public*/ class ConnectionConfig  : public AbstractSerialConnectionConfig {

/**
 * Ctor for an object being created during load process;
 * Swing init is deferred.
 */
/*public*/ Pr3ConnectionConfig::Pr3ConnectionConfig(PR3Adapter* p, QObject *parent)
    : AbstractSerialConnectionConfig((PortAdapter*)p, parent)
{
 //super(p);
    Q_ASSERT(adapter != NULL);
 setObjectName("Pr3ConnectionConfig");
}

/**
 * Ctor for a functional Swing object with no prexisting adapter
 */
///*public*/ ConnectionConfig() {
//    super();
//}

/*public*/ QString Pr3ConnectionConfig::name() { return "LocoNet PR3"; }

/*public*/ bool Pr3ConnectionConfig::isOptList2Advanced() { return false; }

//@Override
/*protected*/ QStringList Pr3ConnectionConfig::getPortFriendlyNames()
{
 QStringList list = QStringList();
//    if(SystemType.isWindows()){
//        return new String[]{"Communications Port"};
//    }
 return list;
}

/*protected*/ void Pr3ConnectionConfig::setInstance()
{
 if (adapter == NULL)
   adapter = (SerialPortAdapter*)new PR3Adapter();
}

