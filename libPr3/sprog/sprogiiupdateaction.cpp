#include "sprogiiupdateaction.h"
#include "loggerfactory.h"
#include "sprogiiupdateframe.h"
#include "joptionpane.h"

using namespace Sprog;
/**
 * Swing action to create and register a SprogIIUpdateFrame object.
 *
 * @author	Andrew crosland Copyright (C) 2004
 */
// /*public*/ class SprogIIUpdateAction extends SprogUpdateAction {

/*public*/ SprogIIUpdateAction::SprogIIUpdateAction(QString s,SprogSystemConnectionMemo* memo, QWidget* frame) : SprogUpdateAction(s, memo, frame )
{
    //super(s,memo);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void SprogIIUpdateAction::actionPerformed() {
    //Object[] options = {Bundle.getMessage("ButtonCancel"), Bundle.getMessage("ButtonContinue")};
 QVariantList options = QVariantList() << tr("Cancel") << tr("Continue");
    if (1 == JOptionPane::showOptionDialog(NULL,
            tr("Sprog%1 Update").arg(" II"),
            tr("Sprog%1 Firmware Update").arg(" II"), JOptionPane::YES_NO_OPTION,
            JOptionPane::QUESTION_MESSAGE, QIcon(), options, options.at(0))) {
        // create a SprogIIUpdateFrame
        SprogIIUpdateFrame* f = new SprogIIUpdateFrame(_memo);
        try {
            f->initComponents();
        } catch (Exception* ex) {
            log->warn("SprogIIUpdateAction starting SprogIIUpdateFrame: Exception: " + ex->getMessage());
        }
        f->setVisible(true);
    }
}

/*private*/ /*final*/ /*static*/ Logger* SprogIIUpdateAction::log = LoggerFactory::getLogger("SprogIIUpdateAction");
