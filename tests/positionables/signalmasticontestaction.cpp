#include "signalmasticontestaction.h"
#include "signalmasticontest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

SignalMastIconTestAction::SignalMastIconTestAction(QObject* parent)
 : AbstractAction(tr("SignalMastIconTest"),parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void SignalMastIconTestAction::actionPerformed()
{
    SignalMastIconTest* test = new SignalMastIconTest();
    try
    {
     QStringList testList = QStringList()
       // PositionableTestBase:
       << "testGetAndSetPositionable"
       << "testGetAndSetEditable"
       << "testGetAndSetShowToolTip"
       << "testGetAndSetToolTip"
       << "testGetAndSetViewCoordinates"
       << "testGetAndSetControlling"
       << "testGetAndSetHidden"
       << "testGetAndSetDisplayLevel"
       << "testGetAndSetEditor"
       << "testClone"
       << "testMaxWidth"
       << "testMaxHeight"
       << "testGetAndSetScale"
       << "testGetAndSetRotationDegrees"
       << "testGetTextComponent"
       << "testStoreItem"
       << "testDoViemMenu"
       << "testGetNameString"
       << "testShow"

     // PositionableIconTest
       << "testCTor"

     // SignalMastIconTest
     << "testShowText"
     << "testShowIcon";

     JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError* er)
    {
        JOptionPane::showMessageDialog(nullptr, er->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* SignalMastIconTestAction::log = LoggerFactory::getLogger("SignalMastIconTestAction");
