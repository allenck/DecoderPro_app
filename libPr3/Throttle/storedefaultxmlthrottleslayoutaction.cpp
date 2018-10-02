#include "storedefaultxmlthrottleslayoutaction.h"
#include "storexmlthrottleslayoutaction.h"
#include "instancemanager.h"
#include "throttlemanager.h"
#include "file.h"
#include "throttlewindow.h"
/**
 * Save throttles to XML
 *
 * @author Lionel Jeanson Copyright 2009
 */
///*public*/ class StoreDefaultXmlThrottlesLayoutAction extends AbstractAction {

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/ StoreDefaultXmlThrottlesLayoutAction::StoreDefaultXmlThrottlesLayoutAction(QString s, QObject* parent) : AbstractAction(s, parent) {
 //super(s);
 // disable this ourselves if there is no throttle Manager
 if (InstanceManager::getNullableDefault("ThrottleManager") == NULL) {
     setEnabled(false);
 }
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/**
 * The action is performed. Let the user choose the file to save to. Write
 * XML for each ThrottleFrame.
 *
 * @param e The event causing the action.
 */
//@Override
/*public*/ void StoreDefaultXmlThrottlesLayoutAction::actionPerformed(/*ActionEvent e*/)
{
 StoreXmlThrottlesLayoutAction* sxta = new StoreXmlThrottlesLayoutAction(parent());
 sxta->saveThrottlesLayout(new File(ThrottleWindow::getDefaultThrottleFilename()));
}
