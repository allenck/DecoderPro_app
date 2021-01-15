
#include "schedulestablemodel.h"
#include "propertychangeevent.h"
#include "schedulemanager.h"
#include "schedulestableframe.h"
#include "schedule.h"
#include "scheduleeditframe.h"
#include "locationmanager.h"
#include "control.h"
#include "track.h"
#include "logger.h"
#include "vptr.h"
#include "locationtrackpair.h"
#include "location.h"
#include "jcombobox.h"
#include "jtable.h"
#include "xtablecolumnmodel.h"
#include "tablecolumn.h"
#include "pushbuttondelegate.h"
#include <QMessageBox>
#include "operationsxml.h"

/*private*/ JComboBox* getComboBox(Operations::Schedule* schedule, Operations::SchedulesTableModel* model)
{
 JComboBox* box = Operations::ScheduleManager::instance()->getSpursByScheduleComboBox(schedule);
 return box;
}

namespace Operations
{
/**
 * Table Model for edit of schedules used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2009, 2011, 2013
 * @version $Revision: 29644 $
 */
///*public*/ class SchedulesTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

    /**
     *
  */
 //private static final long serialVersionUID = -7373278452466866383L;



 /*public*/ SchedulesTableModel::SchedulesTableModel(QObject* parent)
     : AbstractTableModel(parent)
 {
     //super();
  SORTBYNAME = 1;
  SORTBYID = 2;
  _sort = SORTBYNAME;
  sysList = QList<Schedule*>();
  sef = NULL ;
  log = new Logger("SchedulesTableModel");
  comboSelect = QHash<Schedule*, QString>();

  scheduleManager = ScheduleManager::instance();
  //scheduleManager.addPropertyChangeListener(this);
  connect(scheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateList();
 }



 /*public*/ void SchedulesTableModel::setSort(int sort)
 {
  /*synchronized (this)*/ {
      _sort = sort;
  }
  updateList();
  fireTableDataChanged();
 }

 /*synchronized*/ void SchedulesTableModel::updateList()
 {
  // first, remove listeners from the individual objects
  removePropertyChangeSchedules();
  removePropertyChangeTracks();

  if (_sort == SORTBYID) {
      sysList = scheduleManager->getSchedulesByIdList();
  } else {
      sysList = scheduleManager->getSchedulesByNameList();
  }
  // and add them back in
  foreach (Schedule* sch, sysList)
  {
      //sch.addPropertyChangeListener(this);
   connect(sch->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  addPropertyChangeTracks();
 }

 void SchedulesTableModel::initTable(SchedulesTableFrame* frame, JTable* table) {
     this->table = table;
     // Install the button handlers

     TableColumnModel* tcm = table->getColumnModel();
#if 0
     ButtonRenderer buttonRenderer = new ButtonRenderer();
     TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());
     tcm.getColumn(EDIT_COLUMN)->setCellRenderer(buttonRenderer);
     tcm.getColumn(EDIT_COLUMN)->setCellEditor(buttonEditor);
     tcm.getColumn(DELETE_COLUMN)->setCellRenderer(buttonRenderer);
     tcm.getColumn(DELETE_COLUMN)->setCellEditor(buttonEditor);
     table->setDefaultRenderer("JComboBox", new jmri.jmrit.symbolicprog.ValueRenderer());
     table->setDefaultEditor("JComboBox", new jmri.jmrit.symbolicprog.ValueEditor());
#endif
     table->setItemDelegateForColumn(EDIT_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(DELETE_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(SPUR_COLUMN, new STMSComboBoxDelegate(this, getComboBox));

     setPreferredWidths(frame, table);

     // set row height
     //table->setRowHeight(new JComboBox<>().getPreferredSize().height);
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
     //table->setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

 }

 /*private*/ void SchedulesTableModel::setPreferredWidths(SchedulesTableFrame* frame, JTable* table)
 {
#if 0
  if (frame->loadTableDetails(table)) {
      return; // done
  }
#endif
  log->debug("Setting preferred widths");
  // set column preferred widths
  table->getColumnModel()->getColumn(ID_COLUMN)->setPreferredWidth(40);
  table->getColumnModel()->getColumn(NAME_COLUMN)->setPreferredWidth(200);
  table->getColumnModel()->getColumn(SCHEDULE_STATUS_COLUMN)->setPreferredWidth(80);
  table->getColumnModel()->getColumn(SPUR_NUMBER_COLUMN)->setPreferredWidth(40);
  table->getColumnModel()->getColumn(SPUR_COLUMN)->setPreferredWidth(350);
  table->getColumnModel()->getColumn(STATUS_COLUMN)->setPreferredWidth(150);
  table->getColumnModel()->getColumn(MODE_COLUMN)->setPreferredWidth(70);
  table->getColumnModel()->getColumn(EDIT_COLUMN)->setPreferredWidth(70);
  table->getColumnModel()->getColumn(DELETE_COLUMN)->setPreferredWidth(90);
 }

 /*public*/ int SchedulesTableModel::rowCount(const QModelIndex &parent) const {
     return sysList.size();
 }

 /*public*/ int SchedulesTableModel::columnCount(const QModelIndex &parent) const {
     return HIGHEST_COLUMN;
 }

 /*public*/ QVariant SchedulesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case ID_COLUMN:
             return tr("Id");
         case NAME_COLUMN:
             return tr("Name");
         case SCHEDULE_STATUS_COLUMN:
             return tr("Status");
         case SPUR_NUMBER_COLUMN:
             return tr("Number");
         case SPUR_COLUMN:
             return tr("Spurs");
         case STATUS_COLUMN:
             return tr("Status Spur");
         case MODE_COLUMN:
             return tr("Schedule Mode");
         case EDIT_COLUMN:
             return tr("Edit");
         case DELETE_COLUMN:
             return tr("Delete");
         default:
             return "unknown"; // NOI18N
     }
  }
  return QVariant();
 }

 /*public*/ QString SchedulesTableModel::getColumnClass(int col) {
     switch (col) {
         case ID_COLUMN:
             return "String";
         case NAME_COLUMN:
             return "String";
         case SCHEDULE_STATUS_COLUMN:
             return "String";
         case SPUR_NUMBER_COLUMN:
             return "String";
         case SPUR_COLUMN:
             return "JComboBox";
         case STATUS_COLUMN:
             return "String";
         case MODE_COLUMN:
             return "String";
         case EDIT_COLUMN:
             return "JButton";
         case DELETE_COLUMN:
             return "JButton";
         default:
             return QString() ;
     }
 }

 /*public*/ Qt::ItemFlags SchedulesTableModel::flags(const QModelIndex &index) const
 {
  switch (index.column())
  {
   case EDIT_COLUMN:
   case DELETE_COLUMN:
   case SPUR_COLUMN:
       return Qt::ItemIsEditable | Qt::ItemIsEnabled;
   default:
       return Qt::ItemIsEnabled;;
  }
 }

 /*public*/ QVariant SchedulesTableModel::data(const QModelIndex &index, int role) const
 {
  if(role == Qt::DisplayRole)
  {
   int row = index.row();
   int col = index.column();
   if (row >= sysList.size()) {
       return "ERROR row " + row; // NOI18N
   }
   Schedule* schedule = sysList.at(row);
   if (schedule == NULL ) {
       return "ERROR schedule unknown " + row; // NOI18N
   }
   switch (col) {
       case ID_COLUMN:
           return schedule->getId();
       case NAME_COLUMN:
           return schedule->getName();
       case SCHEDULE_STATUS_COLUMN:
           return getScheduleStatus(row);
       case SPUR_NUMBER_COLUMN:
           return scheduleManager->getSpursByScheduleComboBox(schedule)->count();
       case SPUR_COLUMN: {
//             return getComboBox(row, schedule);
        return scheduleManager->getSpursByScheduleComboBox(schedule)->currentText();
       }
       case STATUS_COLUMN:
           return getSpurStatus(row);
       case MODE_COLUMN:
           return getSpurMode(row);
       case EDIT_COLUMN:
           return tr("Edit");
       case DELETE_COLUMN:
           return tr("Delete");
       default:
           return "unknown " + col; // NOI18N
   }
  }
  return QVariant();
 }

 /*public*/ bool SchedulesTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  if(role == Qt::EditRole)
  {
   int row = index.row();
     switch (index.column()) {
         case EDIT_COLUMN:
             editSchedule(row);
             break;
         case DELETE_COLUMN:
             deleteSchedule(row);
             break;
         case SPUR_COLUMN:
             //selectJComboBox(value, row);
             break;
         default:
             break;
      return true;
     }
  }
  return false;
 }


 /*private*/ void SchedulesTableModel::editSchedule(int row) {
     log->debug("Edit schedule");
     if (sef != NULL ) {
         sef->dispose();
     }
     Schedule* sch = sysList.at(row);
     LocationTrackPair* ltp = getLocationTrackPair(row);
     if (ltp == NULL ) {
         log->debug("Need location track pair");
//         JOptionPane.showMessageDialog(NULL , MessageFormat.format(tr("AssignSchedule"),
//                 new Object[]{sch.getName()}), MessageFormat.format(tr("CanNotSchedule"),
//                         new Object[]{tr("Edit")}), JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(NULL, tr("Can not %1 schedule!").arg(tr("Edit")), tr("You must first assign schedule \"%1\" to a spur").arg(sch->getName()));
         return;
     }
     // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
             sef = new ScheduleEditFrame(sch, ltp->getTrack());
//         }
//     });
 }

 /*private*/ void SchedulesTableModel::deleteSchedule(int row) {
     log->debug("Delete schedule");
     Schedule* s = sysList.at(row);
//     if (JOptionPane.showConfirmDialog(NULL , MessageFormat.format(tr("DoYouWantToDeleteSchedule"),
//             new Object[]{s.getName()}), tr("DeleteSchedule?"), JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) {
     if(QMessageBox::critical(NULL, tr("Delete Schedule?"), tr("Do you want to delete schedule %1?").arg(s->getName()), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
     {
         scheduleManager->deregister(s);
         OperationsXml::save();
     }
 }

 /*private*/ void SchedulesTableModel::selectJComboBox(JComboBox* box, int row) {
     Schedule* schedule = sysList.at(row);
     //JComboBox<?> box = (JComboBox<?>) value;
     if (box->currentIndex() >= 0) {
         comboSelect.insert(schedule, QString::number(box->currentIndex()));
     }
     fireTableRowsUpdated(row, row);
 }

 /*private*/ LocationTrackPair* SchedulesTableModel::getLocationTrackPair(int row) const {
     Schedule* s = sysList.at(row);
     JComboBox* box = scheduleManager->getSpursByScheduleComboBox(s);
     QString index = comboSelect.value(sysList.at(row));
     LocationTrackPair* ltp;
     if (index != NULL ) {
         ltp = VPtr<LocationTrackPair>::asPtr(box->itemData(index.toInt()));
     } else {
         ltp = VPtr<LocationTrackPair>::asPtr(box->itemData(0));
     }
     return ltp;
 }

 /*private*/ QString SchedulesTableModel::getScheduleStatus(int row) const {
     Schedule* sch = sysList.at(row);
     JComboBox* box = scheduleManager->getSpursByScheduleComboBox(sch);
     for (int i = 0; i < box->count(); i++) {
         LocationTrackPair* ltp = (LocationTrackPair*) VPtr<LocationTrackPair>::asPtr(box->itemData(i));
         QString status = ltp->getTrack()->checkScheduleValid();
         if (status!=(Track::SCHEDULE_OKAY)) {
             return tr("Error");
         }
     }
     return tr("Okay");
 }

#if 0
 protected void comboBoxActionPerformed(ActionEvent ae) {
     log->debug("combobox action");
     if (table.isEditing()) {
         table.getCellEditor().stopCellEditing(); // Allows the table contents to update
     }
 }
#endif
 /*private*/ QString SchedulesTableModel::getSpurStatus(int row) const
 {
  LocationTrackPair* ltp = getLocationTrackPair(row);
  if (ltp == NULL ) {
      return "";
  }
  QString status = ltp->getTrack()->checkScheduleValid();
  if (status!=(Track::SCHEDULE_OKAY)) {
      return status;
  }
  return tr("Okay");
 }

 /*private*/ QString SchedulesTableModel::getSpurMode(int row) const {
     LocationTrackPair* ltp = getLocationTrackPair(row);
     if (ltp == NULL ) {
         return "";
     }
     QString mode = tr("Sequential");
     if (ltp->getTrack()->getScheduleMode() == Track::MATCH) {
         mode = tr("Match");
     }
     return mode;
 }

 /*private*/ void SchedulesTableModel::removePropertyChangeSchedules() {
     if (!sysList.isEmpty() ) {
         foreach (Schedule* sch, sysList) {
             //sch.removePropertyChangeListener(this);
          disconnect(sch->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }

 /*private*/ void SchedulesTableModel::addPropertyChangeTracks() {
     // only spurs have schedules
     foreach (Track* track, LocationManager::instance()->getTracks(Track::SPUR)) {
         //track.addPropertyChangeListener(this);
         connect(track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

 }

 /*private*/ void SchedulesTableModel::removePropertyChangeTracks() {
     foreach (Track* track, LocationManager::instance()->getTracks(Track::SPUR)) {
         //track.removePropertyChangeListener(this);
         disconnect(track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*public*/ void SchedulesTableModel::dispose()
 {
  if (log->isDebugEnabled()) {
      log->debug("dispose");
  }
  if (sef != NULL ) {
      sef->dispose();
  }
  //scheduleManager.removePropertyChangeListener(this);
  disconnect(scheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  removePropertyChangeSchedules();
  removePropertyChangeTracks();
 }

 // check for change in number of schedules, or a change in a schedule
 /*public*/ void SchedulesTableModel::propertyChange(PropertyChangeEvent *e)
 {
  if (Control::SHOW_PROPERTY) {
   log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
           ->getNewValue().toString()));
  }
  if (e->getPropertyName()==(ScheduleManager::LISTLENGTH_CHANGED_PROPERTY))
  {
   updateList();
   fireTableDataChanged();
  }
  else if (QString(e->getSource()->metaObject()->className())==("Schedule"))
  {
   Schedule* schedule = (Schedule*) e->getSource();
   int row = sysList.indexOf(schedule);
   if (Control::SHOW_PROPERTY)
   {
    log->debug(tr("Update schedule table row: %1 name: %2").arg(row).arg(schedule->getName()));
   }
   if (row >= 0)
   {
    fireTableRowsUpdated(row, row);
   }
  }
  if (QString(e->getSource()->metaObject()->className())==("Track"))
  {
   Track* track = (Track*) e->getSource();
   Schedule* schedule = track->getSchedule();
   int row = sysList.indexOf(schedule);
   if (row >= 0)
   {
    fireTableRowsUpdated(row, row);
   }
   else
   {
    fireTableDataChanged();
   }
  }

  if (e->getPropertyName()==(Track::SCHEDULE_ID_CHANGED_PROPERTY))
  {
   fireTableDataChanged();
  }
 }




 STMSComboBoxDelegate::STMSComboBoxDelegate(SchedulesTableModel* model,  GETCOMBO1, QObject *parent)
  : JComboBoxEditor(parent)
 {
  this->model  = model;
  this->items = QStringList();
  this->box = box;
 }


 QWidget *STMSComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &index ) const
 {
  JComboBox* editor;
  if(box != NULL)
  {
   Schedule* schedule = model->sysList.at(index.row());
   //editor = new JComboBox(box(si, this->model));
   JComboBox* b = ScheduleManager::instance()->getSpursByScheduleComboBox(schedule);
   editor = new JComboBox(parent);
   for(int i=0; i < b->count(); i++)
   {
    editor->addItem(b->itemText(i), b->itemData(i));
   }
  }
  else
  {
   editor = new JComboBox(parent);
   editor->addItems(items);
  }
  return editor;
 }

// void STMSComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
// {
//   JComboBox *comboBox = static_cast<JComboBox*>(editor);
//   int value = index.model()->data(index, Qt::EditRole).toUInt();
//   comboBox->setCurrentIndex(value);
// }

// void STMSComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
// {
//   JComboBox *comboBox = static_cast<JComboBox*>(editor);
//   model->setData(index, comboBox->currentText(), Qt::EditRole);
// }

// void STMSComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
// {
//   editor->setGeometry(option.rect);
// }
}
