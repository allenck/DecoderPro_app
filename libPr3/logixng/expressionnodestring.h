#ifndef EXPRESSIONNODESTRING_H
#define EXPRESSIONNODESTRING_H

#include "expressionnode.h"
#include "token.h"

class ExpressionNodeString : public ExpressionNode
{
 public:
  ExpressionNodeString(Token* token);
  /*public*/  QVariant calculate(SymbolTable* )override;
  /*public*/  QString getDefinitionString()override;

 private:
  /*private*/ /*final*/ Token* _token;
};

#endif // EXPRESSIONNODESTRING_H
