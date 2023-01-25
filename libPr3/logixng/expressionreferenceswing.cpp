#include "expressionreferenceswing.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "expressionreference.h"
#include "jcombobox.h"
#include "jtextfield.h"
#include "swingconfiguratorinterface.h"

ExpressionReferenceSwing::ExpressionReferenceSwing(QObject *parent) : AbstractDigitalExpressionSwing(parent)
{
 setObjectName("ExpressionReferenceSwing");
}
/**
 * Configures an ExpressionReference object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class ExpressionReferenceSwing extends AbstractDigitalExpressionSwing {



    //@Override
    /*protected*/ void ExpressionReferenceSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionReference* expression = nullptr;
        if(object) expression = (ExpressionReference*)object->bself();

        panel = new JPanel(new FlowLayout());

        _sensorReferenceTextField = new JTextField(30);

        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e),e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_is_IsNot_ComboBox);

        _stateComboBox = new JComboBox();
        for (ExpressionReference::PointsTo::TYPE e : ExpressionReference::PointsTo::values()) {
            _stateComboBox->addItem(ExpressionReference::PointsTo::toString(e), e);
        }
//        JComboBoxUtil->setupComboBoxMaxRows(_stateComboBox);

        if (expression != nullptr) {
            _sensorReferenceTextField->setText(expression->getReference());
            _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());
            _stateComboBox->setSelectedItem(expression->getPointsTo());
        }

        QList<JComponent*> components = QList<JComponent*>{
            _sensorReferenceTextField,
            _is_IsNot_ComboBox,
            _stateComboBox};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("Reference %1 %2 %3"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionReferenceSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        // Create a temporary expression to test formula
        ExpressionReference* expression = new ExpressionReference("IQDE1", "");

        try {
            expression->setReference(_sensorReferenceTextField->text());
        } catch (IllegalArgumentException* e) {
            errorMessages->append(e->getMessage());
            return false;
        }

        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionReferenceSwing::getAutoSystemName() {
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getAutoSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ExpressionReferenceSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ExpressionReference* expression = new ExpressionReference(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReferenceSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ExpressionReference*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ExpressionReference but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionReference* expression = (ExpressionReference*)object->bself();
        expression->setReference(_sensorReferenceTextField->text());
        expression->set_Is_IsNot((Is_IsNot_Enum::VAL)_is_IsNot_ComboBox->getSelectedItem().toInt());
        expression->setPointsTo((ExpressionReference::PointsTo::TYPE)_stateComboBox->getSelectedItem().toInt());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionReferenceSwing::toString() {
        return tr("Reference");
    }

    //@Override
    /*public*/  void ExpressionReferenceSwing::dispose() {
        // Do nothing
    }
