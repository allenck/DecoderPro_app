#include "expressionnodeidentifier.h"
#include "localvariableexpressionvariable.h"
/**
 * A parsed expression
 */
///*public*/  class ExpressionNodeIdentifier implements ExpressionNode {


    /*public*/  ExpressionNodeIdentifier::ExpressionNodeIdentifier(Token* token, QMap<QString, Variable*> variables) /*throws IdentifierNotExistsException*/ {
        _token = token;
        Variable* variable = variables.value(token->getString());

        if (variable == nullptr) {
            // Assume the identifier is a local variable.
            // Local variables may not be known when the expression is parsed.

            variable = new LocalVariableExpressionVariable(token->getString());
        }

        _variable = variable;
    }

    /*public*/  QString ExpressionNodeIdentifier::getIdentifier() {
        return _token->getString();
    }

    //@Override
    /*public*/  QVariant ExpressionNodeIdentifier::calculate(SymbolTable* symbolTable) /*throws JmriException*/ {
        return _variable->getValue(symbolTable);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionNodeIdentifier::canBeAssigned() {
        // If the identifier is a local variable, assignment is possible. And
        // we don't know if the identifier is a valid local variable until the
        // expression is calculated. So we assume that it is.
        return true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionNodeIdentifier::assignValue(SymbolTable* symbolTable, QVariant value) /*throws JmriException*/ {
        if (_variable != nullptr) {
            _variable->setValue(symbolTable, value);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionNodeIdentifier::getDefinitionString() {
        return "Identifier:"+_token->getString();
    }
