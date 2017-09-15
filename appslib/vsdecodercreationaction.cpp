#include "vsdecodercreationaction.h"
#include "jframe.h"
#include "vsdecodermanager.h"
#include "vsdecoderframe.h"
#include "logger.h"
#include "file.h"
#include "vsdecoderpreferences.h"
#include "loadvsdfileaction.h"

//VSDDecoderCreationAction::VSDDecoderCreationAction()
//{
//}
/**
 * Create a new VSDecoder Pane.
 *
 * @author	Mark Underwood
 * @version $Revision: 28746 $
 */
//@SuppressWarnings("serial")
///*public*/ class VSDecoderCreationAction extends AbstractAction {

    //private static JFrame openFrame = null;

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/VSDecoderCreationAction:: VSDecoderCreationAction(QString s, bool ng, QObject* parent)
 : AbstractAction(s,parent)
{
 //super(s);
 common();
    _useNewGUI = ng;
}

/*public*/ VSDecoderCreationAction::VSDecoderCreationAction(QObject* parent)
 : AbstractAction("Virtual Sound Decoder",parent) {
    //this(ThrottleBundle.bundle().getString("MenuItemNewThrottle"));
 common();
    //this("Virtual Sound Decoder", false);
 //setText("Virtual Sound Decoder");
 _useNewGUI = false;

}

void VSDecoderCreationAction::common()
{
 _useNewGUI= false;
 log = new Logger("VSDecoderCreationAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * The action is performed. Create a new ThrottleFrame.
 *
 * @param e The event causing the action.
 */
/*public*/ void VSDecoderCreationAction::actionPerformed(ActionEvent* /*e*/)
{
 QString fp = "", fn = "";
 JFrame* tf = NULL;
 if (_useNewGUI == true)
 {
  tf = VSDecoderManager::instance()->provideManagerFrame();
 }
 else
 {
  tf = new VSDecoderFrame();
 }
 if (VSDecoderManager::instance()->getVSDecoderPreferences()->isAutoLoadingDefaultVSDFile())
 {
  // Force load of a VSD file
  fp = VSDecoderManager::instance()->getVSDecoderPreferences()->getDefaultVSDFilePath();
  fn = VSDecoderManager::instance()->getVSDecoderPreferences()->getDefaultVSDFileName();
  log->debug("Loading VSD File: " + fp + File::separator + fn);
  LoadVSDFileAction::loadVSDFile(fp + File::separator + fn);
 }
 tf->toFront();
}
