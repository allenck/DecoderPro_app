#include "editmanifesttextframe.h"

namespace Operations
{
 /**
  * Frame for user edit of manifest text strings
  *
  * @author Dan Boudreau Copyright (C) 2013
  * @version $Revision: 21846 $
  */
 ///*public*/ class EditManifestTextFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = 104327699477689025L;

 /*public*/ EditManifestTextFrame::EditManifestTextFrame(QWidget* parent) : OperationsFrame(tr("Manifest Test"), parent)
 {
  //super(Bundle.getMessage("TitleManifestText"), new EditManifestTextPanel());
 }

 //@Override
 /*public*/ void EditManifestTextFrame::initComponents() {
     OperationsFrame::initComponents();

     // build menu
     addHelpMenu("package.jmri.jmrit.operations.Operations_ManifestPrintOptionsTools", true); // NOI18N

     initMinimumSize();
 }
/*public*/ QString EditManifestTextFrame::getClassName()
{
 return "jmri.jmrit.operations.setup.EditManifestTextFrame";
}

}
