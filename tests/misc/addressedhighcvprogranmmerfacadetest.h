#ifndef ADDRESSEDHIGHCVPROGRANMMERFACADETEST_H
#define ADDRESSEDHIGHCVPROGRANMMERFACADETEST_H

#include <QObject>
#include "proglistener.h"
#include "exceptions.h"

class Logger;
class AddressedHighCvProgranmmerFacadeTest : public QObject
{
 Q_OBJECT
public:
 explicit AddressedHighCvProgranmmerFacadeTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testWriteReadDirect() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDirectHighCV() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadDirectHighCVRightSide() throw (ProgrammerException, InterruptedException);
 /*public*/ void testWriteReadIndexed() throw (ProgrammerException, InterruptedException);
 /*public*/ void testCvLimit();

private:
 int readValue = -2;
 bool replied = false;
 static Logger* log;
 /*synchronized*/ void waitReply() throw (InterruptedException);

 friend class ProgListenerO6;
};

class ProgListenerO6 : public QObject, public ProgListener {
 Q_OBJECT
 Q_INTERFACES(ProgListener)
 //@Override
 AddressedHighCvProgranmmerFacadeTest* test;
public:
 ProgListenerO6(AddressedHighCvProgranmmerFacadeTest* test) {this->test = test;}
 QObject* self() {return (QObject*)this;}
public slots:
 /*public*/ void programmingOpReply(int value, int status);
};
#endif // ADDRESSEDHIGHCVPROGRANMMERFACADETEST_H
