#ifndef DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H
#define DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"
#include "femalesocketmanager.h"
#include "stringexpressionmanager.h"
#include "instancemanager.h"
#include "defaultfemalestringexpressionsocket.h"

class DefaultFemaleStringExpressionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketFactory)
 public:
  explicit DefaultFemaleStringExpressionSocketFactory(QObject *parent = nullptr) : QObject(parent) {}
  /*public*/  FemaleSocketManager::SocketType* getFemaleSocketType();

 signals:

 private:
  /*private*/ static /*final*/ FemaleSocketManager::SocketType* _femaleSocketType;// = new SocketType();
  /*private*/ /*static*/ class SocketType : FemaleSocketManager::SocketType {

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
          return (StringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");
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
};

#endif // DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H
