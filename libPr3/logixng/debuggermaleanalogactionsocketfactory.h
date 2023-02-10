#ifndef DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H
#define DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H

#include "maleanalogactionsocketfactory.h"
#include "abstractmalesocket.h"

class DebuggerMaleAnalogActionSocketFactory : public QObject, public MaleAnalogActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleAnalogActionSocketFactory)
 public:
  DebuggerMaleAnalogActionSocketFactory(QObject* parent = nullptr) : QObject(parent){
   setObjectName("DebuggerMaleAnalogActionSocketFactory");
  }
  /*public*/ AbstractMaleSocket *encapsulateMaleSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, AbstractMaleSocket *maleSocket)override;

  QObject* self() override {return (QObject*)this;}
};

#endif // DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H
