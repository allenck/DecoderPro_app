#ifndef USB_BUS_H
#define USB_BUS_H

#include <QObject>
#include "clientif.h"

class DevKey
{
 qint8 _bus;
 qint8 _address;
public:
 DevKey(qint8 bus, qint8 port) { this->_bus = bus; this->_address = port;}
 qint16 key() const {return ((_bus <<8) + _address);}
 quint8 port() {return _address;}
 quint8 bus() {return _bus;}
 //bool operator<(const DevKey other) {return key() < other.key();}
};

enum libusb_class_code {
 /** In the context of a \ref libusb_device_descriptor "device descriptor",
  * this bDeviceClass value indicates that each interface specifies its
  * own class information and all interfaces operate independently.
  */
 LIBUSB_CLASS_PER_INTERFACE = 0,

 /** Audio class */
 LIBUSB_CLASS_AUDIO = 1,

 /** Communications class */
 LIBUSB_CLASS_COMM = 2,

 /** Human Interface Device class */
 LIBUSB_CLASS_HID = 3,

 /** Physical */
 LIBUSB_CLASS_PHYSICAL = 5,

 /** Printer class */
 LIBUSB_CLASS_PRINTER = 7,

 /** Image class */
 LIBUSB_CLASS_PTP = 6, /* legacy name from libusb-0.1 usb.h */
 LIBUSB_CLASS_IMAGE = 6,

 /** Mass storage class */
 LIBUSB_CLASS_MASS_STORAGE = 8,

 /** Hub class */
 LIBUSB_CLASS_HUB = 9,

 /** Data class */
 LIBUSB_CLASS_DATA = 10,

 /** Smart Card */
 LIBUSB_CLASS_SMART_CARD = 0x0b,

 /** Content Security */
 LIBUSB_CLASS_CONTENT_SECURITY = 0x0d,

 /** Video */
 LIBUSB_CLASS_VIDEO = 0x0e,

 /** Personal Healthcare */
 LIBUSB_CLASS_PERSONAL_HEALTHCARE = 0x0f,

 /** Diagnostic Device */
 LIBUSB_CLASS_DIAGNOSTIC_DEVICE = 0xdc,

 /** Wireless class */
 LIBUSB_CLASS_WIRELESS = 0xe0,

 /** Application class */
 LIBUSB_CLASS_APPLICATION = 0xfe,

 /** Class is vendor-specific */
 LIBUSB_CLASS_VENDOR_SPEC = 0xff
};
struct Parent
{
 quint16 size;     // size of this structure
 quint8 bus;
 quint8 port;
 quint8 address;
 quint16 vid;      /**< Vendor ID */
 quint16 pid;      /**< Product ID */
 quint8  bDeviceClass;
 quint8  bDeviceSubClass;
 quint8  bDeviceProtocol;
};

class DeviceFilter
{
public:
 DeviceFilter();
 DeviceFilter(QVariantList);
 quint16 size;     // size of this structure
 quint8 bus;
 quint8 port;
 quint8 address;
 quint16 vid;      /**< Vendor ID */
 quint16 pid;      /**< Product ID */
 quint8  bDeviceClass;
 quint8  bDeviceSubClass;
 quint8  bDeviceProtocol;
 // parent information
 bool bHasParent;
 Parent parent;
//  DeviceConfig cfg; /**< Configuration for a given device */
 QString manufacturer;
 QString product;
 QString serialNumber;
 quint8 interface;
 quint8 interfaceClass;
 QString deviceClass;

};
Q_DECLARE_METATYPE(DeviceFilter)

class Usb_Device;
class Usb_Bus : public QObject
{
 Q_OBJECT
public:
 explicit Usb_Bus(QObject *parent = 0);
 /*public*/ Usb_Device* getDevices();
 /*public*/ QString getDirname();
 /*public*/ Usb_Bus* getNext();
 /*public*/ Usb_Bus* getPrev() ;
 /*public*/ Usb_Device* getRootDev();
 /*public*/ long getLocation();
 /*public*/ QString toString();
 /*public*/ QList<DeviceFilter> getChildrenOf(quint8 bus, quint8 port);
 /*public*/ DeviceFilter getDevice(quint8 bus, quint8 address);


signals:

 void notify_deviceChange(uchar bus, uchar port, bool bAdded);

public slots:

 void deviceChange(uchar,uchar,bool);

private:
 /*private*/ Usb_Bus* next;
 /*private*/ Usb_Bus* prev;
 /*private*/ QString dirname;
 /*private*/ Usb_Device* devices;
 /*private*/ long location;
 /*private*/ Usb_Device* root_dev;
 QHash<qint16,DeviceFilter> devHash;
 ClientIf* interface;
 //QDBusConnection dBusConn;// = QDBusConnection::systemBus();


 friend class UsbTreeModel;

};

#endif // USB_BUS_H
