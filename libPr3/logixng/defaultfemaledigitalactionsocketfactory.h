#ifndef DEFAULTFEMALEDIGITALACTIONSOCKETFACTORY_H
#define DEFAULTFEMALEDIGITALACTIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"
#include "digitalactionmanager.h"
#include "instancemanager.h"
#include "defaultfemaledigitalactionsocket.h"

class DefaultFemaleDigitalActionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
  /*private*/ /*static*/ class SocketType : public FemaleSocketManager::SocketType {

      //@Override
      /*public*/  QString getName()override {
          return "DefaultFemaleDigitalActionSocket";
      }

      //@Override
      /*public*/  QString getDescr()override {
          return tr("Digital action socket");
      }

      //@Override
      /*public*/  BaseManager/*<? extends MaleSocket>*/* getManager() {
          return ((DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
      }

      //@Override
      /*public*/  FemaleSocket* createSocket(Base* parent, FemaleSocketListener* listener, QString name) {
          return new DefaultFemaleDigitalActionSocket(parent, listener, name);
      }

      //@Override
      /*public*/  QString toString() {
          return getDescr();
      }
  };
   public:
  explicit DefaultFemaleDigitalActionSocketFactory(QObject *parent = nullptr);

 signals:
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();

};

#endif // DEFAULTFEMALEDIGITALACTIONSOCKETFACTORY_H
