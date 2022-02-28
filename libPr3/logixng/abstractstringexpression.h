#ifndef ABSTRACTSTRINGEXPRESSION_H
#define ABSTRACTSTRINGEXPRESSION_H

#include "abstractbase.h"
#include "stringexpressionbean.h"

class AbstractStringExpression : public AbstractBase, public StringExpressionBean
{
  Q_OBJECT
  Q_INTERFACES(StringExpressionBean)
 public:
  explicit AbstractStringExpression(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent)override;
  /*public*/  QString getBeanType() override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  void setTriggerOnChange(bool triggerOnChange) override;
  /*public*/  bool getTriggerOnChange()override;
  /*public*/  QString getNewSocketName();

 private:
  static Logger* log;
  /*private*/ Base* _parent = nullptr;
  /*private*/ int _state = StringExpressionBean::UNKNOWN;
  bool _triggerOnChange = true;    // By default, trigger on change

};

#endif // ABSTRACTSTRINGEXPRESSION_H
