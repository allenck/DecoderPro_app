#ifndef INDICATIONLOCKINGSIGNALS_H
#define INDICATIONLOCKINGSIGNALS_H

#include <QObject>
#include "nbhsignal.h"
#include "otherdata.h"
#include <QList>

class IndicationLockingSignals : public QObject
{
  Q_OBJECT
 public:
  /*public*/ IndicationLockingSignals(QString userIdentifier, QList<NBHSignal*> _signals, NBHTurnout* nbhTurnout,
          OtherData::SIGNAL_SYSTEM_TYPE signalSystemType, QObject *parent= nullptr);
  /*public*/ void removeAllListeners();
  /*public*/ bool routeClearedAcross();
  /*public*/ bool checkSignalHeads();
  /*public*/ bool checkSignalMasts();
  /*public*/ bool checkMast(SignalMast* mast, Turnout* turnout);


 signals:

 public slots:

 private:
  /*private*/ /*final*/ QList<NBHSignal*> _mListOfSignals;
  /*private*/ /*final*/ Turnout* turnout;
  /*private*/ /*final*/ OtherData::SIGNAL_SYSTEM_TYPE signalType;

};

#endif // INDICATIONLOCKINGSIGNALS_H
