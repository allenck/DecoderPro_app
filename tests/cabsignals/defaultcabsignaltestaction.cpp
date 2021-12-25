#include "defaultcabsignaltestaction.h"
#include "defaultcabsignaltest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

DefaultCabSignalTestAction::DefaultCabSignalTestAction(QObject *parent) : AbstractAction(tr("DefaultCabSignalTest"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void DefaultCabSignalTestAction::actionPerformed()
{
 DefaultCabSignalTest* test = new DefaultCabSignalTest();
 try
 {
  QStringList testList = QStringList()
    <<  "testCTor"
    <<  "testSetBlock"
    <<  "testSignalSequence"
//    <<  "testSignalSequenceIdTag"
   ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* DefaultCabSignalTestAction::log = LoggerFactory::getLogger("DefaultCabSignalTestAction");
