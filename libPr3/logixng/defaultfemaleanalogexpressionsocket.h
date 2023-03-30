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
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getConnectableClasses() override;
  /*public*/  void disposeMe()override;
  /*public*/ QString getClassName()override;
  /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.implementation.DefaultFemaleAnalogExpressionSocket";}


  QObject* bself() override{return (QObject*)this;}

  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override {return getLongDescription(QLocale());}

};
#endif // DEFAULTFEMALEANALOGEXPRESSIONSOCKET_H
