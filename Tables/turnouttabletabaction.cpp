#include "turnouttabletabaction.h"
#include "instancemanager.h"
#include "turnouttableaction.h"
#include <QVBoxLayout>
#include "userpreferencesmanager.h"

//TurnoutTableTabAction::TurnoutTableTabAction(QObject *parent) :
//    AbstractTableTabAction(parent)
//{
//}
// /*public*/ class TurnoutTableTabAction extends AbstractTableTabAction {

/**
 *
 */
//private static final long serialVersionUID = 5514320062139920106L;

/*public*/ TurnoutTableTabAction::TurnoutTableTabAction(QString s, QObject *parent) :
    AbstractTableTabAction(s, parent)
{
    //super(s);
 common();
}

/*public*/ TurnoutTableTabAction::TurnoutTableTabAction(QObject *parent) :
    AbstractTableTabAction("Multiple Tabbed", parent)
{
    //this("Multiple Tabbed");
 common();
}
void TurnoutTableTabAction::common()
{
}

//@Override
/*protected*/ Manager* TurnoutTableTabAction::getManager() {
    return InstanceManager::turnoutManagerInstance();
}

//@Override
/*protected*/ QString TurnoutTableTabAction::getClassName() {
    return /*TurnoutTableAction.class.getName()*/ "jmri.jmrit.beantable.TurnoutTableTabAction";
}

//@Override
/*protected*/ AbstractTableAction* TurnoutTableTabAction::getNewTableAction (QString choice){
    return new TurnoutTableAction(choice,parent());
}

//@Override
/*protected*/ QString TurnoutTableTabAction::helpTarget() {
    return "package.jmri.jmrit.beantable.TurnoutTable";
}

//@Override
/*public*/ QString TurnoutTableTabAction::getTableClass()
{
 return "TurnoutTableTabAction";
}

