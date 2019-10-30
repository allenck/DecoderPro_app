#include "nodeidentity.h"
#include "file.h"
#include "logger.h"
#include "fileutil.h"
#include "profilemanager.h"
#include "profile.h"
#include <QNetworkInterface>
#include "loggerfactory.h"

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
/*private*/ /*final*/ /*static*/ Logger* NodeIdentity::log = LoggerFactory::getLogger("NodeIdentity");

/*private*/ /*final*/ /*static*/ QString NodeIdentity::ROOT_ELEMENT = "nodeIdentityConfig"; // NOI18N
/*private*/ /*static*/ /*final*/ QString NodeIdentity::UUID = "uuid"; // NOI18N
/*private*/ /*final*/ /*static*/ QString NodeIdentity::NODE_IDENTITY = "nodeIdentity"; // NOI18N
/*private*/ /*final*/ /*static*/ QString NodeIdentity::FORMER_IDENTITIES = "formerIdentities"; // NOI18N
/*private*/ /*static*/ /*final*/ QString NodeIdentity::IDENTITY_PREFIX = "jmri-";


/*private*/ NodeIdentity::NodeIdentity() {
 _formerIdentities = new QStringList();
 _identity = "";
 uuid = "";

 init(); // init as a method so the init can be /*synchronized*/.
}

/*synchronized*/ /*private*/ void NodeIdentity::init()
{
 File* identityFile = this->identityFile();
 if (identityFile->exists())
 {
  try
  {
   QDomDocument doc;// = (new SAXBuilder()).build(identityFile);
   QFile* f = new QFile(identityFile->getPath());
   if(f->open(QIODevice::ReadOnly))
   {
    doc.setContent(f);
   }
   else throw IOException(identityFile->getPath());
   QDomElement uu = doc.documentElement().firstChildElement(UUID);
   if (!uu.isNull()) {
       this->uuid = uu.attribute(UUID);
   } else {
       this->uuid = "";
       this->getIdentity(true);
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
   if (!this->validateIdentity(id))
   {
    log->debug(tr("Node identity %1 is invalid. Generating new node identity.").arg(id));
    this->_formerIdentities->append(id);
    this->getIdentity(true);
   }
   else
   {
    this->getIdentity(true);
   }
  }
  catch (/*JDOMException |*/ IOException ex) {
      log->error(tr("Unable to read node identities: %1").arg( ex.getLocalizedMessage()));
      this->getIdentity(true);
  }
 } else {
  this->uuid = "";
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
 QString uniqueId = "-";
 try
 {
  if(ProfileManager::getDefault()->getActiveProfile() == nullptr)
   throw NullPointerException();
  uniqueId += ProfileManager::getDefault()->getActiveProfile()->getUniqueId();
 }
 catch (NullPointerException ex) {
     uniqueId += ProfileManager::createUniqueId();
 }
 if (_instance == nullptr)
 {
     _instance = new NodeIdentity();
     log->info(tr("Using %1 as the JMRI Node identity").arg(_instance->getIdentity() + uniqueId));
 }
 return _instance->getIdentity() + uniqueId;
}

/**
 * If network hardware on a node was replaced, the identity will change.
 *
 * @return A list of other identities this node may have had in the past.
 */
/*synchronized*/ /*public*/ /*static*/ QList<QString> NodeIdentity::formerIdentities() {
    if (_instance == NULL) {
        _instance = new NodeIdentity();
        log->info(tr("Using %1 as the JMRI Node identity").arg(_instance->getIdentity()));
    }
    return _instance->getFormerIdentities();
}

/**
 * Verify that the current identity is a valid identity for this hardware.
 *
 * @return true if the identity is based on this hardware.
 */
/*synchronized*/ /*private*/ bool NodeIdentity::validateIdentity(QString ident) {
 log->debug(tr("Validating Node identity %1.").arg(ident));
 return (this->uuid != "" && ((IDENTITY_PREFIX + this->uuid) == (ident)));

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
    QString oldIdentity;
    foreach(QString formerIdentity, *this->_formerIdentities)
    {
     if(oldIdentity == formerIdentity)
      continue;
     log->debug(tr("Retaining former node identity %1").arg(formerIdentity));
     QDomElement e = doc.createElement(NODE_IDENTITY);
     e.setAttribute(NODE_IDENTITY, formerIdentity);
     formerIdentitiesElement.appendChild(e);
     oldIdentity = formerIdentity;
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
    QString sb = QString(IDENTITY_PREFIX); // NOI18N
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
 * Creates a copy of the last-used old node identity for use with the new
 * identity.
 *
 * @param oldPath the old node identity folder
 * @param newPath the new node identity folder
 * @return true if successful
 */
/*public*/ /*static*/ bool NodeIdentity::copyFormerIdentity(File* oldPath, File* newPath) {
    QString uniqueId = "-";
    try {
        uniqueId += ProfileManager::getDefault()->getActiveProfile()->getUniqueId();
    } catch (NullPointerException ex) { // because there is no active profile
        uniqueId += ProfileManager::createUniqueId();
        log->debug(tr("created uniqueID \"%1\" because of there (probably) is no active profile").arg( uniqueId));
    }
    QStringList formerIdList = NodeIdentity::formerIdentities();
    int listSize = formerIdList.size();
    if (listSize < 1) {
        log->debug("Unable to copy from a former identity; no former identities found.");
        return false;
    }
    log->debug(tr("%1 former identies found").arg(listSize));
    for (int i = (listSize - 1); i >= 0; i--) {
        QString theIdentity = formerIdList.at(i);
        log->debug(tr("Trying to copy former identity %1, \"%2\"").arg(i + 1).arg(theIdentity));
        File* theDir = new File(oldPath, theIdentity + uniqueId);
        if (theDir->exists()) {
            try {
                log->info(tr("Copying from old node \"%1\"").arg(theDir->toString()));
                log->info(tr("  to new node \"%1\"").arg(newPath->toString()));
                FileUtil::copy(theDir, newPath);
            } catch (IOException ex) {
                log->warn(tr("Unable to copy \"%1\" to \"%2\"").arg(theDir->toString()).arg(newPath->toString()));
                return false;
            }
            return true;
        } else {
            log->warn(tr("Non-existent old node \"%1\"").arg(theDir->toString()));
        }
    }
    return false;
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

