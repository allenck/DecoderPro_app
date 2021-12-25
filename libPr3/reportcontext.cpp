#include "reportcontext.h"
#include <QSerialPortInfo>
#include "system.h"
#include <QApplication>
#include "instancemanager.h"
#include "connectionconfig.h"
#include "profile.h"
#include "profilemanager.h"
#include <QSerialPortInfo>
#include "fileutil.h"
#include "jmrijframe.h"
#include "version.h"
#include "roster.h"
#include "loadxmluseraction.h"
#include "file.h"
#include "audiofactory.h"
#include <QScreen>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include "configuremanager.h"
#include "zeroconfservice.h"
#include <QHostInfo>

/**
 * Provide the JMRI context info.
 * <p>
 *
 * @author Bob Jacobsen Copyright (C) 2007, 2009
 * @author Matt Harris Copyright (C) 2008, 2009
 *
 * @version $Revision$
 */
///*public*/ class ReportContext {
/* public*/ ReportContext::ReportContext(QObject *parent)
 : QObject(parent)
{
 report = "";
}

/**
 * Provide a report of the current JMRI context
 *
 * @param reportNetworkInfo true if network connection and zeroconf service
 *                          information to be included
 * @return current JMRI context
 */
/*public*/ QString ReportContext::getReport(bool reportNetworkInfo) {

    addString("JMRI Version: " + Version::name() + "   ");
    addString("JMRI configuration file name: "
            + System::getProperty("org.jmri.apps.Apps.configFilename") + "  (from org.jmri.apps.Apps.configFilename system property)");
    if (JmriJFrame::getFrameList()->at(0) != nullptr) {
        addString("JMRI main window name: "
                + JmriJFrame::getFrameList()->at(0)->getTitle() + "   ");
    }

    addString("JMRI Application: " + QApplication::applicationName() + "   ");
    //ConnectionConfig[] connList = InstanceManager.getDefault(ConnectionConfigManager.class).getConnections();
    QObjectList connList = static_cast<ConfigureManager*>(InstanceManager::getDefault("ConfigureManager"))->getInstanceList("ConnectionConfig");
    if (!connList.isEmpty()) {
        for (int x = 0; x < connList.length(); x++) {
            ConnectionConfig* conn = (ConnectionConfig*)connList.at(x);
            addString("Connection " + QString::number(x) + ": " + conn->getManufacturer() + " connected via " + conn->name() + " on " + conn->getInfo() + " Disabled " + (conn->getDisabled()?"yes":"no") + "   ");
        }
    }

    addString("Available Communication Ports:");
    addCommunicationPortInfo();

    Profile* profile = ProfileManager::getDefault()->getActiveProfile();
    addString("Active profile: " + profile-> getName() + "   ");
    addString("Profile location: " + profile-> getPath()->getPath() + "   ");
    addString("Profile ID: " + profile-> getId() + "   ");

    QString prefs = FileUtil::getUserFilesPath();
    addString("Preferences directory: " + prefs + "   ");

    QString prog = System::getProperty("user.dir");
    addString("Program directory: " + prog + "   ");

    QString roster = Roster::getDefault()->getRosterIndexPath();
    addString("Roster index location: " + roster + "   ");

    File* panel = LoadXmlUserAction::getCurrentFile();
    addString("Current panel file: " + (panel == nullptr ? "[none]" : panel->getPath()) + "   ");

    //String operations = jmri.jmrit.operations.setup.OperationsSetupXml.getFileLocation();
    //addString("Operations files location: "+operations+"  ");
    AudioFactory* af = ((AudioManager*)InstanceManager::getDefault("AudioManager"))->getActiveAudioFactory();
    QString audio = af != nullptr ? af->objectName() : "[not initialised]";
    addString("Audio factory type: " + audio + "   ");

    addProperty("java.version");
    addProperty("java.vendor");
    addProperty("java.home");

    addProperty("java.vm.version");
    addProperty("java.vm.vendor");
    addProperty("java.vm.name");

    addProperty("java.specification.version");
    addProperty("java.specification.vendor");
    addProperty("java.specification.name");

    addProperty("java.class.version");
    addProperty("java.class.path");
    addProperty("java.library.path");

    addProperty("java.compiler");
    addProperty("java.ext.dirs");

    addProperty("file.encoding");

    addProperty("os.name");
    addProperty("os.arch");
    addProperty("os.version");

    addProperty("python.home");
    addProperty("python.path");
    addProperty("python.cachedir");
    addProperty("python.cachedir.skip");
    addProperty("python.startup");

    addProperty("user.name");
    addProperty("user.home");
    addProperty("user.dir");
    addProperty("user.country");
    addProperty("user.language");
    addProperty("user.timezone");
    addProperty("jmri.log.path");

    addScreenSize();

    if (reportNetworkInfo) {
        addNetworkInfo();
    }

    return report;

}

void ReportContext::addString(QString val) {
    report = report + val + "\n";
}

void ReportContext::addProperty(QString prop) {
    addString(prop + ": " + System::getProperty(prop) + "   ");
}

/**
 * Provide screen - size information. This is based on the
 * jmri.util.JmriJFrame calculation, but isn't refactored to there because
 * we also want diagnostic info
 */
/*public*/ void ReportContext::addScreenSize()
{
#if 0
    try {
        // Find screen size. This throws NULL-pointer exceptions on
        // some Java installs, however, for unknown reasons, so be
        // prepared to fall back.
        JFrame dummy = new JFrame();
        try {
            Insets insets = dummy.getToolkit().getScreenInsets(dummy.getGraphicsConfiguration());
            Dimension screen = dummy.getToolkit().getScreenSize();
            addString("Screen size h:" + screen.height + ", w:" + screen.width + " Inset t:" + insets.top + ", b:" + insets.bottom
                    + "; l:" + insets.left + ", r:" + insets.right);
        } catch (NoSuchMethodError ex) {
            Dimension screen = dummy.getToolkit().getScreenSize();
            addString("Screen size h:" + screen.height + ", w:" + screen.width
                    + " (No Inset method available)");
        }
    } catch (HeadlessException ex) {
        // failed, fall back to standard method
        addString("(Cannot sense screen size due to " + ex.toString() + ")");
    }
#endif
 QList<QScreen*> screens = QApplication::screens();
 addString("Screen size h:" + QString::number(screens.at(0)->availableSize().height()) + ", w:" + QString::number(screens.at(0)->availableSize().width()));

#if 0

    try {
        // Find screen resolution. Not expected to fail, but just in case....
        int dpi = Toolkit.getDefaultToolkit().getScreenResolution();
        addString("Screen resolution: " + dpi);
    } catch (HeadlessException ex) {
        addString("Screen resolution not available");
    }
#endif
 addString("Screen resolution: " + QString::number(screens.at(0)->physicalDotsPerInch()));
#if 0
    // look at context
    //Rectangle virtualBounds = new Rectangle();
    try {
        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        addString("Environment max bounds: " + ge.getMaximumWindowBounds());

        try {
            GraphicsDevice[] gs = ge.getScreenDevices();
            for (GraphicsDevice gd : gs) {
                GraphicsConfiguration[] gc = gd.getConfigurations();
                for (int i = 0; i < gc.length; i++) {
                    addString("bounds[" + i + "] = " + gc[i].getBounds());
                    // virtualBounds = virtualBounds.union(gc[i].getBounds());
                }
                addString("Device: " + gd.getIDstring() + " bounds = " + gd.getDefaultConfiguration().getBounds()
                        + " " + gd.getDefaultConfiguration().toString());
            }
        } catch (HeadlessException ex) {
            addString("Exception getting device bounds " + ex->getMessage());
        }
    } catch (HeadlessException ex) {
        addString("Exception getting max window bounds " + ex->getMessage());
    }
    // Return the insets using a custom class
    // which should return the correct values under
    // various Linux window managers
    try {
        Insets jmriInsets = JmriInsets.getInsets();
        addString("JmriInsets t:" + jmriInsets.top + ", b:" + jmriInsets.bottom
                + "; l:" + jmriInsets.left + ", r:" + jmriInsets.right);
    } catch (Throwable ex) {
        addString("Exception getting JmriInsets" + ex->getMessage());
    }
#endif
}

/**
 * Add network connection and running service information
 */
/*private*/ void ReportContext::addNetworkInfo() {
#if 0
    try {
        // This code is based on that in jmri.jmrit.withrottle.UserInterface which,
        // itself, was adapted from http://www.rgagnon.com/javadetails/java-0390.html
        Enumeration<NetworkInterface> networkInterfaces = NetworkInterface.getNetworkInterfaces();
        while (networkInterfaces.hasMoreElements()) {
            NetworkInterface networkInterface = networkInterfaces.nextElement();
            Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses();
            while (inetAddresses.hasMoreElements()) {
                InetAddress inetAddress = inetAddresses.nextElement();
                String hostAddress = inetAddress.getHostAddress();
                if (!hostAddress.equals("0.0.0.0") && !hostAddress.regionMatches(0, "127", 0, 3) && !hostAddress.contains(":")) {
                    addString("Network Interface: " + networkInterface.getName());
                    addString(" Long Name: " + networkInterface.getDisplayName());
                    addString(" Host Name: " + inetAddress.getHostName());
                    addString(" IP address: " + hostAddress);
                }
            }
        }
    } catch (SocketException ex) {
        addString("Unable to enumerate Network Interfaces");
    }
#endif
 QList<QNetworkInterface> networkInterfaces = QNetworkInterface::allInterfaces();
 foreach(QNetworkInterface networkInterface, networkInterfaces)
 {
  QList<QNetworkAddressEntry> inetAddresses = networkInterface.addressEntries();
  foreach(QNetworkAddressEntry inetAddress, inetAddresses)
  {
   QString hostAddress = inetAddress.ip().toString();
   if (hostAddress!=("0.0.0.0") /*&& !hostAddress.regionMatches(0, "127", 0, 3) */&& !hostAddress.contains(":")) {
       addString("Network Interface: " + networkInterface.name());
       addString(" Long Name: " + networkInterface.humanReadableName());
       //addString(" Host Name: " + QHostInfo::lookupHost(hostAddress);
       addString(" IP address: " + hostAddress);
   }

  }
 }
#if 1

    QList<ZeroConfService*> services = ZeroConfService::allServices();
    for (InetAddress* address : ZeroConfService::netServices().keys())
    {
        addString("ZeroConfService host: " + ZeroConfService::hostName(address) + " running " + QString::number(services.size()) + " service(s)");
    }
    if (services.size() > 0) {
        for (ZeroConfService* service : services) {
            addString("ZeroConfService: " + service->serviceInfo()->getQualifiedName() + "  ");
            addString(" Name: " + service->name() + "   ");
            try {
                for (QString address : service->serviceInfo()->getHostAddresses()) {
                    addString(" Address:" + address + "   ");
                }
            } catch (NullPointerException* ex) {
                addString(" Address: [unknown due to NPE]");
            }
            addString(" Port: " + QString::number(service->serviceInfo()->getPort()) + "   ");
            addString(" Server: " + service->serviceInfo()->getServer() + "   ");
            addString(" Type: " + service->type() + "   ");
            try {
                for (QString url : service->serviceInfo()->getURLs()) {
                    addString(" URL: " + url + "   ");
                }
            } catch (NullPointerException* ex) {
                addString(" URL: [unknown due to NPE]");
            }
            addString(tr(" Published: ") + (service->isPublished() ? "yes" : "no"));
        }
    }
#endif
}

/**
 * Add communication port information
 */
/*private*/ void ReportContext::addCommunicationPortInfo() {
#if 0
    //@SuppressWarnings("unchecked")
    Enumeration<CommPortIdentifier> portIDs = CommPortIdentifier.getPortIdentifiers();

    ArrayList<CommPortIdentifier> ports = new ArrayList<CommPortIdentifier>();

    // find the names of suitable ports
    while (portIDs.hasMoreElements()) {
        CommPortIdentifier id = portIDs.nextElement();
        // filter out line printers
        if (id.getPortType() != CommPortIdentifier.PORT_PARALLEL) {
            ports.add(id);
        }
    }
#endif
  QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    addString(tr(" Found %1 serial ports").arg(ports.size()));
#if 0
    // now output the details
    for (CommPortIdentifier id : ports) {
        // output details
        SerialPortFriendlyName port = PortNameMapper.getPortNameMap().get(id.getName());
        if (port == NULL) {
            port = new SerialPortFriendlyName(id.getName(), NULL);
            PortNameMapper.getPortNameMap().put(id.getName(), port);
        }
        addString(" Port: " + port.getDisplayName()
                + (id.isCurrentlyOwned()
                        ? " - in use by: " + id.getCurrentOwner()
                        : " - not in use") + "   ");
    }
#endif
    foreach(QSerialPortInfo port, ports)
    {
     addString(" Port: " + port.portName() + " " + port.description());
    }
}
