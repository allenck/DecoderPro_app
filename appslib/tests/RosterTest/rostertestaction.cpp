#include "rostertestaction.h"
#include "rostertest.h"
#include "../assert1.h"
#include "joptionpane.h"
#include "loggerfactory.h"

RosterTestAction::RosterTestAction( QObject* parent) : AbstractAction(tr("Roster Test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}
RosterTestAction::RosterTestAction(QString text, QObject* parent) : AbstractAction(text, parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


void RosterTestAction::actionPerformed()
{
    RosterTest* rt = new RosterTest();
    try
    {
        QStringList testList = QStringList()
             << "testDirty"
             << "testAdd"
             << "testDontAddNullEntriesLater"
             << "testDontAddNullEntriesFirst"
             << "testAddrSearch"
             << "testGetByDccAddress"
             << "testSearchList"
             << "testComboBox"
             << "testBackupFile"
             << "testReadWrite"
             << "testAttributeAccess"
             << "testAttributeValueAccess"
             << "testAttributeList"
             << "testDefaultLocation"
             << "testProfileOnePointForward"
             << "testProfileTwoPointForward"
             << "testProfileTwoPointReverse"
             << "testProfileTwoPointForwardGetThrottleSetting"
             << "testProfileTwoPointReverseGetThrottleSetting";
        foreach(QString test, testList)
        {
         log->info(tr("begin '%1'").arg(test));
         QMetaObject::invokeMethod(rt, test.toLocal8Bit(), Qt::DirectConnection);
         log->info(tr("end '%1'").arg(test));
        }
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}

Logger* RosterTestAction::log = LoggerFactory::getLogger("RosterTestAction");
