#include "pointdetailstestaction.h"
#include "pointdetailstest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

PointDetailsTestAction::PointDetailsTestAction(QObject *parent) : AbstractAction(tr("PointDetailsTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void PointDetailsTestAction::actionPerformed()
{
 PointDetailsTest* test = new PointDetailsTest();
 try
 {
  QStringList testList = QStringList()
    << "testCTor"
    << "testGetters"
    << "testNxButton"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* PointDetailsTestAction::log = LoggerFactory::getLogger("PointDetailsTestAction");
