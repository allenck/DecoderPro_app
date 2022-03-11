#ifndef VARIABLE_H
#define VARIABLE_H
#include "symboltable.h"

/**
 * A variable
 */
/*public*/ /*interface*/ class Variable {

 public:
    /*public*/ virtual QString getName()=0;

    /*public*/ virtual QVariant getValue(SymbolTable* symbolTable) /*throws JmriException*/=0;

    /*public*/ virtual void setValue(SymbolTable* symbolTable, QVariant value) /*throws JmriException*/=0;

  virtual QObject* vself() =0;
};
Q_DECLARE_INTERFACE(Variable, "Variable")
#endif // VARIABLE_H
