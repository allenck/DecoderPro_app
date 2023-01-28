#include "lastresultofdigitalexpressionswing.h"
#include "instancemanager.h"
#include "lastresultofdigitalexpression.h"
#include "defaultdigitalexpressionmanager.h"
#include "jcombobox.h"
#include "defaultmaledigitalexpressionsocket.h"

LastResultOfDigitalExpressionSwing::LastResultOfDigitalExpressionSwing(QObject *parent) : AbstractDigitalExpressionSwing(parent)
{
 setObjectName("LastResultOfDigitalExpressionSwing");
}
/**
 * Configures an LastResultOfDigitalExpression object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class LastResultOfDigitalExpressionSwing extends AbstractDigitalExpressionSwing {



    //@Override
    /*protected*/ void LastResultOfDigitalExpressionSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        LastResultOfDigitalExpression* expression = nullptr;
        if(object) expression = (LastResultOfDigitalExpression*)object->bself();

        panel = new JPanel(new FlowLayout());

        _expressionsComboBox = new JComboBox();
        _expressionsComboBox->addItem("");
        for (NamedBean* nb :  ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->getNamedBeanSet()) {
//           MaleDigitalExpressionSocket* bean = qobject_cast</*DefaultMaleDigitalExpressionSocket*/AbstractMaleSocket*>(nb->self());
//         if (bean->NamedBean::getUserName() != "") {
         if(nb->getUserName()!= "")
         {
               // _expressionsComboBox->addItem(bean->getDisplayName());
          _expressionsComboBox->addItem(nb->getDisplayName());
                if (expression != nullptr) {
                    NamedBeanHandle<DigitalExpressionBean*>* handle = expression->getDigitalExpression();
                    if ((handle != nullptr) && (handle->getName() == /*bean*/nb->getDisplayName())) {
                        _expressionsComboBox->setSelectedItem(/*bean*/nb->getDisplayName());
                    }
                }
            }
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_expressionsComboBox);

        panel->layout()->addWidget(_expressionsComboBox);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool LastResultOfDigitalExpressionSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* LastResultOfDigitalExpressionSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        LastResultOfDigitalExpression* expression = new LastResultOfDigitalExpression(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void LastResultOfDigitalExpressionSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<LastResultOfDigitalExpression*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an LastResultOfDigitalExpression but is a: ")+object->bself()->metaObject()->className());
        }

        LastResultOfDigitalExpression* expression = (LastResultOfDigitalExpression*)object->bself();

        QString expr = _expressionsComboBox->getItemAt(_expressionsComboBox->getSelectedIndex()).toString();
        if (expr.isEmpty()) expression->removeDigitalExpression();
        else expression->setDigitalExpression(expr);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString LastResultOfDigitalExpressionSwing::toString() {
        return tr("LastResultOfDigitalExpression");
    }

    //@Override
    /*public*/  void LastResultOfDigitalExpressionSwing::dispose() {
    }
