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
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer) != nullptr);
        Assert::assertEquals("Check Default", ProgrammingMode::OPSBYTEMODE,
                programmer->getMode());
    }

    //@Test
    //@Override
    /*public*/ void AddressedProgrammerTestBase::testGetCanRead() {
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer) != nullptr);
        Assert::assertFalse("can read", programmer->getCanRead());
    }

    //@Test(expected=java.lang.IllegalArgumentException.class)
    //@Override
    /*public*/ void AddressedProgrammerTestBase::testSetGetMode() {
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer) != nullptr);
        programmer->setMode(ProgrammingMode::REGISTERMODE);
        Assert::assertEquals("Check mode matches set", ProgrammingMode::REGISTERMODE,
                programmer->getMode());
    }

    //@Test
    /*public*/ void AddressedProgrammerTestBase::testGetLongAddress(){
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer) != nullptr);
        Assert::assertNotNull("long/short address boolean",((AddressedProgrammer*)programmer)->getLongAddress());
    }

    //@Test
    /*public*/ void AddressedProgrammerTestBase::testGetAddressNumber(){
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer) != nullptr);
        Assert::assertNotNull("Numeric Address",((AddressedProgrammer*)programmer)->getAddressNumber());
    }

    //@Test
    /*public*/ void AddressedProgrammerTestBase::testGetAddress(){
        Assume::assumeTrue(/*programmer instanceof AddressedProgrammer*/ qobject_cast<AddressedProgrammer*>(programmer) != nullptr);
        Assert::assertNotNull("String Address",((AddressedProgrammer*)programmer)->getAddress());
    }


    // must set the value of programmer in setUp.
    //@Before
    //@Override
    // /*abstract*/ /*public*/ void setUp();
