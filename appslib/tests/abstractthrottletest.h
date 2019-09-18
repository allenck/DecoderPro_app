#ifndef ABSTRACTTHROTTLETEST_H
#define ABSTRACTTHROTTLETEST_H

#include <QObject>
#include "abstractthrottlemanager.h"
#include "abstractthrottle.h"

class AbstractThrottleTest : public QObject
{
    Q_OBJECT
public:
    explicit AbstractThrottleTest(QObject *parent = nullptr);
    /*public*/ void setUp() throw (Exception);
    /*public*/ void tearDown() throw (Exception);
    /*public*/ void testGetSpeedSetting();
    /*public*/ void testSetSpeedSettingAgain();
    /*public*/ void testSetSpeedSetting();
    /*public*/ void testGetIsForward();
    /*public*/ void testSetIsForward();
    /*public*/ void testGetF0();



signals:

public slots:

private:
    static Logger* log;

protected:
    /*protected*/ AbstractThrottle* instance = nullptr;


};
class AbstractThrottleManagerO1 : public AbstractThrottleManager
{
    Q_OBJECT
public:
    //@Override
    /*public*/ void requestThrottleSetup(LocoAddress* /*a*/, bool /*control*/) {
    }

    //@Override
    /*public*/ bool canBeLongAddress(int /*address*/) {
        return true;
    }

    //@Override
    /*public*/ bool canBeShortAddress(int /*address*/) {
        return true;
    }

    //@Override
    /*public*/ bool addressTypeUnique() {
        return true;
    }
};
/*public*/ /*final*/ class AbstractThrottleImpl /*extends*/ : public AbstractThrottle
{
Q_OBJECT
    /*private*/ LocoAddress* locoAddress;
private:
    /*public*/ AbstractThrottleImpl() : AbstractThrottle(nullptr){
        //super(null);
        this->setLocoAddress(new DccLocoAddress(3, LocoAddress::Protocol::DCC_SHORT));
    }

    //@Override
    /*public*/ void throttleDispose() {
    }

    /*public*/ void setLocoAddress(LocoAddress* locoAddress) {
        this->locoAddress = locoAddress;
    }

    //@Override
    /*public*/ LocoAddress* getLocoAddress() {
        return this->locoAddress;
    }
    friend class AbstractThrottleTest;
};

#endif // ABSTRACTTHROTTLETEST_H
