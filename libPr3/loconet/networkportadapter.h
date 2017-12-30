#ifndef NETWORKPORTADAPTER_H
#define NETWORKPORTADAPTER_H
#include "portadapter.h"
#include "exceptions.h"

class NetworkPortAdapter : public PortAdapter
{
 Q_OBJECT
public:
 explicit NetworkPortAdapter(QObject *parent = 0) : PortAdapter(parent) {}
 /**
  * Enables basic setup of a network interface for a jmrix implementation. Based
  * upon work by Bob Jacobsen from SerialPortAdapter
  *
  * @author Kevin Dickerson Copyright (C) 2010
  * @author	Bob Jacobsen Copyright (C) 2010
  * @version	$Revision: 28746 $
  * @see jmri.jmrix.NetworkConfigException
  */
 //public interface NetworkPortAdapter extends PortAdapter {

 /**
  * Connects to the end device using a hostname/ip address and port
  */
 /*public*/ virtual void _connect(QString /*host*/, int /*port*/) {} // throw (Exception)

 /**
  * Configure all of the other jmrix widgets needed to work with this adapter
  */
 /*public*/ virtual void configure() {}

 /**
  * Query the status of this connection. If all OK, at least as far as is
  * known, return true
  */
 /*public*/ virtual bool status() {return false;}

 /**
  * Remember the associated port name
  *
  * @param s
  */
 /*public*/ virtual void setPort(QString /*s*/) {}

 /*public*/ virtual void setPort(int /*s*/) {}

 /*public*/ virtual int getPort() {return 0;}

 /*public*/ virtual QString getCurrentPortName() {return "";}

 /*public*/ virtual void setHostName(QString /*hostname*/) {}

 /*public*/ virtual QString getHostName() {return "";}

 /*
  * Set whether or not this adapter should be
  * configured automatically via MDNS.
  */
 /*public*/ virtual void setMdnsConfigure(bool /*autoconfig*/) {}

 /*
  * Get whether or not this adapter is configured
  * to use autoconfiguration via MDNS
  */
 /*public*/ virtual bool getMdnsConfigure() {return false;}

 /*
  * perform the automatic configuration
  */
 /*public*/ virtual void autoConfigure() {}

 /*
  * Get and set the ZeroConf/mDNS advertisement name.
  */
 /*public*/ virtual void setAdvertisementName(QString /*AdName*/) {}

 /*public*/ virtual QString getAdvertisementName()  {return "";}

 /*
  * Get and set the ZeroConf/mDNS service type.
  */
 /*public*/ virtual void setServiceType(QString /*ServiceType*/) {}

 /*public*/ virtual QString getServiceType()  {return "";}

signals:

public slots:

};

#endif // NETWORKPORTADAPTER_H
