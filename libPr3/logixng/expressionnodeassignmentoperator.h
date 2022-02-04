#ifndef EXPRESSIONNODEASSIGNMENTOPERATOR_H
#define EXPRESSIONNODEASSIGNMENTOPERATOR_H

#include "expressionnode.h"
#include "tokentype.h"

class ExpressionNodeAssignmentOperator : public QObject, public ExpressionNode
{
  Q_OBJECT
 public:
  ExpressionNodeAssignmentOperator(TokenType::TTYPE tokenType, ExpressionNode* leftSide, ExpressionNode* rightSide);
  /*public*/ QVariant calculate(SymbolTable* symbolTable) /*throws JmriException*/override;
  /*public*/ QString getDefinitionString()override;

 private:
  /*private*/ /*final*/ TokenType::TTYPE _tokenType;
  /*private*/ /*final*/ ExpressionNode* _leftSide;
  /*private*/ /*final*/ ExpressionNode* _rightSide;
  /*private*/ QVariant add(QVariant left, QVariant right) /*throws CalculateException*/;
  /*private*/ QVariant subtract(QVariant left, QVariant right) /*throws CalculateException*/;
  /*private*/ QVariant multiply(QVariant left, QVariant right) /*throws CalculateException*/;
  /*private*/ QVariant divide(QVariant left, QVariant right) /*throws CalculateException*/;
  /*private*/ QVariant modulo(QVariant left, QVariant right) /*throws CalculateException*/;

};

#endif // EXPRESSIONNODEASSIGNMENTOPERATOR_H
