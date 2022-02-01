#include "localvariabletablemodel.h"
#include "symboltable.h"
#include "jcombobox.h"
#include "jtable.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"

/**
 * Table model for local variables
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class LocalVariableTableModel extends AbstractTableModel {




    /*public*/  LocalVariableTableModel::LocalVariableTableModel(MaleSocket* maleSocket, QObject *parent) {
        if (maleSocket != nullptr) {
            for (VariableData* v : maleSocket->getLocalVariables()) {
                _variables.append(new VariableData(v));
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int LocalVariableTableModel::rowCount(const QModelIndex &parent) const {
        return _variables.size();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int LocalVariableTableModel::columnCount(const QModelIndex &parent) const {
        return 4;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant LocalVariableTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
     if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
     {
        switch (section) {
            case COLUMN_NAME:
                return tr("VariableName");
            case COLUMN_TYPE:
                return tr("VariableType");
            case COLUMN_DATA:
                return tr("VariableData");
            case COLUMN_MENU:
                return tr("VariableMenu");
            default:
                throw new IllegalArgumentException("Invalid column");
        }
       }
     return AbstractTableModel::headerData(section, orientation, role);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString LocalVariableTableModel::getColumnClass(int col) const {
        switch (col) {
            case COLUMN_TYPE:
                return "InitialValueType";
            case COLUMN_MENU:
                return "Menu";
            case COLUMN_NAME:
            case COLUMN_DATA:
                return "String";
            default:
                throw new IllegalArgumentException("Invalid column");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Qt::ItemFlags LocalVariableTableModel::flags(const QModelIndex &index) const {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool LocalVariableTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
        VariableData* variable = _variables.at(index.row());
        if(role == Qt::EditRole)
        {
          switch (index.column()) {
            case COLUMN_NAME:
                variable->_name = value.toString();
                break;
            case COLUMN_TYPE:
                variable->_initalValueType = (SymbolTable::InitialValueType::toType(value.toString()));
                break;
            case COLUMN_DATA:
                variable->_initialValueData =  value.toString();
                break;
            case COLUMN_MENU:
                // Do nothing
                break;
            default:
                throw new IllegalArgumentException("Invalid column");
          }
        }
        return AbstractTableModel::setData(index, value, role);
    }
/*public*/  /*static*/ class Menu {
//        Select(Bundle.getMessage("TableMenuSelect")),
//        Delete(Bundle.getMessage("TableMenuDelete")),
//        MoveUp(Bundle.getMessage("TableMenuMoveUp")),
//        MoveDown(Bundle.getMessage("TableMenuMoveDown"));
 public:
     enum TYPE {Select, Delete, MoveUp, MoveDown};

//        /*private*/ /*final*/ String _descr;

//        /*private*/ Menu(String descr) {
//            _descr = descr;
//        }

    //@Override
    /*public*/static  QString toString(TYPE t) {
        switch(t)
        {
         case Select: return "Select";
        case Delete: return "Select";
        case MoveUp: return "MoveUp";
        case MoveDown: return "MoveDown";
        }
    }
     /*public*/static TYPE toType(QString s)
     {
      if(s == "Select") return Select;
     if(s == "Delete") return Delete;
     if(s == "MoveUp") return MoveUp;
     if(s == "MoveDown") return MoveDown;}
};
    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant LocalVariableTableModel::data(const QModelIndex &index, int role) const  {
     if(role == Qt::DisplayRole)
     {
        if (index.row() >= _variables.size()) throw new IllegalArgumentException("Invalid row");

        switch (index.column()) {
            case COLUMN_NAME:
                return _variables.value(index.row())->getName();
            case COLUMN_TYPE:
                return SymbolTable::InitialValueType::toString(_variables.value(index.row())->getInitalValueType());
            case COLUMN_DATA:
                return _variables.value(index.row())->getInitialValueData();
            case COLUMN_MENU:
                return Menu::toString(Menu::Select);
            default:
                throw new IllegalArgumentException("Invalid column");
        }
     }
     return AbstractTableModel::data(index, role);
    }

    /*public*/  void LocalVariableTableModel::setColumnForMenu(JTable* table) {
        JComboBox/*<Menu>*/* comboBox = new JComboBox();
        table->setRowHeight(comboBox->sizeHint().height());
        table->getColumnModel()->getColumn(COLUMN_MENU)
                ->setPreferredWidth((comboBox->sizeHint().width()) + 4);
    }

    /*public*/  void LocalVariableTableModel::add() {
        int row = _variables.size();
        _variables.append(new VariableData("", SymbolTable::InitialValueType::None, ""));
        fireTableRowsInserted(row, row);
    }

    /*public*/  QList<VariableData*> LocalVariableTableModel::getVariables() {
        return _variables;
    }



#if 0

    /*public*/  static class TypeCellRenderer extends DefaultTableCellRenderer {

        //@Override
        /*public*/  Component getTableCellRendererComponent(JTable table, Object value,
                boolean isSelected, boolean hasFocus, int row, int column) {

            if (value == null) value = InitialValueType.None;

            if (! (value instanceof InitialValueType)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + value.getClass().getName());
            }
            setText(((InitialValueType) value).toString());
            return this;
        }
    }


    /*public*/  static class MenuCellRenderer extends DefaultTableCellRenderer {

        //@Override
        /*public*/  Component getTableCellRendererComponent(JTable table, Object value,
                boolean isSelected, boolean hasFocus, int row, int column) {

            if (value == null) value = Menu.Select;

            if (! (value instanceof Menu)) {
                throw new IllegalArgumentException("value is not an Menu: " + value.getClass().getName());
            }
            setText(((Menu) value).toString());
            return this;
        }
    }


    /*public*/  static class TypeCellEditor extends AbstractCellEditor
            implements TableCellEditor, ActionListener {

        /*private*/ InitialValueType _type;

        //@Override
        /*public*/  QVariant getCellEditorValue() {
            return this._type;
        }

        //@Override
        /*public*/  QWidgget* getTableCellEditorComponent(JTable* table, QVariant value,
                boolean isSelected, int row, int column) {

            if (value == null) value = InitialValueType.None;

            if (! (value instanceof InitialValueType)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + value.getClass().getName());
            }

            JComboBox<InitialValueType> typeComboBox = new JComboBox<>();

            for (InitialValueType type : InitialValueType.values()) {
                typeComboBox.addItem(type);
            }
            JComboBoxUtil.setupComboBoxMaxRows(typeComboBox);

            typeComboBox.setSelectedItem(value);
            typeComboBox.addActionListener(this);

            return typeComboBox;
        }

        //@Override
        //@SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<InitialValueType>
        /*public*/  void actionPerformed(ActionEvent event) {
            if (! (event.getSource() instanceof JComboBox)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + event.getSource().getClass().getName());
            }
            JComboBox<InitialValueType> typeComboBox =
                    (JComboBox<InitialValueType>) event.getSource();
            _type = typeComboBox.getItemAt(typeComboBox.getSelectedIndex());
        }

    }


    /*public*/  static class MenuCellEditor extends AbstractCellEditor
            implements TableCellEditor, ActionListener {

        JTable _table;
        LocalVariableTableModel _tableModel;

        /*public*/  MenuCellEditor(JTable table, LocalVariableTableModel tableModel) {
            _table = table;
            _tableModel = tableModel;
        }

        //@Override
        /*public*/  Object getCellEditorValue() {
            return Menu.Select;
        }

        //@Override
        /*public*/  Component getTableCellEditorComponent(JTable table, Object value,
                boolean isSelected, int row, int column) {

            if (value == null) value = Menu.Select;

            if (! (value instanceof Menu)) {
                throw new IllegalArgumentException("value is not an Menu: " + value.getClass().getName());
            }

            JComboBox<Menu> menuComboBox = new JComboBox<>();

            for (Menu menu : Menu.values()) {
                if ((menu == Menu.MoveUp) && (row == 0)) continue;
                if ((menu == Menu.MoveDown) && (row+1 == _tableModel._variables.size())) continue;
                menuComboBox.addItem(menu);
            }
            JComboBoxUtil.setupComboBoxMaxRows(menuComboBox);

            menuComboBox.setSelectedItem(value);
            menuComboBox.addActionListener(this);

            return menuComboBox;
        }

        //@Override
        @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<Menu>
        /*public*/  void actionPerformed(ActionEvent event) {
            if (! (event.getSource() instanceof JComboBox)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + event.getSource().getClass().getName());
            }
            JComboBox<Menu> menuComboBox =
                    (JComboBox<Menu>) event.getSource();
            int row = _table.getSelectedRow();
            Menu menu = menuComboBox.getItemAt(menuComboBox.getSelectedIndex());

            switch (menu) {
                case Delete:
                    delete(row);
                    break;
                case MoveUp:
                    if ((row) > 0) moveUp(row);
                    break;
                case MoveDown:
                    if ((row+1) < _tableModel._variables.size()) moveUp(row+1);
                    break;
                default:
                    // Do nothing
            }
            // Remove focus from combo box
            if (_tableModel._variables.size() > 0) _table.editCellAt(row, COLUMN_NAME);
        }

        /*private*/ void delete(int row) {
            _tableModel._variables.remove(row);
            _tableModel.fireTableRowsDeleted(row, row);
        }

        /*private*/ void moveUp(int row) {
            VariableData temp = _tableModel._variables.get(row-1);
            _tableModel._variables.set(row-1, _tableModel._variables.get(row));
            _tableModel._variables.set(row, temp);
            _tableModel.fireTableRowsUpdated(row-1, row);
        }

    }
#endif
