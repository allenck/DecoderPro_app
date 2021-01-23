#ifndef LNCVDEVICE_H
#define LNCVDEVICE_H

#include <QObject>
#include "decoderfile.h"
#include "rosterentry.h"

class LncvDevice : public QObject
{
  Q_OBJECT
 public:
  /*public*/ LncvDevice(int productID, int address, int lastCv, int lastVal, QString deviceName, QString rosterName, int swVersion);
  /*public*/ int getProductID();
  /*public*/ int getDestAddr();
  /*public*/ QString getDeviceName();
  /*public*/ QString getRosterName();
  /*public*/ int getSwVersion();
  /*public*/ void setDestAddr(int destAddr);
  /*public*/ void setDevName(QString s);
  /*public*/ void setRosterName(QString s);
  /*public*/ void setSwVersion(int version);
  /*public*/ DecoderFile* getDecoderFile() ;
  /*public*/ void setDecoderFile(DecoderFile* f);
  /*public*/ RosterEntry* getRosterEntry();
  /*public*/ void setRosterEntry(RosterEntry* e);
  /*public*/ int getCvNum();
  /*public*/ void setCvNum(int num);
  /*public*/ int getCvValue();
  /*public*/ void setCvValue(int val);

 signals:

 public slots:

 private:
  /*private*/ int deviceAddress; // Module address in reply, value of -1 is ignored, LNCV default address : 1
  /*private*/ /*final*/ int artNum; // used as LNCV ProductID, must be int to pass as part of CV "art.cv"
  /*private*/ QString deviceName;
  /*private*/ QString rosterEntryName;
  /*private*/ int swVersion;
  /*private*/ RosterEntry* rosterEntry;
  /*private*/ DecoderFile* decoderFile;
  /*private*/ int cvNum;
  /*private*/ int cvValue;

};

#endif // LNCVDEVICE_H
