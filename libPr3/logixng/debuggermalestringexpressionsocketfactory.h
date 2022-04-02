#ifndef DEBUGGERMALESTRINGEXPRESSIONSOCKETFACTORY_H
#define DEBUGGERMALESTRINGEXPRESSIONSOCKETFACTORY_H

#include "malestringexpressionsocketfactory.h"
#include "malestringexpressionsocket.h"

class DebuggerMaleStringExpressionSocketFactory : public QObject, public MaleStringExpressionSocketFactory
{

  Q_INTERFACES(MaleStringExpressionSocketFactory)
 public:
  DebuggerMaleStringExpressionSocketFactory(QObject* parent = nullptr) : QObject(parent) {setObjectName("DebuggerMaleStringExpressionSocketFactory");}
  /*public*/ /*MaleStringExpressionSocket*/MaleSocket* encapsulateMaleSocket(BaseManager/*<MaleStringExpressionSocket>*/* manager, /*MaleStringExpressionSocket*/MaleSocket* maleSocket)override;

  QObject* self() override {return (QObject*)this;}

};

#endif // DEBUGGERMALESTRINGEXPRESSIONSOCKETFACTORY_H
