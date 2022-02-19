#ifndef DEFAULTFEMALEANALOGEXPRESSIONSOCKET_H
#define DEFAULTFEMALEANALOGEXPRESSIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaleanalogexpressionsocket.h"

class Base;
class FemaleSocketListener;
class DefaultFemaleAnalogExpressionSocket : public AbstractFemaleSocket, public FemaleAnalogExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleAnalogExpressionSocket)
 public:
  DefaultFemaleAnalogExpressionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObject = nullptr);
  /*public*/  bool isCompatible(MaleSocket* socket)override ;
  /*public*/  double evaluate() /*throws JmriException*/override;
  /*public*/  bool getTriggerOnChange()override;
  /*public*/  void setTriggerOnChange(bool triggerOnChange)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  QMap<Category*, QList</*Class<? extends Base>*/QString>*> getConnectableClasses() override;
  /*public*/  void disposeMe()override;

  QObject* bself() override{return (QObject*)this;}
};
#endif // DEFAULTFEMALEANALOGEXPRESSIONSOCKET_H
