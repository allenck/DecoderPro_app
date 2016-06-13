#ifndef ADDRESSEDHIGHCVPROGRAMMERFACADE_H
#define ADDRESSEDHIGHCVPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"
#include "libPr3_global.h"

enum ProgState {

    PROGRAMMING, WRITELOWREAD, WRITELOWWRITE, FINISHREAD, FINISHWRITE, NOTPROGRAMMING
};

class Logger;
class LIBPR3_GLOBAL_H AddressedHighCvProgrammerFacade : public AbstractProgrammerFacade
{
 Q_OBJECT
public:
 //explicit AddressedHighCvProgrammerFacade(QObject *parent = 0);
 /*public*/ AddressedHighCvProgrammerFacade(Programmer* prog, QString top, QString addrCVhigh, QString addrCVlow, QString valueCV, QString modulo, QObject *parent = 0);
 /*public*/ void writeCV(int CV, int val, ProgListener* p); //throws ProgrammerException
 /*public*/ void writeCV(QString CV, int val, ProgListener* p); //throws ProgrammerException
 /*public*/ void confirmCV(int CV, int val, ProgListener* p); //throws ProgrammerException
 /*public*/ void confirmCV(QString CV, int val, ProgListener* p); //throws ProgrammerException
 /*public*/ void readCV(int CV, ProgListener* p); //throws ProgrammerException
 /*public*/ void readCV(QString CV, ProgListener* p); //throws ProgrammerException
 /*public*/ void programmingOpReply(int value, int status);
 // Access to full address space provided by this->
 /*public*/ bool getCanRead();
 /*public*/ bool getCanRead(QString addr);
 /*public*/ bool getCanWrite();
 /*public*/ bool getCanWrite(QString addr);

signals:

public slots:

private:
 int top;
 int addrCVhigh;
 int addrCVlow;
 int valueCV;
 int modulo;

 // members for handling the programmer interface
 int _val;	// remember the value being read/written for confirmative reply
 int _cv;	// remember the cv being read/written
 ProgState state;// = ProgState::NOTPROGRAMMING;
 /*private*/ ProgListener* _usingProgrammer;// = null;
 Logger* log;

protected:
 /*protected*/ void useProgrammer(ProgListener* p); //throws ProgrammerException

};

#endif // ADDRESSEDHIGHCVPROGRAMMERFACADE_H
