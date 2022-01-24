#include "paneprogframetest.h"
#include "junitutil.h"
#include "assert1.h"
#include "progdebugger.h"
#include "decoderfiletest.h"
#include "decoderfile.h"
#include "rosterentry.h"

PaneProgFrameTest::PaneProgFrameTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for PaneProgFrame.
 *
 * @author	Bob Jacobsen
 */
// /*public*/ class PaneProgFrameTest {

// test creating a pane in config file
//@Test
/*public*/ void PaneProgFrameTest::testPane() {
//    Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    setupDoc();

    // create test object
    result = "";

//    PaneProgFrame p = new PaneProgFrame(null, new RosterEntry(),
//            "test frame", "programmers/Basic.xml",
//            new jmri.progdebugger.ProgDebugger(), false) {
//        // dummy implementations
//        @Override
//        protected JPanel getModePane() {
//            return new JPanel();
//        }
//    };
        PaneProgFrameO2* p = new PaneProgFrameO2(nullptr, new RosterEntry(),
                "test frame", "programmers/Basic.xml",
                new ProgDebugger(), false);
    // invoke
    result = "";
    p->readConfig(root, new RosterEntry());
    Assert::assertEquals("paneList length ", 4, p->paneList.size(), __FILE__, __LINE__);
    // three panes in root, plus roster entry pane

    JFrame* f = JmriJFrame::getFrame("test frame");
    Assert::assertTrue("found frame", f != nullptr, __FILE__, __LINE__);
    JUnitUtil::dispose(f);
}
//@Override
/*protected*/ JPanel *PaneProgFrameO2::getModePane()
{
    return new JPanel();
}

//@Override
/*protected*/ JPanel *PaneProgFrameO3::getModePane()
{
    return nullptr;
}


// show me the specially-created frame
//@Test
/*public*/ void PaneProgFrameTest::testFrame() {
//    Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    setupDoc();
    PaneProgFrameO3* p = new PaneProgFrameO3(nullptr, new RosterEntry(),
            "test frame", "programmers/Basic.xml",
            new ProgDebugger(), false);
//    {
//        // dummy implementations
//        @Override
//        protected JPanel getModePane() {
//            return null;
//        }
//    };

    // ugly, temporary way to load the decoder info
    DecoderFileTest* t = new DecoderFileTest();
    t->setupDecoder();
    DecoderFile* df = new DecoderFile();  // used as a temporary
    df->loadVariableModel(t->decoder, p->variableModel);

    p->readConfig(root, new RosterEntry());
    p->pack();
    p->setVisible(true);

    JFrame* f = JmriJFrame::getFrame("test frame");
    Assert::assertTrue("found frame", f != nullptr, __FILE__, __LINE__);
    JUnitUtil::dispose(f);
}

// static variables for internal classes to report their interpretations
/*static*/ QString PaneProgFrameTest::result = "";
/*static*/ int PaneProgFrameTest::colCount = -1;
/*static*/ int PaneProgFrameTest::varCount = -1;


// provide a test document in the above static variables
void PaneProgFrameTest::setupDoc() {
    // create a JDOM tree with just some elements
 QDomDocumentType type = QDomDocumentType();
 type.setPrefix("programmer-config");
 type.setNodeValue("programmer-config.dtd");
 doc = QDomDocument(type);
    root = doc.createElement("programmer-config");
    doc.appendChild(root);
//    doc = new Document(root);
//    doc.setDocType(new DocType("programmer-config", "programmer-config.dtd"));

    // add some elements
    QDomElement e1,e2,e3,e4,e5,e6;
    root.appendChild(e1 =doc.createElement("programmer"));
            e1.setAttribute("showFnLanelPane", "yes");
            e1.setAttribute("showRosterMediaPane", "yes");
            e1.appendChild(e2 = doc.createElement("pane"));
                    e2.setAttribute("name", "Basic");
                    e2.appendChild(e3 =doc.createElement("column"));
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Address");
//                            )
                            e3.appendChild(e4 =doc.createElement("display"));
                                    e4.setAttribute("item", "Start voltage");
//                            )
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Normal direction of motion");
//                            )
//                    )
                    e2.appendChild(e3 = doc.createElement("column"));
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Address");
//                            )
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Normal direction of motion");
//                            )
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Normal direction of motion");
                                    e4.setAttribute("format", "checkbox");
//                            )
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Normal direction of motion");
                                    e4.setAttribute("format", "radiobuttons");
//                            )
//                    )
//            )
            e1.appendChild(e2 = doc.createElement("pane"));
                    e2.setAttribute("name", "CV");
                    e2.appendChild(e3 = doc.createElement("column"));
                            e3.appendChild(doc.createElement("cvtable"));
//                    )
//            )
            e1.appendChild(e2 = doc.createElement("pane"));
                    e2.setAttribute("name", "Other");
                    e2.appendChild(e3 = doc.createElement("column"));
                            e3.appendChild(e4 = doc.createElement("display"));
                                    e4.setAttribute("item", "Address");
//                            )
                            e3.appendChild(e4 =doc.createElement("display"));
                                    e4.setAttribute("item", "Normal direction of motion");
//                            )
//                    )
//            )
//    ); // end of adding contents
}

//@Before
/*public*/ void PaneProgFrameTest::setUp() {
    JUnitUtil::setUp();
    JUnitUtil::resetProfileManager();
    JUnitUtil::initRosterConfigManager();
}

//@After
/*public*/ void PaneProgFrameTest::tearDown() {
    JUnitUtil::tearDown();
}
