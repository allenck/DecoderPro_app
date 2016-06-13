#include "decoder3action.h"
#include "windowinterface.h"
#include "decoderpro3window.h"
#include "decoderpro3.h"
#include "userpreferencesmanager.h"
//#include "rostergroupselector.h"

//Decoder3Action::Decoder3Action(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * AbstractAction for the DP3 window so that further windows can be opened
 *
 * @author Kevin Dickerson Copyright (C) 2011
 */
///*public*/ class DecoderPro3Action extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 908346452314380162L;

/*public*/ Decoder3Action::Decoder3Action(QString s, WindowInterface* wi)
 :  JmriAbstractAction(s,wi)
{
 //super(s, wi);
 common();
}

/*public*/ Decoder3Action::Decoder3Action(QString s, QIcon i, WindowInterface* wi)
:  JmriAbstractAction(s, i, wi)
{
 //super(s, i, wi);
 common();
}

/**
 * Method for opening a new window via the classic JMRI interface
 */
/*public*/ Decoder3Action::Decoder3Action(QString pName, bool allowQuit, QObject *parent)
 :  JmriAbstractAction(pName, (WindowInterface*)parent)
{
 //super(pName);
 this->allowQuit = allowQuit;
}
 void Decoder3Action::common()
 {
  allowQuit = true;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

//@Override
/*public*/ void Decoder3Action::actionPerformed(ActionEvent* /*event*/)
 {
    mainFrame = new DecoderPro3Window(DecoderPro3::getMenuFile(), DecoderPro3::getToolbarFile());
    UserPreferencesManager* p =(UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
    if (!p->isWindowPositionSaved(mainFrame->getWindowFrameRef())) {
        mainFrame->resize(QSize(1024, 600));
        mainFrame->setMaximumSize(QSize(1024, 600));
    }
    //if (wi instanceof RosterGroupSelector)
//    if(qobject_cast<RosterGroupSelector>(wi) != NULL)
//    {
//        mainFrame->setSelectedRosterGroup(((RosterGroupSelector*) wi).getSelectedRosterGroup());
//    }
    mainFrame->setVisible(true);
    mainFrame->setAllowQuit(allowQuit);
    mainFrame->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
}

//    // never invoked, because we overrode actionPerformed above
//    //@Override
//    public JmriPanel makePanel() {
//        throw new IllegalArgumentException("Should not be invoked");
//    }
