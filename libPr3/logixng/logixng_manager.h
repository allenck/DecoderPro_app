#ifndef LOGIXNG_MANAGER_H
#define LOGIXNG_MANAGER_H

#include <manager.h>
#include "logixng.h"
#include "clipboard.h"
#include "base.h"


/**
 * Manager for LogixNG
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
/*public*/ /*interface*/ class LogixNG_Manager :  public Manager/*<LogixNG>*/ {
  Q_INTERFACES(Manager)
public:
    /**
     * Create a new LogixNG if the LogixNG does not exist.
     *
     * @param systemName the system name
     * @param userName   the user name
     * @return a new LogixNG or null if unable to create
     */
    /*public*/ virtual LogixNG* createLogixNG(QString systemName, QString userName)
            throw (IllegalArgumentException) =0;

    /**
     * For use with User GUI, to allow the auto generation of systemNames, where
     * the user can optionally supply a username.
     *
     * @param userName the user name
     * @return a new LogixNG or null if unable to create
     */
    /*public*/ virtual LogixNG* createLogixNG(QString userName)
            throw (IllegalArgumentException) =0;

    /**
     * Locate via user name, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param name User name or system name to match
     * @return null if no match found
     */
    /*public*/ virtual LogixNG* getLogixNG(QString name)=0;

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*LogixNG*/NamedBean* getByUserName(QString name)  override;

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*LogixNG*/NamedBean* getBySystemName(QString name)  override;

    /**
     * Create a new system name for a LogixNG.
     * @return a new system name
     */
    /*public*/ virtual QString getAutoSystemName() const =0;

    /**
     * Setup all LogixNGs. This method is called after a configuration file is
     * loaded.
     */
    /*public*/ virtual void setupAllLogixNGs()=0;

    /**
     * Activate all LogixNGs, starts LogixNG processing by connecting all
     * inputs that are included the ConditionalNGs in this LogixNG.
     * <p>
     * A LogixNG must be activated before it will calculate any of its
     * ConditionalNGs.
     */
    /*public*/ virtual void activateAllLogixNGs()=0;

    /**
     * Activate all LogixNGs, starts LogixNG processing by connecting all
     * inputs that are included the ConditionalNGs in this LogixNG.
     * <p>
     * A LogixNG must be activated before it will calculate any of its
     * ConditionalNGs.
     *
     * @param runDelayed true if execute() should run on LogixNG thread delayed,
     *                   false otherwise.
     * @param runOnSeparateThread true if the activation should run on a
     *                            separate thread, false otherwise
     */
    /*public*/ virtual void activateAllLogixNGs(bool runDelayed, bool runOnSeparateThread)=0;

    /**
     * DeActivate all LogixNGs, stops LogixNG processing by disconnecting all
     * inputs that are included the ConditionalNGs in this LogixNG.
     * <p>
     * A LogixNG must be activated before it will calculate any of its
     * ConditionalNGs.
     */
    /*public*/ virtual void deActivateAllLogixNGs() =0;

    /**
     * Is LogixNGs active?
     * @return true if LogixNGs are active, false otherwise
     */
    /*public*/ virtual bool isActive()=0;

    /**
     * Delete LogixNG by removing it from the manager. The LogixNG must first
     * be deactivated so it stops processing.
     *
     * @param x the LogixNG to delete
     */
    virtual void deleteLogixNG(LogixNG* x)=0;

    /**
     * Support for loading LogixNGs in a disabled state
     *
     * @param s true if LogixNG should be disabled when loaded
     */
    /*public*/ virtual void setLoadDisabled(bool s)=0;

    /**
     * Print the tree to a stream.
     *
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/ virtual /*default*/ void printTree(
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int lineNumber) {

        printTree(new PrintTreeSettings(), writer, indent, lineNumber);
    }
    /**
     * Print the tree to a stream.
     *
     * @param settings settings for what to print
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/ virtual void printTree(
            PrintTreeSettings* settings,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int lineNumber)=0;

    /**
     * Print the tree to a stream.
     *
     * @param locale The locale to be used
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/ virtual /*default*/ void printTree(
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int lineNumber) {

        printTree(new PrintTreeSettings(), locale, writer, indent, lineNumber);
    }

    /**
     * Print the tree to a stream.
     *
     * @param settings settings for what to print
     * @param locale The locale to be used
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/ virtual void printTree(
            PrintTreeSettings* settings,
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int lineNumber)=0;

    /**
     * Test if parameter is a properly formatted system name.
     * <P>
     * This method should only be used by the managers of the LogixNG system.
     *
     * @param subSystemNamePrefix the sub system prefix
     * @param systemName the system name
     * @return enum indicating current validity, which might be just as a prefix
     */
    /*public*/ static NameValidity validSystemNameFormat(QString subSystemNamePrefix, QString systemName) {
        // System names with digits. :AUTO: is generated system names
        if (systemName.contains(QRegExp(subSystemNamePrefix+"(:AUTO:)?\\d+"))) {
            return NameValidity::VALID;

        // System names with dollar sign allow any characters in the name
        } else if (systemName.contains(QRegExp(subSystemNamePrefix+"\\$.+"))) {
            return NameValidity::VALID;

        // System names with :JMRI: belongs to JMRI itself
        } else if (systemName.contains(QRegExp(subSystemNamePrefix+":JMRI:.+"))) {
            return NameValidity::VALID;

        // System names with :JMRI-LIB: belongs to software that uses JMRI as a lib
        } else if (systemName.contains(QRegExp(subSystemNamePrefix+":JMRI-LIB:.+"))) {
            return NameValidity::VALID;

        // Other system names are not valid
        } else {
//            LoggerFactory.getLogger(LogixNG_Manager.class)
//                    .warn("system name {} is invalid for sub system prefix {}",
//                            systemName, subSystemNamePrefix);
            return NameValidity::INVALID;
        }
    }

    /**
     * Get the clipboard
     * @return the clipboard
     */
    /*public*/ virtual Clipboard* getClipboard()=0;

    /**
     * Register a manager for later retrieval by getManager()
     * @param manager the manager
     */
    /*public*/ virtual void registerManager(Manager/*<? extends MaleSocket>*/* manager)=0;

    /**
     * Get manager by class name
     * @param className the class name of the manager
     * @return the manager
     */
    /*public*/ virtual Manager/*<? extends MaleSocket>*/* getManager(QString className)=0;

};
Q_DECLARE_INTERFACE(LogixNG_Manager, "LogixNG_Manager")
#endif // LOGIXNG_MANAGER_H
