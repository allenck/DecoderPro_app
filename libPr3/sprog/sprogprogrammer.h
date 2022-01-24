#ifndef SPROGPROGRAMMER_H
#define SPROGPROGRAMMER_H
#include "abstractprogrammer.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogProgrammer : public AbstractProgrammer
 {
  Q_OBJECT
 public:
  SprogProgrammer(SprogSystemConnectionMemo* memo, QObject* parent = 0);
  /*public*/ QList<QString> getSupportedModes();
  /*public*/ bool getCanRead();
  /*synchronized*/ /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
  /*synchronized*/ /*public*/ void writeCV(int CV, int val, ProgListener* p) throw (ProgrammerException);
  /*synchronized*/ /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
  /*synchronized*/ /*public*/ void readCV(int CV, ProgListener* p) throw (ProgrammerException);
  /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
  /*public*/ QObject* self() {return (QObject*)this;}

 public slots:
  /*public*/ void notifyMessage(SprogMessage* m);
  /*synchronized*/ /*public*/ void notifyReply(SprogReply* reply);


 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(SprogProgrammer.class);
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;
  // members for handling the programmer interface
  int progState;// = 0;
  static /*final*/ int NOTPROGRAMMING;// = 0;    // is notProgramming
  static /*final*/ int COMMANDSENT;// = 2;       // read/write command sent, waiting reply
  int _val;	// remember the value being read/written for confirmative reply
  /*private*/ ProgListener* _usingProgrammer;// = null;
  SprogTrafficController* _controller;// = NULL;
  /*private*/ void startProgramming(int val, int CV);
  QString convertEnumToQString(ProgListener::status type);

 signals:
  void notify_programmingOpReply(int value, int status);

 protected:
  /*protected*/ void useProgrammer(ProgListener* p) throw (ProgrammerException);
  /*protected*/ SprogMessage* progTaskStart(ProgrammingMode* mode, int val, int cvnum);
  /*protected*/ void notifyProgListenerEnd(int value, int status);
  /*protected*/ SprogTrafficController* controller();

 protected slots:
  /*synchronized*/ /*protected*/ void timeout();

 };
}
#endif // SPROGPROGRAMMER_H
