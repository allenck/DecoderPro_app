#ifndef EXPRESSIONNODEFALSE_H
#define EXPRESSIONNODEFALSE_H

#include "expressionnode.h"

class ExpressionNodeFalse : QObject, public ExpressionNode
{
    Q_OBJECT
    Q_INTERFACES(ExpressionNode)
public:
    ExpressionNodeFalse(QObject* parent = nullptr);
    /*public*/ QVariant calculate(SymbolTable* symbolTable) override;
    /*public*/ QString getDefinitionString() override;

};

#endif // EXPRESSIONNODEFALSE_H
