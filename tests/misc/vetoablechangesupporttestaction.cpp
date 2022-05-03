#include "vetoablechangesupporttestaction.h"
#include "vetoablechangesupporttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
VetoableChangeSupportTestAction::VetoableChangeSupportTestAction(QObject *parent) : AbstractAction(tr("VetoableChangeSupport"),parent){
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void VetoableChangeSupportTestAction::actionPerformed()
{
 VetoableChangeSupportTest* test = new VetoableChangeSupportTest();
 try
 {
  QStringList testList = QStringList()
    // in VetoableChangeSupportTest
    << "testFireVetoableChange_String_int_boolean_boolean"
    << "testFireVetoableChange_String_int_int_int"
    << "testFireVetoableChange_String_int_Object_Object"
    << "testFireVetoableChange_VetoableChangeEvent"
    << "testAddVetoableChangeListener_VetoableChangeListener"
    << "testAddVetoableChangeListener_String_VetoableChangeListener"
    << "testRemoveVetoableChangeListener_VetoableChangeListener"
    << "testRemoveVetoableChangeListener_String_VetoableChangeListener"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* VetoableChangeSupportTestAction::log = LoggerFactory::getLogger("VetoableChangeSupportTestAction");
