#include "keyboard.h"

namespace Usb
{
Keyboard::Keyboard()
{

}
///*public*/ abstract class Keyboard extends AbstractController {

    /*protected*/ Keyboard::Keyboard(QString name, QVector<UsbComponent*>* keys, QVector<Usb::Controller*>* children, QVector<Rumbler*>* rumblers) : Usb::AbstractController(name, keys, children, rumblers)
{
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: aload_2
         * 3: aload_3
         * 4: aload         4
         * 6: invokespecial net/java/games/input/AbstractController."<init>":(Ljava/lang/String;[Lnet/java/games/input/Component;[Lnet/java/games/input/Controller;[Lnet/java/games/input/Rumbler;)V
         * 9: return
         *  */
        // </editor-fold>
    }

    /*public*/ Usb::Controller::Type Keyboard::getType() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: getstatic     net/java/games/input/Controller$Type.KEYBOARD:Lnet/java/games/input/Controller$Type;
         * 3: areturn
         *  */
        // </editor-fold>
 return _type;
    }

    /*public*/ /*final*/ bool Keyboard::isKeyDown(UsbComponent::Identifier::Key key_id) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: invokevirtual net/java/games/input/Keyboard.getComponent:(Lnet/java/games/input/Component$Identifier;)Lnet/java/games/input/Component;
         * 5: astore_2
         * 6: aload_2
         * 7: ifnonnull     12
         * 10: iconst_0
         * 11: ireturn
         * 12: aload_2
         * 13: invokeinterface net/java/games/input/Component.getPollData:()F
         * 18: fconst_0
         * 19: fcmpl
         * 20: ifeq          27
         * 23: iconst_1
         * 24: goto          28
         * 27: iconst_0
         * 28: ireturn
         *  */
        // </editor-fold>
    }
}
