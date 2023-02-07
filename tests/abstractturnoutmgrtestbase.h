#ifndef ABSTRACTTURNOUTMGRTESTBASE_H
#define ABSTRACTTURNOUTMGRTESTBASE_H

#include <QObject>
#include "propertychangelistener.h"
#include "abstractprovidingturnoutmanagertestbase.h"

class ProxyTurnoutManager;
class AbstractTurnoutMgrTestBase : public AbstractProvidingTurnoutManagerTestBase
{
    Q_OBJECT
public:
    explicit AbstractTurnoutMgrTestBase(QObject *parent = nullptr);
    virtual /*public*/ QString getSystemName(int i) = 0;
    virtual /*public*/ void setUp()  = 0;

signals:

public slots:
 /*public*/ void testCreate();
 /*public*/ void testDispose();
 /*public*/ void testProvideFailure();
 /*public*/ void testTurnoutPutGet();
 /*public*/ void testProvideName();
  /*public*/ void testProvideWithoutWithPrefix() /*throws IllegalArgumentException */;
  /*public*/ void testProvideWithWithoutPrefix() /*throws IllegalArgumentException*/;
  /*public*/ void testProvideFailWithPrefix() /*throws IllegalArgumentException*/;

 /*public*/ void testDefaultSystemName();
 /*public*/ void testSingleObject();
 /*public*/ virtual void testMisses();
 /*public*/ void testUpperLower();
 /*public*/ void testRename();
 /*public*/ void testThrownText();
 /*public*/ void testClosedText();
  /*public*/ virtual void testSetAndGetOutputInterval();
  /*public*/ void testAutoSystemNames() override;
  /*public*/ void testGetEntryToolTip();
  /*public*/ void testGetNextValidAddress() /*throws JmriException*/;
  /*public*/ void testIncorrectGetNextValidAddress();

private:
    static /*protected*/ bool listenerResult;// = false;
    TurnoutManager* l = nullptr;

protected:
    /*protected*/ int getNumToTest1();
    /*protected*/ int getNumToTest2();
 friend class ListenO4;
 friend class LnTurnoutManagerTest;
 friend class InternalTurnoutManagerTest;
};

class ListenO4 : public QObject, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)AbstractTurnoutMgrTestBase* base;
public:
    ListenO4(AbstractTurnoutMgrTestBase* base) {this->base = base;}
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* /*e*/) {
        base->listenerResult = true;
    }
QObject* self() {return (QObject*)this;}
};

#endif // ABSTRACTTURNOUTMGRTESTBASE_H
