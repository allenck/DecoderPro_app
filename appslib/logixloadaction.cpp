#include "logixloadaction.h"
#include "joptionpane.h"
#include "instancemanager.h"
#include "logixmanager.h"

LogixLoadAction::LogixLoadAction()
{

}
/**
 * Provide an action to allow Logixs to be loaded disabled when panel file is
 * loaded
 *
 * @author	Dave Duchamp Copyright (C) 2007
 */
///*public*/ class LogixLoadAction extends AbstractAction {

/*public*/ LogixLoadAction::LogixLoadAction(QString s, QWidget* who) : AbstractAction(s, who) {
    //super(s);
    _who = who;
    log = new Logger("LogixLoadAction");
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


//@Override
/*public*/ void LogixLoadAction::actionPerformed(/*ActionEvent e*/)
{
    // Set option to force Logixs to be loaded disabled

    QList<QVariant> options = QList<QVariant>() <<"Disable" <<
        "Enable";

    int retval = JOptionPane::showOptionDialog(_who, tr("Do you wish to disable Logix, when they are loaded using the Panels menu?"), tr("Debug Option"),
            JOptionPane::YES_NO_OPTION,
            JOptionPane::QUESTION_MESSAGE, QIcon(), options, options.at(0));
    if (retval != 0)
    {
        ((LogixManager*)InstanceManager::getDefault("LogixManager"))->setLoadDisabled(false);
        log->info("Requested load Logixs enabled via Debug menu.");
    } else {
        ((LogixManager*)InstanceManager::getDefault("LogixManager"))->setLoadDisabled(true);
        log->info("Requested load Logixs diabled via Debug menu.");
    }
}
