#ifndef ABSTRACTDIGITALACTION_H
#define ABSTRACTDIGITALACTION_H

#include "abstractbase.h"
#include "digitalactionbean.h"

class AbstractDigitalAction : public AbstractBase, public DigitalActionBean
{
  Q_OBJECT
  Q_INTERFACES(DigitalActionBean)
 public:
  explicit AbstractDigitalAction(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent)override;
  /*public*/  QString getNewSocketName();
  /*public*/  static QString getNewSocketName(QVector<QString> names);
  /*public*/  QString getBeanType()override;
  /*public*/  void setState(int s) /*throws JmriException*/ override;
  /*public*/  int getState()override;
 private:
  static Logger* log;
  /*private*/ Base* _parent = nullptr;
  /*private*/ int _state = NamedBean::UNKNOWN;

};

#endif // ABSTRACTDIGITALACTION_H
