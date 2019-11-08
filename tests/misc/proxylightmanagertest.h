#ifndef PROXYLIGHTMANAGERTEST_H
#define PROXYLIGHTMANAGERTEST_H

#include <QObject>
#include "propertychangelistener.h"
#include "exceptions.h"
class LightManager;
class ProxyLightManagerTest : public QObject
{
 Q_OBJECT
public:
 explicit ProxyLightManagerTest(QObject *parent = nullptr);
 /*public*/ QString getSystemName(int i);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testDispose();
 /*public*/ void testLightPutGet();
 /*public*/ void testDefaultSystemName();
 /*public*/ void testProvideFailure() throw (IllegalAccessException);
 /*public*/ void testSingleObject();
 /*public*/ void testMisses();
 /*public*/ void testUpperLower();
 /*public*/ void testRename();
 /*public*/ void testTwoNames();
 /*public*/ void testDefaultNotInternal();
 /*public*/ void testProvideUser();
 /*public*/ void testInstanceManagerIntegration();

private:


protected:
 /*protected*/ LightManager* l = nullptr;	// holds objects under test
 static /*protected*/ bool listenerResult;// = false;
 /*protected*/ int getNumToTest1();
 /*protected*/ int getNumToTest2();

 friend class ListenO7;
};

class ListenO7 : public PropertyChangeListener
{
 Q_OBJECT
 ProxyLightManagerTest* test;
public:
 ListenO7(ProxyLightManagerTest* test) {this->test = test;}
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

};
#endif // PROXYLIGHTMANAGERTEST_H
