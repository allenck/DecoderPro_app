#include "decoderfiletest.h"
#include "junitutil.h"
#include "assert1.h"
#include "progdebugger.h"
#include "decoderfile.h"
#include <QLabel>
#include "cvtablemodel.h"
#include "variabletablemodel.h"

DecoderFileTest::DecoderFileTest(QObject *parent) : QObject(parent)
{
 p = new ProgDebugger();
}
/**
 * DecoderFileTest.java
 *
 * @author	Bob Jacobsen, Copyright (C) 2001, 2002
 */
///*public*/ class DecoderFileTest {


    //@Test
    /*public*/ void DecoderFileTest::testSingleVersionNumber() {
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "23", "24",
                "family", "filename", 16, 3, QDomElement());
        d->setOneVersion(18);
        Assert::assertEquals("single 18 OK", true, d->isVersion(18), __FILE__, __LINE__);
        Assert::assertEquals("single 19 not OK", false, d->isVersion(19), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testRangeVersionNumber() {
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "24", "25",
                "family", "filename", 16, 3, QDomElement());
        d->setVersionRange(18, 22);
        Assert::assertEquals("single 17 not OK", false, d->isVersion(17), __FILE__, __LINE__);
        Assert::assertEquals("single 18 OK", true, d->isVersion(18), __FILE__, __LINE__);
        Assert::assertEquals("single 19 OK", true, d->isVersion(19), __FILE__, __LINE__);
        Assert::assertEquals("single 20 OK", true, d->isVersion(20), __FILE__, __LINE__);
        Assert::assertEquals("single 21 OK", true, d->isVersion(21), __FILE__, __LINE__);
        Assert::assertEquals("single 22 OK", true, d->isVersion(22), __FILE__, __LINE__);
        Assert::assertEquals("single 23 not OK", false, d->isVersion(23), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testCtorRange() {
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "18", "22",
                "family", "filename", 16, 3, QDomElement());
        Assert::assertEquals("single 17 not OK", false, d->isVersion(17), __FILE__, __LINE__);
        Assert::assertEquals("single 18 OK", true, d->isVersion(18), __FILE__, __LINE__);
        Assert::assertEquals("single 19 OK", true, d->isVersion(19), __FILE__, __LINE__);
        Assert::assertEquals("single 20 OK", true, d->isVersion(20), __FILE__, __LINE__);
        Assert::assertEquals("single 21 OK", true, d->isVersion(21), __FILE__, __LINE__);
        Assert::assertEquals("single 22 OK", true, d->isVersion(22), __FILE__, __LINE__);
        Assert::assertEquals("single 23 not OK", false, d->isVersion(23), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testCtorLow() {
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "18", "",
                "family", "filename", 16, 3, QDomElement());
        Assert::assertEquals("single 17 not OK", false, d->isVersion(17), __FILE__, __LINE__);
        Assert::assertEquals("single 18 OK", true, d->isVersion(18), __FILE__, __LINE__);
        Assert::assertEquals("single 19 not OK", false, d->isVersion(19), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testCtorHigh() {
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "", "18",
                "family", "filename", 16, 3, QDomElement());
        Assert::assertEquals("single 17 not OK", false, d->isVersion(17), __FILE__, __LINE__);
        Assert::assertEquals("single 18 OK", true, d->isVersion(18), __FILE__, __LINE__);
        Assert::assertEquals("single 19 not OK", false, d->isVersion(19), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testSeveralSingleVersionNumber() {
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "23", "24",
                "family", "filename", 16, 3, QDomElement());
        d->setOneVersion(18);
        Assert::assertEquals("single 18 OK", true, d->isVersion(18), __FILE__, __LINE__);
        Assert::assertEquals("single 19 not OK", false, d->isVersion(19), __FILE__, __LINE__);
        d->setOneVersion(19);
        Assert::assertEquals("single 19 OK", true, d->isVersion(19), __FILE__, __LINE__);
        Assert::assertEquals("single 21 not OK", false, d->isVersion(21), __FILE__, __LINE__);
        d->setOneVersion(21);
        Assert::assertEquals("single 21 OK", true, d->isVersion(21), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testMfgName() {
        setupDecoder();
        Assert::assertEquals("mfg name ", "Digitrax", DecoderFile::getMfgName(decoder), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testLoadTable() {
        setupDecoder();

        // this test should probably be done in terms of a test class instead of the real one...
        JLabel* progStatus = new JLabel(" OK ");
        CvTableModel* cvModel = new CvTableModel(progStatus, p);
        VariableTableModel* variableModel = new VariableTableModel(progStatus,
                QStringList() <<"Name"<< "Value", cvModel);
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "23", "24",
                "family", "filename", 16, 16, QDomElement());

        d->loadVariableModel(decoder, variableModel);
        Assert::assertEquals("read rows ", 3, variableModel->getRowCount(), __FILE__, __LINE__);
        Assert::assertEquals("first row name ", "Address", variableModel->getLabel(0), __FILE__, __LINE__);
        Assert::assertEquals("third row name ", "Normal direction of motion", variableModel->getLabel(2), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testIncludeCheck() {
        QDomElement e;
        // test some examples
        e = doc.createElement("Test");
        Assert::assertTrue("1 in null", DecoderFile::isIncluded(e, "1", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("include", "1,2");
        Assert::assertTrue("1 in 1,2", DecoderFile::isIncluded(e, "1", "model", "family", "", ""), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2", DecoderFile::isIncluded(e, "2", "model", "family", "", ""), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", !DecoderFile::isIncluded(e, "3", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("include", "105,205");
        Assert::assertTrue("105 in 105,205", DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("include", "205,105");
        Assert::assertTrue("105 in 205,105", DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("include", "1050,205");
        Assert::assertTrue("105 not in 1050,205", !DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("include", "50,1050");
        Assert::assertTrue("105 not in 50,1050", !DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("include", "827004,827008,827104,827108,827106,828043,828045,828047");
        Assert::assertTrue("827004", DecoderFile::isIncluded(e, "827004", "model", "family", "", ""), __FILE__, __LINE__);
        Assert::assertTrue("Not 827005", !DecoderFile::isIncluded(e, "827005", "model", "family", "", ""), __FILE__, __LINE__);
        Assert::assertTrue("827108", DecoderFile::isIncluded(e, "827108", "model", "family", "", ""), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testIncludeCheckRippleDown() {
        QDomElement e;

        // with nothing in element
        e = doc.createElement("Test");
        Assert::assertTrue("1 in 1,2", DecoderFile::isIncluded(e, "1", "model", "family", "1,2", ""), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2", DecoderFile::isIncluded(e, "2", "model", "family", "1,2", ""), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", !DecoderFile::isIncluded(e, "3", "model", "family", "1,2", ""), __FILE__, __LINE__);

        // with irrelevant element
        (e = doc.createElement("Test")).setAttribute("include", "4,5");
        Assert::assertTrue("1 in 1,2", DecoderFile::isIncluded(e, "1", "model", "family", "1,2", ""), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2", DecoderFile::isIncluded(e, "2", "model", "family", "1,2", ""), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", !DecoderFile::isIncluded(e, "3", "model", "family", "1,2", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("include", "105,205");
        Assert::assertTrue("105 in 105,205", DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        e = doc.createElement("Test");
        Assert::assertTrue("105 in 205,105", DecoderFile::isIncluded(e, "105", "model", "family", "205,105", ""), __FILE__, __LINE__);
        (e = doc.createElement("Test")).setAttribute("include", "1205,1105");
        Assert::assertTrue("105 in 205,105", DecoderFile::isIncluded(e, "105", "model", "family", "205,105", ""), __FILE__, __LINE__);

        e = doc.createElement("Test");
        Assert::assertTrue("105 not in 1050,205", !DecoderFile::isIncluded(e, "105", "model", "family", "1050,205", ""), __FILE__, __LINE__);
        (e = doc.createElement("Test")).setAttribute("include", "222,333");
        Assert::assertTrue("105 not in 1050,205", !DecoderFile::isIncluded(e, "105", "model", "family", "1050,205", ""), __FILE__, __LINE__);

        e = doc.createElement("Test");
        Assert::assertTrue("105 not in 50,1050", !DecoderFile::isIncluded(e, "105", "model", "family", "50,1050", ""), __FILE__, __LINE__);

        e = doc.createElement("Test");
        Assert::assertTrue("827004", DecoderFile::isIncluded(e, "827004", "model", "family", "827004,827008,827104,827108,827106,828043,828045,828047", ""), __FILE__, __LINE__);
        Assert::assertTrue("Not 827005", !DecoderFile::isIncluded(e, "827005", "model", "family", "827004,827008,827104,827108,827106,828043,828045,828047", ""), __FILE__, __LINE__);
        Assert::assertTrue("827108", DecoderFile::isIncluded(e, "827108", "model", "family", "827004,827008,827104,827108,827106,828043,828045,828047", ""), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testIncludeCheckModel() {
        QDomElement e;

        // with nothing in element
        e = doc.createElement("Test");
        Assert::assertTrue("1 in model", DecoderFile::isIncluded(e, "1", "model", "family", "model", ""), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2,model", DecoderFile::isIncluded(e, "2", "model", "family", "1,2,model", ""), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", !DecoderFile::isIncluded(e, "3", "model", "family", "1,2", ""), __FILE__, __LINE__);

        // with irrelevant element
        (e = doc.createElement("Test")).setAttribute("include", "4,5");
        Assert::assertTrue("1 in model", DecoderFile::isIncluded(e, "1", "model", "family", "model", ""), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2,model", DecoderFile::isIncluded(e, "2", "model", "family", "1,2,model", ""), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", !DecoderFile::isIncluded(e, "3", "model", "family", "1,2", ""), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testExcludeCheck() {
        QDomElement e;
        // test some examples
        e = doc.createElement("Test");
        Assert::assertTrue("1 in null", DecoderFile::isIncluded(e, "1", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("exclude", "1,2");
        Assert::assertTrue("1 in 1,2", !DecoderFile::isIncluded(e, "1", "model", "family", "", ""), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2", !DecoderFile::isIncluded(e, "2", "model", "family", "", ""), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", DecoderFile::isIncluded(e, "3", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("exclude", "105,205");
        Assert::assertTrue("105 in 105,205", !DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("exclude", "205,105");
        Assert::assertTrue("105 in 205,105", !DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("exclude", "1050,205");
        Assert::assertTrue("105 not in 1050,205", DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("exclude", "50,1050");
        Assert::assertTrue("105 not in 50,1050", DecoderFile::isIncluded(e, "105", "model", "family", "", ""), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("exclude", "827004,827008,827104,827108,827106,828043,828045,828047");
        Assert::assertTrue("827004", !DecoderFile::isIncluded(e, "827004", "model", "family", "", ""), __FILE__, __LINE__);
        Assert::assertTrue("Not 827005", DecoderFile::isIncluded(e, "827005", "model", "family", "", ""), __FILE__, __LINE__);
        Assert::assertTrue("827108", !DecoderFile::isIncluded(e, "827108", "model", "family", "", ""), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testExcludeCheckRippleDown() {
        QDomElement e;

        e = doc.createElement("Test");
        Assert::assertTrue("1 in model", !DecoderFile::isIncluded(e, "1", "model", "family", "", "model"), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2,model", !DecoderFile::isIncluded(e, "2", "model", "family", "", "1,2,model"), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2,model", !DecoderFile::isIncluded(e, "3", "model", "family", "", "1,2,model"), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("exclude", "4,5");
        Assert::assertTrue("1 in 1,2", !DecoderFile::isIncluded(e, "1", "model", "family", "", "1,2"), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2", !DecoderFile::isIncluded(e, "2", "model", "family", "", "1,2"), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", DecoderFile::isIncluded(e, "3", "model", "family", "", "1,2"), __FILE__, __LINE__);

        e = doc.createElement("Test");
        Assert::assertTrue("105 in 105,205", !DecoderFile::isIncluded(e, "105", "model", "family", "", "105,205"), __FILE__, __LINE__);
        e = doc.createElement("Test");
        e.setAttribute("exclude", "305,405");
        Assert::assertTrue("105 in 105,205", !DecoderFile::isIncluded(e, "105", "model", "family", "", "105,205"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testExcludeCheckModel() {
        QDomElement e;

        e = doc.createElement("Test");
        Assert::assertTrue("1 in model", !DecoderFile::isIncluded(e, "1", "model", "family", "", "1,2"), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2,model", !DecoderFile::isIncluded(e, "2", "model", "family", "", "1,2"), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", DecoderFile::isIncluded(e, "3", "model", "family", "", "1,2"), __FILE__, __LINE__);

        (e = doc.createElement("Test")).setAttribute("exclude", "4,5");
        Assert::assertTrue("1 in model", !DecoderFile::isIncluded(e, "1", "model", "family", "", "1,2"), __FILE__, __LINE__);
        Assert::assertTrue("2 in 1,2,model", !DecoderFile::isIncluded(e, "2", "model", "family", "", "1,2"), __FILE__, __LINE__);
        Assert::assertTrue("3 in 1,2", DecoderFile::isIncluded(e, "3", "model", "family", "", "1,2"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testMinOut() {
        setupDecoder();

        // this test should probably be done in terms of a test class instead of the real one...
        JLabel* progStatus = new JLabel(" OK ");
        CvTableModel* cvModel = new CvTableModel(progStatus, p);
        VariableTableModel* variableModel = new VariableTableModel(progStatus,
                QStringList()<<"Name"<< "Value", cvModel);
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "23", "24",
                "family", "filename", 16, 3, QDomElement());

        d->loadVariableModel(decoder, variableModel);
        Assert::assertEquals("read rows ", 2, variableModel->getRowCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void DecoderFileTest::testMinFn() {
        setupDecoder();

        // this test should probably be done in terms of a test class instead of the real one...
        JLabel* progStatus = new JLabel(" OK ");
        CvTableModel* cvModel = new CvTableModel(progStatus, p);
        VariableTableModel* variableModel = new VariableTableModel(progStatus,
                QStringList()<<"Name"<< "Value", cvModel);
        DecoderFile*  d = new DecoderFile("mfg", "mfgID", "model", "23", "24",
                "family", "filename", 3, 16, QDomElement());

        d->loadVariableModel(decoder, variableModel);
        Assert::assertEquals("read rows ", 2, variableModel->getRowCount(), __FILE__, __LINE__);
    }

    // provide a test document in the above static variables
    /*public*/ void DecoderFileTest::setupDecoder() {
        // create a JDOM tree with just some elements
     QDomDocumentType type = QDomDocumentType();
     type.setPrefix("decoder-config");
     type.setNodeValue("decoder-config.dtd");
     doc = QDomDocument(type);
        root = doc.createElement("decoder-config");
//        doc = new Document(root);
//        doc.setDocType(new DocType("decoder-config", "decoder-config.dtd"));
        doc.appendChild(root);

        // add some elements
        QDomElement e1, e2, e3, e4, e5, e6, e7;
        root.appendChild(decoder = doc.createElement("decoder"));
                decoder.appendChild(e1 = doc.createElement("family"));
                        e1.setAttribute("family", "DH142 etc");
                        e1.setAttribute("mfg", "Digitrax");
                        e1.setAttribute("defnVersion", "242");
                        e1.setAttribute("comment", "DH142 decoder: FX, transponding");
//                )
                decoder.appendChild(e2 = doc.createElement("programming"));
                        e2.setAttribute("direct", "byteOnly");
                        e2.setAttribute("paged", "yes");
                        e2.setAttribute("register", "yes");
                        e2.setAttribute("ops", "yes");
//                )
                decoder.appendChild(e3 = doc.createElement("variables"));
                        e3.appendChild(e4 = doc.createElement("variable"));
                                e4.setAttribute("label", "Address");
                                e4.setAttribute("CV", "1");
                                e4.setAttribute("minFn", "4");
                                e4.setAttribute("mask", "VVVVVVVV");
                                e4.setAttribute("readOnly", "no");
                                e4.appendChild(e5 = doc.createElement("decVal"));
                                        e5.setAttribute("max", "127");
//                                )
//                        )
                        e3.appendChild(e4 = doc.createElement("variable"));
                                e4.setAttribute("label", "Acceleration rate");
                                e4.setAttribute("CV", "3");
                                e4.setAttribute("minOut", "2");
                                e4.setAttribute("mask", "VVVVVVVV");
                                e4.setAttribute("readOnly", "no");
                                e4.appendChild(e5 = doc.createElement("decVal"));
                                        e5.setAttribute("max", "127");
//                                )
//                        )
                        e3.appendChild(e4 = doc.createElement("variable"));
                                e4.setAttribute("label", "Normal direction of motion");
                                e4.setAttribute("CV", "29");
                                e4.setAttribute("minFn", "2");
                                e4.setAttribute("minOut", "5");
                                e4.setAttribute("mask", "XXXXXXXV");
                                e4.setAttribute("readOnly", "no");
                                e4.appendChild(e5 = doc.createElement("enumVal"));
                                        e5.appendChild(e6 = doc.createElement("enumChoice"));
                                                e6.setAttribute("choice", "forward");
//                                        )
                                        e5.appendChild(e7 = doc.createElement("enumChoice"));
                                                e7.setAttribute("choice", "reverse");
//                                        )
//                                )
//                        )
//                )
//        ); // end of adding contents

        return;
    }

    //@Before
    /*public*/ void DecoderFileTest::setUp() {
        JUnitUtil::setUp();
    }

    //@After
    /*public*/ void DecoderFileTest::tearDown() {
        JUnitUtil::tearDown();
    }
