#include "digitalformulaswing.h"
#include "instancemanager.h"
#include "digitalexpressionmanager.h"
#include "loggerfactory.h"
#include "digitalformula.h"
#include "jlabel.h"
#include "defaultdigitalexpressionmanager.h"
#include "recursivedescentparser.h"
#include "parserexception.h"
#include "loggerfactory.h"

/**
 * Configures an Formula object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class DigitalFormulaSwing extends AbstractDigitalExpressionSwing {


    //@Override
    /*protected*/ void DigitalFormulaSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel){
        DigitalFormula* expression = (DigitalFormula*)object->bself();
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
    /*public*/  bool DigitalFormulaSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
        if (_formula->text().isEmpty()) return true;

        try {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();
            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            parser->parseExpression(_formula->text());
        } catch (ParserException* ex) {
            errorMessages.append(tr("Formula is invalid: \"%1\"").arg(_formula->text()));
            log->error("Invalid formula '"+_formula->text()+"'. Error: "+ex->getMessage(), ex);
            return false;
        }
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  MaleSocket* DigitalFormulaSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        DigitalFormula* expression = new DigitalFormula(systemName, userName);
        updateObject(expression);
        return ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void DigitalFormulaSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (!(qobject_cast<DigitalFormula*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an DigitalFormula but is a: ")+object->bself()->metaObject()->className());
        }

        DigitalFormula* expression = (DigitalFormula*)object->bself();

        try {
            expression->setFormula(_formula->text());
        } catch (ParserException* ex) {
            log->error("Error when parsing formula", ex);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DigitalFormulaSwing::toString() {
        return tr("Digital Formula");
    }

    //@Override
    /*public*/  void DigitalFormulaSwing::dispose() {
    }


    /*private*/ /*final*/ /*static*/ Logger* DigitalFormulaSwing::log = LoggerFactory::getLogger("DigitalFormulaSwing");
