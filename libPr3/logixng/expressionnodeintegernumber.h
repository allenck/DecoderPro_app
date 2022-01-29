#ifndef EXPRESSIONNODEINTEGERNUMBER_H
#define EXPRESSIONNODEINTEGERNUMBER_H

#include "expressionnode.h"
#include "token.h"
class ExpressionNodeIntegerNumber : public ExpressionNode
{
 public:
  ExpressionNodeIntegerNumber(Token* token);
  /*public*/  QVariant calculate(SymbolTable* symbolTable)override;
  /*public*/  QString getDefinitionString()override;

 private:
  /*private*/ /*final*/ Token* _token;
  /*private*/ /*final*/ long _value;


};

#endif // EXPRESSIONNODEINTEGERNUMBER_H
