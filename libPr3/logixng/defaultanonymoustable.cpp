#include "defaultanonymoustable.h"
#include "file.h"
#include "printwriter.h"
#include "bufferedwriter.h"
/**
 * Default implementation for anonymous tables
 */
///*public*/  class DefaultAnonymousTable implements AnonymousTable {


    /*public*/  DefaultAnonymousTable::DefaultAnonymousTable(int numRows, int numColumns, QObject* parent) : AnonymousTable(parent){
        _numRows = numRows;
        _numColumns = numColumns;
        _data =  QVector<QVector<QVariant> >();// new Object[numRows+1][numColumns+1];
        setupTable();
    }

    /**
     * Create a new anonymous table with an existing array of cells.
     * Row 0 has the column names and column 0 has the row names.
     * @param data the data in the table. Note that this data is not copied to
     * an new array but used by the table as is.
     */
    /*public*/  DefaultAnonymousTable::DefaultAnonymousTable(/*@Nonnull*/ QVector<QVector<QVariant> > data) {
        // Row 0 has column names
        _numRows = data.length()-1;
        // Column 0 has row names
        _numColumns = data[0].length()-1;
        _data = data;

        for (int row=0; row < _data.length(); row++) {
            if (_numColumns+1 != _data[row].length()) {
                throw new IllegalArgumentException("All rows in table must have same number of columns");
            }
        }

        setupTable();
/*
        int i[][] = new int[15][];
        i[5] = new int[3];
        i[7] = new int[10];
        i[5][2] = 3;
//        i[5][8] = 4;
        i[7][2] = 5;
        i[7][8] = 6;
//        i[2][2] = 7;
//        i[2][8] = 8;

        i = new int[15][20];
//        i[5] = new int[3];
        i[7] = new int[10];
        i[5][2] = 3;
        i[5][8] = 4;
        i[7][2] = 5;
        i[7][8] = 6;
        i[2][2] = 7;
        i[2][8] = 8;
*/
    }

    /*private*/ void DefaultAnonymousTable::setupTable() {
        for (int i=0; i <= _numRows; i++) {
            QVariant cell = _data[i][0];
            if (cell != QVariant() && cell.canConvert<QString>()) {
                rowNames.insert(cell.toString(), i);
            }
        }

        for (int i=0; i <= _numColumns; i++) {
            QVariant cell = _data[0][i];
            if (cell != QVariant() && cell.canConvert<QString>()) {
                columnNames.insert(cell.toString(), i);
            }
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  void DefaultAnonymousTable::storeTableAsCSV(/*@Nonnull*/ File* file)
            /*throws FileNotFoundException*/ {
        storeTableAsCSV(file, "", "");
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  void DefaultAnonymousTable::storeTableAsCSV(
            /*@Nonnull*/ File* file,
            /*@CheckForNull*/ QString systemName, /*@CheckForNull*/ QString userName)
            /*throws FileNotFoundException*/ {
        #if 0 // TODO
        try (PrintWriter* writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file), StandardCharsets.UTF_8)))) {
            writer->format("%s\t%s%n", systemName, userName);
            for (int row=0; row <= _numRows; row++) {
                for (int column=0; column <= _numColumns; column++) {
                    if (column > 0) writer.print("\t");
//                    System.out.format("%d, %d: %s%n", row, column, _data[row][column].toString());
                    if (_data[row][column] != null) writer.print(_data[row][column].toString());
                }
                writer.println();
            }
        }
#endif
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  QVariant DefaultAnonymousTable::getCell(int row, int column) {
        return _data[row][column];
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  void DefaultAnonymousTable::setCell(QVariant value, int row, int column) {
        _data[row][column] = value;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  int DefaultAnonymousTable::numRows() {
        return _numRows;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  int DefaultAnonymousTable::numColumns() {
        return _numColumns;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  int DefaultAnonymousTable::getRowNumber(QString rowName) {
        int rowNumber = rowNames.value(rowName);
        if (rowNumber == 0) {
            try {
          bool ok;
                int row = (rowName.toInt(&ok)); if(!ok) throw new NumberFormatException();
                if (row >= 0 && row <= _numRows) return row;
            } catch (NumberFormatException e) {
                // Do nothing
            }
        } else {
            return rowNumber;
        }
        // If here, the row is not found
        throw new RowNotFoundException(rowName);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  int DefaultAnonymousTable::getColumnNumber(QString columnName) {
        int columnNumber = columnNames.value(columnName);
        if (columnNumber == 0) {
            try {
          bool ok;
                int column = (columnName).toInt(&ok); if(!ok) throw new NumberFormatException();
                if (column >= 0 && column <= _numColumns) return column;
            } catch (NumberFormatException e) {
                // Do nothing
            }
        } else {
            return columnNumber;
        }
        // If here, the column is not found
        throw new ColumnNotFoundException(columnName);
    }

    //@Override
    /*public*/  void DefaultAnonymousTable::insertColumn(int col) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void DefaultAnonymousTable::deleteColumn(int col) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void DefaultAnonymousTable::insertRow(int row) {
        throw new UnsupportedOperationException("Not supported");
    }

    //@Override
    /*public*/  void DefaultAnonymousTable::deleteRow(int row) {
        throw new UnsupportedOperationException("Not supported");
    }
