#include "actionclockswing.h"
#include "actionclock.h"
#include "jcombobox.h"
#include "jtextfield.h"
#include "jlabel.h"
#include "swingconfiguratorinterface.h"
#include "defaultdigitalactionmanager.h"

ActionClockSwing::ActionClockSwing(QObject *parent) : AbstractDigitalActionSwing(parent)
{
 setObjectName("ActionClockSwing");
}
/**
 * Configures an ActionClock object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
///*public*/  class ActionClockSwing extends AbstractDigitalActionSwing {



    //@Override
    /*protected*/ void ActionClockSwing::createPanel(/*CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ActionClock* action = nullptr;
        if(object)
         action = (ActionClock*) object->bself();

        panel = new JPanel(new FlowLayout());

        _stateComboBox = new JComboBox();
        for (ActionClock::ClockState::STATE e : ActionClock::ClockState::values()) {
            _stateComboBox->addItem(ActionClock::ClockState::toString(e), e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_stateComboBox);
        connect(_stateComboBox, &JComboBox::currentIndexChanged, [=]{
            setTimeField(action == nullptr ? 0 : action->getClockTime());
        });

        _timeTextField = new JTextField(4);
        setTimeField(0);

        if (action != nullptr) {
            _stateComboBox->setSelectedItem(action->getBeanState());
            setTimeField(action->getClockTime());
        }

        JPanel* timeField = new JPanel(new FlowLayout());
        JLabel* timelabel = new JLabel(tr("%1").arg(tr("Enter time (hh:mm)")));
        timeField->layout()->addWidget(timelabel);
        timeField->layout()->addWidget(_timeTextField);

        JPanel* container = new JPanel();
        container->setLayout(new QVBoxLayout());//container, BoxLayout.Y_AXIS));
        container->layout()->addWidget(_stateComboBox);
        container->layout()->addWidget(timeField);

        QList<JComponent*> components = QList<JComponent*>{
            container};

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("%1"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget(c->jself());
    }

    /*private*/ void ActionClockSwing::setTimeField(int time) {
        if (_stateComboBox->getSelectedItem().toInt() == ActionClock::ClockState::SetClock) {
            _timeTextField->setEnabled(true);
            _timeTextField->setText(ActionClock::formatTime(time));
        } else {
            _timeTextField->setEnabled(false);
            _timeTextField->setText("");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ActionClockSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
        if (_stateComboBox->getSelectedItem().toInt() == ActionClock::ClockState::SetClock) {
#if 0 // TODO:
            LocalTime* newHHMM;
            try {
                newHHMM = LocalTime::parse(_timeTextField.text().trimmed(), DateTimeFormatter.ofPattern("H:mm"));
                _minutes = newHHMM.getHour() * 60 + newHHMM.getMinute();
                if (_minutes < 0 || _minutes > 1439) {
                    errorMessages.add(Bundle.getMessage("ActionClock_RangeError"));
                }
            } catch (DateTimeParseException* ex) {
                errorMessages.add(Bundle.getMessage("ActionClock_ParseError", ex.getParsedString()));
            }
#endif
        }

        if (!errorMessages->isEmpty()) return false;
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionClockSwing::getAutoSystemName() {
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->getAutoSystemName();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* ActionClockSwing::createNewObject(/*@Nonnull*/ QString systemName, /*CheckForNull*/ QString userName) {
        ActionClock* action = new ActionClock(systemName, userName);
        updateObject(action);
        return ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionClockSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ActionClock*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an ActionClock but is a: ")+object->bself()->metaObject()->className());
        }
        ActionClock* action = (ActionClock*) object->bself();
        action->setBeanState((ActionClock::ClockState::STATE)_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()).toInt());

        if (_stateComboBox->getSelectedItem().toInt() == ActionClock::ClockState::SetClock) {
                action->setClockTime(_minutes);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ActionClockSwing::toString() {
        return tr("ActionClock");
    }

    //@Override
    /*public*/  void ActionClockSwing::dispose() {
    }

