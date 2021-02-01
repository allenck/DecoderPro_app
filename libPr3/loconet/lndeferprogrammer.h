#ifndef LNDEFERPROGRAMMER_H
#define LNDEFERPROGRAMMER_H
#include "abstractprogrammer.h"

class Logger;
class LocoNetSystemConnectionMemo;
class LnDeferProgrammer : public AbstractProgrammer
{
public:
 /*public*/ LnDeferProgrammer(/*@Nonnull*/ LocoNetSystemConnectionMemo* memo, QObject* parent= nullptr);
 /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
 /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException);
 /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException);
 /*@Nonnull*/ /*public*/ QList<QString> getSupportedModes();
 /*public*/ void setMode(ProgrammingMode* p);
 /*public*/ ProgrammingMode* getMode();
 /*public*/ bool getCanRead();
 /*public*/ bool getCanRead(QString addr);
 /*public*/ bool getCanWrite();
 /*public*/ bool getCanWrite(QString addr);
 /*public*/ Programmer::WriteConfirmMode getWriteConfirmMode(QString addr);
 /*public*/ void notifyProgListenerEnd(ProgListener* p, int value, int status);
 /*public*/ void addPropertyChangeListener(PropertyChangeListener* p);
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* p);
 /*public*/ QString decodeErrorCode(int i);
 /*public*/ QObject* self() {return (QObject*) this;}

private:
 LocoNetSystemConnectionMemo* memo;
 static Logger* log;
};

#endif // LNDEFERPROGRAMMER_H
