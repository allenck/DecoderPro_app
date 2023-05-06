#ifndef CONFIGXMLMANAGERTEST_H
#define CONFIGXMLMANAGERTEST_H

#include <QObject>
#include "configxmlmanager.h"
#include "errorhandler.h"

class ConfigXmlManagerTest : public QObject
{
 Q_OBJECT
public:
 explicit ConfigXmlManagerTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testRegisterOK();
 /*public*/ void testLogErrorOnStore();
 /*public*/ void testFind() throw (ClassNotFoundException);
 /*public*/ void testDeregister();
 /*public*/ void testAdapterName();
 /*public*/ void testCurrentClassName();
 /*public*/ void testFindFile() throw (FileNotFoundException, IOException);

private:
 /*private*/ bool innerFlag;
 friend class ErrorHandlerO1;
};
class ConfigXmlManagerO1 : public ConfigXmlManager
{
 Q_OBJECT
public:
 //@SuppressWarnings("unused")
 //@Override
 void locateFailed(Throwable ex, QString adapterName, QObject* o) {
 }
};

class ConfigXmlManagerO2 : public ConfigXmlManager
{
 Q_OBJECT
 ConfigXmlManagerTest* test;
public:
 //@SuppressWarnings("unused")
 //@Override
 ConfigXmlManagerO2(ConfigXmlManagerTest* test){this->test = test;}
 void locateFailed(Throwable ex, QString adapterName, QObject* o) {
 }
 //@Override
 void locateFileFailed(QString f) {
     // suppress warning during testing
 }

};

class ErrorHandlerO1 : public ErrorHandler
{
 Q_OBJECT
 ConfigXmlManagerTest* test;
public:
 ErrorHandlerO1(ConfigXmlManagerTest* test) {this->test = test;}
 //@Override
 /*public*/ void handle(ErrorMemo* e) {
     test->innerFlag = true;
 }
};

class ConfigXmlHandle : public QObject
{

};
#endif // CONFIGXMLMANAGERTEST_H
