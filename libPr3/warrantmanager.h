#ifndef WARRANTMANAGER_H
#define WARRANTMANAGER_H
#include "abstractmanager.h"
#include "libPr3_global.h"

class RosterSpeedProfile;
class Warrant;
class LIBPR3SHARED_EXPORT WarrantManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit WarrantManager(QObject *parent = 0);
    ~WarrantManager() {}
    WarrantManager(const WarrantManager&) : AbstractManager() {}
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter();
    /*public*/ Warrant* createNewWarrant(QString systemName, QString userName, bool SCWa, long TTP);
    /*public*/ Warrant* getWarrant(QString name);
    /*public*/ NamedBean* getBySystemName(QString name);
    /*public*/ NamedBean* getByUserName(QString key);
    /*public*/ Warrant* provideWarrant(QString name) ;
    static WarrantManager* _instance;// = NULL;
    static /*public*/ WarrantManager* instance();
    /*public*/ bool isAssignableFromType() {return true;}

signals:
 void propertyChange(PropertyChangeEvent *e);
private:
 static Logger* log;
 /*private*/ QMap<QString, RosterSpeedProfile*>* _mergeProfiles = nullptr;
 /*private*/ QMap<QString, RosterSpeedProfile*>* _sessionProfiles = nullptr;

public slots:

protected:
 /*protected*/ RosterSpeedProfile* getMergeProfile(QString id);
 /*protected*/ RosterSpeedProfile* getSessionProfile(QString id);
 /*protected*/ void setSpeedProfiles(QString id, RosterSpeedProfile* merge, RosterSpeedProfile* session);
 /*protected*/ QMap<QString, RosterSpeedProfile*>* getMergeProfiles();
 /*protected*/ QMap<QString, RosterSpeedProfile*>* getSessionProfiles();

 friend class SpeedUtil;
 friend class WarrantShutdownTask;
 friend class MergePrompt;
};
Q_DECLARE_METATYPE(WarrantManager)
#endif // WARRANTMANAGER_H
