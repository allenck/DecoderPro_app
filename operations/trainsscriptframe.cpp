#include "trainsscriptframe.h"
#include "jfilechooser.h"
#include "trainmanager.h"
#include <QScrollArea>
#include <QPushButton>
#include <QGroupBox>
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "xmlfile.h"
#include "file.h"
#include "fileutil.h"
#include "operationsxml.h"
#include "setup.h"
#include <QLabel>

namespace Operations
{
 /**
  * Frame for user edit of startup and shutdown operation scripts.
  *
  * @author Bob Jacobsen Copyright (C) 2004
  * @author Dan Boudreau Copyright (C) 2011
  * @version $Revision: 29897 $
  */
 ///*public*/ class TrainsScriptFrame extends OperationsFrame {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -2270290709118571365L;


 /*public*/ TrainsScriptFrame::TrainsScriptFrame(QWidget* parent)  : OperationsFrame(parent){
     //super();
 log = new Logger("TrainsScriptFrame");
     trainManager = TrainManager::instance();

     // script panels
     pStartUpScript = new QWidget();
     pStartUpScript->setLayout(new QVBoxLayout);
     pShutDownScript = new QWidget();
     pShutDownScript->setLayout(new QVBoxLayout);
     // major buttons
     addStartUpScriptButton = new QPushButton(tr("Add Script"));
     addShutDownScriptButton = new QPushButton(tr("Add Script"));
     runStartUpScriptButton = new QPushButton(tr("Run Scripts"));
     runShutDownScriptButton = new QPushButton(tr("Run Scripts"));
     saveButton = new QPushButton(tr("Save"));
     /**
      * We always use the same file chooser in this class, so that the user's
      * last-accessed directory remains available.
      */
      fc = XmlFile::userFileChooser(tr("Python script files"), "py"); // NOI18N
 }

 /*public*/ void TrainsScriptFrame::initComponents()
 {
     // Set up script options in a Scroll Pane..
  QGroupBox* startupScriptFrame = new QGroupBox;
  startupScriptFrame->setLayout(new QVBoxLayout);
  startUpScriptPane = new QScrollArea(/*pStartUpScript*/);
  startUpScriptPane->setWidgetResizable(true);
  startupScriptFrame->layout()->addWidget(startUpScriptPane);
//     startUpScriptPane
//             .setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//     startUpScriptPane.setBorder(BorderFactory.createTitledBorder(tr("ScriptsStartUp")));
  startupScriptFrame->setStyleSheet(gbStyleSheet);
  startupScriptFrame->setTitle(tr("Run the following scripts at startup"));

  QGroupBox* shutDownScriptFrame = new QGroupBox;
  shutDownScriptFrame->setLayout(new QVBoxLayout);
  shutDownScriptPane = new QScrollArea(/*pShutDownScript*/);
  shutDownScriptPane->setWidgetResizable(true);
  shutDownScriptFrame->layout()->addWidget(shutDownScriptPane);
//    shutDownScriptPane
//            .setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//    shutDownScriptPane
//            .setBorder(BorderFactory.createTitledBorder(tr("ScriptsShutDown")));
  shutDownScriptFrame->setStyleSheet(gbStyleSheet);
  shutDownScriptFrame->setTitle(tr("Run the following scripts at shutdown"));

     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Layout the panel by rows
  // row 1
  updateStartUpScriptPanel();

  // row 3
  updateShutDownScriptPanel();

  // row 4 buttons
  QWidget* pB = new QWidget();
  pB->setLayout(new GridBagLayout());
  addItem(pB, saveButton, 3, 0);

  startUpScriptPane->setWidget(pStartUpScript);
  thisLayout->addWidget(/*startUpScriptPane*/startupScriptFrame);
  shutDownScriptPane->setWidget(pShutDownScript);
  thisLayout->addWidget(/*shutDownScriptPane*/shutDownScriptFrame);
  thisLayout->addWidget(pB);

  // setup buttons
  addButtonAction(addStartUpScriptButton);
  addButtonAction(addShutDownScriptButton);
  addButtonAction(runStartUpScriptButton);
  addButtonAction(runShutDownScriptButton);
  addButtonAction(saveButton);

  enableButtons(true);

  addHelpMenu("package.jmri.jmrit.operations.Operations_TrainScripts", true); // NOI18N
  packFrame();
  initMinimumSize();
 }

 /*private*/ void TrainsScriptFrame::updateStartUpScriptPanel() {
     //pStartUpScript.removeAll();
 QLayoutItem* item;
 while ( ( item = pStartUpScript->layout()->takeAt( 0 ) ) != NULL )
 {
     delete item->widget();
     delete item;
 }
 pStartUpScript->setLayout(new GridBagLayout());
     addItem(pStartUpScript, addStartUpScriptButton, 0, 0);

     // load any existing startup scripts
     QStringList scripts = trainManager->getStartUpScripts();
     if (scripts.size() > 0) {
         addItem(pStartUpScript, runStartUpScriptButton, 1, 0);
     }
     for (int i = 0; i < scripts.size(); i++)
     {
      QPushButton* removeStartUpScripts = new QPushButton(tr("RemoveScript"));
      removeStartUpScripts->setObjectName(scripts.at(i));
//      removeStartUpScripts.addActionListener(new java.awt.event.ActionListener() {
//          /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//              buttonActionRemoveStartUpScript(e);
//          }
//      });
      connect(removeStartUpScripts, SIGNAL(clicked(bool)), this, SLOT(buttonActionRemoveStartUpScript(QWidget*)));
      addButtonAction(removeStartUpScripts);
      QLabel* pathname = new QLabel(scripts.at(i));
      addItem(pStartUpScript, removeStartUpScripts, 0, i + 1);
      addItem(pStartUpScript, pathname, 1, i + 1);
  }
 }

 /*private*/ void TrainsScriptFrame::updateShutDownScriptPanel() {
     //pShutDownScript.removeAll();
 QLayoutItem* item;
 while ( ( item = pShutDownScript->layout()->takeAt( 0 ) ) != NULL )
 {
     delete item->widget();
     delete item;
 }
 pShutDownScript->setLayout(new GridBagLayout());
  addItem(pShutDownScript, addShutDownScriptButton, 0, 0);

  // load any existing shutdown scripts
  QStringList scripts = trainManager->getShutDownScripts();
  if (scripts.size() > 0) {
      addItem(pShutDownScript, runShutDownScriptButton, 1, 0);
  }
  for (int i = 0; i < scripts.size(); i++)
  {
   QPushButton* removeShutDownScripts = new QPushButton(tr("RemoveScript"));
   removeShutDownScripts->setObjectName(scripts.at(i));
//   removeShutDownScripts.addActionListener(new java.awt.event.ActionListener() {
//       /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//           buttonActionRemoveShutDownScript(e);
//       }
//   });
   connect(removeShutDownScripts, SIGNAL(clicked(bool)), this, SLOT(buttonActionRemoveShutDownScript()));
   QLabel* pathname = new QLabel(scripts.at(i));
   addItem(pShutDownScript, removeShutDownScripts, 0, i + 1);
   addItem(pShutDownScript, pathname, 1, i + 1);
  }
 }

 // Save train, add scripts buttons
 /*public*/ void TrainsScriptFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
  if (source == addStartUpScriptButton) {
      log->debug("train add move script button activated");
      File* f = selectFile();
      if (f != NULL) {
          trainManager->addStartUpScript(FileUtil::getPortableFilename(f));
          updateStartUpScriptPanel();
          packFrame();
      }
  }
  if (source == addShutDownScriptButton) {
      log->debug("train add termination script button activated");
      File* f = selectFile();
      if (f != NULL) {
          trainManager->addShutDownScript(FileUtil::getPortableFilename(f));
          updateShutDownScriptPanel();
          packFrame();
      }
  }
  if (source == runStartUpScriptButton) {
      runScripts(trainManager->getStartUpScripts());
  }
  if (source == runShutDownScriptButton) {
      runScripts(trainManager->getShutDownScripts());
  }
  if (source == saveButton) {
      log->debug("Save button activated");
      OperationsXml::save();
      if (Setup::isCloseWindowOnSaveEnabled()) {
          dispose();
      }
  }
 }

 /*public*/ void TrainsScriptFrame::buttonActionRemoveStartUpScript(QWidget* ae) {
     QPushButton* rbutton = (QPushButton*) ae;
     log->debug("remove move script button activated " + rbutton->objectName());
     trainManager->deleteStartUpScript(rbutton->objectName());
     updateStartUpScriptPanel();
     packFrame();
 }

 /*public*/ void TrainsScriptFrame::buttonActionRemoveShutDownScript(QWidget* ae) {
     QPushButton* rbutton = (QPushButton*) ae;
     log->debug("remove termination script button activated " + rbutton->objectName());
     trainManager->deleteShutDownScript(rbutton->objectName());
     updateShutDownScriptPanel();
     packFrame();
 }


 /*private*/ File* TrainsScriptFrame::selectFile() {
     if (fc == NULL) {
         log->error("Could not find user directory");
     } else {
         fc->setDialogTitle(tr("FindDesiredScriptFile"));
         // when reusing the chooser, make sure new files are included
         //fc.rescanCurrentDirectory();
         int retVal = fc->showOpenDialog(NULL);
         // handle selection or cancel
         if (retVal == JFileChooser::APPROVE_OPTION) {
             File* file = fc->getSelectedFile();
             // Run the script from it's filename
             return file;
         }
     }
     return NULL;
 }

 /*private*/ void TrainsScriptFrame::enableButtons(bool enabled) {
     addStartUpScriptButton->setEnabled(enabled);
     addShutDownScriptButton->setEnabled(enabled);
     saveButton->setEnabled(enabled);
 }

 /*private*/ void TrainsScriptFrame::runScripts(QStringList scripts) {
     foreach (QString script, scripts) {
         QString scriptPathname = FileUtil::getExternalFilename(script);
         File* file = new File(scriptPathname);
#if 0
         if (file.exists()) {
             JmriScriptEngineManager.getDefault().runScript(file);
         } else {
             JOptionPane.showMessageDialog(this, script, tr("ScriptFileNotFound"),
                     JOptionPane.ERROR_MESSAGE);
         }
#endif
     }
 }

 /*private*/ void TrainsScriptFrame::packFrame() {
     resize(QSize());
     pack();
 }

 /*public*/ void TrainsScriptFrame::dispose() {
     OperationsFrame::dispose();
 }
/*public*/ QString TrainsScriptFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.tools.TrainsScriptFrame";
}

}
