
#include "apps.h"
#include <QDateTime>
#include "instancemanager.h"
#include "defaultshutdownmanager.h"
#include "fileutil.h"
#include "file.h"
#include <QFileInfo>
#include "profilemanager.h"
#include "configxmlmanager.h"
#include "jmriuserpreferencesmanager.h"
#include "entryexitpairs.h"
#include "createbuttonmodel.h"
#include "resourcebundle.h"
#include "defaultshutdownmanager.h"
#include "defaultidtagmanager.h"
#include "tabbedpreferences.h"
#include <QBoxLayout>
#include "logixmanager.h"
#include "decoderindexfile.h"
#include "helputil.h"
#include "layoutblockmanager.h"
#include "defaultcatalogtreemanagerxml.h"
#include "sleeperthread.h"
#include "splashwindow.h"
#include <QMetaType>
#include <QMessageBox>
#include "dialogerrorhandler.h"
#include "appsbase.h"
#include "profilemanagerdialog.h"
#include "profile.h"
#include "defaultusermessagepreferencesxml.h"
#include "../libPr3/loconet/Pr3/pr3connectionconfigxml.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfigxml.h"
#include "programmerconfigpanexml.h"
#include "filelocationpanexml.h"
#include "guilafconfigpanexml.h"
#include "managerdefaultselectorxml.h"
#include "../libPr3/loconet/Pr3/pr3connectionconfig.h"
#include "../libPr3/loconet/Locobuffer/locobufferconnectionconfig.h"
#include "../libPr3/loconet/LocobufferUsb/locobufferusbconnectionconfig.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfig.h"
#include "blockvaluefile.h"
#include "filehistory.h"
#include <QMenu>
#include <QMenuBar>
#ifdef SCRIPTING_ENABLED
#include "jythonautomatonaction.h"
#include "jythonsigletaction.h"
#include "runjythonscript.h"
#include "jynstrument.h"
#include "jynstrumentfactory.h"
#endif
#include "../libPr3/loconet/LnOverTcp/lnovertcpconnectionconfig.h"
#include "audiotableaction.h"
//#include "blocktableaction.h"
//#include "lighttableaction.h"
//#include "memorytableaction.h"
//#include "reportertableaction.h"
//#include "signalmasttableaction.h"
//#include "transitableaction.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfig.h"
#include "../libPr3/loconet/HexFile/hexfileconnectionconfigxml.h"
#include "../libPr3/loconet/LnOverTcp/lnovertcpconnectionconfig.h"
#include "../libPr3/loconet/LnOverTcp/lnovertcpconnectionconfigxml.h"
#include <QDesktopWidget>
#include "connectionstatus.h"
#include "jmrixconfigpane.h"
#include "version.h"
#include <QApplication>
#include "jframeinterface.h"
#include "tabbedpreferencesaction.h"
#include "windowmenu.h"
#include "rostermenu.h"
#include "panelmenu.h"
#include "toolsmenu.h"
#include "lnturnoutmanagerxml.h"
#include "metatypes.h"
#include "activesystemsmenu.h"
#include "operationsmenu.h"
#include "../operations/setup.h"
#include "printdecoderlistaction.h"
#include "system.h"
#include "debugmenu.h"
#include "properties.h"
#include "jmriconfigurationmanager.h"
#include "jmriuserpreferencesmanager.h"
#include "treeaction.h"
#include "usbviewaction.h"
#include "withrottlecreationaction.h"
#include "joptionpane.h"
#include "webserveraction.h"
#include <QImageReader>
#include "startupactionsmanager.h"
#include "throttlewindow.h"
#include "application.h"
#include "fileutilsupport.h"
#include "testsmenu.h"
#include "appsconfigurationmanager.h"

//Apps::Apps(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
/**
 * Base class for Jmri applications.
 * <P>
 *
 * @author	Bob Jacobsen Copyright 2003, 2007, 2008, 2010
 * @author Dennis Miller Copyright 2005
 * @author Giorgio Terdina Copyright 2008
 * @author Matthew Harris Copyright (C) 2011
 * @version $Revision: 28162 $
 */
// /*public*/ class Apps extends JPanel implements PropertyChangeListener, WindowListener {

    /**
     *
     */
//	/*private*/ static final long serialVersionUID = 8846653289120123006L;
/*static*/ QString Apps::profileFilename;
/*static*/ QString Apps::configFilename = "jmriconfig2.xml";  // usually overridden, this is default
bool Apps::configOK = false;
bool Apps::configDeferredLoadOK = false;
/*static*/ QString Apps::nameString = "JMRI program";
//    @edu.umd.cs.findbugs.annotations.SuppressWarnings({"ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD", "SC_START_IN_CTOR"})//"only one application at a time. The thread is only called to help improve user experiance when opening the preferences, it is not critical for it to be run at this stage"
/*public*/ Apps::Apps(JFrame* frame, QWidget *parent) :
    QWidget(parent)
{
 setObjectName("Apps");
 //frame->setVisible(false);
 //super(true);
 //long start = System.nanoTime();
 start = QDateTime::currentMSecsSinceEpoch();
 _buttonSpace = nullptr;
 prefsAction = nullptr;
 cs4 = new QLabel("?", this);
 cs4->setObjectName("cs4");
 cs5 = new QLabel();
 cs6 = new QLabel();
 cs7 = new QLabel();
 connection = QVector<ConnectionConfig*>(4,nullptr);

 new Metatypes();
 QString path = FileUtil::getProgramPath();
 QString curDir = QDir::currentPath();

 _frame = frame;

 if(FileUtilSupport::getDefault()->getPaths() != nullptr && FileUtilSupport::getDefault()->getPaths()->count() > 1)
  FileUtilSupport::getDefault()->selectProgramPath(FileUtilSupport::getDefault()->getPaths());


 splash(false);
 splash(true, true);
 log->trace("splash screens up, about to setButtonSpace");
 setButtonSpace();
#ifdef SCRIPTING_ENABLED
    setJynstrumentSpace();
#endif

    log->trace("setLogo");
    Application::setLogo(logo());
    log->trace("setURL");
    Application::setURL(line2());
#if 0
    // Enable proper snapping of JSliders
    SliderSnap.init();

    // Prepare font lists
    prepareFontLists();
#endif

 // Get configuration profile
 // Needs to be done before loading a ConfigManager or UserPreferencesManager
 FileUtil::createDirectory(FileUtil::getPreferencesPath());
 // Needs to be declared final as we might need to
 // refer to this on the Swing thread
 /*final*/ File* profileFile;
 //Q_ASSERT(configFilename.endsWith(".xml"));
 profileFilename = configFilename.replace(".xml", ".properties");
 // decide whether name is absolute or relative
 File* info = new File(profileFilename);
 if (! info->isAbsolute())
 {
  // must be relative, but we want it to
  // be relative to the preferences directory
  profileFile = new File(FileUtil::getPreferencesPath() + profileFilename);
 }
 else
 {
  profileFile = new File(profileFilename);
 }
 ProfileManager::defaultManager()->setConfigFile(profileFile);
 // See if the profile to use has been specified on the command line as
 // a system property jmri.profile as a profile id.
 if (System::getProperties()->containsKey(/*ProfileManager::SYSTEM_PROPERTY)*/"org.jmri.profile"))
 {
  ProfileManager::getDefault()->setActiveProfile(System::getProperty(ProfileManager::SYSTEM_PROPERTY));
 }
 log->trace("check if profile exists");
 // @see jmri.profile.ProfileManager#migrateToProfiles JavaDoc for conditions handled here
 if (!profileFile->exists())
 { // no profile config for this app
  log->trace(tr("profileFile %1 doesn't exist").arg(profileFile->toString()));
  try
  {
   if (ProfileManager::defaultManager()->migrateToProfiles(configFilename))
   { // migration or first use
     // notify user of change only if migration occurred
     // TODO: a real migration message
     JOptionPane::showMessageDialog(sp,
             tr("Please ensure that the User Files location and Roster location are correct."),
             QApplication::applicationName(),
             JOptionPane::INFORMATION_MESSAGE);
   }
  }
  catch (IOException ex)
  {
   JOptionPane::showMessageDialog(sp,
           ex.getLocalizedMessage(),
           QApplication::applicationName(),
           JOptionPane::ERROR_MESSAGE);
   log->error(ex.getMessage());
  } catch (IllegalArgumentException ex) {
  JOptionPane::showMessageDialog(sp,
          ex.getLocalizedMessage(),
          QApplication::applicationName(),
          JOptionPane::ERROR_MESSAGE);
  log->error(ex.getMessage());
  }
 }
 try
 {
  ProfileManagerDialog::getStartingProfile(sp);
  // Manually setting the configFilename property since calling
  // Apps.setConfigFilename() does not reset the system property
  configFilename = FileUtil::getProfilePath() +   /*Profile::CONFIG_FILENAME*/"ProfileConfig.xml";
  System::setProperty("org.jmri.Apps.configFilename", /*Profile::CONFIG_FILENAME*/"ProfileConfig.xml");
  Profile* profile = ProfileManager::getDefault()->getActiveProfile();
  if(profile != nullptr)
  {
   log->info(tr("Starting with profile %1").arg(  ProfileManager::defaultManager()->getActiveProfile()->getId()));
  }
  else {
   log->info("Starting without a profile");
  }
  // rapid language set; must follow up later with full setting as part of preferences
  //apps.gui.GuiLafPreferencesManager.setLocaleMinimally(profile);

 }
 catch (IOException ex)
 {
   log->info("Profiles not configurable. Using fallback per-application configuration. Error: {}"/*, ex.getMessage()*/);
 }

 // add the default shutdown task to save blocks
 // as a special case, register a ShutDownTask to write out blocks
 ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->
         _register(new WriteBlocksShutdownTask("Writing Blocks"));

// _register(new AbstractShutDownTask("Writing Blocks"));

// {
//             @Override
//             public boolean execute() {
//                 // Save block values prior to exit, if necessary
//                 log.debug("Start writing block info");
//                 try {
//                     new BlockValueFile().writeBlockValues();
//                 } //catch (org.jdom2.JDOMException jde) { log.error("Exception writing blocks: {}", jde); }
//                 catch (IOException ioe) {
//                     log.error("Exception writing blocks: {}", ioe.getMessage());
//                 }

//                 // continue shutdown
//                 return true;
//             }
//         });

 // Install configuration manager and Swing error handler
 ConfigureManager* cm = nullptr;
 if((cm = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager")) == nullptr)
   cm = (ConfigureManager*)InstanceManager::setDefault("ConfigureManager", new AppsConfigurationManager());

  ConfigXmlManager::setErrorHandler(new DialogErrorHandler());
  //InstanceManager::setConfigureManager(cm);

  // Install a history manager
  InstanceManager::store(new FileHistory(), "FileHistory");
     // record startup
  ((FileHistory*)InstanceManager::getDefault("FileHistory"))->addOperation("app", nameString, NULL);

  // Install a user preferences manager
  InstanceManager::store(JmriUserPreferencesManager::getDefault(), "UserPreferencesManager");
  InstanceManager::store(new NamedBeanHandleManager(), "NamedBeanHandleManager");
  // Install an IdTag manager
  InstanceManager::store(new DefaultIdTagManager(), "IdTagManager");
  //Install Entry Exit Pairs Manager
  InstanceManager::store(new EntryExitPairs(), "EntryExitPairs");

  // install preference manager
  InstanceManager::store(new TabbedPreferences(), "TabbedPreferences");

  // Install abstractActionModel
  InstanceManager::store(new CreateButtonModel(), "CreateButtonModel");

  // find preference file and set location in configuration manager
  // Needs to be declared final as we might need to
  // refer to this on the Swing thread
  File* file;
  File* singleConfig;
  File* sharedConfig = NULL;
  // decide whether name is absolute or relative
  if (!(new File(configFilename))->isAbsolute())
  {
   // must be relative, but we want it to
   // be relative to the preferences directory
   singleConfig = new File(FileUtil::getUserFilesPath() + configFilename);
   }
  else
  {
   singleConfig = new File(configFilename);
  }
  try
  {
   // get preferences file
   sharedConfig = FileUtil::getFile(FileUtil::PROFILE + Profile::SHARED_CONFIG);
   if (!sharedConfig->canRead())
   {
    sharedConfig = NULL;
   }
  }
  catch (FileNotFoundException ex) {
   // ignore - sharedConfig will remain null in this case
  }
  // load config file if it exists
  if (sharedConfig != NULL)
  {
   file = sharedConfig;
  }
  else
  {
   file = singleConfig;
  }

  // now (attempt to) load the config file
  log->debug(tr("Using config file(s) %1").arg(file->getPath()));
  if (file->exists())
  {
   log->debug(tr("start load config file %1").arg(file->getPath()));
   try
   {
    configOK = cm->load(file, true);
   }
   catch (JmriException e)
   {
    log->error("Unhandled problem loading configuration", e);
    configOK = false;
   }
   log->debug(tr(", OK=%1").arg(configOK?"yes":"No"));
   }
   else
   {
   log->info(tr("No saved preferences, will open preferences window.  Searched for %1").arg( file->getPath()));
   configOK = false;
  }

  //Install Entry Exit Pairs Manager
  //   Done after load config file so that connection-system-specific Managers are defined and usable
  InstanceManager::store(new EntryExitPairs(), "EntryExitPairs");


  // populate GUI
  log->debug("Start UI");
 #if 0
  setLayout(new QVBoxLayout); //(this, BoxLayout.Y_AXIS));
  // Create a WindowInterface object based on the passed-in Frame
  JFrameInterface* wi = new JFrameInterface(frame);
  // Create a menu bar
  menuBar = new QMenuBar();
  menuBar->setObjectName("AppsMenuBar");
  if(frame != NULL)
   frame->setMenuBar(menuBar);

 // Create menu categories and add to the menu bar, add actions to menus
 createMenus(menuBar, wi);
#endif
 // done
 qint64 end = QDateTime::currentMSecsSinceEpoch();

 qint64 elapsedTime = (end - start) /*/ 1000000*/;
 /*
   his ensures that the message is displayed on the screen for a minimum of 2.5seconds, if the time taken
  to get to this point in the code is longer that 2.5seconds then the wait is not invoked.
  */
 long _sleep = 2500 - elapsedTime;
 if (_sleep > 0)
 {
  log->debug(QString("Debug message was displayed for less than 2500ms (%1ms). Sleeping for %2ms to allow user sufficient time to do something.").arg( elapsedTime).arg( _sleep));

  try
  {
   //sleep(_sleep);
   SleeperThread::msleep(_sleep);
  }
  catch (InterruptedException e)
  {
   log->error(e.getMessage());
  }
 }

 FileUtil::logFilePaths();
 splash(false);
 //splash(true, false);

 while (debugmsg)
 {
  /*The user has pressed the interupt key that allows them to disable logixs
    at start up we do not want to process any more information until the user
    has answered the question */
//  try
//  {
   //Thread.sleep(1000);
  SleeperThread::msleep(1000);
//        } catch (InterruptedException e) {
//            log->error(e.getLocalizedMessage(), e);
//        }
 }

 // Now load deferred config items
 if (file->exists())
 {
  // To avoid possible locks, deferred load should be
  // performed on the Swing thread
//  if (SwingUtilities.isEventDispatchThread())
//  {
  configDeferredLoadOK = doDeferredLoad(file);
//  }
//  else
//  {
//   try
//   {
//    // Use invokeAndWait method as we don't want to
//    // return until deferred load is completed
//    SwingUtilities.invokeAndWait(new Runnable()
//    {
//     //@Override
//     /*public*/ void run()
//     {
//      configDeferredLoadOK = doDeferredLoad(file);
//     }
//    });
//   }
//   catch (Exception ex)
//   {
//    log->error("Exception creating system console frame", ex);
//   }
//  }
 }
 else
 {
  configDeferredLoadOK = false;
 }
 // If preferences need to be migrated, do it now
 if (sharedConfig == NULL && configOK == true && configDeferredLoadOK == true)
 {
  log->info("Migrating preferences to new format...");
  // migrate preferences
  TabbedPreferences* tp = (TabbedPreferences*)InstanceManager::getOptionalDefault("TabbedPreferences");
  if(tp != NULL)
  {
      tp->init();
      tp->saveContents();
      cm->storePrefs();
  } //);
  // notify user of change
  log->info("Preferences have been migrated to new format.");
  log->info("New preferences format will be used after JMRI is restarted.");
//  if (!GraphicsEnvironment.isHeadless())
  {
      JOptionPane::showMessageDialog(sp,
              tr("%1 has been updated to a new storage format. The new storage format will be used next time this profile is used.").arg(ProfileManager::getDefault()->getActiveProfile()->getName()),
              QApplication::applicationName(),
              JOptionPane::INFORMATION_MESSAGE);
  }
 }
    /*Once all the preferences have been loaded we can initial the preferences
     doing it in a thread at this stage means we can let it work in the background*/
//    Runnable r = new Runnable() {
//        //@Override
//        /*public*/ void run() {
//            try {
//                InstanceManager::tabbedPreferencesInstance().init();
//            } catch (Exception ex) {
//                log->error("Error trying to setup preferences {}", ex.getLocalizedMessage(), ex);
//            }
//        }
//    };
 Run1* run1 = new Run1();
 QThread* thr = new QThread(run1);
 thr->setObjectName( "initialize preferences");
 thr->start();

    //Initialise the decoderindex file instance within a seperate thread to help improve first use perfomance
//    r = new Runnable() {
//        //@Override
//        /*public*/ void run() {
//            try {
//                DecoderIndexFile.instance();
//            } catch (Exception ex) {
//                log->error("Error in trying to initialize decoder index file {}", ex.toString());
//            }
//        }
//    };
 Run2* run2 = new Run2();
 QThread* thr2 = new QThread(run2);
 thr2->setObjectName("initialize decoder index");
 thr2->start();
#if 0  // done in main!
    if (bool.getbool("org.jmri.python.preload")) {
        r = new Runnable() {
            /*public*/ void run() {
                try {
                    PythonInterp.getPythonInterpreter();
                } catch (Exception ex) {
                    log->error("Error in trying to initialize python interpreter {}", ex.toString());
                }
            }
        };
        Thread thr3 = new Thread(r, "initialize python interpreter");
        thr3.start();
    }
#endif
 // if the configuration didn't complete OK, pop the prefs frame and help
 log->debug(QString("Config go OK? ")+ QString((configOK || configDeferredLoadOK)?"Yes":"No"));
 if ((!configOK) || (!configDeferredLoadOK))
 {
        HelpUtil::displayHelpRef("package.apps.AppConfigPanelErrorPage");
        doPreferences();
 }
 log->debug("Done with doPreferences, start statusPanel");

 // Before starting to load preferences, make sure some managers are created.
 // This is needed because these aren't particularly well-behaved during
 // creation.
 ((LogixManager*)InstanceManager::getDefault("LogixManager"))->activateAllLogixs();
 InstanceManager::getDefault("LayoutBlockManager");
 DefaultCatalogTreeManagerXml().readCatalogTrees();

 StartupActionsManager* mgr = (StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager");
 QTimer::singleShot(100, (StartupActionsManager*)mgr, SLOT(loadFactories()));

 log->debug("End constructor");
}
#if 0
void Apps::initGui() // must be called after Constructor is complete!
{

 if(_frame->centralWidget() == NULL)
 {
  QWidget* centralWidget = new QWidget;
  QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
  centralWidget->setLayout(centralWidgetLayout);
  _frame->setCentralWidget(centralWidget);
 }
 _frame->centralWidget()->layout()->addWidget(statusPanel());
 log->debug("Done with statusPanel, start buttonSpace");

 _frame->centralWidget()->layout()->addWidget(buttonSpace());

#if 0
    add(_jynstrumentSpace);
    long eventMask = AWTEvent.MOUSE_EVENT_MASK;

    Toolkit.getDefaultToolkit().addAWTEventListener(new AWTEventListener() {
        //@Override
        /*public*/ void eventDispatched(AWTEvent e) {
            if (e instanceof MouseEvent) {
                MouseEvent me = (MouseEvent) e;
                if (me.isPopupTrigger() && me.getComponent() instanceof JTextComponent) {
                    final JTextComponent component = (JTextComponent) me.getComponent();
                    final JPopupMenu menu = new JPopupMenu();
                    JMenuItem item;
                    item = new JMenuItem(new DefaultEditorKit.CopyAction());
                    item.setText("Copy");
                    item.setEnabled(component.getSelectionStart() != component.getSelectionEnd());
                    menu.add(item);
                    item = new JMenuItem(new DefaultEditorKit.CutAction());
                    item.setText("Cut");
                    item.setEnabled(component.isEditable() && component.getSelectionStart() != component.getSelectionEnd());
                    menu.add(item);
                    item = new JMenuItem(new DefaultEditorKit.PasteAction());
                    item.setText("Paste");
                    item.setEnabled(component.isEditable());
                    menu.add(item);
                    menu.show(me.getComponent(), me.getX(), me.getY());
                }
            }
        }
    }, eventMask);
#endif

}
#endif
/*public*/ void Apps::Run1::run() {
    try {
        ((TabbedPreferences*)InstanceManager::getDefault("TabbedPreferences"))->init();
    } catch (Exception ex) {
        Logger::error("Error trying to setup preferences {}"+ ex.getMessage());
    }
}
/*public*/ void Apps::Run2::run()
{
 try
 {
  (DecoderIndexFile*)InstanceManager::getDefault("DecoderIndexFile");
 }
 catch (Exception ex)
 {
  Logger::error("Error in trying to initialize decoder index file {}"+ ex.getMessage());
 }
}

/*private*/ bool Apps::doDeferredLoad(File* file)
{
 bool result;
 log->debug("start deferred load from config file " + file->getPath());
 try
 {
  ConfigureManager* cmOD = (ConfigureManager*)InstanceManager::getNullableDefault("ConfigureManager");
  if (cmOD != NULL) {
      result = cmOD->loadDeferred(file);
  } else {
      log->error("Failed to get default configure manager");
      result = false;
  }
 }
 catch (JmriException e)
 {
  log->error("Unhandled problem loading deferred configuration"+ e.getMessage());
  result = false;
 }
 log->debug(QString("end deferred load from config file, OK=") + ( result?"true":"false"));
 return result;
}

/**
 * @deprecated since 4.5.1
 */
//@Deprecated
/*protected*/ /*final*/ void Apps::addToActionModel() {
    // StartupActionModelUtil populates itself, so do nothing
}
/**
 * Prepare the JPanel to contain buttons in the startup GUI. Since it's
 * possible to add buttons via the preferences, this space may have
 * additional buttons appended to it later. The default implementation here
 * just creates an empty space for these to be added to.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "only one application at a time")
/*protected*/ void Apps::setButtonSpace() {
    _buttonSpace = new QWidget();
    _buttonSpace->setLayout(new FlowLayout());
}
#ifdef SCRIPTING_ENABLED
/*static*/ Component* Apps::_jynstrumentSpace = NULL;

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "only one application at a time")
/*protected*/ void Apps::setJynstrumentSpace() {
    _jynstrumentSpace = new Component();
    FlowLayout* _jynstrumentSpaceLayout;
    _jynstrumentSpace->setLayout(_jynstrumentSpaceLayout =new FlowLayout());
    AppsFileDrop* fileDrop = new AppsFileDrop(_jynstrumentSpace, new FileDrop::Listener(), this);
    Q_UNUSED(fileDrop);
//    new FileDrop(_jynstrumentSpace, new Listener() {
//        //@Override
//        /*public*/ void filesDropped(File[] files) {
//            for (int i = 0; i < files.length; i++) {
//                ynstrument(files[i].getPath());
//            }
//        }
//    });
}

AppsFileDrop::AppsFileDrop(Component *_jynstrumentSpace, FileDrop::Listener *listener, Apps* apps):FileDrop(_jynstrumentSpace, listener,apps)
{
 this->_jynstrumentSpace = _jynstrumentSpace;
 this->listener = listener;
 this->apps = apps;
}

void AppsFileDrop::filesDropped(QList<File *> files)
{
 for (int i = 0; i < files.length(); i++) {
     apps->ynstrument(files[i]->getPath());
 }
}

/*public*/ /*static*/ void Apps::ynstrument(QString path) {
    Jynstrument* it = JynstrumentFactory::createInstrument(path, _jynstrumentSpace);
    if (it == NULL) {
        log->error(tr("Error while creating Jynstrument %1").arg(path));
        return;
    }
    ThrottleWindow::setTransparent(it);
    it->setVisible(true);
    _jynstrumentSpace->setVisible(true);
    _jynstrumentSpace->layout()->addWidget(it);
}
#endif
/**
 * Create default menubar.
 * <P>
 * This does not include the development menu.
 *
 * @param menuBar Menu bar to be populated
 * @param wi WindowInterface where this menu bar will appear
 */
/*protected*/ void Apps::createMenus(QMenuBar* menuBar, WindowInterface* wi)
{
 // the debugging statements in the following are
 // for testing startup time
 log->debug("start building menus");

//    if (SystemType.isMacOSX()) {
//        Application.getApplication().setQuitHandler(new QuitHandler() {
//            //@Override
//            /*public*/ bool handleQuitRequest(EventObject eo) {
//                return handleQuit();
//            }
//        });
//    }

 fileMenu(menuBar, wi);
 editMenu(menuBar, wi);
 toolsMenu(menuBar, wi);
 rosterMenu(menuBar, wi);
 panelMenu(menuBar, wi);
 // check to see if operations in main menu
 if (Operations::Setup::isMainMenuEnabled())
 {
  operationsMenu(menuBar, wi);
 }
 systemsMenu(menuBar, wi);
 scriptMenu(menuBar, wi);
 debugMenu(menuBar, wi);
 menuBar->addMenu(new WindowMenu(wi)); // * GT 28-AUG-2008 Added window menu
 helpMenu(menuBar, wi);
 log->debug("end building menus");
}

/**
 * Create default File menu
 *
 * @param menuBar Menu bar to be populated
 * @param wi WindowInterface where this menu will appear as part of the menu bar
 */
/*protected*/ void Apps::fileMenu(QMenuBar* menuBar, WindowInterface* wi)
{
 QMenu* fileMenu = new QMenu(tr("File"));
 menuBar->addMenu(fileMenu);
 fileMenu->addAction(new PrintDecoderListAction(tr("Print decoder definitions..."), wi->getFrame(), false,this));
 fileMenu->addAction(new PrintDecoderListAction(tr("Print Preview decoder definitions..."), wi->getFrame(), true,this));
 // Use Mac OS X native Quit if using Aqua look and feel
 //if (!(SystemType.isMacOSX() && UIManager.getLookAndFeel().isNativeLookAndFeel()))
 {
  fileMenu->addSeparator();
  QAction* quitAction;
  fileMenu->addAction(quitAction = new QAction(tr("Quit"),wi));
//        {
//            /**
//             *
//             */
//            /*private*/ static final long serialVersionUID = -3051429826192051394L;

//            //@Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                handleQuit();
//            }
//        });
  connect(quitAction, SIGNAL(triggered()), this, SLOT(On_handleQuit()));
 }
}
void Apps::On_handleQuit()
{
 Apps::handleQuit();\
}
/*public*/ void Apps::doPreferences()
{
 if (prefsAction == nullptr) prefsAction = new TabbedPreferencesAction();
 ((TabbedPreferencesAction*)prefsAction)->actionPerformed();
}

/**
 * Set the location of the window-specific help for the preferences pane.
 * Made a separate method so if can be overridden for application specific
 * preferences help
 * @param frame The frame being described in the help system
 * @param location The location within the JavaHelp system
 */
/*protected*/ void Apps::setPrefsFrameHelp(JmriJFrame* frame, QString location)
{
 frame->addHelpMenu(location, true);
}

/*protected*/ void Apps::editMenu(QMenuBar* menuBar, WindowInterface* wi)
{

 QMenu* editMenu = new QMenu(tr("Edit"));
 menuBar->addMenu(editMenu);
#if 0 // TODO:
    // cut, copy, paste
    AbstractAction a;
    a = new DefaultEditorKit.CutAction();
    a.putValue(Action.NAME, tr("MenuItemCut"));
    editMenu.add(a);
    a = new DefaultEditorKit.CopyAction();
    a.putValue(Action.NAME, tr("MenuItemCopy"));
    editMenu.add(a);
    a = new DefaultEditorKit.PasteAction();
    a.putValue(Action.NAME, tr("MenuItemPaste"));
    editMenu.add(a);
#endif
 // prefs
 prefsAction = new TabbedPreferencesAction(tr("Preferences"), wi);
#if 0
    // Put prefs in Apple's prefered area on Mac OS X
    if (SystemType.isMacOSX()) {
        Application.getApplication().setPreferencesHandler(new PreferencesHandler() {
            //@Override
            /*public*/ void handlePreferences(EventObject eo) {
                doPreferences();
            }
        });
    }
#endif
 // Include prefs in Edit menu if not on Mac OS X or not using Aqua Look and Feel
 //if (!SystemType.isMacOSX() || !UIManager.getLookAndFeel().isNativeLookAndFeel())
 {
  editMenu->addSeparator();
  editMenu->addAction(prefsAction);
 }
}

/*protected*/ void Apps::toolsMenu(QMenuBar* menuBar, WindowInterface* /*wi*/)
{
 menuBar->addMenu(new ToolsMenu(tr("Tools")/*,wi*/));
}

/*protected*/ void Apps::operationsMenu(QMenuBar* menuBar, WindowInterface* /*wi*/)
{
 menuBar->addMenu(new OperationsMenu());
}

/*protected*/ void Apps::rosterMenu(QMenuBar* menuBar, WindowInterface* /*wi*/)
{
 menuBar->addMenu(new RosterMenu(tr("Roster"), RosterMenu::MAINMENU, this));
}

/*protected*/ void Apps::panelMenu(QMenuBar* menuBar, WindowInterface* /*wi*/)
{
 menuBar->addMenu((PanelMenu*)InstanceManager::getDefault("PanelMenu"));
}

/**
 * Show only active systems in the menu bar.
 * <P>
 * Alternately, you might want to do
 * <PRE>
 *    menuBar.add(new jmri.jmrix.SystemsMenu());
 * </PRE>
 *
 * @param menuBar
 * @param wi
 */
/*protected*/ void Apps::systemsMenu(QMenuBar* menuBar, WindowInterface* wi)
{
 ActiveSystemsMenu::addItems(menuBar, wi->getFrame());
}

/*protected*/ void Apps::debugMenu(QMenuBar* menuBar, WindowInterface* wi) {
    QMenu* d = new DebugMenu(wi->getFrame());
#if 0
    // also add some tentative items from jmrix
    d.add(new JSeparator());
    d.add(new jmri.jmrix.pricom.PricomMenu());
#endif
    d->addSeparator();
    d->addAction(new TreeAction(this));
    d->addAction(new UsbViewAction(this));
    d->addSeparator();
    d->addAction(new RunJythonScript("RailDriver Throttle", new File("jython/RailDriver.py"),this));

    // also add some tentative items from webserver
    d->addSeparator();
    d->addAction(new WebServerAction(this));

    d->addSeparator();
    d->addAction(new WiThrottleCreationAction(this));

    d->addSeparator();
    QMenu* testsMenu = new TestsMenu();
    d->addMenu(testsMenu);


    menuBar->addMenu(d);

}

/*protected*/ void Apps::scriptMenu(QMenuBar* menuBar, WindowInterface* /*wi*/)
{
 // temporarily remove Scripts menu; note that "Run Script"
 // has been added to the Panels menu
 QMenu* menu = new QMenu("Scripts");
 menuBar->addMenu(menu);
#ifdef SCRIPTING_ENABLED
 menu->addAction(new RunJythonScript("Run Jython script", this));
 menu->addAction(new JythonAutomatonAction("Jython script", this));
 menu->addAction(new JythonSigletAction("Jython siglet", this));
#else
 menu->setEnabled(false);
#endif
}
#if 0
/*protected*/ void developmentMenu(JMenuBar menuBar, WindowInterface wi) {
    JMenu devMenu = new JMenu("Development");
    menuBar.add(devMenu);
    devMenu.add(new jmri.jmrit.symbolicprog.autospeed.AutoSpeedAction("Auto-speed tool"));
    devMenu.add(new JSeparator());
    devMenu.add(new jmri.jmrit.automat.SampleAutomatonAction("Sample automaton 1"));
    devMenu.add(new jmri.jmrit.automat.SampleAutomaton2Action("Sample automaton 2"));
    devMenu.add(new jmri.jmrit.automat.SampleAutomaton3Action("Sample automaton 3"));
    //devMenu.add(new JSeparator());
    //devMenu.add(new jmri.jmrix.serialsensor.SerialSensorAction("Serial port sensors"));
}
#endif
/*protected*/ void Apps::helpMenu(QMenuBar* menuBar, WindowInterface* wi)
{
 //try {


 // create menu and standard items
 QMenu* helpMenu = HelpUtil::instance()->makeHelpMenu(mainWindowHelpID(), true, wi);

 // tell help to use default browser for external types
// SwingHelpUtilities.setContentViewerUI("jmri.util.ExternalLinkContentViewerUI");

 // use as main help menu
 menuBar->addMenu(helpMenu);

//    } catch (Throwable e3) {
//        log->error("Unexpected error creating help.", e3);
//    }

}

/**
 * Returns the ID for the main window's help, which is application specific
 */
/*protected*/ QString Apps::mainWindowHelpID() {
    return "package.apps.Apps";
}

/*protected*/ QString Apps::line1() {
    return tr("%1, part of the JMRI project").arg( Version::name());
}

/*protected*/ QString Apps::line2() {
    return "http://jmri.org/";
}

/*protected*/ QString Apps::line3() {
    return " ";
}


/*protected*/ void Apps::buildLine4(QWidget* pane)
{
 if (connection[0] != NULL)
 {
  buildLine(connection[0], cs4, pane);
 }
}

/*protected*/ void Apps::buildLine5(QWidget* pane)
{
 if (connection[1] != NULL)
 {
  buildLine(connection[1], cs5, pane);
 }
}

/*protected*/ void Apps::buildLine6(QWidget* pane)
{
 if (connection[2] != NULL)
 {
  buildLine(connection[2], cs6, pane);
 }
}

/*protected*/ void Apps::buildLine7(QWidget* pane)
{
 if (connection[3] != NULL)
 {
  buildLine(connection[3], cs7, pane);
 }
}

/*protected*/ void Apps::buildLine(ConnectionConfig* conn, QLabel* cs, QWidget* pane)
{
 if (conn->name()==(JmrixConfigPane::NONE))
 {
  cs->setText(" ");
  return;
 }
 ConnectionStatus::instance()->addConnection(conn->name(), conn->getInfo());
 cs->setFont(pane->font());
 updateLine(conn, cs);
 ((QVBoxLayout*)pane->layout())->addWidget(cs, 0, Qt::AlignLeft);
}

/*protected*/ void Apps::updateLine(ConnectionConfig* conn, QLabel* cs)
{
 if (conn->getDisabled())
 {
  return;
 }
 QString name = conn->getConnectionName();
 if (name == NULL)
 {
  name = conn->getManufacturer();
 }
 if (ConnectionStatus::instance()->isConnectionOk(conn->getInfo()))
 {
  //cs->setForeground(QColor::black());
  cs->setStyleSheet("QLabel { color: black};");
  QString cf = tr("%1: using %2 on %3").arg(name).arg(conn->name()).arg( conn->getInfo());
  cs->setText(cf);
 }
 else
 {
  //cs.setForeground(Color.red);
  QString cf = tr("ConnectionFailed = %1: ERROR %2 using %3").arg(name).arg(conn->name()).arg( conn->getInfo());
  cf = cf.toUpper();
  cs->setText(cf);
  cs->setStyleSheet("QLabel { color: red};");
 }
    //this.revalidate();
 connect(ConnectionStatus::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*protected*/ QString Apps::line8() {
    return " ";
}

/*protected*/ QString Apps::line9() {
//    return tr("JavaVersionCredit",
//            System.getProperty("java.version", "<unknown>"),
//            Locale.getDefault().toString());
    // Java version {0} ({1})
 return tr("Qt version %1").arg(Version::getCanonicalVersion());
}

/*protected*/ QString Apps::logo() {
 qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();

 QImageReader reader(":resources/logo.gif");
 qDebug() << "Can read file?:" << reader.canRead();

 QImage image = reader.read();
 qDebug() << reader.errorString();
    return ":resources/logo.gif";
}

/**
 * Fill in the logo and status panel
 *
 * @return Properly-filled out JPanel
 */
/*protected*/ QWidget* Apps::statusPanel()
{
 QWidget* pane1 = new QWidget();
 QHBoxLayout* pane1Layout;
 pane1->setLayout(pane1Layout = new QHBoxLayout); //(pane1, BoxLayout.X_AXIS));
 log->debug(tr("Fetch main logo: %1").arg(logo()));
 // TODO: pane1Layout->addWidget(new QLabel(new ImageIcon(getToolkit().getImage(logo()), "JMRI logo"), JLabel.LEFT));
 pane1Layout->addWidget(new JLabel("JMRI logo", new ImageIcon(logo(), "JMRI logo"),JLabel::LEFT),0, Qt::AlignCenter);
 //    pane1Layout->addWidget(Box.createRigidArea(new Dimension(15, 0))); // Some spacing between logo and status panel

 log->debug("start labels");
 QWidget* pane2 = new QWidget();
 QVBoxLayout* pane2Layout;
 pane2->setLayout(pane2Layout = new QVBoxLayout); //(pane2, BoxLayout.Y_AXIS));
 pane2Layout->addWidget(new QLabel(line1()),0,Qt::AlignLeft);
 pane2Layout->addWidget(new QLabel(line2()),0,Qt::AlignLeft);
 pane2Layout->addWidget(new QLabel(line3()),0,Qt::AlignLeft);

 if (ProfileManager::getDefault()!=NULL && ProfileManager::getDefault()->getActiveProfile() != NULL)
 {
  pane2Layout->addWidget(new QLabel(tr("Active Profile: %1").arg(ProfileManager::getDefault()->getActiveProfile()->getName())));
 }
 else
 {
  pane2Layout->addWidget(new QLabel(tr("Failed Profile:")));
 }
 // add listerner for Com port updates
 //ConnectionStatus::instance().addPropertyChangeListener(this);
 connect(ConnectionStatus::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this,  SLOT(propertyChange(PropertyChangeEvent*)));
 //ArrayList<Object> connList = InstanceManager::configureManagerInstance().getInstanceList(ConnectionConfig.class);
 QObjectList connList = ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->getInstanceList("ConnectionConfig");

 int i = 0;
 if (!connList.isEmpty())
 {
  for (int x = 0; x < connList.size(); x++)
  {
   ConnectionConfig* conn = (ConnectionConfig*) connList.at(x);
   if (!conn->getDisabled())
   {
    connection[i] = conn;
    i++;
   }
   if (i > 3)
   {
    break;
   }
  }
 }
 buildLine4(pane2);
 buildLine5(pane2);
 buildLine6(pane2);
 buildLine7(pane2);

 pane2Layout->addWidget(new QLabel(line8()),0,Qt::AlignLeft);
 pane2Layout->addWidget(new QLabel(line9()),0,Qt::AlignLeft);
 pane1Layout->addWidget(pane2,0,Qt::AlignLeft);
 return pane1;
}

/*protected*/void  Apps::closeEvent(QCloseEvent * e)
{
 windowClosing(e);
}

/**
 * Closing the main window is a shutdown request
 */
//@Override
/*public*/ void Apps::windowClosing(QCloseEvent* e)
{/*
    if (JOptionPane.showConfirmDialog(NULL,
            tr("MessageLongCloseWarning"),
            tr("MessageShortCloseWarning"),
            JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)*/
 if(QMessageBox::question(NULL, tr("Quit?"), tr("Closing this window will quit the program. Close?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
 {
  handleQuit();
 }
 // if get here, didn't quit, so don't close window
 e->ignore();
}
#if 0
//@Override
/*public*/ void windowActivated(WindowEvent e) {
}

//@Override
/*public*/ void windowClosed(WindowEvent e) {
}

//@Override
/*public*/ void windowDeactivated(WindowEvent e) {
}

//@Override
/*public*/ void windowDeiconified(WindowEvent e) {
}

//@Override
/*public*/ void windowIconified(WindowEvent e) {
}

//@Override
/*public*/ void windowOpened(WindowEvent e) {
}
#endif
/*static*/ /*protected*/ void Apps::setJmriSystemProperty(QString key, QString value) {
    try {
        QString current = System::getProperty("org.jmri.Apps." + key);
        if (current == NULL) {
            System::setProperty("org.jmri.Apps." + key, value);
        } else if (current != (value)) {
            log->warn(tr("JMRI property %1 already set to %2, skipping reset to %3").arg(key).arg(current).arg(value));
        }
    } catch (Exception e) {
        log->error(tr("Unable to set JMRI property %1 to %2 due to execption %3").arg(key).arg(value).arg(e.getMessage()));
    }
}

/**
 * Provide access to a place where applications can expect the configuration
 * code to build run-time buttons.
 *
 * @see apps.CreateButtonPanel
 * @return NULL if no such space exists
 */
/*static*/ /*public*/ QWidget* Apps::buttonSpace() {
    return _buttonSpace;
}
/*static*/ QWidget* Apps::_buttonSpace = NULL;
/*static*/ AppConfigBase*Apps:: prefs = NULL;

/*static*/ /*public*/ AppConfigBase* Apps::getPrefs()
{
    return prefs;
}

/*static*/ SplashWindow* Apps::sp = NULL;
///*static*/ AWTEventListener* Apps::debugListener = NULL;
bool Apps::debugListener = false;
/*static*/ bool Apps::debugFired = false;  // true if we've seen F8 during startup
/*static*/ bool Apps::debugmsg = false;    // true while we're handling the "No Logix?" prompt window on startup

/*static*/ /*protected*/ void Apps::splash(bool show)
{
 splash(show, false);

}

/*static*/ /*protected*/ void Apps::splash(bool show, bool debug)
{
 //Log4JUtil::initLog4J();
 if (debugListener == false && debug)
 {
  // set a global listener for debug options
   debugFired = false;
//   Toolkit.getDefaultToolkit().addAWTEventListener(
//                debugListener = new AWTEventListener() {
//                    //@Override
//                    /*public*/ void eventDispatched(AWTEvent e) {
//                        if (!debugFired) {
//                            /*We set the debugmsg flag on the first instance of the user pressing any button
//                             and the if the debugFired hasn't been set, this allows us to ensure that we don't
//                             miss the user pressing F8, while we are checking*/
//                            debugmsg = true;
//                            if (e.getID() == KeyEvent.KEY_PRESSED) {
//                                KeyEvent ky = (KeyEvent) e;
//                                if (ky.getKeyCode() == 119) {
//                                    startupDebug();
//                                }
//                            } else {
//                                debugmsg = false;
//                            }
//                        }
//                    }
//                },
//                AWTEvent.KEY_EVENT_MASK);
  }

  debugListener = true;
  // bring up splash window for startup
  if (sp == NULL)
  {
   if (debug)
   {
    sp = new SplashWindow(splashDebugMsg(),NULL);
   }
   else
   {
    sp = new SplashWindow();
   }
 }
 sp->setVisible(show);
 if (!show)
 {
  sp->close();
  sp->dispose();
  sp->deleteLater();
//        Toolkit.getDefaultToolkit().removeAWTEventListener(debugListener);
  debugListener = NULL;
  sp = NULL;
 }
}
void Apps::keyPressEvent(QKeyEvent *e)
{
 if(debugListener )
 {
  if (!debugFired)
  {
   /*We set the debugmsg flag on the first instance of the user pressing any button
     and the if the debugFired hasn't been set, this allows us to ensure that we don't
     miss the user pressing F8, while we are checking*/
   debugmsg = true;
   if (e->type() == QEvent::KeyPress)
   {
    QKeyEvent* ky =  e;
    //if (ky.getKeyCode() == 119)
    if(ky->key() == Qt::Key_F8)
    {
     startupDebug();
    }
   }
   else
   {
    debugmsg = false;
   }
  }
 }
}

/*static*/ /*protected*/ QWidget* Apps::splashDebugMsg()
{
 QLabel* panelLabel = new QLabel("Press F8 to disable logixs");
//    panelLabel->setFont(panelLabel->getFont().deriveFont(9f));
 QWidget* panel = new QWidget();
 FlowLayout* l = new FlowLayout;
 panel->setLayout(l);
 l->addWidget(panelLabel);
 return panel;
}

/*static*/ /*protected*/ void Apps::startupDebug()
{
 debugFired = true;
 debugmsg = true;

//    Object[] options = {"Disable",
//        "Enable"};
 QVariantList options = QVariantList() << "Disable" << "Enable";

    int retval = JOptionPane::showOptionDialog(NULL, "Start JMRI with Logix enabled or disabled?", "Start Up",
            JOptionPane::YES_NO_OPTION,
            JOptionPane::QUESTION_MESSAGE, QIcon(), options, options[0]);

 if (retval != 0)
 {
  debugmsg = false;
  return;
 }
 ((LogixManager*)InstanceManager::getDefault("LogixManager"))->setLoadDisabled(true);
 Logger* log = new Logger("Apps");
 log->info("Requested loading with Logixs disabled.");
 debugmsg = false;
}

/**
 * The application decided to quit, handle that.
 */
/*static*/ /*public*/ bool Apps::handleQuit() {
    return AppsBase::handleQuit();
}

/**
 * The application decided to restart, handle that.
 */
/*static*/ /*public*/ bool Apps::handleRestart() {
    return AppsBase::handleRestart();
}

/**
 * Set up the configuration file name at startup.
 * <P>
 * The Configuration File name variable holds the name used to load the
 * configuration file during later startup processing. Applications invoke
 * this method to handle the usual startup hierarchy:
 * <UL>
 * <LI>If an absolute filename was provided on the command line, use it
 * <LI>If a filename was provided that's not absolute, consider it to be in
 * the preferences directory
 * <LI>If no filename provided, use a default name (that's application
 * specific)
 * </UL>
 * This name will be used for reading and writing the preferences. It need
 * not exist when the program first starts up. This name may be proceeded
 * with <em>config=</em> and may not contain the equals sign (=).
 *
 * @param def Default value if no other is provided
 * @param args Argument array from the main routine
 */
/*static*/ /*protected*/ void Apps::setConfigFilename(QString def, char *args[])
{
 Logger log = Logger("Apps");
 // save the configuration filename if present on the command line
 QStringList sl;
 while(*args != NULL)
 {
  sl.append(QString(*args));
  args++;
 }

 if (sl.length() > 1 && sl.at(1) != NULL && !(sl.at(1).contains("=")))
 {
  def = sl.at(1);
  log.debug("Config file was specified as: "+ QString(args[1]));
 }
 foreach (QString arg, sl)
 {
  QStringList split = (arg).split("="/*, 2*/);
  if (split.length() == 2 && QString::compare(split[0], "config",Qt::CaseInsensitive))
  {
   def = split[1];
   log.debug("Config file was specified as:" + arg);
  }
 }

 Apps::configFilename = def;
 setJmriSystemProperty("configFilename", def);
}

/*static*/ /*public*/ QString Apps::getConfigFileName() {
    return configFilename;
}

/*static*/ /*protected*/ void Apps::createFrame(Apps* containedPane, JFrame* frame)
{
 // create the main frame and menus

 // invoke plugin, if any
//    JmriPlugin.start(frame, containedPane.menuBar);

// frame->setMenuBar(((JFrame*)containedPane)->menuBar());
 //frame.getContentPane().add(containedPane);
 if(frame->centralWidget() == NULL)
 {
  QWidget* centralWidget = new QWidget;
  QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
  centralWidget->setLayout(centralWidgetLayout);
  frame->setCentralWidget(centralWidget);
 }
 //((QVBoxLayout*)frame->centralWidget()->layout())->addWidget(containedPane);
 frame->centralWidget()->layout()->addWidget(statusPanel());
 log->debug("Done with statusPanel, start buttonSpace");

 frame->centralWidget()->layout()->addWidget(buttonSpace());

 // Create a WindowInterface object based on the passed-in Frame
 JFrameInterface* wi = new JFrameInterface(frame);
 // Create a menu bar
 menuBar = new QMenuBar();
 menuBar->setObjectName("AppsMenuBar");
 if(frame != NULL)
  frame->setMenuBar(menuBar);

// Create menu categories and add to the menu bar, add actions to menus
createMenus(menuBar, wi);

 // handle window close
 frame->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
 frame->addWindowListener((WindowListener*)containedPane);

 // pack and center this frame
 frame->adjustSize();
 //QSize screen = frame.getToolkit().getScreenSize();
 QDesktopWidget* desktop = QApplication::desktop();
 QSize screen = desktop->screen()->size();QSize size = frame->size();
 frame->setLocation((screen.width() - size.width()) / 2, (screen.height() - size.height()) / 2);
 frame->setVisible(true);
}
#if 0
static /*protected*/ void loadFile(String name) {
    URL pFile = InstanceManager::configureManagerInstance().find(name);
    if (pFile != NULL) {
        try {
            InstanceManager::configureManagerInstance().load(pFile);
        } catch (JmriException e) {
            log->error("Unhandled problem in loadFile", e);
        }
    } else {
        log->warn("Could not find {} config file", name);
    }

}
// The following MUST be /*protected*/ for 3rd party applications
// (such as CATS) which are derived from this class.
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "MS_PKGPROTECT",
        justification = "The following MUST be /*protected*/ for 3rd party applications (such as CATS) which are derived from this class.")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "MS_PKGPROTECT",
        justification = "The following MUST be /*protected*/ for 3rd party applications (such as CATS) which are derived from this class.")
/*protected*/ static bool configDeferredLoadOK;
// GUI members
/*private*/ JMenuBar menuBar;


/*protected*/ static void setApplication(String name) {
    try {
        jmri.Application.setApplicationName(name);
    } catch (IllegalArgumentException ex) {
        log->warn("Unable to set application name", ex);
    } catch (IllegalAccessException ex) {
        log->warn("Unable to set application name", ex);
    }
}

/**
 * Set, log and return some startup information.
 * <p>
 * This method needs to be refactored, but it's in use (2/2014) by CATS so
 * can't easily be changed right away.
 *
 * @deprecated Since 3.7.1, use {@link #setStartupInfo(java.lang.String) }
 * plus {@link Log4JUtil#startupInfo(java.lang.String) }
 */
@Deprecated
/*protected*/ static String startupInfo(String name) {
    setStartupInfo(name);
    return Log4JUtil.startupInfo(name);
}
#endif
/**
 * Set and log some startup information. This is intended to be the central
 * connection point for common startup and logging.
 *
 * @param name Program/application name as known by the user
 */
/*protected*/ /*static*/ void Apps::setStartupInfo(QString name) {
    // Set the application name
//    try {
//        jmri.Application.setApplicationName(name);
//    } catch (IllegalArgumentException ex) {
//        log->warn("Unable to set application name", ex);
//    } catch (IllegalAccessException ex) {
//        log->warn("Unable to set application name", ex);
//    }
 QCoreApplication::setApplicationName(name);
    // Log the startup information
    //log->info(Log4JUtil.startupInfo(name));
}
#if 0
/*private*/ void prepareFontLists() {
    // Prepare font lists
    new Thread(new Runnable() {
        //@Override
        /*public*/ void run() {
            log->debug("Prepare font lists...");
            FontComboUtil.prepareFontLists();
            log->debug("...Font lists built");
        }
    }).start();
}
#endif
//@Override
/*public*/ void Apps::propertyChange(PropertyChangeEvent* /*ev*/)
{
 if (log->isDebugEnabled())
 {
  log->debug("property change: comm port status update");
 }
 if (connection[0] != NULL)
 {
  cs4 = new QLabel();
  updateLine(connection[0], cs4);
 }

 if (connection[1] != NULL)
 {
  updateLine(connection[1], cs5);
 }

 if (connection[2] != NULL)
 {
  updateLine(connection[2], cs6);
 }

 if (connection[3] != NULL)
 {
  updateLine(connection[3], cs7);
 }

}
#if 0
bool Apps::MyAbstractShutDownTask::execute()
{
 // Save block values prior to exit, if necessary
    log->debug("Start writing block info");
    try {
        new BlockValueFile().writeBlockValues();
    } //catch (org.jdom2.JDOMException jde) { log->error("Exception writing blocks: {}", jde); }
    catch (IOException ioe) {
        log->error("Exception writing blocks: {}", ioe);
    }

    // continue shutdown
    return true;
}
#endif
WriteBlocksShutdownTask::WriteBlocksShutdownTask(QString name)
    : AbstractShutDownTask(name)
{
 log = new Logger("WriteBlocksShutdownTask");
}

bool WriteBlocksShutdownTask::execute()
{
 // Save block values prior to exit, if necessary
 log->debug("Start writing block info");
 try
 {
  BlockValueFile* f = new BlockValueFile();
  f->writeBlockValues();
 } //catch (org.jdom2.JDOMException jde) { log->error("Exception writing blocks: {}", jde); }
 catch (IOException ioe)
 {
  log->error(tr("Exception writing blocks: %1").arg(ioe.getMessage()));
 }

// continue shutdown
return true;
}

/*static*/ /*private*/ Logger* Apps::log = LoggerFactory::getLogger("Apps");
