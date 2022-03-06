#ifndef DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H
#define DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H

#include <QObject>
#include "maledigitalactionsocketfactory.h"
#include "malesocket.h"

class DebuggerMaleDigitalActionSocketFactory : public QObject, public MaleDigitalActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalActionSocketFactory)
 public:
  explicit DebuggerMaleDigitalActionSocketFactory(QObject *parent = nullptr)
   : QObject(parent) {
   setObjectName("DebuggerMaleDigitalActionSocketFactory");
  }
  /*public*/ NamedBean* encapsulateMaleSocket(BaseManager/*<MaleDigitalActionSocket>*/* manager, NamedBean* maleSocket)override;

  QObject* self() override {return (QObject*)this;}

 signals:

};

#endif // DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H
