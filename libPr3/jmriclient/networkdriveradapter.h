#ifndef NETWORKDRIVERADAPTER_H
#define NETWORKDRIVERADAPTER_H
#include "jmriclientportcontroller.h"

class ZeroConfClient;
class NetworkDriverAdapter : public JMRIClientPortController
{
public:
 NetworkDriverAdapter(QObject* parent = nullptr);
 /*public*/ void configure();
 /*public*/ bool status();
 QT_DEPRECATED static /*public*/ NetworkDriverAdapter* instance();
 /*public*/ void setMdnsConfigure(bool autoconfig);
 /*public*/ bool getMdnsConfigure();
 /*public*/ void autoConfigure();
 /*public*/ QString getAdvertisementName();
 /*public*/ QString getServiceType();
 /*public*/ QString className();

private:
 static Logger* log;

 // private control members
 /*private*/ bool opened = false;
 /*private*/ bool mDNSConfigure = false;
 ZeroConfClient* mdnsClient = nullptr;

};

#endif // NETWORKDRIVERADAPTER_H
