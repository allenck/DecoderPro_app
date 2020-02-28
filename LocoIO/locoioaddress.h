#ifndef LOCOIOADDRESS_H
#define LOCOIOADDRESS_H
#include <QObject>

class LocoIOAddress : public QObject
{
 Q_OBJECT
 qint32 _address;
 QString _firmwareVersion;
 QString _moduleType;

public:
 LocoIOAddress(QObject* parent = nullptr);
 LocoIOAddress(qint16 unitAddress, qint16 unitSubAddress, QObject* parent = nullptr);
 ~LocoIOAddress() {}
 LocoIOAddress(const LocoIOAddress&) : QObject() {}
 void setAddress(qint16 unitAddress, qint16 unitSubAddress);
 void setUnitAddress(qint16);
 qint16 unitAddress() const;
 void setUnitSubAddress(qint16);
 qint16 unitSubAddress() const;
 qint32 address() const;
 bool operator<(const LocoIOAddress  other) const;
 bool operator ==(const LocoIOAddress other) const;
 void setFirmwareVersion(QString);
 QString firmwareVersion();
 void setModuleType(QString);
 QString moduleType();


};

#endif // LOCOIOADDRESS_H
