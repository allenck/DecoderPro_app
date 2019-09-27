#include "lntrafficroutertestaction.h"
#include "lntrafficroutertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"


LnTrafficRouterTestAction::LnTrafficRouterTestAction(QObject *parent) : AbstractAction(tr("LnTrafficRouter"), parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

void LnTrafficRouterTestAction::actionPerformed()
{
    LnTrafficRouterTest* test = new LnTrafficRouterTest();
    test->setUp();
    try
    {
      QStringList testList = QStringList()
     << "testReceiveAndForward"
     << "testConnectAndDisconnect";
      foreach(QString testName, testList)
      {
       log->info(tr("begin '%1'").arg(testName));
       QMetaObject::invokeMethod(test, testName.toLocal8Bit(), Qt::DirectConnection);
       log->info(tr("end '%1'").arg(testName));
      }}
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    test->tearDown();

}
Logger* LnTrafficRouterTestAction::log = LoggerFactory::getLogger("LnTrafficRouterTestAction");
