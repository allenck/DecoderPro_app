#include "genericexpressionvariable.h"
#include "loggerfactory.h"
#include "femalegenericexpressionsocket.h"

/**
 * A variable that evaluates a generic expression
 */
// /*public*/  class GenericExpressionVariable implements Variable {



    /*public*/  GenericExpressionVariable::GenericExpressionVariable(FemaleGenericExpressionSocket* socket, QObject* parent) : QObject(parent){
        _socket = socket;
    }

    //@Override
    /*public*/  QString GenericExpressionVariable::getName() {
        return _socket->getName();
    }

    //@Override
    /*public*/  QVariant GenericExpressionVariable::getValue(SymbolTable* symbolTable) /*throws JmriException*/ {
        return _socket->evaluateGeneric();
    }

    //@Override
    /*public*/  void GenericExpressionVariable::setValue(SymbolTable* symbolTable, QVariant value) /*throws JmriException*/ {
        log->error("An expression cannot be assigned a value");
    }

    /*private*/ /*final*/ /*static*/ Logger* GenericExpressionVariable::log = LoggerFactory::getLogger("GenericExpressionVariable");
