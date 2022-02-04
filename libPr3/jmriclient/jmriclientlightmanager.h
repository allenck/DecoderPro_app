#ifndef JMRICLIENTLIGHTMANAGER_H
#define JMRICLIENTLIGHTMANAGER_H
#include "abstractlightmanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientLightManager : public AbstractLightManager
{
public:
 JMRIClientLightManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr );
 /*public*/ QString getSystemPrefix() const override;
 /*public*/ Light* createNewLight(QString systemName, QString userName)override;
 /*public*/ NameValidity validSystemNameFormat(QString systemName) override;
 /*public*/ bool validSystemNameConfig(QString systemName) override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Light";
 }
 /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTLIGHTMANAGER_H
