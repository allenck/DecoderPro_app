#include "colorchooserpaneltestaction.h"
#include "colorchooserpaneltest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

ColorChooserPanelTestAction::ColorChooserPanelTestAction(QObject *parent) : AbstractAction(tr("ColorChooserPanel test"),parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void ColorChooserPanelTestAction::actionPerformed()
{
 ColorChooserPanelTest* test = new ColorChooserPanelTest();
 try
 {
  QStringList testList = QStringList()
    << "testCtor"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* ColorChooserPanelTestAction::log = LoggerFactory::getLogger("ColorChooserPanelTestAction");
