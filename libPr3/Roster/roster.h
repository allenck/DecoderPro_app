#ifndef ROSTER_H
#define ROSTER_H

#include <QObject>
//#include "rosterentry.h"
#include <QtXml/QDomDocument>
#include "propertychangesupport.h"
#include "logger.h"
#include <QVector>
#include "xmlfile.h"
#include "libPr3_global.h"
#include "propertychangelistener.h"
#include <QMutex>
#include "propertychangeprovider.h"

class Profile;
class RosterGroup;
class RosterEntry;
class LIBPR3SHARED_EXPORT Roster : public XmlFile, public PropertyChangeProvider
{
    Q_OBJECT
 Q_INTERFACES(PropertyChangeProvider)
public:
    explicit Roster(QObject *parent = 0);
    /** record the single instance of Roster **/
    // should be private except that JUnit testing creates multiple Roster objects
    /*public*/ Roster(QString rosterFilename);
//    /*public*/ /*synchronized*/ Q_DECL_DEPRECATED static void resetInstance();
    /**
     * Locate the single instance of Roster, loading it if need be.
     * @return The valid Roster object
     */
    QT_DEPRECATED /*public*/ static /*synchronized*/ Roster* instance();
    /*public*/ static /*synchronized*/ Roster* getDefault();
    /*public*/ static /*synchronized*/ /*@Nonnull*/ Roster* getRoster(/*@CheckForNull*/ Profile* profile);
    /*public*/ void addEntry(RosterEntry* e);
    /*public*/ void removeEntry(RosterEntry* e);
    /*public*/ int numEntries();
    /*public*/ void dispose();
    /*public*/ void writeRoster();
    /*public*/ void reindex();
    /*public*/ void setRosterIndexFileName(QString fileName);
    /*public*/ QString getRosterIndexFileName() ;
    /*public*/ QString getRosterIndexPath();
    /*public*/ void setRosterLocation(QString f);
    /*public*/ QString getRosterLocation();
    /*public*/ void entryIdChanged(RosterEntry* r);
    static /*public*/ QString makeValidFilename(QString entry);
    /*public*/ RosterEntry* entryFromTitle(QString title );
    /*public*/ RosterEntry* getEntryForId(QString id);
    /*public*/ QList<RosterEntry*> getEntriesByDccAddress(QString a);
    /*public*/ QList<RosterEntry*> getAllEntries();
    /*public*/ RosterEntry* getEntry(int i );
    /*public*/ static QString _AllEntries(QLocale locale);
    /*public*/ QString getSelectedRosterGroup();
    /**
     * @return the defaultRosterGroup
     */
    /*public*/ QString getDefaultRosterGroup();
    /**
     * @param defaultRosterGroup the defaultRosterGroup to set
     */
    /*public*/ void setDefaultRosterGroup(QString defaultRosterGroup);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners();
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName);
    /*public*/ int numGroupEntries(QString group);
    /*public*/ RosterEntry* getGroupEntry(QString group, int i);
    /*public*/ int getGroupIndex(QString group, RosterEntry* re);
    /*public*/ QString fileFromTitle(QString title );
    /*public*/ QList<RosterEntry*> getEntriesWithAttributeKey(QString key);
    /*public*/ QList<RosterEntry*> getEntriesWithAttributeKeyValue(QString key, QString value);
    /*public*/ QSet<QString> getAllAttributeKeys();
    /*public*/ QList<RosterEntry*> getEntriesInGroup(QString group);
    /*public*/ QList<RosterEntry*> getEntriesMatchingCriteria(QString roadName, QString roadNumber, QString dccAddress,
            QString mfg, QString decoderModel, QString decoderFamily, QString id, QString group,
            QString developerID, QString manufacturerID, QString productID);
    /*public*/ QList<RosterEntry*> getEntriesMatchingCriteria(QString roadName, QString roadNumber, QString dccAddress,
            QString mfg, QString decoderMfgID, QString decoderVersionID, QString id, QString group);
    /*public*/ QList<RosterEntry*> matchingList(QString roadName, QString roadNumber, QString dccAddress,
            QString mfg, QString decoderMfgID, QString decoderVersionID, QString id);
    /*public*/ QList<RosterEntry*> matchingList(QString dccAddress, QString productID);
    /*public*/ bool checkEntry(int i, QString roadName, QString roadNumber, QString dccAddress, QString mfg, QString decoderModel, QString decoderFamily, QString id, QString group);
    /*public*/ bool checkEntry(QList<RosterEntry*> list, int i, QString roadName, QString roadNumber, QString dccAddress, QString mfg, QString decoderModel, QString decoderFamily, QString id, QString group);
    /*public*/ bool checkEntry(RosterEntry* r, QString roadName, QString roadNumber, QString dccAddress,
            QString mfg, QString decoderModel, QString decoderFamily,
            QString id, QString group, QString developerID,
                QString manufacturerID, QString productID);
    void writeFile(QString name); // throw (FileNotFoundException, IOException);
    void writeFile (QFile* file); //throw (IOException);
    static QString _rosterGroupPrefix;// = "RosterGroup:";
    /*public*/ static QString getRosterGroupName(QString rosterGroup);
    /*public*/ static QString getRosterGroupProperty(QString name);
    /*public*/ void delRosterGroupList(QString str);
    /*public*/ void copyRosterGroupList(QString oldName, QString newName);
    /*public*/ void renameRosterGroupList(QString oldName, QString newName);
    /*public*/ QVector<QString> getRosterGroupList();
    /*public*/ static QString AllEntries(QLocale /*locale*/);

    /**
     * Name of the default roster index file. {@value #DEFAULT_ROSTER_INDEX}
     */
    /*public*/ static /*final*/ QString DEFAULT_ROSTER_INDEX; // = "roster.xml"; // NOI18N
    /**
     * Name for the property change fired when adding a roster entry.
     * {@value #ADD}
     */
    /*public*/ static /*final*/ QString ADD; // = "add"; // NOI18N
    /**
     * Name for the property change fired when removing a roster entry.
     * {@value #REMOVE}
     */
    /*public*/ static /*final*/ QString REMOVE;// = "remove"; // NOI18N
    /**
     * Name for the property change fired when changing the ID of a roster
     * entry. {@value #CHANGE}
     */
    /*public*/ static /*final*/ QString CHANGE;// = "change"; // NOI18N
    /**
     * Property change event fired when saving the roster. {@value #SAVED}
     */
    /*public*/ static /*final*/ QString SAVED;// = "saved"; // NOI18N/**
    /**
     * Property change fired when adding a roster group.
     * {@value #ROSTER_GROUP_ADDED}
     */
    /*public*/ static /*final*/ QString ROSTER_GROUP_ADDED;// = "RosterGroupAdded"; // NOI18N
    /**
     * Property change fired when removing a roster group.
     * {@value #ROSTER_GROUP_REMOVED}
     */
    /*public*/ static /*final*/ QString ROSTER_GROUP_REMOVED;//= "RosterGroupRemoved"; // NOI18N
    /**
     * Property change fired when renaming a roster group.
     * {@value  #ROSTER_GROUP_RENAMED}
     */
    /*public*/ static /*final*/ QString ROSTER_GROUP_RENAMED;// = "RosterGroupRenamed"; // NOI18N
    /**
     * String prefixed to roster group names in the roster entry XML.
     * {@value #ROSTER_GROUP_PREFIX}
     */
    /*public*/ static /*final*/ QString ROSTER_GROUP_PREFIX;// = "RosterGroup:"; // NOI18N
    /**
     * Title of the "All Entries" roster group. As this varies by locale, do not
     * rely on being able to store this value.
     */
    /*public*/ /*final*/ static QString ALLENTRIES;// = ResourceBundle.getBundle("jmri.jmrit.roster.JmritRosterBundle").getString("ALLENTRIES");
    static const QString schemaVersion;// = "";
    /*public*/ QMap<QString, RosterGroup*> getRosterGroups();
    /*public*/ void rosterGroupRenamed(QString oldName, QString newName);
    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    /*public*/ void addRosterGroup(RosterGroup* rg);
    /*public*/ void addRosterGroup(QString str);
    /*public*/ QString getRosterFilesLocation();
    /*public*/ void addRosterGroups(QList<RosterGroup*> groups);
    /*public*/ void removeRosterGroup(RosterGroup* rg);

signals:
    //void propertyChange(QString text, QObject* o, QObject* n);

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent *evt);
    /*public*/ void reloadRosterFile();


private:
 static Logger* log;
 void common();
 ///*private*/ UserPreferencesManager preferences;
 /*private*/ QString defaultRosterGroup;// = NULL;
 bool readFile(QString name);
 /*private*/ bool dirty;// = false;
 /**
  * Internal interface works with #findMatchingEntries to provide a common
  * search-match-return capability.
  */
 /*private*/ /*interface*/class  RosterComparator {
   Roster* r;
  public:
   RosterComparator(Roster* r) {this->r = r;}
     ///*public*/ bool check(RosterEntry* r);
     #if 0
     return r->checkEntry(r, roadName, roadNumber, dccAddress,
                           mfg, decoderModel, decoderFamily,
                           id, group, developerID, manufacturerID, productID);
#endif
 };
 /*private*/ QList<RosterEntry*> findMatchingEntries(RosterComparator c);
 /*
  * This should only be non-null if explictly set to a non-default location.
  */
 /*private*/ QString rosterLocation;// = null;
 void setDirty(bool b) {dirty = b;}
 bool isDirty() {return dirty;}
 QDomDocument doc;
 /*private*/ static QString rosterFileName;// = "roster.xml";
 /*private*/ static QString fileLocation;//  = FileUtil.getUserFilesPath();
  /*private*/ void delRosterGroupList(QString rg, bool notify);
  static QStringList getAllFileNames();
  /*private*/ /*final*/ QMap<QString, RosterGroup*> rosterGroups;// = new HashMap<>();
  QString rosterIndexFileName;
  QMutex mutex;

protected:
 /**
  * List of contained {@link RosterEntry} elements.
  */
 /*protected*/ QList<RosterEntry*>* _list;// = new QList<RosterEntry*>();
  /*protected*/ QVector<QString> _rosterGroupList;// = new ArrayList<QString>();

  friend class RosterTest;
};

class RosterPropertyChangeListener : public PropertyChangeListener
{
 Q_OBJECT
 Roster* roster;
public:
 RosterPropertyChangeListener(Roster* roster) { this->roster = roster;}

public slots:
 void propertyChange(PropertyChangeEvent*);
};
#endif // ROSTER_H
