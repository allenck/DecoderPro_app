#ifndef DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H
#define DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"
#include "instancemanager.h"
#include "defaultstringactionmanager.h"
#include "defaultfemalestringactionsocket.h"

class DefaultFemaleStringActionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketFactory)
 public:
  /*private*/ /*static*/ class SocketType : public FemaleSocketManager::SocketType {
 public:
      //@Override
      /*public*/  QString getName() {
          return "DefaultFemaleStringActionSocket";
      }

      //@Override
      /*public*/  QString getDescr() {
          return tr("String action socket");
      }

      //@Override
      /*public*/  BaseManager/*<? extends MaleSocket>*/* getManager() {
          return (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
      }

      //@Override
      /*public*/  FemaleSocket* createSocket(Base* parent, FemaleSocketListener* listener, QString name) {
          return new DefaultFemaleStringActionSocket(parent, listener, name);
      }

      //@Override
      /*public*/  QString toString() {
          return getDescr();
      }
  };


explicit DefaultFemaleStringActionSocketFactory(QObject *parent = nullptr)
   : QObject(parent) {setObjectName("DefaultFemaleStringActionSocketFactory");}
  /*public*/  FemaleSocketManager::SocketType* getFemaleSocketType();

 private:
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();
 public:

};
#endif // DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H
