#include "jmriuserpreferencesmanagertest.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "temporaryfolder.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"
#include <QDesktopWidget>
#include <QApplication>
#include "junitappender.h"
#include "joptionpane.h"
#include "appconfigbase.h"
#include "nullprofile.h"
#include "profilemanager.h"
#include "nodeidentity.h"
#include "vptr.h"

JmriUserPreferencesManagerTest::JmriUserPreferencesManagerTest(QObject *parent) : QObject(parent)
{
 //@Rule
 /*public*/ folder = new TemporaryFolder();
 strClass = "jmri.managers.JmriUserPreferencesManagerTest";
 qRegisterMetaType<JmriUserPreferencesManagerTest>("JmriUserPreferencesManagerTest");
}

/**
 * Tests for the jmri.managers.JmriUserPreferencesManager class.
 *
 * @author Bob Jacobsen Copyright 2009
 * @author Randall Wood Copyright 2017
 */
// /*public*/ class JmriUserPreferencesManagerTest {


/*private*/ /*final*/ /*static*/ Logger* JmriUserPreferencesManagerTest::log = LoggerFactory::getLogger("JmriUserPreferencesManagerTest");

//@Test
///*public*/ void JmriUserPreferencesManagerTest::testGetInstance() {
//    Assert::assertFalse(InstanceManager::containsDefault("UserPreferencesManager"), __FILE__, __LINE__);
//    Assert::assertNotNull(JmriUserPreferencesManager::getInstance(), __FILE__, __LINE__);
//    Assert::assertEquals(InstanceManager::getDefault("UserPreferencesManager"), JmriUserPreferencesManager::getInstance(), __FILE__, __LINE__);
//    Assert::assertEquals(JmriUserPreferencesManager::getDefault(), JmriUserPreferencesManager::getInstance(), __FILE__, __LINE__);
//}

//@Test
///*public*/ void JmriUserPreferencesManagerTest::testGetDefault() {
//    Assert::assertFalse(InstanceManager::containsDefault("UserPreferencesManager"), __FILE__, __LINE__);
//    Assert::assertNotNull(JmriUserPreferencesManager::getDefault(), __FILE__, __LINE__);
//    Assert::assertEquals(InstanceManager::getDefault("UserPreferencesManager"), JmriUserPreferencesManager::getDefault(), __FILE__, __LINE__);
//}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testAllowSave() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->isSaveAllowed(), __FILE__, __LINE__);
    m->setSaveAllowed(true);
    Assert::assertTrue(m->isSaveAllowed(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testDisallowSave() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    Assert::assertTrue(m->isSaveAllowed(), __FILE__, __LINE__);
    m->setSaveAllowed(false);
    Assert::assertFalse(m->isSaveAllowed(), __FILE__, __LINE__);
    m->setSaveAllowed(true);
    Assert::assertTrue(m->isSaveAllowed(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetSaveAllowed() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->isSaveAllowed(), __FILE__, __LINE__);
    m->setSaveAllowed(true);
    Assert::assertTrue(m->isSaveAllowed(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testIsSaveAllowed() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    Assert::assertTrue(m->isSaveAllowed(), __FILE__, __LINE__);
    m->setSaveAllowed(false);
    Assert::assertFalse(m->isSaveAllowed(), __FILE__, __LINE__);
    m->setSaveAllowed(true);;
    Assert::assertTrue(m->isSaveAllowed(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetScreen() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    QDesktopWidget* desktop = QApplication::desktop();
    QSize screen = desktop->screen()->size();
    Assert::assertEquals(screen, (new JmriUserPreferencesManager())->getScreen(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetSimplePreferenceState() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);

    Assert::assertFalse(m->getSimplePreferenceState("one"), __FILE__, __LINE__);

    m->setSimplePreferenceState("one", true);
    Assert::assertTrue(m->getSimplePreferenceState("one"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSimplePreferenceState("two"), __FILE__, __LINE__);

    m->setSimplePreferenceState("one", false);
    Assert::assertFalse(m->getSimplePreferenceState("one"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSimplePreferenceState("two"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetSimplePreferenceState() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);

    Assert::assertFalse(m->getSimplePreferenceState("one"), __FILE__, __LINE__);

    m->setSimplePreferenceState("one", true);
    Assert::assertTrue(m->getSimplePreferenceState("one"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSimplePreferenceState("two"), __FILE__, __LINE__);

    m->setSimplePreferenceState("one", false);
    Assert::assertFalse(m->getSimplePreferenceState("one"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSimplePreferenceState("two"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetSimplePreferenceStateList() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    // defaults to empty
    Assert::assertEquals(0, m->getSimplePreferenceStateList().size(), __FILE__, __LINE__);
    m->setSimplePreferenceState("test1", true);
    // setting a preference to true adds it
    Assert::assertEquals(1, m->getSimplePreferenceStateList().size(), __FILE__, __LINE__);
    m->setSimplePreferenceState("test1", false);
    // setting a preference to false removes it
    Assert::assertEquals(0, m->getSimplePreferenceStateList().size(), __FILE__, __LINE__);
    m->setSimplePreferenceState("test1", true);
    m->setSimplePreferenceState("test2", true);
    // setting a preference to true adds it
    Assert::assertEquals(2, m->getSimplePreferenceStateList().size(), __FILE__, __LINE__);
    m->setSimplePreferenceState("test2", true);
    // setting a preference to true twice adds it once
    Assert::assertEquals(2, m->getSimplePreferenceStateList().size(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetPreferenceState() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);

    Assert::assertFalse(m->getPreferenceState(strClass, "test1"), __FILE__, __LINE__);

    m->setPreferenceState(strClass, "test1", true);
    Assert::assertTrue(m->getPreferenceState(strClass, "test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPreferenceState(strClass, "test2"), __FILE__, __LINE__);

    m->setPreferenceState(strClass, "test1", false);
    Assert::assertFalse(m->getPreferenceState(strClass, "test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPreferenceState(strClass, "test2"), __FILE__, __LINE__);

    // non-existant class should not cause an error
    m->setPreferenceState("non.existant.class", "test1", true);
    JUnitAppender::assertWarnMessage("class name \"non.existant.class\" cannot be found, perhaps an expected plugin is missing?", __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetPreferenceState() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);

    Assert::assertFalse(m->getPreferenceState(strClass, "test1"), __FILE__, __LINE__);

    m->setPreferenceState(strClass, "test1", true);
    Assert::assertTrue(m->getPreferenceState(strClass, "test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPreferenceState(strClass, "test2"), __FILE__, __LINE__);

    m->setPreferenceState(strClass, "test1", false);
    Assert::assertFalse(m->getPreferenceState(strClass, "test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPreferenceState(strClass, "test2"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetPreferenceItemDetails() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->getPreferenceItemDescription(strClass, "test1"), __FILE__, __LINE__);
    m->setPreferenceItemDetails(strClass, "test1", "description1");
    Assert::assertEquals("description1", m->getPreferenceItemDescription(strClass, "test1"), __FILE__, __LINE__);
    m->setPreferenceItemDetails(strClass, "test1", QString());
    Assert::assertNull(m->getPreferenceItemDescription(strClass, "test1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetPreferenceList() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);

    Assert::assertTrue(m->getPreferenceList(strClass).isEmpty(), __FILE__, __LINE__);

    m->setPreferenceState(strClass, "test1", true);
    Assert::assertTrue(m->getPreferenceState(strClass, "test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPreferenceState(strClass, "test2"), __FILE__, __LINE__);

    m->setPreferenceState(strClass, "test1", false);
    Assert::assertFalse(m->getPreferenceState(strClass, "test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPreferenceState(strClass, "test2"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetPreferenceItemName() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);

    Assert::assertTrue(m->getPreferenceList(strClass).isEmpty(), __FILE__, __LINE__);

    Assert::assertNull(m->getPreferenceItemName(strClass, 0), __FILE__, __LINE__);

    m->setPreferenceState(strClass, "test1", true);
    Assert::assertEquals("test1", m->getPreferenceItemName(strClass, 0), __FILE__, __LINE__);
    Assert::assertNull("test2", m->getPreferenceItemName(strClass, 1), __FILE__, __LINE__);

    m->setPreferenceState(strClass, "test1", false);
    Assert::assertEquals("test1", m->getPreferenceItemName(strClass, 0), __FILE__, __LINE__);
    Assert::assertNull("test2", m->getPreferenceItemName(strClass, 1), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetPreferenceItemDescription() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->getPreferenceItemDescription(strClass, "test1"), __FILE__, __LINE__);
    m->setPreferenceItemDetails(strClass, "test1", "description1");
    Assert::assertEquals("description1", m->getPreferenceItemDescription(strClass, "test1"), __FILE__, __LINE__);
    m->setPreferenceItemDetails(strClass, "test1", QString());
    Assert::assertNull(m->getPreferenceItemDescription(strClass, "test1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetSessionPreferenceState() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->getSessionPreferenceState("test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSessionPreferenceState("test2"), __FILE__, __LINE__);
    m->setSessionPreferenceState("test1", true);
    Assert::assertTrue(m->getSessionPreferenceState("test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSessionPreferenceState("test2"), __FILE__, __LINE__);
    m->setSessionPreferenceState("test1", false);
    Assert::assertFalse(m->getSessionPreferenceState("test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSessionPreferenceState("test2"), __FILE__, __LINE__);
    m->setSessionPreferenceState("test2", true);
    Assert::assertFalse(m->getSessionPreferenceState("test1"), __FILE__, __LINE__);
    Assert::assertTrue(m->getSessionPreferenceState("test2"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetSessionPreferenceState() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->getSessionPreferenceState("test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSessionPreferenceState("test2"), __FILE__, __LINE__);
    m->setSessionPreferenceState("test1", true);
    Assert::assertTrue(m->getSessionPreferenceState("test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSessionPreferenceState("test2"), __FILE__, __LINE__);
    m->setSessionPreferenceState("test1", false);
    Assert::assertFalse(m->getSessionPreferenceState("test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getSessionPreferenceState("test2"), __FILE__, __LINE__);
    m->setSessionPreferenceState("test2", true);
    Assert::assertFalse(m->getSessionPreferenceState("test1"), __FILE__, __LINE__);
    Assert::assertTrue(m->getSessionPreferenceState("test2"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testShowInfoMessage_4args() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->title, __FILE__, __LINE__);
    Assert::assertNull(m->message, __FILE__, __LINE__);
    Assert::assertNull(m->strClass, __FILE__, __LINE__);
    Assert::assertNull(m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(-1, m->type, __FILE__, __LINE__);
    m->showInfoMessage("title1", "message1", strClass, "item1");
    Assert::assertEquals("title1", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message1", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item1", m->item, __FILE__, __LINE__);
    Assert::assertTrue(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(JOptionPane::INFORMATION_MESSAGE, m->type, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testShowErrorMessage() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->title, __FILE__, __LINE__);
    Assert::assertNull(m->message, __FILE__, __LINE__);
    Assert::assertNull(m->strClass, __FILE__, __LINE__);
    Assert::assertNull(m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(-1, m->type, __FILE__, __LINE__);
    m->showErrorMessage("title1", "message1", strClass, "item1", true, true);
    Assert::assertEquals("title1", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message1", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item1", m->item, __FILE__, __LINE__);
    Assert::assertTrue(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertTrue(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(JOptionPane::ERROR_MESSAGE, m->type, __FILE__, __LINE__);
    m->showErrorMessage("title2", "message2", strClass, "item2", false, false);
    Assert::assertEquals("title2", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message2", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item2", m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(JOptionPane::ERROR_MESSAGE, m->type, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testShowInfoMessage_6args() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->title, __FILE__, __LINE__);
    Assert::assertNull(m->message, __FILE__, __LINE__);
    Assert::assertNull(m->strClass, __FILE__, __LINE__);
    Assert::assertNull(m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(-1, m->type, __FILE__, __LINE__);
    m->showInfoMessage("title1", "message1", strClass, "item1", true, true);
    Assert::assertEquals("title1", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message1", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item1", m->item, __FILE__, __LINE__);
    Assert::assertTrue(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertTrue(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(JOptionPane::INFORMATION_MESSAGE, m->type, __FILE__, __LINE__);
    m->showInfoMessage("title2", "message2", strClass, "item2", false, false);
    Assert::assertEquals("title2", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message2", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item2", m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(JOptionPane::INFORMATION_MESSAGE, m->type, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testShowWarningMessage() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->title, __FILE__, __LINE__);
    Assert::assertNull(m->message, __FILE__, __LINE__);
    Assert::assertNull(m->strClass, __FILE__, __LINE__);
    Assert::assertNull(m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(-1, m->type, __FILE__, __LINE__);
    m->showWarningMessage("title1", "message1", strClass, "item1", true, true);
    Assert::assertEquals("title1", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message1", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item1", m->item, __FILE__, __LINE__);
    Assert::assertTrue(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertTrue(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(JOptionPane::WARNING_MESSAGE, m->type, __FILE__, __LINE__);
    m->showWarningMessage("title2", "message2", strClass, "item2", false, false);
    Assert::assertEquals("title2", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message2", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item2", m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(JOptionPane::WARNING_MESSAGE, m->type, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testShowMessage() {
    // TODO: Use Jemmy to test showing real message
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->title, __FILE__, __LINE__);
    Assert::assertNull(m->message, __FILE__, __LINE__);
    Assert::assertNull(m->strClass, __FILE__, __LINE__);
    Assert::assertNull(m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(-1, m->type, __FILE__, __LINE__);
    m->showMessage("title1", "message1", strClass, "item1", true, true, JOptionPane::INFORMATION_MESSAGE);
    Assert::assertEquals("title1", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message1", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item1", m->item, __FILE__, __LINE__);
    Assert::assertTrue(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertTrue(m->sessionOnly, __FILE__, __LINE__);
    m->showMessage("title2", "message2", strClass, "item2", false, false, JOptionPane::INFORMATION_MESSAGE);
    Assert::assertEquals("title2", m->title, __FILE__, __LINE__);
    Assert::assertEquals("message2", m->message, __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("item2", m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testAddComboBoxLastSelection() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertEquals(0, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test1", "value1");
    Assert::assertEquals(1, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test1", "value2");
    Assert::assertEquals(1, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test2", "value1");
    Assert::assertEquals(2, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetComboBoxLastSelection_String() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertEquals(0, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test1", "value2");
    m->setComboBoxLastSelection("test2", "value1");
    Assert::assertEquals("value2", m->getComboBoxLastSelection("test1"), __FILE__, __LINE__);
    Assert::assertEquals("value1", m->getComboBoxLastSelection("test2"), __FILE__, __LINE__);
    Assert::assertNull(m->getComboBoxLastSelection("test3"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetComboBoxLastSelection() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertEquals(0, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test1", "value1");
    Assert::assertEquals("value1", m->getComboBoxLastSelection("test1"), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test1", "value2");
    Assert::assertEquals("value2", m->getComboBoxLastSelection("test1"), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test2", "value1");
    Assert::assertEquals("value1", m->getComboBoxLastSelection("test2"), __FILE__, __LINE__);
    Assert::assertNull(m->getComboBoxLastSelection("test3"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetComboBoxSelectionSize() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertEquals(0, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test1", "value1");
    Assert::assertEquals(1, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test1", "value2");
    Assert::assertEquals(1, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
    m->setComboBoxLastSelection("test2", "value1");
    Assert::assertEquals(2, m->getComboBoxLastSelection()->size(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetChangeMade() {
    JmriUserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->getChangeMade(), __FILE__, __LINE__);
    m->setChangeMade(false);
    Assert::assertTrue(m->getChangeMade(), __FILE__, __LINE__);
    m->resetChangeMade();
    Assert::assertFalse(m->getChangeMade(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetChangeMade() {
    JmriUserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    JUPMListener* l = new JUPMListener(this);
    m->addPropertyChangeListener(l);
    Assert::assertFalse(m->getChangeMade(), __FILE__, __LINE__);
    m->setChangeMade(false);
    Assert::assertTrue(m->getChangeMade(), __FILE__, __LINE__);
    Assert::assertNull(l->event, __FILE__, __LINE__);
    m->setChangeMade(true);
//    JUnitUtil::waitFor(() -> {
//        return l.event != null && l.event.getPropertyName().equals(UserPreferencesManager.PREFERENCES_UPDATED);
//    }, "event change notification fired");
    JUnitUtil::waitFor(new JUPMReleaseUntil(l), "event change notification fired", __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testResetChangeMade() {
    JmriUserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->getChangeMade(), __FILE__, __LINE__);
    m->setChangeMade(false);
    Assert::assertTrue(m->getChangeMade(), __FILE__, __LINE__);
    m->resetChangeMade();
    Assert::assertFalse(m->getChangeMade(), __FILE__, __LINE__);
    m->resetChangeMade();
    Assert::assertFalse(m->getChangeMade(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testIsLoading() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertFalse(m->isLoading(), __FILE__, __LINE__);
    m->setLoading();
    Assert::assertTrue(m->isLoading(), __FILE__, __LINE__);
    m->finishLoading();
    Assert::assertFalse(m->isLoading(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetLoading() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertFalse(m->isLoading(), __FILE__, __LINE__);
    m->setLoading();
    Assert::assertTrue(m->isLoading(), __FILE__, __LINE__);
    m->finishLoading();
    Assert::assertFalse(m->isLoading(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testFinishLoading() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertFalse(m->isLoading(), __FILE__, __LINE__);
    m->finishLoading();
    Assert::assertFalse(m->isLoading(), __FILE__, __LINE__);
    m->setLoading();
    Assert::assertTrue(m->isLoading(), __FILE__, __LINE__);
    m->finishLoading();
    Assert::assertFalse(m->isLoading(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testDisplayRememberMsg() {
    TestJmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    m->setLoading();
    m->displayRememberMsg();
    Assert::assertNull(m->title, __FILE__, __LINE__);
    Assert::assertNull(m->message, __FILE__, __LINE__);
    Assert::assertNull(m->strClass, __FILE__, __LINE__);
    Assert::assertNull(m->item, __FILE__, __LINE__);
    Assert::assertFalse(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(-1, m->type, __FILE__, __LINE__);
    m->finishLoading();
    //Bundle.getMessage("Reminder"), Bundle.getMessage("ReminderLine"), getClassName(), "reminder"
    m->displayRememberMsg();
    Assert::assertEquals(tr("Reminder"), m->title, __FILE__, __LINE__);
    Assert::assertEquals(tr("ReminderLine"), m->message, __FILE__, __LINE__);
    Assert::assertEquals(m->getClassName(), m->strClass, __FILE__, __LINE__);
    Assert::assertEquals("reminder", m->item, __FILE__, __LINE__);
    Assert::assertTrue(m->alwaysRemember, __FILE__, __LINE__);
    Assert::assertFalse(m->sessionOnly, __FILE__, __LINE__);
    Assert::assertEquals(JOptionPane::INFORMATION_MESSAGE, m->type, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetWindowLocation() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QPoint windowLocation = QPoint(69, 96);
    m->setWindowLocation(strClass, windowLocation);
    QPoint savedWindowLocation = m->getWindowLocation(strClass);
    Assert::assertEquals(windowLocation, savedWindowLocation, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetWindowSize() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QSize windowSize = QSize(666, 999);
    m->setWindowSize(strClass, windowSize);
    QSize savedWindowSize = m->getWindowSize(strClass);
    Assert::assertEquals(windowSize, savedWindowSize, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetSaveWindowSize() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->getSaveWindowSize(strClass), __FILE__, __LINE__);
    m->setSaveWindowSize(strClass, true);
    Assert::assertTrue(m->getSaveWindowSize(strClass), __FILE__, __LINE__);
    m->setSaveWindowSize(strClass, false);
    Assert::assertFalse(m->getSaveWindowSize(strClass), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetSaveWindowLocation() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->getSaveWindowLocation(strClass), __FILE__, __LINE__);
    m->setSaveWindowLocation(strClass, true);
    Assert::assertTrue(m->getSaveWindowLocation(strClass), __FILE__, __LINE__);
    m->setSaveWindowLocation(strClass, false);
    Assert::assertFalse(m->getSaveWindowLocation(strClass), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetSaveWindowSize() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->getSaveWindowSize(strClass), __FILE__, __LINE__);
    m->setSaveWindowSize(strClass, true);
    Assert::assertTrue(m->getSaveWindowSize(strClass), __FILE__, __LINE__);
    m->setSaveWindowSize(strClass, false);
    Assert::assertFalse(m->getSaveWindowSize(strClass), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetSaveWindowLocation() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->getSaveWindowLocation(strClass), __FILE__, __LINE__);
    m->setSaveWindowLocation(strClass, true);
    Assert::assertTrue(m->getSaveWindowLocation(strClass), __FILE__, __LINE__);
    m->setSaveWindowLocation(strClass, false);
    Assert::assertFalse(m->getSaveWindowLocation(strClass), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetWindowLocation() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QPoint windowLocation = QPoint(69, 96);
    m->setWindowLocation(strClass, windowLocation);
    QPoint savedWindowLocation = m->getWindowLocation(strClass);
    Assert::assertEquals(windowLocation, savedWindowLocation, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetWindowSize() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QSize windowSize = QSize(666, 999);
    m->setWindowSize(strClass, windowSize);
    QSize savedWindowSize = m->getWindowSize(strClass);
    Assert::assertEquals(windowSize, savedWindowSize, __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetWindowList() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertTrue(m->getWindowList().isEmpty(), __FILE__, __LINE__);
    QPoint location = QPoint(69, 96);
    m->setWindowLocation(strClass, location);
    Assert::assertEquals(1, m->getWindowList().size(), __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->getWindowList().at(0), __FILE__, __LINE__);
    QSize windowSize = QSize(666, 999);
    m->setWindowSize(strClass, windowSize);
    Assert::assertEquals(1, m->getWindowList().size(), __FILE__, __LINE__);
    Assert::assertEquals(strClass, m->getWindowList().at(0), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetProperty() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertNull(m->getProperty(strClass, "test1"), __FILE__, __LINE__);
    m->setProperty(strClass, "test1", VPtr<Logger>::asQVariant(log));
    Assert::assertEquals(VPtr<Logger>::asQVariant(log), m->getProperty(strClass, "test1"), __FILE__, __LINE__);
    m->setProperty(strClass, "test1", QVariant());
    Assert::assertNull(m->getProperty(strClass, "test1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetProperty() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertNull(m->getProperty(strClass, "test1"), __FILE__, __LINE__);
    m->setProperty(strClass, "test1", VPtr<Logger>::asQVariant(log));
    Assert::assertEquals(VPtr<Logger>::asQVariant(log), m->getProperty(strClass, "test1"), __FILE__, __LINE__);
    m->setProperty(strClass, "test1", QVariant());
    Assert::assertNull(m->getProperty(strClass, "test1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetPropertyKeys() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
//    Assert::assertNull(m->getPropertyKeys(strClass), __FILE__, __LINE__);
    m->setProperty(strClass, "test1", VPtr<Logger>::asQVariant(log));
    m->setProperty(strClass, "test2", QVariant(1));
    Assert::assertEquals(2, m->getPropertyKeys(strClass).size(), __FILE__, __LINE__);
    Assert::assertTrue(m->getPropertyKeys(strClass).contains("test1"), __FILE__, __LINE__);
    Assert::assertTrue(m->getPropertyKeys(strClass).contains("test2"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPropertyKeys(strClass).contains("test3"), __FILE__, __LINE__);
    m->setProperty(strClass, "test2", QVariant());
    Assert::assertEquals(1, m->getPropertyKeys(strClass).size(), __FILE__, __LINE__);
    Assert::assertTrue(m->getPropertyKeys(strClass).contains("test1"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPropertyKeys(strClass).contains("test2"), __FILE__, __LINE__);
    Assert::assertFalse(m->getPropertyKeys(strClass).contains("test3"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testHasProperties() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    Assert::assertFalse(m->hasProperties(strClass), __FILE__, __LINE__);
    m->setProperty(strClass, "test1", VPtr<Logger>::asQVariant(log));
    m->setProperty(strClass, "test2", QVariant());
    Assert::assertTrue(m->hasProperties(strClass), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetClassDescription_String() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->getClassDescription(strClass), __FILE__, __LINE__);
    Assert::assertTrue(m->getClassDescription(strClass).isEmpty(), __FILE__, __LINE__);
    m->setPreferenceState(strClass, "test1", true);
    Assert::assertNotNull(m->getClassDescription(strClass), __FILE__, __LINE__);
    m->setPreferenceState(AppConfigBase::getClassName(), "test1", true);
    QString d = tr("Application");//ResourceBundle::getBundle("apps.AppsConfigBundle").getString("Application");
    Assert::assertEquals(d, m->getClassDescription("apps.AppConfigBase"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetPreferencesClasses() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    qApp->processEvents();
    QStringList l = m->getPreferencesClasses();
    Assert::assertEquals(1, l.size(), __FILE__, __LINE__);
    Assert::assertEquals("jmri.managers.TestJmriUserPreferencesManager", m->getPreferencesClasses().at(0), __FILE__, __LINE__);
    m->setPreferenceState(strClass, "test1", true);
    Assert::assertEquals(2, m->getPreferencesClasses().size(), __FILE__, __LINE__);
    l = m->getPreferencesClasses();
    Assert::assertEquals(strClass, l.at(1), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetClassDescription() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull(m->getClassDescription(strClass), __FILE__, __LINE__);
    Assert::assertTrue(m->getClassDescription(strClass).isEmpty(), __FILE__, __LINE__);
    m->setClassDescription(strClass);
    Assert::assertNotNull(m->getClassDescription(strClass), __FILE__, __LINE__);
    Assert::assertTrue(m->getClassDescription(strClass).isEmpty(), __FILE__, __LINE__);
    m->setClassDescription(AppConfigBase::getClassName());
    QString d = tr("Application");//ResourceBundle.getBundle("apps.AppsConfigBundle").getString("Application");
//    Assert::assertEquals(d, m->getClassDescription(AppConfigBase.class.getName()), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetMessageItemDetails() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    Assert::assertTrue(m->getChoiceOptions(strClass, "item1")->isEmpty(), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
//    Assert::assertEquals(options, m->getChoiceOptions(strClass, "item1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetChoiceOptions() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    Assert::assertTrue(m->getChoiceOptions(strClass, "item1")->isEmpty(), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
//    Assert::assertEquals(options, m->getChoiceOptions(strClass, "item1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetMultipleChoiceSize() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    Assert::assertEquals(0, m->getMultipleChoiceSize(strClass), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
    Assert::assertEquals(1, m->getMultipleChoiceSize(strClass), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetMultipleChoiceList() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    Assert::assertTrue(m->getMultipleChoiceList(strClass).isEmpty(), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
    Assert::assertEquals(1, m->getMultipleChoiceList(strClass).size(), __FILE__, __LINE__);
    Assert::assertEquals("item1", m->getMultipleChoiceList(strClass).at(0), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetChoiceName() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    Assert::assertNull(m->getChoiceName(strClass, 0), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
    Assert::assertEquals("item1", m->getChoiceName(strClass, 0), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetChoiceDescription() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    Assert::assertNull(m->getChoiceDescription(strClass, "item1"), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
    Assert::assertEquals("description1", m->getChoiceDescription(strClass, "item1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetMultipleChoiceOption() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    Assert::assertEquals(0, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
    Assert::assertEquals(0, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetMultipleChoiceDefaultOption() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    Assert::assertEquals(0, m->getMultipleChoiceDefaultOption(strClass, "item1"), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
    Assert::assertEquals(0, m->getMultipleChoiceDefaultOption(strClass, "item1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetMultipleChoiceOption_3args_String() {
    UserPreferencesManager* m = new JmriUserPreferencesManager();
    m->setSaveAllowed(false);
    m->setMultipleChoiceOption(strClass, "item1", "value1");
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    options->insert(2, "test2");
    Assert::assertEquals(0, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
    Assert::assertEquals(0, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
    m->setMultipleChoiceOption(strClass, "item1", "test1");
    Assert::assertEquals(1, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
    m->setMultipleChoiceOption(strClass, "item1", "test2");
    Assert::assertEquals(2, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSetMultipleChoiceOption_3args_int() {
    UserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    m->setMultipleChoiceOption(strClass, "item1", "value1");
    QMap<int, QString>* options = new QMap<int, QString>();
    options->insert(1, "test1");
    options->insert(2, "test2");
    Assert::assertEquals(0, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
    m->setMessageItemDetails(strClass, "item1", "description1", options, 0);
    Assert::assertEquals(0, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
    m->setMultipleChoiceOption(strClass, "item1", 1);
    Assert::assertEquals(1, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
    m->setMultipleChoiceOption(strClass, "item1", 2);
    Assert::assertEquals(2, m->getMultipleChoiceOption(strClass, "item1"), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetClassDescription_0args() {
    JmriUserPreferencesManager* m = new JmriUserPreferencesManager();
    Assert::assertEquals("Preference Manager", m->getClassDescription(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetClassName() {
    JmriUserPreferencesManager* m = new JmriUserPreferencesManager();
    Assert::assertEquals("jmri.managers.JmriUserPreferencesManager", m->getClassName(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetClassPreferences() {
    JmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull((QObject*)m->getClassPreferences(strClass), __FILE__, __LINE__);
    m->setPreferenceState(strClass, "test1", true);
    Assert::assertNotNull((QObject*)m->getClassPreferences(strClass), __FILE__, __LINE__);
    Assert::assertEquals(1, m->getClassPreferences(strClass)->getPreferenceListSize(), __FILE__, __LINE__);
    Assert::assertEquals("test1", m->getClassPreferences(strClass)->getPreferenceList()->at(0)->getItem(), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testGetPreferencesSize() {
    JmriUserPreferencesManager* m = new TestJmriUserPreferencesManager(this);
    m->setSaveAllowed(false);
    Assert::assertNull((QObject*)m->getClassPreferences(strClass), __FILE__, __LINE__);
    Assert::assertEquals(0, m->getPreferencesSize(strClass), __FILE__, __LINE__);
    m->setPreferenceState(strClass, "test1", true);
    Assert::assertNotNull((QObject*)m->getClassPreferences(strClass), __FILE__, __LINE__);
    Assert::assertEquals(1, m->getPreferencesSize(strClass), __FILE__, __LINE__);

}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testReadUserPreferences() /*throw (IOException)*/ {
    JUnitUtil::resetProfileManager(new NullProfile(folder->newFolder(Profile::PROFILE)));
    QPoint location = QPoint(69, 96);
    QSize windowSize = QSize(100, 200);
    UserPreferencesManager* m1 = new TestJmriUserPreferencesManager(this);
    m1->setSaveAllowed(false);
    m1->setProperty(strClass, "test1", "value1");
    m1->setProperty(strClass, "intTest", 42);
    m1->setProperty(strClass, "doubleTest", M_PI);
    m1->setProperty(strClass, "boolTest", true);
    m1->setWindowLocation(strClass, location);
    m1->setWindowSize(strClass, windowSize);
    m1->setPreferenceState(strClass, "test2", true);
    m1->setPreferenceState(strClass, "test3", false);
    m1->setSimplePreferenceState(strClass, true);
    m1->setComboBoxLastSelection(strClass, "selection1");
    m1->setSaveAllowed(true);
    Profile* profile = ProfileManager::getDefault()->getActiveProfile();
    Assert::assertNotNull(profile, __FILE__, __LINE__); // test with profile
    File* target = new File(new File(new File(profile->getPath(), "profile"), NodeIdentity::storageIdentity()), "user-interface.xml");
    Assert::assertTrue(target->exists(), __FILE__, __LINE__);
    Assert::assertTrue(target->isFile(), __FILE__, __LINE__);
#if 0
    if (log->isDebugEnabled()) {
        Files.lines(target.toPath()).forEach((line) -> log.debug(line));
    }
#endif
    JUnitUtil::resetInstanceManager();
    JUnitUtil::resetPreferencesProviders();
    JmriUserPreferencesManager* m2 = new JmriUserPreferencesManager();
    m2->readUserPreferences();
    Assert::assertEquals("value1", m2->getProperty(strClass, "test1"), __FILE__, __LINE__);
    Assert::assertEquals(42, m2->getProperty(strClass, "intTest"), __FILE__, __LINE__);
    Assert::assertEquals(M_PI, m2->getProperty(strClass, "doubleTest"), __FILE__, __LINE__);
    Assert::assertEquals(true, m2->getProperty(strClass, "boolTest"), __FILE__, __LINE__);
    Assert::assertEquals(location, m2->getWindowLocation(strClass), __FILE__, __LINE__);
    Assert::assertEquals(windowSize, m2->getWindowSize(strClass), __FILE__, __LINE__);
    Assert::assertEquals(true, m2->getPreferenceState(strClass, "test2"), __FILE__, __LINE__);
    Assert::assertEquals(false, m2->getPreferenceState(strClass, "test3"), __FILE__, __LINE__);
    Assert::assertEquals(true, m2->getSimplePreferenceState(strClass), __FILE__, __LINE__);
    Assert::assertEquals("selection1", m2->getComboBoxLastSelection(strClass), __FILE__, __LINE__);
}

//@Test
/*public*/ void JmriUserPreferencesManagerTest::testSaveElement() /*throw (IOException)*/ {
    JUnitUtil::resetProfileManager(new NullProfile(folder->newFolder(Profile::PROFILE)));
    QPoint location = QPoint(69, 96);
    QSize windowSize = QSize(100, 200);
    UserPreferencesManager* m1 = new TestJmriUserPreferencesManager(this);
    m1->setSaveAllowed(false);
    m1->setProperty(strClass, "test1", "value1");
    m1->setProperty(strClass, "intTest", 42);
    m1->setProperty(strClass, "doubleTest", M_PI);
    m1->setProperty(strClass, "boolTest", true);
    m1->setWindowLocation(strClass, location);
    m1->setWindowSize(strClass, windowSize);
    m1->setPreferenceState(strClass, "test2", true);
    m1->setPreferenceState(strClass, "test3", false);
    m1->setSimplePreferenceState(strClass, true);
    m1->setComboBoxLastSelection(strClass, "selection1");
    m1->setSaveAllowed(true);
    Profile* profile = ProfileManager::getDefault()->getActiveProfile();
    Assert::assertNotNull(profile, __FILE__, __LINE__); // test with profile
    File* target = new File(new File(new File(profile->getPath(), "profile"), NodeIdentity::storageIdentity()), "user-interface.xml");
    Assert::assertTrue(target->exists(), __FILE__, __LINE__);
    Assert::assertTrue(target->isFile(), __FILE__, __LINE__);
#if 0
    if (log.isDebugEnabled()) {
        Files.lines(target.toPath()).forEach((line) -> log.debug(line));
    }
#endif
    JUnitUtil::resetInstanceManager();
    JUnitUtil::resetPreferencesProviders();
    JmriUserPreferencesManager* m2 = new JmriUserPreferencesManager();
    m2->readUserPreferences();
    Assert::assertEquals("value1", m2->getProperty(strClass, "test1"), __FILE__, __LINE__);
    Assert::assertEquals(42, m2->getProperty(strClass, "intTest"), __FILE__, __LINE__);
    Assert::assertEquals(M_PI, m2->getProperty(strClass, "doubleTest"), __FILE__, __LINE__);
    Assert::assertEquals(true, m2->getProperty(strClass, "boolTest"), __FILE__, __LINE__);
    Assert::assertEquals(location, m2->getWindowLocation(strClass), __FILE__, __LINE__);
    Assert::assertEquals(windowSize, m2->getWindowSize(strClass), __FILE__, __LINE__);
    Assert::assertEquals(true, m2->getPreferenceState(strClass, "test2"), __FILE__, __LINE__);
    Assert::assertEquals(false, m2->getPreferenceState(strClass, "test3"), __FILE__, __LINE__);
    Assert::assertEquals(true, m2->getSimplePreferenceState(strClass), __FILE__, __LINE__);
    Assert::assertEquals("selection1", m2->getComboBoxLastSelection(strClass), __FILE__, __LINE__);
}

//@Before
/*public*/ void JmriUserPreferencesManagerTest::setUp() throw (Exception) {
    JUnitUtil::setUp();
    JUnitUtil::resetInstanceManager();
    JUnitUtil::resetPreferencesProviders();
    // ensure no existing UserPreferencesManager interferes with this test
    InstanceManager::reset("UserPreferencesManager");
}

//@After
/*public*/ void JmriUserPreferencesManagerTest::tearDown() throw (Exception) {
    JUnitUtil::tearDown();
}

//private static class TestJmriUserPreferencesManager extends JmriUserPreferencesManager {

//    /*public*/ String title = null;
//    /*public*/ String message = null;
//    /*public*/ String strClass = null;
//    /*public*/ String item = null;
//    // bool is nullable unlike bool, null indicates showMessage not called
//    /*public*/ bool sessionOnly = null;
//    /*public*/ bool alwaysRemember = null;
//    /*public*/ int type = -1;

    /*protected*/ TestJmriUserPreferencesManager::TestJmriUserPreferencesManager(JmriUserPreferencesManagerTest* test)
      : JmriUserPreferencesManager()
    {
        //super();
        this->test = test;
    }

    //@Override
    /*protected*/ void TestJmriUserPreferencesManager::showMessage(QString title, QString message, /*final*/ QString strClass, /*final*/ QString item,
      /*final*/ bool sessionOnly, /*final*/ bool alwaysRemember, int type)
{
        this->title = title;
        this->message = message;
        this->strClass = strClass;
        this->item = item;
        this->sessionOnly = sessionOnly;
        this->alwaysRemember = alwaysRemember;
        this->type = type;
        // Uncomment to force failure if wanting to verify that showMessage does not get called.
        //org.slf4j.LoggerFactory.getLogger(TestJmriUserPreferencesManager::class).error("showMessage called.", new Exception());
    }

    /**
     * Expose the HashMap of comboBox last selections for testing purposes.
     *
     * @return the map of combo box last selections
     */
    /*protected*/ QHash<QString, QString>* TestJmriUserPreferencesManager::getComboBoxLastSelection() {
        return this->comboBoxLastSelection;
    }

    QString TestJmriUserPreferencesManager::getComboBoxLastSelection(QString s)
    {
     return this->comboBoxLastSelection->value(s);
    }
    /**
     * Expose the loading flag for testing purposes by changing the method
     * scope from protected to public.
     *
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ bool TestJmriUserPreferencesManager::isLoading() {
        return JmriUserPreferencesManager::isLoading();
    }
    /*public*/ QString TestJmriUserPreferencesManager::getClassName() { return "jmri.managers.TestJmriUserPreferencesManager";}
//}

//    /*private*/ static class JUPMListener* implements PropertyChangeJUPMListener* {

//        /*public*/ PropertyChangeEvent event = null;

    //@Override
    /*public*/ void JUPMListener::propertyChange(PropertyChangeEvent* evt) {
        event = evt;
    }
//    }
//}
/*public*/ QString JmriUserPreferencesManagerTest::getClassDescription()
{
 return "";
}
