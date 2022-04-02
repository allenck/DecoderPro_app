#ifndef DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H
#define DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H

#include "maleanalogactionsocketfactory.h"

class DebuggerMaleAnalogActionSocketFactory : public QObject, public MaleAnalogActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleAnalogActionSocketFactory)
 public:
  DebuggerMaleAnalogActionSocketFactory(QObject* parent = nullptr) : QObject(parent){
   setObjectName("DebuggerMaleAnalogActionSocketFactory");
  }
  /*public*/ MaleSocket *encapsulateMaleSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, MaleSocket *maleSocket)override;

  QObject* self() override {return (QObject*)this;}
};

#endif // DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H
