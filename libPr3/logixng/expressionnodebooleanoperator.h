#ifndef EXPRESSIONNODEBOOLEANOPERATOR_H
#define EXPRESSIONNODEBOOLEANOPERATOR_H

#include "expressionnode.h"
#include "tokentype.h"
#include <QObject>

class ExpressionNodeBooleanOperator : public QObject, public ExpressionNode
{
  Q_OBJECT
 public:
  ExpressionNodeBooleanOperator(TokenType::TTYPE tokenType, ExpressionNode* leftSide, ExpressionNode* rightSide);
  /*public*/ QVariant calculate(SymbolTable* symbolTable) /*throws JmriException */;
  /*public*/ QString getDefinitionString()override;

 private:
  /*private*/ /*final*/ TokenType::TTYPE _tokenType;
  /*private*/ /*final*/ ExpressionNode* _leftSide;
  /*private*/ /*final*/ ExpressionNode* _rightSide;
};

#endif // EXPRESSIONNODEBOOLEANOPERATOR_H
