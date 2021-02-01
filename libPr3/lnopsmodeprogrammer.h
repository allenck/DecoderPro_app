#ifndef LNOPSMODEPROGRAMMER_H
#define LNOPSMODEPROGRAMMER_H
#include "addressedprogrammer.h"
#include <QTimer>

class LocoNetMessage;
class LocoNetSystemConnectionMemo;
class Logger;
class ProgrammingMode;
class SlotManager;
class LnOpsModeProgrammer : public QObject, public AddressedProgrammer
{
    Q_OBJECT
 Q_INTERFACES(AddressedProgrammer)
public:
 enum WriteConfirmMode {
   /**
    * No verification available, writes are blind
    */
   NotVerified,
   /**
    * Programmer signals error if there's no reply from the device
    */
   DecoderReply,
   /**
    * Programmer does a read after write to verify
    */
   ReadAfterWrite
 };
   //explicit LnOpsModeProgrammer(QObject *parent = 0);
   /*public*/ LnOpsModeProgrammer(LocoNetSystemConnectionMemo* memo,
                                 int pAddress, bool pLongAddr, QObject *parent = 0);

    /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
    /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ /*final*/ void setMode(ProgrammingMode* m);
    /*public*/ /*final*/ ProgrammingMode* getMode();
    /*public*/ QList<QString> getSupportedModes();
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
    /*public*/ bool getCanRead();
    /*public*/ bool getCanRead(QString addr);
    /*public*/ bool getCanWrite();
    /*public*/ bool getCanWrite(QString addr);
    /*public*/ QString decodeErrorCode(int i);
    /*public*/ bool getLongAddress();
    /*public*/ int getAddressNumber() ;
    /*public*/ QString getAddress();
    /*public*/ Programmer::WriteConfirmMode getWriteConfirmMode(QString addr);
    /*default*/ /*public*/ void notifyProgListenerEnd(ProgListener* p, int value, int status);
    /*public*/ QObject* self() {return (QObject*)this;}

signals:
    void propertyChange(PropertyChangeEvent*);

public slots:
    /*public*/ void message(LocoNetMessage* m);

private:
    SlotManager* mSlotMgr;
    int mAddress;
    bool mLongAddr;
    ProgListener* p;
    bool doingWrite;
    /*private*/ QTimer* bdOpSwAccessTimer = nullptr;
    void initiializeBdOpsAccessTimer();

 static Logger* log;
 LocoNetSystemConnectionMemo* memo;
 int decodeCvNum(QString CV);
 void loadSV2MessageFormat(LocoNetMessage* m, int mAddress, int cvAddr, int data);

protected:
    // handle mode
    /*protected*/ ProgrammingMode* mode;// = DefaultProgrammerManager.OPSBYTEMODE;
    /*protected*/ void notifyPropertyChange(QString key, QVariant oldValue, QVariant value);

 friend class LnProgrammerManager;
 friend class OpSwAccessTimer;
 friend class LnOpsModeProgrammerTest;
};

class OpSwAccessTimer : public QTimer
{
 Q_OBJECT
 LnOpsModeProgrammer* prg;
public:
 OpSwAccessTimer(LnOpsModeProgrammer* prg)
 {
  this->prg = prg;
  connect(this, SIGNAL(timeout()), this, SLOT(timeout()));
 }
public slots:
 void timeout()
 {
  ProgListener* temp = prg->p;
  prg->p = nullptr;
  prg->notifyProgListenerEnd(temp, 0, ProgListener::FailedTimeout);
 }
};
#endif // LNOPSMODEPROGRAMMER_H
