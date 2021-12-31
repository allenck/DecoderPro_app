#include "routeblockingorderedittablemodel.h"
#include "loggerfactory.h"
#include "routelocation.h"
#include "xtablecolumnmodel.h"
#include "logger.h"
#include "control.h"

namespace Operations {

/**
 * Table Model for edit of route blocking used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2021
 */
// /*public*/  class RouteBlockingOrderEditTableModel extends javax.swing.table->AbstractTableModel implements PropertyChangeListener {

    // Defines the columns

    /*public*/  RouteBlockingOrderEditTableModel::RouteBlockingOrderEditTableModel(QObject* parent) :AbstractTableModel(parent) {
        //super();
    log = new Logger("RouteBlockingOrderEditTableModel");
    }

    /*private*/ void RouteBlockingOrderEditTableModel::updateList() {
        if (_route == nullptr) {
            return;
        }
        // first, remove listeners from the individual objects
        removePropertyChangeRouteLocations();
        _blockingOrderList = _route->getBlockingOrder();
        // and add them back in
        for (RouteLocation* rl : _blockingOrderList) {
            rl->addPropertyChangeListener(this);
        }
    }

    /*protected*/ void RouteBlockingOrderEditTableModel::initTable(RouteBlockingOrderEditFrame* frame, JTable* table, Route* route) {
        _frame = frame;
        _table = table;
        if(table->getModel() == nullptr)
         _table->setModel(this);
        _route = route;
        if (_route != nullptr) {
            _route->addPropertyChangeListener(this);
        }
        this->initTable(table);
    }

    /*private*/ void RouteBlockingOrderEditTableModel::initTable(JTable* table) {
        // Use XTableColumnModel so we can control which columns are visible
        XTableColumnModel* tcm = new XTableColumnModel(table);
        _table->setColumnModel(tcm);
        _table->createDefaultColumnsFromModel();
        // Install the button handlers
        ButtonRenderer* buttonRenderer = new ButtonRenderer();
        TableCellEditor* buttonEditor = new ButtonEditor(new JButton());
        tcm->getColumn(UP_COLUMN)->setCellRenderer(buttonRenderer);
        tcm->getColumn(UP_COLUMN)->setCellEditor(buttonEditor);
        table->setItemDelegateForColumn(UP_COLUMN,new PushButtonDelegate());
        tcm->getColumn(DOWN_COLUMN)->setCellRenderer(buttonRenderer);
        tcm->getColumn(DOWN_COLUMN)->setCellEditor(buttonEditor);
        table->setItemDelegateForColumn(DOWN_COLUMN,new PushButtonDelegate());
        table->setDefaultRenderer("JComboBox", new ValueRenderer());
//        table->setDefaultEditor("JComboBox", new ValueEditor());

        // set column preferred widths
        table->getColumnModel()->getColumn(ID_COLUMN)->setPreferredWidth(40);
        table->getColumnModel()->getColumn(NAME_COLUMN)->setPreferredWidth(150);
        table->getColumnModel()->getColumn(TRAIN_DIRECTION_COLUMN)->setPreferredWidth(95);
        table->getColumnModel()->getColumn(UP_COLUMN)->setPreferredWidth(60);
        table->getColumnModel()->getColumn(DOWN_COLUMN)->setPreferredWidth(70);

        //_frame->loadTableDetails(table);
        // does not use a table sorter
        table->setRowSorter(nullptr);

        updateList();
        fireTableDataChanged();
    }

    //@Override
    /*public*/  int RouteBlockingOrderEditTableModel::rowCount(const QModelIndex &/*parent*/) const{
        return _blockingOrderList.size();
    }

    //@Override
    /*public*/  int RouteBlockingOrderEditTableModel::columnCount(const QModelIndex & /*parent*/) const {
        return HIGHEST_COLUMN;
    }

    //@Override
    /*public*/  QVariant RouteBlockingOrderEditTableModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
     if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
     {
        switch (section) {
            case ID_COLUMN:
                return tr("Id");
            case NAME_COLUMN:
                return tr("Location");
            case TRAIN_DIRECTION_COLUMN:
                return tr("Train Direction");
            case UP_COLUMN:
                return tr("Up");
            case DOWN_COLUMN:
                return tr("Down");
            default:
                return "unknown"; // NOI18N
        }
     }
     return QVariant();
    }

    //@Override
    /*public*/  QString  RouteBlockingOrderEditTableModel::getColumnClass(int col) const{
        switch (col) {
            case ID_COLUMN:
            case NAME_COLUMN:
            case TRAIN_DIRECTION_COLUMN:
                return "String";
            case UP_COLUMN:
            case DOWN_COLUMN:
                return "JButton";
            default:
                return "";
        }
    }

    //@Override
    /*public*/  Qt::ItemFlags RouteBlockingOrderEditTableModel::flags(const QModelIndex &index) const {
        switch (index.column()) {
            case UP_COLUMN:
            case DOWN_COLUMN:
                return Qt::ItemIsEnabled | Qt::ItemIsEditable;
            default:
                return Qt::ItemIsEnabled;
        }
    }

    //@Override
    /*public*/  QVariant RouteBlockingOrderEditTableModel::data(const QModelIndex &index, int role) const {
        int row = index.row();
//        if (row >= rowCount()) {
//            return "ERROR unknown " + QString::number(row); // NOI18N
//        }
        RouteLocation* rl = _blockingOrderList.at(row);
        if (rl == nullptr) {
            return "ERROR unknown route location " + QString::number(row); // NOI18N
        }
        if(role == Qt::DisplayRole)
        {
         switch (index.column()) {
            case ID_COLUMN:
                return rl->getId();
            case NAME_COLUMN:
                return rl->getName();
            case TRAIN_DIRECTION_COLUMN: {
                return rl->getTrainDirectionString();
            }
            case UP_COLUMN:
                return tr("Up");
            case DOWN_COLUMN:
                return tr("Down");
            default:
                return "unknown " + QString::number(index.column()); // NOI18N
         }
        }
        return QVariant();
    }

    //@Override
    /*public*/  bool RouteBlockingOrderEditTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
//        if (value == null) {
//            log.debug("Warning route table row {} still in edit", row);
//            return;
//        }
    if(role == Qt::EditRole)
    {
        int row = index.row();
        RouteLocation* rl = _blockingOrderList.at(row);
        if (rl == nullptr) {
            log->error(tr("ERROR unknown route location for row: %1").arg(row)); // NOI18N
        }
        switch (index.column()) {
            case UP_COLUMN:
                moveUpRouteLocation(rl);
                break;
            case DOWN_COLUMN:
                moveDownRouteLocation(rl);
                break;
            default:
                break;
        }
     }
    }

    /*private*/ void RouteBlockingOrderEditTableModel::moveUpRouteLocation(RouteLocation* rl) {
        log->debug("move location up");
        _route->setBlockingOrderUp(rl);
    }

    /*private*/ void RouteBlockingOrderEditTableModel::moveDownRouteLocation(RouteLocation* rl) {
        log->debug("move location down");
        _route->setBlockingOrderDown(rl);
    }

    // this table listens for changes to a route and it's locations
    //@Override
    /*public*/  void RouteBlockingOrderEditTableModel::propertyChange(PropertyChangeEvent* e) {
        if (Control::SHOW_PROPERTY) {
            log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName(), e->getOldValue().toString(), e
                    ->getNewValue().toString()));
        }
        if (e->getPropertyName() == (Route::ROUTE_BLOCKING_CHANGED_PROPERTY)) {
            updateList();
            fireTableDataChanged();
        }

        if (QString(e->getSource()->metaObject()->className()) ==("RouteLocation")) {
            RouteLocation* rl = (RouteLocation*) e->getSource();
            int row = _blockingOrderList.indexOf(rl);
            if (Control::SHOW_PROPERTY) {
                log->debug(tr("Update route table row: %1 id: %2").arg(row).arg(rl->getId()));
            }
            if (row >= 0) {
                fireTableRowsUpdated(row, row);
            }
        }
    }

    /*private*/ void RouteBlockingOrderEditTableModel::removePropertyChangeRouteLocations() {
        for (RouteLocation* rl : _blockingOrderList) {
            rl->removePropertyChangeListener(this);
        }
    }

    /*public*/  void RouteBlockingOrderEditTableModel::dispose() {
        removePropertyChangeRouteLocations();
        if (_route != nullptr) {
            _route->removePropertyChangeListener(this);
        }
        _blockingOrderList.clear();
        fireTableDataChanged();
    }


} // namespace Operations
///*private*/ /*final*/ /*static*/ Logger* log = LoggerFactory::getLogger("RouteBlockingOrderEditTableModel");
