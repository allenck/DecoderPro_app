#include "expressionnodefalse.h"

/**
 * A parsed expression that always return false
 */
// /*public*/ class ExpressionNodeFalse implements ExpressionNode {

    /*public*/ ExpressionNodeFalse::ExpressionNodeFalse(QObject* parent) {
    }

    //@Override
    /*public*/ QVariant ExpressionNodeFalse::calculate(SymbolTable* symbolTable) {
        return false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString ExpressionNodeFalse::getDefinitionString() {
        return "false";
    }
