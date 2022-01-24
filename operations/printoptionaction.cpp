#include "printoptionaction.h"
#include "printoptionframe.h"

namespace Operations
{
/**
 * Swing action to load the print options.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2009
 * @version $Revision: 28746 $
 */
///*public*/ class PrintOptionAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 3517810572798192308L;

 /*public*/ PrintOptionAction::PrintOptionAction(QObject* parent) : AbstractAction(tr("Print Options"), parent){
     //this(Bundle.getMessage("TitlePrintOptions"));
  f = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ PrintOptionAction::PrintOptionAction(QString s, QObject* parent)  : AbstractAction(s, parent){
     //super(s);
  f = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 /*public*/ void PrintOptionAction::actionPerformed(JActionEvent * /*e*/) {
     if (f == NULL || !f->isVisible()) {
         f = new PrintOptionFrame();
         f->initComponents();
     }
     f->setExtendedState(JFrame::NORMAL);
     f->setVisible(true); // this also brings the frame into focus
 }
}
