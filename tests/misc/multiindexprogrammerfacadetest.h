#ifndef MULTIINDEXPROGRAMMERFACADETEST_H
#define MULTIINDEXPROGRAMMERFACADETEST_H

#include <QObject>
#include "exceptions.h"
#include "proglistener.h"

class Logger;
class MultiIndexProgrammerFacadeTest : public QObject
{
 Q_OBJECT
public:
 explicit MultiIndexProgrammerFacadeTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testWriteReadDirect() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDirectSkip() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadSingleIndexed() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadSingleIndexedSkip() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadSingleIndexedCvLast() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadSingleIndexedCvLastSkip() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteWriteSingleIndexedCvLastSkip() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteWriteSingleIndexedCvFirstSkip() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexed() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexedAltPiSi() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexedSkip() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexedCvList() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexedCvListAltPiSi() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexedCvListSkip() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexedCvListSkipAltPiSi() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexedCvListDelayedSkip() throw (ProgrammerException, InterruptedException);
 /*public*/ void testCvLimit();


private:
 static Logger* log;
 int readValue = -2;
 bool replied = false;
 /*synchronized*/ void waitReply() throw (InterruptedException);

 friend class ProgListenerO5;
};

class ProgListenerO5 : public QObject, public ProgListener {
 Q_OBJECT
  Q_INTERFACES(ProgListener)
    //@Override
 MultiIndexProgrammerFacadeTest* test;
public:
 ProgListenerO5(MultiIndexProgrammerFacadeTest* test) {this->test = test;}
 QObject* self() {return (QObject*)this;}
public slots:
 /*public*/ void programmingOpReply(int value, int status);
};

#endif // MULTIINDEXPROGRAMMERFACADETEST_H
