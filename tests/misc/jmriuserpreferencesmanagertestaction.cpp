#include "jmriuserpreferencesmanagertestaction.h"
#include "jmriuserpreferencesmanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

JmriUserPreferencesManagerTestAction::JmriUserPreferencesManagerTestAction(QObject* parent)
 : AbstractAction(tr("JmriUserPreferencesManagerTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void JmriUserPreferencesManagerTestAction::actionPerformed()
{
    JmriUserPreferencesManagerTest* test = new JmriUserPreferencesManagerTest();
    try
    {
     QStringList testList = QStringList()
//       << "testGetInstance"
//       << "testGetDefault"
       << "testAllowSave"
       << "testDisallowSave"
       << "testSetSaveAllowed"
       << "testIsSaveAllowed"
       << "testGetScreen"
       << "testSetSimplePreferenceState"
       << "testGetSimplePreferenceState"
       << "testGetSimplePreferenceStateList"
       << "testSetPreferenceState"
       << "testGetPreferenceState"
       << "testSetPreferenceItemDetails"
       << "testGetPreferenceList"
       << "testGetPreferenceItemName"
       << "testGetPreferenceItemDescription"
       << "testSetSessionPreferenceState"
       << "testGetSessionPreferenceState"
       << "testShowInfoMessage_4args"
       << "testShowErrorMessage"
       << "testShowInfoMessage_6args"
       << "testShowWarningMessage"
       << "testShowMessage"
       << "testAddComboBoxLastSelection"
       << "testGetComboBoxLastSelection_String"
       << "testSetComboBoxLastSelection"
       << "testGetComboBoxSelectionSize"
       << "testGetChangeMade"
       << "testSetChangeMade"
       << "testResetChangeMade"
       << "testIsLoading"
       << "testSetLoading"
       << "testFinishLoading"
       << "testDisplayRememberMsg"
       << "testGetWindowLocation"
       << "testGetWindowSize"
       << "testGetSaveWindowSize"
       << "testGetSaveWindowLocation"
       << "testSetSaveWindowSize"
       << "testSetSaveWindowLocation"
       << "testSetWindowLocation"
       << "testSetWindowSize"
       << "testGetWindowList"
       << "testSetProperty"
       << "testGetProperty"
       << "testGetPropertyKeys"
       << "testHasProperties"
       << "testGetClassDescription_String"
       << "testGetPreferencesClasses"
       << "testSetClassDescription"
       << "testSetMessageItemDetails"
       << "testGetChoiceOptions"
       << "testGetMultipleChoiceSize"
       << "testGetMultipleChoiceList"
       << "testGetChoiceName"
       << "testGetChoiceDescription"
       << "testGetMultipleChoiceOption"
       << "testGetMultipleChoiceDefaultOption"
       << "testSetMultipleChoiceOption_3args_String"
       << "testSetMultipleChoiceOption_3args_int"
       << "testGetClassDescription_0args"
       << "testGetClassName"
       << "testGetClassPreferences"
       << "testGetPreferencesSize"
       << "testReadUserPreferences"
       << "testSaveElement"

;

     JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* JmriUserPreferencesManagerTestAction::log = LoggerFactory::getLogger("JmriUserPreferencesManagerTestAction");
