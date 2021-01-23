#include "roster.h"
#include <QFile>
#include <QDir>
#include "exceptions.h"
#include "fileutil.h"
#include "rosterentry.h"
#include "logger.h"
#include <QMessageBox>
#include <file.h>
#include "stringutil.h"
#include "rostergroup.h"
#include "rosterconfigmanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "fileutilsupport.h"
#include "userpreferencesmanager.h"
#include "profilemanager.h"
#include "vptr.h"

/** record the single instance of Roster **/
//Roster* Roster::_instance = NULL;
/*private*/ /*static*/ QString Roster::rosterFileName = "roster.xml";
//QString Roster::fileLocation = FileUtil::getUserFilesPath();
QString Roster::fileLocation = QDir::homePath() + QDir::separator() + ".jmri" + QDir::separator();
/**
 * Name of the default roster index file. {@value #DEFAULT_ROSTER_INDEX}
 */
/*public static final */ QString Roster::DEFAULT_ROSTER_INDEX = "roster.xml"; // NOI18N
/**
 * Name for the property change fired when adding a roster entry.
 * {@value #ADD}
 */
/*public static final */ QString Roster::ADD = "add"; // NOI18N
/**
 * Name for the property change fired when removing a roster entry.
 * {@value #REMOVE}
 */
/*public static final */ QString Roster::REMOVE = "remove"; // NOI18N
/**
 * Name for the property change fired when changing the ID of a roster
 * entry. {@value #CHANGE}
 */
/*public static final */ QString Roster::CHANGE = "change"; // NOI18N
/**
 * Property change event fired when saving the roster. {@value #SAVED}
 */
/*public static final */ QString Roster::SAVED = "saved"; // NOI18N/**
/**
 * Property change fired when adding a roster group.
 * {@value #ROSTER_GROUP_ADDED}
 */
/*public*/ /*static*/ /*final*/ QString Roster::ROSTER_GROUP_ADDED = "RosterGroupAdded"; // NOI18N
/**
 * Property change fired when removing a roster group.
 * {@value #ROSTER_GROUP_REMOVED}
 */
/*public*/ /*static*/ /*final*/ QString Roster::ROSTER_GROUP_REMOVED = "RosterGroupRemoved"; // NOI18N
/**
 * Property change fired when renaming a roster group.
 * {@value  #ROSTER_GROUP_RENAMED}
 */
/*public*/ /*static*/ /*final*/ QString Roster::ROSTER_GROUP_RENAMED = "RosterGroupRenamed"; // NOI18N
/**
 * String prefixed to roster group names in the roster entry XML.
 * {@value #ROSTER_GROUP_PREFIX}
 */
/*public*/ /*static*/ /*final*/ QString Roster::ROSTER_GROUP_PREFIX = "RosterGroup:"; // NOI18N
/*public*/ /*final*/ /*static*/ QString Roster::ALLENTRIES = "All Entries";
QString Roster::_rosterGroupPrefix = "RosterGroup:";
/*static final*/ /*public*/ const QString Roster::schemaVersion = "";

Roster::Roster(QObject *parent) :
    XmlFile(parent)
{
 common();
}

/*private*/ void Roster::common()
{
 setObjectName("Roster");
 _list = new QList<RosterEntry*>();
 pcs = new PropertyChangeSupport(this);
 //schemaVersion = "";
 defaultRosterGroup = "";
 rosterGroups = QMap<QString, RosterGroup*>();
 _rosterGroupPrefix = "RosterGroup:";
//schemaVersion = "";
 dirty = false;
 log->setDebugEnabled(true);
 /*
  * This should always be a real path, changes in the UserFiles location are
  * tracked by listening to FileUtilSupport for those changes and updating
  * this path as needed.
  */
 rosterLocation = FileUtil::getUserFilesPath();
 rosterIndexFileName = Roster::DEFAULT_ROSTER_INDEX;

 FileUtilSupport::getDefault()->addPropertyChangeListener(FileUtil::PREFERENCES, (PropertyChangeListener*)new RosterPropertyChangeListener(this));//(PropertyChangeEvent evt) -> {
//             if (Roster.this.getRosterLocation().equals(evt.getOldValue())) {
//                 Roster.this.setRosterLocation((String) evt.getNewValue());
//                 Roster.this.reloadRosterFile();
//             }
//         });
 //connect(FileUtilSupport::getDefault(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

// InstanceManager.getOptionalDefault(UserPreferencesManager.class).ifPresent((upm) -> {
//             // During JUnit testing, preferences is often null
//             this.setDefaultRosterGroup((String) upm.getProperty(Roster.class.getCanonicalName(), "defaultRosterGroup")); // NOI18N
//         });
 UserPreferencesManager* upm;
 if((upm = static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"))) != nullptr)
 {
  this->setDefaultRosterGroup( upm->getProperty(/*Roster.class.getCanonicalName()*/ "jmri.jmrit.roster.Roster", "defaultRosterGroup").toString()); // NOI18N
 }
}

/**
 * Roster manages and manipulates a roster of locomotives.
 * <P>
 * It works
 * with the "roster-config" XML schema to load and store its information.
 *<P>
 * This is an in-memory representation of the roster xml file (see below
 * for constants defining name and location).  As such, this class is
 * also responsible for the "dirty bit" handling to ensure it gets
 * written.  As a temporary reliability enhancement, all changes to
 * this structure are now being written to a backup file, and a copy
 * is made when the file is opened.
 *<P>
 * Multiple Roster objects don't make sense, so we use an "instance" member
 * to navigate to a single one.
 *<P>
 * The only bound property is the list of RosterEntrys; a PropertyChangedEvent
 * is fired every time that changes.
 * <P>
 * The entries are stored in an ArrayList, sorted alphabetically.  That
 * sort is done manually each time an entry is added.
 * <P>
 * The roster is stored in a "Roster Index", which can be read or written.
 * Each individual entry (once stored) contains a filename which can
 * be used to retrieve the locomotive information for that roster entry.
 * Note that the RosterEntry information is duplicated in both the Roster
 * (stored in the roster.xml file) and in the specific file for the entry.
 *
 * @author	Bob Jacobsen   Copyright (C) 2001, 2008, 2010
 * @author  Dennis Miller Copyright 2004
 * @version	$Revision: 22547 $
 * @see         jmri.jmrit.roster.RosterEntry
 */
///*public*/ class Roster extends XmlFile implements RosterGroupSelector {



//    // should be private except that JUnit testing creates multiple Roster objects
//    /*public*/ Roster() {
//        super();
//        this->preferences = InstanceManager.getDefault(UserPreferencesManager.class);
//        if (this->preferences != NULL) {
//            // for some reason, during JUnit testing, preferences is often NULL
//            this->setDefaultRosterGroup((QString) this->preferences.getProperty(Roster.class.getCanonicalName(), "defaultRosterGroup"));
//        }
//    }

// should be private except that JUnit testing creates multiple Roster objects
/*public*/ Roster::Roster(QString rosterFilename)
{
 //this();
 common();
 // if the rosterFilename passed in is null, create a complete path
 // to the default roster index before attempting to read
 if (rosterFilename.isNull() || rosterFilename.isEmpty()) {
     this->rosterFileName = this->getRosterIndexPath();
 }
 QTimer::singleShot(10,this, SLOT(reloadRosterFile()));
}


/**
 * Locate the single instance of Roster, loading it if need be.
 *
 * Calls {@link #getDefault() } to provide the single instance.
 *
 * @deprecated 4.5.1
 * @return The valid Roster object
 */
//@Deprecated
/*public*/ /*synchronized*/ /*static*/ Roster* Roster::instance()
{
 return Roster::getDefault();
}

/**
 * Get the roster for the profile returned by
 * {@link ProfileManager#getActiveProfile()}.
 *
 * @return the roster for the active profile
 */
/*public*/ /*static*/ /*synchronized*/ Roster* Roster::getDefault() {
    return getRoster(ProfileManager::getDefault()->getActiveProfile());
}

/**
 * Get the roster for the specified profile.
 *
 * @param profile the Profile to get the roster for
 * @return the roster for the profile
 */
/*public*/ /*static*/ /*synchronized*/ /*@Nonnull*/
Roster* Roster::getRoster(/*@CheckForNull*/ Profile* profile) {
    return ((RosterConfigManager*)InstanceManager::getDefault("RosterConfigManager"))->getRoster(profile);
}

/**
 * Provide a NULL (empty) roster instance
 *
 */

/**
 * Add a RosterEntry object to the in-memory Roster.
 * @param e Entry to add
 */
/*public*/ void Roster::addEntry(RosterEntry* e)
{
 if(e == nullptr)
  throw (NullPointerException("Roster is null"));
 if (log->isDebugEnabled()) log->debug("Add entry "+e->getFileName());
 /*synchronized (_list)*/ {
  QMutexLocker locker(&mutex);
  int i = _list->size()-1;// Last valid index
  while (i>=0)
  {
   // compareToIgnoreCase not present in Java 1.1.8
   if (e->getId().toUpper().compare(_list->at(i)->getId().toUpper()) > 0 )
    break; // I can never remember whether I want break or continue here
  i--;
 }
 _list->insert(i+1, e);
 }
 e->addPropertyChangeListener((PropertyChangeListener*)this);
 this->addRosterGroups(e->getGroups(this));
 setDirty(true);
 firePropertyChange(ADD, QVariant(), VPtr<RosterEntry>::asQVariant(e));
}

/**
 * Remove a RosterEntry object from the in-memory Roster.  This
 * does not delete the file for the RosterEntry!
 * @param e Entry to remove
 */
/*public*/ void Roster::removeEntry(RosterEntry* e)
{
 if (log->isDebugEnabled()) log->debug(tr("Remove entry ")+e->getId());
 _list->removeAt(_list->indexOf(e));
 setDirty(true);
 firePropertyChange(REMOVE, QVariant(), VPtr<RosterEntry>::asQVariant(e));
}

/**
 * @return Number of entries in the Roster.
 */
/*public*/ int Roster::numEntries() { return _list->size(); }

/**
 * @return The Number of roster entries that are in the specified group.
 */
/*public*/ int Roster::numGroupEntries(QString group) {
    QList<RosterEntry*> l = matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    int num = 0;
    for (int i = 0; i < l.size(); i++) {
        RosterEntry* r = l.at(i);
        if(group!=NULL){
            if(r->getAttribute(getRosterGroupProperty(group))!=NULL){
                if(r->getAttribute(getRosterGroupProperty(group))==("yes"))
                    num++;
            }
        }
        else
            num++;
    }
    return num;
}

/**
 * Return RosterEntry from a "title" string, ala selection in matchingComboBox.
 */
/*public*/ RosterEntry* Roster::entryFromTitle(QString title )
{
 for (int i = 0; i < numEntries(); i++)
 {
  RosterEntry* r = _list->at(i);
  if (r->titleString()==(title)) return r;
 }
 return NULL;
}
/*public*/ RosterEntry* Roster::getEntryForId(QString id)
{
 for (int i=0; i <_list->count(); i++)
 {
  RosterEntry* re = _list->at(i);
  if (re->getId()==(id))
  {
   return re;
  }
 }
 return NULL;
}

/**
 * Return a list of RosterEntry which have a particular DCC address.
 *
 * @param a The address.
 * @return a List of matching entries, empty if there are not matches.
 */
//@Nonnull
/*public*/ QList<RosterEntry*> Roster::getEntriesByDccAddress(QString a) {
#if 0 // done
    return findMatchingEntries(
            (RosterEntry r) -> {
                return r.getDccAddress().equals(a);
            }
    );
#endif
    QList<RosterEntry*> l = QList<RosterEntry*>();
    foreach (RosterEntry* re, *_list) {
     if(re->getDccAddress() == a)
      l.append(re);
    }
    return l;
}

/**
 * Return a specific entry by index
 */
/*public*/ RosterEntry* Roster::getEntry(int i ) {
 if(i < 0 || i >= _list->size())
  throw IndexOutOfBoundsException(tr("index %1 out of range").arg(i));
 return _list->at(i);
}
/**
 * Get all roster entries.
 *
 * @return a list of roster entries; the list is empty if the roster is
 *         empty
 */
//@Nonnull
/*public*/ QList<RosterEntry*> Roster::getAllEntries() {
    return this->getEntriesInGroup("");
}

/**
 * Get the Nth RosterEntry in the group
 *
 * @param group
 * @param i
 * @return The specified entry in the group
 */
/*public*/ RosterEntry* Roster::getGroupEntry(QString group, int i) {
    QList<RosterEntry*> l = matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    int num = 0;
    foreach (RosterEntry* r , l) {
        if (group != NULL) {
            if ((r->getAttribute(getRosterGroupProperty(group)) != NULL)
                    && r->getAttribute(getRosterGroupProperty(group))==("yes")) {
                if (num == i) {
                    return r;
                }
                num++;
            }
        } else {
            if (num == i) {
                return r;
            }
            num++;
        }
    }
    return NULL;
}

/*public*/ int Roster::getGroupIndex(QString group, RosterEntry* re){
    QList<RosterEntry*> l = matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    int num = 0;
    foreach (RosterEntry* r, l) {
        if (group != NULL) {
            if ((r->getAttribute(getRosterGroupProperty(group)) != NULL)
                    && r->getAttribute(getRosterGroupProperty(group))==("yes")) {
                if (r == re) {
                    return num;
                }
                num++;
            }
        } else {
            if (re == r) {
                return num;
            }
            num++;
        }
    }
    return -1;
}

/**
 * Return filename from a "title" string, ala selection in matchingComboBox.
 * @return The filename matching this "title", or NULL if none exists
 */
/*public*/ QString Roster::fileFromTitle(QString title ) {
    RosterEntry* r = entryFromTitle(title);
    if (r != NULL) return r->getFileName();
    return NULL;
}

/*public*/ QList<RosterEntry*> Roster::getEntriesWithAttributeKey(QString key) {
    // slow but effective algorithm
    QList<RosterEntry*> result;// = new ArrayList<RosterEntry>();
//    java.util.Iterator<RosterEntry> i = _list.iterator();
//    while (i.hasNext()) {
    foreach(RosterEntry* r, *_list)
    {
        //RosterEntry* r = i.next();
        if (r->getAttribute(key)!=NULL) result.append(r);
    }
    return result;
}

/*public*/ QList<RosterEntry*> Roster::getEntriesWithAttributeKeyValue(QString key, QString value) {
    // slow but effective algorithm
    QList<RosterEntry*> result;// = new ArrayList<RosterEntry>();
//    java.util.Iterator<RosterEntry> i = _list.iterator();
//    while (i.hasNext()) {
//        RosterEntry r = i.next();
    foreach(RosterEntry* r, *_list)
    {
        QString v = r->getAttribute(key);
        if ( v!="" && v==(value))
            result.append(r);
    }
    return result;
}

/*public*/ QSet<QString> Roster::getAllAttributeKeys() {
    // slow but effective algorithm
    QSet<QString> result;// = new QSet<QString>();
//    java.util.Iterator<RosterEntry> i = _list.iterator();
//    while (i.hasNext()) {
//        RosterEntry* r = i.next();
    foreach(RosterEntry* r, *_list)
    {
        QList<QString> s = r->getAttributes();
        if (!s.isEmpty())
        {
         foreach(QString str, s)
          result.insert(str);
        }
    }
    return result;
}

/*public*/ QList<RosterEntry*> Roster::getEntriesInGroup(QString group) {
   if (group == NULL || group==(Roster::ALLENTRIES)) {
       return this->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   } else {
       return this->getEntriesWithAttributeKeyValue(Roster::getRosterGroupProperty(group), "yes");
   }
}

/**
 * Get a List of {@link RosterEntry} objects in Roster matching some
 * information. The list will be empty if there are no matches.
 *
 * @param roadName      road name of entry or null for any road name
 * @param roadNumber    road number of entry of null for any number
 * @param dccAddress    address of entry or null for any address
 * @param mfg           manufacturer of entry or null for any manufacturer
 * @param decoderModel  decoder model of entry or null for any model
 * @param decoderFamily decoder family of entry or null for any family
 * @param id            id of entry or null for any id
 * @param group         group entry is member of or null for any group
 * @param developerID   developerID of entry, or null for any developerID
 * @param manufacturerID   manufacturerID of entry, or null for any manufacturerID
 * @param productID   productID of entry, or null for any productID
 * @return List of matching RosterEntries or an empty List
 */
//@Nonnull
/*public*/ QList<RosterEntry*> Roster::getEntriesMatchingCriteria(QString roadName, QString roadNumber, QString dccAddress,
        QString mfg, QString decoderModel, QString decoderFamily, QString id, QString group,
        QString developerID, QString manufacturerID, QString productID) {
        // specifically updated for SV2
//        return findMatchingEntries(RosterComparator(this));
//            (RosterEntry r) -> {
//                return checkEntry(r, roadName, roadNumber, dccAddress,
//                        mfg, decoderModel, decoderFamily,
//                        id, group, developerID, manufacturerID, productID);
//            }
//    );
 QList<RosterEntry*> rslt = QList<RosterEntry*>();
 foreach (RosterEntry* re, *_list)
 {
    if(checkEntry(re, roadName, roadNumber, dccAddress,
                                          mfg, decoderModel, decoderFamily,
                                          id, group, developerID, manufacturerID, productID))
     rslt.append(re);
 }
 return rslt;
}

/**
 * Internal method works with #RosterComparator to provide a common
 * search-match-return capability.
 */
/*private*/ QList<RosterEntry*> Roster::findMatchingEntries(RosterComparator c) {
    QList<RosterEntry*> l = QList<RosterEntry*>();
    /*synchronized (_list)*/ {
        //_list.stream().filter((r) -> (c.check(r))).forEachOrdered((r) -> {
//     foreach(Roster* r, *_list)
//     {
//      if(c.check(r))
//        l.append(r);
//     }//);
    }
    return l;
}

/**
 * Get a List of {@link RosterEntry} objects in Roster matching some
 * information. The list may have NULL contents if there are no matches.
 */
/*public*/ QList<RosterEntry*> Roster::getEntriesMatchingCriteria(QString roadName, QString roadNumber, QString dccAddress,
        QString mfg, QString decoderMfgID, QString /*decoderVersionID*/, QString id, QString group)
{
 QList<RosterEntry*> l;// = new ArrayList<RosterEntry>();
 for (int i = 0; i < this->numEntries(); i++)
 {
  if (this->checkEntry(i, roadName, roadNumber, dccAddress, mfg, decoderMfgID, decoderMfgID, id, group))
  {
   l.append(this->getEntry(i));
  }
 }
 return l;
}


/**
 * Get a List of {@link RosterEntry} objects in Roster matching some
 * information. The list may have NULL contents if there are no matches.
 *
 * This method calls {@link #getEntriesMatchingCriteria(java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString) }
 * with a NULL group.
 *
 * @see #getEntriesMatchingCriteria(java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString, java.lang.QString)
 */
/*public*/ QList<RosterEntry*> Roster::matchingList(QString roadName, QString roadNumber, QString dccAddress,
        QString mfg, QString decoderMfgID, QString decoderVersionID, QString id) {
    return this->getEntriesMatchingCriteria(roadName, roadNumber, dccAddress, mfg, decoderMfgID, decoderVersionID, id, NULL);
}

/**
     * Get a List of {@link RosterEntry} objects in Roster matching some
     * information. The list will be empty if there are no matches.
     * <p>
     * This method calls {@link #getEntriesMatchingCriteria(java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String)
     * }
     * with a null group.
     * This pattern is specifically for LNCV (since 4.22).
     *
     * @param dccAddress    address of entry or null for any address
     * @param productID     productID number
     * @return List of matching RosterEntries or an empty List
     * @see #getEntriesMatchingCriteria(java.lang.String, java.lang.String,
     * java.lang.String, java.lang.String, java.lang.String, java.lang.String,
     * java.lang.String, java.lang.String)
     */
    //@Nonnull
    /*public*/ QList<RosterEntry*> Roster::matchingList(QString dccAddress, QString productID) {
        return this->getEntriesMatchingCriteria("", "", dccAddress,
                "", "", "", "", "", "",
                "", productID);
    }
/**
 * Check if an entry is consistent with specific properties.
 *<P>
 * A NULL QString entry
 * always matches. QStrings are used for convenience in GUI building.
 *
 */
/*public*/ bool Roster::checkEntry(int i, QString roadName, QString roadNumber, QString dccAddress,
                          QString mfg, QString decoderModel, QString decoderFamily,
                          QString id, QString group) {
    return this->checkEntry(*_list, i, roadName, roadNumber, dccAddress, mfg, decoderModel, decoderFamily, id, group);
}

/**
 * Check if an entry is consistent with specific properties.
 *<P>
 * A NULL QString entry
 * always matches. QStrings are used for convenience in GUI building.
 *
 */
/*public*/ bool Roster::checkEntry(QList<RosterEntry*> list, int i, QString roadName, QString roadNumber, QString dccAddress,QString mfg, QString decoderModel, QString decoderFamily,QString id, QString group)
{
    RosterEntry* r = list.at(i);
    if (id != NULL && id!=(r->getId())) return false;
    if (roadName != NULL && roadName!=(r->getRoadName())) return false;
    if (roadNumber != NULL && roadNumber!=(r->getRoadNumber())) return false;
    if (dccAddress != NULL && dccAddress!=(r->getDccAddress())) return false;
    if (mfg != NULL && mfg!=(r->getMfg())) return false;
    if (decoderModel != NULL && decoderModel!=(r->getDecoderModel())) return false;
    if (decoderFamily != NULL && decoderFamily!=(r->getDecoderFamily())) return false;
    if (group != NULL
            && Roster::ALLENTRIES!=(group)
            && (r->getAttribute(Roster::getRosterGroupProperty(group)) == NULL
            || r->getAttribute(Roster::getRosterGroupProperty(group))!=("yes"))) {
        return false;
    }
    return true;
}
/**
 * Check if an entry is consistent with specific properties.
 * <p>
 * A null String argument always matches. Strings are used for convenience
 * in GUI building.
 *
 * @param r             the roster entry being checked
 * @param roadName      road name of entry or null for any road name
 * @param roadNumber    road number of entry of null for any number
 * @param dccAddress    address of entry or null for any address
 * @param mfg           manufacturer of entry or null for any manufacturer
 * @param decoderModel  decoder model of entry or null for any model
 * @param decoderFamily decoder family of entry or null for any family
 * @param id            id of entry or null for any id
 * @param group         group entry is member of or null for any group
 * @param developerID   developerID of entry, or null for any developerID
 * @param manufacturerID   manufacturerID of entry, or null for any manufacturerID
 * @param productID     productID of entry, or null for any productID
 * @return True if the entry matches
 */
/*public*/ bool Roster::checkEntry(RosterEntry* r, QString roadName, QString roadNumber, QString dccAddress,
        QString mfg, QString decoderModel, QString decoderFamily,
        QString id, QString group, QString developerID,
            QString manufacturerID, QString productID) {
    // specifically updated for SV2!

    if (id != "" && id != (r->getId())) {
        return false;
    }
    if (roadName != "" && roadName != (r->getRoadName())) {
        return false;
    }
    if (roadNumber != "" && roadNumber != (r->getRoadNumber())) {
        return false;
    }
    if (dccAddress != "" && dccAddress != (r->getDccAddress())) {
        return false;
    }
    if (mfg != "" && mfg != (r->getMfg())) {
        return false;
    }
    if (decoderModel != "" && decoderModel != (r->getDecoderModel())) {
        return false;
    }
    if (decoderFamily != "" && decoderFamily != (r->getDecoderFamily())) {
        return false;
    }
    if (developerID != "" && developerID != (r->getDeveloperID())) {
        return false;
    }
    if (manufacturerID != "" && manufacturerID != (r->getManufacturerID())) {
        return false;
    }
    if (productID != "" && productID != (r->getProductID())) {
        return false;
    }
    return (group == ""
            || Roster::ALLENTRIES == (group)
            || (r->getAttribute(Roster::getRosterGroupProperty(group)) != ""
            && r->getAttribute(Roster::getRosterGroupProperty(group)) ==("yes")));
}

/**
 * Write the entire roster to a file.
 *
 * Creates a new file with the given name, and then calls writeFile (File)
 * to perform the actual work.
 *
 * @param name Filename for new file, including path info as needed.
 * @throws FileNotFoundException
 * @throws IOException
 */
void Roster::writeFile(QString name) //throw (FileNotFoundException, IOException)
{
    if (log->isDebugEnabled()) log->debug("writeFile "+name);
    // This is taken in large part from "Java and XML" page 368
    QFile* file = findFile(name);
    if (file == NULL) {
        file = new QFile(name);
    }

    writeFile (file);
}



/**
 * Write the entire roster to a file object. This does not do backup; that has
 * to be done separately. See writeRosterFile() for a public function that
 * finds the default location, does a backup and then calls this->
 * @param file an op
 * @throws IOException
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient QString processing not really a problem
// though it would be good to fix it if you're working in this area
void Roster::writeFile (QFile* file) //throw (IOException)
{
 // create root element
 QDomDocument doc = QDomDocument("roster-config");
 QDomProcessingInstruction xmlProcessingInstruction = doc.createProcessingInstruction("xml", "version=\"1.0\"  encoding=\"UTF-8\"");
 doc.appendChild(xmlProcessingInstruction);
 xmlProcessingInstruction = doc.createProcessingInstruction("xml-stylesheet", "type=\"text/xsl\" href=\"/xml/XSLT/roster2array.xsl\"");
 doc.appendChild(xmlProcessingInstruction);
 QDomElement root = doc.createElement("roster-config");
//    root.setAttribute("noNamespaceSchemaLocation",
//        "http://jmri.org/xml/schema/roster"+schemaVersion+".xsd",
//        org.jdom.Namespace.getNamespace("xsi",
//          "http://www.w3.org/2001/XMLSchema-instance"));
 root.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
 root.setAttribute("xsi:noNamespaceSchemaLocation", "http://jmri.org/xml/schema/roster" + schemaVersion + ".xsd");
 //doc = newDocument(root);
 //doc.appendChild(root);
 // add XSLT processing instruction
 // <?xml-stylesheet type="text/xsl" href="XSLT/roster.xsl"?>
// QHash<QString, QString> m = QHash<QString, QString>();
// m.insert("type", "text/xsl");
// m.insert("href", xsltLocation+"roster2array.xsl");
 QDomProcessingInstruction p;
 p.setData("?xml-stylesheet type=\"text/xsl\" href=\"/xml/XSLT/roster2array.xsl\"?");
 doc.appendChild(p);

 QString newLocoString = tr("LabelNewDecoder");

 //Check the Comment and Decoder Comment fields for line breaks and
 //convert them to a processor directive for storage in XML
 //Note: this is also done in the LocoFile.java class to do
 //the same thing in the indidvidual locomotive roster files
 //Note: these changes have to be undone after writing the file
 //since the memory version of the roster is being changed to the
 //file version for writing
 for (int i=0; i<numEntries(); i++)
 {

  //Extract the RosterEntry at this index and inspect the Comment and
  //Decoder Comment fields to change any \n characters to <?p?> processor
  //directives so they can be stored in the xml file and converted
  //back when the file is read.
  RosterEntry* r = _list->at(i);
  if(r->getId()!=(newLocoString))
  {
   QString tempComment = r->getComment();
   QString xmlComment = "";

   //transfer tempComment to xmlComment one character at a time, except
   //when \n is found.  In that case, insert <?p?>
//    for (int k = 0; k < tempComment.length(); k++)
//    {
//     //if (tempComment.startsWith("\n", k))
//     if(tempComment.mid(k).startsWith("\n"))
//     {
//      xmlComment = xmlComment + "<?p?>";
//     }
//     else
//     {
//      xmlComment = xmlComment + tempComment.mid(k, 1);
//     }
//    }
   xmlComment = tempComment.replace("\n", "<?p?>");
   r->setComment(xmlComment);

   //Now do the same thing for the decoderComment field
   QString tempDecoderComment = r->getDecoderComment();
   QString xmlDecoderComment = "";

//    for (int k = 0; k < tempDecoderComment.length(); k++)
//    {
//        //if (tempDecoderComment.startsWith("\n", k))
//        if(tempDecoderComment.mid(k).startsWith("\n"))
//        {
//            xmlDecoderComment = xmlDecoderComment + "<?p?>";
//        }
//        else
//        {
//            xmlDecoderComment = xmlDecoderComment +
//                tempDecoderComment.mid(k, k + 1);
//        }
//    }
   xmlDecoderComment = tempDecoderComment.replace("\n", "<?p?>");
   r->setDecoderComment(xmlDecoderComment);
  }
  else
  {
   log->info("skip unsaved roster entry with default name " + r->getId());
  }
 }
 //All Comments and Decoder Comment line feeds have been changed to processor directives


 // add top-level elements
 QDomElement values;
 root.appendChild(values = doc.createElement("roster"));
 // add entries
 for (int i=0; i<numEntries(); i++)
 {
  if(_list->at(i)->getId()!=(newLocoString))
  {
   values.appendChild(_list->at(i)->store(doc));
  }
  else
  {
   log->info("skip unsaved roster entry with default name " + _list->at(i)->getId());
  }
 }

 if(_rosterGroupList.size()>=1)
 {
   QDomElement rosterGroup = doc.createElement("rosterGroup");
   for (int i=0; i<_rosterGroupList.size(); i++){
       QDomElement group = doc.createElement("group");
       if(_rosterGroupList.at(i)!=(ALLENTRIES))
       {
        QDomText text = doc.createTextNode(_rosterGroupList.at(i));
           group.appendChild(text);
           rosterGroup.appendChild(group);
       }
   }
   root.appendChild(rosterGroup);
 }
 doc.appendChild(root);
 writeXML(file, doc);

 //Now that the roster has been rewritten in file form we need to
 //restore the RosterEntry object to its normal \n state for the
 //Comment and Decoder comment fields, otherwise it can cause problems in
 //other parts of the program (e.g. in copying a roster)
 for (int i=0; i<numEntries(); i++)
 {
  RosterEntry* r = _list->at(i);
  if(r->getId()!=(newLocoString))
  {
   QString xmlComment = r->getComment();
   QString tempComment = "";

//    for (int k = 0; k < xmlComment.length(); k++)
//    {
//        if (xmlComment.mid(k).startsWith("<?p?>"))
//        {
//            tempComment = tempComment + "\n";
//            k = k + 4;
//        }
//        else {
//            tempComment = tempComment + xmlComment.mid(k, k + 1);
//        }
//    }
   tempComment = xmlComment.replace("<?p?>", "\n");
   r->setComment(tempComment);

   QString xmlDecoderComment = r->getDecoderComment();
   QString tempDecoderComment = "";

//    for (int k = 0; k < xmlDecoderComment.length(); k++)
//    {
//     if (xmlDecoderComment.mid(k).startsWith("<?p?>"))
//     {
//      tempDecoderComment = tempDecoderComment + "\n";
//      k = k + 4;
//     }
//     else
//     {
//      tempDecoderComment = tempDecoderComment +
//                xmlDecoderComment.mid(k, k + 1);
//     }
//    }
   tempDecoderComment = xmlDecoderComment.replace("<?p?>", "\n");
   r->setDecoderComment(tempDecoderComment);
  }
  else
  {
   log->info("skip unsaved roster entry with default name " + r->getId());
  }
 }

 // done - roster now stored, so can't be dirty
 setDirty(false);
 firePropertyChange(SAVED, QVariant(false), QVariant(true));
}

/**
 * Name a valid roster entry filename from an entry name.
 * <p>
 * <ul>
 * <li>Replaces all problematic characters with "_".
 * <li>Append .xml suffix
 * </ul>
 * Does not check for duplicates.
 * @throws IllegalArgumentException if called with NULL or empty entry name
 * @param entry the getId() entry name from the RosterEntry
 * @see RosterEntry#ensureFilenameExists()
 * @since 2.1.5
 */
/*static*/ /*public*/ QString Roster::makeValidFilename(QString entry)
{
 if (entry.isNull()) throw new IllegalArgumentException("makeValidFilename requires non-NULL argument");
 if (entry==("")) throw new IllegalArgumentException("makeValidFilename requires non-empty argument");

 // name sure there are no bogus chars in name
 QString cleanName = entry.replace("[\\W]","_");  // remove \W, all non-word (a-zA-Z0-9_) characters
 cleanName = cleanName.replace(" ", "_");

 // ensure suffix
 return cleanName+".xml";
}

/**
 * Read the contents of a roster XML file into this object.
 * <P>
 * Note that this does not
 * clear any existing entries.
 * @param name filename of roster file
 */
//@SuppressWarnings("unchecked")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient QString processing not really a problem
// though it would be good to fix it if you're working in this area
bool Roster::readFile(QString name) //throw org.jdom.JDOMException, java.io.IOException {
{
 QFile file(name);
 // roster exists?
 if (!(file.exists()))
 {
  log->debug("no roster file found; this is normal if you haven't put decoders in your roster yet");
  return false;
 }
 doc = QDomDocument("roster");
 if(!file.open(QFile::ReadOnly | QFile::Text)) return 1;
 if(!doc.setContent(&file))
 {
  qDebug() << tr("Error parsing file %1 ").arg(file.fileName());
  file.close();
  return false;
 }
 file.close();

 // find root
 QDomElement root = doc.documentElement();
 qDebug() << tr("rootElement = %1").arg(root.tagName());
 if (root.isNull())
 {
  log->error("Roster file exists, but could not be read; roster not available");
  return false;
 }
 //if (log->isDebugEnabled()) XmlFile.dumpElement(root);

 // decode type, invoke proper processing routine if a decoder file
 if (!root.firstChildElement("roster").isNull())
 {
  //List<Element> l = root.getChild("roster").getChildren("locomotive");
  QDomNodeList l = root.firstChildElement("roster").elementsByTagName("locomotive"); // NOI18N
  if (log->isDebugEnabled())
   log->debug("readFile sees "+QString("%1").arg(l.size())+" children");
  for (int i=0; i<l.size(); i++)
  {
   addEntry(new RosterEntry(l.at(i).toElement()));
//   qApp->processEvents();
  }
  //Scan the object to check the Comment and Decoder Comment fields for
  //any <?p?> processor directives and change them to back \n characters
  for (int i = 0; i < numEntries(); i++)
  {
   //Get a RosterEntry object for this index
   RosterEntry* r = _list->at(i);

   //Extract the Comment field and create a new string for output
   QString tempComment = r->getComment();
   QString xmlComment = "";

   //transfer tempComment to xmlComment one character at a time, except
   //when <?p?> is found.  In that case, insert a \n and skip over those
   //characters in tempComment.
//   for (int k = 0; k < tempComment.length(); k++)
//   {
//    //if (tempComment.startsWith("<?p?>", k))
//       if(tempComment.mid(k).startsWith("<?p?>"))
//    {
//     xmlComment = xmlComment + "\n";
//     k = k + 4;
//    }
//    else
//    {
//     xmlComment = xmlComment + tempComment.mid(k, k + 1);
//    }
//   }
   xmlComment = tempComment.replace("<?p?>", "\n");

   r->setComment(xmlComment);

   //Now do the same thing for the decoderComment field
   QString tempDecoderComment = r->getDecoderComment();
   QString xmlDecoderComment = "";

//   for (int k = 0; k < tempDecoderComment.length(); k++)
//   {
//    if (tempDecoderComment.mid(k).startsWith("<?p?>"))
//    {
//     xmlDecoderComment = xmlDecoderComment + "\n";
//     k = k + 4;
//    }
//    else
//    {
//     xmlDecoderComment = xmlDecoderComment +
//     tempDecoderComment.mid(k, k + 1);
//    }
//   }
//   xmlDecoderComment = tempDecoderComment.replace("<?p?>", "\n");

   r->setDecoderComment(xmlDecoderComment);
  }
 }
 else
 {
  log->error("Unrecognized roster file contents in file: "+name);
 }
 if (!root.firstChildElement("rosterGroup").isNull())
 {
  //List<Element> g = root.getChild("rosterGroup").getChildren("group");
  QDomNodeList g = root.firstChildElement("rosterGroup").childNodes();
  for (int i=0; i<g.size(); i++)
  {
   addRosterGroup(g.at(i).toElement().text());
  }
 }
 return true;
}


/*public*/ void Roster::dispose() {
    if (log->isDebugEnabled()) log->debug("dispose");
    if (dirty) log->error("Dispose invoked on dirty Roster");
}

/**
 * Store the roster in the default place, including making a backup if needed.
 * <p>
 * Uses writeFile(QString), a protected method that can write to
 * a specific location.
 */
/*public*/  void Roster::writeRoster()
{
 Roster::getDefault()->makeBackupFile(this->getRosterIndexPath());
 try
 {
  Roster::getDefault()->writeFile(this->getRosterIndexPath());
 }
 catch (Exception e) {
        log->error("Exception while writing the new roster file, may not be complete: "+e.getMessage());
//        try {
//            JOptionPane.showMessageDialog(NULL,
//                    ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getQString("ErrorSavingText")+"\n"+e.getMessage(),
//                    ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getQString("ErrorSavingTitle"),
//                    JOptionPane.ERROR_MESSAGE);
        QMessageBox::critical(0,tr("Error saving Roster"), tr("Exception while writing the new roster file, may not be complete"));
        }
//        catch (HeadlessException he)
//        {
//            // silently ignore failure to display dialog
//        }
//    }
}
/**
 * Rebuild the Roster index and store it.
 */
/*public*/ void Roster::reindex()
{
 Roster* roster = new Roster();
 foreach (QString fileName, Roster::getAllFileNames())
 {
  // Read file
  try {
      QDomElement loco = (new LocoFile())->rootFromName(LocoFile::getFileLocation() + fileName).firstChildElement("locomotive");
      if (!loco.isNull()) {
          RosterEntry* re = new RosterEntry(loco);
          re->setFileName(fileName);
          roster->addEntry(re);
      }
  } catch (JDOMException /*| IOException*/ ex) {
   log->error(tr("Exception while loading loco XML file: %1 execption: %2").arg(fileName).arg(ex.getMessage()));
  }
 }

 this->makeBackupFile(this->getRosterIndexPath());
 try {
     roster->writeFile(this->getRosterIndexPath());
 } catch (IOException ex) {
     log->error(tr("Exception while writing the new roster file, may not be complete: %1").arg(ex.getMessage()));
 }
 this->reloadRosterFile();
 log->info(tr("Roster rebuilt, stored in %1").arg(this->getRosterIndexPath()));
}
/**
 * Update the in-memory Roster to be consistent with
 * the current roster file.  This removes any existing roster entries!
 */
/*public*/ void Roster::reloadRosterFile()
{
 // clear existing
 _list->clear();
 this->rosterGroups.clear();
 // and read new
 try
 {
  this->readFile(this->getRosterIndexPath());
 }
 catch (Exception e)
 {
  log->error("Exception during roster reading: "+e.getMessage());
 }
}

/*public*/ void Roster::setRosterIndexFileName(QString fileName) {
        this->rosterIndexFileName = fileName;
}

/*public*/ QString Roster::getRosterIndexFileName() {
    return this->rosterIndexFileName;
}

/*public*/ QString Roster::getRosterIndexPath() {
    return this->getRosterLocation() + this->getRosterIndexFileName();
}

/*
 * get the path to the file containing roster entry files.
 */
/*public*/ QString Roster::getRosterFilesLocation() {
    return getDefault()->getRosterLocation() + "roster" + File::separator;
}

/**
 * Set the default location for the Roster file, and all individual
 * locomotive files.
 *
 * @param f Absolute pathname to use. A null or "" argument flags a return
 *          to the original default in the user's files directory. This
 *          parameter must be a potentially valid path on the system.
 */
/*public*/ void Roster::setRosterLocation(QString f)
{
 QString oldRosterLocation = this->rosterLocation;
 QString p = f;
 if (p != "") {
     if (p.isEmpty()) {
         p = "";
     } else {
         p = FileUtil::getAbsoluteFilename(p);
         if (p == "") {
             throw IllegalArgumentException(tr("\"%1\" is not a valid path").arg(f)); // NOI18N
         }
         if (!p.endsWith(File::separator)) {
             p = p + File::separator;
         }
     }
 }
 if (p == "") {
     p = FileUtil::getUserFilesPath();
 }
 this->rosterLocation = p;
 log->debug(tr("Setting roster location from %1 to %2").arg(oldRosterLocation).arg(this->rosterLocation));
 if (this->rosterLocation == (FileUtil::getUserFilesPath())) {
     log->debug("Roster location reset to default");
 }
 if (this->rosterLocation != (oldRosterLocation)) {
     this->firePropertyChange(RosterConfigManager::DIRECTORY, oldRosterLocation, this->rosterLocation);
 }
 this->reloadRosterFile();
}

/**
 * Absolute path to roster file location.
 * <P>
 * Default is in the user's files directory, but can be set to anything.
 *
 * @return location of the Roster file
 * @see jmri.util.FileUtil#getUserFilesPath()
 */
/*public*/ QString Roster::getRosterLocation()
{
 return this->rosterLocation;
}

//@Override
/*public*/ /*synchronized*/ void Roster::addPropertyChangeListener(PropertyChangeListener* l)
{
    pcs->addPropertyChangeListener(l);
}

/*public*/ /*synchronized*/ void Roster::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    pcs->addPropertyChangeListener(propertyName, listener);
}

/*protected*/ void Roster::firePropertyChange(QString p, QVariant old, QVariant n) {
    pcs->firePropertyChange(p,old,n);
}

/*public*/ /*synchronized*/ void Roster::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}

/*public*/ /*synchronized*/ void Roster::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    pcs->removePropertyChangeListener(propertyName, listener);
}

//@Override
/*public*/ QVector<PropertyChangeListener*> Roster::getPropertyChangeListeners() {
    return pcs->getPropertyChangeListeners();
}

//@Override
/*public*/ QVector<PropertyChangeListener*> Roster::getPropertyChangeListeners(QString propertyName) {
    return pcs->getPropertyChangeListeners(propertyName);
}
/**
 * Notify that the ID of an entry has changed.  This doesn't actually change the
 * Roster per se, but triggers recreation.
 */
/*public*/ void Roster::entryIdChanged(RosterEntry* r) {
    log->debug("EntryIdChanged");
#if 1 // TODO:
    // order may be wrong! Sort
    //RosterEntry[] rarray = new RosterEntry[_list.size()];
    QMap<QString, RosterEntry*>* rarray = new QMap<QString, RosterEntry*>();
    for (int i=0; i<_list->count(); i++)
    {
     RosterEntry*re = _list->at(i);
     rarray->insert(re->getId(), re);
    }
    //StringUtil.sortUpperCase(rarray);
    //for (int i=0; i<rarray.length; i++) _list.set(i,rarray[i]);
    QMapIterator<QString, RosterEntry*> iter(*rarray);
    _list->clear();
    while(iter.hasNext())
    {
     iter.next();
     _list->append(iter.value());
    }
    firePropertyChange(CHANGE, QVariant(), VPtr<RosterEntry>::asQVariant(r));
#endif
}

/*public*/ /*static*/ QString Roster::getRosterGroupName(QString rosterGroup)
{
    if(rosterGroup == NULL)
        return ALLENTRIES;
    return rosterGroup;
}

/**
 * Get the string for a RosterGroup property in a RosterEntry
 *
 * @param name The name of the rosterGroup
 * @return The full property string
 */
/*public*/ /*static*/ QString Roster::getRosterGroupProperty(QString name) {
    return _rosterGroupPrefix + name;
}

/**
 * Add a roster group, notifying all listeners of the change.
 *
 * This method fires the property change notification
 * {@value #ROSTER_GROUP_ADDED}.
 *
 * @param rg The group to be added
 */
/*public*/ void Roster::addRosterGroup(RosterGroup* rg) {
    if (this->rosterGroups.contains(rg->getName())) {
        return;
    }
    this->rosterGroups.insert(rg->getName(), rg);
    log->debug(tr("firePropertyChange Roster Groups model: %1").arg(rg->getName())); // test for panel redraw after duplication
    firePropertyChange(ROSTER_GROUP_ADDED, "", rg->getName());
}

/**
 * Add a roster group and optionally notify all listeners
 *
 * renameRosterGroupList(old, new) calls this method with notify=false
 * The public version of this method calls this method with notify=true
 * This method fires the property change notification "RosterGroupAdded"
 *
 * @param str The group to be added
 * @param notify Flag to fire a property change
 */
/*public*/ void Roster::addRosterGroup(QString rg) {
    if (_rosterGroupList.contains(rg)) {
        return;
    }
    this->addRosterGroup(new RosterGroup(rg));
}
/**
 * Add a list of {@link jmri.jmrit.roster.rostergroup.RosterGroup}.
 * RosterGroups that are already known to the Roster are ignored.
 *
 * @param groups RosterGroups to add to the roster. RosterGroups already in
 *               the roster will not be added again.
 */
/*public*/ void Roster::addRosterGroups(QList<RosterGroup*> groups) {
    //groups.stream().forEach((rg) ->
 foreach(RosterGroup* rg, groups)
 {
     this->addRosterGroup(rg);
 }//);
}

/*public*/ void Roster::removeRosterGroup(RosterGroup* rg) {
    this->delRosterGroupList(rg->getName());
}
/**
 * Delete a roster group, notifying all listeners of the change
 * <p>
 * This method fires the property change notification "RosterGroupDeleted"
 *
 * @param str The group to be deleted
 */
/*public*/ void Roster::delRosterGroupList(QString str) {
    delRosterGroupList(str, true);
}

/**
 * Delete a roster group and optionally notify all listeners
 * <p>
 * renameRosterGroupList(old, new) calls this method with notify=false
 * The public version of this method calls this method with notify=true
 * This method fires the property change notification "RosterGroupDeleted"
 *
 * @param str The group to be deleted
 * @param notify Flag to fire a property change
 */
/*private*/ void Roster::delRosterGroupList(QString rg, bool notify) {
    _rosterGroupList.remove(_rosterGroupList.indexOf(rg));
    QString str = _rosterGroupPrefix + rg;
    QList<RosterEntry*> groupentries = getEntriesWithAttributeKey(str);
    for (int i = 0; i < groupentries.size(); i++) {
        groupentries.at(i)->deleteAttribute(str);
    }
    QString rg1;
    if (notify)
    {
     firePropertyChange("ROSTER_GROUP_REMOVED", QVariant(rg), QVariant());
     //emit propertyChange("RosterGroupRemoved", (QObject*)&rg, NULL);
    }
}

/**
 * Copy a roster group, adding every entry in the roster group to the new
 * group.
 * <p>
 * If a roster group with the target name already exists, this method
 * silently fails to rename the roster group. The GUI method
 * CopyRosterGroupAction.performAction() catches this error and informs
 * the user. This method fires the property change "RosterGroupAdded".
 *
 * @param oldName Name of the roster group to be copied
 * @param newName Name of the new roster group
 * @see jmri.jmrit.roster.swing.RenameRosterGroupAction
 */
/*public*/ void Roster::copyRosterGroupList(QString oldName, QString newName) {
    if (_rosterGroupList.contains(newName)) {
        return;
    }
    QString oldGroup = _rosterGroupPrefix + oldName;
    QString newGroup = _rosterGroupPrefix + newName;
    QList<RosterEntry*> groupEntries = getEntriesWithAttributeKey(oldGroup);
    foreach (RosterEntry* re , groupEntries) {
        re->putAttribute(newGroup, "yes");
    }
    this->addRosterGroup(newName);
}

/**
 * Rename a roster group, while keeping every entry in the roster group
 * <p>
 * If a roster group with the target name already exists, this method
 * silently fails to rename the roster group. The GUI method
 * RenameRosterGroupAction.performAction() catches this error and informs
 * the user. This method fires the property change "RosterGroupRenamed".
 *
 * @param oldName Name of the roster group to be renamed
 * @param newName New name for the roster group
 * @see jmri.jmrit.roster.swing.RenameRosterGroupAction
 */
/*public*/ void Roster::renameRosterGroupList(QString oldName, QString newName) {
    if (_rosterGroupList.contains(newName)) {
        return;
    }
    this->rosterGroups.value(oldName)->setName(newName);
}

/**
 * Get a list of the user defined roster groups.
 *
 * This list is a shallow copy of the system-wide list of roster groups.
 * QStrings are immutable, so deleting an item from the copy should not
 * affect the system-wide list of roster groups.
 *
 * @return QVector<QString>
 */
/*public*/ QVector<QString> Roster::getRosterGroupList() {
    return QVector<QString>(_rosterGroupList);
}

/**
 * Get the identifier for all entries in the roster.
 *
 * @param locale - The desired locale
 * @return "All Entries" in the specified locale
 */
/*public*/ /*static*/ QString Roster::AllEntries(QLocale /*locale*/) {
     return tr("All Entries"); // NOI18N
}

/**
 * Get the identifier for all entries in the roster.
 *
 * @param locale - The desired locale
 * @return "All Entries" in the specified locale
 */
/*public*/ /*static*/ QString Roster::_AllEntries(QLocale /*locale*/) {
 // NOTE: A QTranslator class for the locale needs to be loaded!
    return tr( "All Entries"); // NOI18N
}
/**
 * Get the default roster group.
 *
 * This method ensures adherence to the RosterGroupSelector protocol
 *
 * @return The entire roster
 */
//@Override
/*public*/ QString Roster::getSelectedRosterGroup()
{
    return getDefaultRosterGroup();
}

/**
 * @return the defaultRosterGroup
 */
/*public*/ QString Roster::getDefaultRosterGroup() {
    return defaultRosterGroup;
}

/**
 * @param defaultRosterGroup the defaultRosterGroup to set
 */
/*public*/ void Roster::setDefaultRosterGroup(QString defaultRosterGroup) {
    this->defaultRosterGroup = defaultRosterGroup;
    // TODO: this->preferences.setProperty(Roster.class.getCanonicalName(), "defaultRosterGroup", defaultRosterGroup);
}

/**
 * Get an array of all the RosterEntry-containing files in the target
 * directory
 */
/*static*/ QStringList Roster::getAllFileNames()
{
 Logger log("Roster");
 // ensure preferences will be found for read
 FileUtil::createDirectory(LocoFile::getFileLocation());

 // create an array of file names from roster dir in preferences, count entries
 int i;
 int np = 0;
 QStringList sp;// = null;
 if (log.isDebugEnabled())
 {
  log.debug("search directory " + LocoFile::getFileLocation());
 }
 File* fp = new File(LocoFile::getFileLocation());
 if (fp->exists())
 {
  sp = fp->list();
  for (i = 0; i < sp.length(); i++)
  {
   if (sp[i].endsWith(".xml") || sp[i].endsWith(".XML"))
   {
    np++;
   }
  }
 }
 else
 {
  log.warn(FileUtil::getUserFilesPath() + "roster directory was missing, though tried to create it");
 }

 // Copy the entries to the final array
 QVector<QString> sbox =  QVector<QString>(np);
 int n = 0;
 if (!sp.isEmpty() && np > 0)
 {
  for (i = 0; i < sp.length(); i++)
  {
   if (sp[i].endsWith(".xml") || sp[i].endsWith(".XML"))
   {
    sbox.replace(n++, sp[i]);
   }
  }
 }
 // The resulting array is now sorted on file-name to make it easier
 // for humans to read
 QStringList l = sbox.toList();
 StringUtil::sort(l);

 if (log.isDebugEnabled())
 {
  log.debug("filename list:");
  for (i = 0; i < l.length(); i++)
  {
   log.debug("      " + l[i]);
  }
 }
 return l;
}

/**
 * Get the groups known to the roster itself.
 *
 * @return the rosterGroups
 */
/*public*/ QMap<QString, RosterGroup*> Roster::getRosterGroups() {
    return rosterGroups;
}

/*public*/ void Roster::rosterGroupRenamed(QString oldName, QString newName) {
    this->firePropertyChange(Roster::ROSTER_GROUP_RENAMED, oldName, newName);
}

/*public*/ void RosterPropertyChangeListener::propertyChange(PropertyChangeEvent *evt)
{
 FileUtil::Property* oldValue = VPtr<FileUtil::Property>::asPtr( evt->getOldValue());
 FileUtil::Property* newValue = VPtr<FileUtil::Property>::asPtr( evt->getNewValue());
 Profile* project = oldValue->getKey();
 if (roster->getRoster(project) && roster->getRosterLocation() == (oldValue->getValue())) {
     roster->setRosterLocation( evt->getNewValue().toString());
     roster->reloadRosterFile();
 }
}

//@Override
/*public*/ void Roster::propertyChange(PropertyChangeEvent* evt) {
    if ( qobject_cast<RosterEntry*>(evt->getSource())) {
        if (evt->getPropertyName() == (RosterEntry::ID)) {
            this->entryIdChanged((RosterEntry*) evt->getSource());
        }
    }
}
//    // initialize logging
/*private*/ /*final*/ /*static*/ Logger* Roster::log = LoggerFactory::getLogger("Roster");
