#ifndef LOCOSTATSFUNC_H
#define LOCOSTATSFUNC_H

#include <QObject>
#include "loconetlistener.h"

class LocoNetInterfaceStatsListener;
class LocoNetSystemConnectionMemo;
class LocoStatsFunc : public QObject, public LocoNetListener
{
 Q_OBJECT
 Q_INTERFACES(LocoNetListener)
public:
 explicit LocoStatsFunc(LocoNetSystemConnectionMemo* memo, QObject *parent = nullptr);
 /*public*/ void sendLocoNetInterfaceStatusQueryMessage();
 /*public*/ QObject *getInterfaceStatus();
 /*public*/ void dispose();

signals:

public slots:
 /*public*/ void message(LocoNetMessage* msg);
 /*public*/ /*synchronized*/ void addLocoNetInterfaceStatsListener(/*@Nonnull*/ LocoNetInterfaceStatsListener* l);
 /*public*/ /*synchronized*/ void removeLocoNetInterfaceStatsListener(/*@Nonnull*/ LocoNetInterfaceStatsListener* l);

private:
 /*private*/ LocoNetSystemConnectionMemo* memo;
 static Logger* log;
 /*private*/ bool updatePending;
 /*private*/ bool need2ndUpdate;
 /*private*/ QObject* ifaceStatus;
 /*private*/ void sendQuery();
 /*private*/ void updateListeners();

protected:
 /*protected*/ QVector<LocoNetInterfaceStatsListener*> listeners;// = new Vector<LocoNetInterfaceStatsListener>();

};

#endif // LOCOSTATSFUNC_H
