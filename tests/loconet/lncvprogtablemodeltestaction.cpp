#include "lncvprogtablemodeltestaction.h"
#include "lncvprogtablemodeltest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LncvProgTableModelTestAction::LncvProgTableModelTestAction(QObject *parent) : AbstractAction(tr("LncvProgTableModelTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void LncvProgTableModelTestAction::actionPerformed()
{
    LncvProgTableModelTest* smt = new LncvProgTableModelTest();
    try
    {
     QStringList testList = QStringList()
       << "testCTor"
       << "testInitTable"
       << "testGetColumnName"
       << "testGetColumnClass"
       << "tastIsCellEditable"
       << "testGetColumnCount"
       << "testGetSetValueAt"
          ;

       JUnitUtil::runTests(smt, testList);

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* LncvProgTableModelTestAction::log = LoggerFactory::getLogger("LncvProgTableModelTestAction");
