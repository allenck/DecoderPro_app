#include "lnportcontrollertestaction.h"
#include "lnportcontrollertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"

LnPortControllerTestAction::LnPortControllerTestAction(QObject* parent) : AbstractAction(tr("LnPortController Test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
void LnPortControllerTestAction::actionPerformed()
{
    LnPortControllerTest* lnpct = new LnPortControllerTest();
    lnpct->setUp();
    try
    {
       QStringList testList = QStringList()
       << "testisDirtyNotNPE";
       foreach(QString test, testList)
       {
        log->info(tr("begin '%1'").arg(test));
        QMetaObject::invokeMethod(lnpct, test.toLocal8Bit(), Qt::DirectConnection);
        log->info(tr("end '%1'").arg(test));
       }

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    lnpct->tearDown();
}
Logger* LnPortControllerTestAction::log = LoggerFactory::getLogger("LnPortControllerTestAction");
