#include "abstractconsisttestbase.h"
#include "instancemanager.h"
#include "assert1.h"
#include "junitappender.h"
#include "RosterTest/rostertestutil.h"
#include "roster.h"
#include "rosterentry.h"
#include "consistpreferencesmanager.h"
#include "file.h"

AbstractConsistTestBase::AbstractConsistTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Test simple functioning of Consist classes.
 *
 * @author	Paul Copyright (C) 2017
 */
//abstract /*public*/ class AbstractConsistTestBase {

    //@Before
    //abstract /*public*/ void setUp();  // should set the consist under test to c.
    //@After
    //abstract /*public*/ void tearDown(); // should clean up the consist c.

    /*@Test*/ /*public*/ void AbstractConsistTestBase::testCtor() {
        Assert::assertNotNull(c);
    }

    //@Test(expected=java.lang.NullPointerException.class)
    /*public*/ void AbstractConsistTestBase::checkDisposeMethod(){
        DccLocoAddress* A = new DccLocoAddress(200,true);
        DccLocoAddress* B = new DccLocoAddress(250,true);
        c->restore(A,true); // use restore here, as it does not send
                           // any data to the command station
        c->restore(B,false); // use restore here, as it does not send
                           // any data to the command station
        // before dispose, this should succeed.
        Assert::assertTrue("Advanced Consist Contains",c->contains(A));
        Assert::assertTrue("Advanced Consist Contains",c->contains(B));
        c->dispose();
        // after dispose, this should fail
        Assert::assertTrue("Advanced Consist Contains",c->contains(A));
        Assert::assertTrue("Advanced Consist Contains",c->contains(B));
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::testGetConsistType(){
        Assert::assertEquals("default consist type",Consist::ADVANCED_CONSIST,c->getConsistType());
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::testSetConsistTypeAdvanced(){
        c->setConsistType(Consist::ADVANCED_CONSIST);
        Assert::assertEquals("default consist type",Consist::ADVANCED_CONSIST,c->getConsistType());
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::testSetConsistTypeCS(){
        c->setConsistType(Consist::CS_CONSIST);
        // make sure an error message is generated.
        JUnitAppender::assertErrorMessage("Consist Type Not Supported");
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::checkAddressAllowedGood(){
        Assert::assertTrue("AddressAllowed", c->isAddressAllowed(new DccLocoAddress(200,true)));
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::checkAddressAllowedBad(){
        Assert::assertFalse("AddressAllowed", c->isAddressAllowed(new DccLocoAddress(0,false)));
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::checkSizeLimitAdvanced(){
        c->setConsistType(Consist::ADVANCED_CONSIST);
        Assert::assertEquals("Advanced Consist Limit",-1,c->sizeLimit());
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::checkContainsAdvanced(){
        c->setConsistType(Consist::ADVANCED_CONSIST);
        DccLocoAddress* A = new DccLocoAddress(200,true);
        DccLocoAddress* B = new DccLocoAddress(250,true);
        // nothing added, should be false for all.
        Assert::assertFalse("Advanced Consist Contains",c->contains(A));
        Assert::assertFalse("Advanced Consist Contains",c->contains(B));
        // add just A
        c->restore(A,true); // use restore here, as it does not send
                           // any data to the command station
        Assert::assertTrue("Advanced Consist Contains",c->contains(A));
        Assert::assertFalse("Advanced Consist Contains",c->contains(B));
        // then add B
        c->restore(B,false);
        Assert::assertTrue("Advanced Consist Contains",c->contains(A));
        Assert::assertTrue("Advanced Consist Contains",c->contains(B));
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::checkGetLocoDirectionAdvanced(){
        c->setConsistType(Consist::ADVANCED_CONSIST);
        DccLocoAddress* A = new DccLocoAddress(200,true);
        DccLocoAddress* B = new DccLocoAddress(250,true);
        c->restore(A,true); // use restore here, as it does not send
                           // any data to the command station
        c->restore(B,false); // revese direction.
        Assert::assertTrue("Direction in Advanced Consist",c->getLocoDirection(A));
        Assert::assertFalse("Direction in Advanced Consist",c->getLocoDirection(B));
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::checkGetSetLocoRosterIDAdvanced() throw (IOException,FileNotFoundException) {
        RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()),"rosterTest.xml");
        RosterEntry* entry = Roster::getDefault()->getEntryForId("ATSF123");
        c->setConsistType(Consist::ADVANCED_CONSIST);
        DccLocoAddress* A = entry->getDccLocoAddress();
        DccLocoAddress* B = new DccLocoAddress(250,true);
        c->restore(A,true); // use restore here, as it does not send
                           // any data to the command station
        c->restore(B,false); // revese direction.
        c->setRosterId(A,"ATSF123");
        Assert::assertEquals("Roster ID A","ATSF123",c->getRosterId(A));
        Assert::assertNull("Roster ID B", c->getRosterId(B));
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::checkRemoveWithGetRosterIDAdvanced() throw (IOException,FileNotFoundException) {
        RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()),"rosterTest.xml");
        RosterEntry* entry = Roster::getDefault()->getEntryForId("ATSF123");
        c->setConsistType(Consist::ADVANCED_CONSIST);
        DccLocoAddress* A = entry->getDccLocoAddress();
        DccLocoAddress* B = new DccLocoAddress(250,true);
        c->restore(A,true); // use restore here, as it does not send
                           // any data to the command station
        c->restore(B,false); // revese direction.
        c->setRosterId(A,"ATSF123");
        Assert::assertEquals("Roster ID A","ATSF123",c->getRosterId(A));
        Assert::assertNull("Roster ID B",c->getRosterId(B));
        c->remove(A);
        Assert::assertFalse("Roster A is no longer in consist",c->contains(A));
    }

    /*@Test*/ /*public*/ void AbstractConsistTestBase::checkAddRemoveWithRosterUpdateAdvanced() throw (IOException,FileNotFoundException) {
        // verify the roster update process is active.
        ((ConsistPreferencesManager*)InstanceManager::getDefault("ConsistPreferencesManager"))->setUpdateCV19(true);
        RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()),"rosterTest.xml");
        RosterEntry* entry = Roster::getDefault()->getEntryForId("ATSF123");
        c->setConsistType(Consist::ADVANCED_CONSIST);
        DccLocoAddress* A = entry->getDccLocoAddress();
        DccLocoAddress* B = new DccLocoAddress(250,true);
        c->restore(A,true); // use restore here, as it does not send
                           // any data to the command station
        c->restore(B,false); // revese direction.
        c->setRosterId(A,"ATSF123");

        // verify that roster ATSF123 has CV19 set to the consist address
        CvTableModel*  cvTable = new CvTableModel(nullptr, nullptr);  // will hold CV objects
        VariableTableModel* varTable = new VariableTableModel(nullptr,QStringList()<<"Name"<<"Value",cvTable);
        entry->readFile();  // read, but don’t yet process

        // load from decoder file
        RosterTestUtil::loadDecoderFromLoco(entry,varTable);

        entry->loadCvModel(varTable, cvTable);
        CvValue* cv19Value = cvTable->getCvByNumber("19");
        Assert::assertEquals("CV19 value after add",c->getConsistAddress()->getNumber(),cv19Value->getValue());

        Assert::assertEquals("Roster ID A","ATSF123",c->getRosterId(A));
        Assert::assertNull("Roster ID B",c->getRosterId(B));
        c->remove(A);
        Assert::assertFalse("Roster A is no longer in consist",c->contains(A));

        cvTable = new CvTableModel(nullptr, nullptr);  // will hold CV objects
        varTable = new VariableTableModel(nullptr,QStringList()<<"Name"<<"Value",cvTable);
        entry->readFile();  // read, but don’t yet process

        // load from decoder file
        RosterTestUtil::loadDecoderFromLoco(entry,varTable);

        entry->loadCvModel(varTable, cvTable);
        cv19Value = cvTable->getCvByNumber("19");
        Assert::assertEquals("CV19 value after remove",0,cv19Value->getValue());
    }


    // The minimal setup for log4J
