#ifndef PROXYTURNOUTMANAGERTEST_H
#define PROXYTURNOUTMANAGERTEST_H

#include <QObject>
#include "propertychangelistener.h"

class TurnoutManager;
class ProxyTurnoutManagerTest : public QObject
{
 Q_OBJECT
public:
 explicit ProxyTurnoutManagerTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ QString getSystemName(int i);

signals:

public slots:
 /*public*/ void testDispose();
 /*public*/ void testPutGet();
 /*public*/ void testDefaultSystemName();
 /*public*/ void testProvideFailure();
 /*public*/ void testSingleObject();
 /*public*/ void testMisses();
 /*public*/ void testUpperLower();
 /*public*/ void testRename();
 /*public*/ void testTwoNames();
 /*public*/ void testDefaultNotInternal();
 /*public*/ void testProvideUser();
 /*public*/ void testInstanceManagerIntegration();

protected:
 /*protected*/ TurnoutManager* l = nullptr;	// holds objects under test
 static /*protected*/ bool listenerResult;// = false;
 /*protected*/ int getNumToTest1();
 /*protected*/ int getNumToTest2();

 friend class ListenO5;
};

/*protected*/ class ListenO5 : public QObject, public PropertyChangeListener {
Q_OBJECT
 Q_INTERFACES(PropertyChangeListener)ProxyTurnoutManagerTest* test;
public:
 ListenO5(ProxyTurnoutManagerTest* test) {this->test = test;}
QObject* self() {return (QObject*)this;}public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};

#endif // PROXYTURNOUTMANAGERTEST_H
