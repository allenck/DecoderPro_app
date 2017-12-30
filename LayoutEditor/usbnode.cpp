#include "usbnode.h"
#include "sensormanager.h"
#include "instancemanager.h"
#include "usbcomponent.h"

//UsbNode::UsbNode()
//{

//}
/**
 * UsbNode represents the USB controllers or component.
 * <P>
 * Generally accessed via the TreeModel.
 * <P>
 * Can be connected to a JMRI Sensor or Memory.
 *
 * @author	Bob Jacobsen Copyright 2008
 */
///*public*/ class UsbNode extends DefaultMutableTreeNode {


UsbNode::UsbNode(QString name, Usb::Controller* controller, UsbComponent* component, QObject* parent)
 : DefaultMutableTreeNode(name, parent)
{
    //super(name);
 attachedMemory = "";
 attachedSensor = "";
 val = -1;
 log = new Logger("UsbNode");

    this->name = name;
    this->controller = controller;
    this->component = component;
}

//@Override
/*public*/ int UsbNode::hashCode() {
#if 0
    if (component != NULL) {
        return component->hashCode();
    }
    if (controller == NULL) {
        return DefaultMutableTreeNode::hashCode();
    } else {
        return controller->hashCode();
    }
#endif
}

/*public*/ Usb::Controller* UsbNode::getController() {
    return controller;
}

/*public*/ UsbComponent* UsbNode::getComponent() {
    return component;
}

//@Override
/*public*/ bool UsbNode::equals(QObject* a) {
    if (a == NULL) {
        return false;
    }
    //if (!(a instanceof UsbNode))
    if(qobject_cast<UsbNode*>(a) != NULL)
    {
        return false;
    }
    UsbNode* opp = (UsbNode*) a;
    return (name == (opp->name)) && (controller == opp->controller) && (component == opp->component);
}

/*public*/ void UsbNode::setValue(float val) {
    this->val = val;
    // if attached, set value
    try {
        if ((attachedSensor != "") && (attachedSensor != (""))) {
            InstanceManager::sensorManagerInstance()
                    ->provideSensor(attachedSensor)->setKnownState(
                            val > 0.0 ? Sensor::ACTIVE : Sensor::INACTIVE);
        }
    } catch (Exception e1) {
        log->error(tr("Can't set sensor: ") + e1.getMessage());
    }
    try {
        if ((attachedMemory != NULL) && (attachedMemory!=(""))) {
            InstanceManager::memoryManagerInstance()
                    ->provideMemory(attachedMemory)->setValue(val);
        }
    } catch (Exception e2) {
        log->error("Can't set memory: " + e2.getMessage());
    }
}

/*public*/ float UsbNode::getValue() {
    return val;
}


/*public*/ void UsbNode::setAttachedSensor(QString sensor) {
    attachedSensor = sensor;
}

/*public*/ QString UsbNode::getAttachedSensor() {
    return attachedSensor;
}


/*public*/ void UsbNode::setAttachedMemory(QString memory) {
    attachedMemory = memory;
}

/*public*/ QString UsbNode::getAttachedMemory() {
    return attachedMemory;
}

/*public*/ QString UsbNode::getName() {
    return name;
}
/**
 * Get a specific node. This is used instead of a ctor to ensure that node
 * objects for a given USB object are unique.
 */
/*static*/ /*public*/ UsbNode* UsbNode::getNode(QString name, Usb::Controller* controller, UsbComponent* component) {
    QObject* key = (QObject*)controller;
    if (component != NULL) {
        key = (QObject*)component;
    }

    UsbNode* temp = map->value(key);
    if (temp != NULL) {
        return temp;
    }
    UsbNode* node = new UsbNode(name, controller, component);
    map->insert(key, node);
    return node;
}

/*static*/ /*private*/ QHash<QObject*, UsbNode*>* UsbNode::map = new QHash<QObject*, UsbNode*>();
