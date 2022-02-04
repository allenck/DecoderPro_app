#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H

#include "functionfactory.h"
#include <QObject>

class StringFunctions : public FunctionFactory
{
 public:
  StringFunctions(){}
  /*public*/ QString getModule()override;
  /*public*/ QSet<Function*> getFunctions()override;
  /*public*/ QSet<Constant*> getConstants()override;
  /*public*/ QString getConstantDescription()override;
};

/*public*/ /*static*/ class FormatFunction : public QObject, public Function {
    Q_OBJECT
  Q_INTERFACES(Function)
    /*public*/ QString getModule()override;
    /*public*/ QString getConstantDescriptions()override;
    /*public*/ QString getName()override;
    /*public*/ QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
            /*throws CalculateException, JmriException*/ override;
    /*public*/ QString getDescription()override;
  QObject* self() override {return (QObject*)this;}
};

#endif // STRINGFUNCTIONS_H
