#include "loglevel.h"
LogLevel::LogLevel()
{

}
// /*public*/ class Level extends Priority implements Serializable {

/*public*/ /*static*/ /*final*/ int LogLevel::TRACE_INT = 5000;
///*static*/ /*final*/ long LogLevel::serialVersionUID = 3491141966387921974L;

/*protected*/ LogLevel::LogLevel(int level, QString levelStr, int syslogEquivalent) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: iload_1
     * 2: aload_2
     * 3: iload_3
     * 4: invokespecial org/apache/log4j/Priority."<init>":(ILjava/lang/String;I)V
     * 7: return
     *  */
    // </editor-fold>
}

/*public*/ /*static*/ LogLevel LogLevel::toLevel(QString sArg) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getstatic     org/apache/log4j/Level.DEBUG:Lorg/apache/log4j/Level;
     * 4: invokestatic  org/apache/log4j/Level.toLevel:(Ljava/lang/String;Lorg/apache/log4j/Level;)Lorg/apache/log4j/Level;
     * 7: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*static*/ LogLevel LogLevel::toLevel(int val) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iload_0
     * 1: getstatic     org/apache/log4j/Level.DEBUG:Lorg/apache/log4j/Level;
     * 4: invokestatic  org/apache/log4j/Level.toLevel:(ILorg/apache/log4j/Level;)Lorg/apache/log4j/Level;
     * 7: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*static*/ LogLevel LogLevel::toLevel(int val, LogLevel defaultLevel) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iload_0
     * 1: lookupswitch  { // 8
     * -2147483648: 76
     * 5000: 104
     * 10000: 80
     * 20000: 84
     * 30000: 88
     * 40000: 92
     * 50000: 96
     * 2147483647: 100
     * default: 108
     * }
     * 76: getstatic     org/apache/log4j/Level.ALL:Lorg/apache/log4j/Level;
     * 79: areturn
     * 80: getstatic     org/apache/log4j/Level.DEBUG:Lorg/apache/log4j/Level;
     * 83: areturn
     * 84: getstatic     org/apache/log4j/Level.INFO:Lorg/apache/log4j/Level;
     * 87: areturn
     * 88: getstatic     org/apache/log4j/Level.WARN:Lorg/apache/log4j/Level;
     * 91: areturn
     * 92: getstatic     org/apache/log4j/Level.ERROR:Lorg/apache/log4j/Level;
     * 95: areturn
     * 96: getstatic     org/apache/log4j/Level.FATAL:Lorg/apache/log4j/Level;
     * 99: areturn
     * 100: getstatic     org/apache/log4j/Level.OFF:Lorg/apache/log4j/Level;
     * 103: areturn
     * 104: getstatic     org/apache/log4j/Level.TRACE:Lorg/apache/log4j/Level;
     * 107: areturn
     * 108: aload_1
     * 109: areturn
     *  */
    // </editor-fold>
}

/*public*/ /*static*/ LogLevel LogLevel::toLevel(QString sArg, LogLevel defaultLevel) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: ifnonnull     6
     * 4: aload_1
     * 5: areturn
     * 6: aload_0
     * 7: invokevirtual java/lang/String.toUpperCase:()Ljava/lang/String;
     * 10: astore_2
     * 11: aload_2
     * 12: ldc           ALL
     * 14: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 17: ifeq          24
     * 20: getstatic     org/apache/log4j/Level.ALL:Lorg/apache/log4j/Level;
     * 23: areturn
     * 24: aload_2
     * 25: ldc           DEBUG
     * 27: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 30: ifeq          37
     * 33: getstatic     org/apache/log4j/Level.DEBUG:Lorg/apache/log4j/Level;
     * 36: areturn
     * 37: aload_2
     * 38: ldc           INFO
     * 40: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 43: ifeq          50
     * 46: getstatic     org/apache/log4j/Level.INFO:Lorg/apache/log4j/Level;
     * 49: areturn
     * 50: aload_2
     * 51: ldc           WARN
     * 53: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 56: ifeq          63
     * 59: getstatic     org/apache/log4j/Level.WARN:Lorg/apache/log4j/Level;
     * 62: areturn
     * 63: aload_2
     * 64: ldc           ERROR
     * 66: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 69: ifeq          76
     * 72: getstatic     org/apache/log4j/Level.ERROR:Lorg/apache/log4j/Level;
     * 75: areturn
     * 76: aload_2
     * 77: ldc           FATAL
     * 79: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 82: ifeq          89
     * 85: getstatic     org/apache/log4j/Level.FATAL:Lorg/apache/log4j/Level;
     * 88: areturn
     * 89: aload_2
     * 90: ldc           OFF
     * 92: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 95: ifeq          102
     * 98: getstatic     org/apache/log4j/Level.OFF:Lorg/apache/log4j/Level;
     * 101: areturn
     * 102: aload_2
     * 103: ldc           TRACE
     * 105: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 108: ifeq          115
     * 111: getstatic     org/apache/log4j/Level.TRACE:Lorg/apache/log4j/Level;
     * 114: areturn
     * 115: aload_2
     * 116: ldc           İNFO
     * 118: invokevirtual java/lang/String.equals:(Ljava/lang/Object;)Z
     * 121: ifeq          128
     * 124: getstatic     org/apache/log4j/Level.INFO:Lorg/apache/log4j/Level;
     * 127: areturn
     * 128: aload_1
     * 129: areturn
     *  */
    // </editor-fold>
}
#if 0
/*private*/ void readObject(ObjectInputStream s) throws IOException, ClassNotFoundException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: invokevirtual java/io/ObjectInputStream.defaultReadObject:()V
     * 4: aload_0
     * 5: aload_1
     * 6: invokevirtual java/io/ObjectInputStream.readInt:()I
     * 9: putfield      org/apache/log4j/Level.level:I
     * 12: aload_0
     * 13: aload_1
     * 14: invokevirtual java/io/ObjectInputStream.readInt:()I
     * 17: putfield      org/apache/log4j/Level.syslogEquivalent:I
     * 20: aload_0
     * 21: aload_1
     * 22: invokevirtual java/io/ObjectInputStream.readUTF:()Ljava/lang/String;
     * 25: putfield      org/apache/log4j/Level.levelStr:Ljava/lang/String;
     * 28: aload_0
     * 29: getfield      org/apache/log4j/Level.levelStr:Ljava/lang/String;
     * 32: ifnonnull     41
     * 35: aload_0
     * 36: ldc
     * 38: putfield      org/apache/log4j/Level.levelStr:Ljava/lang/String;
     * 41: return
     *  */
    // </editor-fold>
}

/*private*/ void writeObject(ObjectOutputStream s) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: invokevirtual java/io/ObjectOutputStream.defaultWriteObject:()V
     * 4: aload_1
     * 5: aload_0
     * 6: getfield      org/apache/log4j/Level.level:I
     * 9: invokevirtual java/io/ObjectOutputStream.writeInt:(I)V
     * 12: aload_1
     * 13: aload_0
     * 14: getfield      org/apache/log4j/Level.syslogEquivalent:I
     * 17: invokevirtual java/io/ObjectOutputStream.writeInt:(I)V
     * 20: aload_1
     * 21: aload_0
     * 22: getfield      org/apache/log4j/Level.levelStr:Ljava/lang/String;
     * 25: invokevirtual java/io/ObjectOutputStream.writeUTF:(Ljava/lang/String;)V
     * 28: return
     *  */
    // </editor-fold>
}

/*private*/ QObject* readResolve() throw ObjectStreamException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokevirtual java/lang/Object.getClass:()Ljava/lang/Class;
     * 4: getstatic     org/apache/log4j/Level.class$org$apache$log4j$Level:Ljava/lang/Class;
     * 7: ifnonnull     22
     * 10: ldc           org.apache.log4j.Level
     * 12: invokestatic  org/apache/log4j/Level.class$:(Ljava/lang/String;)Ljava/lang/Class;
     * 15: dup
     * 16: putstatic     org/apache/log4j/Level.class$org$apache$log4j$Level:Ljava/lang/Class;
     * 19: goto          25
     * 22: getstatic     org/apache/log4j/Level.class$org$apache$log4j$Level:Ljava/lang/Class;
     * 25: if_acmpne     36
     * 28: aload_0
     * 29: getfield      org/apache/log4j/Level.level:I
     * 32: invokestatic  org/apache/log4j/Level.toLevel:(I)Lorg/apache/log4j/Level;
     * 35: areturn
     * 36: aload_0
     * 37: areturn
     *  */
    // </editor-fold>
}
#endif
