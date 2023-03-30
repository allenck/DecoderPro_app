#ifndef DEFAULTFEMALEANYSOCKET_H
#define DEFAULTFEMALEANYSOCKET_H
#include "abstractfemalesocket.h"
#include "femaleanysocket.h"
#include "base.h"
#include "category.h"
#include <QMap>

class DefaultFemaleAnySocket : public AbstractFemaleSocket, public FemaleAnySocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleAnySocket)
 public:
  /*public*/ DefaultFemaleAnySocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObject=nullptr);
  /*public*/ void disposeMe() override;
  /*public*/ bool isCompatible(MaleSocket* socket)override;
  /*public*/ QHash<Category, QList<QString> > getConnectableClasses()override;
  /*public*/ QString getShortDescription(QLocale locale)override;
  /*public*/ QString getLongDescription(QLocale locale)override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.implementation.DefaultFemaleAnySocket";}
  /*public*/ QString getClass() const override {return "jmri.jmrit.logixng.implementation.DefaultFemaleAnySocket";}

  QObject* bself() override {return (QObject*)this;}
  /*public*/ QString getSystemName() const override {return AbstractFemaleSocket::getSystemName();}
  /*public*/ QString getUserName() const override {return AbstractFemaleSocket::getUserName();}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)  override
  {return AbstractFemaleSocket::getUsageDetail(level,bean, report, cdl );}
  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override { }
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override{return AbstractFemaleSocket::toString();}
};

#endif // DEFAULTFEMALEANYSOCKET_H
