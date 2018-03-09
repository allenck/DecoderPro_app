#ifndef LNOPSMODEPROGRAMMER_H
#define LNOPSMODEPROGRAMMER_H
#include "addressedprogrammer.h"

class LocoNetMessage;
class LocoNetSystemConnectionMemo;
class Logger;
class ProgrammingMode;
class SlotManager;
class LnOpsModeProgrammer : public AddressedProgrammer
{
    Q_OBJECT
public:
    //explicit LnOpsModeProgrammer(QObject *parent = 0);
    /*public*/ LnOpsModeProgrammer(SlotManager* pSlotMgr, LocoNetSystemConnectionMemo* memo,int pAddress, bool pLongAddr, QObject *parent = 0);
    /*public*/ void readCV(int CV, ProgListener* p) throw (ProgrammerException);
    /*public*/ void writeCV(int CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ void confirmCV(int CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
    /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
    /*public*/ /*final*/ void setMode(ProgrammingMode* m);
    /*public*/ /*final*/ ProgrammingMode* getMode();
    /*public*/ QList<ProgrammingMode*> getSupportedModes();
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

protected:
    // handle mode
    /*protected*/ ProgrammingMode* mode;// = DefaultProgrammerManager.OPSBYTEMODE;
    /*protected*/ void notifyPropertyChange(QString key, QVariant oldValue, QVariant value);
 Logger* log;
 LocoNetSystemConnectionMemo* memo;
 int decodeCvNum(QString CV);
 void loadSV2MessageFormat(LocoNetMessage* m, int mAddress, int cvAddr, int data);
 friend class LnProgrammerManager;
};

#endif // LNOPSMODEPROGRAMMER_H
