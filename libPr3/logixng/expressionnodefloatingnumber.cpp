#include "expressionnodefloatingnumber.h"

/**
 * A parsed expression
 */
// /*public*/  class ExpressionNodeFloatingNumber implements ExpressionNode {


    /*public*/  ExpressionNodeFloatingNumber::ExpressionNodeFloatingNumber(Token* token) {
        _token = token;
        _value = token->getString().toDouble();
    }

    //@Override
    /*public*/  QVariant ExpressionNodeFloatingNumber::calculate(SymbolTable* /*symbolTable*/) {
        return _value;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionNodeFloatingNumber::getDefinitionString() {
        return "FloatNumber:"+_token->getString();
    }
