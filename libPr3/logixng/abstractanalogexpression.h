#ifndef ABSTRACTANALOGEXPRESSION_H
#define ABSTRACTANALOGEXPRESSION_H

#include "abstractbase.h"
#include "Analogexpressionbean.h"

class AbstractAnalogExpression : public AbstractBase, public AnalogExpressionBean
{
  Q_OBJECT
  Q_INTERFACES(AnalogExpressionBean)
 public:
  explicit AbstractAnalogExpression(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent)override;
  /*public*/  QString getBeanType()override;
  /*public*/  void setState(int s) /*throws JmriException */override;
  /*public*/  int getState()override;
  /*public*/  void setTriggerOnChange(bool triggerOnChange)override;
  /*public*/  bool getTriggerOnChange()override;
  /*public*/  QString getNewSocketName();

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}


 private:
  static Logger* log;
  /*private*/ Base* _parent = nullptr;
  /*private*/ int _state = AnalogExpressionBean::UNKNOWN;
  bool _triggerOnChange = true;    // By default, trigger on change

};

#endif // ABSTRACTANALOGEXPRESSION_H
