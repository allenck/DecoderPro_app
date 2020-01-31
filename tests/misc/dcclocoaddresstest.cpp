#include "dcclocoaddresstest.h"
#include "dcclocoaddress.h"
#include "assert1.h"

DccLocoAddressTest::DccLocoAddressTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test simple functioning of DccLocoAddress
 *
 * @author Bob Jacobsen Copyright (C) 2005
 */
///*public*/ class DccLocoAddressTest {

    //@Test
    /*public*/ void DccLocoAddressTest::testValue1() {
        DccLocoAddress l = DccLocoAddress(12, true);
        Assert::assertEquals("number ", l.getNumber(), 12, __FILE__,  __LINE__);
        Assert::assertEquals("long/short ", l.isLongAddress(), true, __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testValue2() {
        DccLocoAddress l = DccLocoAddress(12, false);
        Assert::assertEquals("number ", l.getNumber(), 12, __FILE__,  __LINE__);
        Assert::assertEquals("long/short ", l.isLongAddress(), false, __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testValue3() {
        DccLocoAddress l = DccLocoAddress(121, true);
        Assert::assertEquals("number ", l.getNumber(), 121, __FILE__,  __LINE__);
        Assert::assertEquals("long/short ", l.isLongAddress(), true, __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testCopy1() {
        DccLocoAddress l = DccLocoAddress( DccLocoAddress(121, true));
        Assert::assertEquals("number ", l.getNumber(), 121, __FILE__,  __LINE__);
        Assert::assertEquals("long/short ", l.isLongAddress(), true, __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testEquals1() {
        DccLocoAddress* l1 = new DccLocoAddress(121, true);
        DccLocoAddress* l2 = new DccLocoAddress(121, true);

        Assert::assertTrue("equate ", l1 ->equals (l2), __FILE__,  __LINE__);

        Assert::assertTrue("reflexive 1 ", l1->equals(l1), __FILE__,  __LINE__);
        Assert::assertTrue("reflexive 2 ", l2->equals(l2), __FILE__,  __LINE__);

//        Assert::assertTrue("null 1 ", !l1 == (null), __FILE__,  __LINE__);
//        Assert::assertTrue("null 2 ", !l2 == (null), __FILE__,  __LINE__);
        Assert::assertTrue("transitive ", (l2->equals(l1)) == ((l1 ==(l2))), __FILE__,  __LINE__);

        QList<TestAddr> tlist = QList<TestAddr>();
        TestAddr ta = TestAddr();
        tlist.append(ta);

        QList<DccLocoAddressX> list = QList<DccLocoAddressX>();
        DccLocoAddressX l1x = DccLocoAddressX(121, true);
        list.append(l1x);
        Assert::assertTrue("contains", list.contains(l1x), __FILE__,  __LINE__);

        DccLocoAddress* l3 =  new DccLocoAddress(121, true);
        DccLocoAddress* l4 =  new DccLocoAddress(121, true);

        Assert::assertTrue("equate ", l3->equals(l4), __FILE__,  __LINE__);

    }

    //@Test
    /*public*/ void DccLocoAddressTest::testEquals2() {
        DccLocoAddress l1 = DccLocoAddress(4321, true);
        DccLocoAddress l2 = DccLocoAddress(121, true);

        Assert::assertTrue("equate ", !(l1.equals(&l2)), __FILE__,  __LINE__);

        Assert::assertTrue("reflexive 1 ", l1.equals(&l1), __FILE__,  __LINE__);
        Assert::assertTrue("reflexive 2 ", l2.equals(&l2), __FILE__,  __LINE__);

//        Assert::assertTrue("null 1 ", !l1 == (null), __FILE__,  __LINE__);
//        Assert::assertTrue("null 2 ", !l2 == (null), __FILE__,  __LINE__);
        Assert::assertTrue("transitive ", (l2.equals(&l1)) == ((l1.equals(&l2))), __FILE__,  __LINE__);

    }

    //@Test
    /*public*/ void DccLocoAddressTest::testEquals3() {
        DccLocoAddress l1 = DccLocoAddress(121, false);
        DccLocoAddress l2 = DccLocoAddress(121, true);

        Assert::assertTrue("equate ", !(l1.equals(&l2)), __FILE__,  __LINE__);

        Assert::assertTrue("reflexive 1 ", l1.equals(&l1), __FILE__,  __LINE__);
        Assert::assertTrue("reflexive 2 ", l2.equals(&l2), __FILE__,  __LINE__);

//        Assert::assertTrue("null 1 ", !l1 == (null), __FILE__,  __LINE__);
//        Assert::assertTrue("null 2 ", !l2 == (null), __FILE__,  __LINE__);
        Assert::assertTrue("transitive ", (l2.equals(&l1)) == ((l1.equals(&l2))), __FILE__,  __LINE__);

    }

    //@Test
    /*public*/ void DccLocoAddressTest::testEquals4() {
        DccLocoAddress l1 = DccLocoAddress(4321, true);
        DccLocoAddress l2 = DccLocoAddress(121, false);

        Assert::assertTrue("equate ", !(l1.equals(&l2)), __FILE__,  __LINE__);

        Assert::assertTrue("reflexive 1 ", l1.equals(&l1), __FILE__,  __LINE__);
        Assert::assertTrue("reflexive 2 ", l2 .equals(&l2), __FILE__,  __LINE__);

//        Assert::assertTrue("null 1 ", !(l1 == (null)), __FILE__,  __LINE__);
//        Assert::assertTrue("null 2 ", l2 != (null), __FILE__,  __LINE__);
        Assert::assertTrue("transitive ", (l2.equals(&l1)) == ((l1.equals(&l2))), __FILE__,  __LINE__);

    }

    //@Test
    /*public*/ void DccLocoAddressTest::testHash0() {
        DccLocoAddress l1 = DccLocoAddress(121, true);
        DccLocoAddress l2 = DccLocoAddress(4321, false);

        Assert::assertTrue("equate self 1", l1.hashCode() == l1.hashCode(), __FILE__,  __LINE__);
        Assert::assertTrue("equate self 2", l2.hashCode() == l2.hashCode(), __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testHash1() {
        DccLocoAddress l1 = DccLocoAddress(121, true);
        DccLocoAddress l2 = DccLocoAddress(121, true);

        Assert::assertTrue("equate ", l1.hashCode() == l2.hashCode(), __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testHash2() {
        DccLocoAddress l1 = DccLocoAddress(4321, true);
        DccLocoAddress l2 = DccLocoAddress(121, true);

        Assert::assertTrue("equate ", l1.hashCode() != l2.hashCode(), __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testHash3() {
        DccLocoAddress l1 = DccLocoAddress(4321, false);
        DccLocoAddress l2 = DccLocoAddress(4321, true);

        Assert::assertTrue("equate ", l1.hashCode() != l2.hashCode(), __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testHash4() {
        DccLocoAddress l1 = DccLocoAddress(4321, false);
        DccLocoAddress l2 = DccLocoAddress(121, true);

        Assert::assertTrue("equate ", l1.hashCode() != l2.hashCode(), __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testHash5() {
        DccLocoAddress l1 = DccLocoAddress(4321, true);
        DccLocoAddress l2 = DccLocoAddress(4321, true);

        Assert::assertTrue("equate ", l1.hashCode() == l2.hashCode(), __FILE__,  __LINE__);
    }

    //@Test
    /*public*/ void DccLocoAddressTest::testHash6() {
        DccLocoAddress l1 = DccLocoAddress(4321, false);
        DccLocoAddress l2 = DccLocoAddress(4321, false);

        Assert::assertTrue("equate ", l1.hashCode() == l2.hashCode(), __FILE__,  __LINE__);
    }

 DccLocoAddressX:: DccLocoAddressX(int number, bool isLong)
{
    this->number = number;
    protocol = DccLocoAddressX::DCC_SHORT;
    if(isLong)
        protocol = DccLocoAddressX::DCC_LONG;
}
 DccLocoAddressX:: DccLocoAddressX(int number, Protocol protocol)
{
    this->number = number;
    this->protocol = protocol;
}
 DccLocoAddressX:: DccLocoAddressX(const  DccLocoAddressX& l ) //: QObject()
{
 this->number = l.number;
 this->protocol = l.protocol;
}

bool  DccLocoAddressX::operator==(const DccLocoAddressX &a)
{
 //if (a==NULL) return false;
 try
 {
  // DccLocoAddressX other = ( DccLocoAddressX ) a;
  if (this->number != a.getNumber()) return false;
  if (this->protocol != a.getProtocol()) return false;
   return true;
 }
 catch (std::exception e)
 { return false; }
}

//@Override
///*public*/ bool  DccLocoAddressX::equals(QObject* a) {
//    if (a != nullptr && a->metaObject()->className() == (this->metaObject()->className())) {
//        try {
//             DccLocoAddressX* other = ( DccLocoAddressX*) a;
//            if (this->number != other->number) {
//                return false;
//            }
//            if (this->protocol != other->protocol) {
//                return false;
//            }
//            return true;
//        } catch (/*RuntimeException*/Exception e) {
//            return false;
//        }
//    }
//    return false;
//}

int  DccLocoAddressX::hashCode() const {
    switch(protocol){
        case DCC_SHORT :    return (int)(number&0xFFFFFFFF);
        case DCC_LONG :     return (int)(20000+(number&0xFFFFFFFF));
        case SELECTRIX:     return (int)(30000+(number&0xFFFFFFFF));
        case MOTOROLA:      return (int)(40000+(number&0xFFFFFFFF));
        case MFX:           return (int)(50000+(number&0xFFFFFFFF));
        case M4:            return (int)(60000+(number&0xFFFFFFFF));
        case OPENLCB:       return (int)(70000+(number&0xFFFFFFFF));
        default:            return (int)(number&0xFFFFFFFF);
    }
}

QString  DccLocoAddressX::toString() const {
    switch(protocol){
    case DCC_SHORT : return QString("%1(S)").arg(number);
        case DCC_LONG : return QString("%1(L)").arg(number);
        case SELECTRIX: return QString("%1(SX)").arg(number);
        case MOTOROLA: return QString("%1(MM)").arg(number);
        case M4: return QString("%1(M4)").arg(number);
        case MFX: return QString("%1(MFX)").arg(number);
        case OPENLCB: return QString("%1(OpenLCB)").arg(number);
        default: return QString("%1(D)").arg(number);
    }
}

bool  DccLocoAddressX::isLongAddress() const {
    if(protocol==DCC_SHORT)
        return false;
    return true;
}

DccLocoAddressX::Protocol  DccLocoAddressX::getProtocol() const {
    return protocol;
}

int  DccLocoAddressX::getNumber() const { return (int)number; }
