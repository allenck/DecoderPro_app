#include "defaultinternalnamedtable.h"

/**
 * The default implementation of a NamedTable
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultInternalNamedTable extends AbstractNamedTable {

    /**
     * Create a new named table.
     * @param sys the system name
     * @param user the user name or null if no user name
     * @param numRows the number or rows in the table
     * @param numColumns the number of columns in the table
     */
    /*public*/  DefaultInternalNamedTable::DefaultInternalNamedTable(
            /*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
            int numRows, int numColumns, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractNamedTable(sys,user,numRows,numColumns, parent){
        //super(sys,user,numRows,numColumns);
    }

    /**
     * Create a new named table with an existing array of cells.
     * Row 0 has the column names and column 0 has the row names.
     * @param systemName the system name
     * @param userName the user name
     * @param data the data in the table. Note that this data is not copied to
     * an new array but used by the table as is.
     */
    /*public*/  DefaultInternalNamedTable::DefaultInternalNamedTable(
            /*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName,
            /*@Nonnull*/ QVector<QVector<QVariant> > data, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractNamedTable(systemName,userName,data, parent){
        //super(systemName,userName,data);
    }

