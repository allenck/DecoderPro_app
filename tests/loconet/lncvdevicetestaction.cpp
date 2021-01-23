#include "lncvdevicetestaction.h"
#include "lncvdevicetest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"
LncvDeviceTestAction::LncvDeviceTestAction(QObject *parent) : AbstractAction(tr("LncvDeviceTest "), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}
void LncvDeviceTestAction::actionPerformed()
{
 LncvDeviceTest* test = new LncvDeviceTest();
 try
 {
  QStringList testList = QStringList()
    <<  "testCTor"
    <<  "testGetProductID"
    <<  "testGetDestAddr"
    <<  "testSetDestAddr"
    <<  "testGetCvNum"
    <<  "testSetCvNum"
    <<  "testGetCvValue"
    <<  "testSetCvValue"
    ;
  JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError er)
 {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* LncvDeviceTestAction::log = LoggerFactory::getLogger("LncvDeviceTestAction");
