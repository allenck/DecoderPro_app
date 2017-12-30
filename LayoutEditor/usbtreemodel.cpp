#include "usbtreemodel.h"
#include "loggerfactory.h"
#include "usb_bus.h"
#include "usb_device.h"
#include "jtextarea.h"
//#include "defaultmutabletreenode.h"
#include "vptr.h"
#include <QDebug>

UsbTreeItem::UsbTreeItem(const QList<QVariant> &data, DeviceFilter f, DefaultTreeItem *parent) : DefaultTreeItem(data, QVariant(), parent)
{
 QVariant var;
 var.setValue(f);
 userData = var;
 UsbTreeModel::itemHash->insert(DevKey(f.bus,f.address).key(), this);
 setObjectName(QString("%1:%2").arg(f.bus,3,10,QLatin1Char('0')).arg(f.address,3,10,QLatin1Char('0')));
}
void UsbTreeItem::clear()
{

}

bool UsbTreeItem::removeChild(DefaultTreeItem * item)
{
 DeviceFilter f = item->userData.value<DeviceFilter>();
 UsbTreeModel::itemHash->remove(DevKey(f.bus,f.address).key());
}

/*static*/ QHash<int, UsbTreeItem*>* UsbTreeModel::itemHash = new QHash<int, UsbTreeItem*>();

///*public*/ class UsbTreeModel : public TreeModel //, TreeSelectionListener {
/*private*/ /*static*/ /*final*/ QString UsbTreeModel::USB_ROOT = "USB";


/*public*/ UsbTreeModel::UsbTreeModel(Usb_Bus* rootBus, JTextArea* textArea, QObject* parent) : DefaultTreeModel1(true, parent) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: aload_0
     * 5: new           java/util/Vector
     * 8: dup
     * 9: invokespecial java/util/Vector."<init>":()V
     * 12: putfield      ch/ntb/usb/usbView/UsbTreeModel.treeModelListeners:Ljava/util/Vector;
     * 15: aload_0
     * 16: aload_1
     * 17: putfield      ch/ntb/usb/usbView/UsbTreeModel.rootBus:Lch/ntb/usb/Usb_Bus;
     * 20: aload_0
     * 21: aload_2
     * 22: putfield      ch/ntb/usb/usbView/UsbTreeModel.textArea:Ljavax/swing/JTextArea;
     * 25: return
     *  */
    // </editor-fold>
 log = LoggerFactory::getLogger("UsbTreeModel");
 if(qobject_cast<JTree*>(parent) != NULL)
  tree = (JTree*)parent;
 textArea = new JTextArea();
 this->rootBus = rootBus;
 qRegisterMetaType<Usb_Device>("Usb_Device");

 QList<QVariant> rootData; // Define the number of columns in the model.
 rootData<<"Name" << "Manufacturer" << "Product";
 rootItem = new UsbTreeItem(rootData, DeviceFilter(), NULL);
 itemHash = new QHash<int, UsbTreeItem*>();
 connect(rootBus, SIGNAL(notify_deviceChange(uchar,uchar,bool)), this, SLOT(deviceChange(uchar,uchar,bool)));
}

/*public*/ QVariant UsbTreeModel::data(const QModelIndex &index, int role) const
{
 DefaultTreeItem *item = static_cast<DefaultTreeItem*>(index.internalPointer());

 if(role == Qt::DisplayRole)
 {
  if(item->userData.canConvert<QString>() && index.column() == 0)
   return item->userData.toString();
  DeviceFilter f = item->userData.value<DeviceFilter>();

  switch (index.column())
  {
   case 0:
    return QString("%1:%2").arg(f.bus,3,10,QLatin1Char('0')).arg(f.address,3,10,QLatin1Char('0'));
   case 1:
    return f.manufacturer;
   case 2:
   return f.product;
  }
 }
 return DefaultTreeModel1::data(index,role);
}


///*public*/ QObject* UsbTreeModel::getRoot() {
//    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
//    /* 0: ldc           USB
//     * 2: areturn
//     *  */
//    // </editor-fold>
// return DefaultTreeModel::getRoot();
//}
#if 0
/*public*/ QObject* UsbTreeModel::getChild(QObject* parent, int index) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: instanceof    java/lang/String
     * 4: ifeq          53
     * 7: aload_1
     * 8: checkcast     java/lang/String
     * 11: ldc           USB
     * 13: invokevirtual java/lang/String.compareTo:(Ljava/lang/String;)I
     * 16: ifne          53
     * 19: aload_0
     * 20: getfield      ch/ntb/usb/usbView/UsbTreeModel.rootBus:Lch/ntb/usb/Usb_Bus;
     * 23: astore_3
     * 24: iconst_0
     * 25: istore        4
     * 27: aload_3
     * 28: ifnull        50
     * 31: iload         4
     * 33: iload_2
     * 34: if_icmpne     39
     * 37: aload_3
     * 38: areturn
     * 39: aload_3
     * 40: invokevirtual ch/ntb/usb/Usb_Bus.getNext:()Lch/ntb/usb/Usb_Bus;
     * 43: astore_3
     * 44: iinc          4, 1
     * 47: goto          27
     * 50: goto          222
     * 53: aload_1
     * 54: instanceof    ch/ntb/usb/Usb_Bus
     * 57: ifeq          96
     * 60: aload_1
     * 61: checkcast     ch/ntb/usb/Usb_Bus
     * 64: invokevirtual ch/ntb/usb/Usb_Bus.getDevices:()Lch/ntb/usb/Usb_Device;
     * 67: astore_3
     * 68: iconst_0
     * 69: istore        4
     * 71: aload_3
     * 72: ifnull        94
     * 75: iload         4
     * 77: iload_2
     * 78: if_icmpne     83
     * 81: aload_3
     * 82: areturn
     * 83: iinc          4, 1
     * 86: aload_3
     * 87: invokevirtual ch/ntb/usb/Usb_Device.getNext:()Lch/ntb/usb/Usb_Device;
     * 90: astore_3
     * 91: goto          71
     * 94: aconst_null
     * 95: areturn
     * 96: aload_1
     * 97: instanceof    ch/ntb/usb/Usb_Device
     * 100: ifeq          141
     * 103: aload_1
     * 104: checkcast     ch/ntb/usb/Usb_Device
     * 107: astore_3
     * 108: iload_2
     * 109: ifne          117
     * 112: aload_3
     * 113: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 116: areturn
     * 117: aload_3
     * 118: invokevirtual ch/ntb/usb/Usb_Device.getConfig:()[Lch/ntb/usb/Usb_Config_Descriptor;
     * 121: astore        4
     * 123: iload_2
     * 124: aload         4
     * 126: arraylength
     * 127: iconst_1
     * 128: iadd
     * 129: if_icmplt     134
     * 132: aconst_null
     * 133: areturn
     * 134: aload         4
     * 136: iload_2
     * 137: iconst_1
     * 138: isub
     * 139: aaload
     * 140: areturn
     * 141: aload_1
     * 142: instanceof    ch/ntb/usb/Usb_Config_Descriptor
     * 145: ifeq          168
     * 148: aload_1
     * 149: checkcast     ch/ntb/usb/Usb_Config_Descriptor
     * 152: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getInterface:()[Lch/ntb/usb/Usb_Interface;
     * 155: astore_3
     * 156: iload_2
     * 157: aload_3
     * 158: arraylength
     * 159: if_icmplt     164
     * 162: aconst_null
     * 163: areturn
     * 164: aload_3
     * 165: iload_2
     * 166: aaload
     * 167: areturn
     * 168: aload_1
     * 169: instanceof    ch/ntb/usb/Usb_Interface
     * 172: ifeq          195
     * 175: aload_1
     * 176: checkcast     ch/ntb/usb/Usb_Interface
     * 179: invokevirtual ch/ntb/usb/Usb_Interface.getAltsetting:()[Lch/ntb/usb/Usb_Interface_Descriptor;
     * 182: astore_3
     * 183: iload_2
     * 184: aload_3
     * 185: arraylength
     * 186: if_icmplt     191
     * 189: aconst_null
     * 190: areturn
     * 191: aload_3
     * 192: iload_2
     * 193: aaload
     * 194: areturn
     * 195: aload_1
     * 196: instanceof    ch/ntb/usb/Usb_Interface_Descriptor
     * 199: ifeq          222
     * 202: aload_1
     * 203: checkcast     ch/ntb/usb/Usb_Interface_Descriptor
     * 206: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getEndpoint:()[Lch/ntb/usb/Usb_Endpoint_Descriptor;
     * 209: astore_3
     * 210: iload_2
     * 211: aload_3
     * 212: arraylength
     * 213: if_icmplt     218
     * 216: aconst_null
     * 217: areturn
     * 218: aload_3
     * 219: iload_2
     * 220: aaload
     * 221: areturn
     * 222: aconst_null
     * 223: areturn
     *  */
    // </editor-fold>
}

/*public*/ int UsbTreeModel::getChildCount(QObject* parent) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: instanceof    java/lang/String
     * 4: ifeq          43
     * 7: aload_1
     * 8: checkcast     java/lang/String
     * 11: ldc           USB
     * 13: invokevirtual java/lang/String.compareTo:(Ljava/lang/String;)I
     * 16: ifne          43
     * 19: iconst_0
     * 20: istore_2
     * 21: aload_0
     * 22: getfield      ch/ntb/usb/usbView/UsbTreeModel.rootBus:Lch/ntb/usb/Usb_Bus;
     * 25: astore_3
     * 26: aload_3
     * 27: ifnull        41
     * 30: iinc          2, 1
     * 33: aload_3
     * 34: invokevirtual ch/ntb/usb/Usb_Bus.getNext:()Lch/ntb/usb/Usb_Bus;
     * 37: astore_3
     * 38: goto          26
     * 41: iload_2
     * 42: ireturn
     * 43: aload_1
     * 44: instanceof    ch/ntb/usb/Usb_Bus
     * 47: ifeq          77
     * 50: aload_1
     * 51: checkcast     ch/ntb/usb/Usb_Bus
     * 54: invokevirtual ch/ntb/usb/Usb_Bus.getDevices:()Lch/ntb/usb/Usb_Device;
     * 57: astore_2
     * 58: iconst_0
     * 59: istore_3
     * 60: aload_2
     * 61: ifnull        75
     * 64: iinc          3, 1
     * 67: aload_2
     * 68: invokevirtual ch/ntb/usb/Usb_Device.getNext:()Lch/ntb/usb/Usb_Device;
     * 71: astore_2
     * 72: goto          60
     * 75: iload_3
     * 76: ireturn
     * 77: aload_1
     * 78: instanceof    ch/ntb/usb/Usb_Device
     * 81: ifeq          95
     * 84: aload_1
     * 85: checkcast     ch/ntb/usb/Usb_Device
     * 88: invokevirtual ch/ntb/usb/Usb_Device.getConfig:()[Lch/ntb/usb/Usb_Config_Descriptor;
     * 91: arraylength
     * 92: iconst_1
     * 93: iadd
     * 94: ireturn
     * 95: aload_1
     * 96: instanceof    ch/ntb/usb/Usb_Config_Descriptor
     * 99: ifeq          111
     * 102: aload_1
     * 103: checkcast     ch/ntb/usb/Usb_Config_Descriptor
     * 106: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getInterface:()[Lch/ntb/usb/Usb_Interface;
     * 109: arraylength
     * 110: ireturn
     * 111: aload_1
     * 112: instanceof    ch/ntb/usb/Usb_Interface
     * 115: ifeq          127
     * 118: aload_1
     * 119: checkcast     ch/ntb/usb/Usb_Interface
     * 122: invokevirtual ch/ntb/usb/Usb_Interface.getAltsetting:()[Lch/ntb/usb/Usb_Interface_Descriptor;
     * 125: arraylength
     * 126: ireturn
     * 127: aload_1
     * 128: instanceof    ch/ntb/usb/Usb_Interface_Descriptor
     * 131: ifeq          143
     * 134: aload_1
     * 135: checkcast     ch/ntb/usb/Usb_Interface_Descriptor
     * 138: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getEndpoint:()[Lch/ntb/usb/Usb_Endpoint_Descriptor;
     * 141: arraylength
     * 142: ireturn
     * 143: iconst_0
     * 144: ireturn
     *  */
    // </editor-fold>
}

/*public*/ bool UsbTreeModel::isLeaf(QObject* node) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_0
     * 1: ireturn
     *  */
    // </editor-fold>
}

/*public*/ void UsbTreeModel::valueForPathChanged(TreePath* path, QObject* newValue) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: getstatic     java/lang/System.out:Ljava/io/PrintStream;
     * 3: new           java/lang/StringBuilder
     * 6: dup
     * 7: invokespecial java/lang/StringBuilder."<init>":()V
     * 10: ldc           *** valueForPathChanged :
     * 12: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 15: aload_1
     * 16: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
     * 19: ldc            -->
     * 21: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 24: aload_2
     * 25: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
     * 28: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 31: invokevirtual java/io/PrintStream.println:(Ljava/lang/String;)V
     * 34: return
     *  */
    // </editor-fold>
}

/*public*/ int UsbTreeModel::getIndexOfChild(QObject* parent, QObject* child) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_0
     * 1: ireturn
     *  */
    // </editor-fold>
}

/*public*/ void UsbTreeModel::addTreeModelListener(TreeModelListener* l) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbTreeModel.treeModelListeners:Ljava/util/Vector;
     * 4: aload_1
     * 5: invokevirtual java/util/Vector.addElement:(Ljava/lang/Object;)V
     * 8: return
     *  */
    // </editor-fold>
}

/*public*/ void UsbTreeModel::removeTreeModelListener(TreeModelListener* l) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      ch/ntb/usb/usbView/UsbTreeModel.treeModelListeners:Ljava/util/Vector;
     * 4: aload_1
     * 5: invokevirtual java/util/Vector.removeElement:(Ljava/lang/Object;)Z
     * 8: pop
     * 9: return
     *  */
    // </editor-fold>
}

/*protected*/ void UsbTreeModel::fireTreeStructureChanged(Usb_Bus* newRootBus) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: aload_1
     * 2: putfield      ch/ntb/usb/usbView/UsbTreeModel.rootBus:Lch/ntb/usb/Usb_Bus;
     * 5: aload_0
     * 6: getfield      ch/ntb/usb/usbView/UsbTreeModel.treeModelListeners:Ljava/util/Vector;
     * 9: invokevirtual java/util/Vector.size:()I
     * 12: istore_2
     * 13: new           javax/swing/event/TreeModelEvent
     * 16: dup
     * 17: aload_0
     * 18: iconst_1
     * 19: anewarray     java/lang/Object
     * 22: dup
     * 23: iconst_0
     * 24: aload_1
     * 25: aastore
     * 26: invokespecial javax/swing/event/TreeModelEvent."<init>":(Ljava/lang/Object;[Ljava/lang/Object;)V
     * 29: astore_3
     * 30: iconst_0
     * 31: istore        4
     * 33: iload         4
     * 35: iload_2
     * 36: if_icmpge     63
     * 39: aload_0
     * 40: getfield      ch/ntb/usb/usbView/UsbTreeModel.treeModelListeners:Ljava/util/Vector;
     * 43: iload         4
     * 45: invokevirtual java/util/Vector.elementAt:(I)Ljava/lang/Object;
     * 48: checkcast     javax/swing/event/TreeModelListener
     * 51: aload_3
     * 52: invokeinterface javax/swing/event/TreeModelListener.treeStructureChanged:(Ljavax/swing/event/TreeModelEvent;)V
     * 57: iinc          4, 1
     * 60: goto          33
     * 63: return
     *  */
    // </editor-fold>
}

/*public*/ void UsbTreeModel::valueChanged(TreeSelectionEvent* e) {
#if 0
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: invokevirtual javax/swing/event/TreeSelectionEvent.getSource:()Ljava/lang/Object;
     * 4: checkcast     javax/swing/JTree
     * 7: astore_2
     * 8: aload_2
     * 9: invokevirtual javax/swing/JTree.getLastSelectedPathComponent:()Ljava/lang/Object;
     * 12: astore_3
     * 13: aload_3
     * 14: instanceof    ch/ntb/usb/Usb_Bus
     * 17: ifeq          123
     * 20: aload_3
     * 21: checkcast     ch/ntb/usb/Usb_Bus
     * 24: astore        4
     * 26: new           java/lang/StringBuffer
     * 29: dup
     * 30: ldc           Usb_Bus\n
     * 32: invokespecial java/lang/StringBuffer."<init>":(Ljava/lang/String;)V
     * 35: astore        5
     * 37: aload         5
     * 39: new           java/lang/StringBuilder
     * 42: dup
     * 43: invokespecial java/lang/StringBuilder."<init>":()V
     * 46: ldc           \tdirname:
     * 48: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 51: aload         4
     * 53: invokevirtual ch/ntb/usb/Usb_Bus.getDirname:()Ljava/lang/String;
     * 56: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 59: ldc           \n
     * 61: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 64: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 67: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 70: pop
     * 71: aload         5
     * 73: new           java/lang/StringBuilder
     * 76: dup
     * 77: invokespecial java/lang/StringBuilder."<init>":()V
     * 80: ldc           \tlocation: 0x
     * 82: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 85: aload         4
     * 87: invokevirtual ch/ntb/usb/Usb_Bus.getLocation:()J
     * 90: invokestatic  java/lang/Long.toHexString:(J)Ljava/lang/String;
     * 93: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 96: ldc           \n
     * 98: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 101: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 104: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 107: pop
     * 108: aload_0
     * 109: getfield      ch/ntb/usb/usbView/UsbTreeModel.textArea:Ljavax/swing/JTextArea;
     * 112: aload         5
     * 114: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 117: invokevirtual javax/swing/JTextArea.setText:(Ljava/lang/String;)V
     * 120: goto          3075
     * 123: aload_3
     * 124: instanceof    ch/ntb/usb/Usb_Device
     * 127: ifeq          264
     * 130: aload_3
     * 131: checkcast     ch/ntb/usb/Usb_Device
     * 134: astore        4
     * 136: new           java/lang/StringBuffer
     * 139: dup
     * 140: ldc           Usb_Device\n
     * 142: invokespecial java/lang/StringBuffer."<init>":(Ljava/lang/String;)V
     * 145: astore        5
     * 147: aload         5
     * 149: new           java/lang/StringBuilder
     * 152: dup
     * 153: invokespecial java/lang/StringBuilder."<init>":()V
     * 156: ldc           \tfilename:
     * 158: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 161: aload         4
     * 163: invokevirtual ch/ntb/usb/Usb_Device.getFilename:()Ljava/lang/String;
     * 166: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 169: ldc           \n
     * 171: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 174: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 177: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 180: pop
     * 181: aload         5
     * 183: new           java/lang/StringBuilder
     * 186: dup
     * 187: invokespecial java/lang/StringBuilder."<init>":()V
     * 190: ldc           \tdevnum:
     * 192: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 195: aload         4
     * 197: invokevirtual ch/ntb/usb/Usb_Device.getDevnum:()B
     * 200: invokevirtual java/lang/StringBuilder.append:(I)Ljava/lang/StringBuilder;
     * 203: ldc           \n
     * 205: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 208: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 211: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 214: pop
     * 215: aload         5
     * 217: new           java/lang/StringBuilder
     * 220: dup
     * 221: invokespecial java/lang/StringBuilder."<init>":()V
     * 224: ldc           \tnum_children:
     * 226: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 229: aload         4
     * 231: invokevirtual ch/ntb/usb/Usb_Device.getNumChildren:()B
     * 234: invokevirtual java/lang/StringBuilder.append:(I)Ljava/lang/StringBuilder;
     * 237: ldc           \n
     * 239: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 242: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 245: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 248: pop
     * 249: aload_0
     * 250: getfield      ch/ntb/usb/usbView/UsbTreeModel.textArea:Ljavax/swing/JTextArea;
     * 253: aload         5
     * 255: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 258: invokevirtual javax/swing/JTextArea.setText:(Ljava/lang/String;)V
     * 261: goto          3075
     * 264: aload_3
     * 265: instanceof    ch/ntb/usb/Usb_Device_Descriptor
     * 268: ifeq          1212
     * 271: aload_3
     * 272: checkcast     ch/ntb/usb/Usb_Device_Descriptor
     * 275: astore        4
     * 277: new           java/lang/StringBuffer
     * 280: dup
     * 281: ldc           Usb_Device_Descriptor\n
     * 283: invokespecial java/lang/StringBuffer."<init>":(Ljava/lang/String;)V
     * 286: astore        5
     * 288: aload         5
     * 290: new           java/lang/StringBuilder
     * 293: dup
     * 294: invokespecial java/lang/StringBuilder."<init>":()V
     * 297: ldc           \tblenght: 0x
     * 299: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 302: aload         4
     * 304: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBLength:()B
     * 307: sipush        255
     * 310: iand
     * 311: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 314: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 317: ldc           \n
     * 319: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 322: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 325: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 328: pop
     * 329: aload         5
     * 331: new           java/lang/StringBuilder
     * 334: dup
     * 335: invokespecial java/lang/StringBuilder."<init>":()V
     * 338: ldc           \tbDescriptorType: 0x
     * 340: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 343: aload         4
     * 345: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBDescriptorType:()B
     * 348: sipush        255
     * 351: iand
     * 352: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 355: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 358: ldc           \n
     * 360: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 363: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 366: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 369: pop
     * 370: aload         5
     * 372: new           java/lang/StringBuilder
     * 375: dup
     * 376: invokespecial java/lang/StringBuilder."<init>":()V
     * 379: ldc           \tbcdUSB: 0x
     * 381: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 384: aload         4
     * 386: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBcdUSB:()S
     * 389: ldc           65535
     * 391: iand
     * 392: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 395: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 398: ldc           \n
     * 400: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 403: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 406: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 409: pop
     * 410: aload         5
     * 412: new           java/lang/StringBuilder
     * 415: dup
     * 416: invokespecial java/lang/StringBuilder."<init>":()V
     * 419: ldc           \tbDeviceClass: 0x
     * 421: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 424: aload         4
     * 426: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBDeviceClass:()B
     * 429: sipush        255
     * 432: iand
     * 433: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 436: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 439: ldc           \n
     * 441: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 444: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 447: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 450: pop
     * 451: aload         5
     * 453: new           java/lang/StringBuilder
     * 456: dup
     * 457: invokespecial java/lang/StringBuilder."<init>":()V
     * 460: ldc           \tbDeviceSubClass: 0x
     * 462: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 465: aload         4
     * 467: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBDeviceSubClass:()B
     * 470: sipush        255
     * 473: iand
     * 474: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 477: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 480: ldc           \n
     * 482: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 485: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 488: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 491: pop
     * 492: aload         5
     * 494: new           java/lang/StringBuilder
     * 497: dup
     * 498: invokespecial java/lang/StringBuilder."<init>":()V
     * 501: ldc           \tbDeviceProtocol: 0x
     * 503: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 506: aload         4
     * 508: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBDeviceProtocol:()B
     * 511: sipush        255
     * 514: iand
     * 515: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 518: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 521: ldc           \n
     * 523: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 526: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 529: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 532: pop
     * 533: aload         5
     * 535: new           java/lang/StringBuilder
     * 538: dup
     * 539: invokespecial java/lang/StringBuilder."<init>":()V
     * 542: ldc           \tbMaxPacketSize0: 0x
     * 544: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 547: aload         4
     * 549: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBMaxPacketSize0:()B
     * 552: sipush        255
     * 555: iand
     * 556: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 559: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 562: ldc            (
     * 564: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 567: aload         4
     * 569: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBMaxPacketSize0:()B
     * 572: invokevirtual java/lang/StringBuilder.append:(I)Ljava/lang/StringBuilder;
     * 575: ldc           )\n
     * 577: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 580: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 583: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 586: pop
     * 587: aload         5
     * 589: new           java/lang/StringBuilder
     * 592: dup
     * 593: invokespecial java/lang/StringBuilder."<init>":()V
     * 596: ldc           \tidVendor: 0x
     * 598: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 601: aload         4
     * 603: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIdVendor:()S
     * 606: ldc           65535
     * 608: iand
     * 609: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 612: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 615: ldc           \n
     * 617: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 620: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 623: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 626: pop
     * 627: aload         5
     * 629: new           java/lang/StringBuilder
     * 632: dup
     * 633: invokespecial java/lang/StringBuilder."<init>":()V
     * 636: ldc           \tidProduct: 0x
     * 638: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 641: aload         4
     * 643: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIdProduct:()S
     * 646: ldc           65535
     * 648: iand
     * 649: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 652: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 655: ldc           \n
     * 657: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 660: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 663: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 666: pop
     * 667: aload         5
     * 669: new           java/lang/StringBuilder
     * 672: dup
     * 673: invokespecial java/lang/StringBuilder."<init>":()V
     * 676: ldc           \tbcdDevice: 0x
     * 678: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 681: aload         4
     * 683: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBcdDevice:()S
     * 686: sipush        255
     * 689: iand
     * 690: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 693: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 696: ldc           \n
     * 698: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 701: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 704: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 707: pop
     * 708: aload         5
     * 710: new           java/lang/StringBuilder
     * 713: dup
     * 714: invokespecial java/lang/StringBuilder."<init>":()V
     * 717: ldc           \tiManufacturer: 0x
     * 719: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 722: aload         4
     * 724: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIManufacturer:()B
     * 727: sipush        255
     * 730: iand
     * 731: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 734: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 737: ldc           \n
     * 739: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 742: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 745: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 748: pop
     * 749: aload         5
     * 751: new           java/lang/StringBuilder
     * 754: dup
     * 755: invokespecial java/lang/StringBuilder."<init>":()V
     * 758: ldc           \tiProduct: 0x
     * 760: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 763: aload         4
     * 765: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIProduct:()B
     * 768: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 771: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 774: ldc           \n
     * 776: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 779: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 782: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 785: pop
     * 786: aload         5
     * 788: new           java/lang/StringBuilder
     * 791: dup
     * 792: invokespecial java/lang/StringBuilder."<init>":()V
     * 795: ldc           \tiSerialNumber: 0x
     * 797: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 800: aload         4
     * 802: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getISerialNumber:()B
     * 805: sipush        255
     * 808: iand
     * 809: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 812: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 815: ldc           \n
     * 817: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 820: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 823: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 826: pop
     * 827: aload         5
     * 829: new           java/lang/StringBuilder
     * 832: dup
     * 833: invokespecial java/lang/StringBuilder."<init>":()V
     * 836: ldc           \tbNumConfigurations: 0x
     * 838: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 841: aload         4
     * 843: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getBNumConfigurations:()B
     * 846: sipush        255
     * 849: iand
     * 850: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 853: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 856: ldc           \n
     * 858: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 861: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 864: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 867: pop
     * 868: aload_0
     * 869: getfield      ch/ntb/usb/usbView/UsbTreeModel.rootBus:Lch/ntb/usb/Usb_Bus;
     * 872: astore        6
     * 874: aload         6
     * 876: ifnull        1197
     * 879: aload         6
     * 881: invokevirtual ch/ntb/usb/Usb_Bus.getDevices:()Lch/ntb/usb/Usb_Device;
     * 884: astore        7
     * 886: aload         7
     * 888: ifnull        1187
     * 891: aload         7
     * 893: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 896: astore        8
     * 898: aload         7
     * 900: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 903: ifnull        1177
     * 906: aload         7
     * 908: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 911: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIManufacturer:()B
     * 914: ifgt          939
     * 917: aload         7
     * 919: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 922: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIProduct:()B
     * 925: ifgt          939
     * 928: aload         7
     * 930: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 933: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getISerialNumber:()B
     * 936: ifle          1177
     * 939: aload         8
     * 941: aload         4
     * 943: invokevirtual java/lang/Object.equals:(Ljava/lang/Object;)Z
     * 946: ifeq          1177
     * 949: aload         7
     * 951: invokestatic  ch/ntb/usb/LibusbJava.usb_open:(Lch/ntb/usb/Usb_Device;)J
     * 954: lstore        9
     * 956: aload         5
     * 958: ldc           \nString descriptors\n
     * 960: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 963: pop
     * 964: lload         9
     * 966: lconst_0
     * 967: lcmp
     * 968: ifgt          982
     * 971: aload         5
     * 973: ldc           \terror opening the device\n
     * 975: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 978: pop
     * 979: goto          1187
     * 982: aload         7
     * 984: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 987: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIManufacturer:()B
     * 990: ifle          1045
     * 993: lload         9
     * 995: aload         4
     * 997: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIManufacturer:()B
     * 1000: invokestatic  ch/ntb/usb/LibusbJava.usb_get_string_simple:(JI)Ljava/lang/String;
     * 1003: astore        11
     * 1005: aload         11
     * 1007: ifnonnull     1014
     * 1010: ldc           unable to fetch manufacturer string
     * 1012: astore        11
     * 1014: aload         5
     * 1016: new           java/lang/StringBuilder
     * 1019: dup
     * 1020: invokespecial java/lang/StringBuilder."<init>":()V
     * 1023: ldc           \tiManufacturer:
     * 1025: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1028: aload         11
     * 1030: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1033: ldc           \n
     * 1035: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1038: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1041: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1044: pop
     * 1045: aload         7
     * 1047: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 1050: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIProduct:()B
     * 1053: ifle          1108
     * 1056: lload         9
     * 1058: aload         4
     * 1060: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getIProduct:()B
     * 1063: invokestatic  ch/ntb/usb/LibusbJava.usb_get_string_simple:(JI)Ljava/lang/String;
     * 1066: astore        11
     * 1068: aload         11
     * 1070: ifnonnull     1077
     * 1073: ldc           unable to fetch product string
     * 1075: astore        11
     * 1077: aload         5
     * 1079: new           java/lang/StringBuilder
     * 1082: dup
     * 1083: invokespecial java/lang/StringBuilder."<init>":()V
     * 1086: ldc           \tiProduct:
     * 1088: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1091: aload         11
     * 1093: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1096: ldc           \n
     * 1098: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1101: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1104: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1107: pop
     * 1108: aload         7
     * 1110: invokevirtual ch/ntb/usb/Usb_Device.getDescriptor:()Lch/ntb/usb/Usb_Device_Descriptor;
     * 1113: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getISerialNumber:()B
     * 1116: ifle          1171
     * 1119: lload         9
     * 1121: aload         4
     * 1123: invokevirtual ch/ntb/usb/Usb_Device_Descriptor.getISerialNumber:()B
     * 1126: invokestatic  ch/ntb/usb/LibusbJava.usb_get_string_simple:(JI)Ljava/lang/String;
     * 1129: astore        11
     * 1131: aload         11
     * 1133: ifnonnull     1140
     * 1136: ldc           unable to fetch serial number string
     * 1138: astore        11
     * 1140: aload         5
     * 1142: new           java/lang/StringBuilder
     * 1145: dup
     * 1146: invokespecial java/lang/StringBuilder."<init>":()V
     * 1149: ldc           \tiSerialNumber:
     * 1151: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1154: aload         11
     * 1156: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1159: ldc           \n
     * 1161: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1164: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1167: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1170: pop
     * 1171: lload         9
     * 1173: invokestatic  ch/ntb/usb/LibusbJava.usb_close:(J)I
     * 1176: pop
     * 1177: aload         7
     * 1179: invokevirtual ch/ntb/usb/Usb_Device.getNext:()Lch/ntb/usb/Usb_Device;
     * 1182: astore        7
     * 1184: goto          886
     * 1187: aload         6
     * 1189: invokevirtual ch/ntb/usb/Usb_Bus.getNext:()Lch/ntb/usb/Usb_Bus;
     * 1192: astore        6
     * 1194: goto          874
     * 1197: aload_0
     * 1198: getfield      ch/ntb/usb/usbView/UsbTreeModel.textArea:Ljavax/swing/JTextArea;
     * 1201: aload         5
     * 1203: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 1206: invokevirtual javax/swing/JTextArea.setText:(Ljava/lang/String;)V
     * 1209: goto          3075
     * 1212: aload_3
     * 1213: instanceof    ch/ntb/usb/Usb_Config_Descriptor
     * 1216: ifeq          1798
     * 1219: aload_3
     * 1220: checkcast     ch/ntb/usb/Usb_Config_Descriptor
     * 1223: astore        4
     * 1225: new           java/lang/StringBuffer
     * 1228: dup
     * 1229: ldc           Usb_Config_Descriptor\n
     * 1231: invokespecial java/lang/StringBuffer."<init>":(Ljava/lang/String;)V
     * 1234: astore        5
     * 1236: aload         5
     * 1238: new           java/lang/StringBuilder
     * 1241: dup
     * 1242: invokespecial java/lang/StringBuilder."<init>":()V
     * 1245: ldc           \tblenght: 0x
     * 1247: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1250: aload         4
     * 1252: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getBLength:()B
     * 1255: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1258: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1261: ldc           \n
     * 1263: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1266: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1269: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1272: pop
     * 1273: aload         5
     * 1275: new           java/lang/StringBuilder
     * 1278: dup
     * 1279: invokespecial java/lang/StringBuilder."<init>":()V
     * 1282: ldc           \tbDescriptorType: 0x
     * 1284: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1287: aload         4
     * 1289: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getBDescriptorType:()B
     * 1292: sipush        255
     * 1295: iand
     * 1296: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1299: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1302: ldc           \n
     * 1304: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1307: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1310: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1313: pop
     * 1314: aload         5
     * 1316: new           java/lang/StringBuilder
     * 1319: dup
     * 1320: invokespecial java/lang/StringBuilder."<init>":()V
     * 1323: ldc           \tbNumInterfaces: 0x
     * 1325: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1328: aload         4
     * 1330: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getBNumInterfaces:()B
     * 1333: sipush        255
     * 1336: iand
     * 1337: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1340: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1343: ldc           \n
     * 1345: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1348: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1351: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1354: pop
     * 1355: aload         5
     * 1357: new           java/lang/StringBuilder
     * 1360: dup
     * 1361: invokespecial java/lang/StringBuilder."<init>":()V
     * 1364: ldc           \tbConfigurationValue: 0x
     * 1366: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1369: aload         4
     * 1371: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getBConfigurationValue:()B
     * 1374: sipush        255
     * 1377: iand
     * 1378: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1381: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1384: ldc           \n
     * 1386: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1389: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1392: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1395: pop
     * 1396: aload         5
     * 1398: new           java/lang/StringBuilder
     * 1401: dup
     * 1402: invokespecial java/lang/StringBuilder."<init>":()V
     * 1405: ldc           \tiConfiguration: 0x
     * 1407: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1410: aload         4
     * 1412: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getIConfiguration:()B
     * 1415: sipush        255
     * 1418: iand
     * 1419: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1422: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1425: ldc           \n
     * 1427: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1430: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1433: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1436: pop
     * 1437: aload         5
     * 1439: new           java/lang/StringBuilder
     * 1442: dup
     * 1443: invokespecial java/lang/StringBuilder."<init>":()V
     * 1446: ldc           \tbmAttributes: 0x
     * 1448: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1451: aload         4
     * 1453: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getBmAttributes:()B
     * 1456: sipush        255
     * 1459: iand
     * 1460: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1463: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1466: ldc           \n
     * 1468: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1471: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1474: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1477: pop
     * 1478: aload         5
     * 1480: new           java/lang/StringBuilder
     * 1483: dup
     * 1484: invokespecial java/lang/StringBuilder."<init>":()V
     * 1487: ldc           \tMaxPower [mA]: 0x
     * 1489: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1492: aload         4
     * 1494: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getMaxPower:()B
     * 1497: sipush        255
     * 1500: iand
     * 1501: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1504: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1507: ldc            (
     * 1509: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1512: aload         4
     * 1514: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getMaxPower:()B
     * 1517: invokevirtual java/lang/StringBuilder.append:(I)Ljava/lang/StringBuilder;
     * 1520: ldc           )\n
     * 1522: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1525: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1528: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1531: pop
     * 1532: aload         5
     * 1534: new           java/lang/StringBuilder
     * 1537: dup
     * 1538: invokespecial java/lang/StringBuilder."<init>":()V
     * 1541: ldc           \textralen: 0x
     * 1543: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1546: aload         4
     * 1548: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getExtralen:()I
     * 1551: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1554: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1557: ldc           \n
     * 1559: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1562: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1565: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1568: pop
     * 1569: aload         5
     * 1571: new           java/lang/StringBuilder
     * 1574: dup
     * 1575: invokespecial java/lang/StringBuilder."<init>":()V
     * 1578: ldc           \textra:
     * 1580: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1583: aload_0
     * 1584: aload         4
     * 1586: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getExtra:()[B
     * 1589: invokespecial ch/ntb/usb/usbView/UsbTreeModel.extraDescriptorToString:([B)Ljava/lang/String;
     * 1592: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1595: ldc           \n
     * 1597: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1600: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1603: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1606: pop
     * 1607: aload_0
     * 1608: getfield      ch/ntb/usb/usbView/UsbTreeModel.rootBus:Lch/ntb/usb/Usb_Bus;
     * 1611: astore        6
     * 1613: aload         6
     * 1615: ifnull        1783
     * 1618: aload         6
     * 1620: invokevirtual ch/ntb/usb/Usb_Bus.getDevices:()Lch/ntb/usb/Usb_Device;
     * 1623: astore        7
     * 1625: aload         7
     * 1627: ifnull        1773
     * 1630: aload         7
     * 1632: invokevirtual ch/ntb/usb/Usb_Device.getConfig:()[Lch/ntb/usb/Usb_Config_Descriptor;
     * 1635: astore        8
     * 1637: iconst_0
     * 1638: istore        9
     * 1640: iload         9
     * 1642: aload         8
     * 1644: arraylength
     * 1645: if_icmpge     1763
     * 1648: aload         8
     * 1650: aload         4
     * 1652: invokevirtual java/lang/Object.equals:(Ljava/lang/Object;)Z
     * 1655: ifeq          1757
     * 1658: aload         4
     * 1660: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getIConfiguration:()B
     * 1663: ifle          1757
     * 1666: aload         7
     * 1668: invokestatic  ch/ntb/usb/LibusbJava.usb_open:(Lch/ntb/usb/Usb_Device;)J
     * 1671: lstore        10
     * 1673: aload         5
     * 1675: ldc           \nString descriptors\n
     * 1677: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1680: pop
     * 1681: lload         10
     * 1683: lconst_0
     * 1684: lcmp
     * 1685: ifgt          1699
     * 1688: aload         5
     * 1690: ldc           \terror opening the device\n
     * 1692: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1695: pop
     * 1696: goto          1763
     * 1699: lload         10
     * 1701: aload         4
     * 1703: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getIConfiguration:()B
     * 1706: invokestatic  ch/ntb/usb/LibusbJava.usb_get_string_simple:(JI)Ljava/lang/String;
     * 1709: astore        12
     * 1711: aload         12
     * 1713: ifnonnull     1720
     * 1716: ldc           unable to fetch configuration string
     * 1718: astore        12
     * 1720: aload         5
     * 1722: new           java/lang/StringBuilder
     * 1725: dup
     * 1726: invokespecial java/lang/StringBuilder."<init>":()V
     * 1729: ldc           \tiConfiguration:
     * 1731: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1734: aload         12
     * 1736: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1739: ldc           \n
     * 1741: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1744: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1747: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1750: pop
     * 1751: lload         10
     * 1753: invokestatic  ch/ntb/usb/LibusbJava.usb_close:(J)I
     * 1756: pop
     * 1757: iinc          9, 1
     * 1760: goto          1640
     * 1763: aload         7
     * 1765: invokevirtual ch/ntb/usb/Usb_Device.getNext:()Lch/ntb/usb/Usb_Device;
     * 1768: astore        7
     * 1770: goto          1625
     * 1773: aload         6
     * 1775: invokevirtual ch/ntb/usb/Usb_Bus.getNext:()Lch/ntb/usb/Usb_Bus;
     * 1778: astore        6
     * 1780: goto          1613
     * 1783: aload_0
     * 1784: getfield      ch/ntb/usb/usbView/UsbTreeModel.textArea:Ljavax/swing/JTextArea;
     * 1787: aload         5
     * 1789: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 1792: invokevirtual javax/swing/JTextArea.setText:(Ljava/lang/String;)V
     * 1795: goto          3075
     * 1798: aload_3
     * 1799: instanceof    ch/ntb/usb/Usb_Interface
     * 1802: ifeq          1908
     * 1805: aload_3
     * 1806: checkcast     ch/ntb/usb/Usb_Interface
     * 1809: astore        4
     * 1811: new           java/lang/StringBuffer
     * 1814: dup
     * 1815: ldc           Usb_Interface\n
     * 1817: invokespecial java/lang/StringBuffer."<init>":(Ljava/lang/String;)V
     * 1820: astore        5
     * 1822: aload         5
     * 1824: new           java/lang/StringBuilder
     * 1827: dup
     * 1828: invokespecial java/lang/StringBuilder."<init>":()V
     * 1831: ldc           \tnum_altsetting: 0x
     * 1833: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1836: aload         4
     * 1838: invokevirtual ch/ntb/usb/Usb_Interface.getNumAltsetting:()I
     * 1841: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1844: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1847: ldc           \n
     * 1849: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1852: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1855: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1858: pop
     * 1859: aload         5
     * 1861: new           java/lang/StringBuilder
     * 1864: dup
     * 1865: invokespecial java/lang/StringBuilder."<init>":()V
     * 1868: ldc           \taltsetting:
     * 1870: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1873: aload         4
     * 1875: invokevirtual ch/ntb/usb/Usb_Interface.getAltsetting:()[Lch/ntb/usb/Usb_Interface_Descriptor;
     * 1878: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
     * 1881: ldc           \n
     * 1883: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1886: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1889: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1892: pop
     * 1893: aload_0
     * 1894: getfield      ch/ntb/usb/usbView/UsbTreeModel.textArea:Ljavax/swing/JTextArea;
     * 1897: aload         5
     * 1899: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 1902: invokevirtual javax/swing/JTextArea.setText:(Ljava/lang/String;)V
     * 1905: goto          3075
     * 1908: aload_3
     * 1909: instanceof    ch/ntb/usb/Usb_Interface_Descriptor
     * 1912: ifeq          2628
     * 1915: aload_3
     * 1916: checkcast     ch/ntb/usb/Usb_Interface_Descriptor
     * 1919: astore        4
     * 1921: new           java/lang/StringBuffer
     * 1924: dup
     * 1925: ldc           Usb_Interface_Descriptor\n
     * 1927: invokespecial java/lang/StringBuffer."<init>":(Ljava/lang/String;)V
     * 1930: astore        5
     * 1932: aload         5
     * 1934: new           java/lang/StringBuilder
     * 1937: dup
     * 1938: invokespecial java/lang/StringBuilder."<init>":()V
     * 1941: ldc           \tblenght: 0x
     * 1943: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1946: aload         4
     * 1948: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getBLength:()B
     * 1951: sipush        255
     * 1954: iand
     * 1955: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1958: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1961: ldc           \n
     * 1963: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1966: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 1969: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 1972: pop
     * 1973: aload         5
     * 1975: new           java/lang/StringBuilder
     * 1978: dup
     * 1979: invokespecial java/lang/StringBuilder."<init>":()V
     * 1982: ldc           \tbDescriptorType: 0x
     * 1984: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 1987: aload         4
     * 1989: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getBDescriptorType:()B
     * 1992: sipush        255
     * 1995: iand
     * 1996: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 1999: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2002: ldc           \n
     * 2004: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2007: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2010: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2013: pop
     * 2014: aload         5
     * 2016: new           java/lang/StringBuilder
     * 2019: dup
     * 2020: invokespecial java/lang/StringBuilder."<init>":()V
     * 2023: ldc           \tbInterfaceNumber: 0x
     * 2025: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2028: aload         4
     * 2030: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getBInterfaceNumber:()B
     * 2033: sipush        255
     * 2036: iand
     * 2037: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2040: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2043: ldc           \n
     * 2045: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2048: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2051: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2054: pop
     * 2055: aload         5
     * 2057: new           java/lang/StringBuilder
     * 2060: dup
     * 2061: invokespecial java/lang/StringBuilder."<init>":()V
     * 2064: ldc           \tbAlternateSetting: 0x
     * 2066: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2069: aload         4
     * 2071: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getBAlternateSetting:()B
     * 2074: sipush        255
     * 2077: iand
     * 2078: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2081: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2084: ldc           \n
     * 2086: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2089: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2092: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2095: pop
     * 2096: aload         5
     * 2098: new           java/lang/StringBuilder
     * 2101: dup
     * 2102: invokespecial java/lang/StringBuilder."<init>":()V
     * 2105: ldc           \tbNumEndpoints: 0x
     * 2107: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2110: aload         4
     * 2112: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getBNumEndpoints:()B
     * 2115: sipush        255
     * 2118: iand
     * 2119: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2122: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2125: ldc           \n
     * 2127: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2130: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2133: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2136: pop
     * 2137: aload         5
     * 2139: new           java/lang/StringBuilder
     * 2142: dup
     * 2143: invokespecial java/lang/StringBuilder."<init>":()V
     * 2146: ldc           \tbInterfaceClass: 0x
     * 2148: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2151: aload         4
     * 2153: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getBInterfaceClass:()B
     * 2156: sipush        255
     * 2159: iand
     * 2160: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2163: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2166: ldc           \n
     * 2168: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2171: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2174: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2177: pop
     * 2178: aload         5
     * 2180: new           java/lang/StringBuilder
     * 2183: dup
     * 2184: invokespecial java/lang/StringBuilder."<init>":()V
     * 2187: ldc           \tbInterfaceSubClass: 0x
     * 2189: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2192: aload         4
     * 2194: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getBInterfaceSubClass:()B
     * 2197: sipush        255
     * 2200: iand
     * 2201: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2204: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2207: ldc           \n
     * 2209: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2212: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2215: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2218: pop
     * 2219: aload         5
     * 2221: new           java/lang/StringBuilder
     * 2224: dup
     * 2225: invokespecial java/lang/StringBuilder."<init>":()V
     * 2228: ldc           \tbInterfaceProtocol: 0x
     * 2230: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2233: aload         4
     * 2235: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getBInterfaceProtocol:()B
     * 2238: sipush        255
     * 2241: iand
     * 2242: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2245: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2248: ldc           \n
     * 2250: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2253: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2256: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2259: pop
     * 2260: aload         5
     * 2262: new           java/lang/StringBuilder
     * 2265: dup
     * 2266: invokespecial java/lang/StringBuilder."<init>":()V
     * 2269: ldc           \tiInterface: 0x
     * 2271: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2274: aload         4
     * 2276: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getIInterface:()B
     * 2279: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2282: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2285: ldc           \n
     * 2287: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2290: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2293: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2296: pop
     * 2297: aload         5
     * 2299: new           java/lang/StringBuilder
     * 2302: dup
     * 2303: invokespecial java/lang/StringBuilder."<init>":()V
     * 2306: ldc           \textralen: 0x
     * 2308: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2311: aload         4
     * 2313: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getExtralen:()I
     * 2316: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2319: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2322: ldc           \n
     * 2324: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2327: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2330: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2333: pop
     * 2334: aload         5
     * 2336: new           java/lang/StringBuilder
     * 2339: dup
     * 2340: invokespecial java/lang/StringBuilder."<init>":()V
     * 2343: ldc           \textra:
     * 2345: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2348: aload_0
     * 2349: aload         4
     * 2351: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getExtra:()[B
     * 2354: invokespecial ch/ntb/usb/usbView/UsbTreeModel.extraDescriptorToString:([B)Ljava/lang/String;
     * 2357: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2360: ldc           \n
     * 2362: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2365: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2368: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2371: pop
     * 2372: aload_0
     * 2373: getfield      ch/ntb/usb/usbView/UsbTreeModel.rootBus:Lch/ntb/usb/Usb_Bus;
     * 2376: astore        6
     * 2378: aload         6
     * 2380: ifnull        2613
     * 2383: aload         6
     * 2385: invokevirtual ch/ntb/usb/Usb_Bus.getDevices:()Lch/ntb/usb/Usb_Device;
     * 2388: astore        7
     * 2390: aload         7
     * 2392: ifnull        2603
     * 2395: aload         7
     * 2397: invokevirtual ch/ntb/usb/Usb_Device.getConfig:()[Lch/ntb/usb/Usb_Config_Descriptor;
     * 2400: astore        8
     * 2402: iconst_0
     * 2403: istore        9
     * 2405: iload         9
     * 2407: aload         8
     * 2409: arraylength
     * 2410: if_icmpge     2593
     * 2413: aload         8
     * 2415: iload         9
     * 2417: aaload
     * 2418: invokevirtual ch/ntb/usb/Usb_Config_Descriptor.getInterface:()[Lch/ntb/usb/Usb_Interface;
     * 2421: astore        10
     * 2423: iconst_0
     * 2424: istore        11
     * 2426: iload         11
     * 2428: aload         10
     * 2430: arraylength
     * 2431: if_icmpge     2587
     * 2434: aload         10
     * 2436: iload         11
     * 2438: aaload
     * 2439: invokevirtual ch/ntb/usb/Usb_Interface.getAltsetting:()[Lch/ntb/usb/Usb_Interface_Descriptor;
     * 2442: astore        12
     * 2444: iconst_0
     * 2445: istore        13
     * 2447: iload         13
     * 2449: aload         10
     * 2451: arraylength
     * 2452: if_icmpge     2581
     * 2455: iload         9
     * 2457: aload         12
     * 2459: arraylength
     * 2460: if_icmpge     2575
     * 2463: aload         12
     * 2465: iload         9
     * 2467: aaload
     * 2468: aload         4
     * 2470: invokevirtual java/lang/Object.equals:(Ljava/lang/Object;)Z
     * 2473: ifeq          2575
     * 2476: aload         4
     * 2478: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getIInterface:()B
     * 2481: ifle          2575
     * 2484: aload         7
     * 2486: invokestatic  ch/ntb/usb/LibusbJava.usb_open:(Lch/ntb/usb/Usb_Device;)J
     * 2489: lstore        14
     * 2491: aload         5
     * 2493: ldc           \nString descriptors\n
     * 2495: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2498: pop
     * 2499: lload         14
     * 2501: lconst_0
     * 2502: lcmp
     * 2503: ifgt          2517
     * 2506: aload         5
     * 2508: ldc           \terror opening the device\n
     * 2510: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2513: pop
     * 2514: goto          2581
     * 2517: lload         14
     * 2519: aload         4
     * 2521: invokevirtual ch/ntb/usb/Usb_Interface_Descriptor.getIInterface:()B
     * 2524: invokestatic  ch/ntb/usb/LibusbJava.usb_get_string_simple:(JI)Ljava/lang/String;
     * 2527: astore        16
     * 2529: aload         16
     * 2531: ifnonnull     2538
     * 2534: ldc           unable to fetch interface string
     * 2536: astore        16
     * 2538: aload         5
     * 2540: new           java/lang/StringBuilder
     * 2543: dup
     * 2544: invokespecial java/lang/StringBuilder."<init>":()V
     * 2547: ldc           \tiInterface:
     * 2549: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2552: aload         16
     * 2554: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2557: ldc           \n
     * 2559: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2562: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2565: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2568: pop
     * 2569: lload         14
     * 2571: invokestatic  ch/ntb/usb/LibusbJava.usb_close:(J)I
     * 2574: pop
     * 2575: iinc          13, 1
     * 2578: goto          2447
     * 2581: iinc          11, 1
     * 2584: goto          2426
     * 2587: iinc          9, 1
     * 2590: goto          2405
     * 2593: aload         7
     * 2595: invokevirtual ch/ntb/usb/Usb_Device.getNext:()Lch/ntb/usb/Usb_Device;
     * 2598: astore        7
     * 2600: goto          2390
     * 2603: aload         6
     * 2605: invokevirtual ch/ntb/usb/Usb_Bus.getNext:()Lch/ntb/usb/Usb_Bus;
     * 2608: astore        6
     * 2610: goto          2378
     * 2613: aload_0
     * 2614: getfield      ch/ntb/usb/usbView/UsbTreeModel.textArea:Ljavax/swing/JTextArea;
     * 2617: aload         5
     * 2619: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 2622: invokevirtual javax/swing/JTextArea.setText:(Ljava/lang/String;)V
     * 2625: goto          3075
     * 2628: aload_3
     * 2629: instanceof    ch/ntb/usb/Usb_Endpoint_Descriptor
     * 2632: ifeq          3075
     * 2635: aload_3
     * 2636: checkcast     ch/ntb/usb/Usb_Endpoint_Descriptor
     * 2639: astore        4
     * 2641: new           java/lang/StringBuffer
     * 2644: dup
     * 2645: ldc           Usb_Endpoint_Descriptor\n
     * 2647: invokespecial java/lang/StringBuffer."<init>":(Ljava/lang/String;)V
     * 2650: astore        5
     * 2652: aload         5
     * 2654: new           java/lang/StringBuilder
     * 2657: dup
     * 2658: invokespecial java/lang/StringBuilder."<init>":()V
     * 2661: ldc           \tblenght: 0x
     * 2663: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2666: aload         4
     * 2668: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getBLength:()B
     * 2671: sipush        255
     * 2674: iand
     * 2675: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2678: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2681: ldc           \n
     * 2683: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2686: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2689: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2692: pop
     * 2693: aload         5
     * 2695: new           java/lang/StringBuilder
     * 2698: dup
     * 2699: invokespecial java/lang/StringBuilder."<init>":()V
     * 2702: ldc           \tbDescriptorType: 0x
     * 2704: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2707: aload         4
     * 2709: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getBDescriptorType:()B
     * 2712: sipush        255
     * 2715: iand
     * 2716: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2719: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2722: ldc           \n
     * 2724: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2727: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2730: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2733: pop
     * 2734: aload         5
     * 2736: new           java/lang/StringBuilder
     * 2739: dup
     * 2740: invokespecial java/lang/StringBuilder."<init>":()V
     * 2743: ldc           \tbEndpointAddress: 0x
     * 2745: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2748: aload         4
     * 2750: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getBEndpointAddress:()B
     * 2753: sipush        255
     * 2756: iand
     * 2757: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2760: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2763: ldc           \n
     * 2765: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2768: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2771: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2774: pop
     * 2775: aload         5
     * 2777: new           java/lang/StringBuilder
     * 2780: dup
     * 2781: invokespecial java/lang/StringBuilder."<init>":()V
     * 2784: ldc           \tbmAttributes: 0x
     * 2786: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2789: aload         4
     * 2791: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getBmAttributes:()B
     * 2794: sipush        255
     * 2797: iand
     * 2798: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2801: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2804: ldc           \n
     * 2806: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2809: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2812: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2815: pop
     * 2816: aload         5
     * 2818: new           java/lang/StringBuilder
     * 2821: dup
     * 2822: invokespecial java/lang/StringBuilder."<init>":()V
     * 2825: ldc           \twMaxPacketSize: 0x
     * 2827: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2830: aload         4
     * 2832: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getWMaxPacketSize:()S
     * 2835: ldc           65535
     * 2837: iand
     * 2838: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2841: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2844: ldc            (
     * 2846: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2849: aload         4
     * 2851: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getWMaxPacketSize:()S
     * 2854: invokevirtual java/lang/StringBuilder.append:(I)Ljava/lang/StringBuilder;
     * 2857: ldc           )\n
     * 2859: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2862: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2865: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2868: pop
     * 2869: aload         5
     * 2871: new           java/lang/StringBuilder
     * 2874: dup
     * 2875: invokespecial java/lang/StringBuilder."<init>":()V
     * 2878: ldc           \tbInterval: 0x
     * 2880: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2883: aload         4
     * 2885: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getBInterval:()B
     * 2888: sipush        255
     * 2891: iand
     * 2892: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2895: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2898: ldc           \n
     * 2900: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2903: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2906: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2909: pop
     * 2910: aload         5
     * 2912: new           java/lang/StringBuilder
     * 2915: dup
     * 2916: invokespecial java/lang/StringBuilder."<init>":()V
     * 2919: ldc           \tbRefresh: 0x
     * 2921: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2924: aload         4
     * 2926: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getBRefresh:()B
     * 2929: sipush        255
     * 2932: iand
     * 2933: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2936: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2939: ldc           \n
     * 2941: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2944: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2947: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2950: pop
     * 2951: aload         5
     * 2953: new           java/lang/StringBuilder
     * 2956: dup
     * 2957: invokespecial java/lang/StringBuilder."<init>":()V
     * 2960: ldc           \tbSynchAddress: 0x
     * 2962: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2965: aload         4
     * 2967: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getBSynchAddress:()B
     * 2970: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 2973: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2976: ldc           \n
     * 2978: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 2981: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 2984: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 2987: pop
     * 2988: aload         5
     * 2990: new           java/lang/StringBuilder
     * 2993: dup
     * 2994: invokespecial java/lang/StringBuilder."<init>":()V
     * 2997: ldc           \textralen: 0x
     * 2999: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 3002: aload         4
     * 3004: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getExtralen:()I
     * 3007: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 3010: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 3013: ldc           \n
     * 3015: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 3018: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 3021: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 3024: pop
     * 3025: aload         5
     * 3027: new           java/lang/StringBuilder
     * 3030: dup
     * 3031: invokespecial java/lang/StringBuilder."<init>":()V
     * 3034: ldc           \textra:
     * 3036: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 3039: aload_0
     * 3040: aload         4
     * 3042: invokevirtual ch/ntb/usb/Usb_Endpoint_Descriptor.getExtra:()[B
     * 3045: invokespecial ch/ntb/usb/usbView/UsbTreeModel.extraDescriptorToString:([B)Ljava/lang/String;
     * 3048: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 3051: ldc           \n
     * 3053: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 3056: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 3059: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 3062: pop
     * 3063: aload_0
     * 3064: getfield      ch/ntb/usb/usbView/UsbTreeModel.textArea:Ljavax/swing/JTextArea;
     * 3067: aload         5
     * 3069: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 3072: invokevirtual javax/swing/JTextArea.setText:(Ljava/lang/String;)V
     * 3075: return
     *  */
    // </editor-fold>
#endif
}

/*private*/ QString UsbTreeModel::extraDescriptorToString(QVector<quint8> extra) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: ifnull        60
     * 4: new           java/lang/StringBuffer
     * 7: dup
     * 8: invokespecial java/lang/StringBuffer."<init>":()V
     * 11: astore_2
     * 12: iconst_0
     * 13: istore_3
     * 14: iload_3
     * 15: aload_1
     * 16: arraylength
     * 17: if_icmpge     55
     * 20: aload_2
     * 21: ldc           0x
     * 23: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 26: pop
     * 27: aload_2
     * 28: aload_1
     * 29: iload_3
     * 30: baload
     * 31: sipush        255
     * 34: iand
     * 35: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 38: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 41: pop
     * 42: aload_2
     * 43: bipush        32
     * 45: invokevirtual java/lang/StringBuffer.append:(C)Ljava/lang/StringBuffer;
     * 48: pop
     * 49: iinc          3, 1
     * 52: goto          14
     * 55: aload_2
     * 56: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 59: areturn
     * 60: aconst_null
     * 61: areturn
     *  */
    // </editor-fold>
}
#endif
QVariant UsbTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole &&  orientation == Qt::Horizontal)
 {
  switch(section)
  {
   case 0:
   return tr("Usb Devices");
  case 1:
   return tr("Manufacturer");
  case 2:
   return tr("Product");
  }

 }
 return DefaultTreeModel1::headerData(section, orientation, role);
}

void UsbTreeModel::deviceChange(uchar bus, uchar address, bool bAdded)
{
 UsbTreeItem* item = itemHash->value(DevKey(bus, address).key());
 if(bAdded)
 {
  Q_ASSERT(item == NULL);
  DeviceFilter f = rootBus->getDevice(bus, address);
  UsbTreeItem* parentItem = itemHash->value(DevKey(f.parent.bus, f.parent.address).key());
  if(parentItem != NULL)
  {
   QString displayValue = QString("%1:%2*").arg(f.parent.bus,3,10,QLatin1Char('0')).arg(f.parent.address,3,10,QLatin1Char('0'));
   QModelIndexList list= match(index(0,0),Qt::DisplayRole, displayValue,-1, Qt::MatchWildcard|Qt::MatchRecursive);
   if(list.count() > 0 && list.at(0).isValid())
   {
    QModelIndex target = list.at(0);
    beginInsertRows(target, target.row()+1, target.row()+1);
    QList<QVariant> rootData; // Define the number of columns in the model.
    parentItem->appendChild(new UsbTreeItem(rootData, f, parentItem));
    endInsertRows();
   }
   return;
  }
 }
 else  if(!bAdded && item && (item->childCount() == 0) )
 {
  QString displayValue = QString("%1:%2*").arg(bus,3,10,QLatin1Char('0')).arg(address,3,10,QLatin1Char('0'));
  QModelIndexList list= match(index(0,0),Qt::DisplayRole, displayValue,-1, Qt::MatchWildcard|Qt::MatchRecursive);
  if(list.count() > 0 && list.at(0).isValid())
  {
   QModelIndex target = list.at(0);
   beginRemoveRows(target.parent(), target.row(), target.row());
   item->parent()->removeChild(item);
   delete item;
   endRemoveRows();
  return;
  }
 }
 else
  reload();
}

/*public*/ void UsbTreeModel::reload() // SLOT
{
 beginResetModel();
 quint8 bus = 1;
 quint8 port = 0;
 int added = 0;
 //int index = 0;
 rootItem->clear(); //removeAllChildren();
 itemHash->clear();
 QList<QVariant> rootData; // Define the number of columns in the model.
 rootData<<"Usb"<<"Manufacturer" << "Product";
 UsbTreeItem* node = new UsbTreeItem(rootData, DeviceFilter(),rootItem);
 node->setIcon(":resources/icons/icons8-usb-50.png");
 rootItem->appendChild(node);
 qDebug() << "rootItem child count " << rootItem->childCount();


 QList<DeviceFilter> allDevices = this->rootBus->devHash.values();
 foreach (DeviceFilter f, allDevices)
 {
  if(f.bDeviceClass == LIBUSB_CLASS_HUB && !f.bHasParent )
  {

   QList<QVariant> rootData; // Define the number of columns in the model.
   rootData<<"Usb"<<"Manufacturer" << "Product";
   UsbTreeItem* child = new UsbTreeItem(rootData, f, node);
   child->setIcon(":/resources/icons/icons8-hub-50.png");
   node->appendChild(child);
   added += (1+addChildren(child));
   qDebug() << f.bus << ":" <<f.address << "has " << child->childCount() << "Children";
  }
 }
 qDebug() << "added: " << added << "bus:" << bus;
 endResetModel();
 //DefaultTreeModel1::reload();

 qDebug() << "node child count " << node->childCount();
 qDebug() << "Row count " << rowCount(QModelIndex());

}

/**
  * add chldren which have node as parent
  *
  */
/*private*/ int UsbTreeModel::addChildren(UsbTreeItem* node)
{
 int added = 0;
 DeviceFilter f = node->userData.value<DeviceFilter>();

 foreach(DeviceFilter fc,this->rootBus->devHash.values())
 {
  if(fc.bus == f.bus && fc.address == f.address)
   continue;
  if(fc.bHasParent && ((fc.parent.bus == f.bus) && (fc.parent.address == f.address)))
  {
   QList<QVariant> data;
   data << QVariant("title");
   UsbTreeItem* child = new UsbTreeItem(data,fc, node);
   if(fc.bDeviceClass == LIBUSB_CLASS_HUB)
    child->setIcon(":/resources/icons/icons8-hub-50.png");
   node->appendChild(child);
   added += (1 + addChildren(child));
   continue;
  }
 }
 qDebug() << tr("child %1 : %2 has %3 children").arg(f.bus).arg(f.address).arg(node->childCount());
 return added;
}

///*private*/ int UsbTreeModel::columnCount(const QModelIndex &parent) const
//{
// return 3;
//}

