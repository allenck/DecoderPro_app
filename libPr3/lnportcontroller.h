#ifndef LNPORTCONTROLLER_H
#define LNPORTCONTROLLER_H

#include <QObject>
#include <QStringList>
#include "loconetsystemconnectionmemo.h"
#include "abstractserialportcontroller.h"
#include "LocoIO/lncommandstationtype.h"
#include "QtSerialPort/QSerialPort"

class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT LnPortController : public  AbstractSerialPortController
{
 Q_OBJECT
public:
  LnPortController(LocoNetSystemConnectionMemo* connectionMemo, QObject *parent = 0);
    ~LnPortController() {}
 // returns the InputStream from the port
  /*public abstract*/ QDataStream* getInputStream(){return NULL;}

 // returns the outputStream to the port
  /*public abstract*/  QDataStream* getOutputStream(){return NULL;}
  /*public abstract*/ virtual QSerialPort* getSerialPort() {return NULL;}
 /**
  * Check that this object is ready to operate. This is a question
  * of configuration, not transient hardware status.
  */
  bool status();
 /**
  * Can the port accept additional characters?  This might
  * go false for short intervals, but it might also stick
  * off if something goes wrong.
  *<P>
  * Provide a default implementation for the MS100, etc,
  * in which this is _always_ true, as we rely on the
  * queueing in the port itself.
  */
  bool okToSend();
  /*public*/ SystemConnectionMemo* getSystemConnectionMemo();

 /**
  * Set config info from the command station type name.
  */
  /*public*/ void setCommandStationType(QString name);
 void setCommandStationType(LnCommandStationType* value);
 /*public*/ void setTurnoutHandling(QString value) ;
 /*public*/  void setDisabled(bool disabled) ;
 /*public*/ void setTranspondingAvailable(QString value);

signals:
    
public slots:
private:
 Logger* log;
protected:
 LocoNetSystemConnectionMemo* adaptermemo;

 bool mCanRead;
 bool mProgPowersOff;
 QString commandStationName;
 bool mTurnoutNoRetry;
 bool mTurnoutExtraSpace;

 QStringList commandStationNames;
 LnCommandStationType* commandStationType;// = NULL;
 // There are also "PR3 standalone programmer" and "Stand-alone LocoNet"
 // in pr3/PR3Adapter
 QList<LnCommandStationType*> commandStationTypes;

protected:
 /*protected*/ bool mTranspondingAvailable = false;
};

#endif // LNPORTCONTROLLER_H
