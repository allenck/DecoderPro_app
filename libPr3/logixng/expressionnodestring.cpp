#include "expressionnodestring.h"

/**
 * A parsed expression
 */
///*public*/  class ExpressionNodeString implements ExpressionNode {


    /*public*/  ExpressionNodeString::ExpressionNodeString(Token* token) {
        _token = token;
    }

    //@Override
    /*public*/  QVariant ExpressionNodeString::calculate(SymbolTable* symbolTable) {
        return _token->getString();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionNodeString::getDefinitionString() {
        return "String:"+_token->getString();
    }


