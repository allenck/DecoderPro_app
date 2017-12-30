#include "startuppausefactory.h"
#include "instancemanager.h"
#include "startupactionsmanager.h"
#include "startuppausemodel.h"
#include "joptionpane.h"
#include <QVBoxLayout>
#include <QLabel>
#include "vptr.h"

StartupPauseFactory::StartupPauseFactory()
{
 setObjectName("StartupPauseFactory");
}
/**
 * Factory for {@link apps.startup.StartupPauseModel} objects.
 *
 * @author Randall Wood (c) 2016
 */
///*public*/ class StartupPauseFactory implements StartupModelFactory {

//@Override
/*public*/ QString /*Class<? extends StartupModel>*/ StartupPauseFactory::getModelClass() {
    return "StartupPauseModel";
}

//@Override
/*public*/ StartupModel* StartupPauseFactory::newModel() {
    return new StartupPauseModel();
}

//@Override
/*public*/ QString StartupPauseFactory::getDescription() {
    //return tr(this->getModelClass().getCanonicalName());
  return "Pause";
}

//@Override
/*public*/ QString StartupPauseFactory::getActionText() {
    return tr("%1...").arg(this->getDescription()); // NOI18N
}

//@Override
/*public*/ void StartupPauseFactory::editModel(StartupModel* model, QWidget* parent) {
    if (Class::forName(this->getModelClass())->isInstance(model)) {
        int delay = ((StartupPauseModel*) model)->getDelay();
//        SpinnerNumberModel snm = new SpinnerNumberModel(
//                delay >= 0 ? delay : StartupPauseModel.DEFAULT_DELAY,
//                0,
//                600,
//                1);
//        JSpinner spinner = new JSpinner(snm);
        QSpinBox* spinner = new QSpinBox();
        spinner->setMaximum(600);
        spinner->setMinimum(0);
        spinner->setSingleStep(1);
        spinner->setValue(delay >= 0 ? delay : StartupPauseModel::DEFAULT_DELAY);
        int result = JOptionPane::showConfirmDialog(parent,
                VPtr<QWidget>::asQVariant(this->getDialogMessage(spinner)),
                this->getDescription(),
                JOptionPane::OK_CANCEL_OPTION,
                JOptionPane::PLAIN_MESSAGE);
        if (result == JOptionPane::OK_OPTION && delay != /*snm.getNumber().intValue()*/spinner->value())
        {
            ((StartupPauseModel*) model)->setDelay(/*snm.getNumber().intValue()*/spinner->value());
            ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->setRestartRequired();
        }
    }
}

//@Override
/*public*/ void StartupPauseFactory::initialize() {
    // nothing to do
}

/*private*/ QWidget* StartupPauseFactory::getDialogMessage(QSpinBox* spinner) {
    QWidget* panel = new QWidget();
    QVBoxLayout* panelLayout = new QVBoxLayout(panel);
    panelLayout->addWidget(new QLabel(tr("Pause for"))); // NOI18N
    panelLayout->addWidget(spinner);
    panelLayout->addWidget(new QLabel(tr("seconds before starting the following action."))); // NOI18N
    return panel;
}
