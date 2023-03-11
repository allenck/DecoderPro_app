#ifndef RPSREPORTERMANAGER_H
#define RPSREPORTERMANAGER_H
#include "abstractreportermanager.h"

class RpsSystemConnectionMemo;
class RpsReporterManager : public AbstractReporterManager
{
public:
 RpsReporterManager(RpsSystemConnectionMemo* memo, QObject* parent = 0);
 /*public*/ SystemConnectionMemo* getMemo()  override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix) /*throw (JmriException)*/override;
 /*public*/ QString validateSystemNameFormat(/*@Nonnull*/ QString name, /*@Nonnull*/ QLocale locale)  override;
 /*public*/ RpsReporterManager::NameValidity validSystemNameFormat(/*@Nonnull*/ QString systemName) override;
 /*public*/ QString getEntryToolTip()override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Reporter";
 }
 QObject* self() override{return (QObject*)this;}
 QObject* vself() override {return (QObject*)this;}
 QObject* pself() override{return (QObject*)this;}

 void addPropertyChangeListener(PropertyChangeListener* l) override {PropertyChangeSupport::addPropertyChangeListener(l);}

 private:
 static Logger* log;

protected:
 /*protected*/ Reporter* createNewReporter(QString systemName, QString userName) override;

};

#endif // RPSREPORTERMANAGER_H
