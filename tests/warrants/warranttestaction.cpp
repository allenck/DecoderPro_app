#include "warranttestaction.h"
#include "warranttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

WarrantTestAction::WarrantTestAction(QObject * parent) : AbstractAction(tr("WarrantTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void WarrantTestAction::actionPerformed()
{
    WarrantTest* test = new WarrantTest();
    try
    {
     QStringList testList = QStringList()
       << "testCTor"
       << "testSetAndGetTrainName"
       << "testGetSpeedUtil"
       << "testAddPropertyChangeListener"
       << "testAllocateAndDeallocateWarrant"
       << "testSetRouteUsingViaOrders"
       << "testSetRoute"
       << "setThrottleCommands"
       << "testWarrant"
;

     JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* WarrantTestAction::log = LoggerFactory::getLogger("WarrantTestAction");
