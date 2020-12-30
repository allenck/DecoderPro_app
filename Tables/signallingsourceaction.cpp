#include "signallingsourceaction.h"
#include "signallingsourceframe.h"

SignallingSourceAction::SignallingSourceAction(QObject *parent) :  QAction(tr("SignallingPairs"),parent)
{
 init();
 source = NULL;
}
/**
 * Swing action to create and register a
 *       			SignallingFrame object
 *
 * @author	    Kevin Dickerson    Copyright (C) 2011
 * @version		$Revision: 17977 $
 */

///*public*/ class SignallingSourceAction extends AbstractAction {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.SignallingBundle");

/*public*/ SignallingSourceAction::SignallingSourceAction(QString s, QObject *parent) : QAction(s, parent)
{
 //super(s);
    init();
 source = NULL;
}

/*public*/ SignallingSourceAction::SignallingSourceAction(QString s, SignalMast* source, QObject *parent) : QAction(s, parent)
{
 //super(s);
    init();
 this->source=source;
}

///*public*/ SignallingSourceAction() {
//    super(rb.getString("SignallingPairs"));
//}
void SignallingSourceAction::init()
{
    log = new Logger("SignallingSourceAction");
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void SignallingSourceAction::setMast(SignalMast* source){
    this->source = source;
}

/*public*/ void SignallingSourceAction::actionPerformed(JActionEvent * /*e*/) // SLOT
{
 SignallingSourceFrame* f = new SignallingSourceFrame();
 try
 {
  f->initComponents(source);
 }
 catch (Exception ex)
 {
  log->error("Exception: "+ex.getMessage());
  //ex.printStackTrace();
 }
 f->setVisible(true);
}
