#ifndef DEFAULTANONYMOUSTABLE_H
#define DEFAULTANONYMOUSTABLE_H

#include "anonymoustable.h"
#include <QVector>

class DefaultAnonymousTable : /*public QObject,*/ public AnonymousTable
{
  Q_OBJECT
 public:
  DefaultAnonymousTable(int numRows, int numColumns, QObject* parent = nullptr);
  /*public*/  DefaultAnonymousTable(/*@Nonnull*/ QVector<QVector<QVariant> > data);
  /*public*/  void storeTableAsCSV(/*@Nonnull*/ File* file)override;
  /*public*/  void storeTableAsCSV(
          /*@Nonnull*/ File* file,
          /*@CheckForNull*/ QString systemName, /*@CheckForNull*/ QString userName)
          /*throws FileNotFoundException*/override;
  /*public*/  QVariant getCell(int row, int column)override;
  /*public*/  void setCell(QVariant value, int row, int column)override;
  /*public*/  int numRows()override;
  /*public*/  int numColumns()override;
  /*public*/  int getRowNumber(QString rowName)override;
  /*public*/  int getColumnNumber(QString columnName)override;
  /*public*/  void insertColumn(int col)override;
  /*public*/  void deleteColumn(int col)override;
  /*public*/  void insertRow(int row)override;
  /*public*/  void deleteRow(int row)override;

 private:
  /*private*/ /*final*/ int _numRows;
  /*private*/ /*final*/ int _numColumns;
  /*private*/ /*final*/ QVector<QVector<QVariant> > _data;
  /*private*/ /*final*/ QMap<QString,int> rowNames = QMap<QString,int>();
  /*private*/ /*final*/ QMap<QString,int> columnNames = QMap<QString,int>();
  /*private*/ void setupTable();

};

#endif // DEFAULTANONYMOUSTABLE_H
