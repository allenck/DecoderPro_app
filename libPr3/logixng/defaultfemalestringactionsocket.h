#ifndef DEFAULTFEMALESTRINGACTIONSOCKET_H
#define DEFAULTFEMALESTRINGACTIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femalestringactionsocket.h"

class DefaultFemaleStringActionSocket : public AbstractFemaleSocket, public FemaleStringActionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleStringActionSocket)
 public:
  DefaultFemaleStringActionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObject = nullptr);
  /*public*/  bool isCompatible(MaleSocket* socket)override;
  /*public*/  void setValue(QString value) /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getConnectableClasses()override;
  /*public*/  void disposeMe()override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.implementation.DefaultFemaleStringActionSocket";}


  QObject* bself() override {return (QObject*)this;}

  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override {return getLongDescription(QLocale());}

};
#endif // DEFAULTFEMALESTRINGACTIONSOCKET_H
