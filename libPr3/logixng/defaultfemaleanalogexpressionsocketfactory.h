#ifndef DEFAULTFEMALEANALOGEXPRESSIONSOCKETFACTORY_H
#define DEFAULTFEMALEANALOGEXPRESSIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"
#include "defaultanalogexpressionmanager.h"
#include "instancemanager.h"
#include "defaultfemaleanalogexpressionsocket.h"

class DefaultFemaleAnalogExpressionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketFactory)
 public:
  /*private*/ /*static*/ class SocketType : public FemaleSocketManager::SocketType {
  public:
      //@Override
      /*public*/  QString getName() {
          return "DefaultFemaleAnalogExpressionSocket";
      }

      //@Override
      /*public*/  QString getDescr() {
          return tr("Analog expression socket");
      }

      //@Override
      /*public*/  BaseManager/*<? extends MaleSocket>*/* getManager() {
          return (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
      }

      //@Override
      /*public*/  FemaleSocket* createSocket(Base* parent, FemaleSocketListener* listener, QString name) {
          return (FemaleSocket*)(new DefaultFemaleAnalogExpressionSocket(parent, listener, name))->bself();
      }

      //@Override
      /*public*/  QString toString() {
          return getDescr();
      }
  };
  explicit DefaultFemaleAnalogExpressionSocketFactory(QObject *parent = nullptr)
   : QObject(parent) {setObjectName("DefaultFemaleAnalogExpressionSocketFactory");}
  /*public*/  FemaleSocketManager::SocketType* getFemaleSocketType();

 private:
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();

};

#endif // DEFAULTFEMALEANALOGEXPRESSIONSOCKETFACTORY_H
