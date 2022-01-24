#include "loggerfactory.h"

LoggerFactory::LoggerFactory(QObject *parent) : QObject(parent)
{

}
// /*public*/ final class LoggerFactory {
#if 0
static final String CODES_PREFIX = "http://www.slf4j.org/codes.html";
static final String NO_STATICLOGGERBINDER_URL = "http://www.slf4j.org/codes.html#StaticLoggerBinder";
static final String MULTIPLE_BINDINGS_URL = "http://www.slf4j.org/codes.html#multiple_bindings";
static final String NULL_LF_URL = "http://www.slf4j.org/codes.html#null_LF";
static final String VERSION_MISMATCH = "http://www.slf4j.org/codes.html#version_mismatch";
static final String SUBSTITUTE_LOGGER_URL = "http://www.slf4j.org/codes.html#substituteLogger";
static final String LOGGER_NAME_MISMATCH_URL = "http://www.slf4j.org/codes.html#loggerNameMismatch";
static final String UNSUCCESSFUL_INIT_URL = "http://www.slf4j.org/codes.html#unsuccessfulInit";
static final String UNSUCCESSFUL_INIT_MSG = "org.slf4j.LoggerFactory could not be successfully initialized. See also http://www.slf4j.org/codes.html#unsuccessfulInit";
static final int UNINITIALIZED = 0;
static final int ONGOING_INITIALIZATION = 1;
static final int FAILED_INITIALIZATION = 2;
static final int SUCCESSFUL_INITIALIZATION = 3;
static final int NOP_FALLBACK_INITIALIZATION = 4;
static int INITIALIZATION_STATE;
static SubstituteLoggerFactory TEMP_FACTORY;
static NOPLoggerFactory NOP_FALLBACK_FACTORY;
static final String DETECT_LOGGER_NAME_MISMATCH_PROPERTY = "slf4j.detectLoggerNameMismatch";
static boolean DETECT_LOGGER_NAME_MISMATCH;
private static final String[] API_COMPATIBILITY_LIST;
private static String STATIC_LOGGER_BINDER_PATH;

private LoggerFactory() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokespecial java/lang/Object."<init>":()V
     * 4: return
     *  */
    // </editor-fold>
}

static void reset() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_0
     * 1: putstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 4: new           org/slf4j/helpers/SubstituteLoggerFactory
     * 7: dup
     * 8: invokespecial org/slf4j/helpers/SubstituteLoggerFactory."<init>":()V
     * 11: putstatic     org/slf4j/LoggerFactory.TEMP_FACTORY:Lorg/slf4j/helpers/SubstituteLoggerFactory;
     * 14: return
     *  */
    // </editor-fold>
}

private static final void performInitialization() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: invokestatic  org/slf4j/LoggerFactory.bind:()V
     * 3: getstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 6: iconst_3
     * 7: if_icmpne     13
     * 10: invokestatic  org/slf4j/LoggerFactory.versionSanityCheck:()V
     * 13: return
     *  */
    // </editor-fold>
}

private static boolean messageContainsOrgSlf4jImplStaticLoggerBinder(String msg) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: ifnonnull     6
     * 4: iconst_0
     * 5: ireturn
     * 6: aload_0
     * 7: ldc           org/slf4j/impl/StaticLoggerBinder
     * 9: invokevirtual java/lang/String.contains:(Ljava/lang/CharSequence;)Z
     * 12: ifeq          17
     * 15: iconst_1
     * 16: ireturn
     * 17: aload_0
     * 18: ldc           org.slf4j.impl.StaticLoggerBinder
     * 20: invokevirtual java/lang/String.contains:(Ljava/lang/CharSequence;)Z
     * 23: ifeq          28
     * 26: iconst_1
     * 27: ireturn
     * 28: iconst_0
     * 29: ireturn
     *  */
    // </editor-fold>
}

private static final void bind() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: invokestatic  org/slf4j/LoggerFactory.findPossibleStaticLoggerBinderPathSet:()Ljava/util/Set;
     * 3: astore_0
     * 4: aload_0
     * 5: invokestatic  org/slf4j/LoggerFactory.reportMultipleBindingAmbiguity:(Ljava/util/Set;)V
     * 8: invokestatic  org/slf4j/impl/StaticLoggerBinder.getSingleton:()Lorg/slf4j/impl/StaticLoggerBinder;
     * 11: pop
     * 12: iconst_3
     * 13: putstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 16: aload_0
     * 17: invokestatic  org/slf4j/LoggerFactory.reportActualBinding:(Ljava/util/Set;)V
     * 20: invokestatic  org/slf4j/LoggerFactory.fixSubstitutedLoggers:()V
     * 23: goto          126
     * 26: astore_0
     * 27: aload_0
     * 28: invokevirtual java/lang/NoClassDefFoundError.getMessage:()Ljava/lang/String;
     * 31: astore_1
     * 32: aload_1
     * 33: invokestatic  org/slf4j/LoggerFactory.messageContainsOrgSlf4jImplStaticLoggerBinder:(Ljava/lang/String;)Z
     * 36: ifeq          61
     * 39: iconst_4
     * 40: putstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 43: ldc           Failed to load class \"org.slf4j.impl.StaticLoggerBinder\".
     * 45: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 48: ldc           Defaulting to no-operation (NOP) logger implementation
     * 50: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 53: ldc           See http://www.slf4j.org/codes.html#StaticLoggerBinder for further details.
     * 55: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 58: goto          67
     * 61: aload_0
     * 62: invokestatic  org/slf4j/LoggerFactory.failedBinding:(Ljava/lang/Throwable;)V
     * 65: aload_0
     * 66: athrow
     * 67: goto          126
     * 70: astore_0
     * 71: aload_0
     * 72: invokevirtual java/lang/NoSuchMethodError.getMessage:()Ljava/lang/String;
     * 75: astore_1
     * 76: aload_1
     * 77: ifnull        108
     * 80: aload_1
     * 81: ldc           org.slf4j.impl.StaticLoggerBinder.getSingleton()
     * 83: invokevirtual java/lang/String.contains:(Ljava/lang/CharSequence;)Z
     * 86: ifeq          108
     * 89: iconst_2
     * 90: putstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 93: ldc           slf4j-api 1.6.x (or later) is incompatible with this binding.
     * 95: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 98: ldc           Your binding is version 1.5.5 or earlier.
     * 100: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 103: ldc           Upgrade your binding to version 1.6.x.
     * 105: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 108: aload_0
     * 109: athrow
     * 110: astore_0
     * 111: aload_0
     * 112: invokestatic  org/slf4j/LoggerFactory.failedBinding:(Ljava/lang/Throwable;)V
     * 115: new           java/lang/IllegalStateException
     * 118: dup
     * 119: ldc           Unexpected initialization failure
     * 121: aload_0
     * 122: invokespecial java/lang/IllegalStateException."<init>":(Ljava/lang/String;Ljava/lang/Throwable;)V
     * 125: athrow
     * 126: return
     * Exception table:
     * from    to  target type
     * 0    23    26   Class java/lang/NoClassDefFoundError
     * 0    23    70   Class java/lang/NoSuchMethodError
     * 0    23   110   Class java/lang/Exception
     *  */
    // </editor-fold>
}

static void failedBinding(Throwable t) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: iconst_2
     * 1: putstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 4: ldc           Failed to instantiate SLF4J LoggerFactory
     * 6: aload_0
     * 7: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;Ljava/lang/Throwable;)V
     * 10: return
     *  */
    // </editor-fold>
}

private static final void fixSubstitutedLoggers() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: getstatic     org/slf4j/LoggerFactory.TEMP_FACTORY:Lorg/slf4j/helpers/SubstituteLoggerFactory;
     * 3: invokevirtual org/slf4j/helpers/SubstituteLoggerFactory.getLoggers:()Ljava/util/List;
     * 6: astore_0
     * 7: aload_0
     * 8: invokeinterface java/util/List.isEmpty:()Z
     * 13: ifeq          17
     * 16: return
     * 17: ldc           The following set of substitute loggers may have been accessed
     * 19: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 22: ldc           during the initialization phase. Logging calls during this
     * 24: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 27: ldc           phase were not honored. However, subsequent logging calls to these
     * 29: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 32: ldc           loggers will work as normally expected.
     * 34: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 37: ldc           See also http://www.slf4j.org/codes.html#substituteLogger
     * 39: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 42: aload_0
     * 43: invokeinterface java/util/List.iterator:()Ljava/util/Iterator;
     * 48: astore_1
     * 49: aload_1
     * 50: invokeinterface java/util/Iterator.hasNext:()Z
     * 55: ifeq          89
     * 58: aload_1
     * 59: invokeinterface java/util/Iterator.next:()Ljava/lang/Object;
     * 64: checkcast     org/slf4j/helpers/SubstituteLogger
     * 67: astore_2
     * 68: aload_2
     * 69: aload_2
     * 70: invokevirtual org/slf4j/helpers/SubstituteLogger.getName:()Ljava/lang/String;
     * 73: invokestatic  org/slf4j/LoggerFactory.getLogger:(Ljava/lang/String;)Lorg/slf4j/Logger;
     * 76: invokevirtual org/slf4j/helpers/SubstituteLogger.setDelegate:(Lorg/slf4j/Logger;)V
     * 79: aload_2
     * 80: invokevirtual org/slf4j/helpers/SubstituteLogger.getName:()Ljava/lang/String;
     * 83: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 86: goto          49
     * 89: getstatic     org/slf4j/LoggerFactory.TEMP_FACTORY:Lorg/slf4j/helpers/SubstituteLoggerFactory;
     * 92: invokevirtual org/slf4j/helpers/SubstituteLoggerFactory.clear:()V
     * 95: return
     *  */
    // </editor-fold>
}

private static final void versionSanityCheck() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: getstatic     org/slf4j/impl/StaticLoggerBinder.REQUESTED_API_VERSION:Ljava/lang/String;
     * 3: astore_0
     * 4: iconst_0
     * 5: istore_1
     * 6: getstatic     org/slf4j/LoggerFactory.API_COMPATIBILITY_LIST:[Ljava/lang/String;
     * 9: astore_2
     * 10: aload_2
     * 11: arraylength
     * 12: istore_3
     * 13: iconst_0
     * 14: istore        4
     * 16: iload         4
     * 18: iload_3
     * 19: if_icmpge     45
     * 22: aload_2
     * 23: iload         4
     * 25: aaload
     * 26: astore        5
     * 28: aload_0
     * 29: aload         5
     * 31: invokevirtual java/lang/String.startsWith:(Ljava/lang/String;)Z
     * 34: ifeq          39
     * 37: iconst_1
     * 38: istore_1
     * 39: iinc          4, 1
     * 42: goto          16
     * 45: iload_1
     * 46: ifne          93
     * 49: new           java/lang/StringBuilder
     * 52: dup
     * 53: invokespecial java/lang/StringBuilder."<init>":()V
     * 56: ldc           The requested version
     * 58: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 61: aload_0
     * 62: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 65: ldc            by your slf4j binding is not compatible with
     * 67: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 70: getstatic     org/slf4j/LoggerFactory.API_COMPATIBILITY_LIST:[Ljava/lang/String;
     * 73: invokestatic  java/util/Arrays.asList:([Ljava/lang/Object;)Ljava/util/List;
     * 76: invokevirtual java/lang/Object.toString:()Ljava/lang/String;
     * 79: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 82: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 85: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 88: ldc           See http://www.slf4j.org/codes.html#version_mismatch for further details.
     * 90: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 93: goto          107
     * 96: astore_0
     * 97: goto          107
     * 100: astore_0
     * 101: ldc           Unexpected problem occured during version sanity check
     * 103: aload_0
     * 104: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;Ljava/lang/Throwable;)V
     * 107: return
     * Exception table:
     * from    to  target type
     * 0    93    96   Class java/lang/NoSuchFieldError
     * 0    93   100   Class java/lang/Throwable
     *  */
    // </editor-fold>
}

private static Set<URL> findPossibleStaticLoggerBinderPathSet() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: new           java/util/LinkedHashSet
     * 3: dup
     * 4: invokespecial java/util/LinkedHashSet."<init>":()V
     * 7: astore_0
     * 8: ldc_w         org/slf4j/LoggerFactory
     * 11: invokevirtual java/lang/Class.getClassLoader:()Ljava/lang/ClassLoader;
     * 14: astore_1
     * 15: aload_1
     * 16: ifnonnull     29
     * 19: getstatic     org/slf4j/LoggerFactory.STATIC_LOGGER_BINDER_PATH:Ljava/lang/String;
     * 22: invokestatic  java/lang/ClassLoader.getSystemResources:(Ljava/lang/String;)Ljava/util/Enumeration;
     * 25: astore_2
     * 26: goto          37
     * 29: aload_1
     * 30: getstatic     org/slf4j/LoggerFactory.STATIC_LOGGER_BINDER_PATH:Ljava/lang/String;
     * 33: invokevirtual java/lang/ClassLoader.getResources:(Ljava/lang/String;)Ljava/util/Enumeration;
     * 36: astore_2
     * 37: aload_2
     * 38: invokeinterface java/util/Enumeration.hasMoreElements:()Z
     * 43: ifeq          67
     * 46: aload_2
     * 47: invokeinterface java/util/Enumeration.nextElement:()Ljava/lang/Object;
     * 52: checkcast     java/net/URL
     * 55: astore_3
     * 56: aload_0
     * 57: aload_3
     * 58: invokeinterface java/util/Set.add:(Ljava/lang/Object;)Z
     * 63: pop
     * 64: goto          37
     * 67: goto          77
     * 70: astore_1
     * 71: ldc           Error getting resources from path
     * 73: aload_1
     * 74: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;Ljava/lang/Throwable;)V
     * 77: aload_0
     * 78: areturn
     * Exception table:
     * from    to  target type
     * 8    67    70   Class java/io/IOException
     *  */
    // </editor-fold>
}

private static boolean isAmbiguousStaticLoggerBinderPathSet(Set<URL> staticLoggerBinderPathSet) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokeinterface java/util/Set.size:()I
     * 6: iconst_1
     * 7: if_icmple     14
     * 10: iconst_1
     * 11: goto          15
     * 14: iconst_0
     * 15: ireturn
     *  */
    // </editor-fold>
}

private static void reportMultipleBindingAmbiguity(Set<URL> staticLoggerBinderPathSet) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokestatic  org/slf4j/LoggerFactory.isAmbiguousStaticLoggerBinderPathSet:(Ljava/util/Set;)Z
     * 4: ifeq          73
     * 7: ldc           Class path contains multiple SLF4J bindings.
     * 9: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 12: aload_0
     * 13: invokeinterface java/util/Set.iterator:()Ljava/util/Iterator;
     * 18: astore_1
     * 19: aload_1
     * 20: invokeinterface java/util/Iterator.hasNext:()Z
     * 25: ifeq          68
     * 28: aload_1
     * 29: invokeinterface java/util/Iterator.next:()Ljava/lang/Object;
     * 34: checkcast     java/net/URL
     * 37: astore_2
     * 38: new           java/lang/StringBuilder
     * 41: dup
     * 42: invokespecial java/lang/StringBuilder."<init>":()V
     * 45: ldc           Found binding in [
     * 47: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 50: aload_2
     * 51: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
     * 54: ldc           ]
     * 56: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 59: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 62: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 65: goto          19
     * 68: ldc           See http://www.slf4j.org/codes.html#multiple_bindings for an explanation.
     * 70: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 73: return
     *  */
    // </editor-fold>
}

private static void reportActualBinding(Set<URL> staticLoggerBinderPathSet) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokestatic  org/slf4j/LoggerFactory.isAmbiguousStaticLoggerBinderPathSet:(Ljava/util/Set;)Z
     * 4: ifeq          39
     * 7: new           java/lang/StringBuilder
     * 10: dup
     * 11: invokespecial java/lang/StringBuilder."<init>":()V
     * 14: ldc           Actual binding is of type [
     * 16: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 19: invokestatic  org/slf4j/impl/StaticLoggerBinder.getSingleton:()Lorg/slf4j/impl/StaticLoggerBinder;
     * 22: invokevirtual org/slf4j/impl/StaticLoggerBinder.getLoggerFactoryClassStr:()Ljava/lang/String;
     * 25: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 28: ldc           ]
     * 30: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
     * 33: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
     * 36: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 39: return
     *  */
    // </editor-fold>
}
#endif
/*private*/ QMap<QString, Logger*>* LoggerFactory::loggerMap = new QMap<QString, Logger*>();

/*public*/ /*static*/ Logger* LoggerFactory::getLogger(QString name) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: invokestatic  org/slf4j/LoggerFactory.getILoggerFactory:()Lorg/slf4j/ILoggerFactory;
     * 3: astore_1
     * 4: aload_1
     * 5: aload_0
     * 6: invokeinterface org/slf4j/ILoggerFactory.getLogger:(Ljava/lang/String;)Lorg/slf4j/Logger;
     * 11: areturn
     *  */
    // </editor-fold>
  if(loggerMap == nullptr)
   loggerMap = new QMap<QString, Logger*>();
  if(loggerMap->contains(name))
   return loggerMap->value(name);
  Logger* log;
  loggerMap->insert(name, log = new Logger(name));
  return log;
}
#if 0
/*public*/ static Logger getLogger(Class<?> clazz) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_0
     * 1: invokevirtual java/lang/Class.getName:()Ljava/lang/String;
     * 4: invokestatic  org/slf4j/LoggerFactory.getLogger:(Ljava/lang/String;)Lorg/slf4j/Logger;
     * 7: astore_1
     * 8: getstatic     org/slf4j/LoggerFactory.DETECT_LOGGER_NAME_MISMATCH:Z
     * 11: ifeq          63
     * 14: invokestatic  org/slf4j/helpers/Util.getCallingClass:()Ljava/lang/Class;
     * 17: astore_2
     * 18: aload_2
     * 19: ifnull        63
     * 22: aload_0
     * 23: aload_2
     * 24: invokestatic  org/slf4j/LoggerFactory.nonMatchingClasses:(Ljava/lang/Class;Ljava/lang/Class;)Z
     * 27: ifeq          63
     * 30: ldc           Detected logger name mismatch. Given name: \"%s\"; computed name: \"%s\".
     * 32: iconst_2
     * 33: anewarray     java/lang/Object
     * 36: dup
     * 37: iconst_0
     * 38: aload_1
     * 39: invokeinterface org/slf4j/Logger.getName:()Ljava/lang/String;
     * 44: aastore
     * 45: dup
     * 46: iconst_1
     * 47: aload_2
     * 48: invokevirtual java/lang/Class.getName:()Ljava/lang/String;
     * 51: aastore
     * 52: invokestatic  java/lang/String.format:(Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/String;
     * 55: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 58: ldc           See http://www.slf4j.org/codes.html#loggerNameMismatch for an explanation
     * 60: invokestatic  org/slf4j/helpers/Util.report:(Ljava/lang/String;)V
     * 63: aload_1
     * 64: areturn
     *  */
    // </editor-fold>
}

private static boolean nonMatchingClasses(Class<?> clazz, Class<?> autoComputedCallingClass) {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: aload_1
     * 1: aload_0
     * 2: invokevirtual java/lang/Class.isAssignableFrom:(Ljava/lang/Class;)Z
     * 5: ifne          12
     * 8: iconst_1
     * 9: goto          13
     * 12: iconst_0
     * 13: ireturn
     *  */
    // </editor-fold>
}

/*public*/ static ILoggerFactory getILoggerFactory() {
    // <editor-fold defaultstate="collapsed" desc="Compiled Code">
    /* 0: getstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 3: ifne          13
     * 6: iconst_1
     * 7: putstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 10: invokestatic  org/slf4j/LoggerFactory.performInitialization:()V
     * 13: getstatic     org/slf4j/LoggerFactory.INITIALIZATION_STATE:I
     * 16: tableswitch   { // 1 to 4
     * 1: 69
     * 2: 59
     * 3: 48
     * 4: 55
     * default: 73
     * }
     * 48: invokestatic  org/slf4j/impl/StaticLoggerBinder.getSingleton:()Lorg/slf4j/impl/StaticLoggerBinder;
     * 51: invokevirtual org/slf4j/impl/StaticLoggerBinder.getLoggerFactory:()Lorg/slf4j/ILoggerFactory;
     * 54: areturn
     * 55: getstatic     org/slf4j/LoggerFactory.NOP_FALLBACK_FACTORY:Lorg/slf4j/helpers/NOPLoggerFactory;
     * 58: areturn
     * 59: new           java/lang/IllegalStateException
     * 62: dup
     * 63: ldc           org.slf4j.LoggerFactory could not be successfully initialized. See also http://www.slf4j.org/codes.html#unsuccessfulInit
     * 65: invokespecial java/lang/IllegalStateException."<init>":(Ljava/lang/String;)V
     * 68: athrow
     * 69: getstatic     org/slf4j/LoggerFactory.TEMP_FACTORY:Lorg/slf4j/helpers/SubstituteLoggerFactory;
     * 72: areturn
     * 73: new           java/lang/IllegalStateException
     * 76: dup
     * 77: ldc           Unreachable code
     * 79: invokespecial java/lang/IllegalStateException."<init>":(Ljava/lang/String;)V
     * 82: athrow
     *  */
    // </editor-fold>
}
#endif
