#include "rosterentrytestaction.h"
#include "rosterentrytest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"

RosterEntryTestAction::RosterEntryTestAction(QString text, QObject* parent) : AbstractAction(text, parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void RosterEntryTestAction::actionPerformed()
{
    RosterEntryTest* ret = new RosterEntryTest();
    try
    {
     QStringList testList = QStringList()
        << "testCreate"
        << "testPartialLoad"
        << "testEmptyLoad"
        << "testFullLoad"
        << "testFromSchemaFile"
        << "testFromDtdFile"
        << "testStoreFunctionLabel"
        << "testModifyDateUnparseable"
        << "testDateFormatHistoric"
        << "testDateFormatISO"
        << "testDateFormatTraditional"
        << "testStoreFunctionLockable"
        << "testXmlLoadStore"
        << "testXmlFunctionLabelsLoadStore"
        << "testEnsureFilenameExistsNew"
        << "testEnsureFilenameExistsOld"
        << "testNoAttribute"
        << "testOneAttribute"
        << "testReplaceAttribute"
        << "testNullAttributeValue"
        << "testAttributeList"
        << "testXmlAttributesLoadStore"
        << "testStoreAttribute";
     foreach(QString test, testList)
     {
      log->info(tr("begin '%1'").arg(test));
      QMetaObject::invokeMethod(ret, test.toLocal8Bit(), Qt::DirectConnection);
      log->info(tr("end '%1'").arg(test));
     }}
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
}
Logger* RosterEntryTestAction::log = LoggerFactory::getLogger("RosterEntryTestAction");
