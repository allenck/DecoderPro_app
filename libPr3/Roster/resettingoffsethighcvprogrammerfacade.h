#ifndef RESETTINGOFFSETHIGHCVPROGRAMMERFACADE_H
#define RESETTINGOFFSETHIGHCVPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"

class Logger;
class ResettingOffsetHighCvProgrammerFacade : public AbstractProgrammerFacade
{
public:
 /*public*/ ResettingOffsetHighCvProgrammerFacade(Programmer* prog, QString top, QString addrCV, QString cvFactor, QString modulo, QString indicator, QObject* parent = nullptr);
 /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
 /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
 /*public*/ bool getCanRead() ;
 /*public*/ bool getCanRead(QString addr);
 /*public*/ bool getCanWrite();
 /*public*/ bool getCanWrite(QString addr);

public slots:
 /*public*/ void programmingOpReply(int value, int status);

signals:
 void on_programmingOpReply(int value, int status);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("ResettingOffsetHighCvProgrammerFacade");
 int top;
 QString addrCV;
 int cvFactor;
 int modulo;
 int indicator;

 // members for handling the programmer interface
 int _val; // remember the value being read/written for confirmative reply
 int _cv; // remember the cv being read/written
 /*private*/ProgListener* _usingProgrammer;// = null;
 enum ProgState {

     PROGRAMMING, FINISHREAD, FINISHWRITE, RESET, NOTPROGRAMMING
 };
 ProgState state;// = ProgState::NOTPROGRAMMING;

protected:
 /*protected*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);

};

#endif // RESETTINGOFFSETHIGHCVPROGRAMMERFACADE_H
