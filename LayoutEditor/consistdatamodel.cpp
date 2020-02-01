#include "consistdatamodel.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "tablecolumnmodel.h"
#include "jtable.h"
#include "dcclocoaddress.h"

/**
 * Table data model for display of consist information.
 *
 * @author Paul Bender Copyright (c) 2004-2005
 */
///*public*/ class ConsistDataModel extends AbstractTableModel {


// Construct a new instance
ConsistDataModel::ConsistDataModel(QObject* parent) {
    consistMan = qobject_cast<AbstractConsistManager*>(InstanceManager::getDefault("ConsistManager"));
}

void ConsistDataModel::initTable(JTable* consistTable) {
    // Install the button handlers for the Delete Buttons
    TableColumnModel* tcm = consistTable->getColumnModel();
#if 0
    ButtonRenderer buttonRenderer = new ButtonRenderer();
    tcm->getColumn(DELCOLUMN).setCellRenderer(buttonRenderer);
    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
    tcm.getColumn(DELCOLUMN).setCellEditor(buttonEditor);
#endif
}

/*public*/ void ConsistDataModel::setConsist(Consist* consist) {
    log->debug("Setting Consist");
    _consist = consist;
    fireTableDataChanged();
}

/*public*/ void ConsistDataModel::setConsist(DccLocoAddress* address) {
    log->debug(tr("Setting Consist using address: %1").arg(address->toString()));
    _consist = consistMan->getConsist(address);
    fireTableDataChanged();
}

/*public*/ Consist* ConsistDataModel::getConsist() {
    return _consist;
}

//@Override
/*public*/ int ConsistDataModel::getRowCount() const
{
 try
 {
  if(_consist == nullptr) throw NullPointerException();
  return (_consist->getConsistList().size());
 } catch (NullPointerException e) {
     return (0);
 }
}

//@Override
/*public*/ int ConsistDataModel::getColumnCount() const {
    return NUMCOLUMN;
}

//@Override
/*public*/ QString ConsistDataModel::getColumnName(int col) const {
    switch (col) {
        case ADDRCOLUMN:
            return tr("Address");
        case ROSTERCOLUMN:
            return tr("Roster");
        case DIRECTIONCOLUMN:
            return tr("Direction");
        default:
            return "";
    }
}
#if 1
//@Override
/*public*/ QString ConsistDataModel::getColumnClass(int col) const {
    switch (col) {
        case ROSTERCOLUMN:
            return ("String");
        case DELCOLUMN:
            return ("JButton");
        case DIRECTIONCOLUMN:
            return ("Boolean");
        default:
            return ("String");
    }
}
#endif
//@Override
/*public*/ bool ConsistDataModel::isCellEditable(int row, int col) {
    log->debug(tr("isCellEditable called for row: %1 column: %2").arg(row).arg(col));
    if (col == DELCOLUMN) {
        return (true);
    } else if (row != 0 && col == DIRECTIONCOLUMN) {
        return (true);
    } else {
        return (false);
    }
}

//@Override
/*public*/ QVariant ConsistDataModel::getValueAt(int row, int col) const
{
    log->debug(tr("getValueAt called for row: %1 column: %2").arg(row).arg(col));
    if (_consist == nullptr) {
        log->debug("Consist not defined");
        return (QVariant());
    }
    // some error checking
    if (row >= _consist->getConsistList().size()) {
        log->debug("row is greater than consist list size");
        return QVariant();
    }
    switch (col) {
        case ADDRCOLUMN:
            return (_consist->getConsistList().at(row)->toString());
        case ROSTERCOLUMN:
            return _consist->getRosterId(_consist->getConsistList().at(row));
        case DIRECTIONCOLUMN:
            return _consist->getLocoDirection(_consist->getConsistList().at(row))?"true":"false";
        case DELCOLUMN:
            return tr("Delete");
        default:
            return ("");
    }
}

//@Override
/*public*/ void ConsistDataModel::setValueAt(QVariant value, int row, int col) {
    log->debug(tr("setValueAt called for row: %1 column: %2").arg(row).arg(col));
    if (_consist == nullptr) {
        return;
    }
    switch (col) {
        case DIRECTIONCOLUMN:
            _consist->add(_consist->getConsistList().at(row),  value.toBool());
            fireTableDataChanged();
            break;
        case DELCOLUMN:
            log->debug(tr("Delete Called for row %1").arg(row));
            fireTableRowsDeleted(row, row);
            _consist->remove(_consist->getConsistList().at(row));
            fireTableDataChanged();
            break;
        default:
            log->error("Unknown Consist Operation");
    }
}
/*private*/ /*static*/ /*final*/ Logger* ConsistDataModel::log = LoggerFactory::getLogger("ConsistDataModel");

