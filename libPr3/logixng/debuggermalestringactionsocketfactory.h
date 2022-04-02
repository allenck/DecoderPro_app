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
  /*public*/ MaleSocket *encapsulateMaleSocket(BaseManager/*<MaleStringActionSocket>*/* manager, MaleSocket *maleSocket)override;

  QObject* self() override {return (QObject*)this;}

};

#endif // DEBUGGERMALESTRINGACTIONSOCKETFACTORY_H
