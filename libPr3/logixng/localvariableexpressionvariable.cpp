#include "localvariableexpressionvariable.h"
#include "constant.h"
#include "functionmanager.h"
#include "instancemanager.h"

/**
 * A variable that evaluates a local variable
 */
///*public*/  class LocalVariableExpressionVariable implements Variable {


    /*public*/  LocalVariableExpressionVariable::LocalVariableExpressionVariable(QString name) {
        _name = name;
    }

    //@Override
    /*public*/  QString LocalVariableExpressionVariable::getName() {
        return _name;
    }

    //@Override
    /*public*/  QVariant LocalVariableExpressionVariable::getValue(SymbolTable* symbolTable) /*throws JmriException*/ {
        try {
            return symbolTable->getValue(_name);
        } catch (SymbolTable::SymbolNotFound* e) {
            Constant* constant = (Constant*)((FunctionManager*)InstanceManager::getDefault("FunctionManager"))->getConstant(_name);
            if (constant != nullptr) return constant->getValue();
            throw e;
        }
    }

    //@Override
    /*public*/  void LocalVariableExpressionVariable::setValue(SymbolTable* symbolTable, QVariant value) /*throws JmriException*/ {
        symbolTable->setValue(_name, value);
    }
