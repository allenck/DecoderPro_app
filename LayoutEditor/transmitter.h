#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <QObject>
#include "measurement.h"
#include "dccthrottle.h"

namespace RPS
{
class Transmitter : public QObject
{
 Q_OBJECT
public:
 Transmitter(QString id, bool polled, int address, bool longAddress, QObject*parent = nullptr);
 /*public*/ QString getID();
 /*public*/ void setID(QString id);
 /*public*/ QString getRosterName();
 /*public*/ void setRosterName(QString rosterName);
 /*public*/ bool isLongAddress();
 /*public*/ void setLongAddress(bool longAddress);
 /*public*/ int getAddress();
 /*public*/ void setAddress(int address);
 /*public*/ bool isPolled();
 /*public*/ void setPolled(bool polled);
 /*public*/ void setLastMeasurement(Measurement* last);
 /*public*/ Measurement* getLastMeasurement();

signals:

public slots:
 /*public*/ void notifyThrottleFound(DccThrottle* t);
 /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);

  private:
  bool polled;
  QString id;
  int address;
  bool longAddress;
  QString rosterName;
  Measurement* lastMeasurement;// = null;
  // stuff to do F2 poll
  DccThrottle* throttle;
  bool needReqThrottle;// = true;
  DccThrottle* getThrottle();
  bool checkInit();

};
}
#endif // TRANSMITTER_H
