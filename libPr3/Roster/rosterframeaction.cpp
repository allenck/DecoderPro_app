#include "rosterframeaction.h"
#include "jmriuserpreferencesmanager.h"
#include "instancemanager.h"
#include "rosterframe.h"
//#include "rostergroupselector.h"
#include "windowinterface.h"

//RosterFrameAction::RosterFrameAction(QObject *parent) :
//    AbstractAction(tr("Roster"), parent)
//{
//}
/**
 * AbstractAction for the RosterFrane so that multiple windows can be opened
 *
 * @author Kevin Dickerson Copyright (C) 2011
 * @author Randall Wood Copyright (C) 2012
 */
// /*public*/ class RosterFrameAction extends JmriAbstractAction {

/*public*/ RosterFrameAction::RosterFrameAction(QString s, WindowInterface* wi)
    : JmriAbstractAction(s,wi)
{
   // super(s, wi);
 common();
}
/*public*/ RosterFrameAction::RosterFrameAction(QString s, WindowInterface* wi, bool allowQuit)
: JmriAbstractAction(s,wi)
{
    //super(s, wi);
 common();
    this->allowQuit = allowQuit;
}

/*public*/ RosterFrameAction::RosterFrameAction(QString s, QIcon i, WindowInterface* wi) :JmriAbstractAction(s,i,wi)
{
    //super(s, i, wi);
    common();
}

/**
 * Default constructor used when instantiating via startup action
 * or button configured in user preferences
 */
/*public*/ RosterFrameAction::RosterFrameAction(QObject *parent) :
    JmriAbstractAction(tr("RosterFrameAction"), parent)
{
    //super(ResourceBundle.getBundle("apps.ActionListBundle").getString("jmri.jmrit.roster.swing.RosterFrameAction"));
    common();
    allowQuit = false;
}
/**
* Method for opening a new window via the classic JMRI interface
*/
/*public*/ RosterFrameAction::RosterFrameAction(QString pName, bool allowQuit, QObject* parent) : JmriAbstractAction(pName,parent)
{
    //super(pName);
    common();
    this->allowQuit=allowQuit;
}
void RosterFrameAction::common()
{
 allowQuit = true;
 log = new Logger("RosterFrameAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
//@Override
/*public*/ void RosterFrameAction::actionPerformed(ActionEvent* /*event*/) {
 mainFrame = new RosterFrame();
 UserPreferencesManager* p = (UserPreferencesManager*) InstanceManager::getDefault("UserPreferencesManager");
 if(!p->isWindowPositionSaved(mainFrame->getWindowFrameRef()))
 {
  mainFrame->resize( QSize(1024, 600));
  mainFrame->setMaximumSize( QSize(1024, 600));
 }
 //if (wi instanceof RosterGroupSelector)
// if(qobject_cast<RosterGroupSelector*>(wi)!= NULL)
// {
//   mainFrame.setSelectedRosterGroup(((RosterGroupSelector)wi).getSelectedRosterGroup());
// }
  mainFrame->setVisible(true);
  mainFrame->setAllowQuit(allowQuit);
  mainFrame->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* RosterFrameAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
