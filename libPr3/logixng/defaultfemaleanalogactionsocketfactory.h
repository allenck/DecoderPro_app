#ifndef DEFAULTFEMALEANALOGACTIONSOCKETFACTORY_H
#define DEFAULTFEMALEANALOGACTIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"
#include "instancemanager.h"
#include "defaultanalogactionmanager.h"
#include "defaultfemaleanalogactionsocket.h"

class SocketType;
class DefaultFemaleAnalogActionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketFactory)
 public:
  /*private*/ /*static*/ class SocketType : public FemaleSocketManager::SocketType {
      public:
      //@Override
      /*public*/  QString getName()override {
          return "DefaultFemaleAnalogActionSocket";
      }

      //@Override
      /*public*/  QString getDescr()override {
          return tr("Analog action socket");
      }

      //@Override
      /*public*/  BaseManager/*<? extends MaleSocket>*/* getManager() override{
          return (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
      }

      //@Override
      /*public*/  FemaleSocket* createSocket(Base* parent, FemaleSocketListener* listener, QString name)override {
          return (new DefaultFemaleAnalogActionSocket(parent, listener, name));
      }
      //@Override
      /*public*/  QString toString() {
          return getDescr();
      }
  };
 public:
  explicit DefaultFemaleAnalogActionSocketFactory(QObject *parent = nullptr)
   : QObject(parent) {setObjectName("DefaultFemaleAnalogActionSocketFactory");}
  /*public*/  FemaleSocketManager::SocketType* getFemaleSocketType()override;

 signals:

 private:
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();


};

#endif // DEFAULTFEMALEANALOGACTIONSOCKETFACTORY_H
