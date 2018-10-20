#include "sensortabletabaction.h"
#include "sensortableaction.h"
#include "instancemanager.h"
#include <QBoxLayout>

//SensorTableTabAction::SensorTableTabAction()
//{

//}
///*public*/ class SensorTableTabAction extends AbstractTableTabAction {

/*public*/ SensorTableTabAction::SensorTableTabAction(QString s, QObject*parent)
    : AbstractTableTabAction(s, parent)
{
    //super(s);
}
//BeanTableFrame* SensorTableTabAction::frame = NULL;

/*public*/ SensorTableTabAction::SensorTableTabAction(QObject* parent)
    : AbstractTableTabAction("Multiple Tabbed", parent)
{
    //this("Multiple Tabbed");
}

/*protected*/ Manager* SensorTableTabAction::getManager() {
    return InstanceManager::sensorManagerInstance();
}

/*protected*/ QString SensorTableTabAction::getClassName() {
    return "SensorTableAction";
}

/*protected*/ AbstractTableAction* SensorTableTabAction::getNewTableAction(QString choice) {
    return new SensorTableAction(choice, this);
}

//@Override
/*protected*/ QString SensorTableTabAction::helpTarget() {
    return "package.jmri.jmrit.beantable.SensorTable";
}

//@Override
/*public*/ QString SensorTableTabAction::getTableClass()
{
 return "SensorTableTabAction";
}
