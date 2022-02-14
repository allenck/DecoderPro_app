#ifndef DEFAULTFEMALEANALOGEXPRESSIONSOCKETFACTORY_H
#define DEFAULTFEMALEANALOGEXPRESSIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"
#include "analogexpressionmanager.h"
#include "instancemanager.h"
#include "defaultfemaleanalogexpressionsocket.h"

class DefaultFemaleAnalogExpressionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
 public:
  explicit DefaultFemaleAnalogExpressionSocketFactory(QObject *parent = nullptr);

 signals:

 private:
  /*private*/ /*static*/ class SocketType : FemaleSocketManager::SocketType {

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
          return (AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
      }

      //@Override
      /*public*/  FemaleSocket* createSocket(Base* parent, FemaleSocketListener* listener, QString name) {
          return (FemaleSocket*)(new DefaultFemaleAnalogExpressionSocket(parent, listener, name))->self();
      }

      //@Override
      /*public*/  QString toString() {
          return getDescr();
      }
  };
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();

};

#endif // DEFAULTFEMALEANALOGEXPRESSIONSOCKETFACTORY_H
