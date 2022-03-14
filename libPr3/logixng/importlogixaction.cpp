#include "importlogixaction.h"
#include "importlogixframe.h"

/**
 * Swing action to create and register a LogixNGEditor object.
 *
 * @author Daniel Bergqvist Copyright (C) 2018
 */
// /*public*/  class ImportLogixAction extends AbstractAction {

    /*public*/  ImportLogixAction::ImportLogixAction(QString s, QObject* parent) : AbstractAction(s, parent) {
        //super(s);
    }

    /*public*/  ImportLogixAction::ImportLogixAction(QObject* parent) : AbstractAction(tr("Import Logix"), parent){
        //this(Bundle.getMessage("MenuImportLogix")); // NOI18N
    }

    /*static*/ ImportLogixFrame* ImportLogixAction::importLogixFrame = nullptr;

    //@Override
    //@SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD", justification = "Only one ImportLogixFrame")
    /*public*/  void ImportLogixAction::actionPerformed(JActionEvent* e) {
        // create a settings frame
        if (importLogixFrame == nullptr || !importLogixFrame->isVisible()) {
            importLogixFrame = new ImportLogixFrame();
            importLogixFrame->initComponents();
        }
        importLogixFrame->setExtendedState(JFrame::NORMAL);
        importLogixFrame->setVisible(true); // this also brings the frame into focus
    }
