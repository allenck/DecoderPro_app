#include "swingconfiguratorinterfacetestactionaction.h"
#include "swingconfiguratorinterfacetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
SwingConfiguratorInterfaceTestActionAction::SwingConfiguratorInterfaceTestActionAction(QObject* parent)
    : AbstractAction(tr("SwingConfiguratorInterface"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
void SwingConfiguratorInterfaceTestActionAction::actionPerformed()
{
    SwingConfiguratorInterfaceTest* smt = new SwingConfiguratorInterfaceTest();
    try
    {
     QStringList testList = QStringList()
       << "testSwingTools"
          ;

       JUnitUtil::runTests(smt, testList);

    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* SwingConfiguratorInterfaceTestActionAction::log = LoggerFactory::getLogger("SwingConfiguratorInterfaceTestActionAction");
