#ifndef ABSTRACTDIGITALEXPRESSION_H
#define ABSTRACTDIGITALEXPRESSION_H

#include "abstractbase.h"
#include "digitalexpressionbean.h"

class AbstractDigitalExpression : public AbstractBase, public DigitalExpressionBean
{
  Q_OBJECT
  Q_INTERFACES(DigitalExpressionBean)
 public:
  explicit AbstractDigitalExpression(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  void notifyChangedResult(bool oldResult, bool newResult) override;
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent)override;
  /*public*/  QString getBeanType() override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString getNewSocketName();
  /*public*/  /*static*/ QString getNewSocketName(QVector<QString> names);
 private:
  static Logger* log;
  /*private*/ Base* _parent = nullptr;
  /*private*/ int _state = DigitalExpressionBean::UNKNOWN;

};

#endif // ABSTRACTDIGITALEXPRESSION_H
