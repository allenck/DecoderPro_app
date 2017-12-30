#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "usbcomponent.h"

class UsbComponent;
class Type;

class EventQueue;
class Rumbler;
namespace Usb {
 class Controller : public QObject
 {
  Q_OBJECT
 public:
  class PortType
  {
   /*private*/ /*final*/ QString name;
  public:
   enum PORTTYPES
   {
     UNKNOWN,
     USB,
     GAME,
     NETWORK,
     SERIAL,
     I8042,
     PARALLEL
   };
   PortType();
   /*public*/ QString toString();

  protected:
   /*protected*/ PortType(QString name);

  };
  /*public*/ /*static*/ class Type {

   /*private*/ /*final*/ QString name;
  public:
   enum TYPES
   {
      UNKNOWN,
      MOUSE,
      KEYBOARD,
      FINGERSTICK,
      GAMEPAD,
      HEADTRACKER,
      RUDDER,
      STICK,
      TRACKBALL,
      TRACKPAD,
      WHEEL
     };
   Type();
   /*protected*/ Type(QString name);
   /*public*/ QString toString();

   friend class UsbTreeModel0;
   friend class TreePanel;
 };

  explicit Controller(QObject *parent = 0);
  /*public*/ virtual QVector<Controller*>* getControllers() {return NULL;}
  /*public*/ virtual Controller::Type getType() {}
  /*public*/ virtual QVector<UsbComponent*>* getComponents() {return NULL;}

  /*public*/ virtual UsbComponent* getComponent(UsbComponent::Identifier idntfr) {return NULL;}

  /*public*/ virtual QVector<Rumbler*>* getRumblers() {return NULL;}

  /*public*/ virtual bool poll() {return false;}

  /*public*/ virtual void setEventQueueSize(int i) {}

  /*public*/ virtual EventQueue* getEventQueue() {return NULL;}

  /*public*/ virtual Controller::PortType getPortType();

  /*public*/ virtual int getPortNumber();

  /*public*/ virtual QString getName();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ QString name;

 protected:
 friend class UsbTreeModel0;
 };
}
#endif // CONTROLLER_H
