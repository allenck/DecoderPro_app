#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#include <QObject>
#include "usb_bus.h"

class Usb_Device_Descriptor;
class Usb_Bus;
class Usb_Config_Descriptor;
class Usb_Device : public QObject
{
 Q_OBJECT
public:
 //explicit Usb_Device(QObject *parent = 0);
 /*public*/ long devStructAddr;
 /*public*/ Usb_Device(QObject *parent = 0);
 ~Usb_Device() {}
 Usb_Device(const Usb_Device&) : QObject() {}
 /*public*/ Usb_Bus* getBus();
 /*public*/ Usb_Device* getChildren();
 /*public*/ QList<Usb_Config_Descriptor*> getConfig() ;
 /*public*/ Usb_Device_Descriptor* getDescriptor() ;
 /*public*/ quint8 getDevnum() ;
 /*public*/ QString getFilename();
 /*public*/ Usb_Device* getNext();
 /*public*/ quint8 getNumChildren();
 /*public*/ Usb_Device* getPrev();
 /*public*/ QString toString();
 /*public*/ void setDeviceFilter(DeviceFilter f, QList<DeviceFilter> children, Usb_Bus* bus);

 DeviceFilter f;
signals:

public slots:

private:
 /*private*/ Usb_Device* next;
 /*private*/ Usb_Device* prev;
 /*private*/ QString filename;
 /*private*/ Usb_Bus* bus;
 /*private*/ Usb_Device_Descriptor* descriptor;
 /*private*/ QList<Usb_Config_Descriptor*>* config;
 /*private*/ quint8 devnum;
 /*private*/ quint8 num_children;
 /*private*/ Usb_Device* children;

};
Q_DECLARE_METATYPE(Usb_Device)
#endif // USB_DEVICE_H
