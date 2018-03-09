#include "appslaunchframe.h"
#include "jframeinterface.h"
#include <QMenu>
#include <QMenuBar>
#include "action.h"
#include "abstractaction.h"
#include "tabbedpreferencesaction.h"
#include "toolsmenu.h"
#include "rostermenu.h"
#include "panelmenu.h"
#include "helputil.h"
#include <QBoxLayout>
#include "jmripanel.h"
#include <QDesktopWidget>
#include "windowmenu.h"
#include "activesystemsmenu.h"
#include "appslaunchpane.h"
#include <QApplication>
#include "withrottlecreationaction.h"
#include "operationsmenu.h"
#include "debugmenu.h"
#include "webserveraction.h"
#include "windowinterface.h"

//AppsLaunchFrame::AppsLaunchFrame(QWidget *parent) :
//  JmriJFrame(parent)
//{
//}
/**
 * Base class for main frame (window) of traditional-style JMRI applications
 * <P>
 * This is for launching after the system is initialized, so it does none of
 * that.
 *
 * @author	Bob Jacobsen Copyright 2003, 2007, 2008, 2010, 2014
 * @author Dennis Miller Copyright 2005
 * @author Giorgio Terdina Copyright 2008
 * @author Matthew Harris Copyright (C) 2011
 * @version $Revision: 29305 $
 */
///*public*/ class AppsLaunchFrame extends jmri.util.JmriJFrame {

/**
 *
 */
///*private*/ static final long serialVersionUID = 8986597544309635883L;
/*static*/ QString profileFilename = "";

/*public*/ AppsLaunchFrame::AppsLaunchFrame(AppsLaunchPane* containedPane, QString name, QWidget* parent) : JmriJFrame(name, parent) {
    //super(name);
 log = new Logger("AppsLaunchFrame");

    // Create a WindowInterface object based on this frame (maybe pass it in?)
    JFrameInterface* wi = NULL; //new JFrameInterface((QWidget*)this);
    QWidget* centralWidget = new QWidget;
    QVBoxLayout* centralWidgetLayout = new QVBoxLayout;
    setCentralWidget(centralWidget);
    QVBoxLayout* thisLayout = new QVBoxLayout;
    //setLayout(thisLayout);
    centralWidgetLayout->addLayout(thisLayout);

    // Create a menu bar
    menuBar = new QMenuBar();

    // Create menu categories and add to the menu bar, add actions to menus
    createMenus(menuBar, wi, containedPane);

    setMenuBar(menuBar);
    thisLayout->addWidget(containedPane);

    // handle window close
//    setDefaultCloseOperation(JmriJFrame::HIDE_ON_CLOSE);

    // pack and center this frame
    adjustSize();
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QSize screen = /*getToolkit().getScreenSize(); */desktopWidget->screen()->size();
    QSize size = this->size();
    move((screen.width() - size.width()) / 2, (screen.height() - size.height()) / 2);

}

/**
 * Create default menubar.
 * <P>
 * This does not include the development menu.
 *
 * @param menuBar
 * @param wi
 */
/*protected*/ void AppsLaunchFrame::createMenus(QMenuBar* menuBar, WindowInterface* wi, AppsLaunchPane* pane) {
    // the debugging statements in the following are
    // for testing startup time
    log->debug("start building menus");

    fileMenu(menuBar, wi);
    editMenu(menuBar, wi);
    toolsMenu(menuBar, wi);
    rosterMenu(menuBar, wi);
    panelMenu(menuBar, wi);
    // check to see if operations in main menu
//    if (Setup.isMainMenuEnabled()) {
//        operationsMenu(menuBar, wi);
//    }
    systemsMenu(menuBar, wi);
    scriptMenu(menuBar, wi);
    debugMenu(menuBar, wi, pane);
    menuBar->addMenu(new WindowMenu(wi)); // * GT 28-AUG-2008 Added window menu
    helpMenu(menuBar, wi, pane);
    log->debug("end building menus");
}

/*protected*/ void AppsLaunchFrame::fileMenu(QMenuBar* menuBar, WindowInterface* /*wi*/) {
    QMenu* fileMenu = new QMenu(tr("MenuFile"));
    menuBar->addMenu(fileMenu);

//    fileMenu->addMenu(new PrintDecoderListAction(tr("MenuPrintDecoderDefinitions"), wi->getFrame(), false));
//    fileMenu->addMenu(new PrintDecoderListAction(tr("MenuPrintPreviewDecoderDefinitions"), wi->getFrame(), true));

}

/**
 * Set the location of the window-specific help for the preferences pane.
 * Made a separate method so if can be overridden for application specific
 * preferences help
 */
/*protected*/ void AppsLaunchFrame::setPrefsFrameHelp(JmriJFrame */*f*/, QString /*l*/) {
//    f->addHelpMenu(l, true);
}


/*protected*/ void AppsLaunchFrame::editMenu(QMenuBar* menuBar, WindowInterface* /*wi*/) {

    QMenu* editMenu = new QMenu(tr("Edit"));
    menuBar->addMenu(editMenu);
#if 0
    // cut, copy, paste
    AbstractAction* a;
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
    prefsAction = new TabbedPreferencesAction(tr("Preferences"),this);
    // Put prefs in Apple's prefered area on Mac OS X
//    if (SystemType.isMacOSX()) {
//        Application.getApplication().setPreferencesHandler(new PreferencesHandler() {
//            //@Override
//            /*public*/ void handlePreferences(EventObject eo) {
//                prefsAction.actionPerformed(null);
//            }
//        });
//    }
    // Include prefs in Edit menu if not on Mac OS X or not using Aqua Look and Feel
    //if (!SystemType.isMacOSX() || !UIManager.getLookAndFeel().isNativeLookAndFeel()) {
        editMenu->addSeparator();
        editMenu->addAction(prefsAction);
    //}

}

/*protected*/ void AppsLaunchFrame::toolsMenu(QMenuBar* menuBar, WindowInterface* /*wi*/) {
    menuBar->addMenu(new ToolsMenu(tr("MenuTools"),this));
}

/*protected*/ void AppsLaunchFrame::operationsMenu(QMenuBar* menuBar, WindowInterface* /*wi*/) {
 menuBar->addMenu(new OperationsMenu());
}

/*protected*/ void AppsLaunchFrame::rosterMenu(QMenuBar* menuBar, WindowInterface* /*wi*/) {
    menuBar->addMenu(new RosterMenu(tr("Roster"), RosterMenu::MAINMENU, this));
}

/*protected*/ void AppsLaunchFrame::panelMenu(QMenuBar* menuBar, WindowInterface* /*wi*/) {
    menuBar->addMenu(PanelMenu::instance());
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
/*protected*/ void AppsLaunchFrame::systemsMenu(QMenuBar* menuBar, WindowInterface* wi) {
    ActiveSystemsMenu::addItems(menuBar, wi->getFrame());
}

/*protected*/ void AppsLaunchFrame::debugMenu(QMenuBar* menuBar, WindowInterface* /*wi*/, AppsLaunchPane* pane)
{

    QMenu* d = new DebugMenu(pane);
#if 0
    // also add some tentative items from jmrix
    d.add(new JSeparator());
    d.add(new jmri.jmrix.pricom.PricomMenu());
    d.add(new JSeparator());

    d.add(new jmri.jmrix.jinput.treecontrol.TreeAction());
    d.add(new jmri.jmrix.libusb.UsbViewAction());

    d.add(new JSeparator());
    try {
        d.add(new RunJythonScript("RailDriver Throttle", new File(FileUtil.findURL("jython/RailDriver.py").toURI())));
    } catch (URISyntaxException | NullPointerException ex) {
        log->error("Unable to load RailDriver Throttle", ex);
        QMenuItem i = new QMenuItem("RailDriver Throttle");
        i.setEnabled(false);
        d.add(i);
    }
#endif
    // also add some tentative items from webserver
    d->addSeparator();
    d->addAction(new WebServerAction(this));

    d->addSeparator();
    d->addAction(new WiThrottleCreationAction(this));
    menuBar->addMenu(d);
}

/*protected*/ void AppsLaunchFrame::scriptMenu(QMenuBar* /*menuBar*/, WindowInterface* /*wi*/) {
    // temporarily remove Scripts menu; note that "Run Script"
    // has been added to the Panels menu
    // QMenu menu = new QMenu("Scripts");
    // menuBar.add(menu);
    // menu.add(new jmri.jmrit.automat.JythonAutomatonAction("Jython script", this));
    // menu.add(new jmri.jmrit.automat.JythonSigletAction("Jython siglet", this));
}

/*protected*/ void developmentMenu(QMenuBar* menuBar, WindowInterface* wi) {

    QMenu* devMenu = new QMenu("Development");
    menuBar->addMenu(devMenu);
#if 0
    devMenu.add(new jmri.jmrit.symbolicprog.autospeed.AutoSpeedAction("Auto-speed tool"));
    devMenu.add(new JSeparator());
    devMenu.add(new jmri.jmrit.automat.SampleAutomatonAction("Sample automaton 1"));
    devMenu.add(new jmri.jmrit.automat.SampleAutomaton2Action("Sample automaton 2"));
    devMenu.add(new jmri.jmrit.automat.SampleAutomaton3Action("Sample automaton 3"));
    //devMenu.add(new JSeparator());
    //devMenu.add(new jmri.jmrix.serialsensor.SerialSensorAction("Serial port sensors"));
#endif
}

/*protected*/ void AppsLaunchFrame::helpMenu(QMenuBar* menuBar, WindowInterface* wi, AppsLaunchPane* containedPane) {
    try {

        // create menu and standard items
        QMenu* helpMenu = HelpUtil::makeHelpMenu(containedPane->windowHelpID(), true, wi);

        // tell help to use default browser for external types
        //SwingHelpUtilities.setContentViewerUI("jmri.util.ExternalLinkContentViewerUI");

        // use as main help menu
        menuBar->addMenu(helpMenu);

    } catch (Throwable e3) {
        log->error("Unexpected error creating help.", e3.getMessage());
    }

}

/**
 * Provide access to a place where applications can expect the configuration
 * code to build run-time buttons.
 *
 * @see apps.CreateButtonPanel
 * @return null if no such space exists
 */
/*static*/ /*public*/ QWidget* AppsLaunchFrame::buttonSpace() {
    return _buttonSpace;
}
/*static*/ QWidget* AppsLaunchFrame::_buttonSpace = NULL;

