#ifndef LOCOADDRESS_H
#define LOCOADDRESS_H

#include <QObject>
#include "libPr3_global.h"
//enum Protocol {
//            DCC_SHORT,
//            DCC_LONG,  // NOI18N
//            DCC,       // NOI18N
//            SELECTRIX, // NOI18N
//            MOTOROLA,  // NOI18N
//            MFX,       // NOI18N
//            M4,        // NOI18N
//            OPENLCB
//};
class AbstractThrottleManager;
class LIBPR3SHARED_EXPORT LocoAddress : public QObject
{
    Q_OBJECT
    //Q_ENUMS(Protocol)
    friend class AbstractThrottleManager;
public:
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
    Q_ENUM(Protocol)
    explicit LocoAddress(QObject *parent = 0) : QObject(parent) {}
    /**
     * Interface for generic Locomotive Address.
     *
     * Note that this is not DCC-specific.
     *
     *
     * <hr>
     * This file is part of JMRI.
     * <P>
     * JMRI is free software; you can redistribute it and/or modify it under
     * the terms of version 2 of the GNU General Public License as published
     * by the Free Software Foundation. See the "COPYING" file for a copy
     * of this license.
     * <P>
     * JMRI is distributed in the hope that it will be useful, but WITHOUT
     * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
     * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
     * for more details.
     * <P>
     * @author			Bob Jacobsen Copyright (C) 2005
     * @version			$Revision: 22214 $
     */

//    virtual interface LocoAddress {

        virtual int getNumber() const {return 0;}

//        enum Protocol {
//            DCC_SHORT(  "dcc_short","ProtocolDCC_Short"), // NOI18N
//            DCC_LONG(   "dcc_long", "ProtocolDCC_Long"),  // NOI18N
//            DCC(        "dcc",      "ProtocolDCC"),       // NOI18N
//            SELECTRIX(  "selectrix","ProtocolSelectrix"), // NOI18N
//            MOTOROLA(   "motorola", "ProtocolMotorola"),  // NOI18N
//            MFX(        "mfx",      "ProtocolMFX"),       // NOI18N
//            M4(         "m4",       "ProtocolM4"),        // NOI18N
//            OPENLCB(    "openlcb",  "ProtocolOpenLCB");   // NOI18N
//            LGB("lgb", "ProtocolLGB");   // NOI18N

//            Protocol(QString shName, QString peopleKey) {
//                this->shortName = shName;
//                this->peopleName = /*Bundle.getMessage(peopleKey)*/tr("People key");
//            }


 static QString getShortName(Protocol p)
 {
     switch(p)
     {
     case DCC_SHORT:
         return "dcc_short";
     case DCC_LONG:
         return "dcc_long";
     case DCC:
         return "dcc";
     case SELECTRIX:
         return "selectrix";
     case MOTOROLA:
         return "motorola";
     case MFX:
         return "mfx";
     case M4:
         return "m4";
     case OPENLCB:
         return "openlcb";
     case LGB:
         return "lgb";
     default:
         return "";
     }
 }

 static QString getPeopleName(Protocol p)
 {
     switch(p)
     {
     case DCC_SHORT:
         return tr("DCC Short");
     case DCC_LONG:
         return tr("DCC Long");
     case DCC:
         return tr("DCC");
     case SELECTRIX:
         return tr("Selectrix");
     case MOTOROLA:
         return tr("Motorola");
     case MFX:
         return tr("MFX");
     case M4:
         return tr("M4");
     case OPENLCB:
         return tr("OpenLCB");
     case LGB:
         return tr("LGB");
     default:
         break;
     }
     return "";
 }


static Protocol getByShortName(QString shName) {
//                for (Protocol p , Protocol.values()) {
//                    if (p.shortName==(shName)) return p;
//                }
                //throw new java.lang.IllegalArgumentException("argument value "+shName+" not valid");
    if(shName == "dcc_short")
      return DCC_SHORT;
    else
    if(shName =="dcc_long")
      return DCC_LONG;
    else if(shName == "dcc")
        return DCC;
    else if(shName == "selectrix")
        return SELECTRIX;
    else if(shName == "motorola")
        return MOTOROLA;
    else if(shName == "mfx")
        return MFX;
    else if(shName == "m4")
        return M4;
    else if(shName == "openlcb")
        return OPENLCB;
    else if(shName == "lgb")
        return LGB;
    return DCC_SHORT;
}

static Protocol getByPeopleName(QString pName) {
//    for (Protocol p , Protocol.values()) {
//        if (p.peopleName.equals(pName)) return p;
//    }
    //throw new java.lang.IllegalArgumentException("argument value "+pName+" not valid");
    if(pName == tr("DCC Short"))
      return DCC_SHORT;
    else
    if(pName ==tr("DCC Long"))
      return DCC_LONG;
    else
    if(pName == tr("DCC"))
        return DCC;
    // TODO: do the rest
    if(pName == tr("Selectrix"))
        return SELECTRIX;
    if(pName == tr("Motorola"))
        return MOTOROLA;
    if(pName == tr("MFX"))
        return MFX;
    if(pName == tr("M4"))
        return M4;
    if(pName == tr("OpenLCB"))
        return OPENLCB;
    if(pName == tr("LGB"))
        return LGB;
    return DCC_SHORT;
}

//        }
    virtual Protocol getProtocol() const {return DCC;}
    virtual QString toString() { return "";}
//    virtual bool operator ==(const LocoAddress &a)
//    {
//     //if (a==NULL) return false;
////     if(dynamic_cast<LocoAddress*>(a)== nullptr) return false;
//     if(this->metaObject()->className() != a.metaObject()->className()) return false;
//     try
//     {
//      //LocoAddress &other = (LocoAddress ) a;
//      if (this->getNumber() != a.getNumber()) return false;
//      if (this->getProtocol() != a.getProtocol()) return false;
//       return true;
//     }
//     catch (std::exception e)
//     { return false; }
//    }

    virtual bool equals(QObject* a)
    {
     if (a==NULL) return false;
     if(qobject_cast<LocoAddress*>(a)== nullptr) return false;
     if(this->metaObject()->className() != a->metaObject()->className()) return false;
     try
     {
      LocoAddress* other = (LocoAddress *) a;
      if (this->getNumber() != other->getNumber()) return false;
      if (this->getProtocol() != other->getProtocol()) return false;
       return true;
     }
     catch (std::exception e)
     { return false; }
    }

virtual int hashCode() const {return 0;}

signals:
    
public slots:
private:
inline bool operator<(const LocoAddress &e2) const
{
    if (getNumber() != e2.getNumber())
        return getNumber() < e2.getNumber();
    return getProtocol() < e2.getProtocol();
}
inline bool operator==(const LocoAddress &e2)
{
  return getNumber() == e2.getNumber();
}

//inline uint qHash(const LocoAddress &key, uint seed)
//{
// return qHash(key.hashCode(), seed);
//}

};
//QString LocoAddress::getShortName(LocoAddress::Protocol);
//QString LocoAddress::getPeopleName(LocoAddress::Protocol);
//LocoAddress::Protocol LocoAddress::getByPeopleName(QString pName);
//LocoAddress::Protocol LocoAddress::getByShortName(QString shName);

#endif // LOCOADDRESS_H
