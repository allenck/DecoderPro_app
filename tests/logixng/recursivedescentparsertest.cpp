#include "recursivedescentparsertest.h"
#include "recursivedescentparser.h"
#include "assert1.h"
#include "junitutil.h"
#include "atomicboolean.h"
#include "defaultsymboltable.h"
#include "defaultconditionalng.h"
#include "logixng_thread.h"
#include "functionnotexistsexception.h"
#include "calculateexception.h"
#include "wrongnumberofparametersexception.h"
#include "simpletimebase.h"
#include "instancemanager.h"
#include "invalidsyntaxexception.h"
#include "loggerfactory.h"
/**
 * Test ExpressionParser
 *
 * @author Daniel Bergqvist 2019
 */
///*public*/  class RecursiveDescentParserTest {

    //@Test
    /*public*/  void RecursiveDescentParserTest::testCtor() {
        RecursiveDescentParser* t = new RecursiveDescentParser(QMap<QString, Variable*>());
        Assert::assertNotNull("not null", t, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void  RecursiveDescentParserTest::testParseAndCalculate() /*throws Exception*/ {

        AtomicBoolean* exceptionIsThrown = new AtomicBoolean();
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        SymbolTable* symbolTable = new DefaultSymbolTable((ConditionalNG*)new DefaultConditionalNG("IQC1", ""));

        variables.insert("abc", new MyVariable("abc", "ABC"));
        variables.insert("x", new MyVariable("x", 12));

        RecursiveDescentParser* t = new RecursiveDescentParser(variables);
        ExpressionNode* exprNode = t->parseExpression("");
        Assert::assertTrue("expression node is null", nullptr == exprNode, __FILE__, __LINE__);
        exprNode = t->parseExpression("134");
        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertTrue("calculate is correct", ((qint32)134) == (exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("abc");
        Assert::assertTrue("expression matches", "Identifier:abc" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertTrue("calculate is correct", "ABC" == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("\"a little string\"");
        Assert::assertTrue("expression matches", "String:a little string" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
//        System.err.format("expected: '%s', %s%n", 134d, ((Object)134d).getClass().getName());
        Assert::assertTrue("calculate is correct", "a little string" == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("123*1233");
        Assert::assertTrue("expression matches", "(IntNumber:123)*(IntNumber:1233)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertEquals("calculate is correct", ((int)151659), ( exprNode->calculate(symbolTable).toString()), __FILE__, __LINE__);
        exprNode = t->parseExpression("123+2123");
        Assert::assertTrue("expression matches", "(IntNumber:123)+(IntNumber:2123)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertTrue("calculate is correct", ((qint32)2246) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("123*3.2331");
        Assert::assertTrue("expression matches", "(IntNumber:123)*(FloatNumber:3.2331)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertEquals("calculate is correct", ((double)397.6713), ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12+45*12.2");
        Assert::assertTrue("expression matches", "(IntNumber:12)+((IntNumber:45)*(FloatNumber:12.2))" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertTrue("calculate is correct", ((double)561.0) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12*45+34");
        Assert::assertTrue("expression matches", "((IntNumber:12)*(IntNumber:45))+(IntNumber:34)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertTrue("calculate is correct", ((qint32)574L) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12-57/43");
        Assert::assertTrue("expression matches", "(IntNumber:12)-((IntNumber:57)/(IntNumber:43))" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertTrue("calculate is correct", ((qint32)11L) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12/23.2-43");
        Assert::assertTrue("expression matches", "((IntNumber:12)/(FloatNumber:23.2))-(IntNumber:43)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        Assert::assertTrue("calculate is correct", ((double)(-42.482758620689655172413793103448)) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);

        exprNode = t->parseExpression("12 < 2");
        Assert::assertTrue("expression matches", "(IntNumber:12)<(IntNumber:2)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
        Assert::assertTrue("calculate is correct", ((bool)false) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12 <= 2");
        Assert::assertTrue("expression matches", "(IntNumber:12)<=(IntNumber:2)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
        Assert::assertTrue("calculate is correct", ((bool)false) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12 > 2");
        Assert::assertTrue("expression matches", "(IntNumber:12)>(IntNumber:2)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
        Assert::assertTrue("calculate is correct", ((bool)true) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12 >= 2");
        Assert::assertTrue("expression matches", "(IntNumber:12)>=(IntNumber:2)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
        Assert::assertTrue("calculate is correct", ((bool)true) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12 == 2");
        Assert::assertTrue("expression matches", "(IntNumber:12)==(IntNumber:2)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
        Assert::assertTrue("calculate is correct", ((bool)false) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
        exprNode = t->parseExpression("12 != 2");
        Assert::assertTrue("expression matches", "(IntNumber:12)!=(IntNumber:2)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
        Assert::assertTrue("calculate is correct", ((bool)true) == ( exprNode->calculate(symbolTable)), __FILE__, __LINE__);
/*
        exprNode = t->parseExpression("not 12 < 2");
        System.err.format("getDefinitionString: '%s'%n",  exprNode->getDefinitionString());
        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
        Assert::assertTrue("expression matches", "(not (IntNumber:12))<(IntNumber:2)" == ( exprNode->getDefinitionString()));
        Assert::assertTrue("calculate is correct", ((bool)false) == ( exprNode->calculate(symbolTable)));
        exprNode = t->parseExpression("not (12 < 2)");
        System.err.format("getDefinitionString: '%s'%n",  exprNode->getDefinitionString());
        System.err.format("calculate: '%s', %s%n",  exprNode->calculate(symbolTable),  exprNode->calculate(symbolTable).getClass().getName());
        Assert::assertTrue("expression matches", "not ((IntNumber:12)<(IntNumber:2))" == ( exprNode->getDefinitionString()));
        Assert::assertTrue("calculate is correct", ((bool)true) == ( exprNode->calculate(symbolTable)));
*/
        exprNode = t->parseExpression("2 <= 3");
        Assert::assertTrue("expression matches", "(IntNumber:2)<=(IntNumber:3)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        exprNode = t->parseExpression("2 <= 3 and 3");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("2 <= 3 and 3 > 4");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("4 and 2");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("4 or 2");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("2 <= 3 and 3 > 4 or 2");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("2 <= 3 and 3 > 4 or 2 < 3");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("(2 <= 3) and 3 > 4 or 2 < 3");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("2 <= (3 and 3) > 4 or 2 < 3");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("2 <= 3 and (3 > 4) or 2 < 3");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("2 <= 3 and (3 > 4) or (2 < 3)");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));
//        exprNode = t->parseExpression("(2 <= 3) and (3 > 4) or 2 < 3");
//        Assert::assertTrue("expression matches", "IntNumber:134" == ( exprNode->getDefinitionString()));

        exceptionIsThrown->set(false);
        try {
            t->parseExpression("12+31*(23-1)+((((9*2+3)-2)/23");
        } catch (InvalidSyntaxException* e) {
//            System.err.format("Error message: %s%n", e.getMessage());
            Assert::assertTrue("exception message matches", "Invalid syntax error" == (e->getMessage()), __FILE__, __LINE__);
            exceptionIsThrown->set(true);
        }
        Assert::assertTrue("exception is thrown", exceptionIsThrown->get(), __FILE__, __LINE__);

        exprNode = t->parseExpression("12+31*(23-1)+21*((((9*2+3)-2)/23+3)/3+4)");
        Assert::assertTrue(
                "expression matches",
                "((IntNumber:12)+((IntNumber:31)*((IntNumber:23)-(IntNumber:1))))+((IntNumber:21)*((((((((IntNumber:9)*(IntNumber:2))+(IntNumber:3))-(IntNumber:2))/(IntNumber:23))+(IntNumber:3))/(IntNumber:3))+(IntNumber:4)))"
                         == ( exprNode->getDefinitionString()), __FILE__, __LINE__);

        exprNode = t->parseExpression("random()");
        Assert::assertTrue("expression matches", "Function:random()" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        QVariant result =  exprNode->calculate(symbolTable);
//        System.err.format("Result: %s, %s%n", result, result->getClass().getName());
        log->debug(tr("Result: %1, %2 Line %3").arg(result.toDouble()).arg(result.typeName()).arg(__LINE__));
        Assert::assertTrue("calculate is probably correct", (result.type() == QMetaType::Double) && ((result.toDouble()) >= 0.0) && ((result.toDouble()) <= 1.0), __FILE__, __LINE__);
        exprNode = t->parseExpression("int(23.56)");
        Assert::assertTrue("expression matches", "Function:int(FloatNumber:23.56)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        result = exprNode->calculate(symbolTable);
        log->debug(tr("Result: %1, %2 Line %3").arg(result.toString(), result.typeName()).arg(__LINE__));
        Assert::assertEquals("calculate is correct", ((int)23), ( exprNode->calculate(symbolTable).toInt()), __FILE__, __LINE__);
        exprNode = t->parseExpression("sin(180,\"deg\")");
        Assert::assertTrue("expression matches", "Function:sin(IntNumber:180,String:deg)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        System.err.format("Result: %s, %s%n", result, result->getClass().getName());
        Assert::assertEquals("calculate is correct", 0,  exprNode->calculate(symbolTable).toDouble(), 1e-15, __FILE__, __LINE__);
        exprNode = t->parseExpression("int(x*2+5)");
        Assert::assertTrue("expression matches", "Function:int(((Identifier:x)*(IntNumber:2))+(IntNumber:5))" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
        exprNode = t->parseExpression("int((x))");
        Assert::assertTrue("expression matches", "Function:int(Identifier:x)" == ( exprNode->getDefinitionString()), __FILE__, __LINE__);
//        exprNode = t->parseExpression("abc(x*(2+3),23,\"Abc\",2)");
//        Assert::assertTrue(
//                "expression matches",
//                "Function:abc((Identifier:x)*((IntNumber:2)+(IntNumber:3)),IntNumber:23,String:Abc,IntNumber:2)"
//                         == ( exprNode->getDefinitionString()));

        exceptionIsThrown->set(false);
        try {
            t->parseExpression("abc(123)");
        } catch (FunctionNotExistsException* e) {
//            System.err.format("Error message: %s%n", e.getMessage());
            Assert::assertTrue("exception message matches", "The function \"abc\" does not exists" == (e->getMessage()), __FILE__, __LINE__);
            exceptionIsThrown->set(true);
        }
        Assert::assertTrue("exception is thrown", exceptionIsThrown->get(), __FILE__, __LINE__);
/*
        exceptionIsThrown.set(false);
        try {
            t->parseExpression("abcde");
        } catch (IdentifierNotExistsException e) {
//            System.err.format("Error message: %s%n", e.getMessage());
            Assert::assertTrue("exception message matches", "The identifier \"abcde\" does not exists" == (e.getMessage()));
            exceptionIsThrown.set(true);
        }
        Assert::assertTrue("exception is thrown", exceptionIsThrown.get());
*/
        exceptionIsThrown->set(false);
        try {
            t->parseExpression("abc(123)");
        } catch (FunctionNotExistsException* e) {
//            System.err.format("Error message: %s%n", e.getMessage());
            Assert::assertTrue("exception message matches", "The function \"abc\" does not exists" == (e->getMessage()), __FILE__, __LINE__);
            exceptionIsThrown->set(true);
        }
        Assert::assertTrue("exception is thrown", exceptionIsThrown->get(), __FILE__, __LINE__);

        exceptionIsThrown->set(false);
        try {
            exprNode = t->parseExpression("sin(1,2,3)");
             exprNode->calculate(symbolTable);
        } catch (WrongNumberOfParametersException* e) {
//            System.err.format("Error message: %s%n", e.getMessage());
            Assert::assertTrue("exception message matches", "Function \"sin\" has wrong number of parameters" == (e->getMessage()), __FILE__, __LINE__);
            exceptionIsThrown->set(true);
        }
        Assert::assertTrue("exception is thrown", exceptionIsThrown->get(), __FILE__, __LINE__);

        exceptionIsThrown->set(false);
        try {
            exprNode = t->parseExpression("123+\"abc\"");
             exprNode->calculate(symbolTable);
        } catch (CalculateException* e) {
//            System.err.format("Error message: %s%n", e.getMessage());
            Assert::assertEquals("exception message matches", "The two operands \"123\" and \"abc\" have different types",(e->getMessage()), __FILE__, __LINE__);
            exceptionIsThrown->set(true);
        }
        Assert::assertTrue("exception is thrown", exceptionIsThrown->get(), __FILE__, __LINE__);



        Timebase* fastClock = (SimpleTimebase*)InstanceManager::getDefault("Timebase");
        fastClock->setRun(false);
        fastClock->setTime( QDateTime(QDate(0,0,0), QTime(11, 05, 0)));   // 11:05

        int minSinceMidnight = (11 * 60) + 5;
        exprNode = t->parseExpression("fastClock()");
        Assert::assertEquals("expression matches", "Function:fastClock()",  exprNode->getDefinitionString(), __FILE__, __LINE__);
//        System.err.format("Result: %s, %s%n", result, result->getClass().getName());
        Assert::assertEquals("calculate is correct", minSinceMidnight, exprNode->calculate(symbolTable).toInt(), __FILE__, __LINE__);
    }


    // The minimal setup for log4J
    //@Before
    /*public*/  void  RecursiveDescentParserTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/  void RecursiveDescentParserTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
Logger* RecursiveDescentParserTest::log = LoggerFactory::getLogger("RecursiveDescentParserTest");

