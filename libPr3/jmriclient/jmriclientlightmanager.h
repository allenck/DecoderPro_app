#ifndef JMRICLIENTLIGHTMANAGER_H
#define JMRICLIENTLIGHTMANAGER_H
#include "abstractlightmanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientLightManager : public AbstractLightManager
{
public:
 JMRIClientLightManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr );
 /*public*/ QString getSystemPrefix()const override;
 /*public*/ Light* createNewLight(QString systemName, QString userName)override;
 /*public*/ NameValidity validSystemNameFormat(QString systemName)const override;
 /*public*/ bool validSystemNameConfig(QString systemName)const override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Light";
 }

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTLIGHTMANAGER_H
