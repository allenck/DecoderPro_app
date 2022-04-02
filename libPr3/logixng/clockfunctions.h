#ifndef CLOCKFUNCTIONS_H
#define CLOCKFUNCTIONS_H

#include "functionfactory.h"
#include "timebase.h"
#include "instancemanager.h"
class ClockFunctions : public QObject, public FunctionFactory
{
  Q_OBJECT
  Q_INTERFACES(FunctionFactory)
 public:
  ClockFunctions() : FunctionFactory() {}
      /*public*/  QString getModule()override;
      /*public*/  QSet<Function*> getFunctions()override;
      /*public*/  QSet<Constant*> getConstants()override;
      /*public*/  QString getConstantDescription()override;
};
/*public*/  /*static*/ class SystemClockFunction : public QObject, public Function {
  Q_OBJECT
  Q_INTERFACES(Function)
 public:
  SystemClockFunction() {}
    /*public*/  QString getModule() override;
    /*public*/  QString getConstantDescriptions()override;
    /*public*/  QString getName()override;
    /*public*/  QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)override;
    /*public*/  QString getDescription()override;
  QObject* self() override {return (QObject*)this;}
 private:
  /*private*/ /*final*/ Timebase* _fastClock = (Timebase*)InstanceManager::getDefault("Timebase");

};

/*public*/  /*static*/ class FastClockFunction : public QObject, public Function {
  Q_OBJECT
  Q_INTERFACES(Function)
 public:
  FastClockFunction() {}
  /*public*/  QString getModule()override;
  /*public*/  QString getConstantDescriptions()override;
  /*public*/  QString getName()override;
  /*public*/  QVariant calculate(SymbolTable* symbolTable, QList<ExpressionNode*> parameterList)override;
  /*public*/  QString getDescription()override;
  QObject* self() override {return (QObject*)this;}

 private:
  /*private*/ /*final*/ Timebase* _fastClock = (Timebase*)InstanceManager::getDefault("Timebase");

};

#endif // CLOCKFUNCTIONS_H
