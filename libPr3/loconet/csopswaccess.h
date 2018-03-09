#ifndef CSOPSWACCESS_H
#define CSOPSWACCESS_H

#include <QObject>
#include <QTimer>
#include "loconetsystemconnectionmemo.h"
#include "proglistener.h"

class CsOpSwAccess : public QObject
{
 Q_OBJECT
public:
 /*public*/ CsOpSwAccess(/*@Nonnull*/ LocoNetSystemConnectionMemo* memo, /*@Nonnull */ProgListener* p, QObject* parent = 0);
 /*public*/ void setProgrammerListener(/*@NonNULL*/ ProgListener* p);
 /*public*/ void readCsOpSw(QString opSw, /*@NonNULL*/ ProgListener* pL) throw (ProgrammerException);
 /*public*/ void readCmdStationOpSw(int cv);
 /*public*/ void returnCmdStationOpSwVal(int cmdStnOpSwNum);
 /*public*/ bool updateCmdStnOpSw(int opSwNum, bool val);
 /*public*/ bool extractCmdStnOpSw(int cmdStnOpSwNum);
 /*public*/ LocoNetMessage* updateOpSwVal(int cmdStnOpSwNum, bool cmdStnOpSwVal);


signals:

public slots:

private:
 enum CmdStnOpSwStateType {
     IDLE,
     QUERY,
     QUERY_ENHANCED,
     QUERY_BEFORE_WRITE,
     QUERY_ENHANCED_BEFORE_WRITE,
     WRITE,
     HAS_STATE
 };
 /*private*/ QTimer* csOpSwAccessTimer;
 /*private*/ QTimer* csOpSwValidTimer;
 /*private*/ CmdStnOpSwStateType cmdStnOpSwState;
 /*private*/ int cmdStnOpSwNum;
 /*private*/ bool cmdStnOpSwVal;
 /*private*/ LocoNetSystemConnectionMemo* memo;
 /*private*/ ProgListener* p;
 /*private*/ bool doingWrite;
 /*private*/ QVector<int> opSwBytes;
 /*private*/ bool haveValidLowBytes;
 /*private*/ bool haveValidHighBytes;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("CsOpSwAccess");
 /*private*/ void sendFinalProgrammerReply(int val, int response);
 void initializeCsOpSwAccessTimer();
 void initializeCsOpSwValidTimer();
 /*private*/ void finishTheWrite();

private slots:
 void on_csOpSwAccessTimer_timeout();
 void on_csOpSwValidTimer_timeout();
};

#endif // CSOPSWACCESS_H
