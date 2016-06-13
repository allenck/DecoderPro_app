#include "panelproaction.h"
#include "appslaunchframe.h"
#include "panelpropane.h"

PanelProAction::PanelProAction(QObject *parent) :
  JmriAbstractAction(tr("PanelPro"), parent)
{
 common();
}
/**
 * Create a new PanelPro start window
 *
 * @author	Bob Jacobsen (C) 2014
 * @version $Revision: 28746 $
 */
///*public*/ class PanelProAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 702355860636134517L;

/*public*/ PanelProAction::PanelProAction(QString s, WindowInterface* wi)  :
  JmriAbstractAction(s, wi) {
 //super(s, wi);
 common();
}

/*public*/ PanelProAction::PanelProAction(QString s, QIcon i, WindowInterface* wi)  :
  JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/**
 * Constructor
 *
 * @param s Name for the action.
 */
/*public*/ PanelProAction::PanelProAction(QString s, QObject* parent) : JmriAbstractAction(s, (WindowInterface*)parent)
{
 //super(s);
 common();
}

///*public*/ PanelProAction() {
//    this("PanelPro");
//}
void PanelProAction::common()
{
 frame = NULL;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * The action is performed. Create a new ThrottleFrame.
 *
 * @param e The event causing the action.
 */
/*public*/ void PanelProAction::actionPerformed(ActionEvent* e) {
    if (frame == NULL) {
        frame = new AppsLaunchFrame(new PanelProPane(), "PanelPro");
    }
    frame->setVisible(true);
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* PanelProAction::makePanel() {
    //throw new IllegalArgumentException("Should not be invoked");
 Q_ASSERT(false);
}
