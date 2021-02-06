#include "cvutiltestaction.h"
#include "cvutiltest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

CvUtilTestAction::CvUtilTestAction(QObject* parent) : AbstractAction(tr("CvUtil Test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void CvUtilTestAction::actionPerformed()
{
 CvUtilTest* test = new CvUtilTest();
 try
 {
  QStringList testList = QStringList()
    << "testExpandCvList"
    << "testAddCvDescription"
    << "testGetMaskDescription"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* CvUtilTestAction::log = LoggerFactory::getLogger("CvUtilTestAction");
