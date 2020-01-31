#ifndef CONSISTTOOLFRAMETEST_H
#define CONSISTTOOLFRAMETEST_H

#include <QObject>
#include "exceptions.h"
#include "abstractconsistmanager.h"
#include "testconsistmanager.h"

class TemporaryFolder;
class ConsistToolFrameTest : public QObject
{
 Q_OBJECT
public:
 explicit ConsistToolFrameTest(QObject *parent = nullptr);
 //@Rule
 /*public*/ TemporaryFolder* folder;// = new TemporaryFolder();
 Q_INVOKABLE /*public*/ void setUp() throw (IOException);
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCtor();
 /*public*/ void testCtorWithCSpossible();
 /*public*/ void testAdd();
 /*public*/ void testReverseButton();
 /*public*/ void testRestoreButton();
 /*public*/ void testThrottle();
 /*public*/ void testDeleteNoConsistAddress();
 /*public*/ void testScanEmptyRoster();
 /*public*/ void testScanRosterNoConsists() throw (IOException, FileNotFoundException) ;
 /*public*/ void testScanRosterWithConsists() throw (IOException, FileNotFoundException);

private:

};

class TestConsistManagerO1 : public TestConsistManager
{
 Q_OBJECT
public:
 // package protected integers for tests to use
 int addCalls = 0; // records the number of times addToAdvancedConsist is called
 int removeCalls = 0; // records the  number of times removeFromAdancedConsist is called.
 TestConsistManagerO1()
 {
 }
     //@Override
     /*public*/ bool isCommandStationConsistPossible() {
         return true;
     }
};

#endif // CONSISTTOOLFRAMETEST_H
