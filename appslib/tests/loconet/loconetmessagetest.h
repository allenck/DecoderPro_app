#ifndef LOCONETMESSAGETEST_H
#define LOCONETMESSAGETEST_H

#include <QObject>

class LocoNetMessage;
class LocoNetMessageTest : public QObject
{
    Q_OBJECT
public:
    explicit LocoNetMessageTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();



signals:

public slots:
 /*public*/ void testCtor();
 /*public*/ void testArrayCtor();
 /*public*/ void testGetPeerXfr();
 /*public*/ void testConstructorNoParams();
 /*public*/ void testConstructorString();
 /*public*/ void testGetPeerXfrData();
 /*public*/ void testEqualsFromInt();
 /*public*/ void testEqualsFromBytes();
 /*public*/ void testEqualsFromString();
 /*public*/ void testEqualsSpecificCase();
 /*public*/ void testToString();
 /*public*/ void testToMonitorString();
 /*public*/ void testLowByte();
 /*public*/ void testHighByte();
 /*public*/ void testHighBit();
 /*public*/ void testInputRepAddr();
 /*public*/ void testSensorAddr();
 /*public*/ void testGetOpCodeHex();
 /*public*/ void testTurnoutAddr();
 /*public*/ void testGetElement();
 /*public*/ void testsetElement();
 /*public*/ void testHashCode();
 /*public*/ void testSetParity();
 /*public*/ void testCheckParity();

protected:
    /*protected*/ void checkPeerXfr(LocoNetMessage* m, int src, int dst, QVector<int> d, int code);

};

#endif // LOCONETMESSAGETEST_H
