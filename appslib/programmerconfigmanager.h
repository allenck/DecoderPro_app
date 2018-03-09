#ifndef PROGRAMMERCONFIGMANAGER_H
#define PROGRAMMERCONFIGMANAGER_H
#include "abstractpreferencesmanager.h"

class Logger;
class ProgrammerConfigManager : public AbstractPreferencesManager
{
 Q_OBJECT
public:
 ProgrammerConfigManager();
 ~ProgrammerConfigManager() {}
 ProgrammerConfigManager(const ProgrammerConfigManager&) : AbstractPreferencesManager() {}
 /*public*/ /*final*/ static QString DEFAULT_FILE;// = "defaultFile";
 /*public*/ /*final*/ static QString SHOW_EMPTY_PANES;// = "showEmptyPanes";
 /*public*/ /*final*/ static QString SHOW_CV_NUMBERS;// = "showCvNumbers";
 /*public*/ /*final*/ static QString CAN_CACHE_DEFAULT;// = "canCacheDefault";
 /*public*/ /*final*/ static QString DO_CONFIRM_READ;// = "doConfirmRead";

 /*public*/ void initialize(Profile* profile)throw (InitializationException);
 /*public*/ QSet<QString>* getRequires();
 /*public*/ QSet<QString>* getProvides();
 /*public*/ void savePreferences(Profile* profile);
 /*public*/ QString getDefaultFile();
 /*public*/ void setDefaultFile(QString defaultFile);
 /*public*/ bool isShowEmptyPanes();
 /*public*/ void setShowEmptyPanes(bool showEmptyPanes);
 /*public*/ bool isShowCvNumbers();
 /*public*/ void setShowCvNumbers(bool showCvNumbers);
 /*public*/ bool isCanCacheDefault();
 /*public*/ void setCanCacheDefault(bool canCacheDefault);
 /*public*/ bool isDoConfirmRead() ;
 /*public*/ void setDoConfirmRead(bool doConfirmRead);


private:
 Logger* log;
 /*private*/ QString defaultFile;// = NULL;
 /*private*/ bool showEmptyPanes;// = true;
 /*private*/ bool showCvNumbers;// = false;
 /*private*/ bool doConfirmRead;// = false;
 /*private*/ bool canCacheDefault;// = false;


};
Q_DECLARE_METATYPE(ProgrammerConfigManager)
#endif // PROGRAMMERCONFIGMANAGER_H
