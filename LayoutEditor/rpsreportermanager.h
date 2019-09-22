#ifndef RPSREPORTERMANAGER_H
#define RPSREPORTERMANAGER_H
#include "abstractreportermanager.h"

class RpsSystemConnectionMemo;
class RpsReporterManager : public AbstractReporterManager
{
public:
 RpsReporterManager(RpsSystemConnectionMemo* memo, QObject* parent = 0);
 //static RpsReporterManager* _instance;// = NULL;
 //static /*public*/ RpsReporterManager* instance();
 /*public*/ QString getSystemPrefix();
 /*public*/ SystemConnectionMemo* getMemo();

protected:
 /*protected*/ Reporter* createNewReporter(QString systemName, QString userName);

};

#endif // RPSREPORTERMANAGER_H
