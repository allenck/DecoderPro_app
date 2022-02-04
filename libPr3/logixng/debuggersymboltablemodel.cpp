#include "debuggersymboltablemodel.h"
#include "jcombobox.h"
#include "jtable.h"
#include "tablecolumnmodel.h"
/**
 * Table model for the current symbol table while debugging
 * @author Daniel Bergqvist Copyright 2020
 */
// /*public*/  class DebuggerSymbolTableModel extends AbstractTableModel {

//    /*public*/  static /*final*/ int COLUMN_TYPE = 1;
//    /*public*/  static /*final*/ int COLUMN_DATA = 2;
//    /*public*/  static /*final*/ int COLUMN_MENU = 3;



    /*public*/  DebuggerSymbolTableModel::DebuggerSymbolTableModel(ConditionalNG* conditionalNG, QObject* parent)
      : AbstractTableModel(parent)
    {
        _conditionalNG = conditionalNG;
//        if (maleSocket != null) {
//            for (VariableData v : maleSocket.getLocalVariables()) {
//                _variables.add(new VariableData(v));
//            }
//        }
    }

    /*public*/  void DebuggerSymbolTableModel::update(QMap<QString, Symbol*> symbols) {
        _symbols.clear();
        for (Symbol* s : symbols.values()) {
            _symbols.append(s);
        }
        fireTableDataChanged();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int DebuggerSymbolTableModel::rowCount(const QModelIndex &parent) const {
        return _symbols.size();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int DebuggerSymbolTableModel::columnCount(const QModelIndex &parent) const {
        return 2;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant DebuggerSymbolTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
        switch (section) {
            case COLUMN_NAME:
                return tr("SymbolName");
            case COLUMN_VALUE:
                return tr("Value");
//            case COLUMN_TYPE:
//                return Bundle.getMessage("ColumnVariableType");
//            case COLUMN_DATA:
//                return Bundle.getMessage("ColumnVariableData");
//            case COLUMN_MENU:
//                return Bundle.getMessage("ColumnVariableMenu");
            default:
                throw new IllegalArgumentException("Invalid column");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString DebuggerSymbolTableModel::getColumnClass(int col) const {
        switch (col) {
//            case COLUMN_TYPE:
//                return InitialValueType.class;
//            case COLUMN_MENU:
//                return Menu.class;
            case COLUMN_NAME:
            case COLUMN_VALUE:
//            case COLUMN_DATA:
                return "String";
            default:
                throw new IllegalArgumentException("Invalid column");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Qt::ItemFlags DebuggerSymbolTableModel::flags(const QModelIndex &index) const {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool DebuggerSymbolTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
        Symbol* symbol = _symbols.value(index.row());
     if(role == Qt::EditRole)
     {
        switch (index.column()) {
            case COLUMN_VALUE:
                _conditionalNG->getStack()->setValueAtIndex(symbol->getIndex(), value);
                break;
//            case COLUMN_TYPE:
//                variable._initalValueType = (InitialValueType) value;
//                break;
//            case COLUMN_DATA:
//                variable._initialValueData = (String) value;
//                break;
//            case COLUMN_MENU:
//                // Do nothing
//                break;
            default:
                throw new IllegalArgumentException("Invalid column");
        }
     }
     return AbstractTableModel::setData(index, value, role);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant DebuggerSymbolTableModel::data(const QModelIndex &index, int role) const {
      if(role == Qt::DisplayRole)
      {
        if (index.row() >= _symbols.size()) throw new IllegalArgumentException("Invalid row");

        switch (index.column()) {
            case COLUMN_NAME:
                return _symbols.value(index.row())->getName();
            case COLUMN_VALUE:
                return _conditionalNG->getStack()->getValueAtIndex(_symbols.value(index.row())->getIndex());
//            case COLUMN_TYPE:
//                return _variables.get(rowIndex).getInitalValueType();
//            case COLUMN_DATA:
//                return _variables.get(rowIndex).getInitialValueData();
//            case COLUMN_MENU:
//                return Menu.Select;
            default:
                throw new IllegalArgumentException("Invalid column");
        }
      }
      return AbstractTableModel::data(index, role);
    }
#if 0
    /*public*/  void DebuggerSymbolTableModel::setColumnForMenu(JTable* table) {
        JComboBox/*<Menu>*/* comboBox = new JComboBox();
        table->setRowHeight(comboBox->sizeHint().height());
        table->getColumnModel()->getColumn(COLUMN_MENU)
                ->setPreferredWidth((comboBox->sizeHint().width()) + 4);
    }

    /*public*/  void add() {
        int row = _symbols.size();
        _symbols.add(new VariableData("", InitialValueType.None, ""));
        fireTableRowsInserted(row, row);
    }

    /*public*/  List<VariableData> getVariables() {
        return _symbols;
    }


    /*public*/  static enum Menu {
        Select(Bundle.getMessage("TableMenuSelect")),
        Delete(Bundle.getMessage("TableMenuDelete")),
        MoveUp(Bundle.getMessage("TableMenuMoveUp")),
        MoveDown(Bundle.getMessage("TableMenuMoveDown"));

        /*private*/ /*final*/ String _descr;

        /*private*/ Menu(String descr) {
            _descr = descr;
        }

        //@Override
        /*public*/  String toString() {
            return _descr;
        }
    }


    /*public*/  static class TypeCellRenderer extends DefaultTableCellRenderer {

        //@Override
        /*public*/  Component getTableCellRendererComponent(JTable table, Object value,
                boolean isSelected, boolean hasFocus, int row, int column) {

            if (value == null) value = InitialValueType.None;

            if (! (value instanceof InitialValueType)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + value.getClass().getName());
            }
            setText(((InitialValueType) value).getDescr());
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
        /*public*/  Object getCellEditorValue() {
            return this._type;
        }

        //@Override
        /*public*/  Component getTableCellEditorComponent(JTable table, Object value,
                boolean isSelected, int row, int column) {

            if (value == null) value = InitialValueType.None;

            if (! (value instanceof InitialValueType)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + value.getClass().getName());
            }

            JComboBox<InitialValueType> typeComboBox = new JComboBox<>();

            for (InitialValueType type : InitialValueType.values()) {
                typeComboBox.addItem(type);
            }

            typeComboBox.setSelectedItem(value);
            typeComboBox.addActionListener(this);

            return typeComboBox;
        }

        //@Override
        @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<InitialValueType>
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
        DebuggerLocalVariableTableModel _tableModel;

        /*public*/  MenuCellEditor(JTable table, DebuggerLocalVariableTableModel tableModel) {
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
                if ((menu == Menu.MoveDown) && (row+1 == _tableModel._symbols.size())) continue;
                menuComboBox.addItem(menu);
            }

            menuComboBox.setSelectedItem(value);
            menuComboBox.addActionListener(this);

            return menuComboBox;
        }

        //@Override
        //@SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<Menu>
        /*public*/  void actionPerformed(JActionEvent* event) {
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
                    if ((row+1) < _tableModel._symbols.size()) moveUp(row+1);
                    break;
                default:
                    // Do nothing
            }
            // Remove focus from combo box
            if (_tableModel._symbols.size() > 0) _table.editCellAt(row, COLUMN_NAME);
        }

        /*private*/ void delete(int row) {
            _tableModel._symbols.remove(row);
            _tableModel.fireTableRowsDeleted(row, row);
        }

        /*private*/ void moveUp(int row) {
            VariableData temp = _tableModel._symbols.get(row-1);
            _tableModel._symbols.set(row-1, _tableModel._symbols.get(row));
            _tableModel._symbols.set(row, temp);
            _tableModel.fireTableRowsUpdated(row-1, row);
        }

    }
#endif
