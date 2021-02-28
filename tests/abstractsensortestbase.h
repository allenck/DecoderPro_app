#ifndef ABSTRACTSENSORTESTBASE_H
#define ABSTRACTSENSORTESTBASE_H

#include <QObject>
#include "propertychangelistener.h"
#include "exceptions.h"
#include "junitutil.h"
#include "abstractsensor.h"


class AbstractSensor;
class AbstractSensorTestBase : public QObject
{
    Q_OBJECT
public:
    explicit AbstractSensorTestBase(QObject *parent = nullptr);
    virtual /*public*/ int numListeners()=0;
    virtual /*public*/ void checkOnMsgSent()=0;
    virtual /*public*/ void checkOffMsgSent()=0;
    virtual /*public*/ void checkStatusRequestMsgSent()=0;
    virtual /*public*/ void setUp()=0; // load t with actual object; create scaffolds as needed
    virtual /*public*/ void tearDown()=0;
    virtual /*public*/ QString getSystemName(int i) {return "";}
    // start of common tests
    // test creation - real work is in the setup() routine

public slots:
    /*public*/ void testCreate();
    /*public*/ void testAddListener() throw (JmriException);
    /*public*/ void testRemoveListener();
    /*public*/ void testDispose() throw (JmriException);
    /*public*/ void testCommandInactive() throw (JmriException);
    /*public*/ void testCommandActive() throw (JmriException);
    /*public*/ void testInvertAfterInactive() throw (JmriException) ;
    /*public*/ void testInvertAfterActive() throw (JmriException);
    /*public*/ void testDebounceSettings() throw (JmriException) ;
    /*public*/ void testDebounce() throw (JmriException);
    /*public*/ void testGetPullResistance();
    /*public*/ void testGetBeanType();
    /*public*/ void testSensorStatusRequest();
    /*public*/ void testSensor() throw (JmriException);
signals:

public slots:
protected:
    /*protected*/ AbstractSensor* t = nullptr;	// holds object under test; set by setUp()
    static /*protected*/ bool listenerResult;// = false;
 friend class ListenO2;
 friend class ReleaseUntilO8;
 friend class ReleaseUntilO9;
};

/*protected*/ class ListenO2 : public QObject, public PropertyChangeListener {
Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
    AbstractSensorTestBase* test;
public:
    ListenO2(AbstractSensorTestBase* test) {this->test = test;}
QObject* self() {return (QObject*)this;}public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};

class  ReleaseUntilO8 : public ReleaseUntil
{
    Q_OBJECT
    AbstractSensorTestBase* test;
    int i;
public:
    ReleaseUntilO8(AbstractSensorTestBase* test) {this->i = i; this->test = test;}
    bool ready() throw (Exception) {return test->t->getState() == test->t->getRawState();}
};

class  ReleaseUntilO9 : public ReleaseUntil
{
    Q_OBJECT
    AbstractSensorTestBase* test;
    int i;
public:
    ReleaseUntilO9(int i, AbstractSensorTestBase* test)
    {
     this->i = i;
     this->test = test;
    }
    bool ready() throw (Exception) {return test->t->getState() == i;}
};

#endif // ABSTRACTSENSORTESTBASE_H
