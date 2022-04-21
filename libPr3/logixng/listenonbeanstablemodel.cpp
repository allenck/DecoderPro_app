#include "listenonbeanstablemodel.h"
#include "vptr.h"
#include "jcombobox.h"
#include "jtable.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"

/**
 * Table model for ListenOnBeans named beans
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/  class ListenOnBeansTableModel extends AbstractTableModel {




    /*public*/  ListenOnBeansTableModel::ListenOnBeansTableModel(QList<ActionListenOnBeans::NamedBeanReference*>* namedBeanReference, QObject* parent)
     : AbstractTableModel(parent){
        if (namedBeanReference != nullptr) {
        // .addAll(namedBeanReference);
         for( ActionListenOnBeans::NamedBeanReference* ref : *namedBeanReference)
        {
         _namedBeanReference->append(ref);
        }
       }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int ListenOnBeansTableModel::rowCount(const QModelIndex& ) const {
        return _namedBeanReference->size();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int ListenOnBeansTableModel::columnCount(const QModelIndex& ) const {
        return COLUMN_DUMMY+1;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant ListenOnBeansTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
     if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
     {
        switch (section) {
            case COLUMN_BEAN_TYPE:
                return tr("Bean type");
            case COLUMN_BEAN_NAME:
                return tr("Bean name");
            case COLUMN_DELETE:
                return "";  // no label
            case COLUMN_DUMMY:
                return "";  // no label
            default:
                throw new IllegalArgumentException("Invalid column");
        }
     }
     return QVariant();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString ListenOnBeansTableModel::getColumnClass(int col) const{
        switch (col) {
            case COLUMN_BEAN_TYPE:
                return "NamedBeanType";
            case COLUMN_BEAN_NAME:
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
    /*public*/  Qt::ItemFlags ListenOnBeansTableModel::flags(const QModelIndex &index) const {
        return Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ListenOnBeansTableModel::setData(const QModelIndex &index, const QVariant &value, int role)  {
     if(role == Qt::EditRole){
        ActionListenOnBeans::NamedBeanReference* ref = _namedBeanReference->at(index.row());

        switch (index.column()) {
            case COLUMN_BEAN_TYPE:
        {
                NamedBeanType::TYPE oldType = ref->getType();
                ref->setType((NamedBeanType::TYPE)value.toInt());
                if (oldType != ref->getType()) ref->setName("");
                break;
        }
            case COLUMN_BEAN_NAME:
                ref->setName( value.toString());
                break;
            case COLUMN_DELETE:
                _delete(index.row());
                break;
            case COLUMN_DUMMY:
                break;
            default:
                throw new IllegalArgumentException("Invalid column");
        }
     }
     return false;

    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QVariant ListenOnBeansTableModel::data(const QModelIndex &index, int role) const {
     if(role == Qt::DisplayRole)
     {
        if (index.row() >= _namedBeanReference->size()) throw new IllegalArgumentException("Invalid row");

        switch (index.column()) {
            case COLUMN_BEAN_TYPE:
                return _namedBeanReference->at(index.row())->getType();
            case COLUMN_BEAN_NAME:
                return _namedBeanReference->at(index.row())->getName();
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

    /*public*/  void ListenOnBeansTableModel::setColumnsForComboBoxes(JTable* table) {
        JComboBox/*<NamedBeanType>*/* beanTypeComboBox = new JComboBox();
//        table->setRowHeight(beanTypeComboBox.getPreferredSize().height);
        table->getColumnModel()->getColumn(COLUMN_BEAN_TYPE)
                ->setPreferredWidth((beanTypeComboBox->sizeHint().width()) + 4);
    }

    /*public*/  void ListenOnBeansTableModel::add() {
        int row = _namedBeanReference->size();
        _namedBeanReference->append(new ActionListenOnBeans::NamedBeanReference("", NamedBeanType::Turnout));
        fireTableRowsInserted(row, row);
    }

    /*private*/ void ListenOnBeansTableModel::_delete(int row) {
        _namedBeanReference->removeAt(row);
        fireTableRowsDeleted(row, row);
    }

    /*public*/  QList<ActionListenOnBeans::NamedBeanReference*>* ListenOnBeansTableModel::getReferences() {
        return _namedBeanReference;
    }

    #if 0
    /*public*/  static class CellRenderer extends DefaultTableCellRenderer {

        //@Override
        /*public*/  Component getTableCellRendererComponent(JTable table, Object value,
                bool isSelected, bool hasFocus, int row, int column) {

            if (column == COLUMN_BEAN_TYPE) {
                if (value == null) value = NamedBeanType.Turnout;

                if (! (value instanceof NamedBeanType)) {
                    throw new IllegalArgumentException("value is not an NamedBeanType: " + value.getClass().getName());
                }
                setText(((NamedBeanType) value).toString());
            } else {
                throw new RuntimeException("Unknown column: "+Integer.toString(column));
            }
            return this;
        }
    }


    /*public*/  static class NamedBeanTypeCellEditor extends AbstractCellEditor
            implements TableCellEditor, ActionListener {

        /*private*/ NamedBeanType _beanType;

        //@Override
        /*public*/  Object getCellEditorValue() {
            return this._beanType;
        }

        //@Override
        /*public*/  Component getTableCellEditorComponent(JTable table, Object value,
                bool isSelected, int row, int column) {

            if (value == null) value = NamedBeanType.Turnout;

            if (! (value instanceof NamedBeanType)) {
                throw new IllegalArgumentException("value is not an NamedBeanType: " + value.getClass().getName());
            }

            JComboBox<NamedBeanType> returnValueTypeComboBox = new JComboBox<>();

            for (NamedBeanType type : NamedBeanType.values()) {
                returnValueTypeComboBox.addItem(type);
            }
            JComboBoxUtil.setupComboBoxMaxRows(returnValueTypeComboBox);

            returnValueTypeComboBox.setSelectedItem(value);
            returnValueTypeComboBox.addActionListener(this);

            return returnValueTypeComboBox;
        }

        //@Override
        @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<NamedBeanType>
        /*public*/  void actionPerformed(ActionEvent event) {
            if (! (event.getSource() instanceof JComboBox)) {
                throw new IllegalArgumentException("value is not an JComboBox: " + event.getSource().getClass().getName());
            }
            JComboBox<NamedBeanType> returnValueTypeComboBox =
                    (JComboBox<NamedBeanType>) event.getSource();
            _beanType = returnValueTypeComboBox.getItemAt(returnValueTypeComboBox.getSelectedIndex());

        }

    }


    /*public*/  NamedBeanCellEditor getNamedBeanCellEditor() {
        return new NamedBeanCellEditor();
    }


    /*public*/  class NamedBeanCellEditor extends AbstractCellEditor
            implements TableCellEditor, ActionListener {

        /*private*/ String _namedBean;

        //@Override
        /*public*/  Object getCellEditorValue() {
            return this._namedBean;
        }

        //@Override
        /*public*/  Component getTableCellEditorComponent(JTable table, Object value,
                bool isSelected, int row, int column) {

            if ((value != null) && (! (value instanceof String))) {
                throw new IllegalArgumentException("value is not a String: " + value.getClass().getName());
            }

            JComboBox<String> namedBeanComboBox = new JComboBox<>();
            SortedSet<? extends NamedBean> set =
                    _namedBeanReference.get(row).getType().getManager().getNamedBeanSet();

            String name = _namedBeanReference.get(row).getName();

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
        @SuppressWarnings("unchecked")  // Not possible to check that event.getSource() is instanceof JComboBox<NamedBeanType>
        /*public*/  void actionPerformed(ActionEvent event) {
            if (! (event.getSource() instanceof JComboBox)) {
                throw new IllegalArgumentException("value is not an JComboBox: " + event.getSource().getClass().getName());
            }
            JComboBox<String> namedBeanComboBox = (JComboBox<String>) event.getSource();
            int index = namedBeanComboBox.getSelectedIndex();
            _namedBean = (index != -1) ? namedBeanComboBox.getItemAt(index) : null;
        }

    }
    #endif
