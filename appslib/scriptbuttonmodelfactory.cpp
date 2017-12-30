#include "scriptbuttonmodelfactory.h"
#include "instancemanager.h"
#include "startupactionsmanager.h"
#include "joptionpane.h"
#include "file.h"
#include "scriptbuttonmodel.h"
#include "scriptfilechooser.h"
#include "scriptbuttonpanel.h"
#include "vptr.h"
/**
 *
 * @author Randall Wood 2016
 */
///*public*/ class ScriptButtonModelFactory implements StartupModelFactory {

/*public*/ ScriptButtonModelFactory::ScriptButtonModelFactory()
{
 chooser = NULL;
 setObjectName("ScriptButtonModelFactory");
}

//@Override
/*public*/ /*Class<? extends StartupModel>*/QString ScriptButtonModelFactory::getModelClass() {
    return "ScriptButtonModel";
}

//@Override
/*public*/ StartupModel* ScriptButtonModelFactory::newModel() {
    return (StartupModel*)new ScriptButtonModel();
}

//@Override
/*public*/ QString ScriptButtonModelFactory::getDescription() {
   // return Bundle.getMessage(this->getModelClass().getCanonicalName());
 return tr("Add script to button");
}

//@Override
/*public*/ QString ScriptButtonModelFactory::getActionText() {
    return tr("%1...").arg(this->getDescription()); // NOI18N
}

//@Override
/*public*/ void ScriptButtonModelFactory::editModel(StartupModel* model, QWidget* parent) {
 if (this->chooser == NULL)
 {
  this->chooser = new ScriptFileChooser();
  this->chooser->setDialogTitle(this->getDescription());
  this->chooser->setDialogType(JFileChooser::CUSTOM_DIALOG);
 }
 //if (ScriptButtonModel.class.isInstance(model))
 if(Class::forName("ScriptButtonModel")->isInstance(model))
 {
     ScriptButtonPanel* buttonPanel = new ScriptButtonPanel(this->chooser, parent);
     if (((ScriptButtonModel*) model)->getScript() != NULL) {
         buttonPanel->setScript(((ScriptButtonModel*) model)->getScript()->getPath());
     } else {
         buttonPanel->setScript(""); // NOI18N
     }
     buttonPanel->setButtonName(model->getName());
     JOptionPane::showMessageDialog(parent,
             VPtr<ScriptButtonPanel>::asQVariant(buttonPanel),
             this->getDescription(),
             JOptionPane::PLAIN_MESSAGE);
     if (!buttonPanel->getButtonName().isEmpty()) {
         model->setName(buttonPanel->getButtonName());
         ((ScriptButtonModel*) model)->setScript(new File(buttonPanel->getScript()));
         ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->setRestartRequired();
     }
 }
}

//@Override
/*public*/ void ScriptButtonModelFactory::initialize() {
    // nothing to do
}
