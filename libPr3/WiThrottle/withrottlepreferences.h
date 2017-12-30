#ifndef WITHROTTLEPREFERENCES_H
#define WITHROTTLEPREFERENCES_H
#include "abstractwithrottlepreferences.h"

class WiThrottlePreferences : public AbstractWiThrottlePreferences
{
public:
 WiThrottlePreferences();
 /*public*/ WiThrottlePreferences(QString fileName);

 /*public*/ static /*final*/ int DEFAULT_PORT;// = 12090;
 /*public*/ bool isRestartRequired();
 /*public*/ bool isUseEStop();
 /*public*/ void setUseEStop(bool value);
 /*public*/ int getEStopDelay();
 /*public*/ void setEStopDelay(int value);
 /*public*/ bool isUseMomF2();
 /*public*/ void setUseMomF2(bool value);
 /*public*/ int getPort();
 /*public*/ void setPort(int value) ;
 /*public*/ bool isAllowTrackPower();
 /*public*/ void setAllowTrackPower(bool value);
 /*public*/ bool isAllowTurnout();
 /*public*/ void setAllowTurnout(bool value);
 /*public*/ bool isAllowRoute();
 /*public*/ void setAllowRoute(bool value);
 /*public*/ bool isAllowConsist();
 /*public*/ void setAllowConsist(bool value);
 /*public*/ bool isUseWiFiConsist();
 /*public*/ void setUseWiFiConsist(bool value);
 /*public*/ void load(QDomElement child);
 /*public*/ bool compareValuesDifferent(WiThrottlePreferences* prefs);
 /*public*/ void apply(WiThrottlePreferences* prefs);
 /*public*/ QDomElement store();
 /*public*/ bool isDirty();

private:
 void common();
 //  Flag that restart is required to apply preferences
 /*private*/ bool _isRestartRequired;// = false;

 /*private*/ bool useEStop;// = true;
 /*private*/ int eStopDelay;// = 10;

 /*private*/ bool useMomF2;// = true;

 /*private*/ int port;// = DEFAULT_PORT;

 /*private*/ bool allowTrackPower;// = true;
 /*private*/ bool allowTurnout;// = true;
 /*private*/ bool allowRoute;// = true;
 /*private*/ bool allowConsist;// = true;
 /*private*/ bool useWiFiConsist;// = true;

 // track as loaded / as saved state
 /*private*/ bool asLoadedUseEStop;// = true;
 /*private*/ int asLoadedEStopDelay;// = 10;

 /*private*/ bool asLoadedUseMomF2;// = true;

 /*private*/ int asLoadedPort;// = 0;

 /*private*/ bool asLoadedAllowTrackPower;// = true;
 /*private*/ bool asLoadedAllowTurnout;// = true;
 /*private*/ bool asLoadedAllowRoute;// = true;
 /*private*/ bool asLoadedAllowConsist;// = true;
 /*private*/ bool asLoadedUseWiFiConsist;// = true;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(WiThrottlePreferences.class);


};

#endif // WITHROTTLEPREFERENCES_H
