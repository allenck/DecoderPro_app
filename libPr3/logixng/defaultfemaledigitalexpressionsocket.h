#ifndef DEFAULTFEMALEDIGITALEXPRESSIONSOCKET_H
#define DEFAULTFEMALEDIGITALEXPRESSIONSOCKET_H

#include "abstractfemalesocket.h"
#include "femaledigitalexpressionsocket.h"

class DefaultFemaleDigitalExpressionSocket : public AbstractFemaleSocket, public FemaleDigitalExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(FemaleDigitalExpressionSocket)
 public:
  DefaultFemaleDigitalExpressionSocket(Base* parent, FemaleSocketListener* listener, QString name, QObject* parentObj = nullptr);
  /*public*/  bool isCompatible(MaleSocket* socket)override;
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale) override;
  /*public*/  QMap<Category*, QList</*Class<? extends Base>*/Base*>> getConnectableClasses()override;
  /*public*/  void disposeMe()override;

};

#endif // DEFAULTFEMALEDIGITALEXPRESSIONSOCKET_H
