#include "loconetmessageexceptiontestaction.h"
#include "loconetmessageexceptiontest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LocoNetMessageExceptionTestAction::LocoNetMessageExceptionTestAction(QObject* parent)
    : AbstractAction(tr("LocoNetMessageExceptionTest"),parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void LocoNetMessageExceptionTestAction::actionPerformed()
{
    LocoNetMessageExceptionTest* test = new LocoNetMessageExceptionTest();
    try
    {
     QStringList testList = QStringList()
       << "ConstructorTest"
       << "StringConstructorTest";
     JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* LocoNetMessageExceptionTestAction::log = LoggerFactory::getLogger("LocoNetMessageExceptionTestAction");
