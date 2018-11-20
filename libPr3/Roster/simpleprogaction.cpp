#include "simpleprogaction.h"
#include "instancemanager.h"
#include "lnprogrammermanager.h"
#include "simpleprogframe.h"
#include "windowinterface.h"

//SimpleProgAction::SimpleProgAction(QObject *parent) :
//    QAction(parent)
//{
//}
/**
 * Swing action to create and register a
 *       			SimpleProgAction object
 *
 * @author			Bob Jacobsen    Copyright (C) 2001, 2008
 * @version			$Revision: 22216 $
 */
 // /*public*/ class SimpleProgAction 			extends JmriAbstractAction {

/*public*/ SimpleProgAction::SimpleProgAction(QString s, WindowInterface* wi) : JmriAbstractAction(s,wi)
{
 //super(s, wi);
 init();
}

/*public*/ SimpleProgAction::SimpleProgAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s,i, wi)
{
 //super(s, i, wi);
 init();
}
// /*public*/ SimpleProgAction(QString s) {
//     super(s);
void SimpleProgAction::init()
{
 // disable ourself if programming is not possible
 bool enabled = false;
 if ( (!InstanceManager::getList("GlobalProgrammerManager").isEmpty())
      && (InstanceManager::getList("GlobalProgrammerManager").size() > 0) )
  enabled = true;
 if ( (!InstanceManager::getList("AddressedProgrammerManager").isEmpty())
      && (InstanceManager::getList("AddressedProgrammerManager").size() > 0) )
  enabled = true;
 setEnabled(enabled);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ SimpleProgAction::SimpleProgAction(QObject* wi) : JmriAbstractAction("Single CV Programmer", wi)
{
 init();
}

 /*public*/ void SimpleProgAction::actionPerformed(ActionEvent* /*e*/) {
  // create a SimpleProgFrame
  SimpleProgFrame* f = new SimpleProgFrame();
  f->setVisible(true);
 }

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* SimpleProgAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
