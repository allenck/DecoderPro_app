#ifndef DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H
#define DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H

#include <QObject>
#include "maledigitalactionsocketfactory.h"
#include "malesocket.h"
#include "abstractmalesocket.h"


class DebuggerMaleDigitalActionSocketFactory : public QObject, public MaleDigitalActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalActionSocketFactory)
 public:
  explicit DebuggerMaleDigitalActionSocketFactory(QObject *parent = nullptr)
   : QObject(parent) {
   setObjectName("DebuggerMaleDigitalActionSocketFactory");
  }
  /*public*/ AbstractMaleSocket *encapsulateMaleSocket(BaseManager/*<MaleDigitalActionSocket>*/* manager, AbstractMaleSocket *maleSocket)override;

  QObject* self() override {return (QObject*)this;}

 signals:

};

#endif // DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H
