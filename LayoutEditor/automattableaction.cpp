#include "automattableaction.h"
#include "automattableframe.h"
#include "automattabledatamodel.h"

//AutomatTableAction::AutomatTableAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Swing action to create and register a AutomatTable GUI
 *
 * @author	Bob Jacobsen Copyright (C) 2004, 2008
 * @version $Revision: 28746 $
 */
///*public*/ class AutomatTableAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 247180783423184258L;

/*public*/ AutomatTableAction::AutomatTableAction(QString actionName, QObject *parent) :
  AbstractAction(actionName, parent) {
 //super(actionName);
 common();
}

/*public*/ AutomatTableAction::AutomatTableAction(QObject *parent) :
  AbstractAction(tr("Thread Monitor"), parent)
{
//  this(
//            java.util.ResourceBundle.getBundle("jmri.jmrit.display.DisplayBundle")
//            .getString("MenuItemMonitor"));
 common();
}

void AutomatTableAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void AutomatTableAction::actionPerformed(JActionEvent * /*e*/)
{ // create the frame
 f = new AutomatTableFrame(new AutomatTableDataModel());
 f->pack();
 f->setVisible(true);

}
