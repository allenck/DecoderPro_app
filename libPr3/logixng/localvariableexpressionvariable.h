#ifndef LOCALVARIABLEEXPRESSIONVARIABLE_H
#define LOCALVARIABLEEXPRESSIONVARIABLE_H

#include "variable.h"

class LocalVariableExpressionVariable : public Variable
{
  Q_INTERFACES(Variable)
 public:
  LocalVariableExpressionVariable(QString name);
  /*public*/  QString getName()override;
  /*public*/  QVariant getValue(SymbolTable* symbolTable) /*throws JmriException*/override;
  /*public*/  void setValue(SymbolTable* symbolTable, QVariant value) /*throws JmriException*/override;

  QObject* vself() override {return (QObject*)this;}

 private:
  /*private*/ /*final*/ QString _name;

};

#endif // LOCALVARIABLEEXPRESSIONVARIABLE_H
