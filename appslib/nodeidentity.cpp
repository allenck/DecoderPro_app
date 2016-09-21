#include "nodeidentity.h"
#include "logger.h"
#include "file.h"
#include "fileutil.h"
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include "profilemanager.h"
#include "profile.h"
#include <QtXml>
#include <QTextStream>

/**
 * Provide a unique network identity for JMRI. If a stored identity does not
 * exist, the identity is created by taking the MAC address of the first
 * {@link java.net.InetAddress} and prepending it with "jmri-". and removing all
 * colons from the address.
 *
 * If a stored identity is found, the identity is replaced if none of the
 * InetAddresses for the host match the MAC address in the identity and
 * regenerated.
 *
 * A list of former identities is retained to aid in migrating from the former
 * identity to the new identity.
 *
 * If the MAC address of the localhost cannot be read, fall back on using the
 * hostname or IP address. If no local IP address is available, fall back on
 * using the railroad name.
 *
 * @author Randall Wood (C) 2013, 2014, 2016
 */
///*public*/ class NodeIdentity {

/*private*/ /*static*/ NodeIdentity* NodeIdentity::instance = NULL;

/*private*/ /*final*/ /*static*/ QString NodeIdentity::ROOT_ELEMENT = "nodeIdentityConfig"; // NOI18N
/*private*/ /*final*/ /*static*/ QString NodeIdentity::NODE_IDENTITY = "nodeIdentity"; // NOI18N
/*private*/ /*final*/ /*static*/ QString NodeIdentity::FORMER_IDENTITIES = "formerIdentities"; // NOI18N

/*private*/ NodeIdentity::NodeIdentity(QObject* parent) : QObject(parent)
{
 _formerIdentities = QStringList();
 log = new Logger("NodeIdentity");
 init(); // init as a method so the init can be synchronized.
}

/*synchronized*/ /*private*/ void NodeIdentity::init() {
    File* identityFile = this->identityFile();
    if (identityFile->exists())
    {
#if 0
        try {
            Document doc = (new SAXBuilder()).build(identityFile);
            String id = doc.getRootElement().getChild(NODE_IDENTITY).getAttributeValue(NODE_IDENTITY);
            this->formerIdentities.clear();
            doc.getRootElement().getChild(FORMER_IDENTITIES).getChildren().stream().forEach((e) -> {
                this->formerIdentities.add(e.getAttributeValue(NODE_IDENTITY));
            });
            if (!this->validateIdentity(id)) {
                log->debug("Node identity {} is invalid. Generating new node identity.", id);
                this->formerIdentities.add(id);
                this->getIdentity(true);
            } else {
                this->getIdentity(true);
            }
        } catch (JDOMException | IOException ex) {
            log->error("Unable to read node identities: {}", ex.getLocalizedMessage());
            this->getIdentity(true);
        }
#endif
    } else {
        this->getIdentity(true);
    }
}

/**
 * Return the node's current identity.
 *
 * @return An identity. If this identity is not in the form
 * <i>jmri-MACADDRESS-profileId</i>, this identity should be considered
 * unreliable and subject to change across JMRI restarts.
 */
/*synchronized*/ /*public*/ /*static*/ QString NodeIdentity::identity()
{
 Logger* log = new Logger("NodeIdentity");
    QString uniqueId = "-";
    try {
        uniqueId += ProfileManager::getDefault()->getActiveProfile()->getUniqueId();
    } catch (NullPointerException ex) {
        uniqueId += ProfileManager::createUniqueId();
    }
    if (instance == NULL) {
        instance = new NodeIdentity();
        log->info(tr("Using %1 as the JMRI Node identity").arg(instance->getIdentity() + uniqueId));
    }
    return instance->getIdentity() + uniqueId;
}

/**
 * If network hardware on a node was replaced, the identity will change.
 *
 * @return A list of other identities this node may have had in the past.
 */
/*synchronized*/ /*public*/ /*static*/ QStringList NodeIdentity::formerIdentities()
{
 Logger* log = new Logger("NodeIdentity");
 if (instance == NULL)
 {
  instance = new NodeIdentity();
  log->info(tr("Using %1 as the JMRI Node identity").arg(instance->getIdentity()));
 }
 return instance->getFormerIdentities();
}

/**
 * Verify that the current identity is a valid identity for this hardware.
 *
 * @return true if the identity is based on this hardware.
 */
/*synchronized*/ /*private*/ bool NodeIdentity::validateIdentity(QString identity)
{
    //try {
        //Enumeration<NetworkInterface> enumeration = NetworkInterface.getNetworkInterfaces();
 QListIterator<QNetworkInterface> enumeration(QNetworkInterface::allInterfaces());
 while (enumeration.hasNext())
 {
  QNetworkInterface nic = enumeration.next();
  if (/*!nic.isVirtual() && !nic.isLoopback()*/(!nic.flags() ^ QNetworkInterface::IsLoopBack))
  {
//   QString nicIdentity = this->createIdentity(nic.getHardwareAddress());
//   if (nicIdentity != NULL && nicIdentity.equals(identity)) {
//       return true;
//   }
   QString mac = nic.hardwareAddress();
   return true;
  }
 }
//    } catch (SocketException ex) {
//        log->error("Error accessing interface: {}", ex.getLocalizedMessage(), ex);
//    }
 return false;
}

/**
 * Get a node identity from the current hardware.
 *
 */
/*synchronized*/ /*private*/ void NodeIdentity::getIdentity(bool save)
{
 QList<QHostAddress> list = QNetworkInterface::allAddresses();
 QHostAddress addr;
 for(int nIter=0; nIter<list.count(); nIter++)
 {
  if(!list[nIter].isLoopback())
      if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
    qDebug() << list[nIter].toString();
   addr = list[nIter];
   break;
 }

 QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
 foreach(QNetworkInterface interface, interfaces)
 {
  QList<QHostAddress> list = interface.allAddresses();
  foreach (QHostAddress addr1, list)
  {
   if(addr == addr1)
   {
    this->_identity = createIdentity(interface.hardwareAddress());
    break;
  }
   this->_identity = "";
 }
//    try {
//        try {
//            try {
//                this->_identity = this->createIdentity(NetworkInterface.getByInetAddress(InetAddress.getLocalHost()).getHardwareAddress());
//            } catch (NullPointerException ex) {
//                // NetworkInterface.getByInetAddress(InetAddress.getLocalHost()).getHardwareAddress() failed
//                // this can be due to multiple reasons, most likely getLocalHost() failing on certain platforms.
//                // Only set this->identity = NULL, since the following NULL checks address all potential problems
//                // with getLocalHost() including some expected conditions (such as InetAddress.getLocalHost()
//                // returning the loopback interface).
//                this->identity = NULL;
//            }
//            if (this->identity == NULL) {
//                Enumeration<NetworkInterface> nics = NetworkInterface.getNetworkInterfaces();
//                while (nics.hasMoreElements()) {
//                    NetworkInterface nic = nics.nextElement();
//                    if (!nic.isLoopback() && !nic.isVirtual()) {
//                        this->identity = this->createIdentity(nic.getHardwareAddress());
//                        if (this->identity != NULL) {
//                            break;
//                        }
//                    }
//                }
//            }
//            if (this->identity == NULL) {
//                try {
//                    this->identity = InetAddress.getLocalHost().getHostName();
//                } catch (UnknownHostException ex1) {
//                    this->identity = InetAddress.getLocalHost().getHostAddress();
//                }
//            }
//        } catch (SocketException ex) {
//            try {
//                this->identity = InetAddress.getLocalHost().getHostName();
//            } catch (UnknownHostException ex1) {
//                this->identity = InetAddress.getLocalHost().getHostAddress();
//            }
//        }
//    } catch (UnknownHostException ex) {
//        this->identity = WebServerPreferences.getDefault().getRailRoadName().replaceAll("[^A-Za-z0-9 ]", "-"); // NOI18N
//        log->error("Cannot get host address or name {}", ex.getLocalizedMessage());
//        log->error("Using {} as a fallback.", this->identity);
 }
 if (save) {
     this->saveIdentity();
 }
}

/**
 * Save the current node identity and all former identities to file.
 */
/*private*/ void NodeIdentity::saveIdentity() {
    QDomDocument doc =  QDomDocument();
    QDomElement root = doc.createElement(ROOT_ELEMENT);
    QDomElement identityElement = doc.createElement(NODE_IDENTITY);
    QDomElement formerIdentitiesElement = doc.createElement(FORMER_IDENTITIES);
    if (this->identity == NULL) {
        this->getIdentity(false);
    }
    identityElement.setAttribute(NODE_IDENTITY, this->identity());
    //this->formerIdentities.stream().forEach((formerIdentity) -> {
    foreach(QString formerIdentity, this->formerIdentities())
    {
        log->debug(tr("Retaining former node identity %1").arg(formerIdentity));
        QDomElement e = doc.createElement(NODE_IDENTITY);
        e.setAttribute(NODE_IDENTITY, formerIdentity);
        formerIdentitiesElement.appendChild(e);
    };//);
    root.appendChild(identityElement);
    root.appendChild(formerIdentitiesElement);
    //try (Writer w = new OutputStreamWriter(new FileOutputStream(this->identityFile()), "UTF-8")) { // NOI18N
    QFile* file = new QFile(this->identityFile()->getPath());
    if(file->open(QIODevice::WriteOnly))
    {
     QTextStream* stream = new QTextStream(file);
     stream->setCodec("UTF-8");
     doc.save(*stream,4);
    }
    else
    {
     log->error(tr("unable to save identity file %1 - %2").arg(this->identityFile()->getName()).arg(file->errorString()));
    }
//    Writer* w = new (Writer())
//        XMLOutputter fmt = new XMLOutputter();
//        fmt.setFormat(Format.getPrettyFormat()
//                .setLineSeparator(System.getProperty("line.separator"))
//                .setTextMode(Format.TextMode.PRESERVE));
//        fmt.output(doc, w);
//    } catch (IOException ex) {
//        log->error("Unable to store node identities: {}", ex.getLocalizedMessage());
//    }
}

/**
 * Create an identity string given a MAC address.
 *
 * @param mac a byte array representing a MAC address.
 * @return An identity or NULL if input is NULL.
 */
/*private*/ QString NodeIdentity::createIdentity(QString mac) {
//    StringBuilder sb = new StringBuilder("jmri-"); // NOI18N
//    try {
//        for (int i = 0; i < mac.length; i++) {
//            sb.append(String.format("%02X", mac[i])); // NOI18N
//        }
//    } catch (NullPointerException ex) {
//        return NULL;
//    }
//    return sb.toString();
 return mac;
}

/*private*/ File* NodeIdentity::identityFile() {
    return new File(FileUtil::getPreferencesPath() + "nodeIdentity.xml"); // NOI18N
}

/**
 * @return the identity
 */
/*synchronized*/ /*public*/ QString NodeIdentity::getIdentity() {
    if (this->identity == NULL) {
        this->getIdentity(false);
    }
    return this->_identity;
}

/**
 * @return the formerIdentities
 */
/*public*/ QStringList NodeIdentity::getFormerIdentities() {
    return QStringList(this->_formerIdentities);
}
