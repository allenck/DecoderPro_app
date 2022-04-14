#include "antecedentswing.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "antecedent.h"
#include "jlabel.h"
#include "defaultdigitalexpressionmanager.h"
#include "vptr.h"

/**
 * Configures an ExpressionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class AntecedentSwing extends AbstractDigitalExpressionSwing {


//@Override
/*protected*/ void AntecedentSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    Antecedent* expression = nullptr;
    if(object)
     expression = (Antecedent*)object->bself();
    panel = new JPanel();
    panel->setLayout(new QVBoxLayout());//panel, BoxLayout.Y_AXIS));
    JPanel* antecedentPanel = new JPanel(new FlowLayout());
    JLabel* label = new JLabel(tr("Antecedent"));
    _antecedent = new JTextField();
    _antecedent->setColumns(40);
    if (expression != nullptr) _antecedent->setText(expression->getAntecedent());
    antecedentPanel->layout()->addWidget(label);
    antecedentPanel->layout()->addWidget(_antecedent);
    panel->layout()->addWidget(antecedentPanel);
    JLabel* descriptionLabel = new JLabel(tr("<html><table width=600>                               Important note about Antecedent.                                                                <p>&nbsp;<p>                                                                                    This expression is included for backward compability with Logix. For that reason, Antecedent    uses R1, R2, R3, and so on, in its expression. R1 is the first child expression. R2 is the      second child expression. R3 is the third child expression. And so on. The children may have     whatever name you want.                                                                         <p>&nbsp;<p>                                                                                    R stands for Row, which makes sense in Conditional but not so much here. But Antecedent is      included for backward compability.                                                              <p>&nbsp;<p>                                                                                    It's recommended to use Formula instead of Antecedent. Formula is much more powerful than       Antecedent. And Formula uses the name of the children in the formula, instead of R1, R2, ...    </table></html>"));
    JPanel* subPanel = new JPanel(new FlowLayout());
    subPanel->layout()->addWidget(descriptionLabel);
    panel->layout()->addWidget(subPanel);
}

/** {@inheritDoc} */
//@Override
/*public*/  bool AntecedentSwing::validate(/*@Nonnull*/ QList<QString>* errorMessages) {
    return true;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* AntecedentSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
    Antecedent* expression = new Antecedent(systemName, userName);
    updateObject(expression);
    return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
}

/** {@inheritDoc} */
//@Override
/*public*/  void AntecedentSwing::updateObject(/*@Nonnull*/ Base* object) {
    if (!(qobject_cast<Antecedent*>(object->bself()))) {
        throw new IllegalArgumentException(QString("object must be an Antecedent but is a: ")+object->bself()->metaObject()->className());
    }

    Antecedent* expression = (Antecedent*)object->bself();

    try {
        expression->setAntecedent(_antecedent->text());
    } catch (JmriException* ex) {
        log->error("Error when parsing formula", ex);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AntecedentSwing::toString() {
    return tr("Antecedent");
}

//@Override
/*public*/  void AntecedentSwing::dispose() {
}


/*private*/ /*final*/ /*static*/ Logger* AntecedentSwing::log = LoggerFactory::getLogger("AntecedentSwing");
