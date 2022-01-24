#include "abstractprogrammertestaction.h"
#include "abstractprogrammertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

AbstractProgrammerTestAction::AbstractProgrammerTestAction(QObject* parent) : AbstractAction(tr("AbstractProgrammerTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void AbstractProgrammerTestAction::actionPerformed()
{
    AbstractProgrammerTest* smt = new AbstractProgrammerTest();
    try
    {
     QStringList testList = QStringList()
         << "testCtor"
         << "testDefault"
         << "testGetCanRead"
         << "testGetCanWrite"
         << "testGetCanReadAddress"
         << "testGetCanWriteAddress"
         << "testSetGetMode"
         << "testSetModeNull"
         << "testGetWriteConfirmMode"
         << "testWriteCVNullListener"

         // in AbstractProgrammerTest
         << "testDefaultViaBestMode"
         << "testRegisterFromCV"


     ;
     JUnitUtil::runTests(smt, testList);

    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* AbstractProgrammerTestAction::log = LoggerFactory::getLogger("AbstractProgrammerTestAction");
