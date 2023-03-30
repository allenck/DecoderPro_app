#ifndef DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKET_H
#define DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaledigitalbooleanactionsocket.h"

class DefaultFemaleDigitalBooleanActionSocket : public AbstractFemaleSocket, public FemaleDigitalBooleanActionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleDigitalBooleanActionSocket)
 public:
  DefaultFemaleDigitalBooleanActionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObj = nullptr);
  /*public*/  bool isCompatible(MaleSocket* socket) override;
  /*public*/  void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  QHash<Category, QList</*Class<? extends Base>*/QString>> getConnectableClasses()override;
  /*public*/  void disposeMe()override;
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalBooleanActionSocket";}
  /*public*/ QString getClass() const override {return "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalBooleanActionSocket";}


  QObject* bself() override {return (QObject*)this;}

  /*public*/ /*default*/ virtual bool isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/  /*default*/ virtual void doSocketOperation(int index, FemaleSocketOperation::TYPES oper) override {}
  /*public*/ virtual QString toString() override {return getLongDescription(QLocale());}

};

#endif // DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKET_H
