#include "rosterentrytestaction.h"
#include "rosterentrytest.h"
#include "joptionpane.h"
#include "assert1.h"

RosterEntryTestAction::RosterEntryTestAction(QString text, QObject* parent) : AbstractAction(text, parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void RosterEntryTestAction::actionPerformed()
{
    RosterEntryTest* ret = new RosterEntryTest();
    ret->setUp();
    try
    {
        ret->testCreate();
        ret->testPartialLoad();
        ret->testEmptyLoad();
        ret->testFullLoad();
        ret->testFromSchemaFile();
        ret->testFromDtdFile();
        ret->testStoreFunctionLabel();
        ret->testModifyDateUnparseable();
        ret->testDateFormatHistoric();
        ret->testDateFormatISO();
        ret->testDateFormatTraditional();
        ret->testStoreFunctionLockable();
        ret->testXmlLoadStore();
        ret->testXmlFunctionLabelsLoadStore();
        ret->testEnsureFilenameExistsNew();
        ret->testEnsureFilenameExistsOld();
        ret->testNoAttribute();
        ret->testOneAttribute();
        ret->testReplaceAttribute();
        ret->testNullAttributeValue();
        ret->testAttributeList();
        ret->testXmlAttributesLoadStore();
        ret->testStoreAttribute();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);

    }
    ret->tearDown();
}
