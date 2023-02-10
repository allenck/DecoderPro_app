#ifndef DEBUGGERMALESTRINGEXPRESSIONSOCKETFACTORY_H
#define DEBUGGERMALESTRINGEXPRESSIONSOCKETFACTORY_H

#include "malestringexpressionsocketfactory.h"
#include "malestringexpressionsocket.h"
#include "abstractmalesocket.h"

class DebuggerMaleStringExpressionSocketFactory : public QObject, public MaleStringExpressionSocketFactory
{

  Q_INTERFACES(MaleStringExpressionSocketFactory)
 public:
  DebuggerMaleStringExpressionSocketFactory(QObject* parent = nullptr) : QObject(parent) {setObjectName("DebuggerMaleStringExpressionSocketFactory");}
  /*public*/ /*MaleStringExpressionSocket*/AbstractMaleSocket* encapsulateMaleSocket(BaseManager/*<MaleStringExpressionSocket>*/* manager, /*MaleStringExpressionSocket*/AbstractMaleSocket *maleSocket)override;

  QObject* self() override {return (QObject*)this;}

};

#endif // DEBUGGERMALESTRINGEXPRESSIONSOCKETFACTORY_H
