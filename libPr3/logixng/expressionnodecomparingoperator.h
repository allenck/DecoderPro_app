#ifndef EXPRESSIONNODECOMPARINGOPERATOR_H
#define EXPRESSIONNODECOMPARINGOPERATOR_H

#include "expressionnode.h"
#include "tokentype.h"

class ExpressionNodeComparingOperator : public QObject, public ExpressionNode
{
  Q_OBJECT
  Q_INTERFACES(ExpressionNode)
 public:
  ExpressionNodeComparingOperator(TokenType::TTYPE tokenType, ExpressionNode* leftSide, ExpressionNode* rightSide);
  /*public*/  QVariant calculateNull(QVariant left, QVariant right) /*throws JmriException*/;
  /*public*/  QVariant calculate(SymbolTable* symbolTable)/* throws JmriException*/override;
  /*public*/  QString getDefinitionString()override;

 private:
  /*private*/ /*final*/ TokenType::TTYPE _tokenType;
  /*private*/ /*final*/ ExpressionNode* _leftSide;
  /*private*/ /*final*/ ExpressionNode* _rightSide;

};

#endif // EXPRESSIONNODECOMPARINGOPERATOR_H
