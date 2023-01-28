#include "sequenceswing.h"
#include "sequence.h"
#include "jcheckbox.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class SequenceSwing extends AbstractDigitalActionSwing {


    //@Override
    /*protected*/ void SequenceSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && !(qobject_cast<Sequence*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an Sequence but is a: ")+object->bself()->metaObject()->className());
        }

        Sequence* action = (Sequence*)object->bself();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
        _startImmediately = new JCheckBox(tr("Start sequence immediately on load"));
        _runContinuously = new JCheckBox(tr("Run sequence continuously"));
        if (action != nullptr) {
            _startImmediately->setSelected(action->getStartImmediately());
            _runContinuously->setSelected(action->getRunContinuously());
        }
        panel->layout()->addWidget(_startImmediately);
        panel->layout()->addWidget(_runContinuously);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool SequenceSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* SequenceSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        Sequence* action = new Sequence(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void SequenceSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (!(qobject_cast<Sequence*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an Sequence but is a: ")+object->bself()->metaObject()->className());
        }

        Sequence* action = (Sequence*)object->bself();
        action->setStartImmediately(_startImmediately->isSelected());
        action->setRunContinuously(_runContinuously->isSelected());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString SequenceSwing::toString() {
        return tr("Sequence");
    }

    //@Override
    /*public*/  void SequenceSwing::dispose() {
    }
