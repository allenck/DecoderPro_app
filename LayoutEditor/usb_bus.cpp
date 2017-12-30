#include "usb_bus.h"
#include "exceptions.h"
#include <QDebug>
#include "usb_device.h"

//Usb_Bus::Usb_Bus(QObject *parent) : QObject(parent)
//{

//}
// /*public*/ class Usb_Bus {


/*public*/ Usb_Bus::Usb_Bus(QObject *parent) : QObject(parent)
{
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: return
     *  */
    // </editor-fold>
 devHash = QHash<qint16, DeviceFilter>();
 //dBusConn = QDBusConnection::systemBus();

// QDBusReply<QStringList> reply = dBusConn.interface()->registeredServiceNames();
// if(!reply.isValid())
//  throw UnsatisfiedLinkError("No Dbus interfaces available");
// if(!reply.value().contains("biz.acksoft.USBServer"))
//  throw UnsatisfiedLinkError("Required Dbus server not available");

 interface  = new ClientIf("biz.acksoft.USBServer", "/biz/acksoft/USBInterface", QDBusConnection::systemBus());

 connect(interface, SIGNAL(deviceChange(uchar,uchar,bool)), this, SLOT(deviceChange(uchar,uchar,bool)));
 getDevices();
}

void Usb_Bus::deviceChange(uchar bus, uchar port, bool bAdded)
{
 qDebug() << "Device change bus " << bus << " port " <<port << (bAdded?"added":"removed");
 emit notify_deviceChange( bus,  port,  bAdded); // tell model to reload
}

/*public*/ Usb_Device* Usb_Bus::getDevices() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Bus.devices:Lch/ntb/usb/Usb_Device;
     * 4: areturn
     *  */
    // </editor-fold>

 //if(dBusConn.isConnected())
 {
  //QString name = dBusConn.name();

  //QDBusInterface* interface = new QDBusInterface("biz.acksoft.USBServer", "/biz/acksoft/USBInterface", "biz.acksoft.USBInterface",dBusConn);
  int deviceCount;
  QDBusReply<int> reply2 = interface->call(QLatin1String("DeviceCount"));
  if(reply2.isValid())
  {
   deviceCount = reply2.value();
  }
  else
  {
   qDebug() << interface->lastError().name();
  }
  if(deviceCount > 0)
  {
   for(qint32 i = 0; i < deviceCount; i++)
   {
    QDBusMessage result = interface->call(QLatin1String("GetDevice"), QVariant(i));
    QList<QVariant> values;
    if(result.signature() == "av")
    {
//     qDebug() << result;
     QList<QVariant> outArgs = result.arguments();
//         qDebug() << outArgs;
     QVariant first = outArgs.at(0);
//     qDebug() << "first: " << first;
     const QDBusArgument &dbvfirst = first.value<QDBusArgument>();
//     qDebug() << "QDBusArgument current type is" << dbvfirst.currentType();
     //QVariant vfirst = dbvfirst.variant();
     QVariant val;
     dbvfirst.beginArray();
     while(!dbvfirst.atEnd())
     {
      dbvfirst >> val;
      values.append(val);
     }
     dbvfirst.endArray();
    }
    else
      values = result.arguments();

    qDebug() << "values count = " << values.count();
    if(values.count()>= 6)
    {

//     qDebug() << result;
//     QList<QVariant> outArgs = result.arguments();
     DeviceFilter f = DeviceFilter(values);
#if 0
     for(int i = 0; i < values.length(); i++)
     {
      QVariant v = values.at(i);
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
       f.bHasParent = (v.toString() == "true");
       break;
      case 12:
       f.parent.bus = v.toInt();
       break;
      case 13:
       f.parent.port = v.toInt();
       break;
      case 14:
       f.parent.address = v.toInt();
       break;
      case 15:
       f.parent.vid = v.toInt();
       break;
      case 16:
       f.parent.pid = v.toInt();
       break;
//      case 16:
//       f.interface = v.toInt();
//       break;
//      case 17:
//       f.interfaceClass = v.toInt();
       break;
      default:
       break;
      }
     }
#endif
     qDebug() << QString("Bus: %1 Port: %2 Address: %3 %4:%5 Mfg: %6 Prod: %7").arg(f.bus).arg(f.port).arg(f.address).arg(f.vid,4,16,QLatin1Char('0')).arg(f.pid,4,16,QLatin1Char('0')).arg(f.manufacturer).arg(f.product);
     if(f.bHasParent)
     qDebug() << "Parent: ( bus: " << f.parent.bus << " port: " << f.parent.port << ")";

     QDBusReply<QString> reply3 = interface->getDeviceClass(f.bus, f.port);
     if(reply3.isValid())
     {
      f.deviceClass = reply3.value();
     }
     else
     {
      qDebug() << reply3 << "getDeviceClass" << interface->lastError().message();
     }

     DevKey devKey(f.bus, f.address);
     devHash.insertMulti(devKey.key(), f);
     if(!f.bHasParent)
     {

     }
    }
    else
     qDebug() << result;

     qDebug() << "Last error: " <<interface->lastError().name();
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
  Usb_Device* dev = new Usb_Device();
  QList<DeviceFilter> children =  QList<DeviceFilter>();
  foreach (DeviceFilter fc, allDevices)
  {
   if(fc.bHasParent && ((fc.parent.bus ==  f.bus) && (fc.parent.port == f.port)))
    children.append(fc);
  }
  dev->setDeviceFilter(f, children, this);
 }
}
DeviceFilter::DeviceFilter() {}
DeviceFilter::DeviceFilter(QVariantList values)
{
 for(int i = 0; i < values.length(); i++)
 {
  QVariant v = values.at(i);
  switch (i)
  {
  case 0:
   bus = v.toInt();
   break;
  case 1:
   port = v.toInt();
   break;
  case 2:
   address = v.toInt();
   break;
  case 3:
   vid = v.toInt();
   break;
  case 4:
   pid = v.toInt();
   break;
  case 5:
   manufacturer = v.toString();
   break;
  case 6:
   product = v.toString();
   break;
  case 7:
   serialNumber = v.toString();
   break;
  case 8:
   bDeviceClass = v.toInt();
   break;
  case 9:
   bDeviceSubClass = v.toInt();
   break;
  case 10:
   bDeviceProtocol = v.toInt();
   break;
  case 11:
   bHasParent = (v.toString() == "true");
   break;
  case 12:
   parent.bus = v.toInt();
   break;
  case 13:
   parent.port = v.toInt();
   break;
  case 14:
   parent.address = v.toInt();
   break;
  case 15:
   parent.vid = v.toInt();
   break;
  case 16:
   parent.pid = v.toInt();
   break;
//      case 16:
//       f.interface = v.toInt();
//       break;
//      case 17:
//       f.interfaceClass = v.toInt();
   break;
  default:
   break;
  }
 }
}

/*public*/ QString Usb_Bus::getDirname() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Bus.dirname:Ljava/lang/String;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ Usb_Bus* Usb_Bus::getNext() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Bus.next:Lch/ntb/usb/Usb_Bus;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ Usb_Bus* Usb_Bus::getPrev() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Bus.prev:Lch/ntb/usb/Usb_Bus;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ Usb_Device* Usb_Bus::getRootDev() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Bus.root_dev:Lch/ntb/usb/Usb_Device;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ long Usb_Bus::getLocation() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Bus.location:J
     * 4: lreturn
     *  */
    // </editor-fold>
}

/*public*/ QString Usb_Bus::toString() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: new           java/lang/StringBuilder
     * 3: dup
     * 4: invokespecial java/lang/StringBuilder."<init>":()V
     * 7: ldc           Usb_Bus
     * 9: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 12: aload_0
     * 13: getfield      ch/ntb/usb/Usb_Bus.dirname:Ljava/lang/String;
     * 16: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 19: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 22: areturn
     *  */
    // </editor-fold>
}

/*public*/ QList<DeviceFilter> Usb_Bus::getChildrenOf(quint8 bus, quint8 port)
{
 QList<DeviceFilter> children = QList<DeviceFilter>();
 QList<DeviceFilter> allDevices = devHash.values();
 foreach(DeviceFilter f, allDevices)
 {
  if(f.parent.bus == bus && f.parent.port == port)
  {
   children.append(f);
  }
 }
 return children;
}

/*public*/ DeviceFilter Usb_Bus::getDevice(quint8 bus, quint8 address)
{
 QVariantList list = interface->GetDeviceByKey(bus, address);
 return DeviceFilter(list);
}
