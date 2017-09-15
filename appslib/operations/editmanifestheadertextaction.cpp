#include "editmanifestheadertextaction.h"
#include "editmanifestheadertextframe.h"

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

 /*public*/ EditManifestHeaderTextAction::EditManifestHeaderTextAction(QObject* parent)
  : AbstractAction(tr("Edit Manifest Header Text"),parent)
 {
     //this(Bundle.getMessage("TitleManifestHeaderText"));
  f = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ EditManifestHeaderTextAction::EditManifestHeaderTextAction(QString s, QObject* parent)
 : AbstractAction(s, parent)
 {
  //super(s);
 f = NULL;
  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }


 /*public*/ void EditManifestHeaderTextAction::actionPerformed(ActionEvent* /*e*/) {
     // create a settings frame
     if (f == NULL || !f->isVisible()) {
         f = new EditManifestHeaderTextFrame();
         f->initComponents();
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }

}
