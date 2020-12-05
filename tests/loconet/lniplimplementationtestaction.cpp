#include "lniplimplementationtestaction.h"
#include "lniplimplementationtest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnIplImplementationTestAction::LnIplImplementationTestAction(QObject* parent) : AbstractAction(tr("LnIPLImplementation Test"), parent)

{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

void LnIplImplementationTestAction::actionPerformed()
{
LnIplImplementationTest* smt = new LnIplImplementationTest();
try
{
 QStringList testList = QStringList()
    << "testCtor"
    << "testCreateQueryAllIplDevices"
    << "testCreateQueryHostDevices"
    << "testCreateQuerySlaveDevices"
    << "testCreateQueryHostSlaveDevices"
    << "checkSpecificDeviceTypeQueryMessages"
    << "checkIplIdentityReportMethods"
    << "decodingTest"
    << "checkInterpretHostManufacturerDevice"
    << "checkInterpretSlaveManufacturerDevice"
    << "testExtractIplReportInfo"
    << "testConnectMethod"

   ;
   JUnitUtil::runTests(smt, testList);

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
   }
   Logger* LnIplImplementationTestAction::log = LoggerFactory::getLogger("LnIplImplementationTestAction");
