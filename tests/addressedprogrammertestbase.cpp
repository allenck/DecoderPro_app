#include "addressedprogrammertestbase.h"
#include "assert1.h"
#include "addressedprogrammer.h"
#include "programmingmode.h"
#include "assume.h"

AddressedProgrammerTestBase::AddressedProgrammerTestBase()
{

}
/**
 * Base JUnit tests for the Operations Mode Programmers derived from
 * the AddressedProgrammer interface
 * <p>
 * Copyright: Copyright (c) 2002</p>
 *
 * @author Bob Jacobsen
 * @author Paul Bender copyright (C) 2018
 */
// /*abstract*/ /*public*/ class AddressedProgrammerTestBase extends ProgrammerTestBase {

    //@Test
    //@Override
    /*public*/ void AddressedProgrammerTestBase::testDefault() {
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer->self()) != nullptr);
        Assert::assertEquals("Check Default", ProgrammingMode::OPSBYTEMODE,
                programmer->getMode(), __FILE__, __LINE__);
    }

    //@Test
    //@Override
    /*public*/ void AddressedProgrammerTestBase::testGetCanRead() {
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer->self()) != nullptr);
        Assert::assertFalse("can read", programmer->getCanRead(), __FILE__, __LINE__);
    }

    //@Test(expected=java.lang.IllegalArgumentException.class)
    //@Override
    /*public*/ void AddressedProgrammerTestBase::testSetGetMode() {
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer->self()) != nullptr);
        programmer->setMode(ProgrammingMode::REGISTERMODE);
        Assert::assertEquals("Check mode matches set", ProgrammingMode::REGISTERMODE,
                programmer->getMode(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AddressedProgrammerTestBase::testGetLongAddress(){
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer->self()) != nullptr);
        Assert::assertNotNull("long/short address boolean",((AddressedProgrammer*)programmer)->getLongAddress(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AddressedProgrammerTestBase::testGetAddressNumber(){
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer->self()) != nullptr);
        Assert::assertNotNull("Numeric Address",((AddressedProgrammer*)programmer)->getAddressNumber(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AddressedProgrammerTestBase::testGetAddress(){
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer->self()) != nullptr);
        Assert::assertNotNull("String Address",((AddressedProgrammer*)programmer)->getAddress(), __FILE__, __LINE__);
    }


    // must set the value of programmer in setUp.
    //@Before
    //@Override
    // /*abstract*/ /*public*/ void setUp();
