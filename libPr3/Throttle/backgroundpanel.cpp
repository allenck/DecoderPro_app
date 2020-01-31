#include "backgroundpanel.h"
#include "instancemanager.h"
#include <QColor>
#include "throttleframemanager.h"
#include "rosterentry.h"
#include "throttlespreferences.h"
#include "fileutil.h"

// /*public*/ class BackgroundPanel extends ResizableImagePanel implements AddressListener {

/*public*/ BackgroundPanel::BackgroundPanel(QWidget* parent) : ResizableImagePanel(parent)
{
    //super();
  addressPanel = NULL;

    setBackground(QColor(Qt::gray));
    setRespectAspectRatio(true);
    if (((ThrottleFrameManager*)InstanceManager::getDefault("ThrottleFrameManager"))->getThrottlesPreferences()->isResizingWindow()) {
        setResizingContainer(true);
    }
}


/*public*/ void BackgroundPanel::setAddressPanel(AddressPanel* addressPanel) {
    this->addressPanel = addressPanel;
}

//@Override
/*public*/ void BackgroundPanel::notifyAddressThrottleFound(DccThrottle* t) {
    RosterEntry* rosterEntry = NULL;
    if (addressPanel != NULL) {
        rosterEntry = addressPanel->getRosterEntry();
    }
    if (rosterEntry != NULL) {
        setImagePath(rosterEntry->getImagePath());
    } else {
        if (t->getLocoAddress()->toString() == ("3(S)") ) // default DCC address
        {
            setImagePath(FileUtil::getExternalFilename("resources/icons/throttles/DCCImage.png"));
        }
        if (t->getLocoAddress()->toString() == ("0(S)") ) // default DC address
        {
            setImagePath(FileUtil::getExternalFilename("resources/icons/throttles/DCImage.png"));
        }
    }
}

//@Override
/*public*/ void BackgroundPanel::notifyAddressReleased(locoAddress* la) {
    setImagePath(NULL);
    setVisible(false);
}

//@Override
/*public*/ void BackgroundPanel::notifyAddressChosen(locoAddress* l) {
}

//@Override
/*public*/ void BackgroundPanel::notifyConsistAddressChosen(int newAddress, bool isLong) {
}

//@Override
/*public*/ void BackgroundPanel::notifyConsistAddressReleased(int address, bool isLong) {
}

//@Override
/*public*/ void BackgroundPanel::notifyConsistAddressThrottleFound(DccThrottle* throttle) {
}
