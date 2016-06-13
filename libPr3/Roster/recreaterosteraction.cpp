#include "recreaterosteraction.h"
#include "roster.h"
#include "jmripanel.h"

//RecreateRosterAction::RecreateRosterAction(QObject *parent) :
//  JmriAbstractAction(parent)
//{
//}
/**
 * Recreate the roster index file if it's been damaged or lost.
 * <P>
 * Scans the roster directory for xml files, including any that are found.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @version	$Revision: 29337 $
 */
///*public*/ class RecreateRosterAction extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 2421095427974812157L;

/*public*/ RecreateRosterAction::RecreateRosterAction(QString s, WindowInterface* wi) :
  JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ RecreateRosterAction::RecreateRosterAction(QString s, QIcon i, WindowInterface* wi) :
  JmriAbstractAction(s, i, wi) {
 //super(s, i, wi);
 common();
}

/*public*/ RecreateRosterAction::RecreateRosterAction(QObject *parent) :
  JmriAbstractAction(tr("Rebuild Roster"),parent)
{
 //this("Rebuild Roster");
 common();
}

/*public*/ RecreateRosterAction::RecreateRosterAction(QString s, QObject *parent) :
  JmriAbstractAction(s, (WindowInterface*)parent)
{
 //super(s);
 common();
}
void RecreateRosterAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void RecreateRosterAction::actionPerformed(ActionEvent* e)
{
 Roster::getDefault()->reindex();
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* RecreateRosterAction::makePanel() {
    throw new IllegalArgumentException("Should not be invoked");
}
