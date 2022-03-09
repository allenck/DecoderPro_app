#include "timesincemidnightswing.h"
#include "instancemanager.h"
#include "jlabel.h"
#include "jcombobox.h"
#include "timesincemidnight.h"
#include "defaultanalogexpressionmanager.h"
/**
 * Configures an TimeSinceMidnight object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
// /*public*/  class TimeSinceMidnightSwing extends AbstractAnalogExpressionSwing {


//@Override
/*protected*/ void TimeSinceMidnightSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    TimeSinceMidnight* expression = nullptr;
    if(object)
     expression = (TimeSinceMidnight*) object->bself();
    panel = new JPanel(new FlowLayout());

    _stateComboBox = new JComboBox();
    for (TimeSinceMidnight::Type::TYPE e : TimeSinceMidnight::Type::values) {
        _stateComboBox->addItem(e);
    }
//        JComboBoxUtil.setupComboBoxMaxRows(_stateComboBox);

    if (expression != nullptr) {
        _stateComboBox->setSelectedItem(expression->getType());
    }

    QList<JComponent*> components = QList<JComponent*>{
        _stateComboBox
    };

    QList<JComponent*> componentList = SwingConfiguratorInterface::parseMessage(
            tr("Minutes since midnight by {0}"), components);
#if 0 // TODO
    for (JComponent* c : componentList) panel->layout()->addWidget(c);
#endif
}

/** {@inheritDoc} */
//@Override
/*public*/  bool TimeSinceMidnightSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
    return true;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* TimeSinceMidnightSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
    TimeSinceMidnight* expression = new TimeSinceMidnight(systemName, userName);
    expression->setType(TimeSinceMidnight::Type::FastClock);
    return ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(expression);
}

/** {@inheritDoc} */
//@Override
/*public*/  void TimeSinceMidnightSwing::updateObject(/*@Nonnull*/ Base* object) {
    if (! (qobject_cast<TimeSinceMidnight*>(object->bself()))) {
        throw new IllegalArgumentException(tr("object must be an TimeSinceMidnight but is a: ")+object->bself()->metaObject()->className());
    }
    TimeSinceMidnight* expression = (TimeSinceMidnight*) object->bself();
    //expression->setType(_stateComboBox->getItemAt(_stateComboBox->getSelectedIndex()));
    expression->setType(TimeSinceMidnight::Type::getType(_stateComboBox->currentText()));
}

/** {@inheritDoc} */
//@Override
/*public*/  QString TimeSinceMidnightSwing::toString() {
    return tr("Minutes since midnight");
}

//@Override
/*public*/  void TimeSinceMidnightSwing::dispose() {
}


//    /*private*/ final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(TrueSwing.class);

