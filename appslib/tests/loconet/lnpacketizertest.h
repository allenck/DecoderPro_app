#ifndef LNPACKETIZERTEST_H
#define LNPACKETIZERTEST_H

#include <QObject>
#include "lnportcontroller.h"

class LnPacketizer;
class LocoNetSystemConnectionMemo;
class LnPacketizerTest : public QObject
{
    Q_OBJECT
public:
    explicit LnPacketizerTest(QObject *parent = nullptr);
    /*public*/ void testCtor();
    /*public*/ void testStatusWithoutInit();
    /*public*/ void testStartThreads();
    /*public*/ void setUp();
    /*public*/ void tearDown();

signals:

public slots:
protected:
    /*protected*/ LnPacketizer* lnp;
    /*protected*/ LocoNetSystemConnectionMemo* memo;

};

class LnPortControllerO1 : public LnPortController
{
 Q_OBJECT
    LnPacketizerTest* lnpt;
public:
    LnPortControllerO1(LocoNetSystemConnectionMemo* memo, LnPacketizerTest* lnpt, QObject* parent = 0) : LnPortController(memo,  parent){this->lnpt = lnpt;}
    //@Override
    /*public*/ bool status(){
      return true;
    }
    //@Override
    /*public*/ void configure(){
    }
//    //@Override
//    /*public*/ DataInputStream getInputStream(){
//        return new DataInputStream(new ByteArrayInputStream(new byte[0]));
//    }
//    //@Override
//    /*public*/ DataOutputStream getOutputStream(){
//        return new DataOutputStream(new ByteArrayOutputStream());
//    }

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
    /*public*/ QString openPort(QString portName, QString appName){
       return "";
    }
};

#endif // LNPACKETIZERTEST_H
