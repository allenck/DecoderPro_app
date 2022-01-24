#ifndef MATRIXSIGNALMASTTEST_H
#define MATRIXSIGNALMASTTEST_H

#include <QObject>
#include "junitutil.h"
#include "turnout.h"
class  Turnout;
class MatrixSignalMastTest : public QObject
{
 Q_OBJECT
public:
 explicit MatrixSignalMastTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testSetup();
 /*public*/ void testCtor1();
 /*public*/ void testHeld();
 /*public*/ void testLit();
 /*public*/ void testAspects();
 /*public*/ void testAspectAttributes();
 /*public*/ void testAspectNotSet();
 /*public*/ void testSetDelay();

};

class ReleaseUntilO18 : public ReleaseUntil
{
 Q_OBJECT
 Turnout* turnout;
 Turnout::STATES state;
 MatrixSignalMastTest* test;
public:
 ReleaseUntilO18(Turnout* turnout, Turnout::STATES state,  MatrixSignalMastTest* test)
 {
  this->turnout = turnout;
  this->state=state;
  this->test = test;
 }
 bool ready() /*throw (Exception)*/
 {return turnout->getCommandedState() == state; }
};
#endif // MATRIXSIGNALMASTTEST_H
