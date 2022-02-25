#ifndef DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H
#define DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H

#include "maleanalogactionsocketfactory.h"

class DebuggerMaleAnalogActionSocketFactory : public QObject, public MaleAnalogActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleAnalogActionSocketFactory)
 public:
  DebuggerMaleAnalogActionSocketFactory(QObject* parent = nullptr){}
  /*public*/ MaleAnalogActionSocket* encapsulateMaleSocket(BaseManager/*<MaleAnalogActionSocket>*/* manager, MaleAnalogActionSocket* maleSocket);

};

#endif // DEBUGGERMALEANALOGACTIONSOCKETFACTORY_H
