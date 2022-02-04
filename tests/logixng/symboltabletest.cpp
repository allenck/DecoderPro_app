#include "symboltabletest.h"
#include "junitutil.h"
#include "assert1.h"
#include "symboltable.h"
/**
 * Test SymbolTable
 *
 * @author Daniel Bergqvist 2021
 */
// /*public*/  class SymbolTableTest {

    //@Test
    /*public*/  void SymbolTableTest::testValidateName() {
        // Valid names
        Assert::assertTrue(SymbolTable::validateName("Abc"), __FILE__, __LINE__);
        Assert::assertTrue(SymbolTable::validateName("abc"), __FILE__, __LINE__);
        Assert::assertTrue(SymbolTable::validateName("Abc123"), __FILE__, __LINE__);
        Assert::assertTrue(SymbolTable::validateName("A123bc"), __FILE__, __LINE__);
        Assert::assertTrue(SymbolTable::validateName("Abc___"), __FILE__, __LINE__);
        Assert::assertTrue(SymbolTable::validateName("Abc___fsdffs"), __FILE__, __LINE__);
        Assert::assertTrue(SymbolTable::validateName("Abc3123__2341fsdf"), __FILE__, __LINE__);

        // Invalid names
        Assert::assertFalse(SymbolTable::validateName("12Abc"), __FILE__, __LINE__);  // Starts with a digit
        Assert::assertFalse(SymbolTable::validateName("_Abc"), __FILE__, __LINE__);   // Starts with an underscore
        Assert::assertFalse(SymbolTable::validateName(" Abc"), __FILE__, __LINE__);   // Starts with a non letter
        Assert::assertFalse(SymbolTable::validateName("A bc"), __FILE__, __LINE__);   // Has a character that's not letter, digit or underscore
        Assert::assertFalse(SymbolTable::validateName("A{bc"), __FILE__, __LINE__);   // Has a character that's not letter, digit or underscore
        Assert::assertFalse(SymbolTable::validateName("A+bc"), __FILE__, __LINE__);   // Has a character that's not letter, digit or underscore
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void SymbolTableTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/  void SymbolTableTest::tearDown() {
        JUnitUtil::tearDown();
    }
