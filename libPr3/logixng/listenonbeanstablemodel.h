#ifndef LISTENONBEANSTABLEMODEL_H
#define LISTENONBEANSTABLEMODEL_H

#include <abstracttablemodel.h>
#include "actionlistenonbeans.h"

class ListenOnBeansTableModel : public AbstractTableModel
{
  Q_OBJECT
 public:
  ListenOnBeansTableModel(QList<ActionListenOnBeans::NamedBeanReference *> *namedBeanReference, QObject *parent = nullptr);
  // COLUMN_DUMMY is "hidden" but used when the panel is closed to
  // ensure that the last edited cell is saved.
  enum COLUMNS {
  COLUMN_BEAN_TYPE = 0,
  COLUMN_BEAN_NAME = 1,
  COLUMN_DELETE = 2,
  COLUMN_DUMMY = 3
  };
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  /*public*/  QString getColumnClass(int col) const override;
  /*public*/  void setColumnsForComboBoxes(JTable* table);
  /*public*/  void add();
  /*public*/  QList<ActionListenOnBeans::NamedBeanReference*>* getReferences();

 private:
  /*private*/ /*final*/ QList<ActionListenOnBeans::NamedBeanReference*>* _namedBeanReference = new QList<ActionListenOnBeans::NamedBeanReference*>();
  /*private*/ void _delete(int row);

};

#endif // LISTENONBEANSTABLEMODEL_H
