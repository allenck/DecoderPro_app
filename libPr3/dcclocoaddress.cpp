#include "dcclocoaddress.h"
#include "exceptions.h"
/**
 * Encapsulate information for a DCC Locomotive Decoder Address.
 *
 * In particular, this handles the "short" (standard) vs
 * "extended" (long) address selection.
 *
 * An address must be one of these, hence short vs long is encoded
 * as a boolean.
 *
 * Once created, the number and long/short status cannot be changed.
 *
 * @author			Bob Jacobsen Copyright (C) 2005
 * @version			$Revision: 21278 $
 */


DccLocoAddress::DccLocoAddress(int number, bool isLong, QObject *parent)
{
    this->number = number;
    protocol = LocoAddress::DCC_SHORT;
    if(isLong)
        protocol = LocoAddress::DCC_LONG;
}
DccLocoAddress::DccLocoAddress(int number, Protocol protocol, QObject* parent)
{
    this->number = number;
    this->protocol = protocol;
}
DccLocoAddress::DccLocoAddress(const DccLocoAddress& l , QObject* parent)
{
 this->number = l.number;
 this->protocol = l.protocol;
}

//bool DccLocoAddress::operator==(const LocoAddress &a)
//{
// //if (a==NULL) return false;
// try
// {
//  //DccLocoAddress other = (DccLocoAddress ) a;
//  if (this->number != a.getNumber()) return false;
//  if (this->protocol != a.getProtocol()) return false;
//   return true;
// }
// catch (std::exception e)
// { return false; }
//}

//@Override
/*public*/ bool DccLocoAddress::equals(QObject* a) {
    if (a != nullptr && a->metaObject()->className() == (this->metaObject()->className())) {
        try {
            DccLocoAddress* other = (DccLocoAddress*) a;
            if (this->number != other->number) {
                return false;
            }
            if (this->protocol != other->protocol) {
                return false;
            }
            return true;
        } catch (/*RuntimeException*/Exception e) {
            return false;
        }
    }
    return false;
}

int DccLocoAddress::hashCode() const {
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

QString DccLocoAddress::toString() {
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

bool DccLocoAddress::isLongAddress() {
    if(protocol==DCC_SHORT)
        return false;
    return true;
}

LocoAddress::Protocol DccLocoAddress::getProtocol() const {
    return protocol;
}

int DccLocoAddress::getNumber() const { return (int)number; }

