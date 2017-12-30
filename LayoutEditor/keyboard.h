#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "abstractcontroller.h"

namespace Usb
{
class Keyboard : public Usb::AbstractController
{
public:
 Keyboard();
 /*public*/ Type getType();
 /*public*/ /*final*/ bool isKeyDown(UsbComponent::Identifier::Key key_id);

private:
 Controller::Type _type;
protected:
 /*protected*/ Keyboard(QString name, QVector<UsbComponent*>* keys, QVector<Usb::Controller*>* children, QVector<Rumbler*>* rumblers);

};
}
#endif // KEYBOARD_H
