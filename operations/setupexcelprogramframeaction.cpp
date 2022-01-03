#include "setupexcelprogramframeaction.h"

using namespace Operations;
/**
 * Swing action to launch the SetupExcelProgramFrame.
 *
 * @author Daniel Boudreau Copyright (C) 2013
 *
 */
// /*public*/ class SetupExcelProgramFrameAction extends AbstractAction {

/*public*/ SetupExcelProgramFrameAction::SetupExcelProgramFrameAction(QString s, QObject* parent) : AbstractAction(s, parent)
{
    //super(s);
     f = NULL;
     connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


//@Override
/*public*/ void SetupExcelProgramFrameAction::actionPerformed(JActionEvent* /*e*/) {
    // create a train scripts frame
    if (f != NULL && f->isVisible()) {
        f->dispose();
    }
    f = new SetupExcelProgramManifestFrame();
    f->initComponents();
    f->setExtendedState(JFrame::NORMAL);
}
