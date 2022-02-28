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
  /*public*/   QHash<Category*, QList</*Class<? extends Base>*/QString>> getConnectableClasses() override;
  /*public*/   void disposeMe()override;

  QObject* bself() override{return (QObject*)this;}
};

#endif // DEFAULTFEMALESTRINGEXPRESSIONSOCKET_H
