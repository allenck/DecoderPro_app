#include "usbtreemodel0.h"
#include "usbnode.h"
#include "logger.h"
#include "controller.h"
#include "propertychangesupport.h"
#include <QStringList>
#include <QDebug>
#include "linuxabstractcontroller.h"
#include "usbcomponent.h"
#include "linuxeventdevice.h"

//UsbTreeModel::UsbTreeModel()
//{

//}
/**
 * TreeModel represents the USB controllers and components
 * <P>
 * Accessed via the instance() member, as we expect to have only one of these
 * models talking to the USB subsystem.
 * <P>
 * The tree has three levels below the uninteresting root:
 * <ol>
 * <li>USB controller
 * <li>Components (input, axis)
 * </ol>
 * <P>
 * jinput requires that there be only one of these for a given USB system in a
 * given JVM so we use a pseudo-singlet "instance" approach
 *
 * Class is final because it starts a survey thread, which runs while
 * constructor is still active.
 *
 * @author	Bob Jacobsen Copyright 2008, 2010
  */
// /*public*/ final class TreeModel extends DefaultTreeModel {
namespace Usb
{
/*private*/ UsbTreeModel0::UsbTreeModel0(QObject* parent) : DefaultTreeModel(new DefaultMutableTreeNode("Root"), parent)
{
 log = new Logger("UsbTreeModel");
 ca = new QVector<Usb::Controller*>();
 pcs = new PropertyChangeSupport(this);
 devHash = QHash<qint16, DeviceFilter>();

    //super(new DefaultMutableTreeNode("Root"));
    dRoot = (DefaultMutableTreeNode*) getRoot();  // this is used because we can't store the DMTN we just made during the super() call

    // load initial USB objects
    bool pass = loadSystem();

    // If you don't call loadSystem, the following line was
    // needed to get the display to start
    // insertNodeInto(new UsbNode("System", NULL, NULL), dRoot, 0);
    // start the USB gathering
#if 0
    (new Runner()).start();
#endif
}

/**
 * Add a node to the tree if it doesn't already exist
 *
 * @param pChild  Node to possibly be inserted; relies on equals() to avoid
 *                duplicates
 * @param pParent Node for the parent of the resource to be scanned, e.g.
 *                where in the tree to insert it.
 * @return node, regardless of whether needed or not
 */
DefaultMutableTreeNode* UsbTreeModel0::insertNode(DefaultMutableTreeNode* pChild, DefaultMutableTreeNode* pParent) {
    // if already exists, just return it
    int index;
    index = getIndexOfChild(pParent, pChild);
    if (index >= 0) {
        return (DefaultMutableTreeNode*) getChild(pParent, index);
    }
    // represent this one
    index = pParent->getChildCount();
    insertNodeInto(pChild, pParent, index);
    return pChild;
}


/**
 * Provide access to the model. There's only one, because access to the USB
 * subsystem is required
 */
/*static*/ /*public*/   UsbTreeModel0*  UsbTreeModel0::instance() {
    if (instanceValue == NULL) {
        instanceValue = new UsbTreeModel0();
    }
    return instanceValue;
}

/*static*/ /*private*/ UsbTreeModel0* UsbTreeModel0::instanceValue = NULL;
#if 0
class Runner extends Thread {

    /**
     * Continually poll for events. Report any found.
     */
    @Override
    /*public*/ void run() {
        while (true) {
            Controller[] controllers = ControllerEnvironment.getDefaultEnvironment().getControllers();
            if (controllers.length == 0) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt(); // retain if needed later
                    return;  // interrupt kills the thread
                }
                continue;
            }

            for (int i = 0; i < controllers.length; i++) {
                controllers[i].poll();

                // Now we get hold of the event queue for this device.
                EventQueue queue = controllers[i].getEventQueue();

                // Create an event object to pass down to get populated with the information.
                // The underlying system may not hold the data in a JInput friendly way,
                // so it only gets converted when asked for.
                Event event = new Event();

                // Now we read from the queue until it's empty.
                // The 3 main things from the event are a time stamp
                // (it's in nanos, so it should be accurate,
                // but only relative to other events.
                // It's purpose is for knowing the order events happened in.
                // Then we can get the component that this event relates to, and the new value.
                while (queue.getNextEvent(event)) {
                    Component comp = event.getComponent();
                    float value = event.getValue();

                    if (log->isDebugEnabled()) {
                        StringBuffer buffer = new StringBuffer("Name [");
                        buffer.append(controllers[i].getName());
                        buffer.append("] Component [");
                        // buffer.append(event.getNanos()).append(", ");
                        buffer.append(comp.getName()).append("] changed to ");
                        if (comp.isAnalog()) {
                            buffer.append(value);
                        } else {
                            if (value == 1.0f) {
                                buffer.append("On");
                            } else {
                                buffer.append("Off");
                            }
                        }
                        log->debug(new String(buffer));
                    }

                    // ensure item exits
                    new Report(controllers[i], comp, value);
                }
            }

            try {
                Thread.sleep(20);
            } catch (InterruptedException e) {
                // interrupt kills the thread
                return;
            }
        }
    }
};
#endif

/*public*/ QVector<Usb::Controller*>* UsbTreeModel0::controllers() {
    //return Arrays.copyOf(ca, ca.length);
 return new QVector<Usb::Controller*>(*ca);
}
#if 0
/**
 * Carry a single event to the Swing thread for processing
 */
class Report implements Runnable {

    Controller controller;
    Component component;
    float value;

    Report(Controller controller, Component component, float value) {
        this.controller = controller;
        this.component = component;
        this.value = value;

        SwingUtilities.invokeLater(this);
    }

    /**
     * Handle report on Swing thread to ensure tree node exists and is
     * updated
     */
    @Override
    /*public*/ void run() {
        // ensure controller node exists directly under root
        String cname = controller.getName() + " [" + controller.getType().toString() + "]";
        UsbNode cNode = UsbNode.getNode(cname, controller, NULL);
        cNode = (UsbNode) insertNode(cNode, dRoot);

        // Device (component) node
        String dname = component.getName() + " [" + component.getIdentifier().toString() + "]";
        UsbNode dNode = UsbNode.getNode(dname, controller, component);
        dNode = (UsbNode) insertNode(dNode, cNode);

        dNode.setValue(value);

        // report change to possible listeners
        pcs.firePropertyChange("Value", dNode, Float.valueOf(value));
    }
};
#endif
/**
 * @return true for success
 */
bool UsbTreeModel0::loadSystem() {
    // Get a list of the controllers JInput knows about and can interact with
    log->debug("start looking for controllers");
#if 0
    try {
        ca = ControllerEnvironment.getDefaultEnvironment().getControllers();
        log->debug("Found " + ca.length + " controllers");
    } catch (Exception ex) { // this is probably ClassNotFoundException, but that's not part of the interface
        // could not load some component(s)
        log->debug("Found no controllers, handled Exception", ex);
        ca = NULL;
        return false;
    }
#else
    QDBusConnection dBusConn = QDBusConnection::systemBus();
    if(dBusConn.isConnected())
    {
     QString name = dBusConn.name();
     QDBusReply<QStringList> reply = dBusConn.interface()->registeredServiceNames();
     if(!reply.isValid())
      throw new IOException("No Dbus interfaces available");
     if(!reply.value().contains("org.example.TestServer"))
      throw new IOException("Required Dbus server available");
     QDBusInterface* interface = new QDBusInterface("org.example.TestServer","/org/example/TestObject","org.example.TestInterface",dBusConn);
     int deviceCount;
     QDBusReply<int> reply2 = interface->call(QLatin1String("DeviceCount"));
     if(reply2.isValid())
     {
      deviceCount = reply2.value();
     }
     else {
      qDebug() << interface->lastError().name();
     }
     if(deviceCount > 0)
     {
      for(qint32 i = 0; i < deviceCount; i++)
      {
       QDBusMessage reply = interface->call(QLatin1String("GetDevice"), QVariant(i));
       QList<QVariant> values = reply.arguments();
       if(values.count()>= 6)
       {
        QString info = QString("Bus: %1 Port: %2 %3:%4 Mfg: %5 Prod: %6").arg(values.at(0).toInt()).arg(values.at(1).toInt()).arg(values.at(2).toInt(),0,16).arg(values.at(3).toInt(),0,16).arg(values.at(4).toString()).arg(values.at(5).toString());
        qDebug() << info;

        qDebug() << reply;
        QList<QVariant> outArgs = reply.arguments();
        DeviceFilter f = DeviceFilter();
        for(int i = 0; i < outArgs.length(); i++)
        {
         QVariant v = outArgs.at(i);
         switch (i)
         {
         case 0:
          f.bus = v.toInt();
          break;
         case 1:
          f.port = v.toInt();
          break;
         case 2:
          f.address = v.toInt();
          break;
         case 3:
          f.vid = v.toInt();
          break;
         case 4:
          f.pid = v.toInt();
          break;
         case 5:
          f.manufacturer = v.toString();
          break;
         case 6:
          f.product = v.toString();
          break;
         case 7:
          f.serialNumber = v.toString();
          break;
         case 8:
          f.bDeviceClass = v.toInt();
          break;
         case 9:
          f.bDeviceSubClass = v.toInt();
          break;
         case 10:
          f.bDeviceProtocol = v.toInt();
          break;
         case 11:
          f.bHasParent = (v.toString() == "y");
         case 12:
          f.parent.bus = v.toInt();
          break;
         case 13:
          f.parent.port = v.toInt();
          break;
         case 14:
          f.parent.vid = v.toInt();
          break;
         case 15:
          f.parent.pid = v.toInt();
          break;
         default:
          break;
         }
        }
        DevKey devKey(f.bus, f.port);
        devHash.insert(devKey.key(), f);
        if(!f.bHasParent)
        {
         Usb::Controller* c = new Usb::Controller();

        }
       }
       else
        qDebug() << reply;
        qDebug() << interface->lastError().name();
      }
     }
    }

    QList<DeviceFilter> rootHubs = QList<DeviceFilter>();
    QList<DeviceFilter> allDevices = devHash.values();
    foreach(DeviceFilter f, allDevices)
    {
     if(f.bDeviceClass == LIBUSB_CLASS_HUB && !f.bHasParent )
     {
      rootHubs.append(f);
     }
    }
    foreach(DeviceFilter f, rootHubs)
    {
     QString str;
     Usb::LinuxAbstractController* lac = new Usb::LinuxAbstractController(new LinuxEventDevice(str), new QVector<UsbComponent*>(), new QVector<Usb::Controller*>(), NULL, Usb::Controller::Type(f.product));
     ca->append(lac);
    }

#endif
    for (int i = 0; i < ca->length(); i++) {
        // Get this controller's components (buttons and axis)
        QVector<UsbComponent*>* components = ca->at(i)->getComponents();
        log->info("Controller " + ca->at(i)->getName() + " has " + QString::number(components->length()) + " components");
        for (int j = 0; j < components->length(); j++) {

            Usb::Controller* controller = ca->at(i);
            UsbComponent* component = components->at(j);

            // ensure controller node exists directly under root
            QString cname = controller->getName() + " [" + controller->getType().toString() + "]";
            UsbNode* cNode = UsbNode::getNode(cname, controller, NULL);
            cNode = (UsbNode*) insertNode(cNode, dRoot);

            // Device (component) node
            QString dname = component->getName() + " [" + component->getIdentifier()->toString() + "]";
            UsbNode* dNode = UsbNode::getNode(dname, controller, component);
            dNode = (UsbNode*) insertNode(dNode, cNode);

            dNode->setValue(0.0f);
        }
    }

    return true;
}


#if 0
/*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener l) {
    pcs.addPropertyChangeListener(l);
}

/*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener l) {
    pcs.removePropertyChangeListener(l);
}
#endif
}
