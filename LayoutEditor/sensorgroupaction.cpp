#include "sensorgroupaction.h"
#include "routemanager.h"
#include "instancemanager.h"
#include "sensorgroupframe.h"

//SensorGroupAction::SensorGroupAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Swing action to create and register a SensorGroupFrame object
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2007
 * @version $Revision: 28746 $
 */
///*public*/ class SensorGroupAction extends AbstractAction {

/**
 *
 */
///*private*/ static final long serialVersionUID = -6704486852181647895L;

/*public*/ SensorGroupAction::SensorGroupAction(QString s,QObject *parent) :
  AbstractAction(s, parent) {
    //super(s);
 common();
}
void SensorGroupAction::common()
{
    // disable ourself if there is no route manager object available
    if (InstanceManager::getDefault("RouteManager") == NULL) {
        setEnabled(false);
    }
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ SensorGroupAction::SensorGroupAction(QObject *parent) :
  AbstractAction(tr("Define Sensor Group..."),parent)
{
    //this("Define Sensor Group...");
 common();
}

/*public*/ void SensorGroupAction::actionPerformed(JActionEvent * /*e*/)
{
 SensorGroupFrame* f = new SensorGroupFrame();
 f->initComponents();
 f->setVisible(true);
}
