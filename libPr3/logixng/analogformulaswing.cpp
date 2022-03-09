#include "analogformulaswing.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "analogformula.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "defaultanalogexpressionmanager.h"
#include "variable.h"
#include "recursivedescentparser.h"
#include "parserexception.h"

/**
 * Configures an ActionTurnout object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class AnalogFormulaSwing extends AbstractAnalogExpressionSwing {


    //@Override
/*protected*/ void AnalogFormulaSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
    AnalogFormula* expression = nullptr;
    if(object)
     expression = (AnalogFormula*)object->bself();
    panel = new JPanel(new FlowLayout());
    JLabel* label = new JLabel(tr("Formula"));
    _formula = new JTextField();
    _formula->setColumns(40);
    if (expression != nullptr) _formula->setText(expression->getFormula());
    panel->layout()->addWidget(label);
    panel->layout()->addWidget(_formula);
}

/** {@inheritDoc} */
//@Override
/*public*/  bool AnalogFormulaSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
    if (_formula->text().isEmpty()) return true;

    try {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();
        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        parser->parseExpression(_formula->text());
    } catch (ParserException* ex) {
        errorMessages.append(tr("Formula is invalid:  \"%1\"").arg(_formula->text()));
        log->error("Invalid formula '"+_formula->text()+"'. Error: "+ex->getMessage(), ex);
        return false;
    }
    return true;
}

/** {@inheritDoc} */
//@Override
/*public*/  MaleSocket* AnalogFormulaSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
    AnalogFormula* expression = new AnalogFormula(systemName, userName);
    updateObject(expression);
    return ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(expression);
}

/** {@inheritDoc} */
//@Override
/*public*/  void AnalogFormulaSwing::updateObject(/*@Nonnull*/ Base* object) {
    if (!(qobject_cast<AnalogFormula*>(object->bself()))) {
        throw new IllegalArgumentException(QString("object must be an AnalogFormula but is a: ")+object->bself()->metaObject()->className());
    }

    AnalogFormula* expression = (AnalogFormula*)object->bself();

    try {
        expression->setFormula(_formula->text());
    } catch (ParserException* ex) {
        log->error("Error when parsing formula", ex);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AnalogFormulaSwing::toString() {
    return tr("Analog Formula");
}

//@Override
/*public*/  void AnalogFormulaSwing::dispose() {
}


/*private*/ /*final*/ /*static*/ Logger* AnalogFormulaSwing::log = LoggerFactory::getLogger("AnalogFormulaSwing");
