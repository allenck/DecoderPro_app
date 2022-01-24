#ifndef TWOINDEXTCSPROGRAMMERFACADE_H
#define TWOINDEXTCSPROGRAMMERFACADE_H

#include <QObject>
#include "exceptions.h"
#include "proglistener.h"

class Logger;
class TwoIndexTcsProgrammerFacadeTest : public QObject
{
 Q_OBJECT
public:
 explicit TwoIndexTcsProgrammerFacadeTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testWriteReadDirect() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDoubleIndexed() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadTripleIndexed() throw (ProgrammerException, InterruptedException);
 /*public*/ void testCvLimit();

private:
 static Logger* log;
 int readValue = -2;
 bool replied = false;
 /*synchronized*/ void waitReply() throw (InterruptedException);

 friend class ProgListenerO9;
};

class ProgListenerO9 : public QObject, public ProgListener {
 Q_OBJECT
 Q_INTERFACES(ProgListener)
  TwoIndexTcsProgrammerFacadeTest* test;
public:
ProgListenerO9(TwoIndexTcsProgrammerFacadeTest* test) {this->test = test;}
QObject* self() {return (QObject*)this;}
public slots:
    //@Override
    /*public*/ void programmingOpReply(int value, int status);
};

#endif // TWOINDEXTCSPROGRAMMERFACADE_H
