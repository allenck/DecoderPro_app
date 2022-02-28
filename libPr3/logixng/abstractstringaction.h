#ifndef ABSTRACTSTRINGACTION_H
#define ABSTRACTSTRINGACTION_H

#include "abstractbase.h"
#include "stringactionbean.h"
#include "stringexpressionbean.h"

class AbstractStringAction : public AbstractBase, public StringActionBean
{
  Q_OBJECT
  Q_INTERFACES(StringActionBean)
 public:
  explicit AbstractStringAction(QString sys, QString user, QObject* parent=nullptr);
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent)override;
  /*public*/  QString getBeanType() override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString getNewSocketName();

 private:
  static Logger* log;
  /*private*/ Base* _parent = nullptr;
  /*private*/ int _state = StringExpressionBean::UNKNOWN;

};

#endif // ABSTRACTSTRINGACTION_H
