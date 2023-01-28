#ifndef CALLMODULEPARAMETERTABLEMODEL_H
#define CALLMODULEPARAMETERTABLEMODEL_H

#include <abstracttablemodel.h>
#include "module.h"

class CallModuleParameterTableModel : public AbstractTableModel
{
  Q_OBJECT
 public:
  /*public*/  CallModuleParameterTableModel(Module* module, QList<Module::ParameterData*>* parameterData,
                                            QObject* parent = nullptr);

  enum COLUMNS
  {
   COLUMN_NAME = 0,
   COLUMN_INPUT_TYPE = 1,
   COLUMN_INPUT_DATA = 2,
   COLUMN_OUTPUT_TYPE = 3,
   COLUMN_OUTPUT_DATA = 4
  };
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ QString getColumnClass(int col)const override;
  /*public*/  void setColumnsForComboBoxes(JTable* table);
  /*public*/  void add();
  /*public*/  QList<Module::ParameterData *> *getParameters();

 private:
  /*private*/ /*final*/ QList<Module::ParameterData*>* _parameterData = new QList<Module::ParameterData*>();

};

#endif // CALLMODULEPARAMETERTABLEMODEL_H
