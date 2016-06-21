#include "runjythonscript.h"
#include <QWidget>
#include "file.h"
#include "fileutil.h"
#include "jfilechooser.h"
#include "PythonQt.h"
//#include "PythonQt_QtAll.h"
#include "jframe.h"
#include "pythonwrappers.h"

RunJythonScript::RunJythonScript(QObject *parent) :
  JmriAbstractAction(tr("Run Jython Script"),parent)
{
 common();
}
/**
 * This Action runs a script by invoking a Jython interpreter.
 * <P>
 * A standard JMRI-Jython dialog is defined by invoking the
 * "jython/jmri-defaults.py" file before starting the user code.
 * <P>
 * There are two constructors. One, without a script file name, will open a
 * FileDialog to prompt for the file to use. The other, with a File object, will
 * directly invoke that file.
 * <P>
 * Access is via Java reflection so that both users and developers can work
 * without the jython.jar file in the classpath. To make it easier to read the
 * code, the "non-reflection" statements are in the comments.
 *
 * @author	Bob Jacobsen Copyright (C) 2004, 2007
 * @version $Revision: 28746 $
 */
// /*public*/ class RunJythonScript extends JmriAbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -2957647278966956841L;

/*public*/ RunJythonScript::RunJythonScript(QString s, QWidget* wi) : JmriAbstractAction(s, wi)
{
 //super(s, wi);
 common();
}

/*public*/ RunJythonScript::RunJythonScript(QString s, QIcon i, QWidget* wi)
 : JmriAbstractAction(s, i, (WindowInterface*)wi)
{
 //super(s, i, wi);
 common();
}

/**
 * Constructor that, when action is invoked, opens a JFileChooser to select
 * file to invoke.
 *
 * @param name Action name
 */
/*public*/ RunJythonScript::RunJythonScript(QString name, QObject *parent) : JmriAbstractAction(name, parent)
{
 //super(name);
 common();
 configuredFile = NULL;
}

/**
 * Constructor that, when action is invoked, directly invokes the provided
 * File
 *
 * @param name Action name
 */
/*public*/ RunJythonScript::RunJythonScript(QString name, File* file, QObject *parent )
 : JmriAbstractAction(name, parent)
{
 //super(name);
 common();
 this->configuredFile = file;
}

/**
 * We always use the same file chooser in this class, so that the user's
 * last-accessed directory remains available.
 */
/*static*/ JFileChooser* RunJythonScript::fci = NULL;

void RunJythonScript::common()
{
 this->configuredFile = NULL;
 log = new Logger("RunJythonScript");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * Invoking this action via an event triggers display of a file dialog. If a
 * file is selected, it's then invoked as a script.
 *
 * @param e
 */
/*public*/ void RunJythonScript::actionPerformed(ActionEvent* e)
{
 File* thisFile;
 if (configuredFile != NULL)
 {
  thisFile = configuredFile;
 }
 else
 {
  thisFile = selectFile();
 }

 // and invoke that file
 if (thisFile != NULL)
 {
  invoke(thisFile);
 }
 else
 {
  log->info("No file selected");
  dispose();
 }
}

File* RunJythonScript:: selectFile()
{
 if (fci == NULL)
 {
  //fci = new JFileChooser(System.getProperty("user.dir")+java.io.File.separator+"jython");
  fci = new JFileChooser(FileUtil::getScriptsPath());
  //FileChooserFilter filt = new FileChooserFilter("Python script files");
  //filt.addExtension("py");
  QString filt = "Python script files (*.py);; All files (*.*)";
  fci->setFileFilter(filt);
  fci->setDialogTitle("Find desired script file");
 }
 else
 {
  // when reusing the chooser, make sure new files are included
//  fci->rescanCurrentDirectory();
 }

 int retVal = fci->showOpenDialog(NULL);
 // handle selection or cancel
 if (retVal == JFileChooser::APPROVE_OPTION)
 {
  File* file = fci->getSelectedFile();
  // Run the script from it's filename
  return file;
 }
 return NULL;
}

bool RunJythonScript::firstTime = true;

void RunJythonScript::invoke(File* file)
{
 disconnect(PythonQt::self(),SIGNAL(pythonStdErr(QString)));

 PythonWrappers::defineClasses();
 //jmri.util.PythonInterp.runScript(jmri.util.FileUtil.getExternalFilename(file.toString()));
 if(firstTime)
  connect(PythonQt::self(), SIGNAL(pythonStdErr(QString)), this, SLOT(On_stdErr(QString)));
 firstTime = false;
 PythonQt::self()->getMainModule().evalFile(file->getPath());
 PythonQt::self()->clearError();
}

// never invoked, because we overrode actionPerformed above
/*public*/ JmriPanel* RunJythonScript::makePanel()
{
 throw new IllegalArgumentException("Should not be invoked");
}

void RunJythonScript::On_stdErr(const QString& s)
{
  //_hadError = true;
  _stdErr += s;
  int idx;
  while ((idx = _stdErr.indexOf('\n'))!=-1)
  {
//    consoleMessage(_stdErr.left(idx));
//    std::cerr << _stdErr.left(idx).toLatin1().data() << std::endl;
   log->error( _stdErr.left(idx) );
    _stdErr = _stdErr.mid(idx+1);
  }

}
