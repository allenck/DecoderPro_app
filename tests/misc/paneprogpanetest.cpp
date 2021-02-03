#include "paneprogpanetest.h"
#include "loggerfactory.h"
#include "junitutil.h"
#include "assert1.h"
#include "progdebugger.h"
#include "paneprogframe.h"
#include "rosterentry.h"
#include "cvtablemodel.h"
#include "variabletablemodel.h"
#include "assume.h"

PaneProgPaneTest::PaneProgPaneTest(QObject *parent) : QObject(parent)
{
 root = QDomElement();
 pane1 = QDomElement();
 pane2 = QDomElement();
 pane3 = QDomElement();
 doc = QDomDocument();
 p = new ProgDebugger();

}

/**
 * @author	Bob Jacobsen Copyright 2001, 2002, 2003, 2004
 */
///*public*/ class PaneProgPaneTest {


// test creating columns in a pane
//@Test
/*public*/ void PaneProgPaneTest::testColumn() {
//    Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    setupDoc();
    PaneProgFrameO1* pFrame = new PaneProgFrameO1(nullptr, new RosterEntry(),
            "test frame", "programmers/Basic.xml",
            p, false);
//    {
//        // dummy implementations
//        @Override
//        protected JPanel getModePane() {
//            return null;
//        }
//    };
    CvTableModel* cvModel = new CvTableModel(new QLabel(), p);
    log->debug("CvTableModel ctor complete");
    QStringList args = QStringList() << "CV" << "Name";
    VariableTableModel* varModel = new VariableTableModel(nullptr, args, cvModel);
    log->debug("VariableTableModel ctor complete");

    // create test object with special implementation of the newColumn(String) operation
    colCount = 0;
    PaneProgPaneO1* pane = new PaneProgPaneO1(pFrame, "name", pane1, cvModel, varModel, QDomElement(), nullptr, false, this);
//    {
//        @Override
//        /*public*/ JPanel newColumn(QDomElement e, boolean a, QDomElement el) {
//            colCount++;
//            return new JPanel();
//        }
//    };
    Assert::assertNotNull("exists", pane, __FILE__, __LINE__);
    Assert::assertEquals("column count", 2, colCount, __FILE__, __LINE__);
    JUnitUtil::dispose(pFrame);
}
//@Override
/*protected*/ JPanel *PaneProgFrameO1::getModePane()
{
    return nullptr;
}


/*public*/ JPanel *PaneProgPaneO1::newColumn(QDomElement e, bool a, QDomElement el) {
    test->colCount++;
    return new JPanel();
}

// test specifying variables in columns
//@Test
/*public*/ void PaneProgPaneTest::testVariables() {
//    Assume::assumeFalse(GraphicsEnvironment.isHeadless());
    setupDoc();  // make sure XML document is ready
    PaneProgFrameO1* pFrame = new PaneProgFrameO1(nullptr, new RosterEntry(),
            "test frame", "programmers/Basic.xml",
            p, false);
//    {
//        // dummy implementations
//        @Override
//        protected JPanel getModePane() {
//            return null;
//        }
//    };
    CvTableModel* cvModel = new CvTableModel(new QLabel(), p);
    QStringList args = QStringList() << "CV" << "Name";
    VariableTableModel* varModel = new VariableTableModel(nullptr, args, cvModel);
    log->debug("VariableTableModel ctor complete");

    // create test object with special implementation of the newVariable(String) operation
    varCount = 0;
    PaneProgPaneO2* pane = new PaneProgPaneO2(pFrame, "name", pane1, cvModel, varModel, QDomElement(), nullptr, this, nullptr);
//    {
//        @Override
//        /*public*/ void newVariable(QDomElement e, JComponent p, GridBagLayout g, GridBagConstraints c, boolean a) {
//            varCount++;
//        }
//    };
    Assert::assertNotNull("exists", pane, __FILE__, __LINE__);
    Assert::assertEquals("variable defn count", 7, varCount, __FILE__, __LINE__);
    JUnitUtil::dispose(pFrame);
}

//@Override
/*public*/ void PaneProgPaneO2::newVariable(QDomElement /*e*/, JPanel* /*p*/,
        GridBagLayout * /*g*/, GridBagConstraints* /*c*/, bool /*a*/)
{
    test->varCount++;
}

// test storage of programming info in list
//@Test
/*public*/ void PaneProgPaneTest::testVarListFill() {
//    Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    setupDoc();  // make sure XML document is ready
    PaneProgFrame* pFrame = new PaneProgFrameO1(nullptr, new RosterEntry(),
            "test frame", "programmers/Basic.xml",
            p, false);
//    {
//        // dummy implementations
//        @Override
//        protected JPanel getModePane() {
//            return null;
//        }
//    };

    CvTableModel* cvModel = new CvTableModel(new QLabel(), p);
    QStringList args = QStringList() << "CV"<< "Name";
    VariableTableModel* varModel = new VariableTableModel(nullptr, args, cvModel);
    log->debug("VariableTableModel ctor complete");
    // have to add a couple of defined variables
    doc = QDomDocument();
    QDomElement el0 = doc.createElement("variable");
            el0.setAttribute("CV", "17");
            el0.setAttribute("readOnly", "no");
            el0.setAttribute("mask", "VVVVVVVV");
            el0.setAttribute("label", "Start voltage");
            el0.appendChild(doc.createElement("longAddressVal"));
    log->debug("First QDomElement created");
    varModel->setRow(0, el0);
    log->debug("First QDomElement loaded");
    QDomElement el1 = doc.createElement("variable");
            el1.setAttribute("CV", "17");
            el1.setAttribute("readOnly", "no");
            el1.setAttribute("mask", "VVVVVVVV");
            el1.setAttribute("label", "Primary Address");
            el1.appendChild(doc.createElement("decVal"));
    log->debug("Second QDomElement created");
    varModel->setRow(1, el1);
    log->debug("Two elements loaded");

    // test by invoking
    PaneProgPane* pane = new PaneProgPane(pFrame, "name", pane1, cvModel, varModel, QDomElement(), nullptr);
    qApp->processEvents();
    Assert::assertEquals("variable list length", 2, pane->varList->size(), __FILE__, __LINE__);
    Assert::assertEquals("1st variable index ", (1), pane->varList->at(0), __FILE__, __LINE__);
    Assert::assertEquals("2nd variable index ", (0), pane->varList->at(1), __FILE__, __LINE__);
    JUnitUtil::dispose(pFrame);
}

// test storage of programming info in list
//@Test
/*public*/ void PaneProgPaneTest::testPaneRead() {
//    Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    log->debug("testPaneRead starts");
    // initialize the system
    setupDoc();  // make sure XML document is ready

    PaneProgFrame* pFrame = new PaneProgFrame(nullptr, new RosterEntry(),
            "test frame", "programmers/Basic.xml",
            p, false);
//    {
//        // dummy implementations
//        @Override
//        protected JPanel getModePane() {
//            return null;
//        }
//    };

    CvTableModel* cvModel = new CvTableModel(new QLabel(), p);
    QStringList args = QStringList() << "CV"<< "Name";
    VariableTableModel* varModel = new VariableTableModel(nullptr, args, cvModel);
    log->debug("VariableTableModel ctor complete");
    // have to add a couple of defined variables
    doc = QDomDocument();
    QDomElement el0 = doc.createElement("variable");
            el0.setAttribute("CV", "2");
            el0.setAttribute("readOnly", "no");
            el0.setAttribute("mask", "VVVVVVVV");
            el0.setAttribute("label", "Start voltage");
            el0.appendChild(doc.createElement("decVal"));
    QDomElement el1 = doc.createElement("variable");
            el1.setAttribute("CV", "3");
            el1.setAttribute("readOnly", "no");
            el1.setAttribute("mask", "VVVVVVVV");
            el1.setAttribute("label", "Primary Address");
            el1.appendChild(doc.createElement("decVal"));
    varModel->setRow(0, el0);
    varModel->setRow(1, el1);

    PaneProgPane* progPane = new PaneProgPane(pFrame, "name", pane1, cvModel, varModel, QDomElement(), nullptr);
    qApp->processEvents();

    p->resetCv(2, 20);
    p->resetCv(3, 30);

    // test by invoking
    progPane->readAllButton->setSelected(true);

    // wait for reply (normally, done by callback; will check that later)
//    JUnitUtil::waitFor(() -> {
//        return !progPane->isBusy();
//    }, "progPane->isBusy");
    ReleaseUntilO14* r14 = new ReleaseUntilO14(progPane);
    JUnitUtil::waitFor(r14,  "progPane->isBusy", __FILE__, __LINE__);
    Assert::assertEquals("CV 2 value ", "20", varModel->getValString(0), __FILE__, __LINE__);
    Assert::assertEquals("CV 3 value ", "30", varModel->getValString(1), __FILE__, __LINE__);

    log->debug("testPaneRead ends ok");
    JUnitUtil::dispose(pFrame);
}

//@Test
/*public*/ void PaneProgPaneTest::testPaneWrite() {
//    Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    log->debug("testPaneWrite starts");
    // initialize the system
    setupDoc();  // make sure XML document is ready

    PaneProgFrame* pFrame = new PaneProgFrame(nullptr, new RosterEntry(),
            "test frame", "programmers/Basic.xml",
            p, false);
//    {
//        // dummy implementations
//        @Override
//        protected JPanel getModePane() {
//            return null;
//        }
//    };
    CvTableModel* cvModel = new CvTableModel(new QLabel(), p);
    QStringList args = QStringList() << "CV"<< "Name";
    VariableTableModel* varModel = new VariableTableModel(nullptr, args, cvModel);
    log->debug("VariableTableModel ctor complete");
    // have to add a couple of defined variables
    doc = QDomDocument();
    QDomElement el0 = doc.createElement("variable");
            el0.setAttribute("CV", "2");
            el0.setAttribute("readOnly", "no");
            el0.setAttribute("mask", "VVVVVVVV");
            el0.setAttribute("default", "20");
            el0.setAttribute("label", "Start voltage");
            el0.appendChild(doc.createElement("decVal"));
    QDomElement el1 = doc.createElement("variable");
            el1 .setAttribute("CV", "3");
            el1 .setAttribute("readOnly", "no");
            el1 .setAttribute("mask", "VVVVVVVV");
            el1 .setAttribute("default", "30");
            el1 .setAttribute("label", "Primary Address");
            el1 .appendChild(doc.createElement("decVal"));
    varModel->setRow(0, el0);
    varModel->setRow(1, el1);
    log->debug("Two elements loaded");

    PaneProgPane* progPane = new PaneProgPane(pFrame, "name", pane1, cvModel, varModel, QDomElement(), nullptr);
    qApp->processEvents();

    p->resetCv(2, -1);
    p->resetCv(3, -1);

    // test by invoking
    progPane->writeAllButton->setSelected(true);

    // wait for reply (normally, done by callback; will check that later)
//    JUnitUtil::waitFor(() -> {
//        return !progPane->isBusy();
//    }, "progPane->isBusy");
    ReleaseUntilO14* r14 = new ReleaseUntilO14(progPane);
    JUnitUtil::waitFor(r14,  "progPane->isBusy", __FILE__, __LINE__);

    Assert::assertEquals("CV 2 value ", 20, p->getCvVal(2), __FILE__, __LINE__);
    Assert::assertEquals("CV 3 value ", 30, p->getCvVal(3), __FILE__, __LINE__);

    log->debug("testPaneWrite ends ok");
    JUnitUtil::dispose(pFrame);
}

// test counting of read operations needed
//@Test
/*public*/ void PaneProgPaneTest::testPaneReadOpCount() {
//    Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    log->debug("testPaneReadOpCount starts");
    // initialize the system
    setupDoc();  // make sure XML document is ready

    PaneProgFrame* pFrame = new PaneProgFrame(nullptr, new RosterEntry(),
            "test frame", "programmers/Basic.xml",
            p, false);
//    {
//        // dummy implementations
//        @Override
//        protected JPanel getModePane() {
//            return null;
//        }
//    };
    CvTableModel* cvModel = new CvTableModel(new QLabel(), p);
    QStringList args = QStringList() << "CV"<< "Name";
    VariableTableModel* varModel = new VariableTableModel(nullptr, args, cvModel);

    // have to add a couple of defined variables
    int row = 0;

    // note these +have+ to be on this pane, e.g. named in setupDoc
    doc = QDomDocument();
    QDomElement el0 = doc.createElement("variable");
            el0.setAttribute("CV", "1");
            el0.setAttribute("readOnly", "no");
            el0.setAttribute("mask", "VVVVVVVV");
            el0.setAttribute("label", "Start voltage");
            el0.appendChild(doc.createElement("decVal"));
    varModel->setRow(row++, el0);

    QDomElement el1 = doc.createElement("variable");
            el1.setAttribute("CV", "1");
            el1.setAttribute("readOnly", "no");
            el1.setAttribute("mask", "VVVVVVVV");
            el1.setAttribute("label", "Primary Address");
            el1.appendChild(doc.createElement("decVal"));
    varModel->setRow(row++, el1);

    QDomElement el2 = doc.createElement("variable");
            el2.setAttribute("CV", "67");
            el2.setAttribute("label", "Normal direction of motion");
            el2.setAttribute("readOnly", "no");
            el2.setAttribute("mask", "VVVVVVVV");
            el2.appendChild(doc.createElement("speedTableVal"));
    varModel->setRow(row++, el2);

    QDomElement el3 = doc.createElement("variable");
            el3.setAttribute("CV", "68");
            el3.setAttribute("readOnly", "no");
            el3.setAttribute("mask", "VVVVVVVV");
            el3.setAttribute("label", "Address");
            el3.appendChild(doc.createElement("decVal"));
    varModel->setRow(row++, el3);

    PaneProgPane* progPane = new PaneProgPane(pFrame, "name", pane1, cvModel, varModel, QDomElement(), nullptr);
    qApp->processEvents();

    // start actual testing
    Assert::assertEquals("number of all CVs to read ", 29, progPane->countOpsNeeded(true, false), __FILE__, __LINE__);
    Assert::assertEquals("number of all CVs to write ", 29, progPane->countOpsNeeded(false, false), __FILE__, __LINE__);

    Assert::assertEquals("number of changed CVs to read ", 0, progPane->countOpsNeeded(true, true), __FILE__, __LINE__);
    Assert::assertEquals("number of changed CVs to write ", 0, progPane->countOpsNeeded(false, true), __FILE__, __LINE__);

    // mark some as needing to be written
    (cvModel->allCvMap()->value("1"))->setValue(12);

    Assert::assertEquals("modified all CVs to read ", 29, progPane->countOpsNeeded(true, false), __FILE__, __LINE__);
    Assert::assertEquals("modified all CVs to write ", 29, progPane->countOpsNeeded(false, false), __FILE__, __LINE__);

    Assert::assertEquals("modified changed CVs to read ", 1, progPane->countOpsNeeded(true, true), __FILE__, __LINE__);
    Assert::assertEquals("modified changed CVs to write ", 1, progPane->countOpsNeeded(false, true), __FILE__, __LINE__);

    (cvModel->allCvMap()->value("69"))->setValue(12);
    // careful - might change more than one CV!

    Assert::assertEquals("spdtbl all CVs to read ", 29, progPane->countOpsNeeded(true, false), __FILE__, __LINE__);
    Assert::assertEquals("spdtbl all CVs to write ", 29, progPane->countOpsNeeded(false, false), __FILE__, __LINE__);

    Assert::assertEquals("spdtbl changed CVs to read ", 2, progPane->countOpsNeeded(true, true), __FILE__, __LINE__);
    Assert::assertEquals("spdtbl changed CVs to write ", 2, progPane->countOpsNeeded(false, true), __FILE__, __LINE__);

    log->debug("testPaneReadOpCount ends ok");
    JUnitUtil::dispose(pFrame);
}

// static variables for internal classes to report their interpretations
/*static*/ QString PaneProgPaneTest::result = "";
/*static*/ int PaneProgPaneTest::colCount = -1;
/*static*/ int PaneProgPaneTest::varCount = -1;


// provide a test document in the above static variables
void PaneProgPaneTest::setupDoc() {
    // create a JDOM tree with just some elements
 QDomDocumentType type = QDomDocumentType();
 type.setPrefix("programmer-config");
 type.setNodeValue("programmer-config.dtd");
    doc = QDomDocument(type);
    root = doc.createElement("programmer-config");
    //doc = new Document(root);
    doc.appendChild(root);
   // doc.setDocType(new DocType("programmer-config", "programmer-config.dtd"));

    // add some elements
    QDomElement e1, e2, e3, e4, e5, e6, e7;
    root.appendChild(e1 = doc.createElement("programmer"));
            e1.appendChild(pane1 = doc.createElement("pane"));
              pane1.setAttribute("name", "Basic");
                    pane1.appendChild(e2 = doc.createElement("column"));
                            e2.appendChild(e3 = doc.createElement("display"));
                                    e3.setAttribute("item", "Primary Address");
//                            );
                            e2.appendChild(e3 = doc.createElement("display"));
                                    e3.setAttribute("item", "Start voltage");
//                            );
                            e2.appendChild(e3 = doc.createElement("display"));
                                    e3.setAttribute("item", "Normal direction of motion");
//                            );
//                    );
                    pane1.appendChild(e3 =doc.createElement("column"));
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Address");
//                            ));
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Normal direction of motion");
//                            );
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Normal direction of motion");
                                    e4.setAttribute("format", "checkbox");
//                            );
                            e3.appendChild(e5 = doc.createElement("display"));
                                    e5.setAttribute("item", "Normal direction of motion");
                                    e5.setAttribute("format", "radiobuttons");
//                            );
//                    )
//            )
            e1.appendChild(pane2 = doc.createElement("pane"));
                    pane2.setAttribute("name", "CV");
                    pane2.appendChild(doc.createElement("column")
                            .appendChild(doc.createElement("cvtable")));
//                    )
//            );
            e1.appendChild(pane3 = doc.createElement("pane"));
                    pane3.setAttribute("name", "Other");
                    pane3.appendChild(e6 = doc.createElement("column"));
                            e6.appendChild(e7 = doc.createElement("display"));
                                    e7.setAttribute("item", "Address");
//                            );
                            e6.appendChild(e7 = doc.createElement("display"));
                                    e7.setAttribute("item", "Normal direction of motion");
//                            )
//                    )
//            )
//    ); // end of adding contents

    log->debug("setupDoc complete");
}

//@Before
/*public*/ void PaneProgPaneTest::setUp() {
    JUnitUtil::setUp();
    JUnitUtil::resetProfileManager();
    JUnitUtil::initRosterConfigManager();
}

//@After
/*public*/ void PaneProgPaneTest::tearDown() {
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* PaneProgPaneTest::log = LoggerFactory::getLogger("PaneProgPaneTest");

