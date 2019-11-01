#ifndef LNSENSORADDRESSTEST_H
#define LNSENSORADDRESSTEST_H

#include <QObject>
#include "lnsensoraddress.h"

class Logger;
class LnSensorAddressTest : public QObject
{
 Q_OBJECT
public:
 explicit LnSensorAddressTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();


signals:

public slots:
 /*public*/ void testLnSensorAddressCreate();
 /*public*/ void testLnSensorInvalid();
 /*public*/ void testLnSensorAddressASmode();
 /*public*/ void testLnSensorAddressNumericMode();
 /*public*/ void testLnSensorAddressBDL16Mode();
 /*public*/ void testLnSensorAddressFromPacket() ;

private:
 static Logger* log;
};

class LnSensorAddressO1 : public LnSensorAddress
{
 Q_OBJECT
 LnSensorAddressTest* test;
public:
 LnSensorAddressO1(QString s, QString prefix,   LnSensorAddressTest* test)
  : LnSensorAddress(s, prefix) {this->test = test;}
 void reportParseError(QString s) {}
};
#endif // LNSENSORADDRESSTEST_H
