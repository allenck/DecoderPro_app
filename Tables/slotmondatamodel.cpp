#include "slotmondatamodel.h"
#include "systemconnectionmemo.h"
#include "loconetsystemconnectionmemo.h"
#include "slotlistener.h"
#include "slotmanager.h"
#include <QPushButton>
#include "jtextfield.h"
#include <QMessageBox>
#include "loconetmessage.h"
#include "jtable.h"
#include <QItemDelegate>
#include "runnable.h"
#include <QHeaderView>
#include "sleeperthread.h"

//SlotMonDataModel::SlotMonDataModel(QObject *parent) :
//    QAbstractTableModel(parent)
//{
//}
/**
 * Table data model for display of slot manager contents
 * @author      Bob Jacobsen   Copyright (C) 2001
 * @version     $Revision: 22484 $
 */
// /*public*/ class SlotMonDataModel extends javax.swing.table.AbstractTableModel implements SlotListener  {

SlotMonDataModel::SlotMonDataModel(int row, int column, LocoNetSystemConnectionMemo* memo, QObject *parent)
    : AbstractTableModel(parent)
{
 this->memo = memo;
 _allSlots = true;
 _systemSlots = true;

 log = new Logger("SlotMonDataModel");

 // connect to SlotManager for updates
 memo->getSlotManager()->addSlotListener((SlotListener*)this);

 // start update process
 memo->getSlotManager()-> update();
}

/**
 * Returns the number of rows to be displayed.  This
 * can vary depending on whether only active rows
 * are displayed, and whether the system slots should be
 * displayed.
 * <P>
 * This should probably use a local cache instead
 * of counting/searching each time.
 */
/*public*/ int SlotMonDataModel::rowCount(const QModelIndex &parent) const
{
 if (_allSlots)
 {
  // will show the entire set, so don't bother counting
  if (_systemSlots)
   return 128;
  else
   return 120;  // skip 0, and 120 through 127`1    `1
 }
 int n = 0;
 int nMin = 1;
 int nMax = 120;
 if (_systemSlots)
 {
  nMin = 0;
  nMax = 128;
 }
 for (int i=nMin; i<nMax; i++)
 {
  LocoNetSlot* s = memo->getSlotManager()->slot(i);
  if (s->slotStatus() != LnConstants::LOCO_FREE ||
            i ==0 || i >= 120) n++;    // always show system slots if requested
 }
 return n;
}


/*public*/ int SlotMonDataModel::columnCount(const QModelIndex &parent) const
{ return NUMCOLUMN;}

/*public*/ QVariant  SlotMonDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
 {
  switch (section)
  {
    case SLOTCOLUMN: return tr("Slot");
    case ESTOPCOLUMN: return tr("");     // no heading, as button is clear
    case ADDRCOLUMN: return tr("Address");
    case SPDCOLUMN: return tr("Speed");
    case TYPECOLUMN: return tr("Status");
    case STATCOLUMN: return tr("Use");
    case CONSCOLUMN: return tr("Consisted");
    case DIRCOLUMN: return tr("Dir");
    case DISPCOLUMN: return tr("");     // no heading, as button is clear
    case F0COLUMN: return Throttle::F0;
    case F1COLUMN: return Throttle::F1;
    case F2COLUMN: return Throttle::F2;
    case F3COLUMN: return Throttle::F3;
    case F4COLUMN: return Throttle::F4;
    case F5COLUMN: return Throttle::F5;
    case F6COLUMN: return Throttle::F6;
    case F7COLUMN: return Throttle::F7;
    case F8COLUMN: return Throttle::F8;
    case THROTCOLUMN: return tr("Throttle ID");
    default: return tr("unknown");
  }
 }
 return QVariant();
}

///*public*/ Class<?> getColumnClass(int col) {
//    switch (col) {
//    case SLOTCOLUMN:
//    case ADDRCOLUMN:
//        return Integer.class;
//    case SPDCOLUMN:
//    case TYPECOLUMN:
//    case STATCOLUMN:
//    case CONSCOLUMN:
//    case DIRCOLUMN:
//    case THROTCOLUMN:
//        return String.class;
//    case ESTOPCOLUMN:
//    case DISPCOLUMN:
//        return JButton.class;
//    case F0COLUMN:
//    case F1COLUMN:
//    case F2COLUMN:
//    case F3COLUMN:
//    case F4COLUMN:
//    case F5COLUMN:
//    case F6COLUMN:
//    case F7COLUMN:
//    case F8COLUMN:
//        return Boolean.class;
//    default:
//        return null;
//    }
//}

/*public*/ Qt::ItemFlags SlotMonDataModel::flags(const QModelIndex &index) const
{
    switch (index.column())
    {
    case ESTOPCOLUMN:
    case DISPCOLUMN:
     // system slots to be marked Readonly
     return ((slotNum(index.row()) >= 120) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable));
    case F0COLUMN:
    case F1COLUMN:
    case F2COLUMN:
    case F3COLUMN:
    case F4COLUMN:
    case F5COLUMN:
    case F6COLUMN:
    case F7COLUMN:
    case F8COLUMN:
        // system slots to be marked Readonly
        return ((slotNum(index.row()) >= 120) ? (Qt::ItemIsEnabled | Qt::ItemIsSelectable) : (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable)) | Qt::ItemIsUserCheckable;
    default:
        return (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    }
}

//static final Boolean True = Boolean.valueOf(true);
//static final Boolean False = Boolean.valueOf(false);

//@SuppressWarnings("null")
/*public*/ QVariant SlotMonDataModel::data(const QModelIndex &index, int role) const
{
 int row = index.row();
 int col = index.column();
 LocoNetSlot* s = memo->getSlotManager()->slot(slotNum(row));
 if(role == Qt::DisplayRole)
 {
  QString      t;
  if (s == NULL) log->error("slot pointer was null for slot row: "+QString::number(row)+" col: "+QString::number(col));

  switch (col)
  {
   case SLOTCOLUMN:  // slot number
    return slotNum(row);
   case ESTOPCOLUMN:  //
    return tr("E Stop");          // will be name of button in default GUI
   case ADDRCOLUMN:  //
    s->locoAddr();
   case SPDCOLUMN:  //
    switch (s->consistStatus())
    {
     case LnConstants::CONSIST_TOP:
     case LnConstants::CONSIST_NO:
      if (s->speed() == 1) t = tr("(estop) 1");
      else t = "          "+QString::number(s->speed());
      return t.mid(t.length()-9, t.length()); // 9 comes from (estop)
     case LnConstants::CONSIST_MID:
     case LnConstants::CONSIST_SUB:
      return tr("(consist)");
     default:
      return tr("<error>");
    }
   case TYPECOLUMN:  //
        switch (s->decoderType()) {
        case LnConstants::DEC_MODE_128A:     return "128 step adv";
        case LnConstants::DEC_MODE_28A:      return " 28 step adv";
        case LnConstants::DEC_MODE_128:      return "128 step";
        case LnConstants::DEC_MODE_14:       return " 14 step";
        case LnConstants::DEC_MODE_28TRI:    return " 28 step trinary";
        case LnConstants::DEC_MODE_28:       return " 28 step";
        default:                            return "<unknown>";
        }
   case STATCOLUMN:  //
        switch (s->slotStatus()) {
        case LnConstants::LOCO_IN_USE:       return "In Use";
        case LnConstants::LOCO_IDLE:         return "Idle";
        case LnConstants::LOCO_COMMON:       return "Common";
        case LnConstants::LOCO_FREE:         return "Free";
        default:                            return "<error>";
        }
   case CONSCOLUMN:  //
        switch (s->consistStatus()) {
        case LnConstants::CONSIST_MID:
            t = "mid(" + QString::number(s->speed()) + ")";
            return t;
        case LnConstants::CONSIST_TOP:       return "top";
        case LnConstants::CONSIST_SUB:
            t = "sub("+QString::number(s->speed())+")";
            return t;
        case LnConstants::CONSIST_NO:        return "none";
        default:                            return "<error>";
        }
   case DISPCOLUMN:  //
        return "Free";          // will be name of button in default GUI
   case DIRCOLUMN:  //
        return (s->isForward() ? "F" : "R");
   case F0COLUMN:  //
//        return (s->isF0() ? Qt::Checked: Qt::Unchecked);
   case F1COLUMN:  //
//        return (s->isF1() ? Qt::Checked: Qt::Unchecked);
   case F2COLUMN:  //
//        return (s->isF2() ? Qt::Checked: Qt::Unchecked);
   case F3COLUMN:  //
//        return (s->isF3() ? Qt::Checked: Qt::Unchecked);
   case F4COLUMN:  //
//        return (s->isF4() ? Qt::Checked: Qt::Unchecked);
   case F5COLUMN:  //
//        return (s->isF5() ? Qt::Checked: Qt::Unchecked);
   case F6COLUMN:  //
        return (s->isF6() ? Qt::Checked: Qt::Unchecked);
   case F7COLUMN:  //
//        return (s->isF7() ? Qt::Checked: Qt::Unchecked);
   case F8COLUMN:  //
//        return (s->isF8() ? Qt::Checked: Qt::Unchecked);
    break;
   case THROTCOLUMN:
   {
    int upper = (s->id()>>7)&0x7F;
    int lower = s->id()&0x7F;
    //return StringUtil.twoHexFromInt(upper)+" "+StringUtil.twoHexFromInt(lower);
    QString u = upper>16?"":"0";
    QString l = lower>16?"":"0";
    return u+QString::number(upper,16) + " "+l + QString::number(lower, 16);
   }
   default:
   {
    log->error("internal state inconsistent with table request for "+QString::number(row)+" "+QString::number(col));
    return QVariant();
   }
  }
 }
 if(role == Qt::CheckStateRole)
 {
  switch(col)
  {
   case F0COLUMN:  //
    return (s->isF0() ? Qt::Checked: Qt::Unchecked);
   case F1COLUMN:  //
    return (s->isF1() ? Qt::Checked: Qt::Unchecked);
   case F2COLUMN:  //
    return (s->isF2() ? Qt::Checked: Qt::Unchecked);
   case F3COLUMN:  //
    return (s->isF3() ? Qt::Checked: Qt::Unchecked);
   case F4COLUMN:  //
    return (s->isF4() ? Qt::Checked: Qt::Unchecked);
   case F5COLUMN:  //
    return (s->isF5() ? Qt::Checked: Qt::Unchecked);
   case F6COLUMN:  //
    return (s->isF6() ? Qt::Checked: Qt::Unchecked);
   case F7COLUMN:  //
    return (s->isF7() ? Qt::Checked: Qt::Unchecked);
   case F8COLUMN:  //
    return (s->isF8() ? Qt::Checked: Qt::Unchecked);
   default:
    break;
  }
 }
 return QVariant();
}

/*public*/ int SlotMonDataModel::getPreferredWidth(int col)
{
 switch (col)
 {
    case SLOTCOLUMN:
        return JTextField(3).sizeHint().width();
    case ESTOPCOLUMN:
        return QPushButton(tr("E Stop")).sizeHint().width();
    case ADDRCOLUMN:
        return  JTextField(5).sizeHint().width();
    case SPDCOLUMN:
        return  JTextField(6).sizeHint().width();
    case TYPECOLUMN:
        return  JTextField(12).sizeHint().width();
    case STATCOLUMN:
        return  JTextField(6).sizeHint().width();
    case CONSCOLUMN:
        return  JTextField(4).sizeHint().width();
    case DIRCOLUMN:
        return  JTextField(3).sizeHint().width();
    case DISPCOLUMN:
        return  QPushButton(tr("Free")).sizeHint().width();
    case THROTCOLUMN:
        return  JTextField(7).sizeHint().width();
    case F0COLUMN:
    case F1COLUMN:
    case F2COLUMN:
    case F3COLUMN:
    case F4COLUMN:
    case F5COLUMN:
    case F6COLUMN:
    case F7COLUMN:
    case F8COLUMN:
        return  QLabel(tr(" off    ")).sizeHint().width();
    default:
        return  QLabel(tr(" <unknown> ")).sizeHint().width();
 }
}

/*public*/ bool SlotMonDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 int col = index.column();
 int status = 0;

 if(role == Qt::EditRole)
 {
  if (col == ESTOPCOLUMN)
  {
   log->debug("Start estop in slot "+QString::number(row));
   // check for in use
   LocoNetSlot* s = memo->getSlotManager()->slot(slotNum(row));
   if (s == NULL)
   {
    log->error("slot pointer was null for slot row: "+QString::number(row)+" col: "+QString::number(col));
    return false;
   }
   if ((s->consistStatus() == LnConstants::CONSIST_SUB) ||
            (s->consistStatus() == LnConstants::CONSIST_MID))
   {
//            Object[] options = { "OK", "Cancel" };
//            int result =
//                JOptionPane.showOptionDialog (null,
//                                              "E-Stopping a consist MID or SUB will mess up the consist.\n\nAre you sure you want to do that?",
//                                              "Warning",
//                                              JOptionPane.DEFAULT_OPTION,
//                                              JOptionPane.WARNING_MESSAGE,
//                                              null, options, options[1]);
//            if (result == 1) return;
    if(QMessageBox::warning(NULL, tr("Warning"), tr("E-Stopping a consist MID or SUB will mess up the consist.\n\nAre you sure you want to do that?"),QMessageBox::Ok | QMessageBox::Cancel)==QMessageBox::Cancel)
     return false;

   }
   LocoNetMessage* msg = new LocoNetMessage(4);
   msg->setOpCode(LnConstants::OPC_LOCO_SPD);
   msg->setElement(1, s->getSlot());
   msg->setElement(2, 1);       // 1 here is estop
   memo->getLnTrafficController()->sendLocoNetMessage(msg);
   fireTableRowsUpdated(row,row);
  }

  else if (col == DISPCOLUMN)
  {
   log->debug("Start freeing slot "+QString::number(row));
   // check for in use
   LocoNetSlot* s = memo->getSlotManager()->slot(slotNum(row));
   if (s == NULL)
   {
    log->error("slot pointer was null for slot row: "+QString::number(row)+" col: "+QString::number(col));
    return false;
   }
   if (s->slotStatus()!=LnConstants::LOCO_FREE)
   {
    if (s->consistStatus() != LnConstants::CONSIST_NO) {
    // Freeing a member takes it out of the consist
    // entirely (i.e., while the slot is LOCO_FREE, it
    // still reads the former consist information, but
    // the next time that loco is selected, it comes
    // back as CONSIST_NO).  Freeing the CONSIST_TOP
    // will kill the entire consist.
//    Object[] options = { "OK", "Cancel" };
//    int result =
//        JOptionPane.showOptionDialog (null,
//                                      "Freeing a consist member will destroy the consist.\n\nAre you sure you want to do that?",
//                                      "Warning",
//                                      JOptionPane.DEFAULT_OPTION,
//                                      JOptionPane.WARNING_MESSAGE,
//                                      null, options, options[1]);
//    if (result == 1) return;
     if(QMessageBox::warning(NULL, tr("Warning"), tr("Freeing a consist member will destroy the consist.\n\nAre you sure you want to do that?"),QMessageBox::Ok | QMessageBox::Cancel)==QMessageBox::Cancel)
         return false;
   }
   // send status to free
   memo->getLnTrafficController()->sendLocoNetMessage(
                    s->writeStatus(LnConstants::LOCO_FREE
                ));
  }
   else
   {
    QString txt = QString("Slot %1 not in use").arg(row);
    log->debug(txt);
   }
   fireTableRowsUpdated(row,row);
  }
 }
 if(role == Qt::CheckStateRole)
 {
  if ((col == F0COLUMN) ||
                (col == F1COLUMN) ||
                (col == F2COLUMN) ||
                (col == F3COLUMN) ||
                (col == F4COLUMN) )
  {
   log->debug("F0-F4 change requested "+QString::number(row));
   LocoNetSlot* s = memo->getSlotManager()->slot(slotNum(row));
   if (s == NULL)
   {
    log->error("slot pointer was null for slot row: "+QString::number(row)+" col: "+QString::number(col));
    return false;
   }
   bool tempF0 = (col == F0COLUMN) ? !s->isF0() : s->isF0();
   if(col == F0COLUMN) tempF0 = value.toBool();
   bool tempF1 = (col == F1COLUMN) ? !s->isF1() : s->isF1();
   if(col == F1COLUMN) tempF1 = value.toBool();
   bool tempF2 = (col == F2COLUMN) ? !s->isF2() : s->isF2();
   if(col == F2COLUMN) tempF2 = value.toBool();
   bool tempF3 = (col == F3COLUMN) ? !s->isF3() : s->isF3();
   if(col == F3COLUMN) tempF3 = value.toBool();
   bool tempF4 = (col == F4COLUMN) ? !s->isF4() : s->isF4();
   if(col == F4COLUMN) tempF4 = value.toBool();

   int new_dirf = ((s->isForward() ? 0 : LnConstants::DIRF_DIR) |
                       (tempF0 ? LnConstants::DIRF_F0 : 0) |
                       (tempF1 ? LnConstants::DIRF_F1 : 0) |
                       (tempF2 ? LnConstants::DIRF_F2 : 0) |
                       (tempF3 ? LnConstants::DIRF_F3 : 0) |
                       (tempF4 ? LnConstants::DIRF_F4 : 0));

   // set status to 'In Use' if other
   status = s->slotStatus();
   if (status != LnConstants::LOCO_IN_USE)
   {
    memo->getLnTrafficController()->sendLocoNetMessage(
                       s->writeStatus(LnConstants::LOCO_IN_USE
                   ));
   }
   LocoNetMessage* msg = new LocoNetMessage(4);
   msg->setOpCode(LnConstants::OPC_LOCO_DIRF);
   msg->setElement(1, s->getSlot());
   msg->setElement(2, new_dirf);       // 1 here is estop
   memo->getLnTrafficController()->sendLocoNetMessage(msg);
   // Delay here allows command station time to xmit on the rails.
   try
   {
    SleeperThread::msleep(100);
   }
   catch (InterruptedException ex)
   {
    //Logger.getLogger(SlotMonDataModel.class.getName()).log(Level.SEVERE, null, ex);
   }
   // reset status to original value if not previously 'in use'
   if(status != LnConstants::LOCO_IN_USE)
   {
    memo->getLnTrafficController()->sendLocoNetMessage(
                       s->writeStatus(status));
   }
   fireTableRowsUpdated(row,row);
   fireTableDataChanged();
   return true;
  }
  else if ((col == F5COLUMN) ||
                (col == F6COLUMN) ||
                (col == F7COLUMN) ||
                (col == F8COLUMN) )
  {
   log->debug("F5-F8 change requested "+QString::number(row));
   LocoNetSlot* s = memo->getSlotManager()->slot(slotNum(row));
   if (s == NULL)
   {
    log->error("slot pointer was null for slot row: "+QString::number(row)+" col: "+QString::number(col));
    return false;
   }

   bool tempF5 = (col == F5COLUMN) ? !s->isF5() : s->isF5();
   bool tempF6 = (col == F6COLUMN) ? !s->isF6() : s->isF6();
   bool tempF7 = (col == F7COLUMN) ? !s->isF7() : s->isF7();
   bool tempF8 = (col == F8COLUMN) ? !s->isF8() : s->isF8();

   int new_snd = ((tempF8 ? LnConstants::SND_F8 : 0) |
                          (tempF7 ? LnConstants::SND_F7 : 0) |
                          (tempF6 ? LnConstants::SND_F6 : 0) |
                          (tempF5 ? LnConstants::SND_F5 : 0));

   // set status to 'In Use' if other
   status = s->slotStatus();
   if (status != LnConstants::LOCO_IN_USE)
   {
    memo->getLnTrafficController()->sendLocoNetMessage(
                       s->writeStatus(LnConstants::LOCO_IN_USE
                   ));
   }

   LocoNetMessage* msg = new LocoNetMessage(4);
   msg->setOpCode(LnConstants::OPC_LOCO_SND);
   msg->setElement(1, s->getSlot());
   msg->setElement(2, new_snd);       // 1 here is estop
   memo->getLnTrafficController()->sendLocoNetMessage(msg);
   // Delay here allows command station time to xmit on the rails.
   try
   {
    SleeperThread::msleep(100);
   }
   catch (InterruptedException ex)
   {
     //Logger.getLogger(SlotMonDataModel.class.getName()).log(Level.SEVERE, null, ex);
   }

   // reset status to original value if not previously 'in use'
   if(status != LnConstants::LOCO_IN_USE)
   {
    memo->getLnTrafficController()->sendLocoNetMessage(
    s->writeStatus(status));
   }

   fireTableRowsUpdated(row,row);
  }
 }
 return true;
}
//Added by Jeffrey Machacek, date: 2013
//changed 8/22/2013
/*public*/ void SlotMonDataModel::clearAllSlots()
{
 int count = rowCount(QModelIndex());

 for (int row = 0; row < (count - 1); row++)
 {
  LocoNetSlot* s = memo->getSlotManager()->slot(slotNum(row));

  if ((s->slotStatus() != LnConstants::LOCO_IN_USE) && (s->consistStatus() == LnConstants::CONSIST_NO))
  {
   log->debug(QString("Freeing %1 from slot %2, old status: {%3").arg(s->locoAddr()).arg(s->getSlot()).arg(s->slotStatus()));
   memo->getLnTrafficController()->sendLocoNetMessage(
           s->writeStatus(LnConstants::LOCO_FREE
           ));
   fireTableRowsUpdated(row, row);
  }
  count = rowCount(QModelIndex());
 }
}

/**
 * Configure a table to have our standard rows and columns.
 * This is optional, in that other table formats can use this table model.
 * But we put it here to help keep it consistent.
 * @param slotTable
 */
/*public*/ void SlotMonDataModel::configureTable(JTable* slotTable)
{
#if 0
    // allow reordering of the columns
    slotTable->getTableHeader().setReorderingAllowed(true);

    // shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
    slotTable.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
#endif
 // resize columns as requested
 for (int i=0; i<NUMCOLUMN; i++)
 {
  int width = getPreferredWidth(i);
  //slotTable.getColumnModel().getColumn(i).setPreferredWidth(width);
  slotTable->setColumnWidth(i,width);
 }
 //slotTable.sizeColumnsToFit(-1);
 slotTable->resizeColumnsToContents();

 // install a button renderer & editor in the "DISP" column for freeing a slot
 setColumnToHoldButton(slotTable, SlotMonDataModel::DISPCOLUMN);

 // install a button renderer & editor in the "ESTOP" column for stopping a loco
 setColumnToHoldButton(slotTable, SlotMonDataModel::ESTOPCOLUMN);
}

void SlotMonDataModel:: setColumnToHoldButton(JTable* slotTable, int column)
{
#if 0
    TableColumnModel tcm = slotTable.getColumnModel();
    // install the button renderers & editors in this column
    ButtonRenderer buttonRenderer = new ButtonRenderer();
    tcm.getColumn(column).setCellRenderer(buttonRenderer);
    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
    tcm.getColumn(column).setCellEditor(buttonEditor);
    // ensure the table rows, columns have enough room for buttons
    slotTable.setRowHeight(new JButton("  "+getValueAt(1, column)).getPreferredSize().height);
    slotTable.getColumnModel().getColumn(column)
                    .setPreferredWidth(new JButton("  "+getValueAt(1, column)).getPreferredSize().width);
#endif
}

void setColumnToHoldEStopButton(JTable* slotTable, int column)
{
#if 0
    TableColumnModel tcm = slotTable.getColumnModel();
    // install the button renderers & editors in this column
    ButtonRenderer buttonRenderer = new ButtonRenderer();
    tcm.getColumn(column).setCellRenderer(buttonRenderer);
    TableCellEditor buttonEditor = new ButtonEditor(new JButton()){
        /*public*/ void mousePressed(MouseEvent e) {
            stopCellEditing();
        }
    };
    tcm.getColumn(column).setCellEditor(buttonEditor);
    // ensure the table rows, columns have enough room for buttons
    slotTable.setRowHeight(new JButton("  "+getValueAt(1, column)).getPreferredSize().height);
    slotTable.getColumnModel().getColumn(column)
                    .setPreferredWidth(new JButton("  "+getValueAt(1, column)).getPreferredSize().width);
#endif
}

// methods to communicate with SlotManager
/*public*/ /*synchronized*/ void SlotMonDataModel::notifyChangedSlot(LocoNetSlot* s)
{
 // update model from this slot
 int slotNum = s->getSlot();
 int slotStatus2;

 if (slotNum == LnConstants::CFG_SLOT)
 {
  slotStatus2 = s->ss2() & 0x78; // Bit 3-6 of SS2 contains SW36-39 of the CFG_SLOT
  if (slotStatus2 > 0)
  {
   memo->getSlotManager()->update();
  }
 }
 else
 {
  slotNum = -1;
 }

 if (_allSlots)
 {        // this will be row until we show only active slots
  slotNum=s->getSlot();  // and we are displaying the System slots otherwise
  if( !_systemSlots )   // we need to subtract 1 as slot 0 will not be displayed
  slotNum-- ;
 }
 // notify the JTable object that a row has changed; do that in the Swing thread!
 Runnable* r = new Notify(slotNum, this);   // -1 in first arg means all
 //javax.swing.SwingUtilities.invokeLater(r);
 r->run();
}

//static class Notify implements Runnable {
//    private int _row;
//    javax.swing.table.AbstractTableModel _model;
/*public*/ SlotMonDataModel::Notify::Notify(int row, AbstractTableModel* model)
{
 _row = row; _model = model;
}
/*public*/ void SlotMonDataModel::Notify::run()
{
 if (-1 == _row)
 {  // notify about entire table
  _model->fireTableDataChanged();  // just that row
 }
 else
 {
  // notify that _row has changed
  _model->fireTableRowsUpdated(_row, _row);  // just that row
 }
}
//};

// methods for control of "all slots" vs "only active slots"
/*public*/ void SlotMonDataModel::showAllSlots(bool val) { _allSlots = val; }

// methods for control of display of system slots
/*public*/ void SlotMonDataModel::showSystemSlots(bool val) { _systemSlots = val; }

/**
 * Returns slot number for a specific row.
 * <P>
 * This should probably use a local cache instead
 * of counting/searching each time.
 * @param row Row number in the displayed table
 */
/*protected*/ int SlotMonDataModel::slotNum(int row) const
{
 int slotNum;
 int n = -1;   // need to find a used slot to have the 0th one!
 int nMin = 1;
 int nMax = 120;
 if (_systemSlots)
 {
  nMin = 0;
  nMax = 128;
 }
 for (slotNum=nMin; slotNum<nMax; slotNum++)
 {
  LocoNetSlot* s = memo->getSlotManager()->slot(slotNum);
  if (_allSlots || s->slotStatus() != LnConstants::LOCO_FREE
            || slotNum ==0 || slotNum >= 120) n++;    // always show system slots if requested
        if (n == row) break;
 }
 return slotNum;
}

/**
 * This is a convenience method that makes it easier for classes
 * using this model to set all in-use slots to emergency stop
 */
/*public*/ void SlotMonDataModel::estopAll()
{
 for (int slotNum=0; slotNum<120; slotNum++)
 {
  LocoNetSlot* s = memo->getSlotManager()->slot(slotNum);
  if (s->slotStatus() != LnConstants::LOCO_FREE &&
    (s->consistStatus() == LnConstants::CONSIST_NO ||
     s->consistStatus() == LnConstants::CONSIST_TOP) &&
    s->speed() != 1)
  {
   // send message to estop this loco
   LocoNetMessage* msg = new LocoNetMessage(4);
   msg->setOpCode(LnConstants::OPC_LOCO_SPD);
   msg->setElement(1, s->getSlot());
   msg->setElement(2, 1);  // emergency stop
   memo->getLnTrafficController()->sendLocoNetMessage(msg);
  }
 }
}

/*public*/ void SlotMonDataModel::dispose()
{
 memo->getSlotManager()->removeSlotListener((SlotListener*)this);
 // table.removeAllElements();
 // table = null;
}
