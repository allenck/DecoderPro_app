#ifndef SPEEDPANEL_H
#define SPEEDPANEL_H
#include <QDockWidget>
#include "dccthrottle.h"
#include "addresspanel.h"

class QLabel;
class Logger;
class SpeedPanel : public QDockWidget
{
 Q_OBJECT
public:
 SpeedPanel(QWidget* parent = 0);
 /*public*/ void setAddressPanel(AddressPanel* addressPanel);
 /*public*/ void destroy();
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement e);

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ void notifyAddressChosen(LocoAddress* l);
 /*public*/ void notifyAddressReleased(LocoAddress* la);
 /*public*/ void notifyAddressThrottleFound(DccThrottle* t);
 /*public*/ void notifyConsistAddressChosen(int newAddress, bool isLong);
 /*public*/ void notifyConsistAddressReleased(int address, bool isLong);
 /*public*/ void notifyConsistAddressThrottleFound(DccThrottle* throttle);


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ControlPanel");
 /*private*/ DccThrottle* throttle;
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
