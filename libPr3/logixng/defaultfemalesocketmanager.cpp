#include "defaultfemalesocketmanager.h"
#include "femalesocketfactory.h"
/**
*
* @author daniel
*/
///*public*/  class DefaultFemaleSocketManager implements FemaleSocketManager {

   /*private*/ /*static*/ /*final*/ QMap<QString, FemaleSocketManager::SocketType*> DefaultFemaleSocketManager::femaleSocketTypes = QMap<QString, FemaleSocketManager::SocketType*>();

   /*public*/  DefaultFemaleSocketManager::DefaultFemaleSocketManager(QObject* parent) : QObject(parent) {
       foreach (FemaleSocketFactory* actionFactory , /*ServiceLoader.load("FemaleSocketFactory")*/serviceList) {
           femaleSocketTypes.insert(actionFactory->getFemaleSocketType()->getName(), actionFactory->getFemaleSocketType());
       }
   }

   //@Override
   /*public*/  QMap<QString, FemaleSocketManager::SocketType*> DefaultFemaleSocketManager::getSocketTypes() {
       return QMap<QString, FemaleSocketManager::SocketType*>(femaleSocketTypes);
   }

   //@Override
   /*public*/  FemaleSocketManager::SocketType* DefaultFemaleSocketManager::getSocketTypeByType(QString type) {
       return femaleSocketTypes.value(type);
   }


