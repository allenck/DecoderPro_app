#ifndef WARRANTMANAGER_H
#define WARRANTMANAGER_H
#include "abstractmanager.h"
#include "libPr3_global.h"

class OBlock;
class OPath;
class Portal;
class RosterSpeedProfile;
class Warrant;
class LIBPR3SHARED_EXPORT WarrantManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit WarrantManager(QObject *parent = 0);
    ~WarrantManager() {}
    WarrantManager(const WarrantManager&) : AbstractManager() {}
    /*public*/ int getXMLOrder()const override;
    /*public*/ QString getSystemPrefix()const override;
    /*public*/ char typeLetter() const override;
    /*public*/ Warrant* createNewWarrant(QString systemName, QString userName, bool SCWa, long TTP);
    /*public*/ Warrant* getWarrant(QString name);
    /*public*/ Warrant* getBySystemName(QString name)const ;
    /*public*/ Warrant* getByUserName(QString key)const ;
    /*public*/ Warrant* provideWarrant(QString name) ;
    /*public*/ bool isAssignableFromType() {return true;}
    /*public*/ QString getNamedBeanClass()const override {
        return "Warrant";
    }
    /*public*/ static WarrantManager* getDefault();
    /*public*/ QString getBeanTypeHandled(bool plural);
    /*public*/ QString getNamedBeanClass();

signals:
 void propertyChange(PropertyChangeEvent *e);
private:
 static Logger* log;
 /*private*/ QMap<QString, RosterSpeedProfile*>* _mergeProfiles = nullptr;
 /*private*/ QMap<QString, RosterSpeedProfile*>* _sessionProfiles = nullptr;
 /*private*/ bool _suppressWarnings = false;
 /*private*/ void removeWarrants(QList<Warrant*> list);
 /*private*/ bool okToRemove(QString name, QString message);

public slots:

protected:
 /*protected*/ RosterSpeedProfile* getMergeProfile(QString id);
 /*protected*/ RosterSpeedProfile* getSessionProfile(QString id);
 /*protected*/ void setSpeedProfiles(QString id, RosterSpeedProfile* merge, RosterSpeedProfile* session);
 /*protected*/ QMap<QString, RosterSpeedProfile*>* getMergeProfiles();
 /*protected*/ QMap<QString, RosterSpeedProfile*>* getSessionProfiles();
 /*protected*/ bool okToRemoveBlock(OBlock* block);
 /*protected*/ bool okToRemovePortal(Portal* portal);
 /*protected*/ bool okToRemoveBlockPath(OBlock* block, OPath* path);
 /*synchronized*/ /*protected*/ void portalNameChange(QString oldName, QString newName);
 /*protected*/ QList<Warrant*> warrantsUsing(OBlock* block);
 /*protected*/QList<Warrant*> warrantsUsing(Portal* portal);
 /*protected*/ QList<NamedBean*> signalsUsing(Portal* portal);
 /*protected*/ QList<Warrant*> warrantsUsing(OBlock* block, OPath* path);
 /*synchronized*/ /*protected*/ void pathNameChange(OBlock* block, QString oldName, QString newName);

 friend class SpeedUtil;
 friend class WarrantShutdownTask;
 friend class MergePrompt;
 friend class Portal;
 friend class OBlock;
};
Q_DECLARE_METATYPE(WarrantManager)
#endif // WARRANTMANAGER_H
