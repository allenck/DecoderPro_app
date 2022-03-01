#ifndef DEFAULTFEMALEANALOGACTIONSOCKET_H
#define DEFAULTFEMALEANALOGACTIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaleanalogactionsocket.h"
#include <QObject>

class Base;
class FemaleSocketListener;
class DefaultFemaleAnalogActionSocket : public AbstractFemaleSocket, public FemaleAnalogActionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleAnalogActionSocket)
 public:
  /*public*/  DefaultFemaleAnalogActionSocket(Base* parentObject, FemaleSocketListener* listener, QString name, QObject* parent= nullptr);
  /*public*/  bool isCompatible(MaleSocket* socket)override;
  /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> getConnectableClasses()override;
  /*public*/  void setValue(double value) /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void disposeMe()override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

  QString getUserName() const override {return AbstractFemaleSocket::getUserName();}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) override
  {
   AbstractFemaleSocket::getUsageDetail(level, bean, report, cdl);
  }
};

#endif // DEFAULTFEMALEANALOGACTIONSOCKET_H
