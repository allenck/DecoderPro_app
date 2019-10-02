#include "profilemanagertestaction.h"
#include "profilemanagertest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"


ProfileManagerTestAction::ProfileManagerTestAction(QObject *parent) : AbstractAction(tr("Profile Manager Test"), parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

ProfileManagerTestAction::ProfileManagerTestAction(QString text, QObject *parent) : AbstractAction(text, parent)
{
connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

void ProfileManagerTestAction::actionPerformed()
{
    ProfileManagerTest* pmt = new ProfileManagerTest();
    try
    {
     QStringList testList = QStringList()
         << "testCTor"
         << "testSetActiveProfile_Profile"
         << "testSetActiveProfile_String";
     foreach(QString test, testList)
     {
      log->info(tr("begin '%1'").arg(test));
      QMetaObject::invokeMethod(pmt, test.toLocal8Bit(), Qt::DirectConnection);
      log->info(tr("end '%1'").arg(test));
     }
    }
    catch (AssertionError ex)
    {
        JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
Logger* ProfileManagerTestAction::log = LoggerFactory::getLogger("ProfileManagerTestAction");

