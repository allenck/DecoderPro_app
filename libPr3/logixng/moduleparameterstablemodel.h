#ifndef MODULEPARAMETERSTABLEMODEL_H
#define MODULEPARAMETERSTABLEMODEL_H

#include <abstracttablemodel.h>
#include "defaultsymboltable.h"

class Module;
class ModuleParametersTableModel : public AbstractTableModel
{
    Q_OBJECT
public:
    explicit ModuleParametersTableModel(Module* module, QObject *parent = nullptr);
    enum COLS
    {
     COLUMN_NAME = 0,
     COLUMN_IS_INPUT = 1,
     COLUMN_IS_OUTPUT = 2,
     COLUMN_MENU = 3
    };
    /*public*/ int rowCount(const QModelIndex& parent) const override;
    /*public*/ int columnCount(const QModelIndex& parent) const override;
    /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /*public*/ /*Class<?>*/QString getColumnClass(int col) const override;
    /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
    /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    /*public*/ QVariant data(const QModelIndex &index, int role) const override;
    /*public*/ void setColumnForMenu(JTable* table);
    /*public*/ void add();
    /*public*/ QList<DefaultSymbolTable::DefaultParameter*> getParameters();

private:
    /*private*/ /*final*/ QList<DefaultSymbolTable::DefaultParameter*> _parameters = QList<DefaultSymbolTable::DefaultParameter*>();

};

#endif // MODULEPARAMETERSTABLEMODEL_H
