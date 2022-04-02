#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include "functionfactory.h"

class MathFunctions : public QObject, public FunctionFactory
{
  Q_OBJECT
  Q_INTERFACES(FunctionFactory)
 public:
  explicit MathFunctions(QObject *parent = nullptr) : QObject(parent) {setObjectName("MathFunctions");}
  /*public*/  QString getModule() override;
  /*public*/  QSet<Function*> getFunctions()override;
  /*public*/  QSet<Constant*> getConstants()override;
  /*public*/  QString getConstantDescription()override;

};
/*public*/  /*static*/ class RandomFunction : public QObject, public Function {
    Q_OBJECT
  Q_INTERFACES(Function)
 public:
  RandomFunction() : Function() {}
    //@Override
    /*public*/  QString getModule()override;
    /*public*/  QString getConstantDescriptions()override;
    /*public*/  QString getName()override;
    /*public*/  QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
            /*throws CalculateException, JmriException*/ override;
    /*public*/  QString getDescription()override;

  QObject* self() override {return (QObject*)this;}
};

/*public*/  /*static*/ class SinFunction : public QObject, public  Function {
  Q_OBJECT
  Q_INTERFACES(Function)
    public:
  SinFunction(QObject* parent = nullptr) : Function() {}
    /*public*/  QString getModule()override;
    /*public*/  QString getConstantDescriptions()override;
    /*public*/  QString getName() override;
    /*public*/  QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)override;
    /*public*/  QString getDescription()override;;

  QObject* self() override {return (QObject*)this;}

};
#endif // MATHFUNCTIONS_H
