#include "editswitchlisttextframe.h"

namespace Operations
{
 /**
  * Frame for user edit of switch list text strings
  *
  * @author Dan Boudreau Copyright (C) 2013
  * @version $Revision: 21846 $
  */
 //public class EditSwitchListTextFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = -8868355208674070617L;

 /*public*/ EditSwitchListTextFrame::EditSwitchListTextFrame(QWidget* parent)
     : OperationsFrame(tr("Switch List Text"), parent)
 {
     //super(Bundle.getMessage("TitleSwitchListText"), new EditSwitchListTextPanel());
 }

 //@Override
 /*public*/ void EditSwitchListTextFrame::initComponents() {
     OperationsFrame::initComponents();

     // build menu
     addHelpMenu("package.jmri.jmrit.operations.Operations_ManifestPrintOptionsTools", true); // NOI18N

     initMinimumSize();
 }

}
