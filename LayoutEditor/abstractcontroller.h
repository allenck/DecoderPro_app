#ifndef USB_ABSTRACTCONTROLLER_H
#define USB_ABSTRACTCONTROLLER_H
#include "controller.h"
#include "usbcomponent.h"
#include "exceptions.h"

class Rumbler;
class Event;
class Map;
class EventQueue;
namespace Usb {


class AbstractController : public Usb::Controller
{
public:
 AbstractController();
 /*public*/ /*final*/ QVector<Usb::Controller*>* getControllers();
 /*public*/ /*final*/ QVector<UsbComponent*>* getComponents();
 /*public*/ /*final*/ UsbComponent* getComponent(UsbComponent::Identifier id);
 /*public*/ /*final*/ QVector<Rumbler*>* getRumblers();
 /*public*/ Usb::Controller::PortType getPortType();
 /*public*/ int getPortNumber();
 /*public*/ /*final*/ QString getName();
 /*public*/ QString toString();
 /*public*/ Usb::Controller::Type getType();
 /*public*/ /*final*/ void setEventQueueSize(int size);
 /*public*/ /*final*/ EventQueue* getEventQueue();
 /*public*/ /*synchronized*/ bool poll();

private:
 static /*final*/ int EVENT_QUEUE_DEPTH;// = 32;
 /*private*/ static /*final*/ Event* event;
 /*private*/ /*final*/ QString name;
 /*private*/ /*final*/ QVector<UsbComponent*>* components;
 /*private*/ /*final*/ QVector<Usb::Controller*>* children;
 /*private*/ /*final*/ QVector<Rumbler*>* rumblers;
 /*private*/ /*final*/ Map* id_to_components;
 /*private*/ EventQueue* event_queue;
 Controller::PortType portType;

 /*protected*/ AbstractController(QString name, QVector<UsbComponent*>* components, QVector<Usb::Controller*>* children, QVector<Rumbler*>* rumblers);
 /*protected*/ void setDeviceEventQueueSize(int size) /*throw (IOException)*/;
 /*protected*/ /*abstract*/ virtual bool getNextDeviceEvent(Event* event) /*throw (IOException)*/;
 /*protected*/ void pollDevice() /*throw (IOException)*/;
 friend class LinuxAbstractController;
 friend class Keyboard;
};
}
#endif // USB_ABSTRACTCONTROLLER_H
