#ifndef BACKGROUNDPANEL_H
#define BACKGROUNDPANEL_H
#include "resizableimagepanel.h"
#include "addresspanel.h"
#include "addresslistener.h"

class BackgroundPanel : public ResizableImagePanel, public AddressListener
{
 Q_OBJECT
 Q_INTERFACES(AddressListener)
public:
 BackgroundPanel(QWidget* parent = nullptr);
 /*public*/ void setAddressPanel(AddressPanel* addressPanel);

public slots:
 /*public*/ void notifyAddressThrottleFound(DccThrottle* t);
 /*public*/ void notifyAddressReleased(LocoAddress* la) ;
 /*public*/ void notifyAddressChosen(LocoAddress* l);
 /*public*/ void notifyConsistAddressChosen(int newAddress, bool isLong);
 /*public*/ void notifyConsistAddressReleased(int address, bool isLong);
 /*public*/ void notifyConsistAddressThrottleFound(DccThrottle* throttle);

private:
 AddressPanel* addressPanel;// = null;

};

#endif // BACKGROUNDPANEL_H
