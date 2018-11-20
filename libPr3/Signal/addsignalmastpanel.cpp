#include "addsignalmastpanel.h"
#include "instancemanager.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "defaultsignalsystemmanager.h"
#include "defaultsignalsystem.h"
#include "xmlfile.h"
#include "fileutil.h"
#include "../Tables/jmribeancombobox.h"
#include "jtextfield.h"
#include "slotmanager.h"
#include "signalheadsignalmast.h"
#include <QMessageBox>
#include "turnoutmanager.h"
#include "defaultsignalappearancemap.h"
#include "signalmast.h"
#include "turnoutsignalmast.h"
#include "virtualsignalmast.h"
//#include "dccsignalmast.h"
#include "../Tables/beanselectcreatepanel.h"
#include "defaultsignalmastmanager.h"
#include "stringutil.h"
#include "decimalformat.h"
#include "actionevent.h"
#include "jmriuserpreferencesmanager.h"
#include "signalmastaddpane.h"
#include <QGridLayout>
#include <QFormLayout>
#include "flowlayout.h"
#include "signalsystemmanager.h"
#include "connectionnamefromsystemname.h"
#include "dccsignalmast.h"
#include "lncpsignalmast.h"
#include "joptionpane.h"
#include "exceptions.h"
#include "runtimeexception.h"
#include <QFile>
#include <QUrl>
#include "loggerfactory.h"

//AddSignalMastPanel::AddSignalMastPanel(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * JPanel to create a new SignalMast
 *
 * @author	Bob Jacobsen    Copyright (C) 2009, 2010
 * @version     $Revision: 22539 $
 */

///*public*/ class AddSignalMastPanel extends JPanel {



/*public*/ AddSignalMastPanel::AddSignalMastPanel(QWidget *parent) :
    QWidget(parent)
{
 log->debug("AddSignalMastPanel()");
  init();
}

void AddSignalMastPanel::init()
{
 // head matter
 userName = new JTextField(20); // N11N
 sigSysBox = new QComboBox();  // the basic signal system
 mastBox = new QComboBox(); //new String[]{tr("MastEmpty")}); // the mast within the system NOI18N
 mastBox->addItem(tr("select a System first"));
 mastBoxPassive = false; // if true, mastBox doesn't process updates
 panes =QList<SignalMastAddPane*>();

 // center pane, which holds the specific display
 centerPanel = new QStackedWidget();
 centerPanel->setMaximumHeight(400);
 //cl = new QFormLayout();
 centerPanelLabel = new QLabel();

 // rest of structure
 signalHeadPanel = new QGroupBox();
 signalHeadPanel->setLayout(new QVBoxLayout());
 cancel = new QPushButton(tr("Cancel")); // NOI18N
 apply = new QPushButton(tr("Apply")); // NOI18N
 create = new QPushButton(tr("Create")); // NOI18N
 // connection to preferences
 prefs = static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"));
 systemSelectionCombo = QString("jmri.jmrit.beantable.signalmast.AddSignalMastPanel") + ".SignallingSystemSelected"; // NOI18N
 mastSelectionCombo = QString("jmri.jmrit.beantable.signalmast.AddSignalMastPanel")+ ".SignallingMastSelected"; // NOI18N
 driverSelectionCombo = QString("jmri.jmrit.beantable.signalmast.AddSignalMastPanel") + ".SignallingDriverSelected"; // NOI18N

 // signal system definition variables
 mastFiles = QList<File*>(); // signal system definition files
 mapNameToShowSize = QMap<QString, int>();
 mapTypeToName = QMap<QString, QString>();



 // get the list of possible signal types (as shown by panes)
 // SignalMastAddPane::SignalMastAddPaneProvider::getInstancesCollection().forEach(
 //     (provider)->
 foreach(SignalMastAddPane::SignalMastAddPaneProvider* provider, SignalMastAddPane::SignalMastAddPaneProvider::getInstancesCollection())
 {
  if (provider->isAvailable()) {
      panes.append(provider->getNewPane());
  }
 }
 //);

 { // scoping for temporary variables

  QVector<QString> tempMastNamesArray = QVector<QString>(panes.size());
  int i = 0;
  for (SignalMastAddPane* pane : panes) {
      tempMastNamesArray.replace(i++, pane->getPaneName());
  }
  signalMastDriver = new QComboBox(/*tempMastNamesArray*/);
  signalMastDriver->addItems(tempMastNamesArray.toList());
 }

 //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
 QVBoxLayout* thisLayout = new QVBoxLayout(this);

 QWidget* p;
 p = new QWidget(centerPanelLabel);
 QGridLayout* pLayout = new QGridLayout(p/*5, 2*/);

 QLabel* l = new QLabel(tr("User Name")+ ": ");  // NOI18N
 pLayout->addWidget(l,0,0);
 pLayout->addWidget(userName, 0,1);

 l = new QLabel(tr("Signal System") + ": "); // NOI18N
 pLayout->addWidget(l,1,0);
 pLayout->addWidget(sigSysBox,1,1);

 l = new QLabel(tr("Mast Type") + ": "); // NOI18N
 pLayout->addWidget(l,2,0);
 pLayout->addWidget(mastBox, 2,1);

 l = new QLabel(tr("Driver Type") + ": "); // NOI18N
 pLayout->addWidget(l,3,0);
 pLayout->addWidget(signalMastDriver,3,1);

 thisLayout->addWidget(p);

 // central region
 //centerPanel->setLayout(cl);
 for (SignalMastAddPane* pane : panes) {
     //cl->addRow(pane->getPaneName(), pane); // assumes names are systemwide-unique
  centerPanel->addWidget(pane);
 }
 thisLayout->addWidget(centerPanelLabel);
 thisLayout->addWidget(centerPanel);
// signalMastDriver.addItemListener(new ItemListener(){
//     public void itemStateChanged(ItemEvent evt) {
//             log.trace("about to call selection() from signalMastDriver itemStateChanged");
//             selection((String)evt.getItem());
//         }
// });
 connect(signalMastDriver, SIGNAL(currentIndexChanged(int)), this, SLOT(onSignalMastDriverSelected()));

 // button region
 QWidget* buttonHolder = new QWidget();
 QHBoxLayout* buttonHolderLayout;
 buttonHolder->setLayout(buttonHolderLayout =new QHBoxLayout(/*FlowLayout::TRAILING*/));
 cancel->setVisible(true);
 buttonHolderLayout->addWidget(cancel);
// cancel.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent e) {
//         cancelPressed();
//     } // Cancel button
// });
 connect(cancel, SIGNAL(clicked(bool)), this, SLOT(cancelPressed()));
 cancel->setVisible(true);
 buttonHolderLayout->addWidget(create);
// create.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent e) {
//         okPressed();
//     } // Create button on add new mast pane
// });
 connect(create, SIGNAL(clicked(bool)),this, SLOT(okPressed()));
 create->setVisible(true);
 buttonHolderLayout->addWidget(apply);
// apply.addActionListener(new ActionListener() {
//     @Override
//     public void actionPerformed(ActionEvent e) {
//         okPressed();
//     } // Apply button on Edit existing mast pane
// });
 connect(apply, SIGNAL(clicked(bool)), this, SLOT(okPressed(ActionEvent*)));
 apply->setVisible(false);
 thisLayout->addWidget(buttonHolder,0,Qt::AlignRight); // add bottom row of buttons (to me)

 // default to 1st pane
 currentPane = panes.at(0);
 centerPanelLabel->setText(currentPane->getPaneName());

 // load the list of signal systems
 SignalSystemManager* man = static_cast<SignalSystemManager*>(InstanceManager::getDefault("SignalSystemManager"));
 QSet<NamedBean*> systems = man->getNamedBeanSet();
 for (NamedBean* system : systems) {
     sigSysBox->addItem(((SignalSystem*)system)->getUserName());
 }
 if (prefs->getComboBoxLastSelection(systemSelectionCombo) != nullptr) {
     sigSysBox->setCurrentText(prefs->getComboBoxLastSelection(systemSelectionCombo));
 }
 log->trace(tr("  preferences set %1 into sigSysBox").arg(sigSysBox->currentIndex()));

 loadMastDefinitions();

 // select the 1st one
 selection(panes.at(0)->getPaneName());  // there has to be at least one, so we can do the update

 // set a remembered signalmast type, if present
 if (prefs->getComboBoxLastSelection(driverSelectionCombo) != nullptr) {
     signalMastDriver->setCurrentText(prefs->getComboBoxLastSelection(driverSelectionCombo));
 }

// sigSysBox.addItemListener(new ItemListener() {
//     @Override
//     public void itemStateChanged(ItemEvent e) {
//         loadMastDefinitions();
//         updateSelectedDriver();
//     }
// });
 connect(sigSysBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sigSysBox_currentIndexChanged(int)));
}

/**
 * Select a particular signal implementation to display
 */
void AddSignalMastPanel::selection(QString view) {
    log->trace(tr(" selection(%1) start").arg(view));
    // find the new pane
    for (SignalMastAddPane* pane : panes) {
        if (pane->getPaneName() == (view)) {
            currentPane = pane;
            centerPanel->setCurrentWidget(currentPane);
            centerPanelLabel->setText(currentPane->getPaneName());
        }
    }

    // update that selected pane before display
    updateSelectedDriver();

    // and show
 //   cl->show(centerPanel, view);
    log->trace(tr(" selection(%1) end").arg(view));
}

/*public*/ AddSignalMastPanel::AddSignalMastPanel(SignalMast* mast, QWidget *parent) :
    QWidget(parent)
{
 init();
 log->debug(tr("AddSignalMastPanel(%1) start").arg(mast->getDisplayName()));

 // switch buttons
 apply->setVisible(true);
 create->setVisible(false);

 this->mast = mast;

 // can't change some things from original settings
 sigSysBox->setEnabled(false);
 mastBox->setEnabled(false);
 signalMastDriver->setEnabled(false);
 userName->setEnabled(false);

 //load prior content
 userName->setText(mast->getUserName());
 log->trace(tr("Prior content system name: %1  mast type: %2").arg( mast->getSignalSystem()->getUserName()).arg(mast->getMastType()));
 if (mast->getMastType() == nullptr) log->error("MastType was null, and never should be");
 sigSysBox->setCurrentText(mast->getSignalSystem()->getUserName());  // signal system

 // select and show
 for (SignalMastAddPane* pane : panes)
 {
  if (pane->canHandleMast(mast))
  {
   currentPane = pane;
   // set the driver combobox
   signalMastDriver->setCurrentText(pane->getPaneName());
   log->trace("About to call selection() from SignalMastAddPane loop in AddSignalMastPanel(SignalMast mast)");
   selection(pane->getPaneName());

   // Ensure that the mast type is set
   mastBoxPassive = false;
   if (mapTypeToName.value(mast->getMastType()) == nullptr ) {
       log->error(tr("About to set mast to null, which shouldn't happen. mast.getMastType() is %1").arg(mast->getMastType()),
                Exception("Traceback Exception")); // NOI18N
   }
   log->trace(tr("set mastBox to \"%1\" from \"%2\"").arg( mapTypeToName.value(mast->getMastType())).arg(mast->getMastType())); // NOI18N
   mastBox->setCurrentText(mapTypeToName.value(mast->getMastType()));

   pane->setMast(mast);
   break;
  }
 }

 // set mast type, suppress notification
 mastBoxPassive = true;
 QString newMastType = mapTypeToName.value(mast->getMastType());
 log->debug(tr("Setting type to %1").arg(newMastType)); // NOI18N
 mastBox->setCurrentText(newMastType);
 mastBoxPassive = false;

 log->debug(tr("AddSignalMastPanel(%1) end").arg(mast->getDisplayName()));
}

void AddSignalMastPanel::loadMastDefinitions()
{
 log->trace(" loadMastDefinitions() start");
//    // need to remove itemListener before addItem() or item event will occur
//    if(mastBox.getItemListeners().length >0) {
//        mastBox.removeItemListener(mastBox.getItemListeners()[0]);
//    }
 disconnect(mastBox, SIGNAL(currentIndexChanged(int)));
 mastBox->clear();
 try
 {
  mastFiles = QList<File*>();
  SignalSystemManager* man = static_cast<SignalSystemManager*>(InstanceManager::getDefault("SignalSystemManager"));

  // get the signals system name from the user name in combo box
  QString u = sigSysBox->currentText();
  sigsysname = man->getByUserName(u)->getSystemName();
  log->trace(tr("     loadMastDefinitions with sigsysname %1").arg(sigsysname)); // NOI18N
  mapNameToShowSize = QMap<QString, int>();
  mapTypeToName = QMap<QString, QString>();

  // do file IO to get all the appearances
  // gather all the appearance files
  // Look for the default system defined ones first
  QList<File*> programDirArray = QList<File*>();
  QUrl pathProgramDir = FileUtil::findURL("xml/signals/" + sigsysname, FileUtil::Location::INSTALLED); // NOI18N
  if (!pathProgramDir.isEmpty()) programDirArray =  File(pathProgramDir.toString(QUrl::RemoveScheme)).listFiles();
  if (programDirArray.isEmpty()) programDirArray = QList<File*>();

  QList<File*> profileDirArray = QList<File*>();
  QUrl pathProfileDir = FileUtil::findURL("resources/signals/" + sigsysname, FileUtil::Location::USER); // NOI18N
  if (!pathProfileDir.isEmpty()) profileDirArray =  File(pathProfileDir.toString(QUrl::RemoveScheme)).listFiles();
  if (profileDirArray.isEmpty()) profileDirArray = QList<File*>();

  // create a composite list of files
  //  QList<File*> apps = Arrays.copyOf(programDirArray, programDirArray.length + profileDirArray.length);
  QList<File*> apps = QList<File*>(programDirArray);
//  System.arraycopy(profileDirArray, 0, apps, programDirArray.length, profileDirArray.length);
  foreach (File* f, profileDirArray)
  {
   apps.append(f);
  }
  if(!apps.isEmpty())
  {
   for (File* app : apps)
   {
    if (app->fileName().startsWith("appearance")
                            && app->fileName().endsWith(".xml"))
    {
      log->debug("   found file: "+app->fileName());
      // load it and get name
      mastFiles.append(app);

      XmlFile* xf = new XmlFile();
      QDomElement root = xf->rootFromFile(new QFile(app->absoluteFilePath()));
      QString name = root.firstChildElement("name").text();
      mastBox->addItem(name);
      log->trace(tr("mapTypeToName adding key \"%1\" value \"%2\"").arg( app->getName().mid(11, app->getName().indexOf(".xml"))).arg(name)); // NOI18N
      mapTypeToName.insert(app->getName().mid(11, app->getName().indexOf(".xml")), name); // NOI18N
      mapNameToShowSize.insert(name, root.firstChildElement("appearances") // NOI18N
                                      .firstChildElement("appearance") // NOI18N
                                      .elementsByTagName("show") // NOI18N
                                      .size());
    }
   }
  }
  else {
   log->error("Unexpected null list of signal definition files"); // NOI18N
  }
 } catch (JDOMException e)
 {
  mastBox->addItem("Failed to create definition, did you select a system?");
  log->warn("in loadMastDefinitions"+ e.getMessage());
 } catch (IOException e) {
  mastBox->addItem("Failed to read definition, did you select a system?");
  log->warn("in loadMastDefinitions" + e.getMessage());
 }

 try
 {
  QStringList paths = QStringList() << "xml"<< "resources";
  QUrl path = FileUtil::findURL(QString("signals/") + sigsysname, FileUtil::Location::USER, paths ); // NOI18N
  if (!path.isEmpty())
  {
   QList<File*> apps =  File(path.toString(QUrl::RemoveScheme)).listFiles();
    if(!apps.isEmpty())
    {
     for (File* app : apps)
     {
       if (app->fileName().startsWith("appearance")
                            && app->fileName().endsWith(".xml"))
       {
        log->debug("   found file: "+app->fileName());
        // load it and get name
        //If the mast file name already exists no point in re-adding it
        if(!mastFiles.contains(app))
        {
         mastFiles.append(app);

         XmlFile* xf = new XmlFile();
         QDomElement root = xf->rootFromFile(new QFile(app->getPath()));
         QString name = root.firstChildElement("name").text();
         //if the mast name already exist no point in readding it.
         if(!map.contains(name))
         {
          mastBox->addItem(name);
          map.insert(name, (root.firstChildElement("appearances")
                                .firstChildElement("appearance")
                                .elementsByTagName("show")
                                .size()));
       }
      }
     }
    }
   }
   else
    {
     log->warn("No mast definition files found");
    }
  }
 } catch (JDOMException e) {
        log->warn("in loadMastDefinitions"+ e.getMessage());
 } catch (IOException e) {
        //Can be considered normal
        log->warn("in loadMastDefinitions"+ e.getMessage());
 }
//    mastBox->addItemListener(new ItemListener(){
//        /*public*/ void itemStateChanged(ItemEvent e) {
//            updateSelectedDriver();
//        }
//    });
 connect(mastBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSelectedDriver()));
    updateSelectedDriver();

    if(prefs->getComboBoxLastSelection(mastSelectionCombo+":"+((QString) sigSysBox->currentText()))!=NULL)
        mastBox->setCurrentIndex(mastBox->findText(prefs->getComboBoxLastSelection(mastSelectionCombo+":"+((QString) sigSysBox->currentText()))));
 log->trace(" loadMastDefinitions() end");
}

/**
 * Update contents of Add/Edit mast panel appropriate for chosen Driver
 * type.
 * <p>
 * Invoked when selecting a Signal Mast Driver in {@link #loadMastDefinitions}
 */
/*protected*/ void AddSignalMastPanel::updateSelectedDriver() {
    log->trace(" updateSelectedDriver() start");

    if (mastBox->currentIndex() < 0) return; // no mast selected yet
    QString mastFile = mastFiles.value(mastBox->currentIndex())->getName();
    QString mastType = mastFile.mid(11, mastFile.indexOf(".xml"));
    mastType = mastType.mid(0, mastType.indexOf(".xml"));
    DefaultSignalAppearanceMap* sigMap = DefaultSignalAppearanceMap::getMap(sigsysname, mastType);
    SignalSystem* sigsys = static_cast<SignalSystemManager*>( InstanceManager::getDefault("SignalSystemManager"))->getSystem(sigsysname);
    currentPane->setAspectNames(sigMap, sigsys);
    // clear mast info
    currentPane->setMast(nullptr);

    currentPane->update();
    if (window() != nullptr && qobject_cast<JFrame*>(window())) {
        ((JFrame*)window())->pack();
    } else {
        log->debug(tr("Can't call pack() on %1").arg(window()->metaObject()->className()));
    }
    log->trace(" updateSelectedDriver() end");
}
/**
 * Check of user name done when creating new SignalMast.
 * In case of error, it looks a message and (if not headless) shows a dialog.
 * @return true if OK to proceed
 */
bool AddSignalMastPanel::checkUserName(QString nam) {
    if (!(nam.isEmpty())) {
        // user name provided, check if that name already exists
        NamedBean* nB =  static_cast<SignalSystemManager*>( InstanceManager::getDefault("SignalSystemManager"))->getByUserName(nam);
        if (nB != nullptr) {
            issueWarningUserName(nam);
            return false;
        }
        // Check to ensure that the username doesn't exist as a systemname.
        nB = static_cast<SignalSystemManager*>( InstanceManager::getDefault("SignalSystemManager"))->getBySystemName(nam);
        if (nB != nullptr) {
            issueWarningUserNameAsSystem(nam);
            return false;
        }
    }
    return true;
}

void AddSignalMastPanel::issueWarningUserName(QString nam) {
    log->error(tr("User Name \"%1\" is already in use").arg(nam)); // NOI18N
    //if (!GraphicsEnvironment.isHeadless()) {
        QString msg = tr("User Name \"%1\" is already in use").arg(nam); // NOI18N
        JOptionPane::showMessageDialog(nullptr, msg,
                tr("Warning"), // NOI18N
                JOptionPane::ERROR_MESSAGE);
    //}
}

void AddSignalMastPanel::issueWarningUserNameAsSystem(QString nam) {
 QString msg = tr("User Name \"%1\" already exists as a System name").arg(nam);
    log->error(msg);
    //if (!GraphicsEnvironment.isHeadless()) {
        JOptionPane::showMessageDialog(nullptr, msg,
                tr("Warning"),
                JOptionPane::ERROR_MESSAGE);
    //}
}
void AddSignalMastPanel::okPressed()
{
 log->trace(" okPressed() start");
 bool success = false;

 // get and validate entered global information
 if ( (mastBox->currentIndex() < 0) || ( mastFiles.value(mastBox->currentIndex()) == nullptr) ) {
     issueDialogFailMessage( RuntimeException("There's something wrong with the mast type selection"));
     return;
 }
 QString mastname = mastFiles.value(mastBox->currentIndex())->getName();
 QString user = (userName->text() != "" ? NamedBean::normalizeUserName(userName->text()) : ""); // NOI18N
 //if (!GraphicsEnvironment.isHeadless()) {
     if ( user.isEmpty()) {
         int i = issueNoUserNameGiven();
         if (i != 0) {
             return;
         }
     }
 //}

 // ask top-most pane to make a signal
 try {
     success = currentPane->createMast(sigsysname,mastname,user);
 } catch (RuntimeException ex) {
     issueDialogFailMessage(ex);
     return; // without clearing panel, so user can try again
 }
 if (!success) {
     // should have already provided user feedback via dialog
     return;
 }

 clearPanel();
 log->trace(" okPressed() end");
}

int AddSignalMastPanel::issueNoUserNameGiven() {
        return JOptionPane::showConfirmDialog(nullptr, "No Username has been defined, this may cause issues when editing the mast later.\nAre you sure that you want to continue?",  // NOI18N
                "No UserName Given",  // NOI18N
                JOptionPane::YES_NO_OPTION);
    }

void AddSignalMastPanel::issueDialogFailMessage(RuntimeException ex) {
// This is intrinsically swing, so pop a dialog
log->error("Failed during createMast", ex); // NOI18N
JOptionPane::showMessageDialog(this,
    tr("Failed during createMast %1").arg(ex.getMessage()), // NOI18N
    tr("Create Failed"),  // title of box // NOI18N
    JOptionPane::ERROR_MESSAGE);
}

/**
* Called when an already-initialized AddSignalMastPanel is being
* displayed again, right before it's set visible.
*/
/*public*/ void AddSignalMastPanel::refresh() {
 log->trace(" refresh() start");
 // add new cards (new panes)
 for(int i = centerPanel->count(); i >= 0; i --)
 {
  centerPanel->removeWidget(centerPanel->widget(i));
 }
 for (SignalMastAddPane* pane : panes) {
     //cl->addRow(pane->getPaneName(), pane); // assumes names are systemwide-unique
  centerPanel->addWidget(pane);
 }

 // select pane to match current combobox
 log->trace("about to call selection from refresh");
 selection(signalMastDriver->itemText(signalMastDriver->currentIndex()));
 log->trace(" refresh() end");
}

/**
 * Respond to the Cancel button.
 */
void AddSignalMastPanel::cancelPressed() {
    log->trace(" cancelPressed() start");
    clearPanel();
    log->trace(" cancelPressed() end");
}

/**
 * Close and dispose() panel.
 * <p>
 * Called at end of okPressed() and from Cancel
 */
void AddSignalMastPanel::clearPanel() {
    log->trace(" clearPanel() start");
    if (qobject_cast<JmriJFrame*>(window())) {
        static_cast<JmriJFrame*>( window())->dispose();
    } else {
        log->warn(tr("Unexpected top level ancestor: %1").arg(window()->windowTitle())); // NOI18N
    }
    userName->setText(""); // clear user name
    window()->setVisible(false);
    log->trace(" clearPanel() end");
}

//void AddSignalMastPanel::on_mastSelect_CurrentIndexChanged(int)
//{
//    QString sourceMast = mastSelect->currentText();
//    if(sourceMast!=NULL && sourceMast!=(""))
//     copyFromAnotherDCCMastAspect(sourceMast);
//}

/* @(#)SensorTableAction.java */
void AddSignalMastPanel::sigSysBox_currentIndexChanged(int) // SLOT[]
{
 loadMastDefinitions();
 updateSelectedDriver();
}

void AddSignalMastPanel::onSignalMastDriverSelected()
{
 log->trace("about to call selection() from signalMastDriver itemStateChanged");
 selection(signalMastDriver-> currentText());

}

/*private*/ /*final*/ /*static*/ Logger* AddSignalMastPanel::log = LoggerFactory::getLogger("AddSignalMastPanel");
