#ifndef DEBUGGERMALESTRINGACTIONSOCKETFACTORY_H
#define DEBUGGERMALESTRINGACTIONSOCKETFACTORY_H

#include "malestringactionsocketfactory.h"
#include <QObject>
#include "abstractmalesocket.h"

class MaleStringActionSocket;
class DebuggerMaleStringActionSocketFactory : public QObject, public MaleStringActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleStringActionSocketFactory)
 public:
  DebuggerMaleStringActionSocketFactory(QObject* parent = nullptr) : QObject(parent) {setObjectName("DebuggerMaleStringActionSocketFactory");}
  /*public*/ AbstractMaleSocket *encapsulateMaleSocket(BaseManager/*<MaleStringActionSocket>*/* manager, AbstractMaleSocket *maleSocket)override;

  QObject* self() override {return (QObject*)this;}

};

#endif // DEBUGGERMALESTRINGACTIONSOCKETFACTORY_H
