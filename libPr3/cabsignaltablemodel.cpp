#include "cabsignaltablemodel.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultcabsignalmanager.h"
#include "jtextfield.h"
#include "jtable.h"
#include "tablecolumnmodel.h"
#include "tablecolumn.h"
#include "signalmast.h"
#include "block.h"
#include "path.h"

/**
 * Table data model for display of Cab Signaling information.
 *
 * @author Steve Young (c) 2018
 * @author Paul Bender (c) 2018
 * @see CabSignalPane
 * @since 4.13.4
 */
// /*public*/ class CabSignalTableModel extends javax.swing.table.AbstractTableModel {



/*static*/ /*protected*/ /*final*/ QVector<int> CabSignalTableModel::startupColumns = {0,1,2,3,4,5,6,7,8};

CabSignalTableModel::CabSignalTableModel(int /*row*/, int /*column*/, QObject */*parent*/)
{
 cabSignalManager = (DefaultCabSignalManager*)InstanceManager::getNullableDefault("CabSignalManager");
 if(cabSignalManager == nullptr){
    log->info("creating new DefaultCabSignalManager");
    InstanceManager::store(new DefaultCabSignalManager(), "CabSignalManager");
    cabSignalManager = (DefaultCabSignalManager*)InstanceManager::getNullableDefault("CabSignalManager");
 }
}

// order needs to match column list top of dtabledatamodel
/*static*/ /*protected*/ /*final*/QStringList CabSignalTableModel::columnToolTips = {
    "", // loco id
    tr("Data send will also be paused by the master Pause / Resume button"),
    tr("Block Username"),
    tr("North / South / East / West, 8 point block direction"),
    "", // block lookup button
    tr("Next block in direction from current block"),
    tr("Next signal found"),
    tr("Aspect of next signal"),
    tr("Aspect of next signal"), // aspect icon

}; // Length = number of items in array should (at least) match number of columns

/**
 * Return the number of rows to be displayed.
 */
//@Override
/*public*/ int CabSignalTableModel::getRowCount() const {
    return cabSignalManager->getCabSignalList().size();
}

//@Override
/*public*/ int CabSignalTableModel::getColumnCount() const {
    return MAX_COLUMN;
}

/**
 * Returns String of column name from column int
 * used in table header.
 *
 * @param col int col number
 */
//@Override
/*public*/ QString CabSignalTableModel::getColumnName(int col) const { // not in any order
    switch (col) {
        case LOCO_ID_COLUMN:
            return tr("Loco ID");
        case CURRENT_BLOCK:
            return tr("Block");
        case BLOCK_DIR:
            return tr("Direction of Block");
        case REVERSE_BLOCK_DIR_BUTTON_COLUMN:
            return tr("Lookup");
        case NEXT_BLOCK:
            return tr("Next Block");
        case NEXT_SIGNAL:
            return tr("Next Signal");
        case NEXT_ASPECT:
            return tr("Next Aspect");
        case SEND_CABSIG_COLUMN:
            return tr("Active Cab Signal");
        case NEXT_ASPECT_ICON:
            return tr("Next Aspect");
        default:
            return "unknown"; // NOI18N
    }
}

/**
 * Returns int of startup column widths.
 *
 * @param col int col number
 */
/*public*/ /*static*/ int CabSignalTableModel::getPreferredWidth(int col) {
    switch (col) {
        case LOCO_ID_COLUMN:
            return JTextField(4).getPreferredSize().width();
        case CURRENT_BLOCK:
            return  JTextField(8).getPreferredSize().width();
        case BLOCK_DIR:
            return  JTextField(6).getPreferredSize().width();
        case REVERSE_BLOCK_DIR_BUTTON_COLUMN:
            return  JTextField(10).getPreferredSize().width();
        case NEXT_BLOCK:
            return  JTextField(8).getPreferredSize().width();
        case NEXT_SIGNAL:
            return  JTextField(6).getPreferredSize().width();
        case NEXT_ASPECT:
            return  JTextField(10).getPreferredSize().width();
        case SEND_CABSIG_COLUMN:
            return  JTextField(3).getPreferredSize().width();
        case NEXT_ASPECT_ICON:
            return  JTextField(3).getPreferredSize().width();
        default:
            log->warn(tr("no width found col %1").arg(col));
            return  JTextField(" <unknown> ").getPreferredSize().width(); // NOI18N
    }
}

/**
 * Returns column class type.
 */
//@Override
/*public*/ QString CabSignalTableModel::getColumnClass(int col) const {
    switch (col) {
        case LOCO_ID_COLUMN:
            return "LocoAddress";
        case CURRENT_BLOCK:
            return "String";
        case BLOCK_DIR:
            return "String";
        case REVERSE_BLOCK_DIR_BUTTON_COLUMN:
            return "JButton";
        case NEXT_BLOCK:
            return "String";
        case NEXT_SIGNAL:
            return "String";
        case NEXT_ASPECT:
            return "String";
        case SEND_CABSIG_COLUMN:
            return "Boolean";
        case NEXT_ASPECT_ICON:
            return "String";
        default:
            log->error("no column class located");
            return QString();
    }
}

/**
 * Boolean return to edit table cell or not.
 *
 * @return boolean
 */
//@Override
/*public*/ bool CabSignalTableModel::isCellEditable(int row, int col) {
    switch (col) {
        case SEND_CABSIG_COLUMN:
        case REVERSE_BLOCK_DIR_BUTTON_COLUMN:
            return true;
        default:
            return false;
    }
}

/**
 * Configure a table to have our standard rows and columns.
 * <p>
 * This is optional, in that other table formats can use this table model.
 * But we put it here to help keep it consistent.
 */
/*public*/ void CabSignalTableModel::configureTable(JTable* cmdStatTable) {
    // allow reordering of the columns
//        cmdStatTable->getTableHeader().setReorderingAllowed(true);

    // shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
    cmdStatTable->setAutoResizeMode(JTable::AUTO_RESIZE_OFF);

    // resize columns as requested
    for (int i = 0; i < cmdStatTable->getColumnCount(); i++) {
        int width = getPreferredWidth(i);
        cmdStatTable->getColumnModel()->getColumn(i)->setPreferredWidth(width);
    }
   // cmdStatTable.sizeColumnsToFit(-1);
}

/**
 * Return table values.
 *
 * @param row int row number
 * @param col int col number
 */
//@Override
/*public*/ QVariant CabSignalTableModel::getValueAt(int row, int col) const {
    SignalMast* mast;
    Block* b;
    switch (col) {
        case LOCO_ID_COLUMN:
//                cabSignalManager->getCabSignalArray()[row]->addPropertyChangeListener( (PropertyChangeEvent e) -> {
//                   if(e.getSource() instanceof jmri.CabSignal){
//                      fireTableDataChanged();
//                   }
//                });
            return cabSignalManager->getCabSignalArray()[row]->getCabSignalAddress()->toString();
        case CURRENT_BLOCK:
            b = cabSignalManager->getCabSignalArray()[row]->getBlock();
            if ( b != nullptr){
                return b->getDisplayName();
            } else {
                return "";
            }
        case BLOCK_DIR:
            b = cabSignalManager->getCabSignalArray()[row]->getBlock();
            if ( b != nullptr){
                return Path::decodeDirection(b->getDirection());
            } else {
                return "";
            }
        case REVERSE_BLOCK_DIR_BUTTON_COLUMN:
            if (cabSignalManager->getCabSignalArray()[row]->getBlock()==nullptr){
                return tr("BlockLookup");
            } else {
                return tr("ChngDirection");
            }
        case NEXT_BLOCK:
    {
            Block* nextBl = cabSignalManager->getCabSignalArray()[row]->getNextBlock();
            if ( nextBl != nullptr){
                return nextBl->getDisplayName();
            } else {
                return "";
            }
    }
        case NEXT_SIGNAL:
            mast = cabSignalManager->getCabSignalArray()[row]->getNextMast();
            if (mast!=nullptr) {
                return mast->getDisplayName();
            }
            return "";
        case NEXT_ASPECT:
            mast = cabSignalManager->getCabSignalArray()[row]->getNextMast();
            if (mast!=nullptr) {
                return mast->getAspect();
            }
            return "";
        case NEXT_ASPECT_ICON:
            mast = cabSignalManager->getCabSignalArray()[row]->getNextMast();
            if (mast!=nullptr) {
                QString imageLink = mast->getAppearanceMap()->getProperty(mast->getAspect(), "imagelink");
                log->debug(tr("imagelink is %1").arg(imageLink));
                if ( imageLink != nullptr ) {
                    QString newlink = imageLink.replace("../", "");  // replace is immutable
                    // should start at the resources directory
                    return newlink;
                }
                else {
                    return "";
                }
            }
            return "";
        case SEND_CABSIG_COLUMN:
            return cabSignalManager->getCabSignalArray()[row]->isCabSignalActive();
        default:
            log->error(tr("internal state inconsistent with table request for row %1 col %2").arg(row).arg(col));
            return "";
    }
}
void CabSignalTableModel::propertyChange(PropertyChangeEvent * e)
{
 if(qobject_cast<CabSignal*>(e->getSource())){
    fireTableDataChanged();
 }
}

/**
 * @param value object value
 * @param row int row number
 * @param col int col number
 */
//@Override
/*public*/ void CabSignalTableModel::setValueAt(QVariant value, int row, int col) {
    if (col == LOCO_ID_COLUMN) {
    }
    else if (col == CURRENT_BLOCK) {
    }
    else if (col == BLOCK_DIR) {
    }
    else if (col == REVERSE_BLOCK_DIR_BUTTON_COLUMN) {
        cabSignalManager->getCabSignalArray()[row]->setBlock();
        chngblockdir(row);
    }
    else if (col == NEXT_BLOCK) {
//            jmri.util.ThreadingUtil.runOnLayout( ()->{
            BlockManager* bmgr = (BlockManager*)InstanceManager::getDefault("BlockManager");
            Block* b = bmgr->getBlock(value.toString());
            cabSignalManager->getCabSignalArray()[row]->setBlock(b);
//            });
    }
    else if (col == NEXT_SIGNAL) {
    }
    else if (col == NEXT_ASPECT) {
    }
    else if (col == SEND_CABSIG_COLUMN) {
        cabSignalManager->getCabSignalArray()[row]->setCabSignalActive( value.toBool());
    }
}

/**
 * Reverse the direction on the block associated with
 * the row.  Changes to the cab signal happen when the block's
 * properties change.
 */
/*private*/ void CabSignalTableModel::chngblockdir(int row){
    log->debug(tr("changing block direction for row %1").arg(row));
    int olddirection = 0;
    Block* b = cabSignalManager->getCabSignalArray()[row]->getBlock();
    if (b == nullptr){
        cabSignalManager->getCabSignalArray()[row]->setBlock();
        b = cabSignalManager->getCabSignalArray()[row]->getBlock();
        if (b==nullptr){
            return;
        } else {
            cabSignalManager->getCabSignalArray()[row]->setBlock(b);
            olddirection=b->getDirection();
        }
    }
    else {
        olddirection=b->getDirection();
        log->debug(tr("Block %1 set to direction %2 ").arg(b->getUserName()).arg(olddirection) );
    }

    log->debug(tr(" Direction to reverse :%1").arg(Path::decodeDirection(olddirection) ));

    if (olddirection==0){
        log->debug("No direction found, setting to North, East");
        b->setDirection(80);
    } else {
        log->debug(" direction found, setting reverse.");
        b->setDirection(Path::reverseDirection(olddirection));
    }
//        jmri.util.ThreadingUtil.runOnGUI( ()->{
        fireTableDataChanged();
//        });
    log->debug(tr("block %1 now has direction %2").arg(b->getUserName()).arg(b->getDirection()));
}

/*protected*/ void CabSignalTableModel::setPanelPauseButton(bool isPaused){
    for (int i = 0; i < getRowCount(); i++) {
        cabSignalManager->getCabSignalArray()[i]->setMasterCabSigPauseActive(isPaused);
    }
}

/*public*/ void CabSignalTableModel::dispose() {
}

/*public*/ QVariant CabSignalTableModel:: getToolTip(int col) const
{
 return columnToolTips.at(col);
}
/*private*/ /*final*/ /*static*/ Logger* CabSignalTableModel::log = LoggerFactory::getLogger("CabSignalTableModel");
