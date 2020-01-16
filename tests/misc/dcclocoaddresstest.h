#ifndef DCCLOCOADDRESSTEST_H
#define DCCLOCOADDRESSTEST_H

#include <QObject>


class DccLocoAddressTest : public QObject
{
 Q_OBJECT
public:
 explicit DccLocoAddressTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp() {}
 Q_INVOKABLE /*public*/ void tearDown() {}

signals:

public slots:
 /*public*/ void testValue1();
 /*public*/ void testValue2();
 /*public*/ void testValue3();
 /*public*/ void testCopy1();
 /*public*/ void testEquals1();
 /*public*/ void testEquals2();
 /*public*/ void testEquals3();
 /*public*/ void testEquals4();
 /*public*/ void testHash0();
 /*public*/ void testHash1();
 /*public*/ void testHash2();
 /*public*/ void testHash3();
 /*public*/ void testHash4();
 /*public*/ void testHash5();
 /*public*/ void testHash6();

};

class TestAddr
{
 //Q_OBJECT
public:
 TestAddr() {}
 //TestAddr(int num) {this->num = num;}
 ~TestAddr() {}
 TestAddr(const TestAddr&)  {}
private:
 int num = 0;
};

class  DccLocoAddressX //:  QObject//public LocoAddress
{
    //Q_OBJECT
public:
 DccLocoAddressX() {number=0; protocol = DCC_SHORT;}
 DccLocoAddressX(int number, bool isLong);
 enum Protocol {
             DCC_SHORT,
             DCC_LONG,  // NOI18N
             DCC,       // NOI18N
             SELECTRIX, // NOI18N
             MOTOROLA,  // NOI18N
             MFX,       // NOI18N
             M4,        // NOI18N
             OPENLCB,
             LGB
 };
    DccLocoAddressX(int number, Protocol protocol);
    DccLocoAddressX(const DccLocoAddressX& l ) ;
    bool operator ==(const DccLocoAddressX &a) ;
//    /*public*/ bool equals(QObject* a);
    int hashCode()const;
    QString toString() const;
    bool isLongAddress() const;
    Protocol getProtocol() const;
    int getNumber() const;
signals:

public slots:
protected:
 long number;
 Protocol protocol;

 friend class NmraConsist;

};

#endif // DCCLOCOADDRESSTEST_H
