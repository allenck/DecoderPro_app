#include "vsdecodercreationaction.h"
#include "jmrijframe.h"
#include "vsdecodermanager.h"
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
 JmriJFrame* tf = NULL;

 tf = VSDecoderManager::instance()->provideManagerFrame(); // headless will return null

 if (tf != nullptr) {
     tf->toFront();
 }
}
