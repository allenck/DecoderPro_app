#ifndef ROSTERCONFIGMANAGER_H
#define ROSTERCONFIGMANAGER_H
#include "abstractpreferencesmanager.h"
#include "propertychangeevent.h"

class Logger;
class RosterConfigManager : public AbstractPreferencesManager
{
 Q_OBJECT
public:
 RosterConfigManager();
 ~RosterConfigManager() {}
 RosterConfigManager(const RosterConfigManager&): AbstractPreferencesManager() {}
 /*public*/ static /*final*/ QString DIRECTORY;// = "directory";
 /*public*/ static /*final*/ QString DEFAULT_OWNER;// = "defaultOwner";
 /*public*/ void initialize(Profile* profile)throw (InitializationException);
 /*public*/ void savePreferences(Profile* profile);
 /*public*/ /*Set<Class<? extends PreferencesManager>>*/ QSet<QString>* getRequires();
 /*public*/ QString getDefaultOwner();
 /*public*/ void setDefaultOwner(QString defaultOwner);
 /*public*/ QString getDirectory();
 /*public*/ void setDirectory(QString directory);

public slots:
 void onPropertyChange(PropertyChangeEvent*);

private:
 Logger* log;
 /*private*/ QString directory;// = FileUtil.PREFERENCES;
 /*private*/ QString defaultOwner;// = "";

};
Q_DECLARE_METATYPE(RosterConfigManager)

#endif // ROSTERCONFIGMANAGER_H
