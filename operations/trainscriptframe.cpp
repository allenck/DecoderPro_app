#include "trainscriptframe.h"
#include "file.h"
#include "fileutil.h"
#include "jfilechooser.h"
#include "train.h"
#include <QBoxLayout>
#include <QScrollArea>
#include "gridbaglayout.h"
#include "jbutton.h"
#include <QLabel>
#include "trainmanager.h"
#include "trainmanagerxml.h"
#include "control.h"
#include "operationsxml.h"
#include "setup.h"
#include "logger.h"
#include "traineditframe.h"
#include <QSignalMapper>
#include <QMessageBox>
#include "jmriscriptenginemanager.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Frame for user edit of a train's script options. Allows the user to execute
  * scripts when a train is built, moved or terminated.
  *
  * @author Bob Jacobsen Copyright (C) 2004
  * @author Dan Boudreau Copyright (C) 2010, 2011, 2013
  * @version $Revision: 29897 $
  */
 ///*public*/ class TrainScriptFrame extends OperationsFrame {



 /*public*/ TrainScriptFrame::TrainScriptFrame(QWidget* parent) : OperationsFrame(parent)
{
   //super();
 log = new Logger("TrainScriptFrame");
 fc = XmlFile::userFileChooser(tr("Python Script Files"), "py"); // NOI18N

 _train = NULL;

 // script panels
 pBuildScript = new JPanel();
 pAfterBuildScript = new JPanel();
 pMoveScript = new JPanel();
 pTerminationScript = new JPanel();

// labels
 trainName = new QLabel();
 trainDescription = new QLabel();

// major buttons
 addBuildScriptButton = new JButton(tr("Add Script"));
 addAfterBuildScriptButton = new JButton(tr("Add Script"));
 addMoveScriptButton = new JButton(tr("Add Script"));
 addTerminationScriptButton = new JButton(tr("Add Script"));

 runBuildScriptButton = new JButton(tr("Run Scripts"));
 runAfterBuildScriptButton = new JButton(tr("Run Scripts"));
 runMoveScriptButton = new JButton(tr("Run Scripts"));
 runTerminationScriptButton = new JButton(tr("Run Scripts"));

 saveTrainButton = new JButton(tr("Save Train")); }

 /*public*/ void TrainScriptFrame::initComponents(TrainEditFrame* parent)
{
  // Set up script options in a Scroll Pane..
  JPanel* buildScriptFrame = new JPanel;
  buildScriptFrame->setLayout(new QVBoxLayout);
  buildScriptPane = new QScrollArea(/*pBuildScript*/);
  buildScriptPane->setWidgetResizable(true);
  buildScriptFrame->layout()->addWidget(buildScriptPane);
  //buildScriptPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
  buildScriptFrame->setBorder(BorderFactory::createTitledBorder(tr("Run the following scripts before building this train")));

  JPanel* afterBuildScriptFrame = new JPanel;
  afterBuildScriptFrame->setLayout(new QVBoxLayout);
  afterBuildScriptPane = new QScrollArea(/*pAfterBuildScript*/);
  afterBuildScriptPane->setWidgetResizable(true);
  afterBuildScriptFrame->layout()->addWidget(afterBuildScriptPane);
 // afterBuildScriptPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//  afterBuildScriptPane->setBorder(BorderFactory.createTitledBorder(Bundle
//          .getMessage("ScriptsAfterBuild")));
  afterBuildScriptFrame->setBorder(BorderFactory::createTitledBorder(tr("Run the following scripts after building this train")));

  JPanel* moveScriptFrame = new JPanel;
  moveScriptFrame->setLayout(new QVBoxLayout);
  moveScriptPane = new QScrollArea(/*pMoveScript*/);
  moveScriptPane->setWidgetResizable(true);
  moveScriptFrame->layout()->addWidget(moveScriptPane);
//  moveScriptPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//  moveScriptPane->setBorder(BorderFactory.createTitledBorder(tr("ScriptsWhenMoved")));
  moveScriptFrame->setBorder(BorderFactory::createTitledBorder(tr("Run the following scripts after this train is moved")));

  JPanel* terminationScriptFrame = new JPanel;
  terminationScriptFrame->setLayout(new QVBoxLayout);
  terminationScriptPane = new QScrollArea(/*pTerminationScript*/);
  terminationScriptPane->setWidgetResizable(true);
  terminationScriptFrame->layout()->addWidget(terminationScriptPane);
//  terminationScriptPane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
//  terminationScriptPane->setBorder(BorderFactory.createTitledBorder(Bundle
//          .getMessage("ScriptsWhenTerminated")));
  terminationScriptFrame->setBorder(BorderFactory::createTitledBorder(tr("Run the following scripts after this train terminates")));

  // remember who called us
  //parent->setChildFrame(this);
  _train = parent->_train;

  // load managers
  manager = ((TrainManager*)InstanceManager::getDefault("Operations::TrainManager"));
  managerXml = ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"));

  //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Layout the panel by rows
  QWidget* p1 = new QWidget();
  p1->setLayout(new QHBoxLayout);//(p1, BoxLayout.X_AXIS));

  // row 1a
  JPanel* pName = new JPanel();
  pName->setLayout(new GridBagLayout());
  pName->setBorder(BorderFactory::createTitledBorder(tr("Name")));
  addItem(pName, trainName, 0, 0);

  // row 1b
  JPanel* pDesc = new JPanel();
  pDesc->setLayout(new GridBagLayout());
  pDesc->setBorder(BorderFactory::createTitledBorder(tr("Description")));
  addItem(pDesc, trainDescription, 0, 0);

  p1->layout()->addWidget(pName);
  p1->layout()->addWidget(pDesc);

  // row 2
  updateBuildScriptPanel();

  // row 3
  updateAfterBuildScriptPanel();

  // row 4
  updateMoveScriptPanel();

  // row 6
  updateTerminationScriptPanel();

  // row 8 buttons
  JPanel* pB = new JPanel();
  pB->setLayout(new GridBagLayout());
  addItem(pB, saveTrainButton, 3, 0);

  thisLayout->addWidget(p1);
  buildScriptPane->setWidget(pBuildScript);
  thisLayout->addWidget(buildScriptFrame);
  afterBuildScriptPane->setWidget(pAfterBuildScript);
  thisLayout->addWidget(afterBuildScriptFrame);
  moveScriptPane->setWidget(pMoveScript);
  thisLayout->addWidget(moveScriptFrame);
  terminationScriptPane->setWidget(pTerminationScript);
  thisLayout->addWidget(terminationScriptFrame);
  thisLayout->addWidget(pB);

  // setup buttons
  addButtonAction(addBuildScriptButton);
  addButtonAction(addAfterBuildScriptButton);
  addButtonAction(addMoveScriptButton);
  addButtonAction(addTerminationScriptButton);
  addButtonAction(runBuildScriptButton);
  addButtonAction(runAfterBuildScriptButton);
  addButtonAction(runMoveScriptButton);
  addButtonAction(runTerminationScriptButton);
  addButtonAction(saveTrainButton);

  if (_train != NULL)
  {
   trainName->setText(_train->getName());
   trainDescription->setText(_train->getDescription());
   enableButtons(true);
  }
  else
  {
   enableButtons(false);
  }
  addHelpMenu("package.jmri.jmrit.operations.Operations_TrainScripts", true); // NOI18N
  initMinimumSize();
 }

 /*private*/ void TrainScriptFrame::updateBuildScriptPanel()
 {
  QSignalMapper* mapper = new QSignalMapper;
  connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(buttonActionRemoveBuildScript(QWidget*)));
     //pBuildScript.removeAll();
  QLayoutItem* item;
  if(pBuildScript->layout()!= NULL)
  {
   while ( ( item = pBuildScript->layout()->takeAt( 0 ) ) != NULL )
   {
    delete item->widget();
    delete item;
   }
   pBuildScript->setLayout(new GridBagLayout());
  }
  addItem(pBuildScript, addBuildScriptButton, 0, 0);

  // load any existing train build scripts
  if (_train != NULL)
  {
   QStringList scripts = _train->getBuildScripts();
   if (scripts.size() > 0) {
       addItem(pBuildScript, runBuildScriptButton, 1, 0);
   }
   for (int i = 0; i < scripts.size(); i++)
   {
    JButton* removeBuildScripts = new JButton(tr("Remove Script"));
    removeBuildScripts->setObjectName(scripts.at(i));
//    removeBuildScripts.addActionListener(new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            buttonActionRemoveBuildScript(e);
//        }
//    });
    mapper->setMapping(removeBuildScripts, removeBuildScripts);
    connect(removeBuildScripts, SIGNAL(clicked()), mapper, SLOT(map()));
    //addButtonAction(removeBuildScripts);
    QLabel* pathname = new QLabel(scripts.at(i));
    addItem(pBuildScript, removeBuildScripts, 0, i + 1);
    addItem(pBuildScript, pathname, 1, i + 1);
   }
  }
 }

 /*private*/ void TrainScriptFrame::updateAfterBuildScriptPanel()
 {
  QSignalMapper* mapper = new QSignalMapper;
  connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(buttonActionRemoveAfterBuildScript(QWidget*)(QWidget*)));
     //pAfterBuildScript.removeAll();
  QLayoutItem* item;
  if(pAfterBuildScript->layout()!= NULL)
  {
   while ( ( item = pAfterBuildScript->layout()->takeAt( 0 ) ) != NULL )
   {
    delete item->widget();
    delete item;
   }
   pAfterBuildScript->setLayout(new GridBagLayout());
  }
  pAfterBuildScript->setLayout(new GridBagLayout());
  addItem(pAfterBuildScript, addAfterBuildScriptButton, 0, 0);

  // load any existing train build scripts
  if (_train != NULL) {
      QStringList scripts = _train->getAfterBuildScripts();
      if (scripts.size() > 0) {
          addItem(pAfterBuildScript, runAfterBuildScriptButton, 1, 0);
      }
      for (int i = 0; i < scripts.size(); i++) {
          JButton* removeAfterBuildScripts = new JButton(tr("RemoveScript"));
          removeAfterBuildScripts->setObjectName(scripts.at(i));
//             removeAfterBuildScripts.addActionListener(new java.awt.event.ActionListener() {
//                 /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                     buttonActionRemoveAfterBuildScript(e);
//                 }
//             });
          mapper->setMapping(removeAfterBuildScripts, removeAfterBuildScripts);
          connect(removeAfterBuildScripts, SIGNAL(clicked(bool)), mapper, SLOT(map()));
          //addButtonAction(removeAfterBuildScripts);
          QLabel* pathname = new QLabel(scripts.at(i));
          addItem(pAfterBuildScript, removeAfterBuildScripts, 0, i + 1);
          addItem(pAfterBuildScript, pathname, 1, i + 1);
      }
  }
 }

 /*private*/ void TrainScriptFrame::updateMoveScriptPanel()
 {
  QSignalMapper* mapper = new QSignalMapper;
  connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(buttonActionRemoveMoveScript(QWidget*)));
     //pMoveScript.removeAll();
 QLayoutItem* item;
 if(pMoveScript->layout()!= NULL)
 {
  while ( ( item = pMoveScript->layout()->takeAt( 0 ) ) != NULL )
  {
   delete item->widget();
   delete item;
  }
  pMoveScript->setLayout(new GridBagLayout());
 }
     pMoveScript->setLayout(new GridBagLayout());
     addItem(pMoveScript, addMoveScriptButton, 0, 0);

     // load any existing train move scripts
     if (_train != NULL) {
         QStringList scripts = _train->getMoveScripts();
         if (scripts.size() > 0) {
             addItem(pMoveScript, runMoveScriptButton, 1, 0);
         }
         for (int i = 0; i < scripts.size(); i++) {
             JButton* removeMoveScripts = new JButton(tr("Remove Script"));
             removeMoveScripts->setObjectName(scripts.at(i));
//             removeMoveScripts.addActionListener(new java.awt.event.ActionListener() {
//                 /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                     buttonActionRemoveMoveScript(e);
//                 }
//             });
             mapper->setMapping(removeMoveScripts, removeMoveScripts);
             connect(removeMoveScripts, SIGNAL(clicked(bool)), this, SLOT(map()));
             //addButtonAction(removeMoveScripts);
             QLabel* pathname = new QLabel(scripts.at(i));
             addItem(pMoveScript, removeMoveScripts, 0, i + 1);
             addItem(pMoveScript, pathname, 1, i + 1);
         }
     }
 }

 /*private*/ void TrainScriptFrame::updateTerminationScriptPanel()
 {
  QSignalMapper* mapper = new QSignalMapper;
  connect(mapper, SIGNAL(mapped(QWidget*)), this, SLOT(buttonActionRemoveTerminationScript(QWidget*)));
     //pTerminationScript.removeAll();
  QLayoutItem* item;
  if(pTerminationScript->layout()!= NULL)
  {
   while ( ( item = pTerminationScript->layout()->takeAt( 0 ) ) != NULL )
   {
    delete item->widget();
    delete item;
   }
   pTerminationScript->setLayout(new GridBagLayout());
  }
  pTerminationScript->setLayout(new GridBagLayout());
  addItem(pTerminationScript, addTerminationScriptButton, 0, 0);

  // load any existing train termination scripts
  if (_train != NULL)
  {
   QStringList scripts = _train->getTerminationScripts();
   if (scripts.size() > 0) {
       addItem(pTerminationScript, runTerminationScriptButton, 1, 0);
   }
   for (int i = 0; i < scripts.size(); i++)
   {
    JButton* removeTerminationScripts = new JButton(tr("RemoveScript"));
    removeTerminationScripts->setObjectName(scripts.at(i));
//             removeTerminationScripts.addActionListener(new java.awt.event.ActionListener() {
//                 /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                     buttonActionRemoveTerminationScript(e);
//                 }
//             });
    mapper->setMapping(removeTerminationScripts, removeTerminationScripts);
    connect(removeTerminationScripts, SIGNAL(clicked(bool)), mapper,SLOT(map()));
    QLabel* pathname = new QLabel(scripts.at(i));
    addItem(pTerminationScript, removeTerminationScripts, 0, i + 1);
    addItem(pTerminationScript, pathname, 1, i + 1);
   }
  }
 }

 // Save train, add scripts buttons
 /*public*/ void TrainScriptFrame::buttonActionPerformed(QWidget* ae)
{
 JButton* source = (JButton*)ae;
  if (_train != NULL) {
      if (source == addBuildScriptButton) {
          log->debug("train add build script button activated");
          File* f = selectFile();
          if (f != NULL) {
              _train->addBuildScript(FileUtil::getPortableFilename(f));
              updateBuildScriptPanel();
              adjustSize();
          }
      }
      if (source == addAfterBuildScriptButton) {
          log->debug("train add after build script button activated");
          File* f = selectFile();
          if (f != NULL) {
              _train->addAfterBuildScript(FileUtil::getPortableFilename(f));
              updateAfterBuildScriptPanel();
              adjustSize();
          }
      }
      if (source == addMoveScriptButton) {
          log->debug("train add move script button activated");
          File* f = selectFile();
          if (f != NULL) {
              _train->addMoveScript(FileUtil::getPortableFilename(f));
              updateMoveScriptPanel();
              pack();
          }
      }
      if (source == addTerminationScriptButton) {
          log->debug("train add termination script button activated");
          File* f = selectFile();
          if (f != NULL) {
              _train->addTerminationScript(FileUtil::getPortableFilename(f));
              updateTerminationScriptPanel();
              adjustSize();
          }
      }
      if (source == runBuildScriptButton) {
          runScripts(_train->getBuildScripts());
      }
      if (source == runAfterBuildScriptButton) {
          runScripts(_train->getAfterBuildScripts());
      }
      if (source == runMoveScriptButton) {
          runScripts(_train->getMoveScripts());
      }
      if (source == runTerminationScriptButton) {
          runScripts(_train->getTerminationScripts());
      }
      if (source == saveTrainButton) {
          log->debug("train save button activated");
          OperationsXml::save();
          if (Setup::isCloseWindowOnSaveEnabled()) {
              dispose();
          }
      }
  }
 }

 /*public*/ void TrainScriptFrame::buttonActionRemoveBuildScript(QWidget* ae) {
     if (_train != NULL) {
         JButton* rbutton = (JButton*) ae;
         log->debug("remove build script button activated " + rbutton->objectName());
         _train->deleteBuildScript(rbutton->objectName());
         updateBuildScriptPanel();
         pack();
     }
 }

 /*public*/ void TrainScriptFrame::buttonActionRemoveAfterBuildScript(QWidget* ae) {
     if (_train != NULL) {
         JButton* rbutton = (JButton*) ae;
         log->debug("remove after build script button activated " + rbutton->objectName());
         _train->deleteAfterBuildScript(rbutton->objectName());
         updateAfterBuildScriptPanel();
         pack();
     }
 }

 /*public*/ void TrainScriptFrame::buttonActionRemoveMoveScript(QWidget* ae) {
     if (_train != NULL) {
         JButton* rbutton = (JButton*) ae;
         log->debug("remove move script button activated " + rbutton->objectName());
         _train->deleteMoveScript(rbutton->objectName());
         updateMoveScriptPanel();
         pack();
     }
 }

 /*public*/ void TrainScriptFrame::buttonActionRemoveTerminationScript(QWidget* ae) {
     if (_train != NULL) {
         JButton* rbutton = (JButton*) ae;
         log->debug("remove termination script button activated " + rbutton->objectName());
         _train->deleteTerminationScript(rbutton->objectName());
         updateTerminationScriptPanel();
         adjustSize();
     }
 }

 /*private*/ void TrainScriptFrame::runScripts(QStringList scripts) {
     foreach (QString script, scripts) {
         QString scriptPathname = FileUtil::getExternalFilename(script);
         File* file = new File(scriptPathname);
         if (file->exists())
         {
             JmriScriptEngineManager::getDefault()->runScript(file);
         } else {
//             JOptionPane.showMessageDialog(this, script, tr("ScriptFileNotFound"),
//                     JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Error"), tr("Script file not found"));
         }
     }
 }


 /*private*/ File* TrainScriptFrame::selectFile() {
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

 /*private*/ void TrainScriptFrame::enableButtons(bool enabled) {
     addBuildScriptButton->setEnabled(enabled);
     addAfterBuildScriptButton->setEnabled(enabled);
     addMoveScriptButton->setEnabled(enabled);
     addTerminationScriptButton->setEnabled(enabled);
     saveTrainButton->setEnabled(enabled);
 }
/*public*/ QString TrainScriptFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.tools.TrainScriptFrame";
}

}
