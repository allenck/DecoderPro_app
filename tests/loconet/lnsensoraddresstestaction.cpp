#include "lnsensoraddresstestaction.h"
#include "lnsensoraddresstest.h"
#include "junitutil.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"

LnSensorAddressTestAction::LnSensorAddressTestAction(QObject *parent)
 : AbstractAction(tr("LnSensorAddress test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnSensorAddressTestAction::actionPerformed()
{
 LnSensorAddressTest* test = new LnSensorAddressTest();

 try
 {
     QStringList testList = QStringList()

       << "testLnSensorAddressCreate"
       << "testLnSensorInvalid"
       << "testLnSensorAddressASmode"
       << "testLnSensorAddressNumericMode"
       << "testLnSensorAddressBDL16Mode"
       << "testLnSensorAddressFromPacket";

       JUnitUtil::runTests(test, testList);
   }
   catch (AssertionError* er)
   {
       JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
   }
}
Logger* LnSensorAddressTestAction::log = LoggerFactory::getLogger("LnSensorAddressTestAction");
