#ifndef DEBUGGERSYMBOLTABLEMODEL_H
#define DEBUGGERSYMBOLTABLEMODEL_H

#include <abstracttablemodel.h>
#include "conditionalng.h"
#include "symboltable.h"

class DebuggerSymbolTableModel : public AbstractTableModel
{
  Q_OBJECT
 public:
  explicit DebuggerSymbolTableModel(ConditionalNG* conditionalNG, QObject *parent = nullptr);
  /*public*/  static /*final*/const int COLUMN_NAME = 0;
  /*public*/  static /*final*/const int COLUMN_VALUE = 1;
  /*public*/  void update(QMap<QString, SymbolTable::Symbol*> symbols);
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  /*public*/  QString getColumnClass(int col) const override;
  /*public*/  void setColumnForMenu(JTable* table);

 private:
  /*private*/ /*final*/ ConditionalNG* _conditionalNG;
  /*private*/ /*final*/ QList<SymbolTable::Symbol*> _symbols = QList<SymbolTable::Symbol*>();

};

#endif // DEBUGGERSYMBOLTABLEMODEL_H
