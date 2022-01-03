#include "printmoreoptionaction.h"

namespace Operations
{
 /**
  * Swing action to load the print options.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2009
  * @version $Revision: 21656 $
  */
 ///*public*/ class PrintMoreOptionAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -6885400704456385145L;

 /*public*/ PrintMoreOptionAction::PrintMoreOptionAction(QObject* parent) : AbstractAction(tr("Print More Options"), parent){
     //this(Bundle.getMessage("TitlePrintMoreOptions"));
  common();
 }

 /*public*/ PrintMoreOptionAction::PrintMoreOptionAction(QString s,QObject* parent) : AbstractAction(s, parent){
     //super(s);
     common();
 }
 void PrintMoreOptionAction::common()
 {
  f = NULL;
  connect(this, SIGNAL(triggered()),this, SLOT(actionPerformed()));
 }

 /*public*/ void PrintMoreOptionAction::actionPerformed(JActionEvent* /*e*/) {
     if (f == NULL || !f->isVisible()) {
         f = new PrintMoreOptionFrame();
         f->initComponents();
     }
     f->setExtendedState(JFrame::NORMAL);
     f->setVisible(true); // this also brings the frame into focus
 }
}
