#include "buildreportoptionaction.h"
#include "buildreportoptionframe.h"

namespace Operations
{
 /**
  * Swing action to load the print options.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2012
  * @version $Revision: 17977 $
  */
 // /*public*/ class BuildReportOptionAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 6686776607454912217L;

 /*public*/ BuildReportOptionAction::BuildReportOptionAction(QObject* parent)
     : AbstractAction(tr("Build Report Options"),parent)
 {
  //this(Bundle.getMessage("TitleBuildReportOptions"));
f = NULL;
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ BuildReportOptionAction::BuildReportOptionAction(QString s, QObject* parent)
     : AbstractAction(s, parent)
 {
     //super(s);
 f = NULL;
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void BuildReportOptionAction::actionPerformed(ActionEvent* /*e*/) {
     // create a settings frame
     if (f == NULL || !f->isVisible()) {
         f = new BuildReportOptionFrame();
         f->initComponents();
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }

}
