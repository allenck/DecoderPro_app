#ifndef LNDEFERPROGRAMMER_H
#define LNDEFERPROGRAMMER_H
#include "abstractprogrammer.h"

class Logger;
class LocoNetSystemConnectionMemo;
class LnDeferProgrammer : public AbstractProgrammer
{
public:
 /*public*/ LnDeferProgrammer(/*@Nonnull*/ LocoNetSystemConnectionMemo* memo, QObject* parent= nullptr);
 /*public*/ void writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) override;
 /*public*/ void readCV(QString CV, ProgListener* p) throw (ProgrammerException) override;
 /*public*/ void confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) override;
 /*@Nonnull*/ /*public*/ QList<QString> getSupportedModes() override;
 /*public*/ void setMode(ProgrammingMode* p) override;
 /*public*/ ProgrammingMode* getMode() override;
 /*public*/ bool getCanRead() override;
 /*public*/ bool getCanRead(QString addr);
 /*public*/ bool getCanWrite() override;
 /*public*/ bool getCanWrite(QString addr);
 /*public*/ Programmer::WriteConfirmMode getWriteConfirmMode(QString addr) override;
 /*public*/ void notifyProgListenerEnd(ProgListener* p, int value, int status) override;
 /*public*/ void addPropertyChangeListener(PropertyChangeListener* p) override;
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* p) override;
 /*public*/ QString decodeErrorCode(int i) override;
 /*public*/ QObject* self() {return (QObject*) this;}

private:
 LocoNetSystemConnectionMemo* memo;
 static Logger* log;
};

#endif // LNDEFERPROGRAMMER_H
