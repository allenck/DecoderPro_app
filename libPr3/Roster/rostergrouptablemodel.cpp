#include "rostergrouptablemodel.h"
#include "roster.h"
#include "jtextfield.h"
#include "logger.h"
#include "rosterentry.h"
#include <QTableView>

RosterGroupTableModel::RosterGroupTableModel(QObject *parent) :
  AbstractTableModel(parent)
{
 group = "RosterGroup:";
 log = new Logger("RosterGroupTableModel");

}
/**
 * Table data model for display of Rosters entries to a specific Roster Group.
 * <P>
 * Any desired ordering, etc, is handled outside this class.
 * <P>
 * The initial implementation doesn't automatically update when roster entries
 * change, it only allows the setting of a roster entry, to a roster group.
 * Based Upon RosterTableModel
 *
 * @author Bob Jacobsen Copyright (C) 2009
 * @author Kevin Dickerson Copyright (C) 2009
 * @version $Revision: 28746 $
 * @since 2.7.5
 */
// /*public*/ class RosterGroupTableModel extends javax.swing.table.AbstractTableModel {

/**
 *
 */
//private static final long serialVersionUID = 7420154419304239909L;


/*static*/ /*final*/ int RosterGroupTableModel::NUMCOL = ADDTOGROUPCOL + 1;

/*public*/ int RosterGroupTableModel::rowCount(const QModelIndex &parent) const
{
 return Roster::instance()->numEntries();
}

/*public*/ int RosterGroupTableModel::columnCount(const QModelIndex &parent) const
{
 return NUMCOL;
}

/*public*/ QVariant RosterGroupTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case IDCOL:
            return "ID";
        case ROADNUMBERCOL:
            return "Road Number";
        case ROADNAMECOL:
            return "Road Name";
        case MFGCOL:
            return "Manufacturer";
        case ADDTOGROUPCOL:
            return "Include";
        case OWNERCOL:
            return "Owner";
        default:
            return "<UNKNOWN>";
    }
 }
 return QVariant();
}

/*public*/ int RosterGroupTableModel::getPreferredWidth(int col) {
    switch (col) {
        case IDCOL:
     return JTextField(10).getPreferredSize().width();
        case ROADNUMBERCOL:
            return 75;
        case ROADNAMECOL:
     return  JTextField(20).getPreferredSize().width();
        case OWNERCOL:
     return  JTextField(20).getPreferredSize().width();
        case ADDTOGROUPCOL: // not actually used due to the configureTable, setColumnToHoldButton, configureButton
            return 50;
        case MFGCOL:
     return JTextField(5).getPreferredSize().width();
        default:
            //log->warn("Unexpected column in getPreferredWidth: "+col);
     return JTextField(8).getPreferredSize().width();
    }
}

///*public*/ Class<?> getColumnClass(int col) {
//    if (col == ADDTOGROUPCOL) {
//        return Boolean.class;
//    } else {
//        return String.class;
//    }
//}

/**
 * This implementation can't edit the values yet
 */
/*public*/ bool RosterGroupTableModel::isCellEditable(int row, int col) {
    switch (col) {
        case ADDTOGROUPCOL:
            return true;
        default:
            return false;
    }
}

/**
 * Provides the empty String if attribute doesn't exist.
 */
/*public*/ QVariant RosterGroupTableModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
    // get roster entry for row
  int row = index.row();
    RosterEntry* re = Roster::instance()->getEntry(row);
    if (re == NULL)
    {
        log->debug("roster entry is NULL!");
        return "Error";
    }
    int col = index.column();
    switch (col) {
        case IDCOL:
            return re->getId();
        case ROADNUMBERCOL:
            return re->getRoadNumber();
        case ROADNAMECOL:
            return re->getRoadName();
        case MFGCOL:
            return re->getMfg();
        case OWNERCOL:
            return re->getOwner();
        case ADDTOGROUPCOL:
            if (group == NULL) {
                return false;
            } else {
                if (re->getAttribute(group) != NULL) {
                    return true;
                } else {
                    return false;
                }
            }
        default:
            return "<UNKNOWN>";
    }
 }
 return QVariant();
}

/*public*/ void RosterGroupTableModel::configureTable(QTableView* table) {
    // allow reordering of the columns
    //table.getTableHeader().setReorderingAllowed(true);

    // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
    //table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

    // resize columns as requested
    for (int i = 0; i < table->model()->columnCount(); i++) {
        int width = getPreferredWidth(i);
        table->setColumnWidth(i, width);
    }
    table->resizeColumnsToContents();
    //setUpRosterIdCol(table.getColumnModel().getColumn(3));
    //configAddToRosterColumn(table); Remarked out until the code for the add to roster has been completed

}

/*synchronized*/ /*public*/ void RosterGroupTableModel::dispose() {
    //This needs to be sorted later.
    //getManager().removePropertyChangeListener(this);
}

/*public*/ bool RosterGroupTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
  RosterEntry* re = Roster::instance()->getEntry(row);
    if ((col == ADDTOGROUPCOL) && (group!=("RosterGroup:"))) {
        if (value.toString()==("true")) {
            re->putAttribute(group, "yes");
        } else {
            re->deleteAttribute(group);
        }
        re->updateFile();
        Roster::writeRosterFile();

    }
    //re.updateFile();
    //Roster.instance().writeRosterFile();
 }
 return false;
}

/*public*/ void RosterGroupTableModel::setGroup(QString grp) {
    group = grp;
}

/*public*/ void RosterGroupTableModel::getGroupEnabled(RosterEntry* re) {

}
