#ifndef PROGRAMMERCONFIGMANAGER_H
#define PROGRAMMERCONFIGMANAGER_H
#include "abstractpreferencesmanager.h"

class Logger;
class ProgrammerConfigManager : public AbstractPreferencesManager
{
public:
 ProgrammerConfigManager();
 ~ProgrammerConfigManager() {}
 ProgrammerConfigManager(const ProgrammerConfigManager&) : AbstractPreferencesManager() {}
 /*public*/ /*final*/ static QString DEFAULT_FILE;// = "defaultFile";
 /*public*/ /*final*/ static QString SHOW_EMPTY_PANES;// = "showEmptyPanes";
 /*public*/ /*final*/ static QString SHOW_CV_NUMBERS;// = "showCvNumbers";
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


private:
 Logger* log;
 /*private*/ QString defaultFile;// = NULL;
 /*private*/ bool showEmptyPanes;// = true;
 /*private*/ bool showCvNumbers;// = false;

};
Q_DECLARE_METATYPE(ProgrammerConfigManager)
#endif // PROGRAMMERCONFIGMANAGER_H
