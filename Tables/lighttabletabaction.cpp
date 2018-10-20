#include "lighttabletabaction.h"
#include "instancemanager.h"
#include "lighttableaction.h"
#include <QBoxLayout>

//LightTableTabAction::LightTableTabAction()
//{

//}
///*public*/ class LightTableTabAction extends AbstractTableTabAction {

/*public*/ LightTableTabAction::LightTableTabAction(QString s, QObject* parent) : AbstractTableTabAction(s,parent){
    //super(s);
    frame = NULL;
}

/*public*/ LightTableTabAction::LightTableTabAction( QObject* parent) : AbstractTableTabAction("Multiple Tabbed", parent)
{
    //this("Multiple Tabbed");
    frame = NULL;
}

/*protected*/ Manager* LightTableTabAction::getManager() {
    return InstanceManager::lightManagerInstance();
}

/*protected*/ QString LightTableTabAction::getClassName() {
    return "LightTableAction";
}

/*protected*/ AbstractTableAction* LightTableTabAction::getNewTableAction(QString choice) {
    return new LightTableAction(choice,0);
}

//@Override
/*protected*/ QString LightTableTabAction::helpTarget() {
    return "package.jmri.jmrit.beantable.LightTable";
}

/*public*/ QString LightTableTabAction::getTableClass() {return "LightTableTabAction";}
