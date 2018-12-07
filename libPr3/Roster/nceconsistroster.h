#ifndef NCECONSISTROSTER_H
#define NCECONSISTROSTER_H
#include "xmlfile.h"

class PropertyChangeEvent;
class QComboBox;
class NceConsistRosterEntry;
class NceConsistRoster : public XmlFile
{
    Q_OBJECT
public:
    explicit NceConsistRoster(QObject *parent = 0);
//    /*public*/ /*synchronized*/ static void resetInstance();
    /*public*/ static /*synchronized*/ NceConsistRoster* instance();
    /*public*/ void addEntry(NceConsistRosterEntry* e) ;
    /*public*/ void removeEntry(NceConsistRosterEntry* e);
    /*public*/ int numEntries();
    /*public*/ QComboBox* fullRosterComboBox();
    /*public*/ QComboBox* matchingComboBox(QString roadName, QString roadNumber,
            QString consistNumber, QString eng1Address, QString eng2Address,
            QString eng3Address, QString eng4Address, QString eng5Address,
            QString eng6Address, QString id);
    /*public*/ void updateComboBox(QComboBox* box);
    /*public*/ NceConsistRosterEntry* entryFromTitle(QString title );
    /*public*/ QList<NceConsistRosterEntry*> matchingList(QString roadName, QString roadNumber,
            QString consistNumber, QString eng1Address, QString eng2Address,
            QString eng3Address, QString eng4Address, QString eng5Address,
            QString eng6Address, QString id);
    /*public*/ bool checkEntry(int i, QString roadName, QString roadNumber,
            QString consistNumber, QString loco1Address, QString loco2Address,
            QString loco3Address, QString loco4Address, QString loco5Address,
            QString loco6Address, QString id );
    /*public*/ void dispose();
    /*public*/ void writeRosterFile();
    /*public*/ void reloadRosterFile();
    /*public*/ static QString defaultNceConsistRosterFilename();
    /*public*/ /*static*/ void setNceConsistRosterFileName(QString name);
    /*public*/ void entryIdChanged(NceConsistRosterEntry* r);
    Q_INVOKABLE /*public*/ void initialize();

signals:
    void propertyChange(PropertyChangeEvent*);
public slots:
private:
    /** record the single instance of Roster **/
    ///*private*/ static NceConsistRoster* _instance;// = NULL;
    void writeFile(QString name) throw (FileNotFoundException, IOException);
    void readFile(QString name) throw (JDOMException, IOException);
    /*private*/ bool dirty;// = false;
    void setDirty(bool b);
    bool isDirty();
    /*private*/ static QString NceConsistRosterFileName;// = "ConsistRoster.xml";
    Logger* log;
protected:
    /**
     * List of contained RosterEntry elements.
     */
    /*protected*/ QList<NceConsistRosterEntry*> _list;// = new QList<NceConsistRosterEntry*>();
    /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

};

#endif // NCECONSISTROSTER_H
