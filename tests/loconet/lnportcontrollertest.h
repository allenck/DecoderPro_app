#ifndef LNPORTCONTROLLERTEST_H
#define LNPORTCONTROLLERTEST_H

#include <QObject>
#include "abstractserialportcontrollertestbase.h"
#include "lnportcontroller.h"

class LocoNetSystemConnectionMemo;
class LnPortControllerTest : public AbstractSerialPortControllerTestBase
{
    Q_OBJECT
public:
    explicit LnPortControllerTest(QObject *parent = nullptr);
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:

private:
    /*private*/ LocoNetSystemConnectionMemo* memo;
    LnPortController* apc;

};

class LnPortControllerO2 : public LnPortController
{
    Q_OBJECT
    LnPortControllerTest* lpct;
public:
    LnPortControllerO2(LocoNetSystemConnectionMemo* memo, LnPortControllerTest* lpct) : LnPortController(memo) {this->lpct = lpct;}
    //@Override
    /*public*/ bool status(){
      return true;
    }

    //@Override
    /*public*/ void configure(){
    }

    //@Override
    /*public*/ QDataStream* getInputStream(){
        return nullptr;
    }

    //@Override
    /*public*/ QDataStream* getOutputStream(){
        return nullptr;
    }

    //@Override
    /*public*/ QStringList validBaudRates(){
       QStringList retval = {"9600"};
       return retval;
    }

    /**
     * Open a specified port. The appName argument is to be provided to the
     * underlying OS during startup so that it can show on status displays, etc
     */
    //@Override
    /*public*/ QString openPort(QString /*portName*/, QString /*appName*/){
       return "";
    }
};
#endif // LNPORTCONTROLLERTEST_H
