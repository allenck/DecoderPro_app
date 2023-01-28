#include "logdatatablemodel.h"
#include "../parserexception.h"
#include "runtimeexception.h"

/**
 * Table model for LogData
 *
 * @author Daniel Bergqvist Copyright 2021
 */
// /*public*/  class LogDataTableModel extends AbstractTableModel {
namespace Actions
{
    /*public*/  LogDataTableModel::LogDataTableModel(QList<LogData::Data>* namedBeanReference, QObject* parent) {
        if (namedBeanReference != nullptr) //_dataList.addAll(*namedBeanReference);
        {
         foreach(LogData::Data d , *namedBeanReference)
         {
          _dataList.append(d);
         }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int  LogDataTableModel::rowCount(const QModelIndex &parent) const {
        return _dataList.size();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int  LogDataTableModel::columnCount(const QModelIndex &parent) const {
        return COLUMN_DUMMY+1;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant LogDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
        switch (section) {
            case COLUMN_TYPE:
                return tr("ColumnType");
            case COLUMN_DATA:
                return tr("ColumnData");
            case COLUMN_DELETE:
                return "";  // no label
            case COLUMN_DUMMY:
                return "";  // no label
            default:
                throw new IllegalArgumentException("Invalid column");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString LogDataTableModel::getColumnClass(int col) const{
        switch (col) {
            case COLUMN_TYPE:
                return "LogData::DataType";
            case COLUMN_DATA:
                return "String";
            case COLUMN_DELETE:
                return "JButton";
            case COLUMN_DUMMY:
                return "String";
            default:
                throw new IllegalArgumentException("Invalid column");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Qt::ItemFlags LogDataTableModel::flags(const QModelIndex &index) const {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool LogDataTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(role == Qt::EditRole)
    {
        LogData::Data ref = _dataList.at(index.row());

        switch (index.column()) {
        case COLUMN_TYPE:
        {
          LogData::DataType::DATATYPE oldType = ref.getDataType();
          ref.setDataType(LogData::DataType::fromString( value.toString()));
          if (oldType != ref.getDataType()) ref.setData("");
          break;
        }
            case COLUMN_DATA:
                ref.setData( value.toString());
                break;
            case COLUMN_DELETE:
                _delete(index.row());
                break;
            case COLUMN_DUMMY:
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
    /*public*/  QVariant LogDataTableModel::data(const QModelIndex &index, int role) const {
     if(role == Qt::DisplayRole)
     {
        if (index.row() >= _dataList.size()) throw new IllegalArgumentException("Invalid row");

        switch (index.column()) {
            case COLUMN_TYPE:
                return _dataList.at(index.row()).getDataType();
            case COLUMN_DATA:
                return _dataList.at(index.row()).getData();
            case COLUMN_DELETE:
                return tr("Delete");  // NOI18N
            case COLUMN_DUMMY:
                return "";
            default:
                throw new IllegalArgumentException("Invalid column");
        }
     }
     return QVariant();
    }

    /*public*/  void LogDataTableModel::setColumnsForComboBoxes(JTable* table) {
#if 0
        JComboBox<LogData.DataType> beanTypeComboBox = new JComboBox<>();
        table.setRowHeight(beanTypeComboBox.getPreferredSize().height);
        table.getColumnModel().getColumn(COLUMN_TYPE)
                .setPreferredWidth((beanTypeComboBox.getPreferredSize().width) + 4);
#endif
    }

    /*public*/  void LogDataTableModel::add() {
        int row = _dataList.size();
        try {
            _dataList.append( LogData::Data(LogData::DataType::LocalVariable, ""));
        } catch (ParserException* e) {
            throw new RuntimeException(e);  // This should never happen
        }
        fireTableRowsInserted(row, row);
    }

    /*private*/ void LogDataTableModel::_delete(int row) {
        _dataList.removeAt(row);
        fireTableRowsDeleted(row, row);
    }

    /*public*/  QList<LogData::Data> LogDataTableModel::getDataList() {
        return _dataList;
    }

    #if 0
    /*public*/  static class CellRenderer extends DefaultTableCellRenderer {

        //@Override
        /*public*/  Component getTableCellRendererComponent(JTable table, Object value,
                boolean isSelected, boolean hasFocus, int row, int column) {

            if (column == COLUMN_TYPE) {
                if (value == null) value = LogData.DataType.LocalVariable;

                if (! (value instanceof LogData.DataType)) {
                    throw new IllegalArgumentException("value is not an LogData.DataType: " + value.getClass().getName());
                }
                setText(((LogData.DataType) value).toString());
            } else {
                throw new RuntimeException("Unknown column: "+Integer.toString(column));
            }
            return this;
        }
    }


    /*public*/  static class DataTypeCellEditor extends AbstractCellEditor
            implements TableCellEditor, ActionListener {

        private LogData.DataType _beanType;

        //@Override
        /*public*/  Object getCellEditorValue() {
            return this._beanType;
        }

        //@Override
        /*public*/  Component getTableCellEditorComponent(JTable table, Object value,
                boolean isSelected, int row, int column) {

            if (value == null) value = LogData.DataType.LocalVariable;

            if (! (value instanceof LogData.DataType)) {
                throw new IllegalArgumentException("value is not an LogData.DataType: " + value.getClass().getName());
            }

            JComboBox<LogData.DataType> returnValueTypeComboBox = new JComboBox<>();

            for (LogData.DataType type : LogData.DataType.values()) {
                returnValueTypeComboBox.addItem(type);
            }
            JComboBoxUtil.setupComboBoxMaxRows(returnValueTypeComboBox);

            returnValueTypeComboBox.setSelectedItem(value);
            returnValueTypeComboBox.addActionListener(this);

            return returnValueTypeComboBox;
        }

        //@Override
        @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<LogData.DataType>
        /*public*/  void actionPerformed(ActionEvent event) {
            if (! (event.getSource() instanceof JComboBox)) {
                throw new IllegalArgumentException("value is not an JComboBox: " + event.getSource().getClass().getName());
            }
            JComboBox<LogData.DataType> returnValueTypeComboBox =
                    (JComboBox<LogData.DataType>) event.getSource();
            _beanType = returnValueTypeComboBox.getItemAt(returnValueTypeComboBox.getSelectedIndex());

        }

    }

/*
    /*public*/  NamedBeanCellEditor getNamedBeanCellEditor() {
        return new NamedBeanCellEditor();
    }


    /*public*/  class NamedBeanCellEditor extends AbstractCellEditor
            implements TableCellEditor, ActionListener {

        private String _namedBean;

        //@Override
        /*public*/  QVariant getCellEditorValue() {
            return this._namedBean;
        }

        //@Override
        /*public*/  Component getTableCellEditorComponent(JTable table, Object value,
                boolean isSelected, int row, int column) {

            if ((value != null) && (! (value instanceof String))) {
                throw new IllegalArgumentException("value is not a String: " + value.getClass().getName());
            }

            JComboBox<String> namedBeanComboBox = new JComboBox<>();
            SortedSet<? extends NamedBean> set =
                    _dataList.get(row).getDataType().getManager().getNamedBeanSet();

            String name = _dataList.get(row).getData();

            if (!set.isEmpty()) {
                for (NamedBean bean : set) {
                    namedBeanComboBox.addItem(bean.getDisplayName());

                    if (name != null) {
                        if (name.equals(bean.getUserName()) || name.equals(bean.getSystemName())) {
                            namedBeanComboBox.setSelectedItem(bean.getDisplayName());
                        }
                    }
                }
                JComboBoxUtil.setupComboBoxMaxRows(namedBeanComboBox);
            } else {
                namedBeanComboBox.addItem("");
            }

//            namedBeanComboBox.setSelectedItem(value);
            namedBeanComboBox.addActionListener(this);

            return namedBeanComboBox;
        }

        //@Override
        @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<LogData.DataType>
        /*public*/  void actionPerformed(ActionEvent event) {
            if (! (event.getSource() instanceof JComboBox)) {
                throw new IllegalArgumentException("value is not an JComboBox: " + event.getSource().getClass().getName());
            }
            JComboBox<String> namedBeanComboBox = (JComboBox<String>) event.getSource();
            int index = namedBeanComboBox.getSelectedIndex();
            _namedBean = (index != -1) ? namedBeanComboBox.getItemAt(index) : null;
        }

    }
 */
#endif

}
