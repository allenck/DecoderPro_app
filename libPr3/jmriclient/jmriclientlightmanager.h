#ifndef JMRICLIENTLIGHTMANAGER_H
#define JMRICLIENTLIGHTMANAGER_H
#include "abstractlightmanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientLightManager : public AbstractLightManager
{
public:
 JMRIClientLightManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr );
 /*public*/ QString getSystemPrefix();
 /*public*/ Light* createNewLight(QString systemName, QString userName);
 /*public*/ NameValidity validSystemNameFormat(QString systemName);
 /*public*/ bool validSystemNameConfig(QString systemName);

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTLIGHTMANAGER_H
