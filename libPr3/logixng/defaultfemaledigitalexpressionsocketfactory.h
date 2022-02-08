#ifndef DEFAULTFEMALEDIGITALEXPRESSIONSOCKETFACTORY_H
#define DEFAULTFEMALEDIGITALEXPRESSIONSOCKETFACTORY_H

#include "femalesocketfactory.h"
#include "basemanager.h"
#include "instancemanager.h"
#include "digitalexpressionmanager.h"
#include "femalesocketmanager.h"

class DefaultFemaleDigitalExpressionSocketFactory : public FemaleSocketFactory
{
  Q_OBJECT
  /*private*/ /*static*/ class SocketType : public FemaleSocketManager::SocketType {

      //@Override
      /*public*/  QString getName() {
          return "DefaultFemaleDigitalExpressionSocket";
      }

      //@Override
      /*public*/  QString getDescr() {
          return tr("Digital expression socket");
      }

      //@Override
      /*public*/  BaseManager/*<? extends MaleSocket>*/* getManager() {
          return (DigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
      }

      //@Override
      /*public*/  FemaleSocket createSocket(Base parent, FemaleSocketListener listener, QString name) {
          return new DefaultFemaleDigitalExpressionSocket(parent, listener, name);
      }

      //@Override
      /*public*/  QString toString() {
          return getDescr();
      }
  };
 public:
  DefaultFemaleDigitalExpressionSocketFactory();

 private:
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();

};

#endif // DEFAULTFEMALEDIGITALEXPRESSIONSOCKETFACTORY_H
