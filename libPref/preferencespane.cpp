#include "preferencespane.h"
#include <QTabWidget>
#include "jmrixconfigpane.h"
#include <QBoxLayout>
#include <QPushButton>
#include "programmerconfigpane.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "configxmlmanager.h"
//#include "performactionpanel.h"
//#include "createbuttonpanel.h"
#include "guilafconfigpane.h"


PreferencesPane::PreferencesPane(QWidget *parent) :
    QWidget(parent)
{
//    JInternalFrame frame = new JInternalFrame("Preferences",
//                                                true, //resizable
//                                                true, //closable
//                                                true, //maximizable
//                                                true);//iconifiable
//            frame.setLocation(200+50*count,200+50*count);
//            count++;

 // content
 log = new Logger("PreferencesPane");

 QTabWidget* p = new QTabWidget();
// JmrixConfigPane* pane = JmrixConfigPane::instance(1);
// p->addTab( JmrixConfigPane::instance(1), "Connection 1");
 p->addTab(guiPrefs = new GuiLafConfigPane(),"GUI");
 p->addTab(new ProgrammerConfigPane(),"Programmer");
 //p->addTab(new PerformActionPanel(), "Actions");
 //p->addTab( new CreateButtonPanel(),"Buttons");
//    p.add("Files", new apps.PerformFilePanel());
//    p.add("Scripts", new apps.PerformScriptPanel());
//    p.add("Roster", new jmri.jmrit.roster.RosterConfigPane());

 QWidget* p2 = new QWidget();
 QVBoxLayout* p2Layout;
 p2->setLayout(p2Layout = new QVBoxLayout); //(p2, BoxLayout.Y_AXIS));
 p2Layout->addWidget(p);
 QPushButton* save = new QPushButton("Save");
 p2Layout->addWidget(save);
//    save.addActionListener( new ActionListener() {
//            public void actionPerformed(ActionEvent e) {
//                preferencesSavePressed();
//            }
//        });

 //frame.add(p2);
 //setCentralWidget(p2);
 QVBoxLayout* thisLayout;
 this->setLayout(thisLayout);
 this->layout()->addWidget(p2);
 //frame.pack();
 //pack();

 // show
 //frame.setVisible(true);
 setVisible(true);
 //desktop.add(frame);

// try {
//    frame.setSelected(true);
// } catch (java.beans.PropertyVetoException e) {}

// frame.moveToFront();
}

void PreferencesPane::preferencesSavePressed() {
    saveContents();
}

void PreferencesPane::saveContents()
{
 // remove old prefs that are registered in ConfigManager
 ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->removePrefItems();
 // put the new GUI items on the persistance list
// InstanceManager::configureManagerInstance()->registerPref(guiPrefs);

 // write file
 FileUtil::createDirectory(FileUtil::getUserFilesPath());
 // decide whether name is absolute or relative
 QFileInfo fileInfo = QFileInfo(configFilename);
 QFile* file;
 if (!fileInfo.isAbsolute())
 {
  // must be relative, but we want it to
  // be relative to the preferences directory
  file = new QFile(FileUtil::getUserFilesPath()+configFilename);
 }

 ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->storePrefs(new File(file->fileName()));
}

/*protected*/ void PreferencesPane::loadPreferenceFile() //throw (JmriException)
{
 if (configFilename != "")
 {
  log->debug("configure from specified file "+configFilename);
 }
 else
 {
  configFilename = "jmriprefs3.xml";
  log->debug("configure from default file "+configFilename);
 }
 FileUtil::createDirectory(FileUtil::getUserFilesPath());
 QFileInfo fileInfo = QFileInfo(configFilename);
 QFile* file;
 // decide whether name is absolute or relative
 if (!fileInfo.isAbsolute())
 {
  // must be relative, but we want it to
  // be relative to the preferences directory
  file = new QFile(FileUtil::getUserFilesPath()+configFilename);
 }
 try
 {
  configOK = ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->load(file);
 }
 catch (JmriException e) \
 {
  configOK = false;
  throw e;
 }
 log->debug(tr("end load config file, OK=")+(configOK?"yes":"no"));
}
