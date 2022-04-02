#ifndef DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H
#define DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H

#include "maledigitalexpressionsocketfactory.h"
#include "maledigitalexpressionsocket.h"

class DebuggerMaleDigitalExpressionSocketFactory : public QObject, public MaleDigitalExpressionSocketFactory
{
 public:
  DebuggerMaleDigitalExpressionSocketFactory() {setObjectName("DebuggerMaleDigitalExpressionSocketFactory");}
  /*public*/ /*MaleDigitalExpressionSocket*/MaleSocket* encapsulateMaleSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager, /*MaleDigitalExpressionSocket*/MaleSocket* maleSocket)override;

  QObject* self() override {return (QObject*)this;}

};

#endif // DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H
