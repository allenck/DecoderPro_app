#ifndef DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H
#define DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H

#include "maledigitalexpressionsocketfactory.h"
#include "maledigitalexpressionsocket.h"
#include "abstractmalesocket.h"


class DebuggerMaleDigitalExpressionSocketFactory : public QObject, public MaleDigitalExpressionSocketFactory
{
 public:
  DebuggerMaleDigitalExpressionSocketFactory() {setObjectName("DebuggerMaleDigitalExpressionSocketFactory");}
  /*public*/ /*MaleDigitalExpressionSocket*/AbstractMaleSocket *encapsulateMaleSocket(BaseManager/*<MaleDigitalExpressionSocket>*/* manager, /*MaleDigitalExpressionSocket*/AbstractMaleSocket *maleSocket)override;

  QObject* self() override {return (QObject*)this;}

};

#endif // DEBUGGERMALEDIGITALEXPRESSIONSOCKETFACTORY_H
