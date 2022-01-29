#ifndef EXPRESSIONNODEFLOATINGNUMBER_H
#define EXPRESSIONNODEFLOATINGNUMBER_H

#include "expressionnode.h"
#include "token.h"
class ExpressionNodeFloatingNumber : public ExpressionNode
{
 public:
  ExpressionNodeFloatingNumber(Token* token);
  /*public*/  QVariant calculate(SymbolTable*)override;
  /*public*/  QString getDefinitionString()override;

 private:
  /*private*/ /*final*/ Token* _token;
  /*private*/ /*final*/ double _value;

};

#endif // EXPRESSIONNODEFLOATINGNUMBER_H
