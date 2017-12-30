#include "performscriptmodelfactory.h"
#include "performscriptmodel.h"
#include "scriptfilechooser.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ class PerformScriptModelFactory extends AbstractFileModelFactory {

/*public*/ PerformScriptModelFactory::PerformScriptModelFactory() {
}

//@Override
/*public*/ /*Class<? extends StartupModel>*/QString PerformScriptModelFactory::getModelClass() {
    return "PerformScriptModel";
}

//@Override
/*public*/ StartupModel* PerformScriptModelFactory::newModel() {
    return (StartupModel*)new PerformScriptModel();
}

//@Override
/*protected*/ JFileChooser* PerformScriptModelFactory::setFileChooser() {
    return new ScriptFileChooser();
}
/*public*/ QString PerformScriptModelFactory::getDescription()
{
 return tr("Run script");
}

