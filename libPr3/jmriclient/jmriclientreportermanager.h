#ifndef JMRICLIENTREPORTERMANAGER_H
#define JMRICLIENTREPORTERMANAGER_H
#include "abstractreportermanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientReporterManager : public AbstractReporterManager
{
public:
 JMRIClientReporterManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ QString getSystemPrefix() const override;
 /*public*/ Reporter* createNewReporter(QString systemName, QString userName) override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Reporter";
 }
 /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}

 QObject* self() override {return (QObject*)this;}
 QObject* vself() override { return (QObject*)this;}

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTREPORTERMANAGER_H
