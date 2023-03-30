#ifndef DEFAULTFEMALEDIGITALACTIONSOCKET_H
#define DEFAULTFEMALEDIGITALACTIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaledigitalactionsocket.h"

class DefaultFemaleDigitalActionSocket : public AbstractFemaleSocket, public FemaleDigitalActionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleDigitalActionSocket)
 public:
    explicit DefaultFemaleDigitalActionSocket(QObject*parent = nullptr)
        : AbstractFemaleSocket(parent) {}
  DefaultFemaleDigitalActionSocket(Base* parentObject, FemaleSocketListener* listener, QString name, QObject*parent = nullptr);
  ~DefaultFemaleDigitalActionSocket() {}
  /*public*/  bool isCompatible(MaleSocket* socket)override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  QHash<Category, QList<QString> > getConnectableClasses()override;
  /*public*/  void disposeMe()override;
  /*public*/ QString getClassName()override;
  /*public*/ QString getClass()const override {return "jmri.jmrit.logixng.actions.DefaultFemalDigitalActionSocket";}


  QObject* bself() override{return(QObject*)this;}
  QString getUserName() const override{return AbstractFemaleSocket::getUserName();}
  /*public*/ void getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl)override
  {AbstractFemaleSocket::getUsageDetail(level,bean, report,cdl );}

  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override {return getLongDescription(QLocale());}

};
Q_DECLARE_METATYPE(DefaultFemaleDigitalActionSocket)

#endif // DEFAULTFEMALEDIGITALACTIONSOCKET_H
