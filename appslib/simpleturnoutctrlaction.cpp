#include "simpleturnoutctrlaction.h"
#include "instancemanager.h"
#include "simpleturnoutctrlframe.h"
#include "jmrijframe.h"

//SimpleTurnoutCtrlAction::SimpleTurnoutCtrlAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * SimpleTurnoutCtrlAction.java
 *
 * Description:	Swing action to create and register a SimpleTurnoutCtrlFrame
 * object
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @version
 */

// /*public*/ class SimpleTurnoutCtrlAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -6750002493680281206L;

/*public*/ SimpleTurnoutCtrlAction::SimpleTurnoutCtrlAction(QString s, WindowInterface* wi)
 : JmriAbstractAction( s, (QObject*)wi)
{
 //super(s, wi);
 common();
}

/*public*/ SimpleTurnoutCtrlAction::SimpleTurnoutCtrlAction(QString s, QIcon i, WindowInterface* wi)
 : JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/*public*/ SimpleTurnoutCtrlAction::SimpleTurnoutCtrlAction(QString s, QObject *parent) :
  JmriAbstractAction(s, parent) {
    //super(s);
 common();
}
void SimpleTurnoutCtrlAction::common()
{
 // disable ourself if there is no primary turnout manager available
 if (InstanceManager::turnoutManagerInstance() == NULL) {
     setEnabled(false);
 }
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ SimpleTurnoutCtrlAction::SimpleTurnoutCtrlAction(QObject *parent) :
  JmriAbstractAction(tr("Turnouts"), parent)
{
 //this(java.util.ResourceBundle.getBundle("jmri.NamedBeanBundle").getString("Turnouts"));
 common();
}

/*public*/ void SimpleTurnoutCtrlAction::actionPerformed(ActionEvent* /*e*/) {

    SimpleTurnoutCtrlFrame* f = new SimpleTurnoutCtrlFrame();
    f->setVisible(true);

}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* SimpleTurnoutCtrlAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
