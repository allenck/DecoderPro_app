#include "ifthenelseswing.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "ifthenelse.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class IfThenElseSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void IfThenElseSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && !(qobject_cast<IfThenElse*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an IfThenElse but is a: ")+object->bself()->metaObject()->className());
        }

        IfThenElse* action = nullptr;
        if(object)
         action = (IfThenElse*)object->bself();


        panel = new JPanel(new FlowLayout());

        _typeComboBox = new JComboBox/*<>*/();
        for (IfThenElse::Type::ETYPE type : IfThenElse::Type::values())
         _typeComboBox->addItem(IfThenElse::Type::toString(type), type);
//        JComboBoxUtil.setupComboBoxMaxRows(_typeComboBox);
        if (action != nullptr) _typeComboBox->setSelectedItem(action->getType());

        panel->layout()->addWidget(_typeComboBox);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool IfThenElseSwing::validate(/*@Nonnull*/ QList<QString> *errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* IfThenElseSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        IfThenElse* action = new IfThenElse(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void IfThenElseSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (!(qobject_cast<IfThenElse*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an IfThenElse but is a: ")+object->bself()->metaObject()->className());
        }

        IfThenElse* action = (IfThenElse*)object->bself();

        //QVariant v = _typeComboBox->getItemAt(_typeComboBox->getSelectedIndex());
        int i = _typeComboBox->currentIndex();
        action->setType((IfThenElse::Type::ETYPE)_typeComboBox->getSelectedIndex());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString IfThenElseSwing::toString() {
        return tr("IfThenElse");
    }

    //@Override
    /*public*/  void IfThenElseSwing::dispose() {
    }
