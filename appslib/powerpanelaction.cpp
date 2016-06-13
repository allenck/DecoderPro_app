#include "powerpanelaction.h"
#include "instancemanager.h"
#include "powermanager.h"
#include "powerpanelframe.h"

//PowerPanelAction::PowerPanelAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a PowerPanelFrame object.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @version $Revision: 28746 $
 */
// /*public*/ class PowerPanelAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -8975098374222170676L;
//static ResourceBundle res = ResourceBundle.getBundle("jmri.jmrit.powerpanel.PowerPanelBundle");

/*public*/ PowerPanelAction::PowerPanelAction(QString s, QObject *parent) :
  JmriAbstractAction(s, (QObject*)parent)
{
    //super(s);
 common();
}

void PowerPanelAction::common()
{

    // disable ourself if there is no power Manager
    if (InstanceManager::powerManagerInstance() == NULL) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ PowerPanelAction::PowerPanelAction( QObject *parent) :
  JmriAbstractAction(tr("Power Control"), parent){
   // this(res.getString("TitlePowerPanel"));
 common();
}

/*public*/ void PowerPanelAction::actionPerformed(ActionEvent* /*e*/) {
    // create a PowerPanelFrame
    PowerPanelFrame* f = new PowerPanelFrame();
    f->setVisible(true);
}
