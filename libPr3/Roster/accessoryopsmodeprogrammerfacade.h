#ifndef ACCESSORYOPSMODEPROGRAMMERFACADE_H
#define ACCESSORYOPSMODEPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"
#include "logger.h"

class AddressedProgrammer;
class AccessoryOpsModeProgrammerFacade : public AbstractProgrammerFacade, public ProgListener
{
  Q_OBJECT
  Q_INTERFACES(ProgListener)
public:
    //explicit AccessoryOpsModeProgrammerFacade(QObject *parent = 0);
 /*public*/ AccessoryOpsModeProgrammerFacade(Programmer* prog, /*@Nonnull */QString addrType, int delay, AddressedProgrammer* baseProg, QObject *parent= 0);
    /*public*/ QList<QString> getSupportedModes();
    /*public*/ void setMode(ProgrammingMode* p);
    /*public*/ bool getCanRead();
    /*public*/ bool getCanRead(QString addr);
    /*public*/ bool getCanWrite();
    /*public*/ bool getCanWrite(QString addr);
    /*synchronized*/ /*public*/ void writeCV(QString cv, int val, ProgListener* p) throw (ProgrammerException);
    /*synchronized*/ /*public*/ void confirmCV(QString cv, int val, ProgListener* p) throw (ProgrammerException);
    /*synchronized*/ /*public*/ void readCV(QString cv, ProgListener* p) throw (ProgrammerException);
 /*public*/ QObject* self() {return (QObject*)this;}


signals:

public slots:
    /*public*/ void programmingOpReply(int value, int status);
private:
    // ops accessory mode can't read locally
    ProgrammingMode* mode;
    AddressedProgrammer* aprog;
    // members for handling the programmer interface
    int _val;	// remember the value being read/written for confirmative reply
    QString _cv;	// remember the cv number being read/written
    QString _addrType;               // remember the address type: ("decoder" or null) or ("accessory" or "output")
    int _delay;                     // remember the programming delay, in milliseconds
    AddressedProgrammer* _baseProg;   // remember the underlying programmer
    /*private*/ ProgListener* _usingProgrammer;// = null;
    enum ProgState { PROGRAMMING, NOTPROGRAMMING };
    ProgState state;// = ProgState.NOTPROGRAMMING;
    Logger* log;
protected:
    /*protected*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);
 friend class DelayWorker;
};

class DelayWorker : public QObject
{
 Q_OBJECT
 AccessoryOpsModeProgrammerFacade* facade;
 QString cv;
 int val;
public:
 DelayWorker(QString cv, int val, AccessoryOpsModeProgrammerFacade* facade);
public slots:
 void process();
signals:
 void finished();
};
#endif // ACCESSORYOPSMODEPROGRAMMERFACADE_H
