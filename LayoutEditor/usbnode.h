#ifndef USBNODE_H
#define USBNODE_H
#include "defaultmutabletreenode.h"
#include <QWidget>
#include "logger.h"
#include "controller.h"
class UsbComponent;
class Controller;
class UsbNode : public DefaultMutableTreeNode
{
 Q_OBJECT
public:
 //UsbNode();
 UsbNode(QString name, Usb::Controller* controller, UsbComponent* component, QObject* parent = 0) ;
 /*public*/ int hashCode();
 /*public*/ Usb::Controller* getController() ;
 /*public*/ UsbComponent* getComponent();
 /*public*/ bool equals(QObject* a);
 /*public*/ void setValue(float val);
 /*public*/ float getValue();
 /*public*/ void setAttachedSensor(QString sensor);
 /*public*/ QString getAttachedSensor();
 /*public*/ void setAttachedMemory(QString memory);
 /*public*/ QString getAttachedMemory();
 /*public*/ QString getName();
 static /*public*/ UsbNode* getNode(QString name, Usb::Controller* controller, UsbComponent* component);


private:
 QString name;
 Usb::Controller* controller;
 UsbComponent* component;
 QString attachedMemory;// = null;
 QString attachedSensor;// = NULL;
 float val;// = -1;
 Logger* log;
static /*private*/ QHash<QObject*, UsbNode*>* map;// = new QHash<QObject*, UsbNode*>();
};

#endif // USBNODE_H
