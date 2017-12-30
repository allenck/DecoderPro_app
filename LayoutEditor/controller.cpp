#include "controller.h"
namespace Usb
{
Controller::Controller(QObject *parent) : QObject(parent)
{

}
// /*public*/ interface Controller {

// /*public*/ static /*final*/ class PortType {

Controller::PortType::PortType() {}
    /*protected*/ Controller::PortType::PortType(QString name) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial java/lang/Object."<init>":()V
         * 4: aload_0
         * 5: aload_1
         * 6: putfield      net/java/games/input/Controller$PortType.name:Ljava/lang/String;
         * 9: return
         *  */
        // </editor-fold>
    }

    /*public*/ QString Controller::PortType::toString() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      net/java/games/input/Controller$PortType.name:Ljava/lang/String;
         * 4: areturn
         *  */
        // </editor-fold>
    }
//};

///*public*/ static class Type {

//    private /*final*/ String name;
 Controller::Type::Type() {}
    /*protected*/ Controller::Type::Type(QString name) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial java/lang/Object."<init>":()V
         * 4: aload_0
         * 5: aload_1
         * 6: putfield      net/java/games/input/Controller$Type.name:Ljava/lang/String;
         * 9: return
         *  */
        // </editor-fold>
     this->name = name;
    }

    /*public*/ QString Controller::Type::toString() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      net/java/games/input/Controller$Type.name:Ljava/lang/String;
         * 4: areturn
         *  */
        // </editor-fold>
    }
//};

///*public*/ QVector<Controller*>* Controller::getControllers() {return NULL;}

///*public*/ Controller::Type* Controller::getType()  {return NULL;}

///*public*/ QVector<UsbComponent*>* Controller::getComponents() {return NULL;}

///*public*/ UsbComponent* Controller::getComponent(UsbComponent::Identifier idntfr) {return NULL;}
#if 0
/*public*/ Rumbler[] getRumblers();

/*public*/ bool poll();

/*public*/ void setEventQueueSize(int i);

/*public*/ EventQueue getEventQueue();
#endif
/*public*/ Usb::Controller::PortType Usb::Controller::getPortType() {}

/*public*/ int Usb::Controller::getPortNumber() {return 0;}

/*public*/ QString Usb::Controller::getName() {return "";}

//};
}
