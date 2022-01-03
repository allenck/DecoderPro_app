#include "setphysicallocationaction.h"

/**
 * Swing action to create a SetPhysicalLocation dialog.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2010
 * @author Mark Underwood Copyright (C) 2011
 */
///*public*/  class SetPhysicalLocationAction extends AbstractAction {
namespace Operations
{
 /*public*/  SetPhysicalLocationAction::SetPhysicalLocationAction(Location* location, QObject* parent) : AbstractAction(tr("Set PhysicalLocation"), parent) {
     //super(Bundle.getMessage("MenuSetPhysicalLocation"));
     _location = location;
 }

 //@Override
 /*public*/  void SetPhysicalLocationAction::actionPerformed(JActionEvent* ) {
     // create a copy route frame
     if (f == nullptr || !f->isVisible()) {
         f = new SetPhysicalLocationFrame(_location);
     }
     f->setExtendedState(JFrame::NORMAL);
     f->setVisible(true); // this also brings the frame into focus
 }
} // namespace Operations
