#include "locoioaddress.h"

LocoIOAddress::LocoIOAddress(QObject *parent) //: QObject(parent)
{
 _address = 0;
}

LocoIOAddress::LocoIOAddress(qint16 unitAddress, qint16 unitSubAddress, QObject *parent)
 //: QObject(parent)
{
 setAddress(unitAddress, unitSubAddress);
}

void LocoIOAddress::setAddress(qint16 unitAddress, qint16 unitSubAddress)
{
 _address = (((qint32)unitAddress | 0x100) <<16 ) | unitSubAddress;
}

void LocoIOAddress::setUnitAddress(qint16 u)
{
 _address = (_address & 0xFFFF) | ((u |0x100) << 16);
}

qint16 LocoIOAddress::unitAddress() const { return (_address >> 16) & 0xFF;}

void LocoIOAddress::setUnitSubAddress(qint16 u)
{
 _address = (_address & 0xFFFF0000) | u ;
}

qint16 LocoIOAddress::unitSubAddress() const { return _address & 0xFFFF; }

qint32 LocoIOAddress::address() const { return _address; }

bool LocoIOAddress::operator<(const LocoIOAddress  other) const
{
 if(((_address >> 16)&0xff) == (other.unitAddress()&0xff))
 {
  return other.unitSubAddress() > (_address & 0xFFFF);
 }
 return (other.unitAddress()&0xff) > ((_address >> 16)&0xff);
}

bool LocoIOAddress::operator ==(const LocoIOAddress other) const
{
 return other.unitAddress() == ((_address >> 16)& 0xFF) && (_address & 0xFFFF) == other.unitSubAddress();
}

void LocoIOAddress::setModuleType(QString type) { _moduleType = type;}

QString LocoIOAddress::moduleType() { return _moduleType;}

void LocoIOAddress::setFirmwareVersion(QString v) { _firmwareVersion = v;}

QString LocoIOAddress::firmwareVersion() { return _firmwareVersion;}
