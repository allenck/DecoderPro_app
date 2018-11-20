#include "logaction.h"
#include "logframe.h"

//LogAction::LogAction()
//{

//}
/**
 * Swing action to create and register a LogFrame object
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 */
///*public*/ class LogAction extends AbstractAction {

    /*public*/ LogAction::LogAction(QString s, QObject* parent) : AbstractAction(s, parent) {
        //super(s);
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
    }

    /*public*/ LogAction::LogAction(QObject* parent) : AbstractAction("Add Log Entry", parent) {
        //this("Add Log Entry");
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

    }

    //@Override
    /*public*/ void LogAction::actionPerformed(/*ActionEvent e*/) {
        LogFrame* f = new LogFrame();
        try {
            f->initComponents();
        } catch (Exception ex) {
            log->error("Exception in startup", ex);
        }
        f->setVisible(true);
    }
    /*private*/ /*final*/ /*static*/ Logger* LogAction::log = new Logger("LogAction");
