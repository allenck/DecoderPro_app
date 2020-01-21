#include "printmoreoptionframe.h"
#include "control.h"
#include "printmoreoptionpanel.h"

namespace Operations
{
 /**
  * Frame for user edit of additional manifest print options
  *
  * @author Dan Boudreau Copyright (C) 2012
  * @version $Revision: 21846 $
  */
 ///*public*/ class PrintMoreOptionFrame extends OperationsFrame {

  /**
   *
   */
  //private static final long serialVersionUID = -6234971819984062486L;

  /*public*/ PrintMoreOptionFrame::PrintMoreOptionFrame(QWidget* parent)
     : OperationsFrame(tr("Print More Options"), parent)
  {
      //super(Bundle.getMessage("TitlePrintMoreOptions"), new PrintMoreOptionPanel());
   setContentPane(new PrintMoreOptionPanel(this));
  }

  //@Override
  /*public*/ void PrintMoreOptionFrame::initComponents() {
      OperationsFrame::initComponents();

      // build menu
      addHelpMenu("package.jmri.jmrit.operations.Operations_ManifestPrintOptionsTools", true); // NOI18N

      initMinimumSize(QSize(Control::panelWidth300, Control::panelHeight400));
  }
/*public*/ QString PrintMoreOptionFrame::getClassName()
{
 return "jmri.jmrit.operations.setup.PrintMoreOptionFrame";
}

}
