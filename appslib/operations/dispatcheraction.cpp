#include "dispatcheraction.h"
#include "instancemanager.h"
#include "transitmanager.h"
#include <QMessageBox>
#include "dispatcherframe.h"

//DispatcherAction::DispatcherAction()
//{

//}
/**
 * Swing action to create and register a DispatcherFrame
 *
 * @author	Dave Duchamp Copyright (C) 2008
 */
///*public*/ class DispatcherAction extends AbstractAction {

//    static final ResourceBundle rb = ResourceBundle
//            .getBundle("jmri.jmrit.dispatcher.DispatcherBundle");

/*public*/ DispatcherAction::DispatcherAction(QString s, QObject* parent) : AbstractAction(s, parent){
    //super(s);
 f=NULL;
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/DispatcherAction:: DispatcherAction(QObject* parent) : AbstractAction(tr("Dispatcher"), parent)
{
 f= NULL;
    //this(rb.getString("TitleDispatcher"));
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}


//@Override
/*public*/ void DispatcherAction::actionPerformed(ActionEvent* e) {
    // check that Transits have been defined and are available
    if (((TransitManager*)InstanceManager::getDefault("TransitManager"))->getSystemNameList().size() <= 0)
    {
        // Inform the user that there are no Transits available, and don't open the window
        //JOptionPane.showMessageDialog(null, rb.getString("NoTransitsMessage"));
     QMessageBox::critical(NULL, tr("Error"), tr("No Transits found - cannot open Dispatcher. Please add Transits and try again."));
        return;
    }
    // create a Dispatcher window or activate the existing one
    if (f == NULL) {
        f = DispatcherFrame::instance();
        f->loadAtStartup();
    }
    f->setVisible(true);
}
