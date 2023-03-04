#include "callmoduleparametertablemodel.h"
#include "jcombobox.h"
/**
 * Table model for CallModule parameters
 * @author Daniel Bergqvist Copyright 2020
 */
// /*public*/  class CallModuleParameterTableModel extends AbstractTableModel {




/*public*/  CallModuleParameterTableModel::CallModuleParameterTableModel(Module* module, QList<Module::ParameterData *> *parameterData, QObject* parent) {
 if (module != nullptr) {
  QMap<QString, Module::ParameterData*> parameterDataMap = QMap<QString, Module::ParameterData*>();
  for (Module::ParameterData* pd : *parameterData) {
      parameterDataMap.insert(pd->_name, new Module::ParameterData(pd));
  }
  for (Module::Parameter* p : module->getParameters()) {
      if (parameterDataMap.contains(p->getName())) {
          _parameterData->append(parameterDataMap.value(p->getName()));
      } else {
          _parameterData->append(new Module::ParameterData(
                  p->getName(), SymbolTable::InitialValueType::None, "",
                  ReturnValueType::None, ""));
      }
  }
 }
}

/** {@inheritDoc} */
//@Override
/*public*/  int CallModuleParameterTableModel::rowCount(const QModelIndex &parent) const {
    return _parameterData->size();
}

/** {@inheritDoc} */
//@Override
/*public*/  int CallModuleParameterTableModel::columnCount(const QModelIndex &parent) const  {
    return 5;
}

/** {@inheritDoc} */
//@Override
/*public*/  QVariant CallModuleParameterTableModel::headerData(int section, Qt::Orientation orientation, int role) const{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case COLUMN_NAME:
            return tr("Name");
        case COLUMN_INPUT_TYPE:
            return tr("InputParameterType");
        case COLUMN_INPUT_DATA:
            return tr("InputParameterData");
        case COLUMN_OUTPUT_TYPE:
            return tr("OutputParameterType");
        case COLUMN_OUTPUT_DATA:
            return tr("OutputParameterData");
        default:
            throw new IllegalArgumentException("Invalid column");
    }
 }
 return QVariant();
}

/** {@inheritDoc} */
//@Override
/*public*/ QString CallModuleParameterTableModel::getColumnClass(int col) const{
    switch (col) {
        case COLUMN_INPUT_TYPE:
            return "InitialValueType";
        case COLUMN_OUTPUT_TYPE:
            return "ReturnValueType";
        case COLUMN_NAME:
        case COLUMN_INPUT_DATA:
        case COLUMN_OUTPUT_DATA:
            return "String";
        default:
            throw new IllegalArgumentException("Invalid column");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Qt::ItemFlags CallModuleParameterTableModel::flags(const QModelIndex &index) const{
    //return col != COLUMN_NAME;
 if(index.column() == COLUMN_NAME) return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
 return  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool CallModuleParameterTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
   if(role == Qt::EditRole)
   {
    Module::ParameterData* variable = _parameterData->at(index.row());

    switch (index.column()) {
        case COLUMN_NAME:
            variable->_name =  value.toString();
            break;
        case COLUMN_INPUT_TYPE:
//            variable->_initalValueType = (InitialValueType) value.toUInt();
            break;
        case COLUMN_INPUT_DATA:
            variable->_initialValueData =  value.toString();
            break;
        case COLUMN_OUTPUT_TYPE:
//            variable->_returnValueType = (ReturnValueType) value.toUInt();
            break;
        case COLUMN_OUTPUT_DATA:
            variable->_returnValueData =  value.toString();
            break;
        default:
            throw new IllegalArgumentException("Invalid column");
    }
      return true;
 }
      return false;
}

/** {@inheritDoc} */
//@Override
/*public*/  QVariant CallModuleParameterTableModel::data(const QModelIndex &index, int role) const {
 if(role == Qt::DisplayRole)
 {
    if (index.row() >= _parameterData->size()) throw new IllegalArgumentException("Invalid row");

    switch (index.column()) {
        case COLUMN_NAME:
            return _parameterData->at(index.row() )->getName();
        case COLUMN_INPUT_TYPE:
            return _parameterData->at(index.row() )->getInitalValueType();
        case COLUMN_INPUT_DATA:
            return _parameterData->at(index.row() )->getInitialValueData();
        case COLUMN_OUTPUT_TYPE:
            return _parameterData->at(index.row() )->getReturnValueType();
        case COLUMN_OUTPUT_DATA:
            return _parameterData->at(index.row() )->getReturnValueData();
        default:
            throw new IllegalArgumentException("Invalid column");
    }
 }
 return QVariant();
}

/*public*/  void CallModuleParameterTableModel::setColumnsForComboBoxes(JTable* table) {
#if 0
    JComboBox/*<InitialValueType>*/* initValueComboBox = new JComboBox();
    JComboBox<ReturnValueType> returnValueComboBox = new JComboBox<>();
    table.setRowHeight(initValueComboBox.getPreferredSize().height);
    table.getColumnModel().getColumn(COLUMN_INPUT_TYPE)
            .setPreferredWidth((initValueComboBox.getPreferredSize().width) + 4);
    table.getColumnModel().getColumn(COLUMN_OUTPUT_TYPE)
            .setPreferredWidth((returnValueComboBox.getPreferredSize().width) + 4);
#endif
}

/*public*/  void CallModuleParameterTableModel::add() {
    int row = _parameterData->size();
    _parameterData->append(new Module::ParameterData("", SymbolTable::InitialValueType::None, "", ReturnValueType::None, ""));
    fireTableRowsInserted(row, row);
}

/*public*/  QList<Module::ParameterData*>* CallModuleParameterTableModel::getParameters() {
    return _parameterData;
}


// /*public*/  static class TypeCellRenderer extends DefaultTableCellRenderer {
#if 0
    //@Override
    /*public*/  QWidget* getTableCellRendererComponent(JTable* table, Object value,
            boolean isSelected, boolean hasFocus, int row, int column) {

        if (column == COLUMN_INPUT_TYPE) {
            if (value == null) value = InitialValueType.None;

            if (! (value instanceof InitialValueType)) {
                throw new IllegalArgumentException("value is not an InitialValueType: " + value.getClass().getName());
            }
            setText(((InitialValueType) value).toString());
        }
        else if (column == COLUMN_OUTPUT_TYPE) {
            if (value == null) value = ReturnValueType.None;

            if (! (value instanceof ReturnValueType)) {
                throw new IllegalArgumentException("value is not an ReturnValueType: " + value.getClass().getName());
            }
            setText(((ReturnValueType) value).getDescr());
        } else {
            throw new RuntimeException("Unknown column: "+Integer.toString(column));
        }
        return this;
    }
}


/*public*/  static class InitialValueCellEditor extends AbstractCellEditor
        implements TableCellEditor, ActionListener {

    /*private*/ InitialValueType _initialValueType;

    //@Override
    /*public*/  Object getCellEditorValue() {
        return this._initialValueType;
    }

    //@Override
    /*public*/  Component getTableCellEditorComponent(JTable table, Object value,
            boolean isSelected, int row, int column) {

        if (value == null) value = InitialValueType.None;

        if (! (value instanceof InitialValueType)) {
            throw new IllegalArgumentException("value is not an InitialValueType: " + value.getClass().getName());
        }

        JComboBox<InitialValueType> initialValueTypeComboBox = new JComboBox<>();

        for (InitialValueType type : InitialValueType.values()) {
            initialValueTypeComboBox.addItem(type);
        }
        JComboBoxUtil.setupComboBoxMaxRows(initialValueTypeComboBox);

        initialValueTypeComboBox.setSelectedItem(value);
        initialValueTypeComboBox.addActionListener(this);

        return initialValueTypeComboBox;
    }

    //@Override
    @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<InitialValueType>
    /*public*/  void actionPerformed(ActionEvent event) {
        if (! (event.getSource() instanceof JComboBox)) {
            throw new IllegalArgumentException("value is not an JComboBox: " + event.getSource().getClass().getName());
        }
        JComboBox<InitialValueType> initialValueTypeComboBox =
                (JComboBox<InitialValueType>) event.getSource();
        _initialValueType = initialValueTypeComboBox.getItemAt(initialValueTypeComboBox.getSelectedIndex());

    }

}


/*public*/  static class ReturnValueCellEditor extends AbstractCellEditor
        implements TableCellEditor, ActionListener {

    /*private*/ ReturnValueType _returnValueType;

    //@Override
    /*public*/  Object getCellEditorValue() {
        return this._returnValueType;
    }

    //@Override
    /*public*/  Component getTableCellEditorComponent(JTable table, Object value,
            boolean isSelected, int row, int column) {

        if (value == null) value = ReturnValueType.None;

        if (! (value instanceof ReturnValueType)) {
            throw new IllegalArgumentException("value is not an ReturnValueType: " + value.getClass().getName());
        }

        JComboBox<ReturnValueType> returnValueTypeComboBox = new JComboBox<>();

        for (ReturnValueType type : ReturnValueType.values()) {
            returnValueTypeComboBox.addItem(type);
        }
        JComboBoxUtil.setupComboBoxMaxRows(returnValueTypeComboBox);

        returnValueTypeComboBox.setSelectedItem(value);
        returnValueTypeComboBox.addActionListener(this);

        return returnValueTypeComboBox;
    }

    //@Override
    //@SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<ReturnValueType>
    /*public*/  void actionPerformed(ActionEvent event) {
        if (! (event.getSource() instanceof JComboBox)) {
            throw new IllegalArgumentException("value is not an JComboBox: " + event.getSource().getClass().getName());
        }
        JComboBox<ReturnValueType> returnValueTypeComboBox =
                (JComboBox<ReturnValueType>) event.getSource();
        _returnValueType = returnValueTypeComboBox.getItemAt(returnValueTypeComboBox.getSelectedIndex());

    }

}
#endif
