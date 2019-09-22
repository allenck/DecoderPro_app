#ifndef ABSTRACTTURNOUTMGRTESTBASE_H
#define ABSTRACTTURNOUTMGRTESTBASE_H

#include <QObject>
#include "propertychangelistener.h"

class AbstractTurnoutMgrTestBase : public QObject
{
    Q_OBJECT
public:
    explicit AbstractTurnoutMgrTestBase(QObject *parent = nullptr);
    virtual /*public*/ QString getSystemName(int i) = 0;
    virtual /*public*/ void setUp() = 0;
    /*public*/ void testCreate();
    /*public*/ void testDispose();
    /*public*/ void testProvideFailure();
    /*public*/ void testTurnoutPutGet();
    /*public*/ void testProvideName();
    /*public*/ void testDefaultSystemName();
    /*public*/ void testSingleObject();
    /*public*/ void testMisses();
    /*public*/ void testUpperLower();
    /*public*/ void testRename();
    /*public*/ void testThrownText();
    /*public*/ void testClosedText();

signals:

public slots:
private:
    static /*protected*/ bool listenerResult;// = false;

protected:
    /*protected*/ int getNumToTest1();
    /*protected*/ int getNumToTest2();

};
class ListenO1 : public PropertyChangeListener
{
    Q_OBJECT
    AbstractTurnoutMgrTestBase* base;
public:
    ListenO1(AbstractTurnoutMgrTestBase* base) {this->base = base;}
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e) {
        base->listenerResult = true;
    }
};

#endif // ABSTRACTTURNOUTMGRTESTBASE_H
