#include "nodeidentity.h"
#include "file.h"
#include "logger.h"
#include "fileutil.h"
#include "profilemanager.h"
#include "profile.h"
#include <QNetworkInterface>
#include "loggerfactory.h"
#include "xmlfile.h"

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
/*private*/ /*static*/ /*final*/ QString NodeIdentity::UUID_ELEMENT = "uuid"; // NOI18N
/*private*/ /*final*/ /*static*/ QString NodeIdentity::NODE_IDENTITY = "nodeIdentity"; // NOI18N
/*private*/ /*static*/ /*final*/ QString NodeIdentity::STORAGE_IDENTITY = "storageIdentity"; // NOI18N
/*private*/ /*final*/ /*static*/ QString NodeIdentity::FORMER_IDENTITIES = "formerIdentities"; // NOI18N
/*private*/ /*static*/ /*final*/ QString NodeIdentity::IDENTITY_PREFIX = "jmri-";

/**
 * A string of 64 URL compatible characters.
 * <p>
 * Used by {@link #uuidToCompactString uuidToCompactString} and
 * {@link #uuidFromCompactString uuidFromCompactString}.
 */
/*protected*/ /*static*/ /*final*/ QString NodeIdentity::URL_SAFE_CHARACTERS =
        "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ-0123456789"; // NOI18N

/*private*/ NodeIdentity::NodeIdentity(QObject* parent) : QObject(parent)
{
 _formerIdentities = QStringList();
 _identity = "";
 uuid = "";
 /*private*/ /*final*/
 profileStorageIdentities = QMap<Profile*, QString>();


 init(); // init as a method so the init can be /*synchronized*/.
}

/*synchronized*/ /*private*/ void NodeIdentity::init()
{
 File* identityFile = this->identityFile();
 if (identityFile->exists())
 {
  try
  {
   bool save = false;
   this->_formerIdentities.clear();
   QDomDocument doc;// = (new SAXBuilder()).build(identityFile);
   QFile* f = new QFile(identityFile->getPath());
   if(f->open(QIODevice::ReadOnly))
   {
    doc.setContent(f);
   }
   else throw IOException(identityFile->getPath());
   QDomElement ue = doc.documentElement().firstChildElement(UUID_ELEMENT);
   if (!ue.isNull())
   {
    try
    {
     QString attr = ue.attribute(UUID_ELEMENT);
     this->uuid = uuidFromCompactString( attr);
     this->_storageIdentity = this->uuid.toString(QUuid::WithoutBraces); // backwards compatible, see class docs
     if(!this->_formerIdentities.contains(this->_storageIdentity))
        this->_formerIdentities.append(this->_storageIdentity);
     if(!this->_formerIdentities.contains(IDENTITY_PREFIX + attr))
        this->_formerIdentities.append(IDENTITY_PREFIX + attr);
    }
    catch (IllegalArgumentException ex){
     // do nothing
    }
   }
   QDomElement si = doc.documentElement().firstChildElement(STORAGE_IDENTITY);
   if (!si.isNull())
   {
    try
    {
     this->_storageIdentity = si.attribute(STORAGE_IDENTITY);
     if (this->uuid.isNull() || this->_storageIdentity != (this->uuid.toString(QUuid::WithoutBraces))) {
         this->uuid = QUuid::fromString(this->_storageIdentity);
         save = true; // updated UUID
     }
    } catch (IllegalArgumentException ex) {
        save = true; // save if attribute not available
    }
   } else {
       save = true; // element missing, need to save
   }
   if (this->_storageIdentity.isNull()) {
       save = true;
       this->getStorageIdentity(false);
   }
   QString id = QString();
   try
   {
    id = doc.documentElement().firstChildElement(NODE_IDENTITY).attribute(NODE_IDENTITY);
    QDomNodeList nl = doc.documentElement().firstChildElement(FORMER_IDENTITIES).childNodes();
    for(int i = 0; i < nl.size(); i++)
    {
    QDomElement e = nl.at(i).toElement();
    if(!this->_formerIdentities.contains(e.attribute(NODE_IDENTITY)))
        this->_formerIdentities.append(e.attribute(NODE_IDENTITY));
    }
   } catch (NullPointerException ex)
   {
    // do nothing -- if id was not set, it will be generated
   }

   if (!this->validateNetworkIdentity(id))
   {
    log->warn(tr("Node identity %1 is invalid. Generating new node identity.").arg(id));
    save = true;
    this->getNetworkIdentity(false);
   }
   else
   {
    this->_networkIdentity = id;
   }
   // save if new identities were created or expected attribute did not exist
   if (save)
   {
    this->saveIdentity();
   }
  }
  catch (/*JDOMException |*/ IOException ex) {
      log->error(tr("Unable to read node identities: %1").arg( ex.getLocalizedMessage()));
      this->getNetworkIdentity(true);
  }
 }
 else {
  this->getNetworkIdentity(true);
 }
}

/**
 * Return the node's current network identity. For historical purposes, the
 * network identity is also referred to as the {@literal node} or
 * {@literal node identity}.
 *
 * @return A network identity. If this identity is not in the form
 *         {@code jmri-MACADDRESS-profileId}, or if {@code MACADDRESS} is a
 *         multicast MAC address, this identity should be considered
 *         unreliable and subject to change across JMRI restarts. Note that
 *         if the identity is in the form {@code jmri-MACADDRESS} the JMRI
 *         instance has not loaded a configuration profile, and the network
 *         identity will change once that a configuration profile is loaded.
 */
/*public*/ /*static*/ /*synchronized*/ QString NodeIdentity::networkIdentity() {
    QString uniqueId = "";
    Profile* profile = ProfileManager::getDefault()->getActiveProfile();
    if (profile != nullptr) {
        uniqueId = "-" + profile->getUniqueId();
    }
    if (instance == nullptr) {
        instance = new NodeIdentity();
        log->info(tr("Using %1 as the JMRI Node identity").arg(instance->getNetworkIdentity() + uniqueId));
    }
    return instance->getNetworkIdentity() + uniqueId;
}

/**
 * Return the node's current storage identity for the active profile. This
 * is a convenience method that calls {@link #storageIdentity(Profile)} with
 * the result of {@link jmri.profile.ProfileManager#getActiveProfile()}.
 *
 * @return A storage identity.
 * @see #storageIdentity(Profile)
 */
/*public*/ /*static*/ /*synchronized*/ QString NodeIdentity::storageIdentity() {
    return storageIdentity(ProfileManager::getDefault()->getActiveProfile());
}

/**
 * Return the node's current storage identity. This can be used in networked
 * file systems to ensure per-computer storage is available.
 * <p>
 * <strong>Note</strong> this only ensure uniqueness if the preferences path
 * is not shared between multiple computers as documented in
 * {@link jmri.util.FileUtil#getPreferencesPath()} (the most common cause of
 * this would be sharing a user's home directory in its entirety between two
 * computers with similar operating systems as noted in
 * getPreferencesPath()).
 *
 * @param profile The profile to get the identity for. This is only needed
 *                    to check that the identity should not be in an older
 *                    format.
 *
 * @return A storage identity. If this identity is not in the form of a UUID
 *         or {@code jmri-UUID-profileId}, this identity should be
 *         considered unreliable and subject to change across JMRI restarts.
 *         When generating a new storage ID, the form is always a UUID and
 *         other forms are used only to ensure continuity where other forms
 *         may have been used in the past.
 */
/*public*/ /*static*/ /*synchronized*/ QString NodeIdentity::storageIdentity(Profile* profile) {
    if (instance == nullptr) {
        instance = new NodeIdentity();
    }
    QString id = instance->getStorageIdentity();
    // this entire check is so that a JMRI 4.14 style identity string can be built
    // and checked against the given profile to determine if that should be used
    // instead of just returning the non-profile-specific machine identity
    if (profile != nullptr) {
        // using a map to store profile-specific identities allows for the possibility
        // that, although there is only one active profile at a time, other profiles
        // may be manipulated by JMRI while that profile is active (this happens to a
        // limited extent already in the profile configuration UI)
        // (a map also allows for ensuring the info message is displayed once per profile)
        if (!instance->profileStorageIdentities.contains(profile)) {
            QString oldId = IDENTITY_PREFIX + uuidToCompactString(instance->uuid) + "-" + profile->getUniqueId();
            File* local = new File(new File(profile->getPath(), Profile::PROFILE), oldId);
            if (local->exists() && local->isDirectory()) {
                id = oldId;
            }
            instance->profileStorageIdentities.insert(profile, id);
            log->info(tr("Using %1 as the JMRI storage identity for profile id %2").arg(id).arg(profile->getUniqueId()));
        }
        id = instance->profileStorageIdentities.value(profile);
    }
    return id;
}
/**
 * If network hardware on a node was replaced, the identity will change.
 *
 * @return A list of other identities this node may have had in the past.
 */
/*synchronized*/ /*public*/ /*static*/ QList<QString> NodeIdentity::formerIdentities() {
    if (_instance == NULL) {
        _instance = new NodeIdentity();
        log->info(tr("Using %1 as the JMRI Node identity").arg(_instance->getNetworkIdentity()));
    }
    return _instance->getFormerIdentities();
}

/**
 * Verify that the current identity is a valid identity for this hardware.
 *
 * @param identity the identity to validate; may be null
 * @return true if the identity is based on this hardware; false otherwise
 */
/*private*/ /*synchronized*/ bool NodeIdentity::validateNetworkIdentity(QString identity) {
//    try {
//        Enumeration<NetworkInterface> enumeration = NetworkInterface.getNetworkInterfaces();
//        while (enumeration.hasMoreElements()) {
//            NetworkInterface nic = enumeration.nextElement();
//            if (!nic.isVirtual() && !nic.isLoopback()) {
//                String nicIdentity = this.createNetworkIdentity(nic.getHardwareAddress());
//                if (nicIdentity != null && nicIdentity.equals(identity)) {
//                    return true;
//                }
//            }
//        }
//    } catch (SocketException ex) {
//        log.error("Error accessing interface: {}", ex.getLocalizedMessage(), ex);
//    }
  QList<QNetworkInterface> addresses = QNetworkInterface::allInterfaces();
  foreach(QNetworkInterface nic, addresses)
  {
   if (!nic.isValid() && !nic.IsLoopBack)
   {
    QString nicIdentity = this->createNetworkIdentity(nic.hardwareAddress().toLocal8Bit());
    if (nicIdentity != "" && nicIdentity==(identity)) {
        return true;
    }
   }
  }
    return false;
}

/**
 * Get a node identity from the current hardware.
 *
 * @param save whether to save this identity or not
 */
/*private*/ /*synchronized*/ void NodeIdentity::getNetworkIdentity(bool save) {
//    try {
//        try {
//            try {
 this->_networkIdentity = this->createIdentity(QNetworkInterface::interfaceFromIndex(QHostAddress::LocalHost).hardwareAddress().toLocal8Bit());
//            } catch (NullPointerException ex) {
//                // NetworkInterface.getByInetAddress(InetAddress.getLocalHost()).getHardwareAddress() failed
//                // this can be due to multiple reasons, most likely getLocalHost() failing on certain platforms.
//                // Only set this.identity = null, since the following null checks address all potential problems
//                // with getLocalHost() including some expected conditions (such as InetAddress.getLocalHost()
//                // returning the loopback interface).
//                this.networkIdentity = null;
//            }
            if (this->_networkIdentity == "") {
//                Enumeration<NetworkInterface> nics = NetworkInterface.getNetworkInterfaces();
//                while (nics.hasMoreElements()) {
//                    NetworkInterface nic = nics.nextElement();
//                    if (!nic.isLoopback() && !nic.isVirtual() && (nic.getHardwareAddress() != null)) {
//                        this.networkIdentity = this.createNetworkIdentity(nic.getHardwareAddress());
//                        if (this.networkIdentity != null) {
//                            break;
//                        }
//                    }
//                }
             QList<QNetworkInterface> addresses = QNetworkInterface::allInterfaces();
             foreach(QNetworkInterface nic, addresses)
             {
              if(!nic.IsLoopBack && nic.isValid() )
              {
               this->_networkIdentity = this->createIdentity(nic.hardwareAddress().toLocal8Bit());
               if(this->_networkIdentity !="")
                break;
              }
             }
            }
//        } catch (SocketException ex) {
//            this.networkIdentity = null;
//        }
//    } catch (UnknownHostException ex) {
//        this.networkIdentity = null;
//    }
    if (this->_networkIdentity == "") {
//        log.info("No MAC addresses found, generating a random multicast MAC address as per RFC 4122.");
//        byte[] randBytes = new byte[6];
//        Random randGen = new Random();
//        randGen.nextBytes(randBytes);
//        randBytes[0] = (byte) (randBytes[0] | 0x01); // set multicast bit in first octet
//        this.networkIdentity = this.createNetworkIdentity(randBytes);
     this->_networkIdentity = /*InetAddress.getLocalHost().getHostName()*/ QHostAddress(QHostAddress::LocalHost).toString();

    }
//    this.formerIdentities.add(this.networkIdentity);
    if (save) {
        this->saveIdentity();
    }
}
/*private*/ /*static*/ NodeIdentity* NodeIdentity::instance = nullptr;
#if 0
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
#endif
/**
 * Get a node identity from the current hardware.
 *
 * @param save whether to save this identity or not
 */
/*private*/ /*synchronized*/ void NodeIdentity::getStorageIdentity(bool save) {
    if (this->_storageIdentity.isNull()) {
        // also generate UUID to protect against case where user
        // migrates from JMRI < 4.14 to JMRI > 4.14 back to JMRI = 4.14
        if (this->uuid == "" ) {
            this->uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
        }
        this->_storageIdentity = this->uuid.toString(QUuid::WithoutBraces);
        if(!this->_formerIdentities.contains(this->_storageIdentity))
            this->_formerIdentities.append(this->_storageIdentity);
    }
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
 QDomElement networkIdentityElement = doc.createElement(NODE_IDENTITY);
 QDomElement storageIdentityElement = doc.createElement(STORAGE_IDENTITY);
 QDomElement formerIdentitiesElement = doc.createElement(FORMER_IDENTITIES);
 QDomElement uuidElement = doc.createElement(UUID_ELEMENT);
 if (this->_networkIdentity.isNull()) {
     this->getNetworkIdentity(false);
 }
 if (this->_storageIdentity.isNull()) {
     this->getStorageIdentity(false);
 }
 // ensure formerIdentities contains current identities as well

 if(!this->_formerIdentities.contains(this->_networkIdentity))
  this->_formerIdentities.append(this->_networkIdentity);
 if(!this->_networkIdentity.contains(this->_storageIdentity))
  this->_formerIdentities.append(this->_storageIdentity);
 if (!this->uuid.isNull()) {
  if(!this->_formerIdentities.contains(IDENTITY_PREFIX + uuidToCompactString(this->uuid)))
     this->_formerIdentities.append(IDENTITY_PREFIX + uuidToCompactString(this->uuid));
 }
 networkIdentityElement.setAttribute(NODE_IDENTITY, this->_networkIdentity);
 storageIdentityElement.setAttribute(STORAGE_IDENTITY, this->_storageIdentity);
 //this->_formerIdentities.stream().forEach((formerIdentity) ->
 foreach(QString formerIdentity, this->_formerIdentities)
 {
     log->debug(tr("Retaining former node identity %1").arg(formerIdentity));
     QDomElement e = doc.createElement(NODE_IDENTITY);
     e.setAttribute(NODE_IDENTITY, formerIdentity);
     formerIdentitiesElement.appendChild(e);
 }//);
 doc.documentElement().appendChild(networkIdentityElement);
 doc.documentElement().appendChild(storageIdentityElement);
 if (!this->uuid.isNull()) {
     uuidElement.setAttribute(UUID_ELEMENT, uuidToCompactString(this->uuid));
     doc.documentElement().appendChild(uuidElement);
 }
 doc.documentElement().appendChild(formerIdentitiesElement);
// try (Writer w = new OutputStreamWriter(new FileOutputStream(this.identityFile()), "UTF-8")) { // NOI18N
//     XMLOutputter fmt = new XMLOutputter();
//     fmt.setFormat(Format.getPrettyFormat()
//             .setLineSeparator(System.getProperty("line.separator"))
//             .setTextMode(Format.TextMode.PRESERVE));
//     fmt.output(doc, w);
// } catch (IOException ex) {
//     log.error("Unable to store node identities: {}", ex.getLocalizedMessage());
// }
 XmlFile* xmlFile = new XmlFile();
 xmlFile->writeXML(this->identityFile(), doc);
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

/**
 * Create an identity string given a MAC address.
 *
 * @param mac a byte array representing a MAC address.
 * @return An identity or null if input is null.
 */
/*private*/ QString NodeIdentity::createNetworkIdentity(QByteArray mac) {
    QString sb = QString(IDENTITY_PREFIX); // NOI18N
//    try {
        for (int i = 0; i < mac.length(); i++) {
//            sb.append(String.format("%02X", mac[i])); // NOI18N
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
 * @return the network identity
 */
/*private*/ /*synchronized*/ QString NodeIdentity::getNetworkIdentity() {
    if (this->_networkIdentity == "") {
        this->getNetworkIdentity(false);
    }
    return this->_networkIdentity;
}

/**
 * @return the storage identity
 */
/*private*/ /*synchronized*/ QString NodeIdentity::getStorageIdentity() {
    if (this->_storageIdentity == QString()) {
        this->getStorageIdentity(false);
    }
    return this->_storageIdentity;
}
/**
 * Encodes a UUID into a 22 character URL compatible string. This is used to
 * store the UUID in a manner compatible with JMRI 4.14.
 * <p>
 * From an example by <a href="https://stackoverflow.com/">Tom Lobato</a>.
 *
 * @param uuid the UUID to encode
 * @return the 22 character string
 */
/*protected*/ /*static*/ QString NodeIdentity::uuidToCompactString(QUuid uuid) {
//    char[] c = new char[22];
//    long buffer = 0;
//    int val6;
//    QString sb;// = new StringBuilder();

//    for (int i = 1; i <= 22; i++) {
//        switch (i) {
//            case 1:
//                buffer = uuid.getLeastSignificantBits();
//                break;
//            case 12:
//                buffer = uuid.getMostSignificantBits();
//                break;
//            default:
//                break;
//        }
//        val6 = (int) (buffer & 0x3F);
//        c[22 - i] = URL_SAFE_CHARACTERS.charAt(val6);
//        buffer = buffer >>> 6;
//    }
//    return sb.append(c).toString();
 return uuid.toString(QUuid::WithoutBraces);
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
#if 0
/**
 * @return the identity
 */
/*synchronized*/ /*public*/ QString NodeIdentity::getIdentity() {
    if (this->_identity == "") {
        this->getIdentity(false);
    }
    return this->_identity;
}
#endif
/**
 * Decodes the original UUID from a 22 character string generated by
 * {@link #uuidToCompactString uuidToCompactString}. This is used to store
 * the UUID in a manner compatible with JMRI 4.14.
 *
 * @param compact the 22 character string
 * @return the original UUID
 */
/*protected*/ /*static*/ QUuid NodeIdentity::uuidFromCompactString(QString compact) {
#if 0
    long mostSigBits = 0;
    long leastSigBits = 0;
    long buffer = 0;
    int val6;

    for (int i = 0; i <= 21; i++) {
        switch (i) {
            case 0:
                buffer = 0;
                break;
            case 11:
                mostSigBits = buffer;
                buffer = 0;
                break;
            default:
                buffer = buffer << 6;
                break;
        }
        val6 = URL_SAFE_CHARACTERS.indexOf(compact.charAt(i));
        buffer = buffer | (val6 & 0x3F);
    }
    leastSigBits = buffer;
    return QUuid(mostSigBits, leastSigBits);
#else
 return QUuid::fromString(compact);
#endif
}
/**
 * @return the formerIdentities
 */
/*public*/ QStringList NodeIdentity::getFormerIdentities() {
    return QStringList(this->_formerIdentities);
}

