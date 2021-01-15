#ifndef SYSTEMCONNECTIONMEMOTESTBASE_H
#define SYSTEMCONNECTIONMEMOTESTBASE_H

#include <QObject>
#include "defaultsystemconnectionmemo.h"
#include "resourcebundle.h"

class SystemConnectionMemoTestBase : public QObject
{
 Q_OBJECT
public:
 explicit SystemConnectionMemoTestBase(QObject *parent = nullptr);
 /*abstract*/ virtual /*public*/ void setUp() = 0;
 /*abstract*/ virtual /*public*/ void tearDown() = 0;
 /*public*/ void getTest(QString t);

signals:

public slots:
 /*public*/ void getPowerManager();
 /*public*/ void getTurnoutManager();
 /*public*/ void getThrottleManager();
 /*public*/ void getSensorManager();
 /*public*/ void getLightManager();
 /*public*/ void getReporterManager();
 /*public*/ void testCtor();
 /*public*/ void testProvidesConsistManager();
 /*public*/ void testGetAndSetPrefix();
 /*public*/ void testMultipleMemosSamePrefix();

protected:
 /*protected*/ SystemConnectionMemo* scm = nullptr;

};

class SystemConnectionMemoO1 : public DefaultSystemConnectionMemo
{
 Q_OBJECT
 SystemConnectionMemoTestBase* base;
public:
 SystemConnectionMemoO1(QString prefix, QString userName, SystemConnectionMemoTestBase* base)
  : DefaultSystemConnectionMemo(prefix, userName)
 {this->base = base;}
protected:

 //@Override
 /*protected*/ ResourceBundle* getActionModelResourceBundle() {
     return nullptr;
 }

};
#endif // SYSTEMCONNECTIONMEMOTESTBASE_H
