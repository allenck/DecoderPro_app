#include "stringformulaswing.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "stringformula.h"
#include "jlabel.h"
#include "jtextfield.h"
#include "recursivedescentparser.h"
#include "parserexception.h"
#include "defaultstringexpressionmanager.h"

/**
 * Configures a
 * n Formula object with a Swing JPanel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class StringFormulaSwing extends AbstractStringExpressionSwing {


    //@Override
    /*protected*/ void StringFormulaSwing::createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel) {
        StringFormula* expression = (StringFormula*)object->bself();
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
    /*public*/  bool StringFormulaSwing::validate(/*@Nonnull*/ QList<QString> errorMessages) {
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
    /*public*/  MaleSocket* StringFormulaSwing::createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName) {
        StringFormula* expression = new StringFormula(systemName, userName);
        updateObject(expression);
        return ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->registerExpression(expression);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void StringFormulaSwing::updateObject(/*@Nonnull*/ Base* object) {
        if (!(qobject_cast<StringFormula*>(object->bself()))) {
            throw new IllegalArgumentException(QString("object must be an StringFormula but is a: ")+object->bself()->metaObject()->className());
        }

        StringFormula* expression = (StringFormula*)object->bself();

        try {
            expression->setFormula(_formula->text());
        } catch (ParserException* ex) {
            log->error("Error when parsing formula", ex);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString StringFormulaSwing::toString() {
        return tr("StringFormula");
    }

    //@Override
    /*public*/  void StringFormulaSwing::dispose() {
    }


    /*private*/ /*final*/ /*static*/ Logger* StringFormulaSwing::log = LoggerFactory::getLogger("StringFormulaSwing");
