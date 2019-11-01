#include "buildreportoptionframe.h"
#include "buildreportoptionpanel.h"
#include "control.h"

namespace Operations
{
 /**
  * Frame for user edit of the build report options
  *
  * @author Dan Boudreau Copyright (C) 2008, 2010, 2011, 2012, 2013
  * @version $Revision: 21643 $
  */
 ///*public*/ class BuildReportOptionFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = -5896574373818704098L;

 /*public*/ BuildReportOptionFrame::BuildReportOptionFrame(QWidget* parent)
    : OperationsFrame(tr("Build Report Options"), parent)
 {
  //super(Bundle.getMessage("TitleBuildReportOptions"), new BuildReportOptionPanel());
  setContentPane(new BuildReportOptionPanel(this));
 }

 //@Override
 /*public*/ void BuildReportOptionFrame::initComponents() {
     OperationsFrame::initComponents();
     // build menu
     addHelpMenu("package.jmri.jmrit.operations.Operations_BuildReportDetails", true); // NOI18N

     initMinimumSize(QSize(Control::panelWidth500, Control::panelHeight500));
 }
}
