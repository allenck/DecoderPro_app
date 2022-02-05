#ifndef DEFAULTFEMALEDIGITALACTIONSOCKET_H
#define DEFAULTFEMALEDIGITALACTIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaledigitalactionsocket.h"

class DefaultFemaleDigitalActionSocket : public AbstractFemaleSocket, public FemaleDigitalActionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleDigitalActionSocket)
 public:
  DefaultFemaleDigitalActionSocket(Base* parentObject, FemaleSocketListener* listener, QString name, QObject*parent = nullptr);
  /*public*/  bool isCompatible(MaleSocket* socket)override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  QMap<Category *, QList<Base *> > getConnectableClasses()override;
  /*public*/  void disposeMe()override;

  QObject* self() override{return(QObject*)this;}
  QString getUserName() const override{return AbstractFemaleSocket::getUserName();}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl)override
  {AbstractFemaleSocket::getUsageDetail(level,bean, report,cdl );}

};


#endif // DEFAULTFEMALEDIGITALACTIONSOCKET_H
