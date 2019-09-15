#include "priority.h"

//Priority::Priority()
//{

//}
///*public*/ class Priority {

    /*public*/ /*static*/ /*final*/ int Priority::OFF_INT = 2147483647;
    /*public*/ /*static*/ /*final*/ int Priority::FATAL_INT = 50000;
    /*public*/ /*static*/ /*final*/ int Priority::ERROR_INT = 40000;
    /*public*/ /*static*/ /*final*/ int Priority::WARN_INT = 30000;
    /*public*/ /*static*/ /*final*/ int Priority::INFO_INT = 20000;
    /*public*/ /*static*/ /*final*/ int Priority::DEBUG_INT = 10000;
    /*public*/ /*static*/ /*final*/ int Priority::ALL_INT = -2147483648;

    /*protected*/ Priority::Priority() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial java/lang/Object."<init>":()V
         * 4: aload_0
         * 5: sipush        10000
         * 8: putfield      org/apache/log4j/Priority.level:I
         * 11: aload_0
         * 12: ldc           DEBUG
         * 14: putfield      org/apache/log4j/Priority.levelStr:Ljava/lang/String;
         * 17: aload_0
         * 18: bipush        7
         * 20: putfield      org/apache/log4j/Priority.syslogEquivalent:I
         * 23: return
         *  */
        // </editor-fold>
    }

    /*protected*/ Priority::Priority(int level, QString levelStr, int syslogEquivalent) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial java/lang/Object."<init>":()V
         * 4: aload_0
         * 5: iload_1
         * 6: putfield      org/apache/log4j/Priority.level:I
         * 9: aload_0
         * 10: aload_2
         * 11: putfield      org/apache/log4j/Priority.levelStr:Ljava/lang/String;
         * 14: aload_0
         * 15: iload_3
         * 16: putfield      org/apache/log4j/Priority.syslogEquivalent:I
         * 19: return
         *  */
        // </editor-fold>
    }

    /*public*/ bool Priority::equals(QObject* o) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_1
         * 1: instanceof    org/apache/log4j/Priority
         * 4: ifeq          29
         * 7: aload_1
         * 8: checkcast     org/apache/log4j/Priority
         * 11: astore_2
         * 12: aload_0
         * 13: getfield      org/apache/log4j/Priority.level:I
         * 16: aload_2
         * 17: getfield      org/apache/log4j/Priority.level:I
         * 20: if_icmpne     27
         * 23: iconst_1
         * 24: goto          28
         * 27: iconst_0
         * 28: ireturn
         * 29: iconst_0
         * 30: ireturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*final*/ int Priority::getSyslogEquivalent() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/apache/log4j/Priority.syslogEquivalent:I
         * 4: ireturn
         *  */
        // </editor-fold>
    }

    /*public*/ bool Priority::isGreaterOrEqual(Priority* r) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/apache/log4j/Priority.level:I
         * 4: aload_1
         * 5: getfield      org/apache/log4j/Priority.level:I
         * 8: if_icmplt     15
         * 11: iconst_1
         * 12: goto          16
         * 15: iconst_0
         * 16: ireturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ QVector<Priority*> Priority::getAllPossiblePriorities() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: iconst_5
         * 1: anewarray     org/apache/log4j/Priority
         * 4: dup
         * 5: iconst_0
         * 6: getstatic     org/apache/log4j/Priority.FATAL:Lorg/apache/log4j/Priority;
         * 9: aastore
         * 10: dup
         * 11: iconst_1
         * 12: getstatic     org/apache/log4j/Priority.ERROR:Lorg/apache/log4j/Priority;
         * 15: aastore
         * 16: dup
         * 17: iconst_2
         * 18: getstatic     org/apache/log4j/Level.WARN:Lorg/apache/log4j/Level;
         * 21: aastore
         * 22: dup
         * 23: iconst_3
         * 24: getstatic     org/apache/log4j/Priority.INFO:Lorg/apache/log4j/Priority;
         * 27: aastore
         * 28: dup
         * 29: iconst_4
         * 30: getstatic     org/apache/log4j/Priority.DEBUG:Lorg/apache/log4j/Priority;
         * 33: aastore
         * 34: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*final*/ QString Priority::toString() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/apache/log4j/Priority.levelStr:Ljava/lang/String;
         * 4: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*final*/ int Priority::toInt() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/apache/log4j/Priority.level:I
         * 4: ireturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ Priority* Priority::toPriority(QString sArg) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokestatic  org/apache/log4j/Level.toLevel:(Ljava/lang/String;)Lorg/apache/log4j/Level;
         * 4: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ Priority* Priority::toPriority(int val) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: iload_0
         * 1: getstatic     org/apache/log4j/Priority.DEBUG:Lorg/apache/log4j/Priority;
         * 4: invokestatic  org/apache/log4j/Priority.toPriority:(ILorg/apache/log4j/Priority;)Lorg/apache/log4j/Priority;
         * 7: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ Priority* Priority::toPriority(int val, Priority* defaultPriority) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: iload_0
         * 1: aload_1
         * 2: checkcast     org/apache/log4j/Level
         * 5: invokestatic  org/apache/log4j/Level.toLevel:(ILorg/apache/log4j/Level;)Lorg/apache/log4j/Level;
         * 8: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ /*static*/ Priority* Priority::toPriority(QString sArg, Priority* defaultPriority) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: checkcast     org/apache/log4j/Level
         * 5: invokestatic  org/apache/log4j/Level.toLevel:(Ljava/lang/String;Lorg/apache/log4j/Level;)Lorg/apache/log4j/Level;
         * 8: areturn
         *  */
        // </editor-fold>
    }

