#ifndef ACCESSORYOPSMODEPROGRAMMERFACADE_H
#define ACCESSORYOPSMODEPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"
#include "logger.h"

class AddressedProgrammer;
class AccessoryOpsModeProgrammerFacade : public AbstractProgrammerFacade
{
    Q_OBJECT
public:
    //explicit AccessoryOpsModeProgrammerFacade(QObject *parent = 0);
    /*public*/ AccessoryOpsModeProgrammerFacade(AddressedProgrammer* prog, QObject *parent = 0 );
    /*public*/ QList<ProgrammingMode*> getSupportedModes();
    /*public*/ void setMode(ProgrammingMode* p);
    /*public*/ bool getCanRead();
    /*public*/ bool getCanRead(QString addr);
    /*public*/ bool getCanWrite();
    /*public*/ bool getCanWrite(QString addr);
    /*synchronized*/ /*public*/ void writeCV(QString cv, int val, ProgListener* p) throw (ProgrammerException);
    /*synchronized*/ /*public*/ void confirmCV(QString cv, int val, ProgListener* p) throw (ProgrammerException);
    /*synchronized*/ /*public*/ void readCV(QString cv, ProgListener* p) throw (ProgrammerException);


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
    /*private*/ ProgListener* _usingProgrammer;// = null;
    enum ProgState { PROGRAMMING, NOTPROGRAMMING };
    ProgState state;// = ProgState.NOTPROGRAMMING;
    Logger* log;
protected:
    /*protected*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);

};

#endif // ACCESSORYOPSMODEPROGRAMMERFACADE_H
