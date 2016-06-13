#ifndef DEFAULTTABLEMODEL_H
#define DEFAULTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

class DefaultTableModel : public QAbstractTableModel
{
 Q_OBJECT
public:
 explicit DefaultTableModel(QObject *parent = 0);
 /*public*/ DefaultTableModel(int rowCount, int columnCount, QObject *parent = 0);
 /*public*/ DefaultTableModel(QVector<QObject*> columnNames, int rowCount, QObject *parent = 0);
 /*public*/ QVector<QObject*> getDataVector();
 /*public*/ void setDataVector(QVector<QObject*> dataVector, QVector<QObject*> columnIdentifiers);
 /*public*/ int getRowCount();
 /*public*/ int getColumnCount();
 int rowCount(const QModelIndex &parent) const;
 int columnCount(const QModelIndex &parent) const;
 QVariant data(const QModelIndex &index, int role) const;
signals:

public slots:
private:
 /*private*/ static QVector<QObject*> newVector(int size);
 /*private*/ static QVector<QObject*> nonNullVector(QVector<QObject*> v);
 /*private*/ void justifyRows(int from, int to);

protected:

 /**
  * The <code>Vector</code> of <code>Vectors</code> of
  * <code>Object</code> values.
  */
 /*protected*/ QVector<QObject*>    dataVector;

 /** The <code>Vector</code> of column identifiers. */
 /*protected*/QVector<QObject*>    columnIdentifiers;

};

#endif // DEFAULTTABLEMODEL_H
