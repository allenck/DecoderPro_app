#ifndef ANALOGEXPRESSIONCONSTANT_H
#define ANALOGEXPRESSIONCONSTANT_H

#include "abstractanalogexpression.h"

class AnalogExpressionConstant : public AbstractAnalogExpression
{
  Q_OBJECT

 public:
  explicit AnalogExpressionConstant(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
  /*public*/  Category getCategory()override;
  /*public*/  void setValue(double value);
  /*public*/  double getValue();
  /*public*/  double evaluate()override;
  /*public*/  FemaleSocket* getChild(int index)
          /*throws IllegalArgumentException, UnsupportedOperationException */override;
  /*public*/  int getChildCount()override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

  QObject* self() override{return (QObject*)this;}
  QObject* bself() override{return (QObject*)this;}

  QString getUserName() const override {return AbstractNamedBean::getUserName();}
  /*public*/  void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override
  {return AbstractBase::getUsageDetail(level,bean, report, cdl);}

 private:
  static Logger* log;
  /*private*/ double _value;

};

#endif // ANALOGEXPRESSIONCONSTANT_H
