#ifndef LINUXINPUTID_H
#define LINUXINPUTID_H
#include "controller.h"

class LinuxInputID
{
public:
 LinuxInputID();
 /*public*/ LinuxInputID(int bustype, int vendor, int product, int version);
 /*public*/ /*final*/ Usb::Controller::PortType getPortType();
 /*public*/ /*final*/ QString toString();

private:
 /*private*/ /*final*/ int bustype;
 /*private*/ /*final*/ int vendor;
 /*private*/ /*final*/ int product;
 /*private*/ /*final*/ int version;

};

#endif // LINUXINPUTID_H
