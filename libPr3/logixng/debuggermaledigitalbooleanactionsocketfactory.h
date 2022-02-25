#ifndef DEBUGGERMALEDIGITALBOOLEANACTIONSOCKETFACTORY_H
#define DEBUGGERMALEDIGITALBOOLEANACTIONSOCKETFACTORY_H

#include "maledigitalbooleanactionsocketfactory.h"
#include <QObject>
#include "maledigitalbooleanactionsocket.h"

class DebuggerMaleDigitalBooleanActionSocketFactory : public QObject, public MaleDigitalBooleanActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalBooleanActionSocketFactory)
 public:
  DebuggerMaleDigitalBooleanActionSocketFactory(QObject* parent = nullptr) {}
  /*public*/ MaleDigitalBooleanActionSocket* encapsulateMaleSocket(BaseManager/*<MaleDigitalBooleanActionSocket>*/* manager, MaleDigitalBooleanActionSocket* maleSocket);

};

#endif // DEBUGGERMALEDIGITALBOOLEANACTIONSOCKETFACTORY_H
