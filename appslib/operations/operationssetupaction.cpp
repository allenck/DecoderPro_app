#include "operationssetupaction.h"
#include "operationssetupframe.h"

//OperationsSetupAction::OperationsSetupAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Swing action to create and register a OperationsSetupFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 28746 $
 */
//public class OperationsSetupAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 1935343860582396704L;

 /*public*/ OperationsSetupAction::OperationsSetupAction(QString s,QObject *parent) :
  AbstractAction(s, parent) {
     //super(s);
  common();
 }

 /*public*/ OperationsSetupAction::OperationsSetupAction(QObject *parent) :
  AbstractAction(tr("Setup"), parent) {
     //this(Bundle.getMessage("Setup"));	// NOI18N
  common();
 }

 void OperationsSetupAction::common()
 {
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
  f = NULL;
 }

 /*static*/ Operations::OperationsSetupFrame* OperationsSetupAction::f = NULL;

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*public*/ void OperationsSetupAction::actionPerformed(ActionEvent* e) {
     // create a settings frame
     if (f == NULL || !f->isVisible())
     {
         f = new Operations::OperationsSetupFrame();
//         f->initComponents();
     }
//     f->setExtendedState(Frame::NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }

