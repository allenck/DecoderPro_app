#ifndef ABSTRACTANALOGACTION_H
#define ABSTRACTANALOGACTION_H

#include "abstractbase.h"
#include "analogactionbean.h"

class AbstractAnalogAction : public AbstractBase, public AnalogActionBean
{
  Q_OBJECT
  Q_INTERFACES(AnalogActionBean)
 public:
  explicit AbstractAnalogAction(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent) override;
  /*public*/  QString getBeanType()override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString getNewSocketName();
 private:
  static Logger* log;
  /*private*/ Base* _parent = nullptr;
  /*private*/ int _state = AnalogActionBean::UNKNOWN;

};

#endif // ABSTRACTANALOGACTION_H
