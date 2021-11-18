#include "appslaunchpane.h"
#include "application.h"
#include "createbuttonmodel.h"
#include <QBoxLayout>
#include "instancemanager.h"
#include "flowlayout.h"
#include <QLabel>
#include "connectionconfig.h"
#include "jmrixconfigpane.h"
#include "connectionstatus.h"
#include "fileutil.h"
#include "apps.h"
#include "resourcebundle.h"
#include "system.h"
#include "namedicon.h"
#include "jlabel.h"
#include "configuremanager.h"

//AppsLaunchPane::AppsLaunchPane(QWidget *parent) :
//  QWidget(parent)
//{
//}
/**
 * Base class for pane filling main frame (window) of traditional-style JMRI
 * applications
 * <P>
 * This is for launching after the system is initialized, so it does none of
 * that.
 *
 * @author	Bob Jacobsen Copyright 2003, 2007, 2008, 2010, 2014
 * @author Dennis Miller Copyright 2005
 * @author Giorgio Terdina Copyright 2008
 * @author Matthew Harris Copyright (C) 2011
 * @version $Revision: 29306 $
 */
// /*public*/ abstract class AppsLaunchPane extends JPanel implements PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = 4491168291678104991L;
/*static*/ QString AppsLaunchPane::profileFilename = "";

/*public*/ AppsLaunchPane::AppsLaunchPane(QWidget *parent) :
  QWidget(parent) {

 //super(true);
 log = new Logger("AppsLaunchPane");
 cs4 = new QLabel();
 // line 5 optional
 cs5 = new QLabel();
 // line 6 optional
 cs6 = new QLabel();
 connection =  QList<ConnectionConfig*>() << NULL << NULL << NULL<< NULL;



 setButtonSpace();
 setJynstrumentSpace();

 Application::setLogo(logo());
 Application::setURL(line2());

 // Add actions to abstractActionModel
 // Done here as initial non-GUI initialisation is completed
 // and UI L&F has been set
 addToActionModel();

 // populate GUI
 log->debug("Start UI");
 QVBoxLayout* thisLayout;
 setLayout(thisLayout =new QVBoxLayout); //(this, BoxLayout.Y_AXIS));

 thisLayout->addWidget(statusPanel());
 log->debug("Done with statusPanel, start buttonSpace");
 thisLayout->addWidget(buttonSpace());
 thisLayout->addWidget(_jynstrumentSpace);

}

/**
 * @deprecated since 4.5.1
 */
//@Deprecated
/*protected*/ /*final*/ void AppsLaunchPane::addToActionModel() {
    // StartupActionModelUtil populates itself, so do nothing
}

QWidget* AppsLaunchPane::_buttonSpace = NULL;
/**
 * Prepare the JPanel to contain buttons in the startup GUI. Since it's
 * possible to add buttons via the preferences, this space may have
 * additional buttons appended to it later. The default implementation here
 * just creates an empty space for these to be added to.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "only one application at a time")
/*protected*/ void AppsLaunchPane::setButtonSpace() {
    _buttonSpace = new QWidget();
    FlowLayout* buttonSpaceLayout;
    _buttonSpace->setLayout(buttonSpaceLayout = new FlowLayout());
}
/*static*/ QWidget* AppsLaunchPane::_jynstrumentSpace = NULL;

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD",
//        justification = "only one application at a time")
/*protected*/ void AppsLaunchPane::setJynstrumentSpace()
{
    _jynstrumentSpace = new QWidget();
    _jynstrumentSpace->setLayout(new FlowLayout());
#if 0
    new FileDrop(_jynstrumentSpace, new Listener() {
        @Override
        /*public*/ void filesDropped(File[] files) {
            for (int i = 0; i < files.length; i++) {
                ynstrument(files[i].getPath());
            }
        }
    });
#endif
}

/*public*/ /*static*/ void AppsLaunchPane::ynstrument(QString /*path*/) {
#if 0
    Jynstrument it = JynstrumentFactory.createInstrument(path, _jynstrumentSpace);
    if (it == NULL) {
        log->error("Error while creating Jynstrument {}", path);
        return;
    }
    jmri.jmrit.throttle.ThrottleFrame.setTransparent(it);
    it.setVisible(true);
    _jynstrumentSpace.setVisible(true);
    _jynstrumentSpace.add(it);
#endif
}

/*protected*/ QString AppsLaunchPane::line1() {
    //return Bundle.getMessage("DefaultVersionCredit", jmri.Version.name());
 return (tr("Qt versiom %1").arg(QT_VERSION_STR));
}

/*protected*/ QString AppsLaunchPane::line2() {
    return "http://jmri.org/";
}

/*protected*/ QString AppsLaunchPane::line3() {
    return " ";
}

/*protected*/ void AppsLaunchPane::buildLine4(QWidget* pane) {
    if (connection[0] != NULL) {
        buildLine(connection[0], cs4, pane);
    }
}

/*protected*/ void AppsLaunchPane::buildLine5(QWidget* pane) {
    if (connection[1] != NULL) {
        buildLine(connection[1], cs5, pane);
    }
}

/*protected*/ void AppsLaunchPane::buildLine6(QWidget* pane) {
    if (connection[2] != NULL) {
        buildLine(connection[2], cs6, pane);
    }
}

/*protected*/ void AppsLaunchPane::buildLine7(QWidget* pane) {
    if (connection[3] != NULL) {
        buildLine(connection[3], cs7, pane);
    }
}

/*protected*/ void AppsLaunchPane::buildLine(ConnectionConfig* conn, QLabel* cs, QWidget* pane) {
    if (conn->name()==(JmrixConfigPane::NONE)) {
        cs->setText(" ");
        return;
    }
    ConnectionStatus::instance()->addConnection(conn->name(), conn->getInfo());
    cs->setFont(pane->font());
    updateLine(conn, cs);
    pane->layout()->addWidget(cs);
}

/*protected*/ void AppsLaunchPane::updateLine(ConnectionConfig* conn, QLabel* cs)
{
 if (conn->getDisabled()) {
     return;
 }
 QString name = conn->getConnectionName();
 if (name == NULL) {
     name = conn->getManufacturer();
 }
 if (ConnectionStatus::instance()->isConnectionOk(nullptr, conn->getInfo()))
 {
  //cs.setForeground(Color.black);
  cs->setStyleSheet("QLabel { color: black};");
  QString cf = tr("%1: using %2 on %3").arg(name).arg(conn->name()).arg( conn->getInfo());
  cs->setText(cf);
 } else {
     //cs.setForeground(Color.red);
  cs->setStyleSheet("QLabel { color: red};");
  QString cf = tr("ConnectionFailed = %1: ERROR %2 using %3").arg(name).arg(conn->name()).arg( conn->getInfo());
  cf = cf.toUpper();
  cs->setText(cf);
 }

    //this.revalidate();
}

/*protected*/ QString AppsLaunchPane::line8() {
    return " ";
}

/*protected*/ QString AppsLaunchPane::line9() {
//    return Bundle.getMessage("JavaVersionCredit",
//            System.getProperty("java.version", "<unknown>"),
//            Locale.getDefault().toString());
 return tr("Qt version %1").arg(QT_VERSION_STR);
}

/*protected*/ QString AppsLaunchPane::logo() {
    return "resources/logo.gif";
}

/**
 * Fill in the logo and status panel
 *
 * @return Properly-filled out JPanel
 */
/*protected*/ QWidget* AppsLaunchPane::statusPanel() {
    QWidget* pane1 = new QWidget();
    QVBoxLayout* pane1Layout;
    pane1->setLayout(pane1Layout = new QVBoxLayout); //(pane1, BoxLayout.X_AXIS));
    log->debug(tr("Fetch main logo: %1").arg(logo()));
    //pane1Layout->addWidget(new QLabel(new ImageIcon(getToolkit().getImage(FileUtil.findURL(logo(), FileUtil::Location::INSTALLED)), "JMRI logo"), QLabel.LEFT));
    pane1Layout->addWidget(new JLabel("JMRI logo", new NamedIcon(logo(), "JMRI logo"),JLabel::LEFT),0, Qt::AlignCenter);
//    pane1Layout->addWidget(Box.createRigidArea(new Dimension(15, 0))); // Some spacing between logo and status panel

    log->debug("start labels");
    QWidget* pane2 = new QWidget();
    QVBoxLayout* pane2Layout;
    pane2->setLayout(pane2Layout = new QVBoxLayout); //(pane2, BoxLayout.Y_AXIS));
    pane2Layout->addWidget(new QLabel(line1()));
    pane2Layout->addWidget(new QLabel(line2()));
    pane2Layout->addWidget(new QLabel(line3()));

    // add listerner for Com port updates
    //ConnectionStatus::instance().addPropertyChangeListener(this);
    connect(ConnectionStatus::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    //ArrayList<Object> connList = InstanceManager::configureManagerInstance().getInstanceList(ConnectionConfig.class);
    QObjectList connList = ((ConfigureManager*)InstanceManager::getDefault("ConfigureManager"))->getInstanceList("ConnectionConfig");
    int i = 0;
    if (!connList.isEmpty()) {
        for (int x = 0; x < connList.size(); x++) {
            ConnectionConfig* conn = (ConnectionConfig*) connList.at(x);
            if (!conn->getDisabled()) {
                connection[i] = conn;
                i++;
            }
            if (i > 3) {
                break;
            }
        }
    }
    buildLine4(pane2);
    buildLine5(pane2);
    buildLine6(pane2);
    buildLine7(pane2);

    pane2Layout->addWidget(new QLabel(line8()));
    pane2Layout->addWidget(new QLabel(line9()));
    pane1Layout->addWidget(pane2);
    return pane1;
}
//int[] connection = {-1,-1,-1,-1};

/*static*/ /*protected*/ void AppsLaunchPane::setJmriSystemProperty(QString key, QString value)
{
 Logger* log = new Logger("AppsLaunchPane");
    try {
        QString current = System::getProperty("org.jmri.Apps." + key);
        if (current == NULL) {
            System::setProperty("org.jmri.Apps." + key, value);
        } else if (current!=(value)) {
         log->warn(tr("JMRI property %1 already set to %2, skipping reset to %3").arg(key).arg(current).arg(value));
        }
    } catch (Exception e) {
  log->error(tr("Unable to set JMRI property %1 to %2 due to exception %3").arg(key).arg(value).arg(e.getMessage()));
    }
}

/**
 * Provide access to a place where applications can expect the configuration
 * code to build run-time buttons.
 *
 * @see apps.CreateButtonPanel
 * @return NULL if no such space exists
 */
/*static*/ /*public*/ QWidget*AppsLaunchPane::buttonSpace() {
    return _buttonSpace;
}
#if 0
/**
 * @deprecated as of 2.13.3, directly access the connection configuration
 * from the instance list
 * jmri.InstanceManager.configureManagerInstance().getInstanceList(jmri.jmrix.ConnectionConfig.class)
 */
//@Deprecated
/*static*/ /*public*/ QString AppsLaunchPane::getConnection1() {
    return MessageFormat.format(Bundle.getMessage("ConnectionCredit"),
            new Object[]{AppConfigBase.getConnection(0), AppConfigBase.getPort(0), AppConfigBase.getManufacturerName(0)});
}

/**
 * @deprecated as of 2.13.3, directly access the connection configuration
 * from the instance list
 * jmri.InstanceManager.configureManagerInstance().getInstanceList(jmri.jmrix.ConnectionConfig.class)
 */
//@Deprecated
static /*public*/ QString AppsLaunchPane::getConnection2() {
    return MessageFormat.format(Bundle.getMessage("ConnectionCredit"),
            new Object[]{AppConfigBase.getConnection(1), AppConfigBase.getPort(1), AppConfigBase.getManufacturerName(1)});
}

/**
 * @deprecated as of 2.13.3, directly access the connection configuration
 * from the instance list
 * jmri.InstanceManager.configureManagerInstance().getInstanceList(jmri.jmrix.ConnectionConfig.class)
 */
//@Deprecated
static /*public*/ QString AppsLaunchPane::getConnection3() {
    return MessageFormat.format(Bundle.getMessage("ConnectionCredit"),
            new Object[]{AppConfigBase.getConnection(2), AppConfigBase.getPort(2), AppConfigBase.getManufacturerName(2)});
}

/**
 * @deprecated as of 2.13.3, directly access the connection configuration
 * from the instance list
 * jmri.InstanceManager.configureManagerInstance().getInstanceList(jmri.jmrix.ConnectionConfig.class)
 */
//@Deprecated
static /*public*/ QString AppsLaunchPane::getConnection4() {
    return MessageFormat.format(Bundle.getMessage("ConnectionCredit"),
            new Object[]{AppConfigBase.getConnection(3), AppConfigBase.getPort(3), AppConfigBase.getManufacturerName(3)});
}
#endif
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
 * @param def  Default value if no other is provided
 * @param args Argument array from the main routine
 */
/*static*/ /*protected*/ void AppsLaunchPane::setConfigFilename(QString def, QStringList args)
{
 Logger log = Logger("Apps");
 // save the configuration filename if present on the command line
#if 1 // TODO:
 if (args.length() >= 1 && args[0] != NULL && !args[0].contains("=")) {
     def = args[0];
     log.debug("Config file was specified as: "+ args[0]);
 }
 foreach (QString arg, args) {
     QStringList split = arg.split("="/*, 2*/);
     if (QString::compare(split[0], "config",Qt::CaseInsensitive))
     {
         def = split[1];
         log.debug("Config file was specified as:" + arg);
     }
 }
#endif
 Apps::configFilename = def;
 setJmriSystemProperty("configFilename", def);
}

/*static*/ /*public*/ QString AppsLaunchPane::getConfigFileName() {
    Logger::error("getConfigFileName() called, shouldn't have been")/*, new Exception("bad call traceback"*/;
    return NULL;
    // was hopefully set by setJmriSystemProperty("configFilename", def) earlier, recover
}

//@Override
/*public*/ void AppsLaunchPane::propertyChange(PropertyChangeEvent* /*ev*/) {
    if (log->isDebugEnabled()) {
        log->debug("property change: comm port status update");
    }
    if (connection[0] != NULL) {
        updateLine(connection[0], cs4);
    }

    if (connection[1] != NULL) {
        updateLine(connection[1], cs5);
    }

    if (connection[2] != NULL) {
        updateLine(connection[2], cs6);
    }

    if (connection[3] != NULL) {
        updateLine(connection[3], cs7);
    }

}

/**
 * Returns the ID for the window's help, which is application specific
 */
/*protected*/ /*abstract*/ QString AppsLaunchPane::windowHelpID() { return "";}
