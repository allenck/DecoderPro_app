#include "createbuttonmodelfactory.h"
#include "createbuttonmodel.h"

/**
 *
 * @author Randall Wood 2016
 */
///*public*/ class CreateButtonModelFactory extends AbstractActionModelFactory {

/*public*/ CreateButtonModelFactory::CreateButtonModelFactory() : AbstractActionModelFactory(){
 setObjectName("CreateButtonModelFactory");
}

//@Override
/*public*/ /*Class<? extends StartupModel>*/QString CreateButtonModelFactory::getModelClass() {
    return "CreateButtonModel";
}

//@Override
/*public*/ StartupModel* CreateButtonModelFactory::newModel() {
    return (StartupModel*)new CreateButtonModel();
}

//@Override
/*public*/ QString CreateButtonModelFactory::getEditModelMessage() {
    return tr("<html>Select a button to add to the main window.</html>");
}

/*public*/ QString CreateButtonModelFactory::getDescription()
{
 return tr("Add button to main window");
}
