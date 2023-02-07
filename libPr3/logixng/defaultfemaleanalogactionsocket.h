#ifndef DEFAULTFEMALEANALOGACTIONSOCKET_H
#define DEFAULTFEMALEANALOGACTIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaleanalogactionsocket.h"
#include <QObject>
#include "abstractmalesocket.h"

class Base;
class FemaleSocketListener;
class DefaultFemaleAnalogActionSocket : public AbstractFemaleSocket, public FemaleAnalogActionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleAnalogActionSocket)
 public:
  /*public*/  DefaultFemaleAnalogActionSocket(Base* parentObject, FemaleSocketListener* listener, QString name, QObject* parent= nullptr);
  /*public*/  bool isCompatible(MaleSocket *socket)override;
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getConnectableClasses()override;
  /*public*/  void setValue(double value) /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  void disposeMe()override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.implementation.DefaultFemaleAnalogActionSocket";}


  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

  QString getUserName() const override {return AbstractFemaleSocket::getUserName();}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) override
  {
   AbstractFemaleSocket::getUsageDetail(level, bean, report, cdl);
  }
  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override {return getLongDescription(QLocale());}

};

#endif // DEFAULTFEMALEANALOGACTIONSOCKET_H
