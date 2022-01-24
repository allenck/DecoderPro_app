#include "signalheadsignalmasttestaction.h"
#include "signalheadsignalmasttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

SignalHeadSignalMastTestAction::SignalHeadSignalMastTestAction(QObject* parent) : AbstractAction(tr("SignalHeadSignalMastTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void SignalHeadSignalMastTestAction::actionPerformed()
{
    SignalHeadSignalMastTest* test = new SignalHeadSignalMastTest();
    try
    {
     QStringList testList = QStringList()
       << "testSetup"
       << "testTwoNameOneHeadCtorOK"
       << "testHeld"
       << "testLit"
       << "testTwoNameSe8cHeadCtorOK"
       << "testOneNameOneHeadCtorOK"
       << "testOldTwoNameCtorOK"
       << "testOldOneNameCtorOK"
       << "testOldOneNameCtorFailNoSystem"
       << "testAspects"
       << "testAspectAttributes"
       << "testAspectNotSet"
       << "testAspectFail"
       << "testConfigureOneSearchLight"
       << "testConfigureTwoSearchLight"
       << "testOneSearchLightViaManager"
       << "testSignalSystemLink"
       ;

     JUnitUtil::runTests(test, testList);
    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* SignalHeadSignalMastTestAction::log = LoggerFactory::getLogger("SignalHeadSignalMastTestAction");
