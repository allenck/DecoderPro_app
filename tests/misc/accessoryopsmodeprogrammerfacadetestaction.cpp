#include "accessoryopsmodeprogrammerfacadetestaction.h"
#include "accessoryopsmodeprogrammerfacadetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

AccessoryOpsModeProgrammerFacadeTestAction::AccessoryOpsModeProgrammerFacadeTestAction(QObject* parent)
 : AbstractAction(tr("AccessoryOpsModeProgrammerFacadeTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void AccessoryOpsModeProgrammerFacadeTestAction::actionPerformed()
{
    AccessoryOpsModeProgrammerFacadeTest* test = new AccessoryOpsModeProgrammerFacadeTest();
    try
    {
     QStringList testList = QStringList()
       << "testWriteAddr123long1cv234val14delay200signal"
       << "testWriteAddr3long0cv12val0delay500accessory"
       << "testWriteAddr511long1cv1024val255delay0decoder";

     JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* AccessoryOpsModeProgrammerFacadeTestAction::log = LoggerFactory::getLogger("AccessoryOpsModeProgrammerFacadeTestAction");
