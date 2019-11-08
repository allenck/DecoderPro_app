#include "lnportcontrollertestaction.h"
#include "lnportcontrollertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LnPortControllerTestAction::LnPortControllerTestAction(QObject* parent) : AbstractAction(tr("LnPortController Test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
void LnPortControllerTestAction::actionPerformed()
{
    LnPortControllerTest* lnpct = new LnPortControllerTest();
    try
    {
       QStringList testList = QStringList()
       << "testisDirtyNotNPE";
     JUnitUtil::runTests(lnpct, testList);
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* LnPortControllerTestAction::log = LoggerFactory::getLogger("LnPortControllerTestAction");
