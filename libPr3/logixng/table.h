#ifndef TABLE_H
#define TABLE_H
#include <QVariant>
#include "exceptions.h"
#include "file.h"

/**
 * Represent a Table.
 * A table is a two dimensional array where the rows and columns may have names.
 *
 * @author Daniel Bergqvist Copyright (C) 2019
 */
/*public*/ /*interface*/class  Table {

 public:
    /**
     * Get the value of a cell.
     * If the table has both rows and columns, the value of the first column
     * will be returned.
     * @param row the row of the cell or null if all rows should be returned
     * @return the value of the cell
     */
    //@CheckReturnValue
    /*default*/ /*public*/ virtual QVariant getCell(int row) {
        return getCell(row, 1);
    }
    
    /**
     * Get the value of a cell.
     * @param row the row of the cell
     * @param column the column of the cell
     * @return the value of the cell
     */
    //@CheckReturnValue
    /*public*/ virtual QVariant getCell(int row, int column)=0;
    
    /**
     * Get the value of a cell.
     * If the table has both rows and columns, the value of the first column
     * will be returned.
     * @param row the row of the cell or null if all rows should be returned
     * @return the value of the cell
     * @throws RowNotFoundException if the row is not found
     */
    //@CheckReturnValue
    /*default*/ /*public*/ virtual QVariant getCell(/*@Nonnull*/ QString row)
            /*throws RowNotFoundException*/ {
        return getCell(getRowNumber(row), 1);
    }
    
    /**
     * Get the value of a cell.
     * @param row the row of the cell. If this string is a name of a row, that
     * row is used. If it's not a name of a row, but an integer value, that
     * index is used, where row 0 is the name of the row.
     * @param column the column of the cell. If this string is a name of a
     * column, that column is used. If it's not a name of a column, but an
     * integer value, that index is used, where column 0 is the name of the
     * column.
     * @return the value of the cell
     * @throws RowNotFoundException if the row is not found
     * @throws ColumnNotFoundException if the column is not found
     */
    /*default*/ /*public*/ virtual QVariant getCell(/*@Nonnull*/ QString row, /*@Nonnull*/ QString column)
            /*throws RowNotFoundException, ColumnNotFoundException*/ {
        return getCell(getRowNumber(row), getColumnNumber(column));
    }
    
    /**
     * Get the value of a cell.
     * @param value the new value of the cell
     * @param row the row of the cell
     * @param column the column of the cell
     */
    //@CheckReturnValue
    /*public*/ virtual void setCell(QVariant value, int row, int column);
    
    /**
     * Set the value of a cell.
     * If the table has both rows and columns, the value of the first column
     * will be returned.
     * @param value the new value of the cell
     * @param row the row of the cell
     * @throws RowNotFoundException if the row is not found
     */
    /*default*/ /*public*/ virtual void setCell(QVariant value, QString row)
            /*throws RowNotFoundException*/ {
        setCell(value, getRowNumber(row), 1);
    }
    
    /**
     * Set the value of a cell.
     * @param value the new value of the cell
     * @param row the row of the cell. If this string is a name of a row, that
     * row is used. If it's not a name of a row, but an integer value, that
     * index is used, where row 0 is the name of the row.
     * @param column the column of the cell. If this string is a name of a
     * column, that column is used. If it's not a name of a column, but an
     * integer value, that index is used, where column 0 is the name of the column.
     * @throws RowNotFoundException if the row is not found
     * @throws ColumnNotFoundException if the column is not found
     */
    /*default*/ /*public*/ virtual void setCell(QVariant value, QString row, QString column)
            /*throws RowNotFoundException, ColumnNotFoundException*/ {
        setCell(value, getRowNumber(row), getColumnNumber(column));
    }
    
    /**
     * Get the number of rows in the table.
     * @return the number of rows
     */
    /*public*/ virtual int numRows()=0;
    
    /**
     * Get the number of columns in the table.
     * @return the number of columns
     */
    /*public*/ virtual int numColumns()=0;

    /**
     * Get the row number by name of row.
     * @param rowName the name of the row. If there is no row with this name,
     * and rowName is a positive integer, that row number will be returned.
     * @return the row number
     * @throws RowNotFoundException if the row is not found
     */
    /*public*/ virtual int getRowNumber(QString rowName) /*throws RowNotFoundException*/=0;
    
    /**
     * Get the row number by name of row.
     * @param columnName the name of the column. If there is no column with
     * this name, and columnName is a positive integer, that column number will
     * be returned.
     * @return the column number
     * @throws ColumnNotFoundException if the column is not found
     */
    /*public*/ virtual int getColumnNumber(QString columnName) /*throws ColumnNotFoundException*/=0;
    
    /**
     * Store the table to a CSV file.
     * @param file the CSV file
     * @throws java.io.FileNotFoundException if file not found
     */
    /*public*/ virtual void storeTableAsCSV(/*@Nonnull*/ File* file)
            /*throws FileNotFoundException*/=0;

    /**
     * Store the table to a CSV file.
     * If system name and/or user name is not null, these values are used
     * instead of the tables own system name and user name. If no system name
     * and user name is given and the table is anonymous, no system name and
     * user name is stored in the file.
     * @param file the CSV file
     * @param systemName the system name of the table
     * @param userName the user name of the table
     * @throws java.io.FileNotFoundException if file not found
     */
    /*public*/ virtual void storeTableAsCSV(
            /*@Nonnull*/ File* file,
            /*@CheckForNull*/ QString systemName, /*@CheckForNull*/ QString userName)
            /*throws FileNotFoundException*/=0;




    /*public*/ /*static*/ class RowNotFoundException : public IllegalArgumentException {
      public:
        /**
         * Constructs a <code>RowNotFoundException</code>.
         *
         * @param  name the name of the row.
         */
        /*public*/ RowNotFoundException(QString name) {
            IllegalArgumentException(QString("Row \"%1\" is not found").arg(name));
        }

        /**
         * Constructs a <code>RowNotFoundException</code>.
         *
         * <p>Note that the detail message associated with <code>cause</code> is
         * <i>not</i> automatically incorporated in this exception's detail
         * message.
         *
         * @param  name the name of the row.
         * @param  cause the cause (which is saved for later retrieval by the
         *         {@link Throwable#getCause()} method).  (A {@code null} value
         *         is permitted, and indicates that the cause is nonexistent or
         *         unknown.)
         */
        /*public*/ RowNotFoundException(QString name, Throwable* cause) {
            IllegalArgumentException(QString("Row \"%1\" is not found").arg(name), cause);
        }

    };


    /*public*/ /*static*/ class ColumnNotFoundException : public IllegalArgumentException {

        /**
         * Constructs a <code>ColumnNotFoundException</code>.
         *
         * @param  name the name of the row.
         */
        /*public*/ ColumnNotFoundException(QString name) {
            IllegalArgumentException(QString("Column \"%1\" is not found").arg(name));
        }

        /**
         * Constructs a <code>ColumnNotFoundException</code>.
         *
         * <p>Note that the detail message associated with <code>cause</code> is
         * <i>not</i> automatically incorporated in this exception's detail
         * message.
         *
         * @param  name the name of the row.
         * @param  cause the cause (which is saved for later retrieval by the
         *         {@link Throwable#getCause()} method).  (A {@code null} value
         *         is permitted, and indicates that the cause is nonexistent or
         *         unknown.)
         */
        /*public*/ ColumnNotFoundException(QString name, Throwable* cause) {
            IllegalArgumentException(QString("Column \"%1\" is not found").arg(name), cause);
        }

    };

};
Q_DECLARE_INTERFACE(Table, "Table")
#endif // TABLE_H
