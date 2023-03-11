#include "moduleparameterstablemodel.h"
#include "exceptions.h"
#include "defaultsymboltable.h"
#include "jcombobox.h"
#include "jtable.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
/**
 * Table model for local variables
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/ class ModuleParametersTableModel extends AbstractTableModel {




    /*public*/ModuleParametersTableModel::ModuleParametersTableModel(/*@Nonnull*/ Module* module, QObject *parent)
    : AbstractTableModel{parent} {
    for (Module::Parameter* v : module->getParameters()) {
            _parameters.append(new DefaultSymbolTable::DefaultParameter(v));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int ModuleParametersTableModel::rowCount(const QModelIndex& parent) const {
        return _parameters.size();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int ModuleParametersTableModel::columnCount(const QModelIndex& parent) const {
        return 4;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QVariant ModuleParametersTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section) {
            case COLUMN_NAME:
                return tr("Name");
            case COLUMN_IS_INPUT:
                return tr("IsInput");
            case COLUMN_IS_OUTPUT:
                return tr("IsOutput");
            case COLUMN_MENU:
                return tr("Menu");
            default:
                throw new IllegalArgumentException("Invalid column");
        }
      }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ /*Class<?>*/QString ModuleParametersTableModel::getColumnClass(int col) const {
        switch (col) {
            case COLUMN_NAME:
                return "String";
            case COLUMN_IS_INPUT:
                return "Boolean";
            case COLUMN_IS_OUTPUT:
                return "Boolean";
            case COLUMN_MENU:
                return "Menu";
            default:
                throw new IllegalArgumentException("Invalid column");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Qt::ItemFlags ModuleParametersTableModel::flags(const QModelIndex &index) const {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool ModuleParametersTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(role == Qt::EditRole)
    {
        if (index.row() >= _parameters.size()) return false;

        DefaultSymbolTable::DefaultParameter* parameter = _parameters.at(index.row());

        switch (index.column()) {
            case COLUMN_NAME:
            parameter->setName( value.toString());
                break;
            case COLUMN_IS_INPUT:
            parameter->setIsInput( value.toBool());
                break;
            case COLUMN_IS_OUTPUT:
            parameter->setIsOutput( value.toBool());
                break;
            case COLUMN_MENU:
                // Do nothing
                break;
            default:
                throw new IllegalArgumentException("Invalid column");
        }
      }
      return false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QVariant ModuleParametersTableModel::data(const QModelIndex &index, int role) const  {
    if(role== Qt::DisplayRole)
    {
        if (index.row() >= _parameters.size()) throw new IllegalArgumentException("Invalid row");

        switch (index.column()) {
            case COLUMN_NAME:
            return _parameters.at(index.row())->getName();
        }
    }
    if(role == Qt::CheckStateRole)
    {
        switch (index.column()) {

            case COLUMN_IS_INPUT:
            return _parameters.at(index.row())->isInput()?Qt::Checked:Qt::Unchecked;
            case COLUMN_IS_OUTPUT:
            return _parameters.at(index.row())->isOutput()?Qt::Checked:Qt::Unchecked;
        }
//            case COLUMN_MENU:
//                return Menu.Select;
//            default:
//                throw new IllegalArgumentException("Invalid column");
//        }
      }
      return QVariant();
    }

    /*public*/ void ModuleParametersTableModel::setColumnForMenu(JTable* table) {
        JComboBox/*<Menu>*/* comboBox = new JComboBox();
//        table.setRowHeight(comboBox.getPreferredSize().height);
        table->getColumnModel()->getColumn(COLUMN_MENU)
                ->setPreferredWidth((comboBox->sizeHint().width()) + 4);
    }

    /*public*/ void ModuleParametersTableModel::add() {
        int row = _parameters.size();
        _parameters.append(new DefaultSymbolTable::DefaultParameter("", false, false));
        fireTableRowsInserted(row, row);
    }

    /*public*/ QList<DefaultSymbolTable::DefaultParameter *> ModuleParametersTableModel::getParameters() {
        return _parameters;
    }

#if 0

    /*public*/ static enum Menu {
        Select(tr("Select")),
        Delete(tr("Delete")),
        MoveUp(tr("Move Up")),
        MoveDown(tr("Move Down"));

        private final String _descr;

        private Menu(String descr) {
            _descr = descr;
        }

        //@Override
        /*public*/ String toString() {
            return _descr;
        }
    }


    /*public*/ static class TypeCellRenderer extends DefaultTableCellRenderer {

        //@Override
        /*public*/ Component getTableCellRendererComponent(JTable table, Object value,
                boolean isSelected, boolean hasFocus, int row, int column) {

            if (value == null) value = InitialValueType.None;

            if (! (value instanceof InitialValueType)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + value.getClass().getName());
            }
            setText(((InitialValueType) value).toString());
            return this;
        }
    }


    /*public*/ static class MenuCellRenderer extends DefaultTableCellRenderer {

        //@Override
        /*public*/ Component getTableCellRendererComponent(JTable table, Object value,
                boolean isSelected, boolean hasFocus, int row, int column) {

            if (value == null) value = Menu.Select;

            if (! (value instanceof Menu)) {
                throw new IllegalArgumentException("value is not an Menu: " + value.getClass().getName());
            }
            setText(((Menu) value).toString());
            return this;
        }
    }


    /*public*/ static class TypeCellEditor extends AbstractCellEditor
            implements TableCellEditor, ActionListener {

        private InitialValueType _type;

        //@Override
        /*public*/ Object getCellEditorValue() {
            return this._type;
        }

        //@Override
        /*public*/ Component getTableCellEditorComponent(JTable table, Object value,
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
        @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<InitialValueType>
        /*public*/ void actionPerformed(ActionEvent event) {
            if (! (event.getSource() instanceof JComboBox)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + event.getSource().getClass().getName());
            }
            JComboBox<InitialValueType> typeComboBox =
                    (JComboBox<InitialValueType>) event.getSource();
            _type = typeComboBox.getItemAt(typeComboBox.getSelectedIndex());
        }

    }


    /*public*/ static class MenuCellEditor extends AbstractCellEditor
            implements TableCellEditor, ActionListener {

        JTable _table;
        ModuleParametersTableModel _tableModel;

        /*public*/ MenuCellEditor(JTable table, ModuleParametersTableModel tableModel) {
            _table = table;
            _tableModel = tableModel;
        }

        //@Override
        /*public*/ Object getCellEditorValue() {
            return Menu.Select;
        }

        //@Override
        /*public*/ Component getTableCellEditorComponent(JTable table, Object value,
                boolean isSelected, int row, int column) {

            if (value == null) value = Menu.Select;

            if (! (value instanceof Menu)) {
                throw new IllegalArgumentException("value is not an Menu: " + value.getClass().getName());
            }

            JComboBox<Menu> menuComboBox = new JComboBox<>();

            for (Menu menu : Menu.values()) {
                if ((menu == Menu.MoveUp) && (row == 0)) continue;
                if ((menu == Menu.MoveDown) && (row+1 == _tableModel._parameters.size())) continue;
                menuComboBox.addItem(menu);
            }
            JComboBoxUtil.setupComboBoxMaxRows(menuComboBox);

            menuComboBox.setSelectedItem(value);
            menuComboBox.addActionListener(this);

            return menuComboBox;
        }

        //@Override
        @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<Menu>
        /*public*/ void actionPerformed(ActionEvent event) {
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
                    if ((row+1) < _tableModel._parameters.size()) moveUp(row+1);
                    break;
                default:
                    // Do nothing
            }
            // Remove focus from combo box
            if (_tableModel._parameters.size() > 0) _table.editCellAt(row, COLUMN_NAME);
        }

        private void delete(int row) {
            _tableModel._parameters.remove(row);
            _tableModel.fireTableRowsDeleted(row, row);
        }

        private void moveUp(int row) {
            DefaultParameter temp = _tableModel._parameters.get(row-1);
            _tableModel._parameters.set(row-1, _tableModel._parameters.get(row));
            _tableModel._parameters.set(row, temp);
            _tableModel.fireTableRowsUpdated(row-1, row);
        }

    }
#endif
