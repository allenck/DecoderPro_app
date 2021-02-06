#include "cvutiltest.h"
#include "assert1.h"
#include "junitutil.h"
#include "cvutil.h"
#include "junitappender.h"
/**
 * Test CV Utilities
 *
 * @author Dave Heap Copyright (C) 2016
 */
// /*public*/ class CvUtilTest {

    CvUtilTest::CvUtilTest(QObject *parent) : QObject(parent){
    }

    //@BeforeAll
    /*public*/ /*static*/ void CvUtilTest::setUpClass() {
    }

    //@AfterAll
    /*public*/ /*static*/ void CvUtilTest::tearDownClass() {
    }

    //@BeforeEach
    /*public*/ void CvUtilTest::setUp() {
        JUnitUtil::setUp();
    }

    //@AfterEach
    /*public*/ void CvUtilTest::tearDown() {
        JUnitUtil::tearDown();
    }

    /**
     * Test of expandCvList method, of class CvUtil::
     */
    //@Test
    /*public*/ void CvUtilTest::testExpandCvList() {
//        System.out.println("expandCvList");
        QString cvString;
        QStringList expResult;
        QStringList result;

        cvString = "abc";
        expResult = QStringList();
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "a(bc";
        expResult = QStringList{"abc"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "ab)c";
        expResult = QStringList{"abc"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "a(b)c";
        expResult = QStringList{"abc"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "127";
        expResult = QStringList();
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "CV0.255.256";
        expResult = QStringList();
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "";
        expResult = QStringList();
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "25.3.250:4";
        expResult = QStringList{"25.3.250", "25.3.251", "25.3.252", "25.3.253"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "98-103";
        expResult = QStringList{"98", "99", "100", "101", "102", "103"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "25.3.2(5:4)0";
        expResult = QStringList{"25.3.250", "25.3.260", "25.3.270", "25.3.280"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "16.3(1-7).25";
        expResult = QStringList{"16.31.25", "16.32.25", "16.33.25", "16.34.25", "16.35.25", "16.36.25", "16.37.25"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "1,5,7";
        expResult = QStringList{"1", "5", "7"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "16.3.25(1,2,5,7)";
        expResult = QStringList{"16.3.251", "16.3.252", "16.3.255", "16.3.257"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "16.3.25(1-7)";
        expResult = QStringList{"16.3.251", "16.3.252", "16.3.253", "16.3.254", "16.3.255", "16.3.256", "16.3.257"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "16.3-7.254";
        expResult = QStringList{"16.3.254", "16.4.254", "16.5.254", "16.6.254", "16.7.254"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "T3CV3-7.254";
        expResult = QStringList{"T3CV3.254", "T3CV4.254", "T3CV5.254", "T3CV6.254", "T3CV7.254"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "16.7-0.254";
        expResult = QStringList{"16.7.254", "16.6.254", "16.5.254", "16.4.254", "16.3.254", "16.2.254", "16.1.254", "16.0.254"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "16.23-20.254";
        expResult = QStringList{"16.23.254", "16.22.254", "16.21.254", "16.20.254"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "16.3.25(4-0)";
        expResult = QStringList{"16.3.254", "16.3.253", "16.3.252", "16.3.251", "16.3.250"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "16.3.2(53-48)";
        expResult = QStringList{"16.3.253", "16.3.252", "16.3.251", "16.3.250", "16.3.249", "16.3.248"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "T3CV25(4-0).5";
        expResult = QStringList{"T3CV254.5", "T3CV253.5", "T3CV252.5", "T3CV251.5", "T3CV250.5"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "25.3.250:1";
        expResult = QStringList{"25.3.250"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "25.3.250:-1";
        expResult = QStringList{"25.3.250"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "25.3.250:0";
        expResult = QStringList{"25.3.250"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "25.3.250:-4";
        expResult = QStringList{"25.3.250", "25.3.249", "25.3.248", "25.3.247"};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        cvString = "25.3-4.250:4";
        expResult = QStringList{};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);
        // make sure an error message is generated.
        JUnitAppender::assertErrorMessage("Invalid string '" + cvString + "'", __FILE__, __LINE__);

        cvString = "a(b(c)d)e";
        expResult = QStringList{};
        result = CvUtil::expandCvList(cvString);
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);
        // make sure an error message is generated.
        JUnitAppender::assertErrorMessage("Invalid string '" + cvString + "'", __FILE__, __LINE__);
    }

    /**
     * Test of addCvDescription method, of class CvUtil::
     */
    //@Test
    /*public*/ void CvUtilTest::testAddCvDescription() {
//        System.out.println("addCvDescription");
        QString toolTip = "A test tooltip";
        QString cvDescription = "CV999";
        QString mask1 = "XVXVXVVV";
        QString mask2 = "VVVVVVVV";
        QString expResult;
        QString result;

        // test with null toolTip
        result = CvUtil::addCvDescription("", cvDescription, mask1);
        expResult = "CV999 bits 0-2,4,6";
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        // test with empty toolTip
        result = CvUtil::addCvDescription("", cvDescription, mask1);
        expResult = "CV999 bits 0-2,4,6";
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        // test with no mask
        result = CvUtil::addCvDescription(toolTip, cvDescription, mask2);
        expResult = "A test tooltip (CV999)";
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        // test with no HTML
        result = CvUtil::addCvDescription(toolTip, cvDescription, mask1);
        expResult = "A test tooltip (CV999 bits 0-2,4,6)";
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);

        // test with HTML
        result = CvUtil::addCvDescription("<html>" + toolTip + "</html>", cvDescription, mask1);
        expResult = "<html>A test tooltip (CV999 bits 0-2,4,6)</html>";
        Assert::assertEquals(expResult, result, __FILE__, __LINE__);
    }

    /**
     * Test of getMaskDescription method, of class CvUtil::
     */
    //@Test
    /*public*/ void CvUtilTest::testGetMaskDescription() {
//        System.out.println("getMaskDescription");
        Assert::assertEquals("bit 0", CvUtil::getMaskDescription("XXXXXXXV"), __FILE__, __LINE__);
        Assert::assertEquals("bit 2", CvUtil::getMaskDescription("XXXXXVXX"), __FILE__, __LINE__);
        Assert::assertEquals("bits 0-2,4,6", CvUtil::getMaskDescription("XVXVXVVV"), __FILE__, __LINE__);
        Assert::assertEquals("bits 1-2,4-5", CvUtil::getMaskDescription("XXVVXVVX"), __FILE__, __LINE__);
        Assert::assertEquals("no bits", CvUtil::getMaskDescription("XXXXXXXX"), __FILE__, __LINE__);
    }
