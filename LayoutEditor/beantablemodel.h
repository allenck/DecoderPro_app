#ifndef BEANTABLEMODEL_H
#define BEANTABLEMODEL_H
#include "abstracttablemodel.h"

class Logger;
class Manager;
class BeanTableModel : public AbstractTableModel
{
 Q_OBJECT
public:
 enum COLUMNS
 {
  SNAME_COLUMN = 0,
  UNAME_COLUMN = 1,
  INCLUDE_COLUMN = 2
 };
 Q_ENUM(COLUMNS)
 explicit BeanTableModel(QObject *parent = 0);
 /*public*/ QString getColumnClass(int c);
 /*public*/ virtual /*abstract*/ Manager* getManager() const;

 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;

signals:

public slots:
private:
 Logger* log;

};

#endif // BEANTABLEMODEL_H
