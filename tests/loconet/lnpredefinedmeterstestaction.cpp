#include "lnpredefinedmeterstestaction.h"
#include "lnpredefinedmeterstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnPredefinedMetersTestAction::LnPredefinedMetersTestAction(QObject* parent) : AbstractAction(tr("LnPredefinedMetersTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void LnPredefinedMetersTestAction::actionPerformed()
{
LnPredefinedMetersTest* smt = new LnPredefinedMetersTest();
try
{
 QStringList testList = QStringList()
   << "testLnMeter"
   << "testSN"
   << "testAmps"
   << "testVolts"
   << "testSlotNum";

   JUnitUtil::runTests(smt, testList);

 }
 catch (AssertionError er)
 {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LnPredefinedMetersTestAction::log = LoggerFactory::getLogger("LnPredefinedMetersTestAction");
