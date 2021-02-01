#ifndef OFFSETHIGHCVPROGRAMMERFACADE_H
#define OFFSETHIGHCVPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"

class Logger;
class OffsetHighCvProgrammerFacade : public AbstractProgrammerFacade, public ProgListener
{
 Q_OBJECT
  Q_INTERFACES(ProgListener)
public:
 /*public*/ OffsetHighCvProgrammerFacade(Programmer* prog, QString top, QString addrCV, QString cvFactor, QString modulo, QObject* parent = 0);
 /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
 /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
 /*public*/ bool getCanRead();
 /*public*/ bool getCanRead(QString addr);
 /*public*/ bool getCanWrite();
 /*public*/ bool getCanWrite(QString addr);
 /*public*/ QObject* self() {return (QObject*)this;}

public slots:
 /*public*/ void programmingOpReply(int value, int status);

signals:
 void on_programmingOpReply(int value, int status);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("OffsetHighCvProgrammerFacade");
 int top;
 QString addrCV;
 int cvFactor;
 int modulo;

 // members for handling the programmer interface
 int _val; // remember the value being read/written for confirmative reply
 int _cv; // remember the cv being read/written
 /*private*/ ProgListener* _usingProgrammer;// = null;
 enum ProgState {

     PROGRAMMING, FINISHREAD, FINISHWRITE, NOTPROGRAMMING
 };
 ProgState state;// = ProgState::NOTPROGRAMMING;

protected:
 /*protected*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);

};

#endif // OFFSETHIGHCVPROGRAMMERFACADE_H
