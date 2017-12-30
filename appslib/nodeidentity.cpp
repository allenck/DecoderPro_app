#include "nodeidentity.h"
#include "file.h"
#include "logger.h"
#include "fileutil.h"
#include "profilemanager.h"
#include "profile.h"
#include <QNetworkInterface>

//NodeIdentity::NodeIdentity(QObject *parent) : QObject(parent)
//{

//}
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

/*private*/ /*static*/ NodeIdentity* NodeIdentity::_instance = NULL;
// /*private*/ /*final*/ static Logger log = LoggerFactory.getLogger(NodeIdentity.class);

/*private*/ /*final*/ /*static*/ QString NodeIdentity::ROOT_ELEMENT = "nodeIdentityConfig"; // NOI18N
/*private*/ /*final*/ /*static*/ QString NodeIdentity::NODE_IDENTITY = "nodeIdentity"; // NOI18N
/*private*/ /*final*/ /*static*/ QString NodeIdentity::FORMER_IDENTITIES = "formerIdentities"; // NOI18N


/*private*/ NodeIdentity::NodeIdentity() {
 log = new Logger("NodeIdentity");
_formerIdentities = new QStringList();
_identity = "";

 init(); // init as a method so the init can be /*synchronized*/.
}

/*synchronized*/ /*private*/ void NodeIdentity::init()
{
 File* identityFile = this->identityFile();
 if (identityFile->exists())
 {
//        try {
  QDomDocument doc;// = (new SAXBuilder()).build(identityFile);
  QFile* f = new QFile(identityFile->getPath());
  if(f->open(QIODevice::ReadOnly))
  {
   doc.setContent(f);
  }
  QString id = doc.documentElement().firstChildElement(NODE_IDENTITY).attribute(NODE_IDENTITY);
  this->_formerIdentities->clear();
 //            doc.getRootElement().getChild(FORMER_IDENTITIES).getChildren().stream().forEach((e) -> {
 //                this->formerIdentities.add(e.getAttributeValue(NODE_IDENTITY));
 //            });
  QDomNodeList nl = doc.documentElement().firstChildElement(FORMER_IDENTITIES).childNodes();
  for(int i = 0; i < nl.size(); i++)
  {
   QDomElement e = nl.at(i).toElement();
   this->_formerIdentities->append(e.attribute(NODE_IDENTITY));
  }
  if (!this->validateIdentity(id)) {
      log->debug(tr("Node identity %1 is invalid. Generating new node identity.").arg(id));
      this->_formerIdentities->append(id);
      this->getIdentity(true);
  } else {
      this->getIdentity(true);
  }
//        } catch (JDOMException | IOException ex) {
//            log->error("Unable to read node identities: {}", ex.getLocalizedMessage());
//            this->getIdentity(true);
//        }
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
/*synchronized*/ /*public*/ /*static*/ QString NodeIdentity::identity() {
 Logger log("NodeIdentity");
    QString uniqueId = "-";
    try {
        uniqueId += ProfileManager::getDefault()->getActiveProfile()->getUniqueId();
    } catch (NullPointerException ex) {
        uniqueId += ProfileManager::createUniqueId();
    }
    if (_instance == NULL) {
        _instance = new NodeIdentity();
        log.info(tr("Using %1 as the JMRI Node identity").arg(_instance->getIdentity() + uniqueId));
    }
    return _instance->getIdentity() + uniqueId;
}
#if 1
/**
 * If network hardware on a node was replaced, the identity will change.
 *
 * @return A list of other identities this node may have had in the past.
 */
/*synchronized*/ /*public*/ /*static*/ QList<QString> NodeIdentity::formerIdentities() {
 Logger log("NodeIdentity");
    if (_instance == NULL) {
        _instance = new NodeIdentity();
        log.info(tr("Using %1 as the JMRI Node identity").arg(_instance->getIdentity()));
    }
    return _instance->getFormerIdentities();
}
#endif
/**
 * Verify that the current identity is a valid identity for this hardware.
 *
 * @return true if the identity is based on this hardware.
 */
/*synchronized*/ /*private*/ bool NodeIdentity::validateIdentity(QString identity) {
//    try {
//        Enumeration<NetworkInterface> enumeration = NetworkInterface.getNetworkInterfaces();
//        while (enumeration.hasMoreElements()) {
//            NetworkInterface nic = enumeration.nextElement();
 foreach(QNetworkInterface nic, QNetworkInterface::allInterfaces())
 {
  if (/*!nic.isVirtual() &&*/ !nic.IsLoopBack)
  {
   QString nicIdentity = this->createIdentity(nic.hardwareAddress().toLocal8Bit());
   if (nicIdentity != "" && nicIdentity == (identity)) {
       return true;
   }
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
/*synchronized*/ /*private*/ void NodeIdentity::getIdentity(bool save) {
//    try {
//        try {
//            try {
//                this->_identity = this->createIdentity(NetworkInterface.getByInetAddress(InetAddress.getLocalHost()).getHardwareAddress());
    this->_identity = this->createIdentity(QNetworkInterface::interfaceFromIndex(QHostAddress::LocalHost).hardwareAddress().toLocal8Bit());
//            } catch (NullPointerException ex) {
//                // NetworkInterface.getByInetAddress(InetAddress.getLocalHost()).getHardwareAddress() failed
//                // this can be due to multiple reasons, most likely getLocalHost() failing on certain platforms.
//                // Only set this->identity = null, since the following null checks address all potential problems
//                // with getLocalHost() including some expected conditions (such as InetAddress.getLocalHost()
//                // returning the loopback interface).
//                this->_identity = "";
//            }
            if (this->_identity == "") {
//                Enumeration<NetworkInterface> nics = NetworkInterface.getNetworkInterfaces();
//                while (nics.hasMoreElements()) {
//                    NetworkInterface nic = nics.nextElement();
//                    if (!nic.isLoopback() && !nic.isVirtual()) {
//                        this->identity = this->createIdentity(nic.getHardwareAddress());
//                        if (this->identity != null) {
//                            break;
//                        }
//                    }
//                }
             QList<QNetworkInterface> addresses = QNetworkInterface::allInterfaces();
             foreach(QNetworkInterface nic, addresses)
             {
              if(!nic.IsLoopBack && nic.isValid() )
              {
               this->_identity = this->createIdentity(nic.hardwareAddress().toLocal8Bit());
               if(this->_identity !="")
                break;
              }
             }
            }
            if (this->_identity == "") {
//                try {
                    this->_identity = /*InetAddress.getLocalHost().getHostName()*/ QHostAddress(QHostAddress::LocalHost).toString();
//                } catch (UnknownHostException ex1) {
//                    this->identity = InetAddress.getLocalHost().getHostAddress();
//                }
            }
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
//    }
    if (save) {
        this->saveIdentity();
    }
}

/**
 * Save the current node identity and all former identities to file.
 */
/*private*/ void NodeIdentity::saveIdentity() {
    //Document doc = new Document();
 QDomDocument doc;
 QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
 doc.appendChild(xmlProcessingInstruction);
 QDomElement root;
    doc.appendChild(root = doc.createElement(ROOT_ELEMENT));
    QDomElement identityElement = doc.createElement(NODE_IDENTITY);
    QDomElement formerIdentitiesElement = doc.createElement(FORMER_IDENTITIES);
    if (this->_identity == "") {
        this->getIdentity(false);
    }
    identityElement.setAttribute(NODE_IDENTITY, this->_identity);
   // this->formerIdentities.stream().forEach((formerIdentity) -> {
    foreach(QString formerIdentity, *this->_formerIdentities)
    {
        log->debug(tr("Retaining former node identity %1").arg(formerIdentity));
        QDomElement e = doc.createElement(NODE_IDENTITY);
        e.setAttribute(NODE_IDENTITY, formerIdentity);
        formerIdentitiesElement.appendChild(e);
    } //);
    root.appendChild(identityElement);
    root.appendChild(formerIdentitiesElement);

//    try (Writer w = new OutputStreamWriter(new FileOutputStream(this->identityFile()), "UTF-8")) { // NOI18N
//        XMLOutputter fmt = new XMLOutputter();
//        fmt.setFormat(Format.getPrettyFormat()
//                .setLineSeparator(System.getProperty("line.separator"))
//                .setTextMode(Format.TextMode.PRESERVE));
//        fmt.output(doc, w);
    QFile* f = new QFile(this->identityFile()->getPath());
    if(f->open(QIODevice::WriteOnly))
    {
     QTextStream* s = new QTextStream(f);
     s->setCodec("UTF-8");
     doc.save(*s,2);
    }
//    } catch (IOException ex) {
//        log->error("Unable to store node identities: {}", ex.getLocalizedMessage());
//    }
}

/**
 * Create an identity string given a MAC address.
 *
 * @param mac a byte array representing a MAC address.
 * @return An identity or null if input is null.
 */
/*private*/ QString NodeIdentity::createIdentity(QByteArray mac) {
    QString sb = QString("jmri-"); // NOI18N
//    try {
        for (int i = 0; i < mac.length(); i++) {
//            sb.append(tr("%02X").arg(mac[i])); // NOI18N
         if(mac[i] != ':')
          sb.append(tr("%02").arg(mac[i]));
        }
//    } catch (NullPointerException ex) {
//        return null;
//    }
    return sb/*.toString()*/;
}

/*private*/ File* NodeIdentity::identityFile() {
    return new File(FileUtil::getPreferencesPath() + "nodeIdentity.xml"); // NOI18N
}

/**
 * @return the identity
 */
/*synchronized*/ /*public*/ QString NodeIdentity::getIdentity() {
    if (this->_identity == "") {
        this->getIdentity(false);
    }
    return this->_identity;
}

/**
 * @return the formerIdentities
 */
/*public*/ QStringList NodeIdentity::getFormerIdentities() {
    return QStringList(*this->_formerIdentities);
}

