#include "progmodepane.h"
#include <QButtonGroup>
#include <QBoxLayout>
#include "instancemanager.h"
#include "lnprogrammermanager.h"
#include "../../LayoutEditor/jseparator.h"
#include "progservicemodepane.h"
#include "progopsmodepane.h"

//ProgModePane::ProgModePane(QWidget *parent) :
//    ProgModeSelector(parent)
//{
//}
/**
 * Provide a JPanel to configure the programming mode.
 * <P>
 * The using code should get a configured programmer with getProgrammer.
 * <P>
 * This pane will only display ops mode options if ops mode is available,
 * as evidenced by an attempt to get an ops mode programmer at startup time.
 * <P>
 * For service mode, you can get the programmer either from the JPanel
 * or direct from the instance manager.  For ops mode, you have to
 * get it from here.
 * <P>
 * Note that you should call the dispose() method when you're really done, so that
 * a ProgModePane object can disconnect its listeners.
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 17977 $
 */
///*public*/ class ProgModePane extends ProgModeSelector {


/**
 * @param direction controls layout, either BoxLayout.X_AXIS or BoxLayout.Y_AXIS
 */
/*public*/ ProgModePane::ProgModePane(QBoxLayout::Direction direction, QWidget *parent)
    :  ProgModeSelector(parent)
{
 log = new Logger("ProgModePane");
 group = new QButtonGroup();

 // general GUI config
 QBoxLayout* layout;
 setLayout(layout = new QBoxLayout((QBoxLayout::Direction)direction));

 // service mode support, always present
 mServicePane = new ProgServiceModePane(direction, group);
 layout->addWidget(mServicePane);

 // ops mode support
 mOpsPane = NULL;
 if (InstanceManager::programmerManagerInstance()!=NULL &&
         ((LnProgrammerManager*) InstanceManager::programmerManagerInstance())->isAddressedModePossible())
 {

  layout->addWidget(new JSeparator());
  mOpsPane = new ProgOpsModePane(direction, group);
  layout->addWidget(mOpsPane);
 }
}

/**
 * Default implementation of "isSelected" just returns true.
 * @return Always true in this implementation
 */
/*public*/ bool ProgModePane::isSelected() { return true; }

/**
 * Get the configured programmer
 */
/*public*/ Programmer* ProgModePane::getProgrammer() {
    if (InstanceManager::programmerManagerInstance()==NULL) {
        log->warn("request for programmer with no ProgrammerManager configured");
        return NULL;
    } else if (mServicePane->isSelected()) {
        return mServicePane->getProgrammer();
    } else if (mOpsPane!=NULL && mOpsPane->isSelected()) {
        return mOpsPane->getProgrammer();
    } else return NULL;
}

/*public*/ void ProgModePane::dispose() {
    if (mServicePane != NULL)
        mServicePane->dispose();
    mServicePane = NULL;
    if (mOpsPane != NULL)
        mOpsPane->dispose();
    mOpsPane = NULL;
}

///*public*/ void ProgModePane::setDefaultMode() {
//    mServicePane->setButtonMode(DefaultProgrammerManager::PAGEMODE);
//}
