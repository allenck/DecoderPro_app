#ifndef DEFAULTFEMALESOCKETMANAGER_H
#define DEFAULTFEMALESOCKETMANAGER_H

#include "femalesocketmanager.h"
#include "defaultfemaleanalogactionsocketfactory.h"
#include "defaultfemaledigitalactionsocketfactory.h"
#include "defaultfemaledigitalexpressionsocketfactory.h"
#include "defaultfemalestringactionsocketfactory.h"
#include "defaultfemalestringexpressionsocketfactory.h"
class DefaultFemaleSocketManager : public QObject, public FemaleSocketManager
{
  Q_OBJECT
 public:
  DefaultFemaleSocketManager(QObject* parent = nullptr);
  /*public*/  QMap<QString, FemaleSocketManager::SocketType*> getSocketTypes()override;
  /*public*/  FemaleSocketManager::SocketType* getSocketTypeByType(QString type)override;

 private:
  /*private*/ static /*final*/ QMap<QString, FemaleSocketManager::SocketType*> femaleSocketTypes;// = new HashMap<>();

  QList<FemaleSocketFactory*> serviceList = {new DefaultFemaleAnalogActionSocketFactory(),
                             new DefaultFemaleAnalogExpressionSocketFactory(),
                             new DefaultFemaleDigitalActionSocketFactory(),
                             new DefaultFemaleDigitalExpressionSocketFactory(),
                             new DefaultFemaleStringActionSocketFactory(),
                             new DefaultFemaleStringExpressionSocketFactory{}
                            };
};

#endif // DEFAULTFEMALESOCKETMANAGER_H
