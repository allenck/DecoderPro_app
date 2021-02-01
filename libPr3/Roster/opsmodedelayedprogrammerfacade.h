#ifndef OPSMODEDELAYEDPROGRAMMERFACADE_H
#define OPSMODEDELAYEDPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"

class Logger;
class OpsModeDelayedProgrammerFacade : public AbstractProgrammerFacade, public ProgListener
{
 Q_OBJECT
  Q_INTERFACES(ProgListener)
public:
 /*public*/ OpsModeDelayedProgrammerFacade(Programmer* prog, int writeDelay, QObject* parent = 0);
 /*public*/ /*synchronized*/ void writeCV(QString cv, int val, ProgListener* p) throw (ProgrammerException);
 /*public*/ /*synchronized*/ void readCV(QString cv, ProgListener* p) throw (ProgrammerException) ;
 /*public*/ /*synchronized*/ void confirmCV(QString cv, int val, ProgListener* p) throw (ProgrammerException);
 /*public*/ QObject* self() {return (QObject*)this;}

public slots:
 /*public*/ /*synchronized*/ void programmingOpReply(int value, int status);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("OpsModeDelayedProgrammerFacade");
 // members for handling the programmer interface
 int _val;           // remember the value being read/written for confirmative reply
 QString _cv;         // remember the cv number being read/written
 QString _addrType;   // remember the address type: ("decoder" or null) or ("accessory" or "output")
 int _readDelay;     // remember the programming delay, in milliseconds
 int _writeDelay;    // remember the programming delay, in milliseconds
 int _delay;         // remember the programming delay, in milliseconds
 /*private*/ /*transient*/ /*volatile*/ ProgListener* _usingProgrammer;
 enum ProgState {

     READCOMMANDSENT, WRITECOMMANDSENT, NOTPROGRAMMING
 };
 ProgState state;// = ProgState::NOTPROGRAMMING;

protected:
 /*protected*/ /*synchronized*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);

 friend class OPSMDelayWorker;
};

class OPSMDelayWorker : public QObject
{
 Q_OBJECT
 OpsModeDelayedProgrammerFacade* facade;
 int value;
 int status;
public:
 OPSMDelayWorker(int value, int status, OpsModeDelayedProgrammerFacade* facade);

public slots:
 void process();

signals:
 void finished();
};
#endif // OPSMODEDELAYEDPROGRAMMERFACADE_H
