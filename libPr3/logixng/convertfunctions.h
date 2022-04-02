#ifndef CONVERTFUNCTIONS_H
#define CONVERTFUNCTIONS_H

#include <QObject>
#include "functionfactory.h"
#include "function.h"
class ConvertFunctions : public QObject, public FunctionFactory
{
  Q_OBJECT
  Q_INTERFACES(FunctionFactory)
 public:
  explicit ConvertFunctions(QObject *parent = nullptr) : QObject(parent) {}
  /*public*/  QString getModule()override;
  /*public*/  QSet<Function*> getFunctions() override;
  /*public*/  QSet<Constant*> getConstants() override;
  /*public*/  QString getConstantDescription()override;
 signals:

};
/*public*/  /*static*/ class IntFunction : public QObject, public Function {
  Q_OBJECT
    public:
  IntFunction() {}
    //@Override
    /*public*/  QString getModule()override;
    /*public*/  QString getConstantDescriptions() override;
    /*public*/  QString getName()override;
    /*public*/  QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
            /*throws JmriException*/ override;
    /*public*/  QString getDescription() override;

    QObject* self() override {return (QObject*)this;}
};

/*public*/  /*static*/ class FloatFunction : public QObject, public Function {
  Q_OBJECT
    public:
  FloatFunction() {}
    //@Override
    /*public*/  QString getModule()override;
    /*public*/  QString getConstantDescriptions()override;
    /*public*/  QString getName()override;
    /*public*/  QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
            /*throws JmriException */override;
    /*public*/  QString getDescription()override;

    QObject* self() override {return (QObject*)this;}
};

/*public*/  /*static*/ class StrFunction : public QObject, public Function {
  Q_OBJECT
    public:
  StrFunction() {}
    //@Override
    /*public*/  QString getModule()override;
    /*public*/  QString getConstantDescriptions()override;
    /*public*/  QString getName()override;
    /*public*/  QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)
            /*throws JmriException*/ override;
    /*public*/  QString getDescription()override;

    QObject* self() override {return (QObject*)this;}
};

#endif // CONVERTFUNCTIONS_H
