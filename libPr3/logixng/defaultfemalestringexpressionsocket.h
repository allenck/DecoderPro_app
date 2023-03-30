#ifndef DEFAULTFEMALESTRINGEXPRESSIONSOCKET_H
#define DEFAULTFEMALESTRINGEXPRESSIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femalestringexpressionsocket.h"

class DefaultFemaleStringExpressionSocket : public AbstractFemaleSocket, public FemaleStringExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleStringExpressionSocket)
 public:
  DefaultFemaleStringExpressionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObj = nullptr);
  /*public*/   bool isCompatible(MaleSocket* socket)override;
  /*public*/   QString evaluate() /*throws JmriException*/override;
  /*public*/   bool getTriggerOnChange()override;
  /*public*/   void setTriggerOnChange(bool triggerOnChange)override;
  /*public*/   QString getShortDescription(QLocale locale)override;
  /*public*/   QString getLongDescription(QLocale locale)override;
  /*public*/   QHash<Category, QList</*Class<? extends Base>*/QString>> getConnectableClasses() override;
  /*public*/   void disposeMe()override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.implementation.DefaultFemaleStringExpressionSocket";}
  /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.implementation.DefaultFemaleStringExpressionSocket";}


  QObject* bself() override{return (QObject*)this;}

  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override {return getLongDescription(QLocale());}

};

#endif // DEFAULTFEMALESTRINGEXPRESSIONSOCKET_H
