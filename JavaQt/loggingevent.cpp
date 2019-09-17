#include "loggingevent.h"
#include <QDateTime>
#include "logger.h"

LoggingEvent::LoggingEvent(QObject *parent) : QObject(parent)
{

}
// /*public*/ class LoggingEvent implements Serializable {

/*private*/ /*static*/ qint64 LoggingEvent::startTime = 0;
#if 0
/*public*/ final transient String fqnOfCategoryClass;
/*private*/ transient Category logger;
/*public*/ final String categoryName;
/*public*/ transient Priority level;
/*private*/ String ndc;
/*private*/ Hashtable mdcCopy;
/*private*/ boolean ndcLookupRequired;
/*private*/ boolean mdcCopyLookupRequired;
/*private*/ /*transient*/ QString message;
/*private*/ String renderedMessage;
/*private*/ String threadName;
/*private*/ ThrowableInformation throwableInfo;
/*public*/ final long timeStamp;
/*private*/ LocationInfo locationInfo;
static final long serialVersionUID = -868428216207166145L;
static final Integer[] PARAM_ARRAY;
static final String TO_LEVEL = "toLevel";
static final Class[] TO_LEVEL_PARAMS;
static final Hashtable methodCache;
#endif
/*public*/ LoggingEvent::LoggingEvent(/*QString fqnOfCategoryClass,*/ QString loggerName, LogLevel *level, QString message, Throwable* throwable, QObject *parent) : QObject(parent){
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: aload_0
     * 5: iconst_1
     * 6: putfield      org/apache/log4j/spi/LoggingEvent.ndcLookupRequired:Z
     * 9: aload_0
     * 10: iconst_1
     * 11: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopyLookupRequired:Z
     * 14: aload_0
     * 15: aload_1
     * 16: putfield      org/apache/log4j/spi/LoggingEvent.fqnOfCategoryClass:Ljava/lang/String;
     * 19: aload_0
     * 20: aload_2
     * 21: putfield      org/apache/log4j/spi/LoggingEvent.logger:Lorg/apache/log4j/Category;
     * 24: aload_0
     * 25: aload_2
     * 26: invokevirtual org/apache/log4j/Category.getName:()Ljava/lang/String;
     * 29: putfield      org/apache/log4j/spi/LoggingEvent.categoryName:Ljava/lang/String;
     * 32: aload_0
     * 33: aload_3
     * 34: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 37: aload_0
     * 38: aload         4
     * 40: putfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 43: aload         5
     * 45: ifnull        62
     * 48: aload_0
     * 49: new           org/apache/log4j/spi/ThrowableInformation
     * 52: dup
     * 53: aload         5
     * 55: aload_2
     * 56: invokespecial org/apache/log4j/spi/ThrowableInformation."<init>":(Ljava/lang/Throwable;Lorg/apache/log4j/Category;)V
     * 59: putfield      org/apache/log4j/spi/LoggingEvent.throwableInfo:Lorg/apache/log4j/spi/ThrowableInformation;
     * 62: aload_0
     * 63: invokestatic  java/lang/System.currentTimeMillis:()J
     * 66: putfield      org/apache/log4j/spi/LoggingEvent.timeStamp:J
     * 69: return
     *  */
    // </editor-fold>
 this->message = message;
 this->logLevel = (LogLevel*)level;
 this->categoryName = loggerName;
 this->throwable = throwable;
 this->startTime = QDateTime::currentMSecsSinceEpoch();
}
#if 0
/*public*/ LoggingEvent(String fqnOfCategoryClass, Category logger, long timeStamp, Priority level, Object message, Throwable throwable) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: aload_0
     * 5: iconst_1
     * 6: putfield      org/apache/log4j/spi/LoggingEvent.ndcLookupRequired:Z
     * 9: aload_0
     * 10: iconst_1
     * 11: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopyLookupRequired:Z
     * 14: aload_0
     * 15: aload_1
     * 16: putfield      org/apache/log4j/spi/LoggingEvent.fqnOfCategoryClass:Ljava/lang/String;
     * 19: aload_0
     * 20: aload_2
     * 21: putfield      org/apache/log4j/spi/LoggingEvent.logger:Lorg/apache/log4j/Category;
     * 24: aload_0
     * 25: aload_2
     * 26: invokevirtual org/apache/log4j/Category.getName:()Ljava/lang/String;
     * 29: putfield      org/apache/log4j/spi/LoggingEvent.categoryName:Ljava/lang/String;
     * 32: aload_0
     * 33: aload         5
     * 35: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 38: aload_0
     * 39: aload         6
     * 41: putfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 44: aload         7
     * 46: ifnull        63
     * 49: aload_0
     * 50: new           org/apache/log4j/spi/ThrowableInformation
     * 53: dup
     * 54: aload         7
     * 56: aload_2
     * 57: invokespecial org/apache/log4j/spi/ThrowableInformation."<init>":(Ljava/lang/Throwable;Lorg/apache/log4j/Category;)V
     * 60: putfield      org/apache/log4j/spi/LoggingEvent.throwableInfo:Lorg/apache/log4j/spi/ThrowableInformation;
     * 63: aload_0
     * 64: lload_3
     * 65: putfield      org/apache/log4j/spi/LoggingEvent.timeStamp:J
     * 68: return
     *  */
    // </editor-fold>
 this
}

/*public*/ LoggingEvent(String fqnOfCategoryClass, Category logger, long timeStamp, Level level, Object message, String threadName, ThrowableInformation throwable, String ndc, LocationInfo info, Map properties) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: aload_0
     * 5: iconst_1
     * 6: putfield      org/apache/log4j/spi/LoggingEvent.ndcLookupRequired:Z
     * 9: aload_0
     * 10: iconst_1
     * 11: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopyLookupRequired:Z
     * 14: aload_0
     * 15: aload_1
     * 16: putfield      org/apache/log4j/spi/LoggingEvent.fqnOfCategoryClass:Ljava/lang/String;
     * 19: aload_0
     * 20: aload_2
     * 21: putfield      org/apache/log4j/spi/LoggingEvent.logger:Lorg/apache/log4j/Category;
     * 24: aload_2
     * 25: ifnull        39
     * 28: aload_0
     * 29: aload_2
     * 30: invokevirtual org/apache/log4j/Category.getName:()Ljava/lang/String;
     * 33: putfield      org/apache/log4j/spi/LoggingEvent.categoryName:Ljava/lang/String;
     * 36: goto          44
     * 39: aload_0
     * 40: aconst_null
     * 41: putfield      org/apache/log4j/spi/LoggingEvent.categoryName:Ljava/lang/String;
     * 44: aload_0
     * 45: aload         5
     * 47: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 50: aload_0
     * 51: aload         6
     * 53: putfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 56: aload         8
     * 58: ifnull        67
     * 61: aload_0
     * 62: aload         8
     * 64: putfield      org/apache/log4j/spi/LoggingEvent.throwableInfo:Lorg/apache/log4j/spi/ThrowableInformation;
     * 67: aload_0
     * 68: lload_3
     * 69: putfield      org/apache/log4j/spi/LoggingEvent.timeStamp:J
     * 72: aload_0
     * 73: aload         7
     * 75: putfield      org/apache/log4j/spi/LoggingEvent.threadName:Ljava/lang/String;
     * 78: aload_0
     * 79: iconst_0
     * 80: putfield      org/apache/log4j/spi/LoggingEvent.ndcLookupRequired:Z
     * 83: aload_0
     * 84: aload         9
     * 86: putfield      org/apache/log4j/spi/LoggingEvent.ndc:Ljava/lang/String;
     * 89: aload_0
     * 90: aload         10
     * 92: putfield      org/apache/log4j/spi/LoggingEvent.locationInfo:Lorg/apache/log4j/spi/LocationInfo;
     * 95: aload_0
     * 96: iconst_0
     * 97: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopyLookupRequired:Z
     * 100: aload         11
     * 102: ifnull        118
     * 105: aload_0
     * 106: new           java/util/Hashtable
     * 109: dup
     * 110: aload         11
     * 112: invokespecial java/util/Hashtable."<init>":(Ljava/util/Map;)V
     * 115: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 118: return
     *  */
    // </editor-fold>
}

/*public*/ LocationInfo getLocationInformation() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.locationInfo:Lorg/apache/log4j/spi/LocationInfo;
     * 4: ifnonnull     29
     * 7: aload_0
     * 8: new           org/apache/log4j/spi/LocationInfo
     * 11: dup
     * 12: new           java/lang/Throwable
     * 15: dup
     * 16: invokespecial java/lang/Throwable."<init>":()V
     * 19: aload_0
     * 20: getfield      org/apache/log4j/spi/LoggingEvent.fqnOfCategoryClass:Ljava/lang/String;
     * 23: invokespecial org/apache/log4j/spi/LocationInfo."<init>":(Ljava/lang/Throwable;Ljava/lang/String;)V
     * 26: putfield      org/apache/log4j/spi/LoggingEvent.locationInfo:Lorg/apache/log4j/spi/LocationInfo;
     * 29: aload_0
     * 30: getfield      org/apache/log4j/spi/LoggingEvent.locationInfo:Lorg/apache/log4j/spi/LocationInfo;
     * 33: areturn
     *  */
    // </editor-fold>
}
#endif
/*public*/ int LoggingEvent::getLevel() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 4: checkcast     org/apache/log4j/Level
     * 7: areturn
     *  */
    // </editor-fold>
 return logLevel->level;
}

/*public*/ QString LoggingEvent::getLoggerName() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.categoryName:Ljava/lang/String;
     * 4: areturn
     *  */
    // </editor-fold>
 return categoryName;
}
#if 0
/*public*/ /*Category*/Logger* LoggingEvent::getLogger() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.logger:Lorg/apache/log4j/Category;
     * 4: areturn
     *  */
    // </editor-fold>
 return
}
#endif
/*public*/ QString LoggingEvent::getMessage() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 4: ifnull        12
     * 7: aload_0
     * 8: getfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 11: areturn
     * 12: aload_0
     * 13: invokevirtual org/apache/log4j/spi/LoggingEvent.getRenderedMessage:()Ljava/lang/String;
     * 16: areturn
     *  */
    // </editor-fold>
 return message;
}
#if 0
/*public*/ String getNDC() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.ndcLookupRequired:Z
     * 4: ifeq          19
     * 7: aload_0
     * 8: iconst_0
     * 9: putfield      org/apache/log4j/spi/LoggingEvent.ndcLookupRequired:Z
     * 12: aload_0
     * 13: invokestatic  org/apache/log4j/NDC.get:()Ljava/lang/String;
     * 16: putfield      org/apache/log4j/spi/LoggingEvent.ndc:Ljava/lang/String;
     * 19: aload_0
     * 20: getfield      org/apache/log4j/spi/LoggingEvent.ndc:Ljava/lang/String;
     * 23: areturn
     *  */
    // </editor-fold>
}

/*public*/ Object getMDC(String key) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 4: ifnull        22
     * 7: aload_0
     * 8: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 11: aload_1
     * 12: invokevirtual java/util/Hashtable.get:(Ljava/lang/Object;)Ljava/lang/Object;
     * 15: astore_2
     * 16: aload_2
     * 17: ifnull        22
     * 20: aload_2
     * 21: areturn
     * 22: aload_1
     * 23: invokestatic  org/apache/log4j/MDC.get:(Ljava/lang/String;)Ljava/lang/Object;
     * 26: areturn
     *  */
    // </editor-fold>
}

/*public*/ void getMDCCopy() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopyLookupRequired:Z
     * 4: ifeq          31
     * 7: aload_0
     * 8: iconst_0
     * 9: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopyLookupRequired:Z
     * 12: invokestatic  org/apache/log4j/MDC.getContext:()Ljava/util/Hashtable;
     * 15: astore_1
     * 16: aload_1
     * 17: ifnull        31
     * 20: aload_0
     * 21: aload_1
     * 22: invokevirtual java/util/Hashtable.clone:()Ljava/lang/Object;
     * 25: checkcast     java/util/Hashtable
     * 28: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 31: return
     *  */
    // </editor-fold>
}

/*public*/ String getRenderedMessage() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.renderedMessage:Ljava/lang/String;
     * 4: ifnonnull     89
     * 7: aload_0
     * 8: getfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 11: ifnull        89
     * 14: aload_0
     * 15: getfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 18: instanceof    java/lang/String
     * 21: ifeq          38
     * 24: aload_0
     * 25: aload_0
     * 26: getfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 29: checkcast     java/lang/String
     * 32: putfield      org/apache/log4j/spi/LoggingEvent.renderedMessage:Ljava/lang/String;
     * 35: goto          89
     * 38: aload_0
     * 39: getfield      org/apache/log4j/spi/LoggingEvent.logger:Lorg/apache/log4j/Category;
     * 42: invokevirtual org/apache/log4j/Category.getLoggerRepository:()Lorg/apache/log4j/spi/LoggerRepository;
     * 45: astore_1
     * 46: aload_1
     * 47: instanceof    org/apache/log4j/spi/RendererSupport
     * 50: ifeq          78
     * 53: aload_1
     * 54: checkcast     org/apache/log4j/spi/RendererSupport
     * 57: astore_2
     * 58: aload_0
     * 59: aload_2
     * 60: invokeinterface org/apache/log4j/spi/RendererSupport.getRendererMap:()Lorg/apache/log4j/or/RendererMap;
     * 65: aload_0
     * 66: getfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 69: invokevirtual org/apache/log4j/or/RendererMap.findAndRender:(Ljava/lang/Object;)Ljava/lang/String;
     * 72: putfield      org/apache/log4j/spi/LoggingEvent.renderedMessage:Ljava/lang/String;
     * 75: goto          89
     * 78: aload_0
     * 79: aload_0
     * 80: getfield      org/apache/log4j/spi/LoggingEvent.message:Ljava/lang/Object;
     * 83: invokevirtual java/lang/Object.toString:()Ljava/lang/String;
     * 86: putfield      org/apache/log4j/spi/LoggingEvent.renderedMessage:Ljava/lang/String;
     * 89: aload_0
     * 90: getfield      org/apache/log4j/spi/LoggingEvent.renderedMessage:Ljava/lang/String;
     * 93: areturn
     *  */
    // </editor-fold>
}

/*public*/ static long getStartTime() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: getstatic     org/apache/log4j/spi/LoggingEvent.startTime:J
     * 3: lreturn
     *  */
    // </editor-fold>
}

/*public*/ String getThreadName() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.threadName:Ljava/lang/String;
     * 4: ifnonnull     17
     * 7: aload_0
     * 8: invokestatic  java/lang/Thread.currentThread:()Ljava/lang/Thread;
     * 11: invokevirtual java/lang/Thread.getName:()Ljava/lang/String;
     * 14: putfield      org/apache/log4j/spi/LoggingEvent.threadName:Ljava/lang/String;
     * 17: aload_0
     * 18: getfield      org/apache/log4j/spi/LoggingEvent.threadName:Ljava/lang/String;
     * 21: areturn
     *  */
    // </editor-fold>
}

/*public*/ ThrowableInformation getThrowableInformation() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.throwableInfo:Lorg/apache/log4j/spi/ThrowableInformation;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ String[] getThrowableStrRep() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.throwableInfo:Lorg/apache/log4j/spi/ThrowableInformation;
     * 4: ifnonnull     9
     * 7: aconst_null
     * 8: areturn
     * 9: aload_0
     * 10: getfield      org/apache/log4j/spi/LoggingEvent.throwableInfo:Lorg/apache/log4j/spi/ThrowableInformation;
     * 13: invokevirtual org/apache/log4j/spi/ThrowableInformation.getThrowableStrRep:()[Ljava/lang/String;
     * 16: areturn
     *  */
    // </editor-fold>
}

/*private*/ void readLevel(ObjectInputStream ois) throws IOException, ClassNotFoundException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: invokevirtual java/io/ObjectInputStream.readInt:()I
     * 4: istore_2
     * 5: aload_1
     * 6: invokevirtual java/io/ObjectInputStream.readObject:()Ljava/lang/Object;
     * 9: checkcast     java/lang/String
     * 12: astore_3
     * 13: aload_3
     * 14: ifnonnull     28
     * 17: aload_0
     * 18: iload_2
     * 19: invokestatic  org/apache/log4j/Level.toLevel:(I)Lorg/apache/log4j/Level;
     * 22: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 25: goto          101
     * 28: getstatic     org/apache/log4j/spi/LoggingEvent.methodCache:Ljava/util/Hashtable;
     * 31: aload_3
     * 32: invokevirtual java/util/Hashtable.get:(Ljava/lang/Object;)Ljava/lang/Object;
     * 35: checkcast     java/lang/reflect/Method
     * 38: astore        4
     * 40: aload         4
     * 42: ifnonnull     73
     * 45: aload_3
     * 46: invokestatic  org/apache/log4j/helpers/Loader.loadClass:(Ljava/lang/String;)Ljava/lang/Class;
     * 49: astore        5
     * 51: aload         5
     * 53: ldc           toLevel
     * 55: getstatic     org/apache/log4j/spi/LoggingEvent.TO_LEVEL_PARAMS:[Ljava/lang/Class;
     * 58: invokevirtual java/lang/Class.getDeclaredMethod:(Ljava/lang/String;[Ljava/lang/Class;)Ljava/lang/reflect/Method;
     * 61: astore        4
     * 63: getstatic     org/apache/log4j/spi/LoggingEvent.methodCache:Ljava/util/Hashtable;
     * 66: aload_3
     * 67: aload         4
     * 69: invokevirtual java/util/Hashtable.put:(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
     * 72: pop
     * 73: aload_0
     * 74: aload         4
     * 76: aconst_null
     * 77: iconst_1
     * 78: anewarray     java/lang/Integer
     * 81: dup
     * 82: iconst_0
     * 83: new           java/lang/Integer
     * 86: dup
     * 87: iload_2
     * 88: invokespecial java/lang/Integer."<init>":(I)V
     * 91: aastore
     * 92: invokevirtual java/lang/reflect/Method.invoke:(Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;
     * 95: checkcast     org/apache/log4j/Level
     * 98: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 101: goto          199
     * 104: astore_3
     * 105: aload_3
     * 106: invokevirtual java/lang/reflect/InvocationTargetException.getTargetException:()Ljava/lang/Throwable;
     * 109: instanceof    java/lang/InterruptedException
     * 112: ifne          125
     * 115: aload_3
     * 116: invokevirtual java/lang/reflect/InvocationTargetException.getTargetException:()Ljava/lang/Throwable;
     * 119: instanceof    java/io/InterruptedIOException
     * 122: ifeq          131
     * 125: invokestatic  java/lang/Thread.currentThread:()Ljava/lang/Thread;
     * 128: invokevirtual java/lang/Thread.interrupt:()V
     * 131: ldc           Level deserialization failed, reverting to default.
     * 133: aload_3
     * 134: invokestatic  org/apache/log4j/helpers/LogLog.warn:(Ljava/lang/String;Ljava/lang/Throwable;)V
     * 137: aload_0
     * 138: iload_2
     * 139: invokestatic  org/apache/log4j/Level.toLevel:(I)Lorg/apache/log4j/Level;
     * 142: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 145: goto          199
     * 148: astore_3
     * 149: ldc           Level deserialization failed, reverting to default.
     * 151: aload_3
     * 152: invokestatic  org/apache/log4j/helpers/LogLog.warn:(Ljava/lang/String;Ljava/lang/Throwable;)V
     * 155: aload_0
     * 156: iload_2
     * 157: invokestatic  org/apache/log4j/Level.toLevel:(I)Lorg/apache/log4j/Level;
     * 160: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 163: goto          199
     * 166: astore_3
     * 167: ldc           Level deserialization failed, reverting to default.
     * 169: aload_3
     * 170: invokestatic  org/apache/log4j/helpers/LogLog.warn:(Ljava/lang/String;Ljava/lang/Throwable;)V
     * 173: aload_0
     * 174: iload_2
     * 175: invokestatic  org/apache/log4j/Level.toLevel:(I)Lorg/apache/log4j/Level;
     * 178: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 181: goto          199
     * 184: astore_3
     * 185: ldc           Level deserialization failed, reverting to default.
     * 187: aload_3
     * 188: invokestatic  org/apache/log4j/helpers/LogLog.warn:(Ljava/lang/String;Ljava/lang/Throwable;)V
     * 191: aload_0
     * 192: iload_2
     * 193: invokestatic  org/apache/log4j/Level.toLevel:(I)Lorg/apache/log4j/Level;
     * 196: putfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 199: return
     * Exception table:
     * from    to  target type
     * 5   101   104   Class java/lang/reflect/InvocationTargetException
     * 5   101   148   Class java/lang/NoSuchMethodException
     * 5   101   166   Class java/lang/IllegalAccessException
     * 5   101   184   Class java/lang/RuntimeException
     *  */
    // </editor-fold>
}

/*private*/ void readObject(ObjectInputStream ois) throws IOException, ClassNotFoundException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: invokevirtual java/io/ObjectInputStream.defaultReadObject:()V
     * 4: aload_0
     * 5: aload_1
     * 6: invokespecial org/apache/log4j/spi/LoggingEvent.readLevel:(Ljava/io/ObjectInputStream;)V
     * 9: aload_0
     * 10: getfield      org/apache/log4j/spi/LoggingEvent.locationInfo:Lorg/apache/log4j/spi/LocationInfo;
     * 13: ifnonnull     29
     * 16: aload_0
     * 17: new           org/apache/log4j/spi/LocationInfo
     * 20: dup
     * 21: aconst_null
     * 22: aconst_null
     * 23: invokespecial org/apache/log4j/spi/LocationInfo."<init>":(Ljava/lang/Throwable;Ljava/lang/String;)V
     * 26: putfield      org/apache/log4j/spi/LoggingEvent.locationInfo:Lorg/apache/log4j/spi/LocationInfo;
     * 29: return
     *  */
    // </editor-fold>
}

/*private*/ void writeObject(ObjectOutputStream oos) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokevirtual org/apache/log4j/spi/LoggingEvent.getThreadName:()Ljava/lang/String;
     * 4: pop
     * 5: aload_0
     * 6: invokevirtual org/apache/log4j/spi/LoggingEvent.getRenderedMessage:()Ljava/lang/String;
     * 9: pop
     * 10: aload_0
     * 11: invokevirtual org/apache/log4j/spi/LoggingEvent.getNDC:()Ljava/lang/String;
     * 14: pop
     * 15: aload_0
     * 16: invokevirtual org/apache/log4j/spi/LoggingEvent.getMDCCopy:()V
     * 19: aload_0
     * 20: invokevirtual org/apache/log4j/spi/LoggingEvent.getThrowableStrRep:()[Ljava/lang/String;
     * 23: pop
     * 24: aload_1
     * 25: invokevirtual java/io/ObjectOutputStream.defaultWriteObject:()V
     * 28: aload_0
     * 29: aload_1
     * 30: invokespecial org/apache/log4j/spi/LoggingEvent.writeLevel:(Ljava/io/ObjectOutputStream;)V
     * 33: return
     *  */
    // </editor-fold>
}

/*private*/ void writeLevel(ObjectOutputStream oos) throws IOException {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: aload_0
     * 2: getfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 5: invokevirtual org/apache/log4j/Priority.toInt:()I
     * 8: invokevirtual java/io/ObjectOutputStream.writeInt:(I)V
     * 11: aload_0
     * 12: getfield      org/apache/log4j/spi/LoggingEvent.level:Lorg/apache/log4j/Priority;
     * 15: invokevirtual java/lang/Object.getClass:()Ljava/lang/Class;
     * 18: astore_2
     * 19: aload_2
     * 20: getstatic     org/apache/log4j/spi/LoggingEvent.class$org$apache$log4j$Level:Ljava/lang/Class;
     * 23: ifnonnull     38
     * 26: ldc           org.apache.log4j.Level
     * 28: invokestatic  org/apache/log4j/spi/LoggingEvent.class$:(Ljava/lang/String;)Ljava/lang/Class;
     * 31: dup
     * 32: putstatic     org/apache/log4j/spi/LoggingEvent.class$org$apache$log4j$Level:Ljava/lang/Class;
     * 35: goto          41
     * 38: getstatic     org/apache/log4j/spi/LoggingEvent.class$org$apache$log4j$Level:Ljava/lang/Class;
     * 41: if_acmpne     52
     * 44: aload_1
     * 45: aconst_null
     * 46: invokevirtual java/io/ObjectOutputStream.writeObject:(Ljava/lang/Object;)V
     * 49: goto          60
     * 52: aload_1
     * 53: aload_2
     * 54: invokevirtual java/lang/Class.getName:()Ljava/lang/String;
     * 57: invokevirtual java/io/ObjectOutputStream.writeObject:(Ljava/lang/Object;)V
     * 60: return
     *  */
    // </editor-fold>
}

/*public*/ final void setProperty(String propName, String propValue) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 4: ifnonnull     11
     * 7: aload_0
     * 8: invokevirtual org/apache/log4j/spi/LoggingEvent.getMDCCopy:()V
     * 11: aload_0
     * 12: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 15: ifnonnull     29
     * 18: aload_0
     * 19: new           java/util/Hashtable
     * 22: dup
     * 23: invokespecial java/util/Hashtable."<init>":()V
     * 26: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 29: aload_0
     * 30: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 33: aload_1
     * 34: aload_2
     * 35: invokevirtual java/util/Hashtable.put:(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;
     * 38: pop
     * 39: return
     *  */
    // </editor-fold>
}

/*public*/ final String getProperty(String key) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: aload_1
     * 2: invokevirtual org/apache/log4j/spi/LoggingEvent.getMDC:(Ljava/lang/String;)Ljava/lang/Object;
     * 5: astore_2
     * 6: aconst_null
     * 7: astore_3
     * 8: aload_2
     * 9: ifnull        17
     * 12: aload_2
     * 13: invokevirtual java/lang/Object.toString:()Ljava/lang/String;
     * 16: astore_3
     * 17: aload_3
     * 18: areturn
     *  */
    // </editor-fold>
}

/*public*/ final boolean locationInformationExists() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.locationInfo:Lorg/apache/log4j/spi/LocationInfo;
     * 4: ifnull        11
     * 7: iconst_1
     * 8: goto          12
     * 11: iconst_0
     * 12: ireturn
     *  */
    // </editor-fold>
}

/*public*/ final long getTimeStamp() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.timeStamp:J
     * 4: lreturn
     *  */
    // </editor-fold>
}

/*public*/ Set getPropertyKeySet() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokevirtual org/apache/log4j/spi/LoggingEvent.getProperties:()Ljava/util/Map;
     * 4: invokeinterface java/util/Map.keySet:()Ljava/util/Set;
     * 9: areturn
     *  */
    // </editor-fold>
}

/*public*/ Map getProperties() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokevirtual org/apache/log4j/spi/LoggingEvent.getMDCCopy:()V
     * 4: aload_0
     * 5: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 8: ifnonnull     22
     * 11: new           java/util/HashMap
     * 14: dup
     * 15: invokespecial java/util/HashMap."<init>":()V
     * 18: astore_1
     * 19: goto          27
     * 22: aload_0
     * 23: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 26: astore_1
     * 27: aload_1
     * 28: invokestatic  java/util/Collections.unmodifiableMap:(Ljava/util/Map;)Ljava/util/Map;
     * 31: areturn
     *  */
    // </editor-fold>
}

/*public*/ String getFQNOfLoggerClass() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.fqnOfCategoryClass:Ljava/lang/String;
     * 4: areturn
     *  */
    // </editor-fold>
}

/*public*/ Object removeProperty(String propName) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 4: ifnonnull     11
     * 7: aload_0
     * 8: invokevirtual org/apache/log4j/spi/LoggingEvent.getMDCCopy:()V
     * 11: aload_0
     * 12: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 15: ifnonnull     29
     * 18: aload_0
     * 19: new           java/util/Hashtable
     * 22: dup
     * 23: invokespecial java/util/Hashtable."<init>":()V
     * 26: putfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 29: aload_0
     * 30: getfield      org/apache/log4j/spi/LoggingEvent.mdcCopy:Ljava/util/Hashtable;
     * 33: aload_1
     * 34: invokevirtual java/util/Hashtable.remove:(Ljava/lang/Object;)Ljava/lang/Object;
     * 37: areturn
     *  */
    // </editor-fold>
}

#endif
