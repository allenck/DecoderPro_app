#ifndef EXPRESSIONS_LOGDATATABLEMODEL_H
#define EXPRESSIONS_LOGDATATABLEMODEL_H

#include <abstracttablemodel.h>
#include "ex_logdata.h"

namespace Expressions {

 class LogDataTableModel : public AbstractTableModel
 {
   Q_OBJECT
  public:
   Q_INVOKABLE LogDataTableModel(QList<LogData::Data> *namedBeanReference, QObject* parent = nullptr);
   // COLUMN_DUMMY is "hidden" but used when the panel is closed to
   // ensure that the last edited cell is saved.
   enum COLUMNS {
   COLUMN_TYPE = 0,
   COLUMN_DATA = 1,
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
   /*private*/ void _delete(int row);
   /*public*/  QList<LogData::Data> getDataList();

  private:
   /*private*/ /*final*/ QList<LogData::Data> _dataList = QList<LogData::Data>();

 };
}
//Q_DECLARE_METATYPE(Actions::LogDataTableModel)
#endif // EXPRESSIONS_LOGDATATABLEMODEL_H
