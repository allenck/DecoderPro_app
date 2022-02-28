#ifndef ABSTRACTDIGITALBOOLEANACTION_H
#define ABSTRACTDIGITALBOOLEANACTION_H

#include "abstractbase.h"
#include "digitalbooleanactionbean.h"

class AbstractDigitalBooleanAction : public AbstractBase, public DigitalBooleanActionBean
{
  Q_OBJECT
  Q_INTERFACES(DigitalBooleanActionBean)
 public:
  explicit AbstractDigitalBooleanAction(QString sys, QString user,QObject *parent = nullptr);
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent)override;
  /*public*/  QString getNewSocketName();
  /*public*/  QString getBeanType()override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;

 private:
  static Logger* log;
  /*private*/ Base* _parent = nullptr;
  /*private*/ int _state = DigitalBooleanActionBean::UNKNOWN;


};

#endif // ABSTRACTDIGITALBOOLEANACTION_H
