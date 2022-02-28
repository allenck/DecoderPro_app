#include "powerbuttonaction.h"
#include "abstractpowermanager.h"
#include "instancemanager.h"
#include "jmriexception.h"

/**
 * Swing action to create and register a PowerPanelFrame object.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2010
 */
// /*public*/ class PowerButtonAction extends javax.swing.AbstractAction implements java.beans.PropertyChangeListener {

/*public*/ PowerButtonAction::PowerButtonAction(QString title, QObject* parent) : AbstractAction(title, parent) {
 //super(title);
common();
}

/*public*/ PowerButtonAction::PowerButtonAction(QObject* parent) : AbstractAction(tr("Power On/Off"), parent){
    //this(ResourceBundle.getBundle("jmri.jmrit.powerpanel.PowerPanelBundle").getString("ButtonPowerOnOff"));
common();
}

void PowerButtonAction::common()
{
 checkManager();
 updateLabel();

 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void PowerButtonAction::checkManager()
{
 // disable ourself if there is no power Manager
 if (InstanceManager::getNullableDefault("PowerManager") == NULL)
 {
  setEnabled(false);
 }
 else
 {
        //((PowerManager*)InstanceManager::getDefault("PowerManager").addPropertyChangeListener(this);
   AbstractPowerManager* mgr = (AbstractPowerManager*)InstanceManager::getDefault("PowerManager");
   connect(mgr->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

void PowerButtonAction::updateLabel()
{
 try
 {
  PowerManager* p = (PowerManager*)InstanceManager::getDefault("PowerManager");
  if(p == NULL) return;
  if (p->getPower() != PowerManager::ON) {
      putValue(Action::NAME, tr("Set Power On"));
  }
  else {
      putValue(Action::NAME, tr("Set Power Off"));
  }
  firePropertyChange(Action::NAME, "", getValue(Action::NAME));
 } catch (JmriException* ex) {
     return;
 }
}

//@Override
/*public*/ void PowerButtonAction::propertyChange(PropertyChangeEvent* /*ev*/)
{
 updateLabel();
}

//@Override
/*public*/ void PowerButtonAction::actionPerformed(JActionEvent * /*e*/)
{
 try
 {
  // alternate power state, updating name
  PowerManager* p = (PowerManager*)InstanceManager::getNullableDefault("PowerManager");
  if (p == NULL) {
      return;
  }
  if (p->getPower() != PowerManager::ON) {
      p->setPower(PowerManager::ON);
  } else {
      p->setPower(PowerManager::OFF);
  }
 } catch (Exception* ex) {
     return;
 }
 updateLabel();
}
