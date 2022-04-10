#ifndef GENERICEXPRESSIONVARIABLE_H
#define GENERICEXPRESSIONVARIABLE_H

#include <QObject>
#include "variable.h"

class Logger;
class FemaleGenericExpressionSocket;
class GenericExpressionVariable :  public Variable
{
  Q_OBJECT
  //Q_INTERFACES(Variable)
 public:
  GenericExpressionVariable(FemaleGenericExpressionSocket* socket, QObject *parent = nullptr);
  /*public*/  QString getName() override;
  /*public*/  QVariant getValue(SymbolTable* symbolTable) /*throws JmriException*/override;
  /*public*/  void setValue(SymbolTable* symbolTable, QVariant value) /*throws JmriException*/ override;

  //QObject* vself() override {return (QObject*)this;}
 signals:

 private:
  static Logger* log;
  /*private*/ /*final*/ FemaleGenericExpressionSocket* _socket;

};

#endif // GENERICEXPRESSIONVARIABLE_H
