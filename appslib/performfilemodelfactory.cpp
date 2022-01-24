#include "performfilemodelfactory.h"
#include "performfilemodel.h"
#include "jfilechooser.h"
#include "xmlfile.h"

PerformFileModelFactory::PerformFileModelFactory() : AbstractFileModelFactory()
{
 self()->setObjectName("PerformFileModelFactory");
}
/**
 *
 * @author Randall Wood 2016
 */
///*public*/ class PerformFileModelFactory extends AbstractFileModelFactory {

//@Override
/*public*/ /*Class<? extends StartupModel>*/QString PerformFileModelFactory::getModelClass() {
    return "PerformFileModel";
}

//@Override
/*public*/ StartupModel* PerformFileModelFactory::newModel() {
    return (StartupModel*)new PerformFileModel();
}

//@Override
/*protected*/ JFileChooser* PerformFileModelFactory::setFileChooser() {
    return XmlFile::userFileChooser("XML files", "xml");
}

/*public*/ QString PerformFileModelFactory::getDescription()
{
 return tr("Open file");
}
