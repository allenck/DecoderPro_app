#include "lnlighttestaction.h"
#include "lnlighttest.h"
#include "assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"
#include "junitutil.h"
LnLightTestAction::LnLightTestAction(QObject *parent) : AbstractAction(tr("Light test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void LnLightTestAction::actionPerformed()
{
 LnLightTest* test = new LnLightTest();
 try
 {
  QStringList testList = QStringList()
    << "testCTor";
   JUnitUtil::runTests(test, testList);
  }
  catch (AssertionError er)
  {
      JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
  }
}
