#include "editmanifesttextaction.h"

namespace Operations
{
 /**
  * Swing action to open a window that allows a user to edit the manifest header
  * text strings.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2014
  * @version $Revision: 21656 $
  */
 ///*public*/ class EditManifestHeaderTextAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -1916894570578033881L;

 /*public*/ EditManifestTextAction::EditManifestTextAction(QObject* parent)
 :  AbstractAction(tr("Edit Manifest Text"),parent)
 {
     //this(Bundle.getMessage("TitleManifestText"));
  common();
 }

 /*public*/ EditManifestTextAction::EditManifestTextAction(QString s, QObject* parent)  : AbstractAction(s, parent)
 {
     //super(s);
common();
 }
 void EditManifestTextAction::common()
{
 f = NULL;
}

 /*public*/ void EditManifestTextAction::actionPerformed(JActionEvent* /*e*/) {
     // create a settings frame
     if (f == NULL || !f->isVisible()) {
         f = new EditManifestTextFrame();
         f->initComponents();
     }
     f->setExtendedState(JFrame::NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }

}
