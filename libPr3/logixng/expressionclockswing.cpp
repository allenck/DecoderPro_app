#include "expressionclockswing.h"
#include "jcombobox.h"
#include "jtextfield.h"
#include "logixng/defaultdigitalexpressionmanager.h"
#include "logixng/expressionclock.h"
#include <QTime>
#include "datetimeparseexception.h"
#include "instancemanager.h"

ExpressionClockSwing::ExpressionClockSwing(QObject *parent)
    : AbstractDigitalExpressionSwing{parent}
{

}
/**
 * Configures an ExpressionClock object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
// /*public*/ class ExpressionClockSwing extends AbstractDigitalExpressionSwing {

    //@Override
    /*protected*/ void ExpressionClockSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        ExpressionClock* expression = nullptr;
        if(object) expression = (ExpressionClock*) object->bself();
        panel = new JPanel(new FlowLayout);

        _stateComboBox = new JComboBox();
        for (ExpressionClock::Type::VAL e : ExpressionClock::Type::values()) {
            _stateComboBox->addItem(ExpressionClock::Type::toString(e), e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_stateComboBox);

        _is_IsNot_ComboBox = new JComboBox();
        for (Is_IsNot_Enum::VAL e : Is_IsNot_Enum::values()) {
            _is_IsNot_ComboBox->addItem(Is_IsNot_Enum::toString(e), e);
        }
//        JComboBoxUtil.setupComboBoxMaxRows(_is_IsNot_ComboBox);

        _beginTextField = new JTextField(4);
        _beginTextField->setText(ExpressionClock::formatTime(0));


        _endTextField = new JTextField(4);
        _endTextField->setText(ExpressionClock::formatTime(0));

        if (expression != nullptr) {
            _stateComboBox->setSelectedItem(expression->getType());
            _is_IsNot_ComboBox->setSelectedItem(expression->get_Is_IsNot());
            _beginTextField->setText(ExpressionClock::formatTime(expression->getBeginTime()));
            _endTextField->setText(ExpressionClock::formatTime(expression->getEndTime()));
        }

        QList<JComponent*> components =  QList<JComponent*>{
            _stateComboBox,
            _is_IsNot_ComboBox,
            _beginTextField,
            _endTextField
        };

        QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
                tr("{0} time {1} between {2} and {3}"), components);

        for (JComponent* c : componentList) panel->layout()->addWidget((QWidget*)c->jself());
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ExpressionClockSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
    _beginMinutes = validateTime(errorMessages, _beginTextField);
    _endMinutes = validateTime(errorMessages, _endTextField);

    if (!errorMessages->isEmpty()) return false;
        return true;
    }

    /*private*/ int ExpressionClockSwing::validateTime(QList<QString>* errorMessages, JTextField* timeField) {
        int minutes = 0;
        try {
            QTime newHHMM = QTime::fromString(timeField->text().trimmed(), "H:mm");
            if(!newHHMM.isValid()) throw new DateTimeParseException("invalid time", timeField->text());
            minutes = newHHMM.hour() * 60 + newHHMM.minute();
            if (minutes < 0 || minutes > 1439) {
                errorMessages->append(tr("The entered time is not between 00:00 and 23:59"));
            }
        } catch (DateTimeParseException* ex) {
            errorMessages->append(tr("The entered time, \"%1\", is not valid").arg(ex->getParsedString()));
        }
        return minutes;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ MaleSocket* ExpressionClockSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        ExpressionClock* expression = new ExpressionClock(systemName, userName);
        expression->setType(ExpressionClock::Type::FastClock);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ExpressionClockSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (! (qobject_cast<ExpressionClock*>(object->bself()))) {
            throw new IllegalArgumentException(tr("object must be an ExpressionClock but is a: ")+object->bself()->metaObject()->className());
        }
        ExpressionClock* expression = (ExpressionClock*) object->bself();
        expression->setType(ExpressionClock::Type::valueOf(_stateComboBox->currentText()));
        expression->set_Is_IsNot(Is_IsNot_Enum::valueOf(_is_IsNot_ComboBox->currentText()));
        expression->setRange(_beginMinutes, _endMinutes);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionClockSwing::toString() {
        return tr("Clock");
    }

    //@Override
    /*public*/ void ExpressionClockSwing::dispose() {
    }

