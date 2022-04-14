#ifndef DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H
#define DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"
#include "femalesocketmanager.h"
#include "defaultstringexpressionmanager.h"
#include "instancemanager.h"
#include "defaultfemalestringexpressionsocket.h"

class DefaultFemaleStringExpressionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketFactory)
 public:
  /*private*/ /*static*/ class SocketType : public FemaleSocketManager::SocketType {
   public:
      //@Override
      /*public*/  QString getName() {
          return "DefaultFemaleStringExpressionSocket";
      }

      //@Override
      /*public*/  QString getDescr() {
          return tr("String expression socket");
      }

      //@Override
      /*public*/  BaseManager/*<? extends MaleSocket>*/* getManager() {
          return (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");
      }

      //@Override
      /*public*/  FemaleSocket* createSocket(Base* parent, FemaleSocketListener* listener, QString name) {
          return new DefaultFemaleStringExpressionSocket(parent, listener, name);
      }

      //@Override
      /*public*/  QString toString() {
          return getDescr();
      }
  };
  explicit DefaultFemaleStringExpressionSocketFactory(QObject *parent = nullptr) : QObject(parent) {}
  /*public*/  FemaleSocketManager::SocketType* getFemaleSocketType();

 private:
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();
 public:

};

#endif // DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H
