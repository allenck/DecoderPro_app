#include "layoutshapetestaction.h"
#include "layoutshapetest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

LayoutShapeTestAction::LayoutShapeTestAction(QObject* parent) : AbstractAction(tr("LayoutShape Test"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));

}

void LayoutShapeTestAction::actionPerformed()
{
 LayoutShapeTest* test = new LayoutShapeTest();
 try
 {
  QStringList testList = QStringList()
    << "testNew"
    << "testToString"
    << "testGetDisplayName"
    << "testGetType"
   #if 0
    << "testSetType"
    << "testGetBounds"
    << "testSetCoordsCenter"
    << "testScaleCoords"
    << "testTranslateCoords"
    << "testFindHitPointType"
   #endif
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LayoutShapeTestAction::log = LoggerFactory::getLogger("LayoutShapeTestAction");
