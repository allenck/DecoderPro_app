#include "logixngmenu.h"
#include "startstopalllogixngsaction.h"
#include "logixnginitializationtableaction.h"
#include "importlogixaction.h"

/**
 * Create a "LogixNG" menu
 *
 * @author Daniel Bergqvist Copyright 2019
 */
// /*public*/  class LogixNGMenu extends JMenu {

/*public*/  LogixNGMenu::LogixNGMenu(QString name) {
    //this();
    setTitle(name);
    common();
}

/*public*/  LogixNGMenu::LogixNGMenu() {
    //super();
 setTitle(tr("LogixNG"));

 common();
}

void LogixNGMenu::common()
{

    addAction(new StartStopAllLogixNGsAction(tr("Start LogixNG"), true,this));
    addAction(new StartStopAllLogixNGsAction(tr("Stop LogixNG"), false, this));
    addAction(new LogixNGInitializationTableAction(this));
    addAction(new ImportLogixAction(this));
}
