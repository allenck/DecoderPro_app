#include "inputwindow.h"
#include "jtextarea.h"
#include <QPushButton>
#include <QCheckBox>
#include "jfilechooser.h"
#include "fileutil.h"
#include <QLabel>
#include "borderlayout.h"
#include <QScrollArea>
#include "flowlayout.h"
#include "jmrijframe.h"
#include "file.h"
#include <QTextStream>
#include "pythonwrappers.h"
#include <QTextBlock>
#include <QTextCursor>
#include <QCursor>
//#include "jythonwindow.h"
#include "userpreferencesmanager.h"
#include "instancemanager.h"
#include <QThread>
#include "scripts/scriptoutput.h"
#include "scripts/jmriscriptenginemanager.h"
#include <QComboBox>

//InputWindow::InputWidow(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 * This Action runs creates a JFrame for sending input to the global jython
 * interpreter
 *
 * @author Bob Jacobsen Copyright (C) 2004
 * @version $Revision: 29543 $
 */
// /*public*/ class InputWindow extends JPanel {

/**
 *
 */
//private static final long serialVersionUID = -8043631915757357490L;
//static java.util.ResourceBundle rb = java.util.ResourceBundle.getBundle("jmri.jmrit.jython.JythonBundle");

//JFileChooser userFileChooser;
//{
//    userFileChooser = new JFileChooser(FileUtil.getScriptsPath());
//    jmri.util.FileChooserFilter filt = new jmri.util.FileChooserFilter("Python script files");
//    filt.addExtension("py");
//    userFileChooser.setFileFilter(filt);
//}

/*public*/ InputWindow::InputWindow(QWidget *parent)
 : QWidget(parent)
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 alwaysOnTop = QString(this->metaObject()->className()) + ".alwaysOnTop";

 alwaysOnTopCheckBox = new QCheckBox();
 languages = new QComboBox();
 languages->addItem("PythonQt");
 userFileChooser = new JFileChooser(FileUtil::getScriptsPath());
// jmri.util.FileChooserFilter filt = new jmri.util.FileChooserFilter("Python script files");
// filt.addExtension("py");
 userFileChooser->setFileFilter("Python 'pyq' Script files (*.pyq);;Python 'py' Script files  (*.py);;Python 'py & pyq' Script files (*.py *.pyq);;All files (*.*)");
 log = new Logger("InputWindow");

 //setLayout(new javax.swing.BoxLayout(this, javax.swing.BoxLayout.Y_AXIS));
 QVBoxLayout* thisLayout;
 setLayout(thisLayout = new QVBoxLayout());

 area = new JTextArea(12, 50);
 area->setTabStopWidth(4);

 // from: http://stackoverflow.com/questions/5139995/java-column-number-and-line-number-of-cursors-current-position
 // area.addCaretListener(new CaretListener() {
 //     // Each time the caret is moved, it will trigger the listener and its method caretUpdate.
 //     // It will then pass the event to the update method including the source of the event (which is our textarea control)
 //     /*public*/ void caretUpdate(CaretEvent e) {
 //         JTextArea editArea = (JTextArea) e.getSource();

 //         // Lets start with some default values for the line and column.
 //         int linenum = 1;
 //         int columnnum = 1;

 //         // We create a try catch to catch any exceptions. We will simply ignore such an error for our demonstration.
 //         try {
 //             // First we find the position of the caret. This is the number of where the caret is in relation to the start of the JTextArea
 //             // in the upper left corner. We use this position to find offset values (eg what line we are on for the given position as well as
 //             // what position that line starts on.
 //             int caretpos = editArea.getCaretPosition();
 //             linenum = editArea.getLineOfOffset(caretpos);

 //             // We subtract the offset of where our line starts from the overall caret position.
 //             // So lets say that we are on line 5 and that line starts at caret position 100, if our caret position is currently 106
 //             // we know that we must be on column 6 of line 5.
 //             columnnum = caretpos - editArea.getLineStartOffset(linenum);

 //             // We have to add one here because line numbers start at 0 for getLineOfOffset and we want it to start at 1 for display.
 //             linenum += 1;
 //         } catch (Exception ex) {
 //         }

 //         // Once we know the position of the line and the column, pass it to a helper function for updating the status bar.
 //         updateStatus(linenum, columnnum);
 //     }
 // });
 connect(area, SIGNAL(cursorPositionChanged()), this, SLOT(on_cursorPositionChanged()));

 QScrollArea* js = new QScrollArea(/*area*/);
 js->setWidget(area);
 js->setWidgetResizable(true);
// js.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
// js.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
 thisLayout->addWidget(js);//, BorderLayout::Center);

 QWidget* p = new QWidget();
 FlowLayout* pLayout;
 p->setLayout(pLayout =new FlowLayout());
 pLayout->addWidget(loadButton = new QPushButton(tr("Load")));
 pLayout->addWidget(storeButton = new QPushButton(tr("Store")));
 pLayout->addWidget(button = new QPushButton(tr("Execute")));
 pLayout->addWidget(stopButton = new QPushButton(tr("Stop")));
 stopButton->setEnabled(false);

 alwaysOnTopCheckBox->setText(tr("Window always on Top"));
 alwaysOnTopCheckBox->setVisible(true);
 alwaysOnTopCheckBox->setChecked(pref->getSimplePreferenceState(alwaysOnTop));
 alwaysOnTopCheckBox->setToolTip(tr("If checked, this window be always be displayed in front of any other window"));
 if(pref->getSaveWindowLocation(QString(this->metaObject()->className())))
 {
  this->move(pref->getWindowLocation(QString(this->metaObject()->className())));
 }
 if(pref->getSaveWindowSize(QString(this->metaObject()->className())))
 {
  this->resize(pref->getWindowSize(QString(this->metaObject()->className())));
 }
 pLayout->addWidget(alwaysOnTopCheckBox);

 status = new QLabel("         ");   // create some space for the counters
 pLayout->addWidget(status);
 updateStatus(1, 0);

 thisLayout->addWidget(p); //, BorderLayout::South);

// button.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         buttonPressed();
//     }
// });
 connect(button, SIGNAL(clicked()), this, SLOT(buttonPressed()));
// loadButton.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         loadButtonPressed();
//     }
// });
 connect(loadButton, SIGNAL(clicked()),this, SLOT(loadButtonPressed()));

 // storeButton.addActionListener(new java.awt.event.ActionListener() {
 //     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
 //         storeButtonPressed();
 //     }
 // });
 connect(storeButton, SIGNAL(clicked()), this, SLOT(storeButtonPressed()));

// alwaysOnTopCheckBox.addActionListener(new java.awt.event.ActionListener() {
//     /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//         if (getTopLevelAncestor() != NULL) {
//             ((jmri.util.JmriJFrame) getTopLevelAncestor()).setAlwaysOnTop(alwaysOnTopCheckBox.isSelected());
//         }
//     }
// });
 connect(alwaysOnTopCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_alwaysOnTop_toggled(bool)));

 // set a monospaced font
 int size = area->font().pointSize();
 area->setFont(QFont("Monospace",size, QFont::Normal));
}

void InputWindow::on_alwaysOnTop_toggled(bool bChecked)
{
 ;
 if (window() != NULL)
 {
  ((JFrame*)window())->setAlwaysOnTop(bChecked);
  pref->setSimplePreferenceState(alwaysOnTop, alwaysOnTopCheckBox->isChecked());
 }
}

void InputWindow::on_cursorPositionChanged()
{
 JTextArea* editArea = area;
// Lets start with some default values for the line and column.
int linenum = 1;
int columnnum = 1;

// We create a try catch to catch any exceptions. We will simply ignore such an error for our demonstration.
try {
    // First we find the position of the caret. This is the number of where the caret is in relation to the start of the JTextArea
    // in the upper left corner. We use this position to find offset values (eg what line we are on for the given position as well as
    // what position that line starts on.
    //int caretpos = editArea.getCaretPosition();
 int caretpos = editArea->textCursor().position();
 Q_UNUSED(caretpos);
    //linenum = editArea.getLineOfOffset(caretpos);
 linenum = editArea->textCursor().blockNumber();


    // We subtract the offset of where our line starts from the overall caret position.
    // So lets say that we are on line 5 and that line starts at caret position 100, if our caret position is currently 106
    // we know that we must be on column 6 of line 5.
    //columnnum = caretpos - editArea.getLineStartOffset(linenum);
    columnnum = /*caretpos -*/ editArea->textCursor().positionInBlock();

    // We have to add one here because line numbers start at 0 for getLineOfOffset and we want it to start at 1 for display.
    linenum += 1;
 }
 catch (Exception ex)
 {
 }

  // Once we know the position of the line and the column, pass it to a helper function for updating the status bar.
  updateStatus(linenum, columnnum);
}


// This helper function updates the status bar with the line number and column number.
/*private*/ void InputWindow::updateStatus(int linenumber, int columnnumber) {
    status->setText("    " + QString::number(linenumber) + ":" + QString::number(columnnumber));
}

/**
 *
 * @param fileChooser
 * @return true if successful
 */
/*protected*/ bool InputWindow::loadFile(JFileChooser* fileChooser)
{
 bool results = true;
 File* file = getFile(fileChooser);
 if (file != NULL)
 {
  try
  {
   QString fileData;// = new StringBuilder(1024);
   //   BufferedReader reader = new BufferedReader(new FileReader(file));
   //   char[] buf = new char[1024];
   //   int numRead = 0;
   //   while ((numRead = reader.read(buf)) != -1) {
   //       String readData = String.valueOf(buf, 0, numRead);
   //       fileData.append(readData);
   //       buf = new char[1024];
   //   }
   //   reader.close();
   QFile f(file->getPath());
   if(!f.open(QFile::ReadOnly | QFile::Text))
   {
    results = false;
   }
   QTextStream* stream = new QTextStream(&f);
   fileData = stream->readAll();
   f.close();

   fileData = fileData.replace("\t", "  ");

   area->setText(fileData/*.toString()*/);

  } catch (Exception e)
  {
   log->error("Unhandled problem in loadFile: " + e.getMessage());
  }
 }
 else
 {
  results = false;   // We assume that as the file is NULL then the user has clicked cancel.
 }
 return results;
}

/**
 *
 * @param fileChooser
 * @return true if successful
 */
/*protected*/ bool InputWindow::storeFile(JFileChooser* fileChooser)
{
 bool results = true;
 File* file = getFile(fileChooser);
 if (file != NULL)
 {
//        try {
         // check for possible overwrite
   //            if (file->exists()) {
   //                int selectedValue = JOptionPane.showConfirmDialog(NULL,
   //                        "File " + file.getName() + " already exists, overwrite it?",
   //                        "Overwrite file?",
   //                        JOptionPane.OK_CANCEL_OPTION);
   //                if (selectedValue != JOptionPane.OK_OPTION) {
   //                    results = false; // user clicked no to override
   //                    return results;
   //                }
   //            }

  QString fileData = area->toPlainText();
//            BufferedWriter writer = new BufferedWriter(new FileWriter(file));
//            writer.append(fileData);
//            writer.close();
  QFile f(file->getPath());
  if(f.open(QFile::WriteOnly | QFile::Text))
  {
   QTextStream* stream = new QTextStream(&f);
   *stream << fileData;
  } //catch (Exception e) {
  else
  {
   log->error("Unhandled problem in storeFile: " /*+ e.get*/ + f.errorString());
   results = false;
  }
 }
 else
 {
  results = false;   // If the file is NULL then the user has clicked cancel.
 }
 return results;
}

/*static*/ /*public*/ File* InputWindow::getFile(JFileChooser* fileChooser)
{
 Logger* log = new Logger("InputWindow");
 //fileChooser.rescanCurrentDirectory();
 int retVal = fileChooser->showDialog(NULL, NULL);
 if (retVal != JFileChooser::APPROVE_OPTION)
 {
  return NULL;  // give up if no file selected
 }
 if (log->isDebugEnabled())
 {
  log->debug("Open file: " + fileChooser->getSelectedFile()->getPath());
 }
 QString filename = fileChooser->getSelectedFile()->getPath();
 if(!(filename.endsWith(".py") || filename.endsWith(".pyq")))
 {
  filename = filename.append(".py");
 }
 return new File(filename);
}

void InputWindow::loadButtonPressed()
{
 userFileChooser->setDialogType(JFileChooser::OPEN_DIALOG);
 userFileChooser->setApproveButtonText(tr("Load"));
 userFileChooser->setDialogTitle(tr("Load Script..."));

 bool results = loadFile(userFileChooser);
 log->debug(results ? "load was successful" : "load failed");
// if (!results)
// {
//  if(userFileChooser->getSelectedFile() == NULL)
//   log->warn("No file selected");
//  else
//   log->warn("Not loading file: " + userFileChooser->getSelectedFile()->getPath());
// }
}

void InputWindow::storeButtonPressed()
{
 userFileChooser->setDialogType(JFileChooser::SAVE_DIALOG);
 userFileChooser->setApproveButtonText(tr("Store"));
 userFileChooser->setDialogTitle(tr("Store Script..."));

 bool results = storeFile(userFileChooser);
 log->debug(results ? "store was successful" : "store failed");
 if (!results)
 {
  log->warn("Not storing file: " + userFileChooser->getSelectedFile()->getPath());
 }
}

void InputWindow::buttonPressed()
{
 //PythonInterp.getPythonInterpreter();
 interp = PythonQt::self()->getMainModule();

 //PythonWrappers::defineClasses();

// QString cmd = area->toPlainText() + "\n";

// // The command must end with exactly one \n
// while ((cmd.length() > 1) && cmd.at(cmd.length() - 2) == '\n')
// {
//  cmd = cmd.mid(0, cmd.length() - 1);
// }

// // add the text to the output frame
// QString echo = ">>> " + cmd;
// // intermediate \n characters need to be prefixed
// echo = echo.replace("\n", "\n... ");
// echo = echo.mid(0, echo.length() - 4);
// //PythonInterp.getOutputArea().append(echo);
// JythonWindow::instance()->appendText(echo);

// // and execute
// //PythonInterp.execCommand(cmd);
// //interp.evalScript(cmd);
// stopButton->setEnabled(true);
// loadButton->setEnabled(false);
// button->setEnabled(false);
// storeButton->setEnabled(false);

// Worker* worker = new Worker(cmd, this);
// thread = new QThread;
// worker->moveToThread(thread);
// connect(thread, SIGNAL(started()), worker, SLOT(process()));
// connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
// connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
// connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
// connect(PythonQt::self(), SIGNAL(pythonStdErr(QString)), this, SLOT(on_pythonStdErr(QString)));
// //connect(stopButton, SIGNAL(clicked()), worker, SLOT(stopRequested()));
// connect(stopButton, SIGNAL(clicked()), worker, SLOT(stopRequested()));

// thread->start();

// while(thread->isRunning())
// {
//  loop.exec();
// }
// stopButton->setEnabled(false);
// loadButton->setEnabled(true);
// button->setEnabled(true);
// storeButton->setEnabled(true);
 ScriptOutput::writeScript(area->text);
 try
 {
  JmriScriptEngineManager::getDefault()->eval(area->text, JmriScriptEngineManager::getDefault()->getEngineByName((QString) languages->currentText()));
 } catch (ScriptException ex) {
     log->error("Error executing script", &ex);
 }
}

Worker::Worker(QString script, InputWindow *parent)
{
 this->parent = parent;
 this->script = script;
 interp = PythonQt::self()->getMainModule();

}

void Worker::process()
{
 QVariant rslt = interp.evalScript(script);
 emit finished();
}

void Worker::stopRequested()
{
 emit finished();
 parent->loop.exit(1);
}

void InputWindow::stopButtonPressed()
{
 thread->quit();
}

void InputWindow::on_pythonStdErr(QString)
{
 stopButton->setEnabled(false);
 loadButton->setEnabled(true);
 button->setEnabled(true);
 storeButton->setEnabled(true);
}
