#ifndef RPSSYSTEMCONNECTIONMEMO_H
#define RPSSYSTEMCONNECTIONMEMO_H
#include "systemconnectionmemo.h"
#include "manager.h"

class RpsReporterManager;
class RpsSensorManager;
class RpsSystemConnectionMemo : public SystemConnectionMemo
{
public:
 /*public*/ RpsSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString name, QObject* parent = nullptr);
 /*public*/ RpsSystemConnectionMemo( QObject* parent = nullptr);
 /*public*/ void configureManagers();
 /*public*/ RpsSensorManager* getSensorManager();
 /*public*/ RpsReporterManager* getReporterManager();
 /*public*/ bool provides(/*Class<?>*/QString type);
 /*public*/ Manager* get(QString T);
 /*public*/ QString validateSystemNameFormat(QString name, Manager* manager, QLocale locale);
 /*public*/ Manager::NameValidity validSystemNameFormat(QString systemName, char type);

private:
 static Logger* log;

private:
 /**
  * Provide access to the SensorManager for this particular connection.
  */
 /*private*/ RpsSensorManager* sensorManager = nullptr;
 /*private*/ RpsReporterManager* reporterManager = nullptr;

protected:
 /*protected*/ ResourceBundle* getActionModelResourceBundle();

};

#endif // RPSSYSTEMCONNECTIONMEMO_H
