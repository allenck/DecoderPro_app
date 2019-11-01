#include "sprogmessagetestaction.h"
#include "sprogmessagetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"

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
     foreach(QString test, testList)
     {
      log->info(tr("begin '%1'").arg(test));
      QMetaObject::invokeMethod(smt, test.toLocal8Bit(), Qt::DirectConnection);
      log->info(tr("end '%1'").arg(test));
     }

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* SprogMessageTestAction::log = LoggerFactory::getLogger("SprogMessageTestAction");
