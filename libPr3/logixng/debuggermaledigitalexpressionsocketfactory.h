#ifndef DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H
#define DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H

#include "maledigitalexpressionsocketfactory.h"
#include "maledigitalexpressionsocket.h"

class DebuggerMaleDigitalExpressionSocketFactory : public QObject, public MaleDigitalExpressionSocketFactory
{
 public:
  DebuggerMaleDigitalExpressionSocketFactory() {setObjectName("DebuggerMaleDigitalExpressionSocketFactory");}
  /*public*/ MaleDigitalExpressionSocket* encapsulateMaleSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager, MaleDigitalExpressionSocket* maleSocket);

  QObject* self() override {return (QObject*)this;}

};

#endif // DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H
