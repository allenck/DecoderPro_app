#ifndef EXPRESSIONNODETERNARYOPERATOR_H
#define EXPRESSIONNODETERNARYOPERATOR_H

#include "expressionnode.h"

class ExpressionNodeTernaryOperator : public ExpressionNode
{
  Q_OBJECT
 public:
  ExpressionNodeTernaryOperator(ExpressionNode* leftSide, ExpressionNode* middleSide, ExpressionNode* rightSide);
  /*public*/ QVariant calculate(SymbolTable* symbolTable) /*throws JmriException*/override;
  /*public*/ QString getDefinitionString()override;

 private:

  /*private*/ /*final*/ ExpressionNode* _leftSide;
  /*private*/ /*final*/ ExpressionNode* _middleSide;
  /*private*/ /*final*/ ExpressionNode* _rightSide;
};

#endif // EXPRESSIONNODETERNARYOPERATOR_H
