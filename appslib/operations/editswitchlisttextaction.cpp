#include "editswitchlisttextaction.h"
#include "editswitchlisttextframe.h"

namespace Operations
{
/**
 * Swing action to open a window that allows a user to edit the switch list text
 * strings.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2013
 * @version $Revision: 21656 $
 */
///*public*/ class EditSwitchListTextAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 5992026885290650922L;

 /*public*/ EditSwitchListTextAction::EditSwitchListTextAction(QObject* parent)
   : AbstractAction(tr("Edit Switch List Text"),parent)
 {
     //this(Bundle.getMessage("TitleSwitchListText"));
 common();
 }

 /*public*/ EditSwitchListTextAction::EditSwitchListTextAction(QString s, QObject* parent)
  : AbstractAction(s, parent)
 {
     //super(s);
  common();
 }
 void EditSwitchListTextAction::common()
 {
  f = NULL;
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
 }

 /*public*/ void EditSwitchListTextAction::actionPerformed(ActionEvent* /*e*/) {
     // create a settings frame
     if (f == NULL || !f->isVisible()) {
         f = new EditSwitchListTextFrame();
         f->initComponents();
     }
     //f.setExtendedState(Frame.NORMAL);
     f->setVisible(true);	// this also brings the frame into focus
 }

}
