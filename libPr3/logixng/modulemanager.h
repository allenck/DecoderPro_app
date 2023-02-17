#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H
#include "../../appslib/manager.h"
#include "module.h"
#include "printwriter.h"

class PrintTreeSettings;
class MutableInt;

/**
 * Manager for LogixNG modules
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2020
 */
/*public*/ /*interface*/class ModuleManager : public virtual Manager/*<Module>*/ {
 Q_INTERFACES(Manager)
 public:
    /**
     * Create a new Module if the Module does not exist.
     *
     * @param systemName the system name
     * @param userName   the user name
     * @param socketType the socket type
     * @return a new Module or null if unable to create
     */
    /*public*/ virtual Module* createModule(QString systemName, QString userName,
            FemaleSocketManager::SocketType* socketType)
            /*throw (IllegalArgumentException)*/=0;

    /**
     * For use with User GUI, to allow the auto generation of systemNames, where
     * the user can optionally supply a username.
     *
     * @param userName the user name
     * @param socketType the socket type
     * @return a new Module or null if unable to create
     */
    /*public*/ virtual /*Module*/NamedBean* createModule(QString userName, FemaleSocketManager::SocketType* socketType)
            /*throw (IllegalArgumentException)*/=0;

    /**
     * Locate via user name, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param name User name or system name to match
     * @return null if no match found
     */
    /*public*/ virtual Module* getModule(QString name)=0;

    /** {@inheritDoc} */
    //@Override
    /*public*/ virtual Module* getByUserName(QString name) const override=0;

    /** {@inheritDoc} */
    //@Override
    /*public*/ Module* getBySystemName(QString name) const override =0;

    /**
     * Create a new system name for a Module.
     * @return a new system name
     */
  /*public*/ virtual QString getAutoSystemName() {return "";}

    /**
     * Resolve all the Module trees.
     * <P>
     * This method ensures that everything in the Module tree has a pointer
     * to its parent.
     *
     * @param errors a list of potential errors
     * @return true if success, false otherwise
     */
    /*public*/ virtual bool resolveAllTrees(QList<QString>* errors) =0;

    /**
     * Setup all Modules. This method is called after a configuration file is
     * loaded.
     */
    /*public*/ virtual void setupAllModules()=0;

    /*.*
     * Activate all Modules, starts Module processing by connecting all
     * inputs that are included the ConditionalNGs in this Module.
     * <p>
     * A Module must be activated before it will calculate any of its
     * ConditionalNGs.
     *./
    public void activateAllModules();
*/
    /**
     * Delete Module by removing it from the manager. The Module must first
     * be deactivated so it stops processing.
     *
     * @param x the Module to delete
     */
    virtual void deleteModule(Module* x)=0;

    /*.*
     * Support for loading Modules in a disabled state
     *
     * @param s true if Module should be disabled when loaded
     *./
    public void setLoadDisabled(boolean s);
*/
    /**
     * Print the tree to a stream.
     *
     * @param settings settings for what to print
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     * @param lineNumber the line number
     */
    /*public*/ virtual void printTree(
            Base::PrintTreeSettings* settings,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int* lineNumber)=0;

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
            Base::PrintTreeSettings* settings,
            QLocale locale,
            PrintWriter* writer,
            QString indent,
            /*MutableInt*/int* lineNumber)=0;

    /**
     * Test if parameter is a properly formatted system name.
     * <P>
     * This method should only be used by the managers of the Module system.
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
//            LoggerFactory.getLogger(Module_Manager.class)
//                    .warn("system name {} is invalid for sub system prefix {}",
//                            systemName, subSystemNamePrefix);
            return NameValidity::INVALID;
        }
    }

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the DigitalActionManager is
     * {@link #getSystemNamePrefix() } and "DA";
     */
    //@Override
    /*public*/ /*default*/ QString getSubSystemNamePrefix() const override{
        return getSystemNamePrefix() + "M";
    }

};
Q_DECLARE_INTERFACE(ModuleManager, "ModuleManager")
#endif // MODULEMANAGER_H
