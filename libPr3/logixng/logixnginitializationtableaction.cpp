#include "logixnginitializationtableaction.h"
#include "logixnginitializationtable.h"

/**
 * Swing action to open the table for LogixNG initialization.
 *
 * @author Daniel Bergqvist Copyright (C) 2021
 */
///*public*/  class LogixNGInitializationTableAction extends AbstractAction {

/*public*/  LogixNGInitializationTableAction::LogixNGInitializationTableAction(QString s, QObject *parent)
 : AbstractAction(s, parent) {
    //super(s); connect(this, SIGNAL(trigg))
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

/*public*/  LogixNGInitializationTableAction::LogixNGInitializationTableAction(QObject *parent)
: AbstractAction(tr("LogixNGInitializationTable"), parent){
    //this(tr("LogixNGInitializationTable")); // NOI18N
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

/*private*/ /*static*/ LogixNGInitializationTable* LogixNGInitializationTableAction::initializationTableFrame = nullptr;

//@Override
//@SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD", justification = "Only one ImportLogixFrame")
/*public*/  void LogixNGInitializationTableAction::actionPerformed(JActionEvent* e) {
    // create a settings frame
    if (initializationTableFrame == nullptr || !initializationTableFrame->isVisible()) {
        initializationTableFrame = new LogixNGInitializationTable();
        initializationTableFrame->initComponents();
    }
    initializationTableFrame->setExtendedState(JFrame::NORMAL);
    initializationTableFrame->setVisible(true); // this also brings the frame into focus
}
