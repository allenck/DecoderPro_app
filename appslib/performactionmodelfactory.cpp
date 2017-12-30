#include "performactionmodelfactory.h"

/**
 *
 * @author Randall Wood 2016
 */
///*public*/ class PerformActionModelFactory extends AbstractActionModelFactory {

/*public*/ PerformActionModelFactory::PerformActionModelFactory() : AbstractActionModelFactory()
{
 setObjectName("PerformActionModelFactory");
}

//@Override
/*public*/ /*Class<? extends StartupModel>*/QString PerformActionModelFactory::getModelClass() {
    return "PerformActionModel";
}

//@Override
/*public*/ PerformActionModel* PerformActionModelFactory::newModel() {
    return new PerformActionModel();
}

//@Override
/*public*/ QString PerformActionModelFactory::getEditModelMessage() {
    return tr("<html>Select an action to perform when the application starts.</html>");
}
/*public*/ QString PerformActionModelFactory::getDescription()
{
 return tr("Perform action");
}
