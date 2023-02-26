#ifndef ACTIONSENSORSWINGTEST_H
#define ACTIONSENSORSWINGTEST_H

#include "swingconfiguratorinterfacetestbase.h"
#include <QObject>
#include "junitutil.h"
#include "actionsensor.h"


class ActionSensorSwingTest : public SwingConfiguratorInterfaceTestBase
{
    Q_OBJECT
public:
    explicit ActionSensorSwingTest(QObject *parent = nullptr);
    Q_INVOKABLE /*public*/ void setUp();
    Q_INVOKABLE /*public*/ void tearDown();

public slots:
    /*public*/ void testCtor();
    /*public*/ void testCreatePanel();
    /*public*/ void testDialogUseExistingSensor() /*throws SocketAlreadyConnectedException*/;

};

class SensorWait : public ReleaseUntil
{
    Q_OBJECT
    ActionSensor* action;
public:
    SensorWait(ActionSensor* action) {this->action = action;}
    bool ready()
    {
        action->getSensor() != nullptr;
    }
};

#endif // ACTIONSENSORSWINGTEST_H
