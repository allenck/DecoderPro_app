#ifndef RPSREPORTERMANAGER_H
#define RPSREPORTERMANAGER_H
#include "abstractreportermanager.h"

class RpsSystemConnectionMemo;
class RpsReporterManager : public AbstractReporterManager
{
public:
 RpsReporterManager(RpsSystemConnectionMemo* memo, QObject* parent = 0);
 /*public*/ SystemConnectionMemo* getMemo() const override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix) throw (JmriException);
 /*public*/ QString validateSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale);
 /*public*/ RpsReporterManager::NameValidity validSystemNameFormat(/*@Nonnull*/ QString systemName);
 /*public*/ QString getEntryToolTip();
 /*public*/ QString getNamedBeanClass()const override {
     return "Reporter";
 }

 private:
 static Logger* log;

protected:
 /*protected*/ Reporter* createNewReporter(QString systemName, QString userName)const override;

};

#endif // RPSREPORTERMANAGER_H
