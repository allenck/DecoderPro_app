#include "trainsscheduletablemodel.h"
#include "train.h"
#include "trainmanager.h"
#include "control.h"
#include "trainschedulemanager.h"
#include "jtable.h"
#include "tablecolumn.h"
#include "tablecolumnmodel.h"
#include "trainschedule.h"
#include "trainsscheduletableframe.h"
#include "instancemanager.h"

namespace Operations
{
 /**
  * Table Model for edit of train schedules (Timetable) used by operations
  *
  * @author Daniel Boudreau Copyright (C) 2010, 2012
  * @version $Revision: 29599 $
  */
 ///*public*/ class TrainsScheduleTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 735409937721234004L;

 /*public*/ TrainsScheduleTableModel::TrainsScheduleTableModel(QObject* parent) : AbstractTableModel(parent) {
     //super();
  log = new Logger("TrainsScheduleTableModel");
  trainManager = ((TrainManager*)InstanceManager::getDefault("TrainManager"));
  scheduleManager = ((TrainScheduleManager*)InstanceManager::getDefault("TrainScheduleManager"));
  _sort = SORTBYTIME;
 _frame = NULL;
  sysList = QList<Train*>();

     //trainManager.addPropertyChangeListener(this);
  connect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //scheduleManager.addPropertyChangeListener(this);
  connect(scheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     updateList();
     addPropertyChangeTrainSchedules();
 }



 /*public*/ void TrainsScheduleTableModel::setSort(int sort) {
     /*synchronized (this)*/ {
         _sort = sort;
     }
     updateList();
     fireTableStructureChanged();
     initTable();
 }

 /*private*/ /*synchronized*/ void TrainsScheduleTableModel::updateList() {
     // first, remove listeners from the individual objects
     removePropertyChangeTrains();

     if (_sort == SORTBYID) {
         sysList = trainManager->getTrainsByIdList();
     } else if (_sort == SORTBYNAME) {
         sysList = trainManager->getTrainsByNameList();
     } else if (_sort == SORTBYTIME) {
         sysList = trainManager->getTrainsByTimeList();
     } else if (_sort == SORTBYDEPARTS) {
         sysList = trainManager->getTrainsByDepartureList();
     } else if (_sort == SORTBYTERMINATES) {
         sysList = trainManager->getTrainsByTerminatesList();
     } else if (_sort == SORTBYROUTE) {
         sysList = trainManager->getTrainsByRouteList();
     }

     // and add listeners back in
     addPropertyChangeTrains();
 }

 /*public*/ /*synchronized*/ QList<Train*> TrainsScheduleTableModel::getSelectedTrainList()
 {
  return sysList;
 }


 void TrainsScheduleTableModel::initTable(JTable* table, TrainsScheduleTableFrame* frame)
 {
  _table = table;
  _frame = frame;
  initTable();
 }

 void TrainsScheduleTableModel::initTable()
 {
  if (_table == NULL) {
      return;
  }
  // Install the button handlers
  TableColumnModel* tcm = _table->getColumnModel();
  //_table.setDefaultRenderer(Boolean.class, new EnablingCheckboxRenderer());

  if (!_frame->loadTableDetails(_table))
  {
   // set column preferred widths, note that columns can be deleted
   QList<int> widths = trainManager->getTrainScheduleFrameTableColumnWidths();
   int numCol = widths.length();
   if (widths.length() > columnCount(QModelIndex())) {
       numCol = columnCount(QModelIndex());
   }
   for (int i = 0; i < numCol; i++) {
       tcm->getColumn(i)->setPreferredWidth(widths[i]);
   }
  }
  // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
  //_table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
 }

 /*public*/ /*synchronized*/ int TrainsScheduleTableModel::rowCount(const QModelIndex &parent) const {
     return sysList.size();
 }

 /*public*/ int TrainsScheduleTableModel::getFixedColumn()  const{
     return FIXEDCOLUMN;
 }

 /*public*/ int TrainsScheduleTableModel::columnCount(const QModelIndex &parent) const
 {
     return getFixedColumn() + scheduleManager->numEntries();
 }

 /*public*/ QVariant TrainsScheduleTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
   switch (section)
   {
    case IDCOLUMN:
        /*synchronized (this)*/
    {
     if (_sort == SORTBYID)
     {
         return tr("Id");
     }
     return tr("Time");
    }
    case NAMECOLUMN:
        return tr("Name");
    case DESCRIPTIONCOLUMN:
        return tr("Description");
   }
   TrainSchedule* ts = getSchedule(section);
   if (ts != NULL)
   {
    return ts->getName();
   }
   //return "unknown"; // NOI18N
  }
  return QVariant();
 }

// /*public*/ Class<?> getColumnClass(int col) {
//     switch (col) {
//         case IDCOLUMN:
//             return String.class;
//         case NAMECOLUMN:
//             return String.class;
//         case DESCRIPTIONCOLUMN:
//             return String.class;
//     }
//     if (col >= getFixedColumn() && col < getColumnCount()) {
//         return Boolean.class;
//     }
//     return NULL;
// }

 /*public*/ Qt::ItemFlags TrainsScheduleTableModel::flags(const QModelIndex &index) const
 {
  switch (index.column())
  {
   case IDCOLUMN:
   case NAMECOLUMN:
   case DESCRIPTIONCOLUMN:
       return Qt::ItemIsEnabled;
   default:
       return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
  }
 }

 /*public*/ QVariant TrainsScheduleTableModel::data(const QModelIndex &index, int role) const
 {
  int row = index.row();
  int col =index.column();
  Train* train = sysList.at(row);
  if (train == NULL) {
      return "ERROR train unknown " + row; // NOI18N
  }
  if(role == Qt::DisplayRole)
  {
//     if (row >= sysList.size()) {
//         return "ERROR row " + row; // NOI18N
//     }
   switch (col)
   {
    case IDCOLUMN:
    {
     if (_sort == SORTBYID) {
         return train->getId();
     }
     return train->getDepartureTime();
    }
    case NAMECOLUMN:
        return train->getIconName();
    case DESCRIPTIONCOLUMN:
        return train->getDescription();
   }
  }
  if(role == Qt::CheckStateRole)
  {
   TrainSchedule* ts = getSchedule(col);
   if (ts != NULL) {
       return ts->containsTrainId(train->getId())?Qt::Checked:Qt::Unchecked;
   }
   //return "unknown " + col; // NOI18N
  }
  return QVariant();
 }

 /*public*/ bool TrainsScheduleTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  if(role == Qt::CheckStateRole )
  {
   int col = index.column();
   int row = index.row();
   TrainSchedule* ts = getSchedule(col);
   if (ts != NULL)
   {
    Train* train = sysList.at(row);
    if (train == NULL)
    {
     log->error("train not found");
     return false;
    }
    if (( value).toBool())
    {
     ts->addTrainId(train->getId());
    }
    else
    {
     ts->removeTrainId(train->getId());
    }
    return true;
   }
  }
  return false;
 }

 /*public*/ void TrainsScheduleTableModel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(TrainManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(TrainManager::TRAIN_ACTION_CHANGED_PROPERTY)) {
         updateList();
         fireTableDataChanged();
     } else if (e->getPropertyName()==(TrainScheduleManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(TrainSchedule::NAME_CHANGED_PROPERTY)) {
         // update property change
         removePropertyChangeTrainSchedules();
         addPropertyChangeTrainSchedules();
         fireTableStructureChanged();
         initTable();
     } else if (e->getPropertyName()==(TrainSchedule::SCHEDULE_CHANGED_PROPERTY)) {
         fireTableDataChanged();
     } else if (QString(e->metaObject()->className())==("Train")) {
         Train* train = (Train*) e->getSource();
         /*synchronized (this)*/ {
             int row = sysList.indexOf(train);
             if (Control::SHOW_PROPERTY) {
                 log->debug("Update train table row: " + QString::number(row) + " name: " + train->getName());
             }
             if (row >= 0) {
                 fireTableRowsUpdated(row, row);
             }
         }
     }
 }

 /*public*/ TrainSchedule* TrainsScheduleTableModel::getSchedule(int col) const {
     if (col >= getFixedColumn() && col < columnCount(QModelIndex())) {
         QList<TrainSchedule*> trainSchedules = scheduleManager->getSchedulesByIdList();
         TrainSchedule* ts = trainSchedules.at(col - getFixedColumn());
         return ts;
     }
     return NULL;
 }

 /*private*/ void TrainsScheduleTableModel::removePropertyChangeTrainSchedules() {
     QList<TrainSchedule*> trainSchedules = scheduleManager->getSchedulesByIdList();
     foreach (TrainSchedule* ts, trainSchedules) {
         //ts.removePropertyChangeListener(this);
      disconnect(ts->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*private*/ void TrainsScheduleTableModel::addPropertyChangeTrainSchedules() {
     QList<TrainSchedule*> trainSchedules = scheduleManager->getSchedulesByIdList();
     foreach (TrainSchedule* ts, trainSchedules) {
         //ts.addPropertyChangeListener(this);
      connect(ts->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*private*/ /*synchronized*/ void TrainsScheduleTableModel::removePropertyChangeTrains() {
     if (!sysList.isEmpty()) {
         foreach (Train* train, sysList) {
             //train->removePropertyChangeListener(this);
             disconnect(train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }

 /*private*/ /*synchronized*/ void TrainsScheduleTableModel::addPropertyChangeTrains() {
     if (!sysList.isEmpty()) {
         foreach (Train* train, sysList) {
             //train->PropertyChangeSupport::addPropertyChangeListener(this);
          connect(train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }

 /*public*/ void TrainsScheduleTableModel::dispose() {
     if (log->isDebugEnabled()) {
         log->debug("dispose");
     }
     //trainManager.removePropertyChangeListener(this);
     disconnect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //scheduleManager.removePropertyChangeListener(this);
     disconnect(scheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeTrains();
     removePropertyChangeTrainSchedules();
 }
}
