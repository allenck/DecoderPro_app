#ifndef TOPOLOGYINFO_H
#define TOPOLOGYINFO_H

#include <QObject>
#include <QList>

class SignalMast;
class SignalMastLogic;
class Block;
class Turnout;
class TurnoutInfo;
class Sensor;
class CTCSerialData;
class TopologyInfo : public QObject
{
  Q_OBJECT
 public:
  explicit TopologyInfo(QObject *parent = nullptr);
  /*public*/ TopologyInfo(CTCSerialData* CTCSerialData, QString destinationSignalMast, QString normal, QString reverse,QObject *parent = nullptr);
  /*public*/ QString getDestinationSignalMast();
  /*public*/ bool nonEmpty();
  /*public*/ QString getOSSectionText(int index);
  /*public*/ QString getNormalReversed(int index);
  /*public*/ QString getSensorDisplayName(int index);
  /*public*/ QString getUniqueID(int index);
  /*public*/ void addBlocks(QList<Block*> blocks);
  /*public*/ void addTurnouts(SignalMastLogic* signalMastLogic, SignalMast* signalMast);

 signals:

 public slots:

 private:
  /*private*/ /*final*/ CTCSerialData* _mCTCSerialData;    // Needed to look up a turnout in order to return an O.S. section text.
  /*private*/ /*final*/ QString _mDestinationSignalMast;
  /*private*/ /*final*/ QString _mNormal;                  // Bundle.getMessage("TLE_Normal")
  /*private*/ /*final*/ QString _mReverse;                 // Bundle.getMessage("TLE_Reverse")

  /*private*/ /*final*/ QList<Sensor*> _mSensors = QList<Sensor*>();
//  /*private*/ /*final*/ LinkedList<String> _mSensorNamesDebug = new LinkedList<>();    //Debugging
  /*private*/ /*final*/ QList<TurnoutInfo*> _mTurnoutInfos = QList<TurnoutInfo*>();
//  /*private*/ /*final*/ LinkedList<String> _mOSSectionInfosDebug = new LinkedList<>(); //Debugging
  /*private*/ /*final*/ QList<Turnout*> _mTurnouts = QList<Turnout*>();  // ONLY used for duplicate check (lazy).

};

#endif // TOPOLOGYINFO_H
