#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H
#include <QtCore>
#include "symboltable.h"

/**
 * A parsed expression
 */
/*public*/ /*interface*/class ExpressionNode {

 public:
    /**
     * Calculate the expression
     * @param symbolTable the symbol table
     * @return the result
     * @throws JmriException if an error occurs
     */
    /*public*/ virtual QVariant calculate(SymbolTable* symbolTable) /*throws JmriException*/=0;

    /**
     * Can this expression be assigned a value?
     * @return true if it's possible to assign a value to this expression,
     *         false otherwise
     */
    /*public*/ virtual /*default*/ bool canBeAssigned() {
        return false;
    }

    /**
     * Assign a value to this expression
     * @param symbolTable the symbol table
     * @param value the value to assign
     * @throws jmri.JmriException if an error occurs
     */
    /*public*/ /*default*/ void assignValue(SymbolTable* symbolTable, QVariant value) /*throws JmriException */{
        throw new UnsupportedOperationException("This expression can't be assigned");
    }

    /**
     * Get a String that defines this expression node.
     * @return the string
     */
    /*public*/ virtual QString getDefinitionString()=0;

};
Q_DECLARE_INTERFACE(ExpressionNode, "ExpressionNode")
#endif // EXPRESSIONNODE_H
