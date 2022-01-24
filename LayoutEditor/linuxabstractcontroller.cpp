#include "linuxabstractcontroller.h"

namespace Usb
{
LinuxAbstractController::LinuxAbstractController()
{

}
///*final*/ class LinuxAbstractController extends AbstractController {


    /*protected*/ LinuxAbstractController::LinuxAbstractController(LinuxEventDevice* device, QVector<UsbComponent*>* components, QVector<Usb::Controller*>* children, QVector<Rumbler*>* rumblers, Usb::Controller::Type type) /*throw (IOException)*/ : Usb::AbstractController("", components, children, rumblers)
{
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: invokevirtual net/java/games/input/LinuxEventDevice.getName:()Ljava/lang/String;
         * 5: aload_2
         * 6: aload_3
         * 7: aload         4
         * 9: invokespecial net/java/games/input/AbstractController."<init>":(Ljava/lang/String;[Lnet/java/games/input/Component;[Lnet/java/games/input/Controller;[Lnet/java/games/input/Rumbler;)V
         * 12: aload_0
         * 13: aload_1
         * 14: putfield      net/java/games/input/LinuxAbstractController.device:Lnet/java/games/input/LinuxEventDevice;
         * 17: aload_0
         * 18: aload_1
         * 19: invokevirtual net/java/games/input/LinuxEventDevice.getPortType:()Lnet/java/games/input/Controller$PortType;
         * 22: putfield      net/java/games/input/LinuxAbstractController.port:Lnet/java/games/input/Controller$PortType;
         * 25: aload_0
         * 26: aload         5
         * 28: putfield      net/java/games/input/LinuxAbstractController.type:Lnet/java/games/input/Controller$Type;
         * 31: return
         *  */
        // </editor-fold>
     //type = Controller::Type::UNKNOWN;
     this->type = type;


    }

    /*public*/ /*final*/ Usb::Controller::PortType LinuxAbstractController::getPortType() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      net/java/games/input/LinuxAbstractController.port:Lnet/java/games/input/Controller$PortType;
         * 4: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*final*/ void LinuxAbstractController::pollDevice() /*throw (IOException)*/ {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      net/java/games/input/LinuxAbstractController.device:Lnet/java/games/input/LinuxEventDevice;
         * 4: invokevirtual net/java/games/input/LinuxEventDevice.pollKeyStates:()V
         * 7: return
         *  */
        // </editor-fold>
    }

    /*protected*/ /*final*/ bool LinuxAbstractController::getNextDeviceEvent(Event* event) /*throw (IOException)*/ {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_1
         * 1: aload_0
         * 2: getfield      net/java/games/input/LinuxAbstractController.device:Lnet/java/games/input/LinuxEventDevice;
         * 5: invokestatic  net/java/games/input/LinuxControllers.getNextDeviceEvent:(Lnet/java/games/input/Event;Lnet/java/games/input/LinuxEventDevice;)Z
         * 8: ireturn
         *  */
        // </editor-fold>
    }

    /*public*/ Usb::Controller::Type LinuxAbstractController::getType() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      net/java/games/input/LinuxAbstractController.type:Lnet/java/games/input/Controller$Type;
         * 4: areturn
         *  */
        // </editor-fold>
     return type;
    }
}
