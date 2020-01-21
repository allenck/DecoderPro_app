#include "editmanifestheadertextframe.h"

namespace Operations
{
 /**
  * Frame for user edit of manifest header text strings
  *
  * @author Dan Boudreau Copyright (C) 2014
  * @version $Revision: 21846 $
  */
 //public class EditManifestHeaderTextFrame extends OperationsFrame {

 /**
  *
  */
 //private static final long serialVersionUID = -8750952066802266213L;

 /*public*/ EditManifestHeaderTextFrame::EditManifestHeaderTextFrame(QWidget* parent)
    : OperationsFrame(parent)
 {
     //super(Bundle.getMessage("TitleManifestHeaderText"), new EditManifestHeaderTextPanel());
 }

 //@Override
 /*public*/ void EditManifestHeaderTextFrame::initComponents() {
     OperationsFrame::initComponents();

     // build menu
     addHelpMenu("package.jmri.jmrit.operations.Operations_ManifestPrintOptionsTools", true); // NOI18N

     initMinimumSize();
 }
/*public*/ QString EditManifestHeaderTextFrame::getClassName()
{
 return "jmri.jmrit.operations.setup.EditManifestHeaderTextFrame";
}

}
