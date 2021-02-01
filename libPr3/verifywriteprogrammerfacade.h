#ifndef VERIFYWRITEPROGRAMMERFACADE_H
#define VERIFYWRITEPROGRAMMERFACADE_H
#include "abstractprogrammerfacade.h"

class Logger;
class VerifyWriteProgrammerFacade : public AbstractProgrammerFacade, public ProgListener
{
 Q_OBJECT
  Q_INTERFACES(ProgListener)
public:
 /*public*/ VerifyWriteProgrammerFacade(Programmer* prog, QObject* parent = 0);
 /*synchronized*/ /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
 /*synchronized*/ /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
 /*public*/ Programmer::WriteConfirmMode getWriteConfirmMode(QString addr);
 /*public*/ QObject* self() {return (QObject*)this;}

public slots:
 /*public*/ void programmingOpReply(int value, int status);

signals:
 void do_programmingOpReply(int value, int status);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("VerifyWriteProgrammerFacade");
 // members for handling the programmer interface
 int _val;	// remember the value being read/written for confirmative reply
 QString _cv;	// remember the cv number being read/written
 /*private*/ ProgListener* _usingProgrammer;// = null;

 /*
 * State machine for VerifyWriteProgrammerFacade  (click to magnify):
 * <a href="doc-files/VerifyWriteProgrammerFacade-State-Diagram.png"><img src="doc-files/VerifyWriteProgrammerFacade-State-Diagram.png" alt="UML State diagram" height="50%" width="50%"></a>
 */
enum ProgState {
    /** Waiting for response to read, will end next */
    READING,
    /** Waiting for response to write, issue verify read next */
    FINISHWRITE,
    /** Waiting for response to verify read, will end next */
    FINISHREAD,
    /** No current operation */
    NOTPROGRAMMING
};
ProgState state;// = ProgState.NOTPROGRAMMING;
ProgListener* temp;// = _usingProgrammer;

protected:
 /*protected*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);

};

#endif // VERIFYWRITEPROGRAMMERFACADE_H
