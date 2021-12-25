#include "sectiontestaction.h"
#include "sectiontest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

SectionTestAction::SectionTestAction(QObject* parent) : AbstractAction(tr("Section Test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void SectionTestAction::actionPerformed()
{
 SectionTest* test = new SectionTest();
 try
 {
  QStringList testList = QStringList()
    << "SysNameConstructorTest"
    << "TwoNameStringConstructorTest"
    << "warnOnBlockAdd"
    << "warnOnBlockAddWithNoUserName"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* SectionTestAction::log = LoggerFactory::getLogger("SectionTestAction");
