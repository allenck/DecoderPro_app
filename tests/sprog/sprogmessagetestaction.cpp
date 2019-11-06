#include "sprogmessagetestaction.h"
#include "sprogmessagetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

SprogMessageTestAction::SprogMessageTestAction(QObject *parent) : AbstractAction(tr("SprogMessage test"), parent)
{
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void SprogMessageTestAction::actionPerformed()
{
    Sprog::SprogMessageTest* smt = new Sprog::SprogMessageTest();
    try
    {
     QStringList testList = QStringList()
         << "testCtor"
         << "testToString"
         << "testToMonitorString"
          << "testReadCv"
          << "testWriteCV"
          << "testReadCvLarge"
          << "testWriteCVLarge";
     JUnitUtil::runTests(smt, testList);

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* SprogMessageTestAction::log = LoggerFactory::getLogger("SprogMessageTestAction");
