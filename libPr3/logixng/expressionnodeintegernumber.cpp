#include "expressionnodeintegernumber.h"

/**
 * A parsed expression
 */
// /*public*/  class ExpressionNodeIntegerNumber implements ExpressionNode {

    /*public*/  ExpressionNodeIntegerNumber::ExpressionNodeIntegerNumber(Token* token) {
        _token = token;
        _value = token->getString().toInt();
    }

    //@Override
    /*public*/  QVariant ExpressionNodeIntegerNumber::calculate(SymbolTable* symbolTable) {
        return  QVariant::fromValue(_value);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionNodeIntegerNumber::getDefinitionString() {
        return "IntNumber:"+_token->getString();
    }


