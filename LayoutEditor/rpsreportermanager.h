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
 /*public*/ QString getSystemPrefix()const override;
 /*public*/ SystemConnectionMemo* getMemo() override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Reporter";
 }

protected:
 /*protected*/ Reporter* createNewReporter(QString systemName, QString userName)const override;

};

#endif // RPSREPORTERMANAGER_H
