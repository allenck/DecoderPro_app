#include "shutdowncomputerswing.h"
#include "jcombobox.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/shutdowncomputer.h"
#include "instancemanager.h"

ShutdownComputerSwing::ShutdownComputerSwing(QObject *parent)
    : AbstractDigitalActionSwing(parent)
{

}
/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/ class ShutdownComputerSwing extends AbstractDigitalActionSwing {


    //@Override
    /*protected*/ void ShutdownComputerSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    ShutdownComputer* action = (ShutdownComputer*)object->bself();

        panel = new JPanel(new FlowLayout);
        _operationComboBox = new JComboBox();
        for (ShutdownComputer::Operation::TYPE e : ShutdownComputer::Operation::values()) {
            _operationComboBox->addItem(ShutdownComputer::Operation::toString(e), e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_operationComboBox);
        panel->layout()->addWidget(_operationComboBox);
        if (action != nullptr) {
            _operationComboBox->setSelectedItem(action->getOperation());
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ShutdownComputerSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ShutdownComputerSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ShutdownComputer* action = new ShutdownComputer(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ShutdownComputerSwing::updateObject(/*@Nonnull*/ Base* object) {
        if(!object) throw new NullPointerException();
        if (! (qobject_cast<ShutdownComputer*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ShutdownComputer but is a: ")+object->bself()->metaObject()->className());
        }
        ShutdownComputer* action = (ShutdownComputer*)object->bself();
        action->setOperation(ShutdownComputer::Operation::valueOf(_operationComboBox->currentText()));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ShutdownComputerSwing::toString() {
        return tr("ShutdownComputer");
    }

    //@Override
    /*public*/ void ShutdownComputerSwing::dispose() {
    }

