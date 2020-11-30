#include "controlpaneltestaction.h"
#include "controlpaneltest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"

ControlPanelTestAction::ControlPanelTestAction(QObject* parent) : AbstractAction(tr("ControlPanelTest "), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void ControlPanelTestAction::actionPerformed()
{
 ControlPanelTest* test = new ControlPanelTest();
 try
 {
  QStringList testList = QStringList()
    <<  "testCtor"
    <<  "testExtendedThrottle"
    <<  "testIconThrottle"
    ;
  JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError er)
 {
     JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}

Logger* ControlPanelTestAction::log = LoggerFactory::getLogger("ControlPanelTestAction");
