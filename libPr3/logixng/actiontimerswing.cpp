#include "actiontimerswing.h"
#include "jbutton.h"
#include "jcheckbox.h"
#include "jcombobox.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "logixng/actiontimer.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "logixng/femaledigitalexpressionsocket.h"
#include "actiontimer.h"
#include "instancemanager.h"

ActionTimerSwing::ActionTimerSwing(QObject *parent)
    : AbstractDigitalActionSwing(parent)
{

}

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/ class ActionTimerSwing extends AbstractDigitalActionSwing {

    /*public*/ /*static*/ /*final*/ int ActionTimerSwing::MAX_NUM_TIMERS = 10;


    /*private*/ QString ActionTimerSwing::getNewSocketName(ActionTimer* action) {
        int size = ActionTimer::NUM_STATIC_EXPRESSIONS + MAX_NUM_TIMERS;
        QVector<QString> names = QVector<QString>(size);
        names[ActionTimer::EXPRESSION_START] = action->getStartExpressionSocket()->getName();
        names[ActionTimer::EXPRESSION_STOP] = action->getStopExpressionSocket()->getName();
        for (int i=0; i < MAX_NUM_TIMERS; i++) {
            names.replace(ActionTimer::NUM_STATIC_EXPRESSIONS + i, _timerSocketNames->at(i)->text());
        }
        return AbstractDigitalAction::getNewSocketName(names);
    }

    //@Override
    /*protected*/ void ActionTimerSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        if ((object != nullptr) && !(qobject_cast<ActionTimer*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionTimer but is a: ")+object->bself()->metaObject()->className());
        }

        // Create a temporary action in case we don't have one.
        ActionTimer* action = object != nullptr ? (ActionTimer*)object->bself() : new ActionTimer("IQDA1", "");

        numActions = action->getNumActions();

        panel = new JPanel();
        panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
        _startImmediately = new JCheckBox(tr("Start timer immediately on load"));
        _runContinuously = new JCheckBox(tr("Run timer continuously"));

        _unitComboBox = new JComboBox();
        for (TimerUnit::VAL u : TimerUnit::values()) _unitComboBox->addItem(TimerUnit::toString(u),u);
//        JComboBoxUtil.setupComboBoxMaxRows(_unitComboBox);
        _unitComboBox->setSelectedItem(action->getUnit());

        panel->layout()->addWidget(_startImmediately);
        panel->layout()->addWidget(_runContinuously);

        JPanel* unitPanel = new JPanel(new FlowLayout);
        unitPanel->layout()->addWidget(_unitComboBox);
        panel->layout()->addWidget(unitPanel);

        JPanel* numActionsPanel = new JPanel(new FlowLayout);
        _numTimers = new JTextField(QString::number(numActions));
        _numTimers->setColumns(2);
        _numTimers->setEnabled(false);

        _addTimer = new JButton(tr("Add timer"));
        connect(_addTimer, &JButton::clicked, [=] {
            numActions++;
            _numTimers->setText(QString::number(numActions));
            if (_timerSocketNames->at(numActions-1)->text().trimmed().isEmpty()) {
                _timerSocketNames->at(numActions-1)->setText(getNewSocketName(action));
            }
            _timerSocketNames->at(numActions-1)->setEnabled(true);
            _timerDelays->at(numActions-1)->setEnabled(true);
            if (numActions >= MAX_NUM_TIMERS) _addTimer->setEnabled(false);
            _removeTimer->setEnabled(true);
        });
        if (numActions >= MAX_NUM_TIMERS) _addTimer->setEnabled(false);

        _removeTimer = new JButton(tr("Remove timer"));
        connect(_removeTimer, &JButton::clicked,[=] {
            _timerSocketNames->at(numActions-1)->setEnabled(false);
            _timerDelays->at(numActions-1)->setEnabled(false);
            numActions--;
            _numTimers->setText(QString::number(numActions));
            _addTimer->setEnabled(true);
            if ((numActions <= 1)
                    || ((action->getNumActions() >= numActions)
                        && (action->getActionSocket(numActions-1)->isConnected()))) {
                _removeTimer->setEnabled(false);
            }
        });
        if ((numActions <= 1) || (action->getActionSocket(numActions-1)->isConnected())) {
            _removeTimer->setEnabled(false);
        }

        numActionsPanel->layout()->addWidget(new JLabel(tr("Num timers")));
        numActionsPanel->layout()->addWidget(_numTimers);
        numActionsPanel->layout()->addWidget(_addTimer);
        numActionsPanel->layout()->addWidget(_removeTimer);
        panel->layout()->addWidget(numActionsPanel);

        JPanel* timerDelaysPanel = new JPanel();
        timerDelaysPanel->setLayout(new QVBoxLayout());//timerDelaysPanel, BoxLayout.Y_AXIS));
        timerDelaysPanel->layout()->addWidget(new JLabel(tr("Timer delays")));
        JPanel* timerDelaysSubPanel = new JPanel(new FlowLayout);
        _timerSocketNames = new QVector<JTextField*>(MAX_NUM_TIMERS);
        _timerDelays = new QVector<JTextField*>(MAX_NUM_TIMERS);

        for (int i=0; i < MAX_NUM_TIMERS; i++) {
            JPanel* delayPanel = new JPanel();
            delayPanel->setLayout(new QVBoxLayout());//delayPanel, BoxLayout.Y_AXIS));
            _timerDelays->replace(i, new JTextField("0"));
            _timerDelays->at(i)->setColumns(7);
            _timerDelays->at(i)->setEnabled(false);
            delayPanel->layout()->addWidget(_timerDelays->at(i));
            _timerSocketNames->replace(i, new JTextField());
            _timerSocketNames->at(i)->setEnabled(false);
            delayPanel->layout()->addWidget(_timerSocketNames->at(i));
            timerDelaysSubPanel->layout()->addWidget(delayPanel);
            if (i < action->getNumActions()) {
                QString socketName = action->getActionSocket(i)->getName();
                _timerSocketNames->at(i)->setText(socketName);
                _timerSocketNames->at(i)->setEnabled(true);
                _timerDelays->at(i)->setText(QString::number(action->getDelay(i)));
                _timerDelays->at(i)->setEnabled(true);
            }
        }
        timerDelaysPanel->layout()->addWidget(timerDelaysSubPanel);
        panel->layout()->addWidget(timerDelaysPanel);

        _startImmediately->setSelected(action->getStartImmediately());
        _runContinuously->setSelected(action->getRunContinuously());
        _numTimers->setText(QString::number(action->getNumActions()));
    }

    /** {@inheritDoc} */
    ////@Override
    /*public*/ bool ActionTimerSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        ActionTimer* tempAction = new ActionTimer("IQDA1", "");

        bool hasErrors = false;
        for (int i=0; i < numActions; i++) {
            if (! tempAction->getActionSocket(0)->validateName(_timerSocketNames->at(i)->text())) {
                errorMessages->append(tr("Invalid Socket Name").arg(_timerSocketNames->at(i)->text()));
                hasErrors = true;
            }
        }
        return !hasErrors;
    }

    /** {@inheritDoc} */
    ////@Override
    /*public*/ MaleSocket* ActionTimerSwing::ActionTimerSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ActionTimer* action = new ActionTimer(systemName, userName);
        updateObject(action);
        return (AbstractMaleSocket*)((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    ////@Override
    /*public*/ void ActionTimerSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (!(qobject_cast<ActionTimer*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionTimer but is a: ")+object->bself()->metaObject()->className());
        }

        ActionTimer* action = (ActionTimer*)object->bself();

        action->setStartImmediately(_startImmediately->isSelected());
        action->setRunContinuously(_runContinuously->isSelected());
        action->setUnit(TimerUnit::valueOf(_unitComboBox->currentText()));
        action->setNumActions(numActions);

        for (int i=0; i < numActions; i++) {
            action->getActionSocket(i)->setName(_timerSocketNames->at(i)->text());
            action->setDelay(i, _timerDelays->at(i)->text().toInt());
        }
    }

    /** {@inheritDoc} */
    ////@Override
    /*public*/ QString ActionTimerSwing::toString() {
        return tr("ActionTimer");
    }

    ////@Override
    /*public*/ void ActionTimerSwing::dispose() {
    }

