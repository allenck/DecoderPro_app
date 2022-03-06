#ifndef DEBUGGERMALESTRINGACTIONSOCKETFACTORY_H
#define DEBUGGERMALESTRINGACTIONSOCKETFACTORY_H

#include "malestringactionsocketfactory.h"
#include <QObject>
class MaleStringActionSocket;
class DebuggerMaleStringActionSocketFactory : public QObject, public MaleStringActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleStringActionSocketFactory)
 public:
  DebuggerMaleStringActionSocketFactory(QObject* parent = nullptr) : QObject(parent) {setObjectName("DebuggerMaleStringActionSocketFactory");}
  /*public*/ MaleStringActionSocket* encapsulateMaleSocket(BaseManager/*<MaleStringActionSocket>*/* manager, MaleStringActionSocket* maleSocket);

  QObject* self() override {return (QObject*)this;}

};

#endif // DEBUGGERMALESTRINGACTIONSOCKETFACTORY_H
