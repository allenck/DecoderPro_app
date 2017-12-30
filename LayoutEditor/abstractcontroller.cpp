#include "abstractcontroller.h"
namespace Usb {


AbstractController::AbstractController() : Usb::Controller()
{

}
// /*public*/ abstract class AbstractController implements Controller {

    /*static*/ /*final*/ int AbstractController::EVENT_QUEUE_DEPTH = 32;
/*private*/ /*static*/ /*final*/ Event* AbstractController::event = NULL;

/*protected*/ AbstractController::AbstractController(QString name, QVector<UsbComponent*>* components, QVector<Usb::Controller*>* children, QVector<Rumbler*>* rumblers) : Usb::Controller()
{
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: aload_0
     * 5: new           java/util/HashMap
     * 8: dup
     * 9: invokespecial java/util/HashMap."<init>":()V
     * 12: putfield      net/java/games/input/AbstractController.id_to_components:Ljava/util/Map;
     * 15: aload_0
     * 16: new           net/java/games/input/EventQueue
     * 19: dup
     * 20: bipush        32
     * 22: invokespecial net/java/games/input/EventQueue."<init>":(I)V
     * 25: putfield      net/java/games/input/AbstractController.event_queue:Lnet/java/games/input/EventQueue;
     * 28: aload_0
     * 29: aload_1
     * 30: putfield      net/java/games/input/AbstractController.name:Ljava/lang/String;
     * 33: aload_0
     * 34: aload_2
     * 35: putfield      net/java/games/input/AbstractController.components:[Lnet/java/games/input/UsbComponent;
     * 38: aload_0
     * 39: aload_3
     * 40: putfield      net/java/games/input/AbstractController.children:[Lnet/java/games/input/Controller;
     * 43: aload_0
     * 44: aload         4
     * 46: putfield      net/java/games/input/AbstractController.rumblers:[Lnet/java/games/input/Rumbler;
     * 49: aload_2
     * 50: arraylength
     * 51: iconst_1
     * 52: isub
     * 53: istore        5
     * 55: iload         5
     * 57: iflt          89
     * 60: aload_0
     * 61: getfield      net/java/games/input/AbstractController.id_to_components:Ljava/util/Map;
     * 64: aload_2
     * 65: iload         5
     * 67: aaload
     * 68: invokeinterface net/java/games/input/UsbComponent.getIdentifier:()Lnet/java/games/input/UsbComponent$Identifier;
     * 73: aload_2
     * 74: iload         5
     * 76: aaload
     * 77: invokeinterface java/util/Map.put:(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
     * 82: pop
     * 83: iinc          5, -1
     * 86: goto          55
     * 89: return
     *  */
    // </editor-fold>
this->name = name;
this-> components = components;
this->children = children;
this->rumblers = rumblers;
}

/*public*/ /*final*/ QVector<Usb::Controller*>* AbstractController::getControllers() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/AbstractController.children:[Lnet/java/games/input/Controller;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ QVector<UsbComponent*>* AbstractController::getComponents() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/AbstractController.components:[Lnet/java/games/input/UsbComponent;
     * 4: areturn
     *  */
    // </editor-fold>
 return components;
}

/*public*/ /*final*/ UsbComponent* AbstractController::getComponent(UsbComponent::Identifier id) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/AbstractController.id_to_components:Ljava/util/Map;
     * 4: aload_1
     * 5: invokeinterface java/util/Map.get:(Ljava/lang/Object;)Ljava/lang/Object;
     * 10: checkcast     net/java/games/input/UsbComponent
     * 13: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ QVector<Rumbler*>* AbstractController::getRumblers() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/AbstractController.rumblers:[Lnet/java/games/input/Rumbler;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ Usb::Controller::PortType AbstractController::getPortType() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: getstatic     net/java/games/input/Controller$PortType.UNKNOWN:Lnet/java/games/input/Controller$PortType;
     * 3: areturn
     *  */
    // </editor-fold>
 return portType;
}

/*public*/ int AbstractController::getPortNumber() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_0
     * 1: ireturn
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ QString AbstractController::getName() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/AbstractController.name:Ljava/lang/String;
     * 4: areturn
     *  */
    // </editor-fold>
 return this->name;
}

/*public*/ QString AbstractController::toString() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/AbstractController.name:Ljava/lang/String;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ Usb::Controller::Type AbstractController::getType() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: getstatic     net/java/games/input/Controller$Type.UNKNOWN:Lnet/java/games/input/Controller$Type;
     * 3: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ void AbstractController::setEventQueueSize(int size) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: iload_1
     * 2: invokevirtual net/java/games/input/AbstractController.setDeviceEventQueueSize:(I)V
     * 5: aload_0
     * 6: new           net/java/games/input/EventQueue
     * 9: dup
     * 10: iload_1
     * 11: invokespecial net/java/games/input/EventQueue."<init>":(I)V
     * 14: putfield      net/java/games/input/AbstractController.event_queue:Lnet/java/games/input/EventQueue;
     * 17: goto          52
     * 20: astore_2
     * 21: new           java/lang/StringBuffer
     * 24: dup
     * 25: invokespecial java/lang/StringBuffer."<init>":()V
     * 28: ldc           Failed to create new event queue of size
     * 30: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 33: iload_1
     * 34: invokevirtual java/lang/StringBuffer.append:(I)Ljava/lang/StringBuffer;
     * 37: ldc           :
     * 39: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 42: aload_2
     * 43: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/Object;)Ljava/lang/StringBuffer;
     * 46: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 49: invokestatic  net/java/games/input/ControllerEnvironment.logln:(Ljava/lang/String;)V
     * 52: return
     * Exception table:
     * from    to  target type
     * 0    17    20   Class java/io/IOException
     *  */
    // </editor-fold>
}

/*protected*/ void AbstractController::setDeviceEventQueueSize(int size) throw (IOException)
{
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: return
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ EventQueue* AbstractController::getEventQueue() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/AbstractController.event_queue:Lnet/java/games/input/EventQueue;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*protected*/ /*abstract*/ bool AbstractController::getNextDeviceEvent(Event* event) throw (IOException) {return false;}

/*protected*/ void AbstractController::pollDevice() throw (IOException) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: return
     *  */
    // </editor-fold>
}

/*public*/ /*synchronized*/ bool AbstractController::poll() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokevirtual net/java/games/input/AbstractController.getUsbComponents:()[Lnet/java/games/input/UsbComponent;
     * 4: astore_1
     * 5: aload_0
     * 6: invokevirtual net/java/games/input/AbstractController.pollDevice:()V
     * 9: iconst_0
     * 10: istore_2
     * 11: iload_2
     * 12: aload_1
     * 13: arraylength
     * 14: if_icmpge     49
     * 17: aload_1
     * 18: iload_2
     * 19: aaload
     * 20: checkcast     net/java/games/input/AbstractUsbComponent
     * 23: astore_3
     * 24: aload_3
     * 25: invokevirtual net/java/games/input/AbstractUsbComponent.isRelative:()Z
     * 28: ifeq          39
     * 31: aload_3
     * 32: fconst_0
     * 33: invokevirtual net/java/games/input/AbstractUsbComponent.setPollData:(F)V
     * 36: goto          43
     * 39: aload_3
     * 40: invokevirtual net/java/games/input/AbstractUsbComponent.resetHasPolled:()V
     * 43: iinc          2, 1
     * 46: goto          11
     * 49: aload_0
     * 50: getstatic     net/java/games/input/AbstractController.event:Lnet/java/games/input/Event;
     * 53: invokevirtual net/java/games/input/AbstractController.getNextDeviceEvent:(Lnet/java/games/input/Event;)Z
     * 56: ifeq          145
     * 59: getstatic     net/java/games/input/AbstractController.event:Lnet/java/games/input/Event;
     * 62: invokevirtual net/java/games/input/Event.getUsbComponent:()Lnet/java/games/input/UsbComponent;
     * 65: checkcast     net/java/games/input/AbstractUsbComponent
     * 68: astore_2
     * 69: getstatic     net/java/games/input/AbstractController.event:Lnet/java/games/input/Event;
     * 72: invokevirtual net/java/games/input/Event.getValue:()F
     * 75: fstore_3
     * 76: aload_2
     * 77: invokevirtual net/java/games/input/AbstractUsbComponent.isRelative:()Z
     * 80: ifeq          105
     * 83: fload_3
     * 84: fconst_0
     * 85: fcmpl
     * 86: ifne          92
     * 89: goto          49
     * 92: aload_2
     * 93: aload_2
     * 94: invokevirtual net/java/games/input/AbstractUsbComponent.getPollData:()F
     * 97: fload_3
     * 98: fadd
     * 99: invokevirtual net/java/games/input/AbstractUsbComponent.setPollData:(F)V
     * 102: goto          122
     * 105: fload_3
     * 106: aload_2
     * 107: invokevirtual net/java/games/input/AbstractUsbComponent.getEventValue:()F
     * 110: fcmpl
     * 111: ifne          117
     * 114: goto          49
     * 117: aload_2
     * 118: fload_3
     * 119: invokevirtual net/java/games/input/AbstractUsbComponent.setEventValue:(F)V
     * 122: aload_0
     * 123: getfield      net/java/games/input/AbstractController.event_queue:Lnet/java/games/input/EventQueue;
     * 126: invokevirtual net/java/games/input/EventQueue.isFull:()Z
     * 129: ifne          142
     * 132: aload_0
     * 133: getfield      net/java/games/input/AbstractController.event_queue:Lnet/java/games/input/EventQueue;
     * 136: getstatic     net/java/games/input/AbstractController.event:Lnet/java/games/input/Event;
     * 139: invokevirtual net/java/games/input/EventQueue.add:(Lnet/java/games/input/Event;)V
     * 142: goto          49
     * 145: iconst_1
     * 146: ireturn
     * 147: astore_2
     * 148: new           java/lang/StringBuffer
     * 151: dup
     * 152: invokespecial java/lang/StringBuffer."<init>":()V
     * 155: ldc           Failed to poll device:
     * 157: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 160: aload_2
     * 161: invokevirtual java/io/IOException.getMessage:()Ljava/lang/String;
     * 164: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 167: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 170: invokestatic  net/java/games/input/ControllerEnvironment.logln:(Ljava/lang/String;)V
     * 173: iconst_0
     * 174: ireturn
     * Exception table:
     * from    to  target type
     * 5   146   147   Class java/io/IOException
     *  */
    // </editor-fold>
}
}
