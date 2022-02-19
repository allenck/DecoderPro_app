#ifndef DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H
#define DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"
#include "instancemanager.h"
#include "stringactionmanager.h"
#include "defaultfemalestringactionsocket.h"

class DefaultFemaleStringActionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
 public:
  explicit DefaultFemaleStringActionSocketFactory(QObject *parent = nullptr);
  /*public*/  FemaleSocketManager::SocketType* getFemaleSocketType();

 signals:

 private:
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();
  /*private*/ /*static*/ class SocketType : public FemaleSocketManager::SocketType {

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
          return (StringActionManager*)InstanceManager::getDefault("StringActionManager");
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

};

#endif // DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H
