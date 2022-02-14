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
  /*public*/ QMap<Category::TYPE, QList<QString> > getConnectableClasses()override;
  /*public*/ QString getShortDescription(QLocale locale)override;
  /*public*/ QString getLongDescription(QLocale locale)override;

  QObject* self() override {return (QObject*)this;}
  /*public*/ QString getSystemName() const override {return AbstractFemaleSocket::getSystemName();}
  /*public*/ QString getUserName() const override {return AbstractFemaleSocket::getUserName();}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)  override
   {return AbstractFemaleSocket::getUsageDetail(level,bean, report, cdl );}

};

#endif // DEFAULTFEMALEANYSOCKET_H
