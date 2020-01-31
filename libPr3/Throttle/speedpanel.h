#ifndef SPEEDPANEL_H
#define SPEEDPANEL_H
#include <QDockWidget>
#include "dccthrottle.h"
#include "addresspanel.h"
#include "addresslistener.h"

class QLabel;
class Logger;
class SpeedPanel : public QDockWidget, public AddressListener
{
 Q_OBJECT
 Q_INTERFACES(AddressListener)
public:
 SpeedPanel(QWidget* parent = 0);
 /*public*/ void setAddressPanel(AddressPanel* addressPanel);
 /*public*/ void destroy();
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ void notifyAddressChosen(locoAddress* l);
 /*public*/ void notifyAddressReleased(locoAddress* la);
 /*public*/ void notifyAddressThrottleFound(DccThrottle* t);
 /*public*/ void notifyConsistAddressChosen(int newAddress, bool isLong);
 /*public*/ void notifyConsistAddressReleased(int address, bool isLong);
 /*public*/ void notifyConsistAddressThrottleFound(DccThrottle* throttle);
 QObject* self() {return (QObject*)this;}


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ControlPanel");
 /*private*/ DccThrottle* throttle = nullptr;
 /*private*/ QWidget* mainPanel;
 /*private*/ QWidget* speedDisplayPanel;
 /*private*/ QLabel* scaleSpeedLabel;// = new JLabel("", JLabel.CENTER);
 // tracks whether we are using speed profiles
 /*private*/ bool useSpeedProfile = false;
 // last known direction
 /*private*/ bool currentIsForward;// = true;
 /*private*/ float currentThrottleVol;// = 0.0f;
 //for access to roster entry
 /*private*/ AddressPanel* addressPanel; //for access to roster entry
 /*private*/ void initGUI();
 /*private*/ QString updateSpeedLabel(bool useSpeedProfile, float throttleVolume, bool isForward);

};

#endif // SPEEDPANEL_H
