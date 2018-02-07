#ifndef RPSREPORTERMANAGER_H
#define RPSREPORTERMANAGER_H
#include "abstractreportermanager.h"

class RpsReporterManager : public AbstractReporterManager
{
public:
 RpsReporterManager(QObject* parent = 0);
 static RpsReporterManager* _instance;// = NULL;
 static /*public*/ RpsReporterManager* instance();
 /*public*/ QString getSystemPrefix();

protected:
 /*protected*/ Reporter* createNewReporter(QString systemName, QString userName);

};

#endif // RPSREPORTERMANAGER_H
