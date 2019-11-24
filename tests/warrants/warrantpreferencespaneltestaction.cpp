#include "warrantpreferencespaneltestaction.h"
#include "warrantpreferencespaneltest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
WarrantPreferencesPanelTestAction::WarrantPreferencesPanelTestAction(QObject*parent)
 : AbstractAction(tr("WarrantPreferencesPanelTest"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}
void WarrantPreferencesPanelTestAction::actionPerformed()
{
    WarrantPreferencesPanelTest* test = new WarrantPreferencesPanelTest();
    try
    {
     QStringList testList = QStringList()
       << "testCTor"
;

     JUnitUtil::runTests(test, testList);

    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* WarrantPreferencesPanelTestAction::log = LoggerFactory::getLogger("WarrantPreferencesPanelTestAction");
