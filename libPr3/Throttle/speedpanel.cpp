#include "speedpanel.h"
#include "speedpanel.h"
#include <QLabel>
#include <QBoxLayout>
#include "rosterentry.h"
#include "rosterspeedprofile.h"
#include "windowpreferences.h"
#include "loggerfactory.h"

/**
 * A JInternalFrame that contains a label to display scale speed if available
 * for forward, reverse and STOP. TODO: fix speed increments (14, 28)
 *
 * @author glen Copyright (C) 2002
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Ken Cameron Copyright (C) 2008
 * @author Steve Gigiel Copyright (C) 2017
 */
///*public*/ class SpeedPanel extends JInternalFrame implements java.beans.PropertyChangeListener, AddressListener {


/**
 * Constructor.
 */
/*public*/ SpeedPanel::SpeedPanel(QWidget* parent) : QDockWidget(parent)
{
 setObjectName("SpeedPanel");
 scaleSpeedLabel = new QLabel(""); //, JLabel.CENTER);
 scaleSpeedLabel->setAlignment(Qt::AlignCenter);
 useSpeedProfile = false;
 currentIsForward = true;
 currentThrottleVol = 0.0;

 initGUI();
}

/**
 * Set the AddressPanel this throttle control is listening for new throttle
 * event
 *
 * @param addressPanel - reference to the addresspanel
 */
/*public*/ void  SpeedPanel::setAddressPanel(AddressPanel* addressPanel) {
    this->addressPanel = addressPanel;
}

/**
 * "Destructor"
 */
/*public*/ void  SpeedPanel::destroy() {
    if (addressPanel != NULL) {
        addressPanel->removeAddressListener((AddressListener*)this);
    }
    if (throttle != NULL) {
        //throttle.removePropertyChangeListener(this);
     disconnect(throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        throttle = NULL;
    }
}

/**
 * Create, initialize and place GUI components.
 */
/*private*/ void  SpeedPanel::initGUI() {

    mainPanel = new QWidget();
    //this.setContentPane(mainPanel);
    this->setWidget(mainPanel);
    QVBoxLayout* mainPanelLayout;
    mainPanel->setLayout(mainPanelLayout = new QVBoxLayout());//BorderLayout());
//    this.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);

    speedDisplayPanel = new QWidget();
    speedDisplayPanel->setFont(QFont("", 32, QFont::Normal));//new Font("", Font.PLAIN, 32));
      QHBoxLayout* speedDisplayPanelLayout;
    speedDisplayPanel->setLayout(speedDisplayPanelLayout = new QHBoxLayout());//(speedDisplayPanel, BoxLayout.X_AXIS));
    speedDisplayPanel->setWindowOpacity(10);
    mainPanelLayout->addWidget(speedDisplayPanel, 0, Qt::AlignCenter) ;//BorderLayout.CENTER);

    speedDisplayPanelLayout->addWidget(scaleSpeedLabel);

}

/**
 * update the state of this panel if direction or speed change
 */
//@Override
/*public*/ void  SpeedPanel::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName() == ("SpeedSetting")) {
        currentThrottleVol = ( e->getNewValue()).toFloat();
        scaleSpeedLabel->setText(updateSpeedLabel(useSpeedProfile, currentThrottleVol, currentIsForward));
    } else if (e->getPropertyName() == ("IsForward")) {
        currentIsForward = e->getNewValue().toBool();
        scaleSpeedLabel->setText(updateSpeedLabel(useSpeedProfile, currentThrottleVol, currentIsForward));
    }
    if (log->isDebugEnabled()) {
        log->debug("Property change event received " + e->getPropertyName() + " / " + e->getNewValue().toString());
    }
}

/**
 *
 * @param useSpeedProfile - are we using speed profile
 * @param throttleVolume  - throttle position (percent of 1)
 * @param isForward       - true if going forward.
 * @return a string for displaying speed if available
 */
/*private*/ QString  SpeedPanel::updateSpeedLabel(bool useSpeedProfile, float throttleVolume, bool isForward)
{
 RosterEntry* re = addressPanel->getRosterEntry();
 if (re != NULL && useSpeedProfile) {
     return (re->getSpeedProfile()->convertThrottleSettingToScaleSpeedWithUnits(throttleVolume, isForward));
 } else {
     return (tr("Scale Speed Unavailable"));
 }
}

//@Override
/*public*/ void SpeedPanel::notifyAddressChosen(LocoAddress* l) {
}

//@Override
/*public*/ void SpeedPanel::notifyAddressReleased(LocoAddress* la) {
    this->setEnabled(false);
    if (throttle != NULL) {
        //throttle.removePropertyChangeListener(this);
     disconnect(throttle,  SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    throttle = NULL;
}

//@Override
/*public*/ void SpeedPanel::notifyAddressThrottleFound(DccThrottle* t) {
    if (log->isDebugEnabled()) {
        log->debug("control panel received new throttle");
    }
    this->throttle = t;

    //this->throttle.addPropertyChangeListener(this);
    connect(throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    if (log->isDebugEnabled()) {
        DccLocoAddress* Address = (DccLocoAddress*) throttle->getLocoAddress();
        log->debug("new address is " + Address->toString());
    }

    useSpeedProfile = false;  //posit false
    RosterEntry* re = addressPanel->getRosterEntry();
    if (re != NULL
            && re->getSpeedProfile() != NULL
            && re->getSpeedProfile()->getProfileSize() > 0) {
        useSpeedProfile = true;
    }
}

//@Override
/*public*/ void SpeedPanel::notifyConsistAddressChosen(int newAddress, bool isLong) {
}

//@Override
/*public*/ void SpeedPanel::notifyConsistAddressReleased(int address, bool isLong) {
}

//@Override
/*public*/ void SpeedPanel::notifyConsistAddressThrottleFound(DccThrottle* throttle) {
    if (log->isDebugEnabled()) {
        log->debug("control panel received consist throttle");
    }
    notifyAddressThrottleFound(throttle);
}

/**
 * Collect the prefs of this object into XML Element Just Positional Data
 * <ul>
 * <li> Window prefs
 * </ul>
 *
 *
 * @return the XML of this object.
 */
/*public*/ QDomElement SpeedPanel::getXml() {
 QDomDocument doc = QDomDocument();
    QDomElement me = doc.createElement("SpeedPanel");
    //java.util.ArrayList<Element> children = new java.util.ArrayList<Element>(1);
//    children.add(WindowPreferences.getPreferences(this));
//    me.setContent(children);
    me.appendChild(WindowPreferences::getPreferences(this));
    return me;
}

/**
 * Set the preferences based on the XML Element. Just positional data
 * <ul>
 * <li> Window prefs
 * </ul>
 *
 *
 * @param e The Element for this object.
 */
/*public*/ void SpeedPanel::setXml(QDomElement e) {
    QDomElement window = e.firstChildElement("window");
    WindowPreferences::setPreferences(this, window);
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* SpeedPanel::log = LoggerFactory::getLogger("ControlPanel");
