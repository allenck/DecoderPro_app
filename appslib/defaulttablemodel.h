#ifndef DEFAULTTABLEMODEL_H
#define DEFAULTTABLEMODEL_H

#include "abstracttablemodel.h"
#include <QVector>

class DefaultTableModel : public AbstractTableModel
{
 Q_OBJECT
public:
 explicit DefaultTableModel(QObject *parent = 0);
 /*public*/ DefaultTableModel(int rowCount, int columnCount, QObject *parent = 0);
 /*public*/ DefaultTableModel(QVector<QVariant>* columnNames, int rowCount, QObject *parent = 0);
 /*public*/ QVector<QVariant>* getDataVector();
 /*public*/ void setDataVector(QVector<QVariant>* dataVector, QVector<QVariant>* columnIdentifiers);
 /*public*/ int getRowCount();
 /*public*/ int getColumnCount() const;
 int rowCount(const QModelIndex &parent) const;
 int columnCount(const QModelIndex &parent) const;
 QVariant data(const QModelIndex &index, int role) const;
 bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ void addColumn(QVariant columnName);
 /*public*/ void setRowCount(int rowCount);
 /*public*/ void setValueAt(QVariant aValue, int rowIndex, int columnIndex);
 /*public*/ QVariant getValueAt(int row, int column);

signals:

public slots:
private:
 /*private*/ static QVector<QVariant>* newVector(int size);
 /*private*/ static QVector<QVariant>* nonNullVector(QVector<QVariant>* v);
 /*private*/ void justifyRows(int from, int to);

 int _rowCount = 0;

protected:

 /**
  * The <code>Vector</code> of <code>Vectors</code> of
  * <code>Object</code> values.
  */
 /*protected*/ QVector<QVariant>*   dataVector;

 /** The <code>Vector</code> of column identifiers. */
 /*protected*/QVector<QVariant>*    columnIdentifiers;

};

#endif // DEFAULTTABLEMODEL_H
