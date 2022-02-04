#ifndef LOCALVARIABLETABLEMODEL_H
#define LOCALVARIABLETABLEMODEL_H

#include <abstracttablemodel.h>
#include "symboltable.h"
#include"malesocket.h"
#include "actionevent.h"

class LocalVariableTableModel : public AbstractTableModel
{
  Q_OBJECT
 public:
  explicit LocalVariableTableModel(MaleSocket* maleSocket, QObject *parent = nullptr);
  /*public*/  static /*final*/const int COLUMN_NAME = 0;
  /*public*/  static /*final*/const int COLUMN_TYPE = 1;
  /*public*/  static /*final*/const int COLUMN_DATA = 2;
  /*public*/  static /*final*/const int COLUMN_MENU = 3;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  /*public*/  QString getColumnClass(int col) const;
  /*public*/  void setColumnForMenu(JTable* table);
  /*public*/  void add();
  /*public*/  QList<VariableData*> getVariables();
  /*public*/  void actionPerformed(JActionEvent* event =0);

 private:
  /*private*/ /*final*/ QList<VariableData*> _variables = QList<VariableData*>();

};
#endif // LOCALVARIABLETABLEMODEL_H
