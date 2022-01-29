#ifndef EXPRESSIONNODEIDENTIFIER_H
#define EXPRESSIONNODEIDENTIFIER_H

#include "expressionnode.h"
#include "token.h"
#include "variable.h"
#include <QMap>

class ExpressionNodeIdentifier : public ExpressionNode
{
 public:
  ExpressionNodeIdentifier(Token* token, QMap<QString, Variable*> variables);
  /*public*/  QString getIdentifier();
  /*public*/  QVariant calculate(SymbolTable* symbolTable) /*throws JmriException*/override;
  /*public*/  bool canBeAssigned()override;
  /*public*/  void assignValue(SymbolTable* symbolTable, QVariant value)/*throws JmriException*/;
  /*public*/  QString getDefinitionString()override;

 private:
  /*private*/ /*final*/ Token* _token;
  /*private*/ /*final*/ Variable* _variable;

};

#endif // EXPRESSIONNODEIDENTIFIER_H
