#include "expressionnodefunction.h"
#include "instancemanager.h"
#include "functionmanager.h"
#include "function.h"
#include "functionnotexistsexception.h"

/**
 * A parsed expression
 *
 * @author Daniel Bergqvist 2019
 */
///*public*/  class ExpressionNodeFunction implements ExpressionNode {



    /*public*/  ExpressionNodeFunction::ExpressionNodeFunction(QString identifier, QList<ExpressionNode*> parameterList) /*throws FunctionNotExistsException*/ {
        _identifier = identifier;
        _function = ((FunctionManager*)InstanceManager::getDefault("FunctionManager"))->get(identifier);
        _parameterList = parameterList;

        if (_function == nullptr) {
            throw new FunctionNotExistsException(tr("The function \"%1\" does not exists").arg(identifier), identifier);
        }

//        System.err.format("Function %s, %s%n", _function.getName(), _function.getClass().getName());
    }

    //@Override
    /*public*/  QVariant ExpressionNodeFunction::calculate(SymbolTable* symbolTable) /*throws JmriException */{
        return _function->calculate(symbolTable, _parameterList);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ExpressionNodeFunction::getDefinitionString() {
        QString str;// = new StringBuilder();
        str.append("Function:");
        str.append(_identifier);
        str.append("(");
        for (int i=0; i < _parameterList.size(); i++) {
            if (i > 0) {
                str.append(",");
            }
            str.append(_parameterList.at(i)->getDefinitionString());
        }
        str.append(")");
        return str;
    }
