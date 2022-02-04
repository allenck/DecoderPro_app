#include "abstractnamedtable.h"
#include "defaultanonymoustable.h"
#include "namedtablemanager.h"
#include "instancemanager.h"
#include "defaultcsvnamedtable.h"

/**
 * The default implementation of a NamedTable
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  abstract class AbstractNamedTable extends AbstractNamedBean implements NamedTable {


    /**
     * Create a new named table.
     * @param sys the system name
     * @param user the user name or null if no user name
     * @param numRows the number or rows in the table
     * @param numColumns the number of columns in the table
     */
    /*public*/  AbstractNamedTable::AbstractNamedTable(
            /*@Nonnull*/  QString sys, /*@CheckForNull*/ QString user,
            int numRows, int numColumns, QObject* parent) : NamedTable(sys, user,  parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys,user);
        _internalTable = new DefaultAnonymousTable(numRows, numColumns);
    }

    /**
     * Create a new named table with an existing array of cells.
     * Row 0 has the column names and column 0 has the row names.
     * @param systemName the system name
     * @param userName the user name
     * @param data the data in the table. Note that this data is not copied to
     * an new array but used by the table as is.
     */
    /*public*/  AbstractNamedTable::AbstractNamedTable(
            /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
            /*@Nonnull*/  QVector<QVector<QVariant> > data, QObject* parent) : NamedTable(systemName, userName,  parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(systemName,userName);

        // Do this test here to ensure all the tests are using correct system names
        Manager::NameValidity isNameValid = ((NamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->validSystemNameFormat(systemName);
        if (isNameValid != Manager::NameValidity::VALID) {
            throw new IllegalArgumentException("system name is not valid");
        }
        _internalTable = new DefaultAnonymousTable(data);
    }

    /**
     * Create a new named table with an existing array of cells.
     * Row 0 has the column names and column 0 has the row names.
     * @param systemName the system name
     * @param userName the user name
     * @param fileName the file name of the CSV table
     * @param data the data in the table. Note that this data is not copied to
     * an new array but used by the table as is.
     */
    /*public*/  AbstractNamedTable::AbstractNamedTable(
            /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
            /*@Nonnull*/  QString fileName,
            /*@Nonnull*/  QVector<QVector<QVariant> > data, QObject *parent) : NamedTable(systemName,userName, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(systemName,userName);

        // Do this test here to ensure all the tests are using correct system names
        Manager::NameValidity isNameValid = ((NamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->validSystemNameFormat(mSystemName);
        if (isNameValid != Manager::NameValidity::VALID) {
            throw new IllegalArgumentException("system name is not valid");
        }
        _internalTable = new DefaultAnonymousTable(data);
    }

    /*@Nonnull*/
    /*private*/ /*static*/ NamedTable* AbstractNamedTable::loadFromCSV(
            /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
            /*@CheckForNull*/ QString fileName,
            /*@Nonnull*/  QList<QString> lines,
            bool registerInManager)
            /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException*/ {

        NamedTableManager* manager = (NamedTableManager*)InstanceManager::getDefault("NamedTableManager");

        if (/*userName != null &&*/ userName.isEmpty()) userName = "";

        // First row is column names.
        int numRows = lines.size()-1;

        // If the last row is empty string, ignore it.
        if (lines.at(lines.size()-1).isEmpty()) numRows--;

        int numColumns = 0;

        QVector<QVector<QString> >csvCells =  QVector<QVector<QString> >(numRows+1);//QString[numRows+1][];
        QVector<QVector<QVariant> >csvCellsV =  QVector<QVector<QVariant> >(numRows+1);//QString[numRows+1][];
        for (int rowCount = 0; rowCount < numRows+1; rowCount++) {
            QVector<QString> columns = lines.at(rowCount).split("\t").toVector();
            if (numColumns < columns.length()) numColumns = columns.length();
            csvCells[rowCount] = columns;
        }

        // Ensure all rows have same number of columns
        for (int rowCount = 0; rowCount < numRows+1; rowCount++) {
            QVector<QString> cells = csvCells.at(rowCount);
            if (cells.length() < numColumns) {
                QVector<QString> newCells = QVector<QString>(numColumns);
                QVector<QVariant> newCellsV = QVector<QVariant>(numColumns);
                //System.arraycopy(cells, 0, newCells, 0, cells.length());
                for(int i=0; i < cells.length(); i++)
                {
                 newCells.replace(i, cells.at(i));
                 newCellsV.replace(i, cells.at(i));
                }
                csvCells[rowCount] = newCells;
                csvCellsV[rowCount] = newCellsV;
                for (int i=cells.length(); i < numColumns; i++) newCells[i] = "";
                csvCells[rowCount] = newCells;
                csvCellsV[rowCount] = newCellsV;
            }
        }

        NamedTable* table = new DefaultCsvNamedTable(systemName, userName, fileName, csvCellsV);

        if (registerInManager) manager->Register((NamedBean*)table);

        return table;
    }

    /*@Nonnull*/
    /*public*/  /*static*/ NamedTable* AbstractNamedTable::loadTableFromCSV_Text(
            /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
            /*@Nonnull*/  QString text,
            bool registerInManager)
            /*throws BadUserNameException, BadSystemNameException*/ {

        QList<QString> lines = (text.split("\\r?\\n"/*,-1*/));
        return loadFromCSV(systemName, userName, "", lines, registerInManager);
    }

    /*@Nonnull*/
    /*public*/  /*static*/ NamedTable* AbstractNamedTable::loadTableFromCSV_File(
            /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
            /*@Nonnull*/  QString fileName, bool registerInManager)
            /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/ {
#if 0 // TODO define class "Files"
        QList<QString> lines = Files::readAllLines(FileUtil::getFile(fileName).toPath(), StandardCharsets.UTF_8);
        return loadFromCSV(systemName, userName, fileName, lines, registerInManager);
#endif
    }

    /*@Nonnull*/
    /*public*/  /*static*/ NamedTable* AbstractNamedTable::loadTableFromCSV_File(
            /*@Nonnull*/  QString systemName, /*@CheckForNull*/ QString userName,
            /*@Nonnull*/  File* file, bool registerInManager)
            /*throws NamedBean.BadUserNameException, NamedBean.BadSystemNameException, IOException*/ {
#if 0 // TODO define class "Files"

        QList<QString> lines = Files::readAllLines(file.toPath(), StandardCharsets.UTF_8);
        return loadFromCSV(systemName, userName, file.getPath(), lines, registerInManager);
#endif
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  void AbstractNamedTable::storeTableAsCSV(/*@Nonnull*/  File* file)
            /*throws FileNotFoundException */{
        _internalTable->storeTableAsCSV(file, getSystemName(), getUserName());
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  void AbstractNamedTable::storeTableAsCSV(
            /*@Nonnull*/  File* file,
            /*@CheckForNull*/ QString systemName, /*@CheckForNull*/ QString userName)
            /*throws FileNotFoundException*/ {

        _internalTable->storeTableAsCSV(file, systemName, userName);
    }

    //@Override
    /*public*/  void AbstractNamedTable::setState(int s) /*throws JmriException*/ {
        _state = s;
    }

    //@Override
    /*public*/  int AbstractNamedTable::getState() {
        return _state;
    }

    //@Override
    /*public*/  QString AbstractNamedTable::getBeanType() {
        return tr("NameTable");
//        return Manager.LOGIXNGS;
//        return NamedTable.class;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  QVariant AbstractNamedTable::getCell(int row, int column) {
        return _internalTable->getCell(row, column);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  void AbstractNamedTable::setCell(QVariant value, int row, int column) {
        _internalTable->setCell(value, row, column);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  int AbstractNamedTable::numRows() {
        return _internalTable->numRows();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  int AbstractNamedTable::numColumns() {
        return _internalTable->numColumns();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  int AbstractNamedTable::getRowNumber(QString rowName) {
        return _internalTable->getRowNumber(rowName);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  int AbstractNamedTable::getColumnNumber(QString columnName) {
        return _internalTable->getColumnNumber(columnName);
    }
/*
    protected void insertColumn(int col) {
        _internalTable.insertColumn(col);
    }

    protected void deleteColumn(int col) {
        _internalTable.deleteColumn(col);
    }

    protected void insertRow(int row) {
        _internalTable.insertRow(row);
    }

    protected void deleteRow(int row) {
        _internalTable.deleteRow(row);
    }
*/
