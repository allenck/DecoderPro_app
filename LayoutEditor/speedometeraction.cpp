#include "speedometeraction.h"
#include "instancemanager.h"
#include "speedometerframe.h"

//SpeedometerAction::SpeedometerAction(QObject *parent) :
//  JmriAbstractAction(parent)
//{
//}
/**
 * Swing action to create and register a SpeedometerFrame
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @version	$Revision: 28746 $
 */
///*public*/ class SpeedometerAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -5303424007379961528L;

/*public*/ SpeedometerAction::SpeedometerAction(QString s, WindowInterface* wi) 
 : JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ SpeedometerAction::SpeedometerAction(QString s, QIcon i, WindowInterface* wi) 
 : JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/*public*/ SpeedometerAction::SpeedometerAction(QString s, QObject *parent) :
  JmriAbstractAction(s, parent) 
{
    //super(s);
 common();
}
void SpeedometerAction::common()
{
 // disable ourself if there is no primary sensor manager available
 if (InstanceManager::sensorManagerInstance() == NULL) {
     setEnabled(false);
 }
 connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
}

/*public*/ SpeedometerAction::SpeedometerAction(QObject *parent) :
  JmriAbstractAction(tr("Speedometer"), parent) 
{
 //this("Speedometer");
 common();
}

/*public*/ void SpeedometerAction::actionPerformed(JActionEvent * /*e*/) {

    // create a SimpleProgFrame
    SpeedometerFrame* f = new SpeedometerFrame();
    f->setVisible(true);

}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* SpeedometerAction::makePanel() {
    throw IllegalArgumentException("Should not be invoked");
}
