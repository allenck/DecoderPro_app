#include "carstablemodel.h"
#include "carmanager.h"
#include "xtablecolumnmodel.h"
#include "jtable.h"
#include "setup.h"
#include "car.h"
#include "kernel.h"
#include "logger.h"
#include "control.h"
#include "carmanager.h"
#include <rollingstock.h>
#include "careditframe.h"
#include "carload.h"
#include "carsetframe.h"
#include <QPushButton>
#include <QSignalMapper>
#include <QList>
#include "pushbuttondelegate.h"

namespace Operations
{

/**
 * Table Model for edit of cars used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2011, 2012
 * @version $Revision: 29493 $
 */
///*public*/ class CarsTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

    /**
     *
     */
    ///*/*private*/*/ static final long serialVersionUID = -5846367542654823901L;





 /*public*/ CarsTableModel::CarsTableModel(bool showAllCars, QString locationName, QString trackName, QObject* parent)
: AbstractTableModel(parent)
 {
     //super();
  manager = CarManager::instance(); // There is only one manager
 _sort = SORTBY_NUMBER;
  sysList = NULL;
  cef = NULL;
  csf = NULL;
  _roadNumber = "";
  _index = 0;
  log = new Logger("CarsTableModel");


  this->showAllCars = showAllCars;
  this->locationName = locationName;
  this->trackName = trackName;

// manager->addPropertyChangeListener(this);
  connect(manager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateList();
 }

 /*public*/ void CarsTableModel::setSort(int sort) {
     _sort = sort;
     updateList();
     XTableColumnModel* tcm = (XTableColumnModel*) _table->getColumnModel();
     if (sort == SORTBY_COLOR || sort == SORTBY_LOAD) {
         tcm->setColumnVisible(tcm->getColumnByModelIndex(LOAD_COLUMN), sort == SORTBY_LOAD);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(COLOR_COLUMN), sort == SORTBY_COLOR);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(RWE_LOAD_COLUMN), false);
     } else if (sort == SORTBY_DESTINATION || sort == SORTBY_FINALDESTINATION || sort == SORTBY_RWE) {
         tcm->setColumnVisible(tcm->getColumnByModelIndex(DESTINATION_COLUMN), sort == SORTBY_DESTINATION);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(FINAL_DESTINATION_COLUMN), sort == SORTBY_FINALDESTINATION);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(RWE_COLUMN), sort == SORTBY_RWE);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(RWE_LOAD_COLUMN), sort == SORTBY_RWE);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(LOAD_COLUMN), sort != SORTBY_RWE);
         if (sort == SORTBY_RWE) {
             tcm->setColumnVisible(tcm->getColumnByModelIndex(COLOR_COLUMN), false);
         }
     } else if (sort == SORTBY_MOVES || sort == SORTBY_BUILT || sort == SORTBY_OWNER || sort == SORTBY_VALUE
             || sort == SORTBY_RFID || sort == SORTBY_WAIT || sort == SORTBY_PICKUP || sort == SORTBY_LAST) {
         tcm->setColumnVisible(tcm->getColumnByModelIndex(MOVES_COLUMN), sort == SORTBY_MOVES);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(BUILT_COLUMN), sort == SORTBY_BUILT);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(OWNER_COLUMN), sort == SORTBY_OWNER);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(VALUE_COLUMN), sort == SORTBY_VALUE);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(RFID_COLUMN), sort == SORTBY_RFID);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(WAIT_COLUMN), sort == SORTBY_WAIT);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(PICKUP_COLUMN), sort == SORTBY_PICKUP);
         tcm->setColumnVisible(tcm->getColumnByModelIndex(LAST_COLUMN), sort == SORTBY_LAST);
     } else {
         fireTableDataChanged();
     }
 }

 /*public*/ QString CarsTableModel::getSortByName() {
     return getSortByName(_sort);
 }

 /*public*/ QString CarsTableModel::getSortByName(int sort) {
     switch (sort) {
         case SORTBY_NUMBER:
             return tr("Number");
         case SORTBY_ROAD:
             return tr("Road");
         case SORTBY_TYPE:
             return tr("Type");
         case SORTBY_COLOR:
             return tr("Color");
         case SORTBY_LOAD:
             return tr("Load");
         case SORTBY_KERNEL:
             return tr("Kernel");
         case SORTBY_LOCATION:
             return tr("Location");
         case SORTBY_DESTINATION:
             return tr("Destination");
         case SORTBY_TRAIN:
             return tr("Train");
         case SORTBY_FINALDESTINATION:
             return tr("FinalDestination");
         case SORTBY_RWE:
             return tr("ReturnWhenEmpty");
         case SORTBY_MOVES:
             return tr("Moves");
         case SORTBY_BUILT:
             return tr("Built");
         case SORTBY_OWNER:
             return tr("Owner");
         case SORTBY_VALUE:
             return Setup::getValueLabel();
         case SORTBY_RFID:
             return Setup::getRfidLabel();
         case SORTBY_WAIT:
             return tr("Wait");
         case SORTBY_PICKUP:
             return tr("Pickup");
         case SORTBY_LAST:
             return tr("Last");
         default:
             return "Error"; // NOI18N
     }
 }

 /*private*/ /*static*/ bool CarsTableModel::isSelectVisible = false;

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*public*/ void CarsTableModel::toggleSelectVisible() {
     XTableColumnModel* tcm = (XTableColumnModel*) _table->getColumnModel();
     isSelectVisible = !tcm->isColumnVisible(tcm->getColumnByModelIndex(SELECT_COLUMN));
     tcm->setColumnVisible(tcm->getColumnByModelIndex(SELECT_COLUMN), isSelectVisible);
 }

 /*public*/ void CarsTableModel::resetCheckboxes() {
     foreach (RollingStock* car, *sysList) {
         car->setSelected(false);
     }
 }


 /**
  * Search for car by road number
  *
  * @param roadNumber
  * @return -1 if not found, table row number if found
  */
 /*public*/ int CarsTableModel::findCarByRoadNumber(QString roadNumber) {
     if (sysList != NULL)
     {
         if (roadNumber!=(_roadNumber)) {
             return getIndex(0, roadNumber);
         }
         int index = getIndex(_index, roadNumber);
         if (index > 0) {
             return index;
         }
         return getIndex(0, roadNumber);
     }
     return -1;
 }

 /*private*/ int CarsTableModel::getIndex(int start, QString roadNumber) {
     for (int index = start; index < sysList->size(); index++) {
         Car* c = (Car*) sysList->at(index);
         if (c != NULL) {
             QStringList number = c->getNumber().split("-");
             // check for wild card '*'
             if (roadNumber.startsWith("*")) {
                 QString rN = roadNumber.mid(1);
                 if (c->getNumber().endsWith(rN) || number[0].endsWith(rN)) {
                     _roadNumber = roadNumber;
                     _index = index + 1;
                     return index;
                 }
             } else if (roadNumber.endsWith("*")) {
                 QString rN = roadNumber.mid(0, roadNumber.length() - 1);
                 if (c->getNumber().startsWith(rN)) {
                     _roadNumber = roadNumber;
                     _index = index + 1;
                     return index;
                 }
             } else if (c->getNumber()==(roadNumber) || number[0]==(roadNumber)) {
                 _roadNumber = roadNumber;
                 _index = index + 1;
                 return index;
             }
         }
     }
     _roadNumber = "";
     return -1;
 }

 /*public*/ Car* CarsTableModel::getCarAtIndex(int index) {
     return (Car*) sysList->at(index);
 }

 /*synchronized*/ void CarsTableModel::updateList()
{
  // first, remove listeners from the individual objects
  removePropertyChangeCars();
  sysList = getSelectedCarList();
  // and add listeners back in
  addPropertyChangeCars();
 }

 /*public*/ QList<RollingStock*>* CarsTableModel::getSelectedCarList() {
     return getCarList(_sort);
 }

 /*public*/ QList<RollingStock*>* CarsTableModel::getCarList(int sort) {
     QList<RollingStock*>* list;
     switch (sort) {
         case SORTBY_NUMBER:
             list = manager->getByNumberList();
             break;
         case SORTBY_ROAD:
             list = manager->getByRoadNameList();
             break;

         case SORTBY_TYPE:
             list = manager->getByTypeList();
             break;
         case SORTBY_COLOR:
             list = manager->getByColorList();
             break;
         case SORTBY_LOAD:
             list = manager->getByLoadList();
             break;
         case SORTBY_KERNEL:
             list = manager->getByKernelList();
             break;
         case SORTBY_LOCATION:
             list = manager->getByLocationList();
             break;
         case SORTBY_DESTINATION:
             list = manager->getByDestinationList();
             break;
         case SORTBY_TRAIN:
             list = manager->getByTrainList();
             break;
         case SORTBY_FINALDESTINATION:
             list = manager->getByFinalDestinationList();
             break;
         case SORTBY_RWE:
             list = manager->getByRweList();
             break;
         case SORTBY_MOVES:
             list = manager->getByMovesList();
             break;
         case SORTBY_BUILT:
             list = manager->getByBuiltList();
             break;
         case SORTBY_OWNER:
             list = manager->getByOwnerList();
             break;
         case SORTBY_VALUE:
             list = manager->getByValueList();
             break;
         case SORTBY_RFID:
             list = manager->getByRfidList();
             break;
         case SORTBY_WAIT:
             list = manager->getByWaitList();
             break;
         case SORTBY_PICKUP:
             list = manager->getByPickupList();
             break;
         case SORTBY_LAST:
             list = manager->getByLastDateList();
             break;
         default:
             list = manager->getByNumberList();

     }
     filterList(list);
     return list;
 }

 /*private*/ void CarsTableModel::filterList(QList<RollingStock*>* list) {
     if (showAllCars) {
         return;
     }
     for (int i = 0; i < list->size(); i++) {
         Car* car = (Car*) list->at(i);
         if (car->getLocation() == NULL) {
             list->removeAt(i--);
             continue;
         }
         // filter out cars that don't have a location name that matches
         if (locationName != NULL) {
             if (car->getLocationName()!=(locationName)) {
                 list->removeAt(i--);
                 continue;
             }
             if (trackName != NULL) {
                 if (car->getTrackName()!=(trackName)) {
                     list->removeAt(i--);
                 }
             }
         }
     }
 }

 void CarsTableModel::initTable(JTable* table, CarsTableFrame* frame) {
     _table = table;
     _frame = frame;
     initTable();
 }

 void CarsTableModel::initTable() {
     // Use XTableColumnModel so we can control which columns are visible
     XTableColumnModel* tcm = new XTableColumnModel(/*(AbstractTableModel*)_table->model()*/_table);
     _table->setColumnModel(tcm);
     _table->createDefaultColumnsFromModel();
#if 0 // TODO:
     // Install the button handlers
     ButtonRenderer buttonRenderer = new ButtonRenderer();
     tcm->getColumn(SET_COLUMN).setCellRenderer(buttonRenderer);
     TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());
     tcm->getColumn(SET_COLUMN).setCellEditor(buttonEditor);
     tcm->getColumn(EDIT_COLUMN).setCellRenderer(buttonRenderer);
     tcm->getColumn(EDIT_COLUMN).setCellEditor(buttonEditor);
#endif
     setColumnToHoldButton(_table,SET_COLUMN,NULL);
     setColumnToHoldButton(_table,EDIT_COLUMN,NULL);

#if 0 //TODO:
     // set column preferred widths
     if (!_frame.loadTableDetails(_table)) {
#endif
         // load defaults, xml file data not found
         // Cars frame table column widths, starts with Select column and ends with Edit
         QList<int> tableColumnWidths = QList<int>() << 60 << 60 << 60 << 65 << 35 << 75 << 75 << 75 << 65 << 190 << 190 << 190 << 190 << 65 << 50 << 50 << 50 << 50 << 50
             << 50 << 50 << 50 << 65 << 70;
         for (int i = 0; i < tcm->getColumnCount(false); i++)
         {
          tcm->getColumn(i)->setPreferredWidth(tableColumnWidths[i]);
         }
#if 0
     }
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
     _table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

     // turn off columns
     tcm->setColumnVisible(tcm->getColumnByModelIndex(SELECT_COLUMN), isSelectVisible);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(COLOR_COLUMN), false);

     tcm->setColumnVisible(tcm->getColumnByModelIndex(FINAL_DESTINATION_COLUMN), false);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(RWE_COLUMN), false);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(RWE_LOAD_COLUMN), false);

     tcm->setColumnVisible(tcm->getColumnByModelIndex(BUILT_COLUMN), false);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(OWNER_COLUMN), false);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(VALUE_COLUMN), false);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(RFID_COLUMN), false);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(WAIT_COLUMN), false);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(PICKUP_COLUMN), false);
     tcm->setColumnVisible(tcm->getColumnByModelIndex(LAST_COLUMN), false);
#endif
 }

 /*public*/ int CarsTableModel::rowCount(const QModelIndex &parent) const {
     return sysList->size();
 }

 /*public*/ int CarsTableModel::columnCount(const QModelIndex &parent) const {
     return HIGHESTCOLUMN;
 }

 /*public*/ QVariant CarsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case SELECT_COLUMN:
             return tr("Select");
         case NUMBER_COLUMN:
             return tr("Number");
         case ROAD_COLUMN:
             return tr("Road");
         case LOAD_COLUMN:
             return tr("Load");
         case COLOR_COLUMN:
             return tr("Color");
         case TYPE_COLUMN:
             return tr("Type");
         case LENGTH_COLUMN:
             return tr("Len");
         case KERNEL_COLUMN:
             return tr("Kernel");
         case LOCATION_COLUMN:
             return tr("Location");
         case DESTINATION_COLUMN:
             return tr("Destination");
         case FINAL_DESTINATION_COLUMN:
             return tr("FinalDestination");
         case RWE_COLUMN:
             return tr("ReturnWhenEmpty");
         case RWE_LOAD_COLUMN:
             return tr("RWELoad");
         case TRAIN_COLUMN:
             return tr("Train");
         case MOVES_COLUMN:
             return tr("Moves");
         case BUILT_COLUMN:
             return tr("Built");
         case OWNER_COLUMN:
             return tr("Owner");
         case VALUE_COLUMN:
             return Setup::getValueLabel();
         case RFID_COLUMN:
             return Setup::getRfidLabel();
         case WAIT_COLUMN:
             return tr("Wait");
         case PICKUP_COLUMN:
             return tr("Pickup");
         case LAST_COLUMN:
             return tr("LastMoved");
         case SET_COLUMN:
             return tr("Set");
         case EDIT_COLUMN:
             return tr("Edit");
         default:
             return "unknown"; // NOI18N
     }
  }
  return QVariant();
 }

// /*public*/ Class<?> getColumnClass(int col) {
//     switch (col) {
//         case SELECT_COLUMN:
//             return bool.class;
//         case SET_COLUMN:
//         case EDIT_COLUMN:
//             return JButton.class;
//         default:
//             return String.class;
//     }
// }

 /*public*/ Qt::ItemFlags CarsTableModel::flags(const QModelIndex &index) const
 {
     switch (index.column()) {
         case SELECT_COLUMN:
          Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled |Qt::ItemIsUserCheckable;
         case SET_COLUMN:
         case EDIT_COLUMN:
         case MOVES_COLUMN:
         case WAIT_COLUMN:
         case VALUE_COLUMN:
         case RFID_COLUMN:
             return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
         default:
             return Qt::ItemIsSelectable | Qt::ItemIsEnabled;;
     }
 }

 /*public*/ QVariant CarsTableModel::data(const QModelIndex &index, int role) const
 {
  int row = index.row();
  int col = index.column();
    if (row >= sysList->size()) {
        return "ERROR row " + row; // NOI18N
    }
    Car* car = (Car*) sysList->at(row);
    if (car == NULL) {
        return "ERROR car unknown " + row; // NOI18N
    }
  if(role == Qt::CheckStateRole)
  {
   if(col == SELECT_COLUMN)
    return car->isSelected()?Qt::Checked : Qt::Unchecked;
  }
  else
  if(role == Qt::DisplayRole)
  {
     switch (col) {
//         case SELECT_COLUMN:
//             return car->isSelected();
         case NUMBER_COLUMN:
             return car->getNumber();
         case ROAD_COLUMN:
             return car->getRoadName();
         case LOAD_COLUMN:
             if (car->getLoadPriority()==(CarLoad::PRIORITY_HIGH)) {
                 return car->getLoadName() + " " + tr("(P)");
             } else {
                 return car->getLoadName();
             }
         case COLOR_COLUMN:
             return car->getColor();
         case LENGTH_COLUMN:
             return car->getLengthInteger();
         case TYPE_COLUMN: {
             QString buf = car->getTypeName(); //new StringBuffer(car->getTypeName());
             if (car->isCaboose()) {
                 buf.append(" " + tr("(C)"));
             }
             if (car->hasFred()) {
                 buf.append(" " + tr("(F)"));
             }
             if (car->isPassenger()) {
                 buf.append(" " + tr("(P)") + " " + car->getBlocking());
             }
             if (car->isUtility()) {
                 buf.append(" " + tr("(U)"));
             }
             if (car->isHazardous()) {
                 buf.append(" " + tr("(H)"));
             }
             return buf/*.toString()*/;
         }
         case KERNEL_COLUMN: {
             if (car->getKernel() != NULL && car->getKernel()->isLead(car)) {
                 return car->getKernelName() + "*";
             }
             return car->getKernelName();
         }
         case LOCATION_COLUMN: {
             if (car->getLocation() != NULL) {
                 return car->getStatus() + car->getLocationName() + " (" + car->getTrackName() + ")";
             }
             return car->getStatus();
         }
         case DESTINATION_COLUMN:
         case FINAL_DESTINATION_COLUMN: {
             QString s = "";
             if (car->getDestination() != NULL) {
                 s = car->getDestinationName() + " (" + car->getDestinationTrackName() + ")";
             }
             if (car->getFinalDestination() != NULL) {
                 s = s + "->" + car->getFinalDestinationName(); // NOI18N
             }
             if (car->getFinalDestinationTrack() != NULL) {
                 s = s + " (" + car->getFinalDestinationTrackName() + ")";
             }
             return s;
         }
         case RWE_COLUMN:
             return car->getReturnWhenEmptyDestName();
         case RWE_LOAD_COLUMN:
             return car->getReturnWhenEmptyLoadName();
         case TRAIN_COLUMN: {
             // if train was manually set by user add an asterisk
             if (car->getTrain() != NULL && car->getRouteLocation() == NULL) {
                 return car->getTrainName() + "*";
             }
             return car->getTrainName();
         }
         case MOVES_COLUMN:
             return car->getMoves();
         case BUILT_COLUMN:
             return car->getBuilt();
         case OWNER_COLUMN:
             return car->getOwner();
         case VALUE_COLUMN:
             return car->getValue();
         case RFID_COLUMN:
             return car->getRfid();
         case WAIT_COLUMN:
             return car->getWait();
         case PICKUP_COLUMN:
             return car->getPickupScheduleName();
         case LAST_COLUMN:
             return car->getLastDate();
         case SET_COLUMN:
             return tr("Set");
         case EDIT_COLUMN:
             return tr("Edit");
         default:
             return "unknown " + col; // NOI18N
     }
  }
  return QVariant();
 }


 /*public*/ bool CarsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  Car* car = (Car*) sysList->at(index.row());
  if(role == Qt::CheckStateRole)
  {
   if(index.column() == SELECT_COLUMN)
   {

    car->setSelected(value.toBool());
   }
  }
  else
  if(role == Qt::EditRole)
  {
     //Car* car = (Car*) sysList->at(index.row());
     bool ok;

     switch (index.column()) {
//         case SELECT_COLUMN:
//             car->setSelected(value.toBool());
//             break;
         case SET_COLUMN:
             log->debug("Set car");

             if (csf != NULL) {
                 csf->dispose();
             }

             // use invokeLater so new window appears on top
//             SwingUtilities.invokeLater(new Runnable() {
//                 /*public*/ void run() {

                     csf = new CarSetFrame();
                     csf->initComponents();
                     csf->loadCar(car);
//                 }
//             });

             break;
         case EDIT_COLUMN:
             log->debug("Edit car");
             if (cef != NULL) {
                 cef->dispose();
             }
             // use invokeLater so new window appears on top
//             SwingUtilities.invokeLater(new Runnable() {
//                 /*public*/ void run() {
                     cef = new CarEditFrame();
                     cef->initComponents();
                     cef->loadCar(car);
//                 }
//             });
             break;
         case MOVES_COLUMN:
             //try {
                 car->setMoves(value.toString().toInt(&ok));
             if(!ok) {
                 log->error("move count must be a number");
             }
             break;
         case BUILT_COLUMN:
             car->setBuilt(value.toString());
             break;
         case OWNER_COLUMN:
             car->setOwner(value.toString());
             break;
         case VALUE_COLUMN:
             car->setValue(value.toString());
             break;
         case RFID_COLUMN:
             car->setRfid(value.toString());
             break;
         case WAIT_COLUMN:
             //try {
                 car->setWait(value.toInt(&ok));
             if(!ok) {
                 log->error("wait count must be a number");
             }
             break;
         case LAST_COLUMN:
             // do nothing
             break;
         default:
             break;
     }
   }
  return false;
  }

 /*public*/ void CarsTableModel::dispose()
 {
  if (log->isDebugEnabled())
  {
      log->debug("dispose CarTableModel");
  }
  //manager->removePropertyChangeListener(this);
  disconnect(manager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  removePropertyChangeCars();

  if (csf != NULL) {
      csf->dispose();
  }

  if (cef != NULL) {
      cef->dispose();
  }
 }

 /*private*/ void CarsTableModel::addPropertyChangeCars()
 {
  foreach (RollingStock* car, *manager->getList())
  {
   //car->addPropertyChangeListener(this);
   connect(car->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }

 /*private*/ void CarsTableModel::removePropertyChangeCars()
 {
  foreach (RollingStock* car, *manager->getList())
  {
      //car->removePropertyChangeListener(this);
   disconnect(car->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }

 /*public*/ void CarsTableModel::propertyChange(PropertyChangeEvent* e)
 {
  if (Control::SHOW_PROPERTY)
  {
   log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
           ->getNewValue().toString()));
  }
  if (e->getPropertyName()==(CarManager::LISTLENGTH_CHANGED_PROPERTY))
  {
   updateList();
   fireTableDataChanged();
  } // must be a car change
  else if (e->getSource()->metaObject()->className() ==("Car"))
  {
   Car* car = (Car*) e->getSource();
   int row = sysList->indexOf(car);
   if (Control::SHOW_PROPERTY)
   {
    log->debug(tr("Update car table row: %1").arg(row));
   }
   if (row >= 0)
   {
    fireTableRowsUpdated(row, row);
   }
  }
 }
 /*public*/ void CarsTableModel::setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/)
 { // TODO:
  // install a button renderer & editor
 //    ButtonRenderer buttonRenderer = new ButtonRenderer();
 //    table.setDefaultRenderer(JButton.class,buttonRenderer);
 //    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
 //    table.setDefaultEditor(JButton.class,buttonEditor);
 //    // ensure the table rows, columns have enough room for buttons
 //    table.setRowHeight(sample.getPreferredSize().height);
 //    table.getColumnModel().getColumn(column)
 //        .setPreferredWidth((sample.getPreferredSize().width)+4);
  table->setItemDelegateForColumn(column, new MyDelegate());
  for(int i = 0; i < rowCount(QModelIndex()); i ++)
   table->openPersistentEditor(index(i, column, QModelIndex()) );
 }
}
