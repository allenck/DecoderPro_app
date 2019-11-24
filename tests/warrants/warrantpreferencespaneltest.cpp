#include "warrantpreferencespaneltest.h"
#include "junitutil.h"
#include "assert1.h"
#include "warrantpreferencespanel.h"

WarrantPreferencesPanelTest::WarrantPreferencesPanelTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
// /*public*/ class WarrantPreferencesPanelTest {

    //@Test
    /*public*/ void WarrantPreferencesPanelTest::testCTor() {
        WarrantPreferencesPanel* t = new WarrantPreferencesPanel();
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
        t->show();
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void WarrantPreferencesPanelTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
    }

    //@After
    /*public*/ void WarrantPreferencesPanelTest::tearDown() {
        JUnitUtil::tearDown();
    }
