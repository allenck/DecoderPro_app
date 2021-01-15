#include "signallingaction.h"
#include "signallingframe.h"
#include "exceptions.h"

SignallingAction::SignallingAction(QObject *parent) :
    QAction(tr("SignallingPairs"),parent)
{
    init();
}
/**
 * Swing action to create and register a
 *       			SignallingFrame object
 *
 * @author	    Kevin Dickerson    Copyright (C) 2011
 * @version		$Revision: 17977 $
 */

///*public*/ class SignallingAction extends AbstractAction {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.SignallingBundle");

/*public*/ SignallingAction::SignallingAction(QString s, QObject* parent) : QAction(s, parent)
{
    //super(s);
    init();
}

///*public*/ SignallingAction() {
//    //super(rb.getString("SignallingPairs"));
//}
void SignallingAction::init()
{
    log = new Logger("SignallingAction");
    source = NULL;
    dest= NULL;
}

/*public*/ void SignallingAction::setMast(SignalMast* source, SignalMast* dest){
    this->source = source;
    this->dest=dest;

}


/*public*/ void SignallingAction::actionPerformed(/*JActionEvent* e*/) {
    SignallingFrame* f = new SignallingFrame();
    try {
        f->initComponents(source, dest);
        }
    catch (Exception ex) {
        log->error("Exception: "+ex.getMessage());
        //ex.printStackTrace();
        }
    f->setVisible(true);
}
//   static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SignallingAction.class.getName());
//}
