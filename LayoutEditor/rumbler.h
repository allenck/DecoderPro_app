#ifndef RUMBLER_H
#define RUMBLER_H
#include <QObject>
#include <usbcomponent.h>

/*public*/ /*interface*/class Rumbler : public QObject {

public:
 Rumbler(QObject* parent = 0) : QObject(parent){}
 /*public*/ virtual void rumble(float f) {}

 /*public*/ virtual QString getAxisName() {return "";}

 /*public*/ UsbComponent::Identifier* getAxisIdentifier() {return NULL;}
};

#endif // RUMBLER_H
