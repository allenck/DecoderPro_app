#include "expressionpowerswing.h"
#include "instancemanager.h"
#include "expressionpower.h"
#include "defaultdigitalexpressionmanager.h"
#include "swingconfiguratorinterface.h"

ExpressionPowerSwing::ExpressionPowerSwing(QObject *parent) : AbstractDigitalExpressionSwing(parent)
{
 setObjectName("ExpressionPowerSwing");
}
/**
 * Configures an ExpressionPower object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright (C) 2021
 */
// /*public*/  class ExpressionPowerSwing extends AbstractDigitalExpressionSwing {



    //@Override
    /*protected*/ void ExpressionPowerSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionPower* expression = nullptr;
        if(object) expression = (ExpressionPower*)object->bself();

        panel = new JPanel(new FlowLayout());

        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e), e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_is_IsNot_ComboBox);

        _stateComboBox = new JComboBox();
        for (ExpressionPower::PowerState::STATE e : ExpressionPower::PowerState::values()) {
            _stateComboBox->addItem(ExpressionPower::PowerState::toString(e),e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_stateComboBox);

        if (expression != nullptr) {
            _is_IsNot_ComboBox->setSelectedItem(Is_IsNot_Enum::toString(expression->get_Is_IsNot()));
            _stateComboBox->setSelectedItem(expression->getBeanState());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _is_IsNot_ComboBox,
            _stateComboBox};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Power "
                   "{1} {2}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionPowerSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionPowerSwing::getAutoSystemName() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ExpressionPowerSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ExpressionPower* expression = new ExpressionPower(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionPowerSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast< ExpressionPower*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionPower but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionPower* expression = (ExpressionPower*)object->bself();
        expression->set_Is_IsNot((Is_IsNot_Enum::VAL)_is_IsNot_ComboBox->getSelectedItem().toInt());
        expression->setBeanState((ExpressionPower::PowerState::STATE)_stateComboBox->getSelectedItem().toInt());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionPowerSwing::toString() {
        return tr("Power");
    }

    //@Override
    /*public*/  void ExpressionPowerSwing::dispose() {
        // Do nothing
    }
