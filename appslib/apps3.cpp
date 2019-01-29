#include "apps3.h"
#include "systemconsole.h"
#include "flowlayout.h"
#include "jmrijframe.h"
#include "helputil.h"
#include "instancemanager.h"
#include "createbuttonmodel.h"
#include "splashwindow.h"
#include "fileutil.h"
#include "file.h"
#include "profilemanager.h"
#include <QMessageBox>
#include "profilemanagerdialog.h"
#include "logger.h"
#include "QApplication"
#include <QLabel>
#include <QWidget>
#include "flowlayout.h"
#include "profile.h"
#include "system.h"
#include "properties.h"
#include <QToolBar>
#include "firsttimestartupwizard.h"
#include "firsttimestartupwizardaction.h"

//Apps3::Apps3(QObject *parent) :
//  AppsBase(parent)
//{
//}
/**
 * Base class for GUI3 JMRI applications.
 * <p>
 * This is a complete re-implementation of the apps.Apps support for JMRI
 * applications.
 * <p>
 * Each using application provides it's own main() method. See e.g.
 * apps.gui3.demo3.Demo3 for an example.
 * <p>
 * There are a large number of missing features marked with TODO in comments
 * including code from the earlier implementation.
 * <P>
 * @author	Bob Jacobsen Copyright 2009, 2010
 * @version $Revision: 28851 $
 */
///*public*/  abstract class Apps3 extends AppsBase {

/**
 * Initial actions before frame is created, invoked in the applications
 * main() routine.
 */
/*static*/ /*public*/  void Apps3::preInit(QString applicationName) {
 AppsBase::preInit(applicationName);

 // Initialise system console
 // Put this here rather than in apps.AppsBase as this is only relevant
 // for GUI applications - non-gui apps will use STDOUT & STDERR
 SystemConsole::create();

 splash(true);

 setButtonSpace();

}
/*static*/ AWTEventListener* Apps3::debugListener = NULL;
/**
 * Create and initialize the application object.
 * <p>
 * Expects initialization from preInit() to already be done.
 */
/*public*/  Apps3::Apps3(QString applicationName, QString configFileDef, QStringList args, QObject *parent) :
  AppsBase(applicationName, configFileDef, args, parent)
{
 log = new Logger("Apps3");
 // pre-GUI work
 //super(applicationName, configFileDef, args);
 AppsBase::init();
 // Prepare font lists
 prepareFontLists();

 addToActionModel();
 // create GUI
 initializeHelpSystem();
 //    if (SystemType.isMacOSX()) {
 //        initMacOSXMenus();
 //    }
 if (((!configOK) || (!configDeferredLoadOK)) &&  (!preferenceFileExists))
 {
#if 1
    FirstTimeStartUpWizardAction* prefsAction = new FirstTimeStartUpWizardAction("Start Up Wizard",this);
    prefsAction->setApp(this);
    prefsAction->actionPerformed(nullptr);
    return;
#endif
 }
 //createAndDisplayFrame();
 //QTimer::singleShot(200, this, SLOT(createAndDisplayFrame())); // make sure that DecoderPro3's constructor is finished.
}

/**
 * For compatability with adding in buttons to the toolbar using the
 * existing createbuttonmodel
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "only one application at a time")
/*protected*/ /*static*/ void Apps3::setButtonSpace() {
    _buttonSpace = new QWidget();
    _buttonSpace->setLayout(new FlowLayout); //(FlowLayout::LEFT));
}

/**
 * Provide access to a place where applications can expect the configuration
 * code to build run-time buttons.
 *
 * @see apps.CreateButtonPanel
 * @return NULL if no such space exists
 */
/*static*/ /*public*/  QWidget* Apps3::buttonSpace() {
    return _buttonSpace;
}
/*static*/ QWidget* Apps3::_buttonSpace = NULL;

/*protected*/ void Apps3::initializeHelpSystem() {
    try {

        // initialize help system
        HelpUtil::initOK();

        // tell help to use default browser for external types
//        SwingHelpUtilities.setContentViewerUI("jmri.util.ExternalLinkContentViewerUI");

        // help items are set in the various Tree/Menu/Toolbar constructors
    } catch (Throwable e3) {
        Logger::error("Unexpected error creating help: " + e3.getMessage());
    }
}

/*abstract*/ /*protected*/ void Apps3::createMainFrame() {}

/*public*/  void Apps3::createAndDisplayFrame() {
    createMainFrame();

    //A Shutdown manager handles the quiting of the application
    mainFrame->setDefaultCloseOperation(JFrame::DO_NOTHING_ON_CLOSE);
    displayMainFrame(mainFrame->getMaximumSize());
}

// /*abstract*/ /*protected*/ ResourceBundle getActionModelResourceBundle();

/*protected*/ void Apps3::addToActionModel() {
 CreateButtonModel* bm = (CreateButtonModel*)InstanceManager::getDefault("CreateButtonModel");
 Q_UNUSED(bm);
//    ResourceBundle rb = getActionModelResourceBundle();
//    if (rb == NULL || bm == NULL) {
//        return;
//    }
 //    QStringListIterator e = rb.getKeys();
 //    while (e.hasMoreElements()) {
 //        QString key = e.nextElement();
 //        try {
 //            bm.addAction(key, rb.getString(key));
 //        } catch (ClassNotFoundException ex) {
 //            log->error("Did not find class " + key);
 //        }
 //    }

}

/**
 * Set a toolbar to be initially floating. This doesn't quite work right.
 */
/*protected*/ void setFloating(QToolBar* toolBar) {
    //((javax.swing.plaf.basic.BasicToolBarUI) toolBar.getUI()).setFloatingLocation(100,100);
#if 0 // TODO:
    ((javax.swing.plaf.basic.BasicToolBarUI) toolBar.getUI()).setFloating(true, new Point(500, 500));
#else
 toolBar->setFloatable(true);
 toolBar->move(500,500);
#endif
}

/*protected*/ void Apps3::displayMainFrame(QSize d) {
    mainFrame->resize(d);
    mainFrame->setVisible(true);
}

/**
 * Final actions before releasing control of app to user
 */
//@Override
/*protected*/ void Apps3::start()
{
 // TODO: splash(false);
 AppsBase::start();
 splash(false);
}

/*static*/ /*protected*/ void Apps3::splash(bool show)
{
 splash(show, false);
}

/*static*/ SplashWindow* Apps3::sp = NULL;
///*static*/ AWTEventListener* Apps3::debugListener = NULL;
/*static*/ bool Apps3::debugFired = false;
/*static*/ bool Apps3::debugmsg = false;

/*static*/ /*protected*/ void Apps3::splash(bool show, bool debug)
{
 if (debugListener == NULL && debug)
 {
  // set a global listener for debug options
  debugFired = false;
//        debugListener = new AWTEventListener();
//        {

//            //@Override
//            /*public*/  void eventDispatched(AWTEvent e) {
//                if (!debugFired) {
//                    /*We set the debugmsg flag on the first instance of the user pressing any button
//                     and the if the debugFired hasn't been set, this allows us to ensure that we don't
//                     miss the user pressing F8, while we are checking*/
//                    debugmsg = true;
//                    if (e.getID() == KeyEvent.KEY_PRESSED) {
//                        if (((KeyEvent) e).getKeyCode() == 119) {
//                            startupDebug();
//                        }
//                    } else {
//                        debugmsg = false;
//                    }
//                }
//            }
//        };
//        Toolkit.getDefaultToolkit().addAWTEventListener(debugListener,
//                AWTEvent.KEY_EVENT_MASK);
 }

 // bring up splash window for startup
 if (sp == NULL)
 {
  sp = new SplashWindow((debug ? splashDebugMsg() : NULL),0);
 }
 sp->setVisible(show);
 if (!show)
 {
  sp->dispose();
//        Toolkit.getDefaultToolkit().removeAWTEventListener(debugListener);
  debugListener = NULL;
  sp->deleteLater();
  sp = NULL;
 }
}

/*static*/ /*protected*/ QWidget* Apps3::splashDebugMsg()
{
  QLabel* pane1Label = new QLabel("Press F8 to disable logixs");
  QFont f = pane1Label->font();
  f.setPointSizeF(9.0);
  pane1Label->setFont(f);
  QWidget* pane1 = new QWidget();
  FlowLayout* pane1Layout = new FlowLayout;
  pane1->setLayout(pane1Layout);
  pane1Layout->addWidget(pane1Label);
  return pane1;
}

/*static*/ /*protected*/ void Apps3::startupDebug() {
    debugFired = true;
    debugmsg = true;

    debugmsg = false;
}

/*private*/ void Apps3::prepareFontLists() {
    // Prepare font lists
#if 0
    new Thread(new Runnable() {
        //@Override
        /*public*/  void run() {
            log->debug("Prepare font lists...");
            FontComboUtil.prepareFontLists();
            log->debug("...Font lists built");
        }
    }).start();
#endif
}
#if 0
/*protected*/ void initMacOSXMenus() {
    jmri.plaf.macosx.Application macApp = jmri.plaf.macosx.Application.getApplication();
    macApp.setAboutHandler(new AboutHandler() {

        //@Override
        /*public*/  void handleAbout(EventObject eo) {
            new AboutDialog(NULL, true).setVisible(true);
        }
    });
    macApp.setPreferencesHandler(new PreferencesHandler() {

        //@Override
        /*public*/  void handlePreferences(EventObject eo) {
            new TabbedPreferencesAction(Bundle.getMessage("MenuItemPreferences")).actionPerformed();
        }
    });
    macApp.setQuitHandler(new QuitHandler() {

        //@Override
        /*public*/  bool handleQuitRequest(EventObject eo) {
            return handleQuit();
        }
    });
}
#endif
/**
 * Configure the {@link jmri.profile.Profile} to use for this application.
 * <p>
 * Overrides super() method so dialogs can be displayed.
 */
//@Override
/*protected*/ void Apps3::configureProfile() {
    QString profileFilename;
    FileUtil::createDirectory(FileUtil::getPreferencesPath());
    // Needs to be declared final as we might need to
    // refer to this on the Swing thread
    File* profileFile;
    profileFilename = getConfigFileName().replace(".xml", ".properties");
    // decide whether name is absolute or relative
    if (!(new File(profileFilename))->isAbsolute()) {
        // must be relative, but we want it to
        // be relative to the preferences directory
        profileFile = new File(FileUtil::getPreferencesPath() + profileFilename);
    } else {
        profileFile = new File(profileFilename);
    }
    ProfileManager::defaultManager()->setConfigFile(profileFile);
    // See if the profile to use has been specified on the command line as
    // a system property jmri.profile as a profile id.
    if (System::getProperties()->containsKey(/*ProfileManager::SYSTEM_PROPERTY*/"org.jmri.profile")) {
        ProfileManager::defaultManager()->setActiveProfile(System::getProperty(/*ProfileManager::SYSTEM_PROPERTY*/"org.jmri.profile"));
    }
    // @see jmri.profile.ProfileManager#migrateToProfiles JavaDoc for conditions handled here
    if (!ProfileManager::defaultManager()->getConfigFile()->exists()) { // no profile config for this app
        try {
            if (ProfileManager::defaultManager()->migrateToProfiles(getConfigFileName())) { // migration or first use
                // notify user of change only if migration occured
                // TODO: a real migration message
//                JOptionPane.showMessageDialog(sp,
//                        Bundle.getMessage("ConfigMigratedToProfile"),
//                        jmri.Application.getApplicationName(),
//                        JOptionPane.INFORMATION_MESSAGE);
             QMessageBox::information(sp, QApplication::applicationName(), tr("Please ensure that the User Files location and Roster location are correct."));
            }
        } catch (IOException ex) {
//            JOptionPane.showMessageDialog(sp,
//                    ex.getLocalizedMessage(),
//                    jmri.Application.getApplicationName(),
//                    JOptionPane.ERROR_MESSAGE);
      //QMessageBox::critical(sp, tr("Error"), tr(""));
            log->error(ex.getMessage()/*, ex*/);
        } catch (IllegalArgumentException ex) {
//            JOptionPane.showMessageDialog(sp,
//                    ex.getLocalizedMessage(),
//                    jmri.Application.getApplicationName(),
//                    JOptionPane.ERROR_MESSAGE);
            log->error(ex.getMessage()/*, ex*/);
        }
    }
    try {
        ProfileManagerDialog::getStartingProfile(sp);
        // Manually setting the configFilename property since calling
        // Apps.setConfigFilename() does not reset the system property
        System::setProperty("org.jmri.Apps.configFilename", /*Profile::CONFIG_FILENAME*/"ProfileConfig.xml");
        log->info(tr("Starting with profile %1").arg( ProfileManager::defaultManager()->getActiveProfile()->getId()));
    } catch (IOException ex) {
        log->info(tr("Profiles not configurable. Using fallback per-application configuration. Error: %1").arg( ex.getMessage()));
    }
}
