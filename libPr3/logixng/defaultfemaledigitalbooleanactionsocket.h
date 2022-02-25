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
  /*public*/  QHash<Category*, QList</*Class<? extends Base>*/QString>> getConnectableClasses()override;
  /*public*/  void disposeMe()override;

  QObject* bself() override {return (QObject*)this;}

};

#endif // DEFAULTFEMALEDIGITALBOOLEANACTIONSOCKET_H
