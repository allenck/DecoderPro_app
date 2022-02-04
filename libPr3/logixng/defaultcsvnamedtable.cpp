#include "defaultcsvnamedtable.h"

/**
 * The default implementation of a NamedTable
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultCsvNamedTable extends AbstractNamedTable {


    /**
     * Create a new named table.
     * @param sys the system name
     * @param user the user name or null if no user name
     * @param fileName the file name of the CSV table
     * @param data the data in the table. Note that this data is not copied to
     * an new array but used by the table as is.
     */
    /*public*/  DefaultCsvNamedTable::DefaultCsvNamedTable::DefaultCsvNamedTable(
            /*@Nonnull*/  QString sys, /*@CheckForNull*/ QString user,
            /*@CheckForNull*/ QString fileName,
            /*@Nonnull*/  QVector<QVector<QVariant> > data,
            QObject* parent) : AbstractNamedTable(sys, user, data, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys,user,data);

        _fileName = fileName;
    }

    /*public*/  QString DefaultCsvNamedTable::getFileName() {
        return _fileName;
    }

    /*public*/  void DefaultCsvNamedTable::setFileName(QString fileName) {
        this->_fileName = fileName;
    }
