#ifndef FILELOCATIONSPREFERENCES_H
#define FILELOCATIONSPREFERENCES_H
#include "abstractpreferencesmanager.h"
#include <QSet>

class FileLocationsPreferences : public AbstractPreferencesManager
{
 Q_OBJECT
public:
 Q_INVOKABLE FileLocationsPreferences();
 ~FileLocationsPreferences() {}
 FileLocationsPreferences(const FileLocationsPreferences&) :AbstractPreferencesManager() {}
 /*public*/ static /*final*/ QString USER_FILES;// = "user-files"; // NOI18N
 /*public*/ static /*final*/ QString SCRIPTS;// = "scripts"; // NOI18N
 /*public*/ static /*final*/ QString JMRIPROGRAM;// = "scripts"; // NOI18N
 Q_INVOKABLE /*public*/ void initialize(Profile* profile)/*throw (InitializationException)*/override;
 /*public*/ QSet<QString/* extends PreferencesManager*/> getRequires()override;
 /*public*/ void savePreferences(Profile* profile)override;

 QObject* self() override {return (QObject*)this;}

};
Q_DECLARE_METATYPE(FileLocationsPreferences)
#endif // FILELOCATIONSPREFERENCES_H
