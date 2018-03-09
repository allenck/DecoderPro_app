#include "sprogslotmondatamodel.h"
#include "loggerfactory.h"
#include "jtextfield.h"
#include <QLabel>
#include "jtable.h"

using namespace Sprog;
/**
 * Table data model for display of slot manager contents.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @author  Andrew Crosland (C) 2006 ported to SPROG
 */
///*public*/ class SprogSlotMonDataModel extends javax.swing.table.AbstractTableModel implements SprogSlotListener {


SprogSlotMonDataModel::SprogSlotMonDataModel(int row, int column,SprogSystemConnectionMemo* memo, QObject* parent ) : AbstractTableModel(parent){
    _memo = memo;
    // connect to SprogSlotManager for updates
    _memo->getCommandStation()->addSlotListener((SprogSlotListener*)this);
    // methods for control of "all slots" vs "only active slots"
     _allSlots = true;

}

/**
 * Return the number of rows to be displayed. This can vary depending on
 * whether only active rows are displayed.
 * <p>
 * This should probably use a local cache instead of counting/searching each
 * time.
 */
//@Override
/*public*/ int SprogSlotMonDataModel::rowCount(const QModelIndex &/*parent*/) const
{

    int nMax = SprogConstants::MAX_SLOTS;
    if (_allSlots) {
        // will show the entire set, so don't bother counting
        return nMax;
    }
    int n = 0;
    int nMin = 0;
    for (int i = nMin; i < nMax; i++) {
        SprogSlot* s = _memo->getCommandStation()->slot(i);
        if (s->isFree() != true) {
            n++;
        }
    }
    return n;
}

//@Override
/*public*/ int SprogSlotMonDataModel::columnCount(const QModelIndex &parent) const
{
    return NUMCOLUMN;
}

//@Override
/*public*/ QVariant SprogSlotMonDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case SLOTCOLUMN:
            return tr("SlotCol");
//        case ESTOPCOLUMN: return "";     // no heading, as button is clear
        case ADDRCOLUMN:
            return tr("AddressCol");
        case SPDCOLUMN:
            return tr("SpeedCol");
        case STATCOLUMN:
            return tr("StatusCol");
//        case CONSCOLUMN: return "Consisted";
        case DIRCOLUMN:
            return tr("DirectionCol");
//        case DISPCOLUMN: return "";     // no heading, as button is clear
        default:
            return "unknown"; // NOI18N
    }
 }
 return QVariant();
}

//@Override
///*public*/ Class<?> getColumnClass(int col) {
//    switch (col) {
//        case SLOTCOLUMN:
//        case ADDRCOLUMN:
//        case SPDCOLUMN:
//        case STATCOLUMN:
////        case CONSCOLUMN:
//        case DIRCOLUMN:
//            return String.class;
////        case ESTOPCOLUMN:
////        case DISPCOLUMN:
////            return JButton.class;
//        default:
//            return NULL;
//    }
//}

//@Override
/*public*/ Qt::ItemFlags SprogSlotMonDataModel::flags(const QModelIndex &index) const
{
//    switch (col) {
////        case ESTOPCOLUMN:
////        case DISPCOLUMN:
////            return true;
//        default:
//            return false;
//    }
 return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

#if 0
static /*final*/ bool True = Boolean.valueOf("True");
static /*final*/ bool False = Boolean.valueOf("False");
#endif

//@SuppressWarnings("NULL")
//@Override
/*public*/ QVariant SprogSlotMonDataModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  int row = index.row();
  int col = index.column();
  SprogSlot* s = _memo->getCommandStation()->slot(slotNum(row));
  if (s == NULL)
  {
   log->error("slot pointer was NULL for slot row: " + QString::number(row) + " col: " + QString::number(col));
  }

    switch (col) {
        case SLOTCOLUMN:  // slot number
            return (slotNum(row));
//        case ESTOPCOLUMN:  //
//            return "E Stop";          // will be name of button in default GUI
        case ADDRCOLUMN:  //
                switch (s->slotStatus()) {
                    case SprogConstants::SLOT_IN_USE:
                        return QString::number(s->getAddr()) + "("+ (s->getIsLong() ? tr("LongAddressChar") : tr("ShortAddressChar")) + ")";
                    case SprogConstants::SLOT_FREE:
                        return "-";
                    default:
                        return tr("StateError");
                }
        case SPDCOLUMN:  //
            switch (s->slotStatus()) {
                case SprogConstants::SLOT_IN_USE:
                    if (s->isF0to4Packet()) {
                        return "F0to4Pkt";
                    } else if (s->isF5to8Packet()) {
                        return "F5to8Pkt";
                    } else if (s->isF9to12Packet()) {
                        return "F9to12Pkt";
                    } else if (s->isOpsPkt()) {
                        return "OpsPkt";
                    } else if (s->isSpeedPacket()) {
                        QString t;
                        if (s->speed() == 1) {
                            t = "(estop) 1";
                        } else {
                            t = "          " + s->speed();
                        }
                        return t.mid(t.length() - 9, t.length()); // 9 comes from (estop)
                    } else {
                      return tr("StateError");
                    }
                case SprogConstants::SLOT_FREE:
                    return "-";
                default:
                    return tr("StateError");
            }
        case STATCOLUMN:  //
            switch (s->slotStatus()) {
                case SprogConstants::SLOT_IN_USE:
                    return tr("StateInUse");
                case SprogConstants::SLOT_FREE:
                    return tr("StateFree");
                default:
                    return tr("StateError");
            }
//        case CONSCOLUMN:  //
//            return "<n/a>";
//        case DISPCOLUMN:  //
//            return tr("ButtonRelease"); // will be name of button in default GUI
        case DIRCOLUMN:  //
                switch (s->slotStatus()) {
                    case SprogConstants::SLOT_IN_USE:
                        if (s->isSpeedPacket()) {
                            return (s->isForward() ? tr("DirColForward") : tr("DirColReverse"));
                        } else {
                            return "-";
                        }
                    case SprogConstants::SLOT_FREE:
                        return "-";
                    default:
                        return tr("StateError");
                }

        default:
            log->error(tr("internal state inconsistent with table request for row %1, col %2").arg(row).arg(col));
            return QVariant();
    }
 }
 return QVariant();
}

//@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "DB_DUPLICATE_SWITCH_CLAUSES",
//                    justification="better to keep cases in column order rather than to combine")
/*public*/ int SprogSlotMonDataModel::getPreferredWidth(int col) {
    switch (col) {
        case SLOTCOLUMN:
            return  JTextField(3).getPreferredSize().width();
//        case ESTOPCOLUMN:
//            return new JButton("E Stop").getPreferredSize().width;
        case ADDRCOLUMN:
            return JTextField(5).getPreferredSize().width();
        case SPDCOLUMN:
            return JTextField(6).getPreferredSize().width();
        case STATCOLUMN:
            return JTextField(6).getPreferredSize().width();
//        case CONSCOLUMN:
//            return new JTextField(4).getPreferredSize().width;
        case DIRCOLUMN:
            return JTextField(3).getPreferredSize().width();
//        case DISPCOLUMN:
//            return new JButton(tr("ButtonRelease")).getPreferredSize().width;
        default:
            return QLabel(" <unknown> ").sizeHint().width(); // NOI18N
    }
}

//@Override
/*public*/ bool SprogSlotMonDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  int row = index.row();
  int col = index.column();
    // check for in use
    SprogSlot* s = _memo->getCommandStation()->slot(slotNum(row));
    if (s == NULL) {
        log->error("slot pointer was NULL for slot row: " + QString::number(row) + " col: " + QString::number(col));
        return true;
    }
//        if (col == ESTOPCOLUMN) {
//            log->debug("Start eStop in slot "+row);
//            _memo.getSlotManager().estopSlot(row);
//        }
//        else if (col == DISPCOLUMN) {
//            log->debug("Start freeing slot {}", row);
//            fireTableRowsUpdated(row,row);
//        }
 }
 return false;
}

/**
 * Configure a table to have our standard rows and columns. This is
 * optional, in that other table formats can use this table model. But we
 * put it here to help keep it consistent.
 *
 */
/*public*/ void SprogSlotMonDataModel::configureTable(JTable* slotTable) {
    // allow reordering of the columns
//    slotTable.getTableHeader().setReorderingAllowed(true);

    // shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
//    slotTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

    // resize columns as requested
//    for (int i = 0; i < slotTable->col(); i++) {
//        int width = getPreferredWidth(i);
//        slotTable.getColumnModel().getColumn(i).setPreferredWidth(width);
//    }
//    slotTable.sizeColumnsToFit(-1);
 slotTable->resizeColumnsToContents();

//        // install a button renderer & editor in the "DISP" column for freeing a slot
//        setColumnToHoldButton(slotTable, SprogSlotMonDataModel.DISPCOLUMN);
//
//        // install a button renderer & editor in the "ESTOP" column for stopping a loco
//        setColumnToHoldEStopButton(slotTable, SprogSlotMonDataModel.ESTOPCOLUMN);
}

//    void setColumnToHoldButton(JTable slotTable, int column) {
//        TableColumnModel tcm = slotTable.getColumnModel();
//        // install the button renderers & editors in this column
//        ButtonRenderer buttonRenderer = new ButtonRenderer();
//        tcm.getColumn(column).setCellRenderer(buttonRenderer);
//        TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//        tcm.getColumn(column).setCellEditor(buttonEditor);
//        // ensure the table rows, columns have enough room for buttons
//        slotTable.setRowHeight(new JButton("  "+getValueAt(1, column)).getPreferredSize().height);
//        slotTable.getColumnModel().getColumn(column)
//			.setPreferredWidth(new JButton("  "+getValueAt(1, column)).getPreferredSize().width);
//    }
//
//    void setColumnToHoldEStopButton(JTable slotTable, int column) {
//        TableColumnModel tcm = slotTable.getColumnModel();
//        // install the button renderers & editors in this column
//        ButtonRenderer buttonRenderer = new ButtonRenderer();
//        tcm.getColumn(column).setCellRenderer(buttonRenderer);
//        TableCellEditor buttonEditor = new ButtonEditor(new JButton()){
//            /*public*/ void mousePressed(MouseEvent e) {
//                stopCellEditing();
//            }
//        };
//        tcm.getColumn(column).setCellEditor(buttonEditor);
//        // ensure the table rows, columns have enough room for buttons
//        slotTable.setRowHeight(new JButton("  "+getValueAt(1, column)).getPreferredSize().height);
//        slotTable.getColumnModel().getColumn(column)
//			.setPreferredWidth(new JButton("  "+getValueAt(1, column)).getPreferredSize().width);
//    }
// methods to communicate with SprogSlotManager
//@Override
/*public*/ /*synchronized*/ void SprogSlotMonDataModel::notifyChangedSlot(SprogSlot* s) {
    // update model from this slot

    int slotNum = -1;
    if (_allSlots) {          // this will be row until we show only active slots
        slotNum = s->getSlotNumber();  // and we are displaying the System slots
    }
    log->debug("Received notification of changed slot: " + slotNum);
    // notify the JTable object that a row has changed; do that in the Swing thread!
#if 0 // TODO:
    Runnable r = new Notify(slotNum, this);   // -1 in first arg means all
    javax.swing.SwingUtilities.invokeLater(r);
#endif
}
#if 0
static class Notify implements Runnable {

    /*private*/ int _row;
    javax.swing.table.AbstractTableModel _model;

    /*public*/ Notify(int row, javax.swing.table.AbstractTableModel model) {
        _row = row;
        _model = model;
    }

    @Override
    /*public*/ void run() {
        if (-1 == _row) {  // notify about entire table
            _model.fireTableDataChanged();  // just that row
        } else {
            // notify that _row has changed
            _model.fireTableRowsUpdated(_row, _row);  // just that row
        }
    }
};
#endif

/*public*/ void SprogSlotMonDataModel::showAllSlots(bool val) {
    _allSlots = val;
}

/**
 * Return slot number for a specific row.
 * <p>
 * This should probably use a local cache instead of counting/searching each
 * time.
 *
 * @param row Row number in the displayed table
 */
/*protected*/ int SprogSlotMonDataModel::slotNum(int row) const {
    // ??? Can't this just return row ???
    int slotNum;
    int n = -1;   // need to find a used slot to have the 0th one!
    int nMin = 0;
    int nMax = SprogConstants::MAX_SLOTS;
    for (slotNum = nMin; slotNum < nMax; slotNum++) {
        SprogSlot* s = _memo->getCommandStation()->slot(slotNum);
        if (_allSlots || s->slotStatus() != SprogConstants::SLOT_FREE) {
            n++;
        }
        if (n == row) {
            break;
        }
    }
    return slotNum;
}

/*public*/ void SprogSlotMonDataModel::dispose() {
    _memo->getCommandStation()->removeSlotListener((SprogSlotListener*)this);
    // table.removeAllElements();
    // table = NULL;
}

/*private*/ /*final*/ /*static*/ Logger* SprogSlotMonDataModel::log = LoggerFactory::getLogger("SprogSlotMonDataModel");
