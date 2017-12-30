#include "withrottlepreferences.h"
#include "logger.h"
#include "loggerfactory.h"

//WiThrottlePreferences::WiThrottlePreferences()
//{

//}
/**
 * @author Brett Hoffman Copyright (C) 2010
 */
// /*public*/ class WiThrottlePreferences extends AbstractWiThrottlePreferences {

/*public*/ /*static*/ /*final*/ int WiThrottlePreferences::DEFAULT_PORT = 12090;


/*public*/ WiThrottlePreferences::WiThrottlePreferences(QString fileName) : AbstractWiThrottlePreferences(){
    //super.openFile(fileName);
 common();
 AbstractWiThrottlePreferences::openFile(fileName);

}

/*public*/ WiThrottlePreferences::WiThrottlePreferences() {
 common();
}

void WiThrottlePreferences::common()
{
 //  Flag that restart is required to apply preferences
 _isRestartRequired = false;
 useEStop = true;
 eStopDelay = 10;
 useMomF2 = true;
 port = DEFAULT_PORT;

 allowTrackPower = true;
 allowTurnout = true;
 allowRoute = true;
 allowConsist = true;
 useWiFiConsist = true;
// track as loaded / as saved state
 asLoadedUseEStop = true;
 asLoadedEStopDelay = 10;
 asLoadedUseMomF2 = true;
 asLoadedPort = 0;
 asLoadedAllowTrackPower = true;
 asLoadedAllowTurnout = true;
 asLoadedAllowRoute = true;
 asLoadedAllowConsist = true;
 asLoadedUseWiFiConsist = true;

}
#if 1
////@Override
/*public*/ void WiThrottlePreferences::load(QDomElement child) {
    QString a;
    if ((a = child.attribute("isUseEStop")) != NULL) {
        setUseEStop(a.toLower() == ("true"));
        this->asLoadedUseEStop = this->isUseEStop();
    }
    if ((a = child.attribute("getEStopDelay")) != NULL) {
        try {
            setEStopDelay(a.toInt());
            this->asLoadedEStopDelay = this->getEStopDelay();
        } catch (NumberFormatException e) {
            log->debug(e.getLocalizedMessage());
        }
    }
    if ((a = child.attribute("isUseMomF2")) != NULL) {
        setUseMomF2(a.toLower() == ("true"));
        this->asLoadedUseMomF2 = this->isUseMomF2();
    }
    if ((a = child.attribute("getPort")) != NULL) {
        try {
            setPort(a.toInt());
        } catch (DataConversionException ex) {
            log->error("Port {} is invalid.", a);
        }
        this->asLoadedPort = this->getPort();
    }

    if ((a = child.attribute("isAllowTrackPower")) != NULL) {
        setAllowTrackPower(a.toLower() == ("true"));
        this->asLoadedAllowTrackPower = this->isAllowTrackPower();
    }
    if ((a = child.attribute("isAllowTurnout")) != NULL) {
        setAllowTurnout(a.toLower() == ("true"));
        this->asLoadedAllowTurnout = this->isAllowTurnout();
    }
    if ((a = child.attribute("isAllowRoute")) != NULL) {
        setAllowRoute(a.toLower() == ("true"));
        this->asLoadedAllowRoute = this->isAllowRoute();
    }
    if ((a = child.attribute("isAllowConsist")) != NULL) {
        setAllowConsist(a.toLower() == ("true"));
        this->asLoadedAllowConsist = this->isAllowConsist();
    }
    if ((a = child.attribute("isUseWiFiConsist")) != NULL) {
        setUseWiFiConsist(a.toLower() == ("true"));
        this->asLoadedUseWiFiConsist = this->isUseWiFiConsist();
    }

}

/*public*/ bool WiThrottlePreferences::compareValuesDifferent(WiThrottlePreferences* prefs) {
    if (isAllowTrackPower() != prefs->isAllowTrackPower()) {
        return true;
    }
    if (isAllowTurnout() != prefs->isAllowTurnout()) {
        return true;
    }
    if (isAllowRoute() != prefs->isAllowRoute()) {
        return true;
    }
    if (isAllowConsist() != prefs->isAllowConsist()) {
        return true;
    }
    if (isUseWiFiConsist() != prefs->isUseWiFiConsist()) {
        return true;
    }

    if (isUseEStop() != prefs->isUseEStop()) {
        return true;
    }
    if (getEStopDelay() != prefs->getEStopDelay()) {
        return true;
    }
    if (isUseMomF2() != prefs->isUseMomF2()) {
        return true;
    }
    return getPort() != prefs->getPort();
}

/*public*/ void WiThrottlePreferences::apply(WiThrottlePreferences* prefs) {
    setUseEStop(prefs->isUseEStop());
    setEStopDelay(prefs->getEStopDelay());
    setUseMomF2(prefs->isUseMomF2());
    setPort(prefs->getPort());
    setAllowTrackPower(prefs->isAllowTrackPower());
    setAllowTurnout(prefs->isAllowTurnout());
    setAllowRoute(prefs->isAllowRoute());
    setAllowConsist(prefs->isAllowConsist());
    setUseWiFiConsist(prefs->isUseWiFiConsist());
}

//@Override
/*public*/ QDomElement WiThrottlePreferences::store() {
 QDomDocument doc = QDomDocument();
    if (this->isDirty()) {
        this->_isRestartRequired = true;
    }
    QDomElement element =  doc.createElement("WiThrottlePreferences");
    element.setAttribute("isUseEStop", "" + isUseEStop());
    this->asLoadedUseEStop = this->isUseEStop();
    element.setAttribute("getEStopDelay", "" + getEStopDelay());
    this->asLoadedEStopDelay = this->getEStopDelay();
    element.setAttribute("isUseMomF2", "" + isUseMomF2());
    this->asLoadedUseMomF2 = this->isUseMomF2();
    element.setAttribute("getPort", "" + getPort());
    this->asLoadedPort = this->getPort();
    element.setAttribute("isAllowTrackPower", "" + isAllowTrackPower());
    this->asLoadedAllowTrackPower = this->isAllowTrackPower();
    element.setAttribute("isAllowTurnout", "" + isAllowTurnout());
    this->asLoadedAllowTurnout = this->isAllowTurnout();
    element.setAttribute("isAllowRoute", "" + isAllowRoute());
    this->asLoadedAllowRoute = this->isAllowRoute();
    element.setAttribute("isAllowConsist", "" + isAllowConsist());
    this->asLoadedAllowConsist = this->isAllowConsist();
    element.setAttribute("isUseWiFiConsist", "" + isUseWiFiConsist());
    this->asLoadedUseWiFiConsist = this->isUseWiFiConsist();
    return element;
}

/*public*/ bool WiThrottlePreferences::isDirty() {
    return this->asLoadedUseEStop != this->isUseEStop()
            || this->asLoadedEStopDelay != this->getEStopDelay()
            || this->asLoadedUseMomF2 != this->isUseMomF2()
            || this->asLoadedPort == 0
            || this->asLoadedPort != this->getPort()
            || this->asLoadedAllowTrackPower != this->isAllowTrackPower()
            || this->asLoadedAllowTurnout != this->isAllowTurnout()
            || this->asLoadedAllowRoute != this->isAllowRoute()
            || this->asLoadedAllowConsist != this->isAllowConsist()
            || this->asLoadedUseWiFiConsist != this->isUseWiFiConsist();
}
#endif
/*public*/ bool WiThrottlePreferences::isRestartRequired() {
    return this->_isRestartRequired;
}

/*public*/ bool WiThrottlePreferences::isUseEStop() {
    return useEStop;
}

/*public*/ void WiThrottlePreferences::setUseEStop(bool value) {
    useEStop = value;
}

/*public*/ int WiThrottlePreferences::getEStopDelay() {
    return eStopDelay;
}

/*public*/ void WiThrottlePreferences::setEStopDelay(int value) {
    eStopDelay = value;
}

/*public*/ bool WiThrottlePreferences::isUseMomF2() {
    return useMomF2;
}

/*public*/ void WiThrottlePreferences::setUseMomF2(bool value) {
    useMomF2 = value;
}

/*public*/ int WiThrottlePreferences::getPort() {
    return port;
}

/*public*/ void WiThrottlePreferences::setPort(int value) {
    port = value;
}

/*public*/ bool WiThrottlePreferences::isAllowTrackPower() {
    return allowTrackPower;
}

/*public*/ void WiThrottlePreferences::setAllowTrackPower(bool value) {
    allowTrackPower = value;
}

/*public*/ bool WiThrottlePreferences::isAllowTurnout() {
    return allowTurnout;
}

/*public*/ void WiThrottlePreferences::setAllowTurnout(bool value) {
    allowTurnout = value;
}

/*public*/ bool WiThrottlePreferences::isAllowRoute() {
    return allowRoute;
}

/*public*/ void WiThrottlePreferences::setAllowRoute(bool value) {
    allowRoute = value;
}

/*public*/ bool WiThrottlePreferences::isAllowConsist() {
    return allowConsist;
}

/*public*/ void WiThrottlePreferences::setAllowConsist(bool value) {
    allowConsist = value;
}

/*public*/ bool WiThrottlePreferences::isUseWiFiConsist() {
    return useWiFiConsist;
}

/*public*/ void WiThrottlePreferences::setUseWiFiConsist(bool value) {
    useWiFiConsist = value;
}

/*private*/ /*final*/ /*static*/ Logger* WiThrottlePreferences::log = LoggerFactory::getLogger("WiThrottlePreferences");
