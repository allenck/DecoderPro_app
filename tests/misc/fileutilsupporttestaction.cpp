#include "fileutilsupporttestaction.h"
#include "fileutilsupporttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"

FileUtilSupportTestAction::FileUtilSupportTestAction(QObject* parent) : AbstractAction(tr("FileUtilSupport test"), parent)
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

}

void FileUtilSupportTestAction::actionPerformed()
{
 FileUtilSupportTest* test = new FileUtilSupportTest();
 try
 {
  QStringList testList = QStringList()
    << "testGEFRel"
    << "testGEFAbs"
    << "testGEFProgramRel"
    << "testGEFProgramAbs"
    << "testGEFPrefRel"
    << "testGEFPrefAbs"
    << "testGEFHomeRel"
    << "testGEFHomeAbs"
    << "testGetpfPreferenceF"
    << "testGetpfPreferenceS"
    << "testGetpfResourceF"
    << "testGetpfPrefF"
    << "testGetpfProgramF"
    << "testGetpfProgramS"
    << "testGetpfProgramDirS"
    << "testGetpfHomeS"
    << "testGetpfHomeF"
    << "testGAFRel"
    << "testGAFProgRel"
    << "testGAFProgAbs"
    << "testGAFPrefRel"
    << "testGAFPrefAbs"
    << "testGAFHomeRel"
    << "testGAFHomeAbs"
  //  << "testCopyFile()"
  //  << "testCopyDirectoryToExistingDirectory"
  //  << "testDeleteFile"
  //  << "testAppendTextToFile"
  //  << "testFindURIPath"
  //  << "testFindURIPathLocation"
  //  << "testFindURIPathSearchPaths"
//    << "testFindExternalFilename"
       ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError* ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex->getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* FileUtilSupportTestAction::log = LoggerFactory::getLogger("FileUtilSupportTestAction");
