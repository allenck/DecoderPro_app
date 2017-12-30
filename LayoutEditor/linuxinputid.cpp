#include "linuxinputid.h"

LinuxInputID::LinuxInputID()
{

}
// /*final*/ class LinuxInputID {


/*public*/ LinuxInputID::LinuxInputID(int bustype, int vendor, int product, int version) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: aload_0
     * 5: iload_1
     * 6: putfield      net/java/games/input/LinuxInputID.bustype:I
     * 9: aload_0
     * 10: iload_2
     * 11: putfield      net/java/games/input/LinuxInputID.vendor:I
     * 14: aload_0
     * 15: iload_3
     * 16: putfield      net/java/games/input/LinuxInputID.product:I
     * 19: aload_0
     * 20: iload         4
     * 22: putfield      net/java/games/input/LinuxInputID.version:I
     * 25: return
     *  */
    // </editor-fold>
 this->bustype = bustype;
 this->vendor = vendor;
 this->product = product;
 this->version = version;
}

/*public*/ /*final*/ Usb::Controller::PortType LinuxInputID::getPortType() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxInputID.bustype:I
     * 4: invokestatic  net/java/games/input/LinuxNativeTypesMap.getPortType:(I)Lnet/java/games/input/Controller$PortType;
     * 7: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ QString LinuxInputID::toString() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: new           java/lang/StringBuffer
     * 3: dup
     * 4: invokespecial java/lang/StringBuffer."<init>":()V
     * 7: ldc           LinuxInputID: bustype = 0x
     * 9: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 12: aload_0
     * 13: getfield      net/java/games/input/LinuxInputID.bustype:I
     * 16: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 19: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 22: ldc            | vendor = 0x
     * 24: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 27: aload_0
     * 28: getfield      net/java/games/input/LinuxInputID.vendor:I
     * 31: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 34: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 37: ldc            | product = 0x
     * 39: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 42: aload_0
     * 43: getfield      net/java/games/input/LinuxInputID.product:I
     * 46: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 49: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 52: ldc            | version = 0x
     * 54: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 57: aload_0
     * 58: getfield      net/java/games/input/LinuxInputID.version:I
     * 61: invokestatic  java/lang/Integer.toHexString:(I)Ljava/lang/String;
     * 64: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 67: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 70: areturn
     *  */
    // </editor-fold>
 QString str;

 return str;
}
