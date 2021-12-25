#include "namedbeanusernamecomparatortestaction.h"
#include "namedbeanusernamecomparatortest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

NamedBeanUserNameComparatorTestAction::NamedBeanUserNameComparatorTestAction(QObject* parent)
    : AbstractAction(tr("User Name Comparator test"),parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void NamedBeanUserNameComparatorTestAction::actionPerformed()
{
    NamedBeanUserNameComparatorTest* test = new NamedBeanUserNameComparatorTest();
    try
    {
     QStringList testList = QStringList()
       << "testNonNullUserNameCases"
       << "testOneLetterCases"
       << "testTwoLetterCases"
       << "testThreeLetterCases"
       << "testMixedUserNamesSystemNamesCase"
       << "testSystemSpecificCase";
     JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* NamedBeanUserNameComparatorTestAction::log = LoggerFactory::getLogger("NamedBeanUserNameComparatorTestAction");
