#include "sprogconsoleaction.h"
#include "sprogconsoleframe.h"
#include "loggerfactory.h"

using namespace Sprog;
/**
 * Swing action to create and register a SprogConsoleFrame object.
 *
 * @author	Andrew Crosland Copyright (C) 2008
 */
///*public*/ class SprogConsoleAction extends AbstractAction {


/*public*/ SprogConsoleAction::SprogConsoleAction(QString s, SprogSystemConnectionMemo* memo, QObject* parent) :AbstractAction(s, parent){
    //super(s);
    _memo = memo;
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void SprogConsoleAction::actionPerformed(/*ActionEvent e*/) {
    SprogConsoleFrame* f = new SprogConsoleFrame(_memo);
    try {
        f->initComponents();
    } catch (Exception* ex) {
        log->error("Exception: " + ex->getMessage());
    }
    f->setVisible(true);
}

/*private*/ /*final*/ /*static*/ Logger* SprogConsoleAction::log = LoggerFactory::getLogger("SprogConsoleAction");
