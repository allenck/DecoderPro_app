#include "optionsmenutestaction.h"
#include "operations/optionsmenutest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

OptionsMenuTestAction::OptionsMenuTestAction(QObject* parent) : AbstractAction(tr("OptionMenuTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void OptionsMenuTestAction::actionPerformed()
{
    OptionsMenuTest* test = new OptionsMenuTest();
    try
    {
     QStringList testList = QStringList()
       << "testCTor";

     JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* OptionsMenuTestAction::log = LoggerFactory::getLogger("OptionMenuTestAction");
