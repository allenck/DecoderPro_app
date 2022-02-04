#ifndef EXPRESSIONNODEFUNCTION_H
#define EXPRESSIONNODEFUNCTION_H

#include "expressionnode.h"
#include "function.h"
class ExpressionNodeFunction : public QObject, public ExpressionNode
{
  Q_OBJECT
 public:
  ExpressionNodeFunction(QString identifier, QList<ExpressionNode*> parameterList);
  /*public*/  QVariant calculate(SymbolTable* symbolTable) /*throws JmriException */override;
  /*public*/  QString getDefinitionString()override;

 private:
  /*private*/ /*final*/ QString _identifier;
  /*private*/ /*final*/ Function* _function;
  /*private*/ /*final*/ QList<ExpressionNode*> _parameterList;

};

#endif // EXPRESSIONNODEFUNCTION_H
