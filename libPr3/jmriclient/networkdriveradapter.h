#ifndef NETWORKDRIVERADAPTER_H
#define NETWORKDRIVERADAPTER_H
#include "jmriclientportcontroller.h"

class ZeroConfClient;
class NetworkDriverAdapter : public JMRIClientPortController
{
 Q_OBJECT
public:
 NetworkDriverAdapter(QObject* parent = nullptr);
 /*public*/ void configure() override;
 /*public*/ bool status() override;
 QT_DEPRECATED static /*public*/ NetworkDriverAdapter* instance();
 /*public*/ void setMdnsConfigure(bool autoconfig) override;
 /*public*/ bool getMdnsConfigure() override;
 /*public*/ void autoConfigure() override;
 /*public*/ QString getAdvertisementName() override;
 /*public*/ QString getServiceType() override;
 /*public*/ QString className() override;

private:
 static Logger* log;

 // private control members
 /*private*/ bool opened = false;
 /*private*/ bool mDNSConfigure = false;
 ZeroConfClient* mdnsClient = nullptr;

};

#endif // NETWORKDRIVERADAPTER_H
