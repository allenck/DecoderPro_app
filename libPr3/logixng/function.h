#ifndef FUNCTION_H
#define FUNCTION_H
#include <QVariant>
#include <QMap>
#include <QList>
#include "symboltable.h"
#include "expressionnode.h"

/**
 * Definition of a function used in expressions.
 *
 * @author Daniel Bergqvist 2019
 */
/*public*/  /*interface*/class Function {

 public:
    /**
     * Get the module of the function, for example "Math" or "Conversion".
     * @return the module name
     */
    /*public*/ virtual QString getModule()=0;

    /**
     * Get the descriptions of the constants in the module.
     * @return the description of the constants
     */
    /*public*/ virtual QString getConstantDescriptions()=0;

    /**
     * Get name of the function, for example "sin" or "int"
     * @return the name
     */
    /*public*/virtual  QString getName()=0;

    /**
     * Calculate the function
     * @param symbolTable the symbol table
     * @param parameterList a list of parameters for the function
     * @return the result
     * @throws JmriException in case of an error
     */
    /*public*/virtual  QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
            /*throws JmriException*/=0;

    /**
     * Get the description of the function in Markdown format
     * @return the description
     */
    /*public*/ virtual QString getDescription()=0;

    virtual QObject* self()=0;
   };
Q_DECLARE_INTERFACE(Function, "Function")
#endif // FUNCTION_H
