#include "reportcontext.h"
#include "system.h"
#include "jmrijframe.h"
#include "instancemanager.h"
#include "version.h"
#include <QApplication>
#include "profile.h"
#include "profilemanager.h"
#include "fileutil.h"
#include "roster.h"
#include "loadxmluseraction.h"
#include "audiofactory.h"
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QDesktopWidget>
#include <QScreen>

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
ReportContext::ReportContext(QObject* parent) : QObject(parent)
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
             + System::getProperty("org.jmri.apps.Apps.configFilename") + "   ");
     if (JmriJFrame::getFrameList()->at(0) != NULL) {
         addString("JMRI main window name: "
                 + JmriJFrame::getFrameList()->at(0)->getTitle() + "   ");
     }

     addString("JMRI Application: " + /*jmri.Application.getApplicationName()*/QApplication::applicationName() + "   ");
#if 0 // TODO:
     ConnectionConfig[] connList = InstanceManager.getDefault(ConnectionConfigManager.class).getConnections();
     if (connList != NULL) {
         for (int x = 0; x < connList.length; x++) {
             ConnectionConfig conn = connList[x];
             addString("Connection " + x + ": " + conn.getManufacturer() + " connected via " + conn.name() + " on " + conn.getInfo() + " Disabled " + conn.getDisabled() + "   ");
         }
     }
#endif
     addString("Available Communication Ports:");
     addCommunicationPortInfo();

     Profile* profile = ProfileManager::defaultManager()->getActiveProfile();
     addString("Active profile: " + profile->getName() + "   ");
     addString("Profile location: " + profile->getPath()->getPath() + "   ");
     addString("Profile ID: " + profile->getId() + "   ");

     QString prefs = FileUtil::getUserFilesPath();
     addString("Preferences directory: " + prefs + "   ");

     QString prog = System::getProperty("user.dir");
     addString("Program directory: " + prog + "   ");

     QString roster = Roster::defaultRosterFilename();
     addString("Roster index location: " + roster + "   ");

     File* panel = LoadXmlUserAction::getCurrentFile();
     addString("Current panel file: " + (panel == NULL ? "[none]" : panel->getPath()) + "   ");

     //String operations = jmri.jmrit.operations.setup.OperationsSetupXml.getFileLocation();
     //addString("Operations files location: "+operations+"  ");
     AudioFactory* af = InstanceManager::audioManagerInstance()->getActiveAudioFactory();
     QString audio = af != NULL ? QString(af->metaObject()->className()) : "[not initialised]";
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
 /*public*/ void ReportContext::addScreenSize() {
//     try {
//         // Find screen size. This throws NULL-pointer exceptions on
//         // some Java installs, however, for unknown reasons, so be
//         // prepared to fall back.
//         JFrame dummy = new JFrame();
//         try {
//             Insets insets = dummy.getToolkit().getScreenInsets(dummy.getGraphicsConfiguration());
//             Dimension screen = dummy.getToolkit().getScreenSize();
//             addString("Screen size h:" + screen.height + ", w:" + screen.width + " Inset t:" + insets.top + ", b:" + insets.bottom
//                     + "; l:" + insets.left + ", r:" + insets.right);
//         } catch (NoSuchMethodError ex) {
//             Dimension screen = dummy.getToolkit().getScreenSize();
//             addString("Screen size h:" + screen.height + ", w:" + screen.width
//                     + " (No Inset method available)");
//         }
//     } catch (HeadlessException ex) {
//         // failed, fall back to standard method
//         addString("(Cannot sense screen size due to " + ex.toString() + ")");
//     }
  QDesktopWidget* desktopWidget = QApplication::desktop();
  QRect screen = desktopWidget->screenGeometry();
  addString(tr("Screen size h:") + QString::number(screen.height()) + ", w:" + QString::number(screen.width()));

     try {
         // Find screen resolution. Not expected to fail, but just in case....
         //int dpi = Toolkit.getDefaultToolkit().getScreenResolution();
   QList<QScreen*> slist = QApplication::screens();
   int dpi = slist.at(0)->physicalDotsPerInch();
         addString("Screen resolution: " + dpi);
     } catch (HeadlessException ex) {
         addString("Screen resolution not available");
     }

//     // look at context
//     //Rectangle virtualBounds = new Rectangle();
//     try {
//         GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
//         addString("Environment max bounds: " + ge.getMaximumWindowBounds());

//         try {
//             GraphicsDevice[] gs = ge.getScreenDevices();
//             for (GraphicsDevice gd : gs) {
//                 GraphicsConfiguration[] gc = gd.getConfigurations();
//                 for (int i = 0; i < gc.length; i++) {
//                     addString("bounds[" + i + "] = " + gc[i].getBounds());
//                     // virtualBounds = virtualBounds.union(gc[i].getBounds());
//                 }
//                 addString("Device: " + gd.getIDstring() + " bounds = " + gd.getDefaultConfiguration().getBounds()
//                         + " " + gd.getDefaultConfiguration().toString());
//             }
//         } catch (HeadlessException ex) {
//             addString("Exception getting device bounds " + ex.getMessage());
//         }
//     } catch (HeadlessException ex) {
//         addString("Exception getting max window bounds " + ex.getMessage());
//     }

#if 0
     // Return the insets using a custom class
     // which should return the correct values under
     // various Linux window managers
     try {
         Insets jmriInsets = JmriInsets.getInsets();
         addString("JmriInsets t:" + jmriInsets.top + ", b:" + jmriInsets.bottom
                 + "; l:" + jmriInsets.left + ", r:" + jmriInsets.right);
     } catch (Throwable ex) {
         addString("Exception getting JmriInsets" + ex.getMessage());
     }
#endif
 }

 /**
  * Add network connection and running service information
  */
 /*private*/ void ReportContext::addNetworkInfo()
 {
     //try {
         // This code is based on that in jmri.jmrit.withrottle.UserInterface which,
         // itself, was adapted from http://www.rgagnon.com/javadetails/java-0390.html
         //Enumeration<NetworkInterface> networkInterfaces = NetworkInterface.getNetworkInterfaces();
   QNetworkInterface* nif = new QNetworkInterface;
   QListIterator<QNetworkAddressEntry> networkInterfaces(nif->addressEntries());
         while (networkInterfaces.hasNext())
         {
             QNetworkAddressEntry networkInterface = networkInterfaces.next();
//             Enumeration<InetAddress> inetAddresses = networkInterface.getInetAddresses();
//             while (inetAddresses.hasMoreElements()) {
//                 InetAddress inetAddress = inetAddresses.nextElement();
//                 QString hostAddress = inetAddress.getHostAddress();
             QHostAddress hostAddress = networkInterface.ip();
//                 if (!hostAddress.equals("0.0.0.0") && !hostAddress.regionMatches(0, "127", 0, 3) && !hostAddress.contains(":")) {
                     addString("Network Interface: " + nif->humanReadableName());
                     addString(" Long Name: " + nif->name());
                     //addString(" Host Name: " + inetAddress.getHostName());
                     addString(" IP address: " + hostAddress.toString());
//                 }
//             }
         }
//     } catch (SocketException ex) {
//         addString("Unable to enumerate Network Interfaces");
//     }
#if 0
     Collection<ZeroConfService> services = ZeroConfService.allServices();
     for (InetAddress address : ZeroConfService.netServices().keySet()) {
         addString("ZeroConfService host: " + ZeroConfService.hostName(address) + " running " + services.size() + " service(s)");
     }
     if (services.size() > 0) {
         for (ZeroConfService service : services) {
             addString("ZeroConfService: " + service.serviceInfo().getQualifiedName() + "  ");
             addString(" Name: " + service.name() + "   ");
             try {
                 for (String address : service.serviceInfo().getHostAddresses()) {
                     addString(" Address:" + address + "   ");
                 }
             } catch (NullPointerException ex) {
                 addString(" Address: [unknown due to NPE]");
             }
             addString(" Port: " + service.serviceInfo().getPort() + "   ");
             addString(" Server: " + service.serviceInfo().getServer() + "   ");
             addString(" Type: " + service.type() + "   ");
             try {
                 for (String url : service.serviceInfo().getURLs()) {
                     addString(" URL: " + url + "   ");
                 }
             } catch (NullPointerException ex) {
                 addString(" URL: [unknown due to NPE]");
             }
             addString(" Published: " + (service.isPublished() ? "yes" : "no"));
         }
     }
#endif
 }

 /**
  * Add communication port information
  */
 /*private*/ void ReportContext::addCommunicationPortInfo()
 {
#if 0 // TODO:
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

     addString(String.format(" Found %s serial ports", ports.size()));

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
 }

