#ifndef DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H
#define DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H

#include <QObject>
#include "maledigitalactionsocketfactory.h"

class DebuggerMaleDigitalActionSocketFactory : public QObject, public MaleDigitalActionSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalActionSocketFactory)
 public:
  explicit DebuggerMaleDigitalActionSocketFactory(QObject *parent = nullptr) :QObject(parent) {}
  /*public*/ MaleDigitalActionSocket* encapsulateMaleSocket(BaseManager/*<MaleDigitalActionSocket>*/* manager, MaleDigitalActionSocket* maleSocket);

 signals:

};

#endif // DEBUGGERMALEDIGITALACTIONSOCKETFACTORY_H
