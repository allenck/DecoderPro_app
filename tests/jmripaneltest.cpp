#include "jmripaneltest.h"
#include "junitutil.h"
#include "assert1.h"

JmriPanelTest::JmriPanelTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
///*public*/ class JmriPanelTest {


    //@Test
    /*public*/ void JmriPanelTest::testCTor() {
        Assert::assertNotNull("exists", panel, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void JmriPanelTest::testInitComponents() //throw (Exception)
    {
        // for now, just make sure there isn't an exception.
        panel->initComponents();
    }

    //@Test
    /*public*/ void JmriPanelTest::testGetHelpTarget(){
        Assert::assertEquals("help target", helpTarget, panel->getHelpTarget(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void JmriPanelTest::testGetTitle(){
        Assert::assertEquals("title", title, panel->getTitle(), __FILE__, __LINE__);
    }

    //@BeforeEach
    /*public*/ void JmriPanelTest::setUp() {
        JUnitUtil::setUp();
        panel = new JmriPanel();
        helpTarget = "package.jmri.util.swing.JmriPanel";
    }

    //@AfterEach
    /*public*/ void JmriPanelTest::tearDown() {
        if (panel!=nullptr) {
           panel->dispose();
        }
        panel = nullptr;
        helpTarget = "";
        title = "";
        JUnitUtil::tearDown();
    }
