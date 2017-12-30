#include "linuxeventdevice.h"
#include "rumbler.h"
#include <QVector>

LinuxEventDevice::LinuxEventDevice()
{

}
// /*final*/ class LinuxEventDevice implements LinuxDevice {

/*public*/ LinuxEventDevice::LinuxEventDevice(QString filename, QObject* parent) throw (IOException) : LinuxDevice(parent)
{
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: aload_0
     * 5: new           java/util/HashMap
     * 8: dup
     * 9: invokespecial java/util/HashMap."<init>":()V
     * 12: putfield      net/java/games/input/LinuxEventDevice.component_map:Ljava/util/Map;
     * 15: aload_0
     * 16: bipush        64
     * 18: newarray       byte
     * 20: putfield      net/java/games/input/LinuxEventDevice.key_states:[B
     * 23: iconst_1
     * 24: istore        4
     * 26: aload_1
     * 27: iconst_1
     * 28: invokestatic  net/java/games/input/LinuxEventDevice.nOpen:(Ljava/lang/String;Z)J
     * 31: lstore_2
     * 32: goto          46
     * 35: astore        5
     * 37: aload_1
     * 38: iconst_0
     * 39: invokestatic  net/java/games/input/LinuxEventDevice.nOpen:(Ljava/lang/String;Z)J
     * 42: lstore_2
     * 43: iconst_0
     * 44: istore        4
     * 46: aload_0
     * 47: lload_2
     * 48: putfield      net/java/games/input/LinuxEventDevice.fd:J
     * 51: aload_0
     * 52: aload_0
     * 53: invokespecial net/java/games/input/LinuxEventDevice.getDeviceName:()Ljava/lang/String;
     * 56: putfield      net/java/games/input/LinuxEventDevice.name:Ljava/lang/String;
     * 59: aload_0
     * 60: aload_0
     * 61: invokespecial net/java/games/input/LinuxEventDevice.getDeviceInputID:()Lnet/java/games/input/LinuxInputID;
     * 64: putfield      net/java/games/input/LinuxEventDevice.input_id:Lnet/java/games/input/LinuxInputID;
     * 67: aload_0
     * 68: aload_0
     * 69: invokespecial net/java/games/input/LinuxEventDevice.getDeviceComponents:()Ljava/util/List;
     * 72: putfield      net/java/games/input/LinuxEventDevice.components:Ljava/util/List;
     * 75: iload         4
     * 77: ifeq          91
     * 80: aload_0
     * 81: aload_0
     * 82: invokespecial net/java/games/input/LinuxEventDevice.enumerateRumblers:()[Lnet/java/games/input/Rumbler;
     * 85: putfield      net/java/games/input/LinuxEventDevice.rumblers:[Lnet/java/games/input/Rumbler;
     * 88: goto          99
     * 91: aload_0
     * 92: iconst_0
     * 93: anewarray     net/java/games/input/Rumbler
     * 96: putfield      net/java/games/input/LinuxEventDevice.rumblers:[Lnet/java/games/input/Rumbler;
     * 99: aload_0
     * 100: aload_0
     * 101: invokespecial net/java/games/input/LinuxEventDevice.guessType:()Lnet/java/games/input/Controller$Type;
     * 104: putfield      net/java/games/input/LinuxEventDevice.type:Lnet/java/games/input/Controller$Type;
     * 107: goto          119
     * 110: astore        5
     * 112: aload_0
     * 113: invokevirtual net/java/games/input/LinuxEventDevice.close:()V
     * 116: aload         5
     * 118: athrow
     * 119: return
     * Exception table:
     * from    to  target type
     * 26    32    35   Class java/io/IOException
     * 51   107   110   Class java/io/IOException
     *  */
    // </editor-fold>
 rumblers = new QVector<Rumbler*>();
}
#if 0
/*private*/ static /*final*/ /*native*/ long nOpen(QString string, bool bln) throw (IOException);
#endif
/*public*/ /*final*/ Usb::Controller::Type LinuxEventDevice::getType() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.type:Lnet/java/games/input/Controller$Type;
     * 4: areturn
     *  */
    // </editor-fold>
 return type;
}
#if 0
/*private*/ static /*final*/ int countComponents(List list, Class type, boolean bln) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_0
     * 1: istore_3
     * 2: iconst_0
     * 3: istore        4
     * 5: iload         4
     * 7: aload_0
     * 8: invokeinterface java/util/List.size:()I
     * 13: if_icmpge     59
     * 16: aload_0
     * 17: iload         4
     * 19: invokeinterface java/util/List.get:(I)Ljava/lang/Object;
     * 24: checkcast     net/java/games/input/LinuxEventComponent
     * 27: astore        5
     * 29: aload_1
     * 30: aload         5
     * 32: invokevirtual net/java/games/input/LinuxEventComponent.getIdentifier:()Lnet/java/games/input/Component$Identifier;
     * 35: invokevirtual java/lang/Class.isInstance:(Ljava/lang/Object;)Z
     * 38: ifeq          53
     * 41: iload_2
     * 42: aload         5
     * 44: invokevirtual net/java/games/input/LinuxEventComponent.isRelative:()Z
     * 47: if_icmpne     53
     * 50: iinc          3, 1
     * 53: iinc          4, 1
     * 56: goto          5
     * 59: iload_3
     * 60: ireturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ Controller.Type guessType() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.guessTypeFromUsages:()Lnet/java/games/input/Controller$Type;
     * 4: astore_1
     * 5: aload_1
     * 6: getstatic     net/java/games/input/Controller$Type.UNKNOWN:Lnet/java/games/input/Controller$Type;
     * 9: if_acmpne     17
     * 12: aload_0
     * 13: invokespecial net/java/games/input/LinuxEventDevice.guessTypeFromComponents:()Lnet/java/games/input/Controller$Type;
     * 16: areturn
     * 17: aload_1
     * 18: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ Controller.Type guessTypeFromUsages() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.getDeviceUsageBits:()[B
     * 4: astore_1
     * 5: aload_1
     * 6: iconst_0
     * 7: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 10: ifeq          17
     * 13: getstatic     net/java/games/input/Controller$Type.MOUSE:Lnet/java/games/input/Controller$Type;
     * 16: areturn
     * 17: aload_1
     * 18: iconst_3
     * 19: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 22: ifeq          29
     * 25: getstatic     net/java/games/input/Controller$Type.KEYBOARD:Lnet/java/games/input/Controller$Type;
     * 28: areturn
     * 29: aload_1
     * 30: iconst_2
     * 31: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 34: ifeq          41
     * 37: getstatic     net/java/games/input/Controller$Type.GAMEPAD:Lnet/java/games/input/Controller$Type;
     * 40: areturn
     * 41: aload_1
     * 42: iconst_1
     * 43: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 46: ifeq          53
     * 49: getstatic     net/java/games/input/Controller$Type.STICK:Lnet/java/games/input/Controller$Type;
     * 52: areturn
     * 53: getstatic     net/java/games/input/Controller$Type.UNKNOWN:Lnet/java/games/input/Controller$Type;
     * 56: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ Controller.Type guessTypeFromComponents() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokevirtual net/java/games/input/LinuxEventDevice.getComponents:()Ljava/util/List;
     * 4: astore_1
     * 5: aload_1
     * 6: invokeinterface java/util/List.size:()I
     * 11: ifne          18
     * 14: getstatic     net/java/games/input/Controller$Type.UNKNOWN:Lnet/java/games/input/Controller$Type;
     * 17: areturn
     * 18: aload_1
     * 19: getstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Axis:Ljava/lang/Class;
     * 22: ifnonnull     37
     * 25: ldc           net.java.games.input.Component$Identifier$Axis
     * 27: invokestatic  net/java/games/input/LinuxEventDevice.class$:(Ljava/lang/String;)Ljava/lang/Class;
     * 30: dup
     * 31: putstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Axis:Ljava/lang/Class;
     * 34: goto          40
     * 37: getstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Axis:Ljava/lang/Class;
     * 40: iconst_1
     * 41: invokestatic  net/java/games/input/LinuxEventDevice.countComponents:(Ljava/util/List;Ljava/lang/Class;Z)I
     * 44: istore_2
     * 45: aload_1
     * 46: getstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Axis:Ljava/lang/Class;
     * 49: ifnonnull     64
     * 52: ldc           net.java.games.input.Component$Identifier$Axis
     * 54: invokestatic  net/java/games/input/LinuxEventDevice.class$:(Ljava/lang/String;)Ljava/lang/Class;
     * 57: dup
     * 58: putstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Axis:Ljava/lang/Class;
     * 61: goto          67
     * 64: getstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Axis:Ljava/lang/Class;
     * 67: iconst_0
     * 68: invokestatic  net/java/games/input/LinuxEventDevice.countComponents:(Ljava/util/List;Ljava/lang/Class;Z)I
     * 71: istore_3
     * 72: aload_1
     * 73: getstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Key:Ljava/lang/Class;
     * 76: ifnonnull     91
     * 79: ldc           net.java.games.input.Component$Identifier$Key
     * 81: invokestatic  net/java/games/input/LinuxEventDevice.class$:(Ljava/lang/String;)Ljava/lang/Class;
     * 84: dup
     * 85: putstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Key:Ljava/lang/Class;
     * 88: goto          94
     * 91: getstatic     net/java/games/input/LinuxEventDevice.class$net$java$games$input$Component$Identifier$Key:Ljava/lang/Class;
     * 94: iconst_0
     * 95: invokestatic  net/java/games/input/LinuxEventDevice.countComponents:(Ljava/util/List;Ljava/lang/Class;Z)I
     * 98: istore        4
     * 100: iconst_0
     * 101: istore        5
     * 103: iconst_0
     * 104: istore        6
     * 106: iconst_0
     * 107: istore        7
     * 109: iconst_0
     * 110: istore        8
     * 112: aload_0
     * 113: getfield      net/java/games/input/LinuxEventDevice.name:Ljava/lang/String;
     * 116: invokevirtual java/lang/String.toLowerCase:()Ljava/lang/String;
     * 119: ldc           mouse
     * 121: invokevirtual java/lang/String.indexOf:(Ljava/lang/String;)I
     * 124: iconst_m1
     * 125: if_icmpeq     131
     * 128: iinc          5, 1
     * 131: aload_0
     * 132: getfield      net/java/games/input/LinuxEventDevice.name:Ljava/lang/String;
     * 135: invokevirtual java/lang/String.toLowerCase:()Ljava/lang/String;
     * 138: ldc           keyboard
     * 140: invokevirtual java/lang/String.indexOf:(Ljava/lang/String;)I
     * 143: iconst_m1
     * 144: if_icmpeq     150
     * 147: iinc          6, 1
     * 150: aload_0
     * 151: getfield      net/java/games/input/LinuxEventDevice.name:Ljava/lang/String;
     * 154: invokevirtual java/lang/String.toLowerCase:()Ljava/lang/String;
     * 157: ldc           joystick
     * 159: invokevirtual java/lang/String.indexOf:(Ljava/lang/String;)I
     * 162: iconst_m1
     * 163: if_icmpeq     169
     * 166: iinc          7, 1
     * 169: aload_0
     * 170: getfield      net/java/games/input/LinuxEventDevice.name:Ljava/lang/String;
     * 173: invokevirtual java/lang/String.toLowerCase:()Ljava/lang/String;
     * 176: ldc           gamepad
     * 178: invokevirtual java/lang/String.indexOf:(Ljava/lang/String;)I
     * 181: iconst_m1
     * 182: if_icmpeq     188
     * 185: iinc          8, 1
     * 188: iconst_0
     * 189: istore        9
     * 191: iconst_0
     * 192: istore        10
     * 194: iconst_0
     * 195: istore        11
     * 197: iconst_0
     * 198: istore        12
     * 200: iconst_0
     * 201: istore        13
     * 203: iload         13
     * 205: aload_1
     * 206: invokeinterface java/util/List.size:()I
     * 211: if_icmpge     298
     * 214: aload_1
     * 215: iload         13
     * 217: invokeinterface java/util/List.get:(I)Ljava/lang/Object;
     * 222: checkcast     net/java/games/input/LinuxEventComponent
     * 225: astore        14
     * 227: aload         14
     * 229: invokevirtual net/java/games/input/LinuxEventComponent.getButtonTrait:()Lnet/java/games/input/Controller$Type;
     * 232: getstatic     net/java/games/input/Controller$Type.MOUSE:Lnet/java/games/input/Controller$Type;
     * 235: if_acmpne     244
     * 238: iinc          10, 1
     * 241: goto          292
     * 244: aload         14
     * 246: invokevirtual net/java/games/input/LinuxEventComponent.getButtonTrait:()Lnet/java/games/input/Controller$Type;
     * 249: getstatic     net/java/games/input/Controller$Type.KEYBOARD:Lnet/java/games/input/Controller$Type;
     * 252: if_acmpne     261
     * 255: iinc          9, 1
     * 258: goto          292
     * 261: aload         14
     * 263: invokevirtual net/java/games/input/LinuxEventComponent.getButtonTrait:()Lnet/java/games/input/Controller$Type;
     * 266: getstatic     net/java/games/input/Controller$Type.GAMEPAD:Lnet/java/games/input/Controller$Type;
     * 269: if_acmpne     278
     * 272: iinc          12, 1
     * 275: goto          292
     * 278: aload         14
     * 280: invokevirtual net/java/games/input/LinuxEventComponent.getButtonTrait:()Lnet/java/games/input/Controller$Type;
     * 283: getstatic     net/java/games/input/Controller$Type.STICK:Lnet/java/games/input/Controller$Type;
     * 286: if_acmpne     292
     * 289: iinc          11, 1
     * 292: iinc          13, 1
     * 295: goto          203
     * 298: iload         10
     * 300: iload         9
     * 302: if_icmplt     325
     * 305: iload         10
     * 307: iload         11
     * 309: if_icmplt     325
     * 312: iload         10
     * 314: iload         12
     * 316: if_icmplt     325
     * 319: iinc          5, 1
     * 322: goto          403
     * 325: iload         9
     * 327: iload         10
     * 329: if_icmplt     352
     * 332: iload         9
     * 334: iload         11
     * 336: if_icmplt     352
     * 339: iload         9
     * 341: iload         12
     * 343: if_icmplt     352
     * 346: iinc          6, 1
     * 349: goto          403
     * 352: iload         11
     * 354: iload         9
     * 356: if_icmplt     379
     * 359: iload         11
     * 361: iload         10
     * 363: if_icmplt     379
     * 366: iload         11
     * 368: iload         12
     * 370: if_icmplt     379
     * 373: iinc          7, 1
     * 376: goto          403
     * 379: iload         12
     * 381: iload         9
     * 383: if_icmplt     403
     * 386: iload         12
     * 388: iload         10
     * 390: if_icmplt     403
     * 393: iload         12
     * 395: iload         11
     * 397: if_icmplt     403
     * 400: iinc          8, 1
     * 403: iload_2
     * 404: iconst_2
     * 405: if_icmplt     411
     * 408: iinc          5, 1
     * 411: iload_3
     * 412: iconst_2
     * 413: if_icmplt     422
     * 416: iinc          7, 1
     * 419: iinc          8, 1
     * 422: iload         5
     * 424: iload         6
     * 426: if_icmplt     447
     * 429: iload         5
     * 431: iload         7
     * 433: if_icmplt     447
     * 436: iload         5
     * 438: iload         8
     * 440: if_icmplt     447
     * 443: getstatic     net/java/games/input/Controller$Type.MOUSE:Lnet/java/games/input/Controller$Type;
     * 446: areturn
     * 447: iload         6
     * 449: iload         5
     * 451: if_icmplt     472
     * 454: iload         6
     * 456: iload         7
     * 458: if_icmplt     472
     * 461: iload         6
     * 463: iload         8
     * 465: if_icmplt     472
     * 468: getstatic     net/java/games/input/Controller$Type.KEYBOARD:Lnet/java/games/input/Controller$Type;
     * 471: areturn
     * 472: iload         7
     * 474: iload         5
     * 476: if_icmplt     497
     * 479: iload         7
     * 481: iload         6
     * 483: if_icmplt     497
     * 486: iload         7
     * 488: iload         8
     * 490: if_icmplt     497
     * 493: getstatic     net/java/games/input/Controller$Type.STICK:Lnet/java/games/input/Controller$Type;
     * 496: areturn
     * 497: iload         8
     * 499: iload         5
     * 501: if_icmplt     522
     * 504: iload         8
     * 506: iload         6
     * 508: if_icmplt     522
     * 511: iload         8
     * 513: iload         7
     * 515: if_icmplt     522
     * 518: getstatic     net/java/games/input/Controller$Type.GAMEPAD:Lnet/java/games/input/Controller$Type;
     * 521: areturn
     * 522: aconst_null
     * 523: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ Rumbler[] enumerateRumblers() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: new           java/util/ArrayList
     * 3: dup
     * 4: invokespecial java/util/ArrayList."<init>":()V
     * 7: astore_1
     * 8: aload_0
     * 9: invokevirtual net/java/games/input/LinuxEventDevice.getNumEffects:()I
     * 12: istore_2
     * 13: iload_2
     * 14: ifgt          34
     * 17: aload_1
     * 18: iconst_0
     * 19: anewarray     net/java/games/input/Rumbler
     * 22: invokeinterface java/util/List.toArray:([Ljava/lang/Object;)[Ljava/lang/Object;
     * 27: checkcast     "[Lnet/java/games/input/Rumbler;"
     * 30: checkcast     "[Lnet/java/games/input/Rumbler;"
     * 33: areturn
     * 34: aload_0
     * 35: invokespecial net/java/games/input/LinuxEventDevice.getForceFeedbackBits:()[B
     * 38: astore_3
     * 39: aload_3
     * 40: bipush        80
     * 42: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 45: ifeq          73
     * 48: iload_2
     * 49: aload_1
     * 50: invokeinterface java/util/List.size:()I
     * 55: if_icmple     73
     * 58: aload_1
     * 59: new           net/java/games/input/LinuxRumbleFF
     * 62: dup
     * 63: aload_0
     * 64: invokespecial net/java/games/input/LinuxRumbleFF."<init>":(Lnet/java/games/input/LinuxEventDevice;)V
     * 67: invokeinterface java/util/List.add:(Ljava/lang/Object;)Z
     * 72: pop
     * 73: goto          102
     * 76: astore_2
     * 77: new           java/lang/StringBuffer
     * 80: dup
     * 81: invokespecial java/lang/StringBuffer."<init>":()V
     * 84: ldc           Failed to enumerate rumblers:
     * 86: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 89: aload_2
     * 90: invokevirtual java/io/IOException.getMessage:()Ljava/lang/String;
     * 93: invokevirtual java/lang/StringBuffer.append:(Ljava/lang/String;)Ljava/lang/StringBuffer;
     * 96: invokevirtual java/lang/StringBuffer.toString:()Ljava/lang/String;
     * 99: invokestatic  net/java/games/input/LinuxEnvironmentPlugin.logln:(Ljava/lang/String;)V
     * 102: aload_1
     * 103: iconst_0
     * 104: anewarray     net/java/games/input/Rumbler
     * 107: invokeinterface java/util/List.toArray:([Ljava/lang/Object;)[Ljava/lang/Object;
     * 112: checkcast     "[Lnet/java/games/input/Rumbler;"
     * 115: checkcast     "[Lnet/java/games/input/Rumbler;"
     * 118: areturn
     * Exception table:
     * from    to  target type
     * 8    33    76   Class java/io/IOException
     * 34    73    76   Class java/io/IOException
     *  */
    // </editor-fold>
}
#endif
/*public*/ /*final*/ QVector<Rumbler*>* LinuxEventDevice::getRumblers() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.rumblers:[Lnet/java/games/input/Rumbler;
     * 4: areturn
     *  */
    // </editor-fold>
 return rumblers;
}

/*public*/ /*final*/ /*synchronized*/ int LinuxEventDevice::uploadRumbleEffect(int i, int i1, int i2, int i3, int i4, int i5, int i6, int i7) throw (IOException) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.checkClosed:()V
     * 4: aload_0
     * 5: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 8: iload_1
     * 9: iload_3
     * 10: iload_2
     * 11: iload         4
     * 13: iload         5
     * 15: iload         6
     * 17: iload         7
     * 19: iload         8
     * 21: invokestatic  net/java/games/input/LinuxEventDevice.nUploadRumbleEffect:(JIIIIIIII)I
     * 24: ireturn
     *  */
    // </editor-fold>
}
#if 0
/*private*/ static /*final*/ /*native*/ int nUploadRumbleEffect(long l, int i, int i1, int i2, int i3, int i4, int i5, int i6, int i7) throw IOException;
#endif
/*public*/ /*final*/ /*synchronized*/ int LinuxEventDevice::uploadConstantEffect(int i, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10) throw (IOException) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.checkClosed:()V
     * 4: aload_0
     * 5: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 8: iload_1
     * 9: iload_3
     * 10: iload_2
     * 11: iload         4
     * 13: iload         5
     * 15: iload         6
     * 17: iload         7
     * 19: iload         8
     * 21: iload         9
     * 23: iload         10
     * 25: iload         11
     * 27: invokestatic  net/java/games/input/LinuxEventDevice.nUploadConstantEffect:(JIIIIIIIIIII)I
     * 30: ireturn
     *  */
    // </editor-fold>
}
#if 0
/*private*/ static /*final*/ native int nUploadConstantEffect(long l, int i, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10) throws IOException;

/*final*/ void eraseEffect(int i) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 4: iload_1
     * 5: invokestatic  net/java/games/input/LinuxEventDevice.nEraseEffect:(JI)V
     * 8: return
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native void nEraseEffect(long l, int i) throws IOException;

/*public*/ /*final*/ synchronized void writeEvent(int i, int i1, int i2) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.checkClosed:()V
     * 4: aload_0
     * 5: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 8: iload_1
     * 9: iload_2
     * 10: iload_3
     * 11: invokestatic  net/java/games/input/LinuxEventDevice.nWriteEvent:(JIII)V
     * 14: return
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native void nWriteEvent(long l, int i, int i1, int i2) throws IOException;

/*public*/ /*final*/ void registerComponent(LinuxAxisDescriptor lad, LinuxComponent lc) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.component_map:Ljava/util/Map;
     * 4: aload_1
     * 5: aload_2
     * 6: invokeinterface java/util/Map.put:(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
     * 11: pop
     * 12: return
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ LinuxComponent mapDescriptor(LinuxAxisDescriptor lad) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.component_map:Ljava/util/Map;
     * 4: aload_1
     * 5: invokeinterface java/util/Map.get:(Ljava/lang/Object;)Ljava/lang/Object;
     * 10: checkcast     net/java/games/input/LinuxComponent
     * 13: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ Controller.PortType getPortType() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.input_id:Lnet/java/games/input/LinuxInputID;
     * 4: invokevirtual net/java/games/input/LinuxInputID.getPortType:()Lnet/java/games/input/Controller$PortType;
     * 7: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ LinuxInputID getInputID() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.input_id:Lnet/java/games/input/LinuxInputID;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ LinuxInputID getDeviceInputID() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 4: invokestatic  net/java/games/input/LinuxEventDevice.nGetInputID:(J)Lnet/java/games/input/LinuxInputID;
     * 7: areturn
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native LinuxInputID nGetInputID(long l) throws IOException;

/*public*/ /*final*/ int getNumEffects() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 4: invokestatic  net/java/games/input/LinuxEventDevice.nGetNumEffects:(J)I
     * 7: ireturn
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native int nGetNumEffects(long l) throws IOException;

/*private*/ /*final*/ int getVersion() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 4: invokestatic  net/java/games/input/LinuxEventDevice.nGetVersion:(J)I
     * 7: ireturn
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native int nGetVersion(long l) throws IOException;

/*public*/ /*final*/ synchronized boolean getNextEvent(LinuxEvent le) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.checkClosed:()V
     * 4: aload_0
     * 5: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 8: aload_1
     * 9: invokestatic  net/java/games/input/LinuxEventDevice.nGetNextEvent:(JLnet/java/games/input/LinuxEvent;)Z
     * 12: ireturn
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native boolean nGetNextEvent(long l, LinuxEvent le) throws IOException;

/*public*/ /*final*/ synchronized void getAbsInfo(int i, LinuxAbsInfo lai) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.checkClosed:()V
     * 4: aload_0
     * 5: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 8: iload_1
     * 9: aload_2
     * 10: invokestatic  net/java/games/input/LinuxEventDevice.nGetAbsInfo:(JILnet/java/games/input/LinuxAbsInfo;)V
     * 13: return
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native void nGetAbsInfo(long l, int i, LinuxAbsInfo lai) throws IOException;

/*private*/ /*final*/ void addKeys(List list) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.getKeysBits:()[B
     * 4: astore_2
     * 5: iconst_0
     * 6: istore_3
     * 7: iload_3
     * 8: aload_2
     * 9: arraylength
     * 10: bipush        8
     * 12: imul
     * 13: if_icmpge     56
     * 16: aload_2
     * 17: iload_3
     * 18: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 21: ifeq          50
     * 24: iload_3
     * 25: invokestatic  net/java/games/input/LinuxNativeTypesMap.getButtonID:(I)Lnet/java/games/input/Component$Identifier;
     * 28: astore        4
     * 30: aload_1
     * 31: new           net/java/games/input/LinuxEventComponent
     * 34: dup
     * 35: aload_0
     * 36: aload         4
     * 38: iconst_0
     * 39: iconst_1
     * 40: iload_3
     * 41: invokespecial net/java/games/input/LinuxEventComponent."<init>":(Lnet/java/games/input/LinuxEventDevice;Lnet/java/games/input/Component$Identifier;ZII)V
     * 44: invokeinterface java/util/List.add:(Ljava/lang/Object;)Z
     * 49: pop
     * 50: iinc          3, 1
     * 53: goto          7
     * 56: return
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ void addAbsoluteAxes(List list) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.getAbsoluteAxesBits:()[B
     * 4: astore_2
     * 5: iconst_0
     * 6: istore_3
     * 7: iload_3
     * 8: aload_2
     * 9: arraylength
     * 10: bipush        8
     * 12: imul
     * 13: if_icmpge     56
     * 16: aload_2
     * 17: iload_3
     * 18: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 21: ifeq          50
     * 24: iload_3
     * 25: invokestatic  net/java/games/input/LinuxNativeTypesMap.getAbsAxisID:(I)Lnet/java/games/input/Component$Identifier;
     * 28: astore        4
     * 30: aload_1
     * 31: new           net/java/games/input/LinuxEventComponent
     * 34: dup
     * 35: aload_0
     * 36: aload         4
     * 38: iconst_0
     * 39: iconst_3
     * 40: iload_3
     * 41: invokespecial net/java/games/input/LinuxEventComponent."<init>":(Lnet/java/games/input/LinuxEventDevice;Lnet/java/games/input/Component$Identifier;ZII)V
     * 44: invokeinterface java/util/List.add:(Ljava/lang/Object;)Z
     * 49: pop
     * 50: iinc          3, 1
     * 53: goto          7
     * 56: return
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ void addRelativeAxes(List list) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial net/java/games/input/LinuxEventDevice.getRelativeAxesBits:()[B
     * 4: astore_2
     * 5: iconst_0
     * 6: istore_3
     * 7: iload_3
     * 8: aload_2
     * 9: arraylength
     * 10: bipush        8
     * 12: imul
     * 13: if_icmpge     56
     * 16: aload_2
     * 17: iload_3
     * 18: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 21: ifeq          50
     * 24: iload_3
     * 25: invokestatic  net/java/games/input/LinuxNativeTypesMap.getRelAxisID:(I)Lnet/java/games/input/Component$Identifier;
     * 28: astore        4
     * 30: aload_1
     * 31: new           net/java/games/input/LinuxEventComponent
     * 34: dup
     * 35: aload_0
     * 36: aload         4
     * 38: iconst_1
     * 39: iconst_2
     * 40: iload_3
     * 41: invokespecial net/java/games/input/LinuxEventComponent."<init>":(Lnet/java/games/input/LinuxEventDevice;Lnet/java/games/input/Component$Identifier;ZII)V
     * 44: invokeinterface java/util/List.add:(Ljava/lang/Object;)Z
     * 49: pop
     * 50: iinc          3, 1
     * 53: goto          7
     * 56: return
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ List getComponents() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.components:Ljava/util/List;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ List getDeviceComponents() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: new           java/util/ArrayList
     * 3: dup
     * 4: invokespecial java/util/ArrayList."<init>":()V
     * 7: astore_1
     * 8: aload_0
     * 9: invokespecial net/java/games/input/LinuxEventDevice.getEventTypeBits:()[B
     * 12: astore_2
     * 13: aload_2
     * 14: iconst_1
     * 15: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 18: ifeq          26
     * 21: aload_0
     * 22: aload_1
     * 23: invokespecial net/java/games/input/LinuxEventDevice.addKeys:(Ljava/util/List;)V
     * 26: aload_2
     * 27: iconst_3
     * 28: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 31: ifeq          39
     * 34: aload_0
     * 35: aload_1
     * 36: invokespecial net/java/games/input/LinuxEventDevice.addAbsoluteAxes:(Ljava/util/List;)V
     * 39: aload_2
     * 40: iconst_2
     * 41: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 44: ifeq          52
     * 47: aload_0
     * 48: aload_1
     * 49: invokespecial net/java/games/input/LinuxEventDevice.addRelativeAxes:(Ljava/util/List;)V
     * 52: aload_1
     * 53: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ byte[] getForceFeedbackBits() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: bipush        16
     * 2: newarray       byte
     * 4: astore_1
     * 5: aload_0
     * 6: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 9: bipush        21
     * 11: aload_1
     * 12: invokestatic  net/java/games/input/LinuxEventDevice.nGetBits:(JI[B)V
     * 15: aload_1
     * 16: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ byte[] getKeysBits() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: bipush        64
     * 2: newarray       byte
     * 4: astore_1
     * 5: aload_0
     * 6: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 9: iconst_1
     * 10: aload_1
     * 11: invokestatic  net/java/games/input/LinuxEventDevice.nGetBits:(JI[B)V
     * 14: aload_1
     * 15: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ byte[] getAbsoluteAxesBits() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: bipush        8
     * 2: newarray       byte
     * 4: astore_1
     * 5: aload_0
     * 6: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 9: iconst_3
     * 10: aload_1
     * 11: invokestatic  net/java/games/input/LinuxEventDevice.nGetBits:(JI[B)V
     * 14: aload_1
     * 15: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ byte[] getRelativeAxesBits() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_2
     * 1: newarray       byte
     * 3: astore_1
     * 4: aload_0
     * 5: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 8: iconst_2
     * 9: aload_1
     * 10: invokestatic  net/java/games/input/LinuxEventDevice.nGetBits:(JI[B)V
     * 13: aload_1
     * 14: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ byte[] getEventTypeBits() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_4
     * 1: newarray       byte
     * 3: astore_1
     * 4: aload_0
     * 5: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 8: iconst_0
     * 9: aload_1
     * 10: invokestatic  net/java/games/input/LinuxEventDevice.nGetBits:(JI[B)V
     * 13: aload_1
     * 14: areturn
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native void nGetBits(long l, int i, byte[] bytes) throws IOException;

/*private*/ /*final*/ byte[] getDeviceUsageBits() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_2
     * 1: newarray       byte
     * 3: astore_1
     * 4: aload_0
     * 5: invokespecial net/java/games/input/LinuxEventDevice.getVersion:()I
     * 8: ldc           65537
     * 10: if_icmplt     21
     * 13: aload_0
     * 14: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 17: aload_1
     * 18: invokestatic  net/java/games/input/LinuxEventDevice.nGetDeviceUsageBits:(J[B)V
     * 21: aload_1
     * 22: areturn
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native void nGetDeviceUsageBits(long l, byte[] bytes) throws IOException;

/*public*/ /*final*/ synchronized void pollKeyStates() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 4: aload_0
     * 5: getfield      net/java/games/input/LinuxEventDevice.key_states:[B
     * 8: invokestatic  net/java/games/input/LinuxEventDevice.nGetKeyStates:(J[B)V
     * 11: return
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native void nGetKeyStates(long l, byte[] bytes) throws IOException;

/*public*/ /*final*/ boolean isKeySet(int i) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.key_states:[B
     * 4: iload_1
     * 5: invokestatic  net/java/games/input/LinuxEventDevice.isBitSet:([BI)Z
     * 8: ireturn
     *  */
    // </editor-fold>
}

/*public*/ static /*final*/ boolean isBitSet(byte[] bytes, int i) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: iload_1
     * 2: bipush        8
     * 4: idiv
     * 5: baload
     * 6: iconst_1
     * 7: iload_1
     * 8: bipush        8
     * 10: irem
     * 11: ishl
     * 12: iand
     * 13: ifeq          20
     * 16: iconst_1
     * 17: goto          21
     * 20: iconst_0
     * 21: ireturn
     *  */
    // </editor-fold>
}

/*public*/ /*final*/ QString getName() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.name:Ljava/lang/String;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*private*/ /*final*/ QString getDeviceName() throw (IOException) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.fd:J
     * 4: invokestatic  net/java/games/input/LinuxEventDevice.nGetName:(J)Ljava/lang/String;
     * 7: areturn
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native String nGetName(long l) throws IOException;

/*public*/ /*final*/ synchronized void close() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.closed:Z
     * 4: ifeq          8
     * 7: return
     * 8: aload_0
     * 9: iconst_1
     * 10: putfield      net/java/games/input/LinuxEventDevice.closed:Z
     * 13: new           net/java/games/input/LinuxEventDevice$1
     * 16: dup
     * 17: aload_0
     * 18: invokespecial net/java/games/input/LinuxEventDevice$1."<init>":(Lnet/java/games/input/LinuxEventDevice;)V
     * 21: invokestatic  net/java/games/input/LinuxEnvironmentPlugin.execute:(Lnet/java/games/input/LinuxDeviceTask;)Ljava/lang/Object;
     * 24: pop
     * 25: return
     *  */
    // </editor-fold>
}

/*private*/ static /*final*/ native void nClose(long l) throw (IOException);

/*private*/ /*final*/ void checkClosed() throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      net/java/games/input/LinuxEventDevice.closed:Z
     * 4: ifeq          17
     * 7: new           java/io/IOException
     * 10: dup
     * 11: ldc           Device is closed
     * 13: invokespecial java/io/IOException."<init>":(Ljava/lang/String;)V
     * 16: athrow
     * 17: return
     *  */
    // </editor-fold>
}

/*protected*/ void /*final*/ize() throw IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokevirtual net/java/games/input/LinuxEventDevice.close:()V
     * 4: return
     *  */
    // </editor-fold>
}
#endif
