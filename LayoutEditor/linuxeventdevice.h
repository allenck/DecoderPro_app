#ifndef LINUXEVENTDEVICE_H
#define LINUXEVENTDEVICE_H
#include "linuxdevice.h"
#include <controller.h>
#include "linuxinputid.h"

class UsbComponent;
class Rumbler;
class LinuxInputID;
class LinuxEventDevice : public LinuxDevice
{
public:
 LinuxEventDevice();
 /*public*/ LinuxEventDevice(QString filename, QObject* parent=0) /*throw (IOException)*/;
 /*public*/ /*final*/ Usb::Controller::Type getType();
 /*public*/ /*final*/ /*synchronized*/ int uploadRumbleEffect(int i, int i1, int i2, int i3, int i4, int i5, int i6, int i7) /*throw (IOException)*/;
 /*public*/ /*final*/ /*synchronized*/ int uploadConstantEffect(int i, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10) /*throw (IOException)*/;
 /*public*/ /*final*/ QVector<Rumbler*>* getRumblers();

private:
// /*private*/ /*final*/ Map component_map;
 /*private*/ /*final*/ QVector<Rumbler*>* rumblers;
 /*private*/ /*final*/ long fd;
 /*private*/ /*final*/ QString name;
 /*private*/ /*final*/ LinuxInputID input_id;
 /*private*/ /*final*/ QList<UsbComponent*>* components;
 /*private*/ /*final*/ Usb::Controller::Type type;
 /*private*/ bool closed;
 /*private*/ /*final*/ QVector<quint8>* key_states;


};

#endif // LINUXEVENTDEVICE_H
