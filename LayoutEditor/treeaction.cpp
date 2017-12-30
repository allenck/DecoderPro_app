#include "treeaction.h"

//TreeAction::TreeAction()
//{

//}
/**
 * Create a JInput control window.
 *
 * @author Bob Jacobsen Copyright 2008
  */
// /*public*/ class TreeAction extends JmriJFrameAction {

 /*public*/ TreeAction::TreeAction(QString s, QObject* parent) : JmriJFrameAction(s, parent)
{
     //super(s);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ TreeAction::TreeAction(QObject* parent) : JmriJFrameAction("USB Input Control", parent){
     //this("USB Input Control");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ QString TreeAction::getName() {
     return "jmri.jmrix.jinput.treecontrol.TreeFrame";
}

