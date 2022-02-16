#ifndef NAMEDTABLEMANAGER_H
#define NAMEDTABLEMANAGER_H
#include <QLocale>
#include "printwriter.h"
#include "anonymoustable.h"
#include "../../appslib/manager.h"
#include "namedtable.h"

/**
 * A manager for a NamedTable
 *
 * @author Dave Duchamp       Copyright (C) 2007
 * @author Daniel Bergqvist   Copyright (C) 2018
 */
/*public*/ /*interface*/class  NamedTableManager : public Manager/*<NamedTable>*/ {

  Q_INTERFACES(Manager)
 public:
    /**
     * Create a new anonymous table.
     * This table is not stored in the manager.
     * @param numRows number of rows in the table
     * @param numColumns number of columns in the table
     * @return the new table
     */
    /*public*/virtual AnonymousTable* newAnonymousTable(int numRows, int numColumns)=0;

    /**
     * Create a new CSV table.
     * This table is stored in the manager but it's contents does only exists
     * in the CSV file. If the CSV file is changed, the contents will be read
     * on the next start of the program.
     * @param systemName the system name of the table
     * @param userName the user name of the table, or null if no user name
     * @param fileName the file name of the CSV file
     * @return the new table
     */
    /*public*/virtual NamedTable* newCSVTable(QString systemName, QString userName, QString fileName)=0;

    /**
     * Create a new internal named table.
     * This table is stored in the manager together with its contents. Note
     * that a big table will take a lot of space in the panel file since the
     * storage of table data has a lot of overhead. For larger tables, a CSV
     * table is recommended.
     * @param systemName the system name of the table
     * @param userName the user name of the table, or null if no user name
     * @param numRows number of rows in the table
     * @param numColumns number of columns in the table
     * @return the new table
     */
    /*public*/ virtual NamedTable* newInternalTable(QString systemName, QString userName, int numRows, int numColumns)=0;

    /**
     * Load a table from a CSV text.
     * @param sys the system name of the new table
     * @param user the user name of the new table or null if no user name
     * @param text the CSV text
     * @return the loaded table
     */
    /*public*/ virtual NamedTable* loadTableFromCSVData(
            /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, /*@Nonnull*/ QString text)
            /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException*/=0;

    /**
     * Load a table from a CSV finle.
     * @param sys the system name of the new table
     * @param user the user name of the new table or null if no user name
     * @param fileName the file name of the CSV table
     * @return the loaded table
     * @throws java.io.IOException in case of an exception
     */
    /*public*/ virtual NamedTable* loadTableFromCSV(
            /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
            /*@Nonnull*/ QString fileName)
            /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/=0;

    /**
     * Load a table from a CSV finle.
     * @param file the CSV file
     * @param sys the system name of the new table
     * @param user the user name of the new table or null if no user name
     * @return the loaded table
     * @throws java.io.IOException in case of an exception
     */
    /*public*/ virtual NamedTable* loadTableFromCSV(
            /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
            /*@Nonnull*/ File* file)
            /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/=0;

    /**
     * Locate via user name, then system name if needed. Does not create a new
     * one if nothing found
     *
     * @param name User name or system name to match
     * @return null if no match found
     */
    /*public*/ virtual NamedTable* getNamedTable(QString name)=0;

    /** {@inheritDoc} */
    //@Override
    /*public*/ NamedBean* getByUserName(QString name)override; // NamedTable

    /** {@inheritDoc} */
    //@Override
    /*public*/ NamedBean* getBySystemName(QString name);// NamedTable

    /**
     * Create a new system name for a LogixNG.
     * @return a new system name
     */
    /*public*/ virtual QString getAutoSystemName()=0;

    /**
     * {@inheritDoc}
     *
     * The sub system prefix for the NamedTableManager is
     * {@link #getSystemNamePrefix() } and "T";
     */
    //@Override
    /*public*/ /*default*/ QString getSubSystemNamePrefix()const override{
        return getSystemNamePrefix() + "T";
    }

    /**
     * Delete NamedTable by removing it from the manager.
     *
     * @param x the NamedTable to delete
     */
    virtual void deleteNamedTable(NamedTable* x)=0;

    /**
     * Print the tree to a stream.
     *
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     */
    /*public*/ virtual void printTree(PrintWriter* writer, QString indent)=0;

    /**
     * Print the tree to a stream.
     *
     * @param locale The locale to be used
     * @param writer the stream to print the tree to
     * @param indent the indentation of each level
     */
    /*public*/ virtual void printTree(QLocale locale, PrintWriter* writer, QString indent)=0;

};
Q_DECLARE_INTERFACE(NamedTableManager, "NamedTableManager")
#endif // NAMEDTABLEMANAGER_H
