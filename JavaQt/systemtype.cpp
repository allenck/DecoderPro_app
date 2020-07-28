#include "systemtype.h"
#include "loggerfactory.h"

SystemType::SystemType(QObject *parent) : QObject(parent)
{

}
/**
 * Common utility methods for determining which type of operating system is in
 * use.
 *
 * @author Bob Jacobsen Copyright 2006
 * @author Daniel Boudreau Copyright 2012 (add Unix)
 * @author Randall Wood Copyright 2013
 */
// /*public*/ class SystemType {


    /*static*/ int SystemType::type = 0;
    /*static*/ bool SystemType::isSet = false;

    /*static*/ QString SystemType::osName;

    /**
     * Get the integer constant for the OS. Useful in switch statements.
     *
     * @return Type as an integer
     */
    /*public*/ /*static*/ int SystemType::getType() {
        setType();
        return type;
    }

    /**
     * The os.name property
     *
     * @return OS name
     */
    /*public*/ /*static*/ QString SystemType::getOSName() {
        setType();
        return osName;
    }

    /**
     * Convenience method to determine if OS is Mac OS X. Useful if an exception
     * needs to be made for Mac OS X.
     *
     * @return true if on Mac OS X.
     */
    /*public*/ /*static*/ bool SystemType::isMacOSX() {
        setType();
        return (type == MACOSX);
    }

    /**
     * Convenience method to determine if OS is Linux. Useful if an exception
     * needs to be made for Linux.
     *
     * @return true if on Linux
     */
    /*public*/ /*static*/ bool SystemType::isLinux() {
        setType();
        return (type == LINUX);
    }

    /**
     * Convenience method to determine if OS is Microsoft Windows. Useful if an
     * exception needs to be made for Microsoft Windows.
     *
     * @return true if on Microsoft Windows
     */
    /*public*/ /*static*/ bool SystemType::isWindows() {
        setType();
        return (type == WINDOWS);
    }

    /**
     * Convenience method to determine if OS is OS/2. Useful if an exception
     * needs to be made for OS/2.
     *
     * @return true if on OS/2
     */
    /*public*/ /*static*/ bool SystemType::isOS2() {
        setType();
        return (type == OS2);
    }

    /**
     * Convenience method to determine if OS is Unix. Useful if an exception
     * needs to be made for Unix.
     *
     * @return true if on Unix
     */
    /*public*/ /*static*/ bool SystemType::isUnix() {
        setType();
        return (type == UNIX);
    }

    /*static*/ void SystemType::setType() {
        if (isSet) {
            return;
        }
        isSet = true;
#if 0
        osName = System.getProperty("os.name");
        QString lowerCaseName = osName.toLowerCase();

        if (lowerCaseName.contains("os x")) { // Prefered test per http://developer.apple.com/library/mac/#technotes/tn2002/tn2110.html
            // Mac OS X
            type = MACOSX;
        } else if (lowerCaseName.contains("linux")) {
            // Linux
            type = LINUX;
        } else if (lowerCaseName.contains("os/2")) {
            // OS/2
            type = OS2;
        } else if (lowerCaseName.contains("windows")) {  // usually a suffix indicates flavor
            // Windows
            type = WINDOWS;
        } else if (lowerCaseName.contains("nix") || lowerCaseName.contains("nux") || lowerCaseName.contains("aix") || lowerCaseName.contains("solaris")) {
            // Unix
            type = UNIX;
        } else {
            // No match
            type = 0;
            log.error("Could not determine system type from os.name=/{}/", osName);
        }
#else
#ifdef Q_OS_WIN
        type = WINDOWS;
#endif
#ifdef Q_OS_LINUX
        type = LINUX;
#endif
#ifdef Q_OS_UNIX
        type = unix;
#endif
#ifdef Q_OS_MACOSX
        type = MACOS;
#endif
#endif
    }

    // initialize logging
    /*private*/ /*final*/ /*static*/ Logger* log = LoggerFactory::getLogger("SystemType");
