#include "throttlecreationaction.h"
#include "windowinterface.h"
#include "instancemanager.h"
#include "throttlewindow.h"
#include "throttleframemanager.h"
#include "addresspanel.h"
#include "rosterentryselectorpanel.h"

ThrottleCreationAction::ThrottleCreationAction(QObject *parent) :
    JmriAbstractAction(tr("New Throttle"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
/**
 * Create a new throttle.
 *
 * @author			Glen Oberhauser
 * @version     $Revision: 22216 $
 */
// /*public*/ class ThrottleCreationAction extends JmriAbstractAction {

/*public*/ ThrottleCreationAction::ThrottleCreationAction(QString s, WindowInterface* wi) : JmriAbstractAction(s,wi)
{
    //super(s, wi);
    // disable the ourselves if there is no throttle Manager
 if (InstanceManager::getNullableDefault("ThrottleManager") == nullptr)
 {
  setEnabled(false);
 }
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ ThrottleCreationAction::ThrottleCreationAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s,i,wi)
{
    //super(s, i, wi);
    // disable the ourselves if there is no throttle Manager
  if (InstanceManager::getNullableDefault("ThrottleManager") == nullptr){
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

///**
// * Constructor
// * @param s Name for the action.
// */
///*public*/ ThrottleCreationAction::ThrottleCreationAction(QString s) {
//    super(s);
//// disable the ourselves if there is no throttle Manager
//    if (jmri.InstanceManager.throttleManagerInstance()==NULL) {
//        setEnabled(false);
//    }
//}

///*public*/ ThrottleCreationAction() {
//    this(Bundle.getMessage("MenuItemNewThrottle"));
//}

/**
 * The action is performed. Create a new ThrottleFrame.
 * @param e The event causing the action.
 */
/*public*/ void ThrottleCreationAction::actionPerformed(ActionEvent* /*e*/)
{
    QString group = NULL;
//    if (Beans.hasProperty(wi, "selectedRosterGroup")) {
//        group = (String) Beans.getProperty(wi, "selectedRosterGroup");
//    }
 /*ThrottleFrame*/ ThrottleWindow* tf = ThrottleFrameManager::instance()->createThrottleFrame();
 tf->getAddressPanel()->getRosterEntrySelector()->setSelectedRosterGroup(group);
 tf->toFront();
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* ThrottleCreationAction::makePanel()
{
    throw new IllegalArgumentException("Should not be invoked");
}
