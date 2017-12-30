#include "usb_device.h"

//Usb_Device::Usb_Device(QObject *parent) : QObject(parent)
//{

//}
///*public*/ class Usb_Device {


/*public*/ Usb_Device::Usb_Device(QObject *parent) : QObject(parent) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: return
     *  */
    // </editor-fold>
}

/*public*/ void Usb_Device::setDeviceFilter(DeviceFilter f, QList<DeviceFilter> children, Usb_Bus* bus)
{
 prev = NULL;
 this->bus = bus;
 this->f = f;
 num_children = children.count();
}

/*public*/ Usb_Bus* Usb_Device::getBus() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.bus:Lch/ntb/usb/Usb_Bus;
     * 4: areturn
     *  */
    // </editor-fold>
 return bus;
}

/*public*/ Usb_Device* Usb_Device::getChildren() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.children:Lch/ntb/usb/Usb_Device;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ QList<Usb_Config_Descriptor*> Usb_Device::getConfig() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.config:[Lch/ntb/usb/Usb_Config_Descriptor;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ Usb_Device_Descriptor* Usb_Device::getDescriptor() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.descriptor:Lch/ntb/usb/Usb_Device_Descriptor;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ quint8 Usb_Device::getDevnum() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.devnum:B
     * 4: ireturn
     *  */
    // </editor-fold>
}

/*public*/ QString Usb_Device::getFilename() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.filename:Ljava/lang/String;
     * 4: areturn
     *  */
    // </editor-fold>
 return QString("Bus: %1 Port: %2").arg(f.bus).arg(f.port);
}

/*public*/ Usb_Device* Usb_Device::getNext() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.next:Lch/ntb/usb/Usb_Device;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ quint8 Usb_Device::getNumChildren() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.num_children:B
     * 4: ireturn
     *  */
    // </editor-fold>
 return num_children;
}

/*public*/ Usb_Device* Usb_Device::getPrev() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/Usb_Device.prev:Lch/ntb/usb/Usb_Device;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ QString Usb_Device::toString() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: new           java/lang/StringBuilder
     * 3: dup
     * 4: invokespecial java/lang/StringBuilder."<init>":()V
     * 7: ldc           Usb_Device
     * 9: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 12: aload_0
     * 13: getfield      ch/ntb/usb/Usb_Device.filename:Ljava/lang/String;
     * 16: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 19: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 22: areturn
     *  */
    // </editor-fold>
 return QString("Bus: %1 Port: %2 %3:%4 Mfg: %5 Prod: %6").arg(f.bus).arg(f.port).arg(f.vid,0,16).arg(f.pid,0,16).arg(f.manufacturer).arg(f.product);
}
