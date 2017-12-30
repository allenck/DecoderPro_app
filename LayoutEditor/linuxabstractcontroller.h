#ifndef LINUXABSTRACTCONTROLLER_H
#define LINUXABSTRACTCONTROLLER_H
#include "abstractcontroller.h"
#include "usbcomponent.h"


class LinuxEventDevice;

namespace Usb
{
class LinuxAbstractController : public Usb::AbstractController
{
public:
 LinuxAbstractController();
 /*public*/ /*final*/ PortType getPortType();
 /*public*/ /*final*/ void pollDevice() throw (IOException);
 /*public*/ Controller::Type getType();

private:
 /*private*/ /*final*/ PortType port;
 /*private*/ /*final*/ LinuxEventDevice* device;
 /*private*/ /*final*/ Controller::Type type;

protected:
 /*protected*/ LinuxAbstractController(LinuxEventDevice* device, QVector<UsbComponent*>* components, QVector<Usb::Controller*>* children, QVector<Rumbler*>* rumblers, Type type) throw (IOException);
 /*protected*/ /*final*/ bool getNextDeviceEvent(Event* event) throw (IOException);

 friend class UsbTreeModel0;
};
}
#endif // LINUXABSTRACTCONTROLLER_H
