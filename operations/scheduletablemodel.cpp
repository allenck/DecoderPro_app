#include "scheduletablemodel.h"
#include "schedule.h"
#include "location.h"
#include "track.h"
#include "jtable.h"
#include "scheduleeditframe.h"
#include "scheduleitem.h"
#include "propertychangeevent.h"
#include "logger.h"
#include "control.h"
#include <QComboBox>
#include "carroads.h"
#include "track.h"
#include "xtablecolumnmodel.h"
#include "car.h"
#include "carmanager.h"
#include "carloads.h"
#include "pushbuttondelegate.h"
#include "vptr.h"
#include "locationmanager.h"
#include "trainschedulemanager.h"
#include "trainschedule.h"

namespace Operations
{
/**
 * Table Model for edit of a schedule used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2009, 2014
 * @version $Revision: 29681 $
 */
///*public*/ class ScheduleTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -2920410151470878120L;
 // Defines the columns


 /*public*/ ScheduleTableModel::ScheduleTableModel(QObject* parent)
  : AbstractTableModel(parent) {
     //super();
     _matchMode = false;
     _list = QList<ScheduleItem*>();
     log = new Logger("ScheduleTableModel");
     randomValues = QStringList() << ScheduleItem::NONE <<  "50" <<  "30" <<  "25" <<  "20" <<  "15" <<  "10" <<  "5" <<  "2" <<  "1";  // NOI18N
 }


 /*synchronized*/ void ScheduleTableModel::updateList() {
     if (_schedule == NULL ) {
         return;
     }
     // first, remove listeners from the individual objects
     removePropertyChangeScheduleItems();
     _list = _schedule->getItemsBySequenceList();
     // and add them back in
     foreach (ScheduleItem* si, _list) {
         //si.addPropertyChangeListener(this);
      connect(si->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         // TODO the following two property changes could be moved to ScheduleItem
         // covers the cases where destination or track is deleted
         if (si->getDestination() != NULL ) {
             //.getDestination().addPropertyChangeListener(this);
          connect(si->getDestination()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

         }
         if (si->getDestinationTrack() != NULL ) {
             //si.getDestinationTrack().addPropertyChangeListener(this);
          connect(si->getDestinationTrack()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }


 void ScheduleTableModel::initTable(ScheduleEditFrame* frame, JTable* table, Schedule* schedule, Location* location, Track* track) {
     _schedule = schedule;
     _location = location;
     _track = track;
     _table = table;
     _frame = frame;

     // add property listeners
     if (_schedule != NULL ) {
         //_schedule.addPropertyChangeListener(this);
      connect(_schedule->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     //_location.addPropertyChangeListener(this);
     connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //_track.addPropertyChangeListener(this);
     connect(_track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     initTable(table);
 }

 /*private*/ void ScheduleTableModel::initTable(JTable* table) {
     // Install the button handlers

  XTableColumnModel* tcm = new XTableColumnModel(/*(AbstractTableModel*)table->model()*/table);
  table->setColumnModel(tcm);
  table->createDefaultColumnsFromModel();
#if 0
     ButtonRenderer buttonRenderer = new ButtonRenderer();
     TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());
     tcm.getColumn(UP_COLUMN)->setCellRenderer(buttonRenderer);
     tcm.getColumn(UP_COLUMN)->setCellEditor(buttonEditor);
     tcm.getColumn(DOWN_COLUMN)->setCellRenderer(buttonRenderer);
     tcm.getColumn(DOWN_COLUMN)->setCellEditor(buttonEditor);
     tcm.getColumn(DELETE_COLUMN)->setCellRenderer(buttonRenderer);
     tcm.getColumn(DELETE_COLUMN)->setCellEditor(buttonEditor);
     table->setDefaultRenderer("JComboBox", new jmri.jmrit.symbolicprog.ValueRenderer());
     table->setDefaultEditor("JComboBox", new jmri.jmrit.symbolicprog.ValueEditor());
#endif
     table->setItemDelegateForColumn(UP_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(DOWN_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(DELETE_COLUMN, new MyDelegate());

     setPreferredWidths(table);

     // set row height
     //table->setRowHeight(QComboBox().sizeHint().height());

     table->setItemDelegateForColumn(UP_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(DOWN_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(DELETE_COLUMN, new MyDelegate());

     table->setItemDelegateForColumn(RANDOM_COLUMN, new STMComboBoxDelegate(this));
     table->setItemDelegateForColumn(SETOUT_DAY_COLUMN, new STMComboBoxDelegate(this));
     table->setItemDelegateForColumn(ROAD_COLUMN, new STMComboBoxDelegate(this));
     table->setItemDelegateForColumn(LOAD_COLUMN, new STMComboBoxDelegate(this));
     table->setItemDelegateForColumn(DEST_COLUMN, new STMComboBoxDelegate(this));
     table->setItemDelegateForColumn(TRACK_COLUMN, new STMComboBoxDelegate(this));
     table->setItemDelegateForColumn(PICKUP_DAY_COLUMN, new STMComboBoxDelegate(this));

     updateList();
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
     //table->setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
 }
#if 1
 /*private*/ void ScheduleTableModel::setPreferredWidths(JTable* table) {
     if (_frame->loadTableDetails(table)) {
         return; // done
     }
     log->debug("Setting preferred widths");
     // set column preferred widths
     table->getColumnModel()->getColumn(ID_COLUMN)->setPreferredWidth(35);
     table->getColumnModel()->getColumn(CURRENT_COLUMN)->setPreferredWidth(50);
     table->getColumnModel()->getColumn(TYPE_COLUMN)->setPreferredWidth(90);
     table->getColumnModel()->getColumn(RANDOM_COLUMN)->setPreferredWidth(60);
     table->getColumnModel()->getColumn(SETOUT_DAY_COLUMN)->setPreferredWidth(90);
     table->getColumnModel()->getColumn(ROAD_COLUMN)->setPreferredWidth(90);
     table->getColumnModel()->getColumn(LOAD_COLUMN)->setPreferredWidth(90);
     table->getColumnModel()->getColumn(SHIP_COLUMN)->setPreferredWidth(90);
     table->getColumnModel()->getColumn(DEST_COLUMN)->setPreferredWidth(130);
     table->getColumnModel()->getColumn(TRACK_COLUMN)->setPreferredWidth(130);
     table->getColumnModel()->getColumn(PICKUP_DAY_COLUMN)->setPreferredWidth(90);
     table->getColumnModel()->getColumn(COUNT_COLUMN)->setPreferredWidth(45);
     table->getColumnModel()->getColumn(WAIT_COLUMN)->setPreferredWidth(40);
     table->getColumnModel()->getColumn(UP_COLUMN)->setPreferredWidth(60);
     table->getColumnModel()->getColumn(DOWN_COLUMN)->setPreferredWidth(70);
     table->getColumnModel()->getColumn(DELETE_COLUMN)->setPreferredWidth(70);
 }
#endif
 /*public*/ int ScheduleTableModel::rowCount(const QModelIndex &/*parent*/) const
 {
  return _list.size();
 }

 /*public*/ int ScheduleTableModel::columnCount(const QModelIndex &/*parent*/) const
 {
  return HIGHEST_COLUMN;
 }

 /*public*/ QVariant ScheduleTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole  && orientation == Qt::Horizontal)
  {
   switch (section)
   {
    case ID_COLUMN:
        return tr("Id");
    case CURRENT_COLUMN:
        return tr("Current");
    case TYPE_COLUMN:
        return tr("Type");
    case RANDOM_COLUMN:
        return tr("Random");
    case SETOUT_DAY_COLUMN:
        return tr("Delivery");
    case ROAD_COLUMN:
        return tr("Road");
    case LOAD_COLUMN:
        return tr("Receive");
    case SHIP_COLUMN:
        return tr("Ship");
    case DEST_COLUMN:
        return tr("Destination");
    case TRACK_COLUMN:
        return tr("Track");
    case PICKUP_DAY_COLUMN:
        return tr("Pickup");
    case COUNT_COLUMN:
        if (_matchMode)
        {
            return tr("Hits");
        }
        return tr("Count");
    case WAIT_COLUMN:
        return tr("Wait");
    case UP_COLUMN:
        return tr("Up");
    case DOWN_COLUMN:
        return tr("Down");
    case DELETE_COLUMN:
        return tr("Delete");
    default:
        return "unknown"; // NOI18N
   }
  }
  return QVariant();
 }

 /*public*/ QString ScheduleTableModel::getColumnClass(int col) {
     switch (col) {
         case ID_COLUMN:
             return "String";
         case CURRENT_COLUMN:
             return "String";
         case TYPE_COLUMN:
             return "String";
         case RANDOM_COLUMN:
             return "JComboBox";
         case SETOUT_DAY_COLUMN:
             return "JComboBox";
         case ROAD_COLUMN:
             return "JComboBox";
         case LOAD_COLUMN:
             return "JComboBox";
         case SHIP_COLUMN:
             return "JComboBox";
         case DEST_COLUMN:
             return "JComboBox";
         case TRACK_COLUMN:
             return "JComboBox";
         case PICKUP_DAY_COLUMN:
             return "JComboBox";
         case COUNT_COLUMN:
             return "String";
         case WAIT_COLUMN:
             return "String";
         case UP_COLUMN:
             return "JButton";
         case DOWN_COLUMN:
             return "JButton";
         case DELETE_COLUMN:
             return "JButton";
         default:
             return "" ;
     }
 }

 /*public*/ Qt::ItemFlags ScheduleTableModel::flags(const QModelIndex &index) const
 {
  switch (index.column())
  {
   case RANDOM_COLUMN:
   case SETOUT_DAY_COLUMN:
   case ROAD_COLUMN:
   case LOAD_COLUMN:
   case SHIP_COLUMN:
   case DEST_COLUMN:
   case TRACK_COLUMN:
   case PICKUP_DAY_COLUMN:
   case COUNT_COLUMN:
   case WAIT_COLUMN:
   case UP_COLUMN:
   case DOWN_COLUMN:
   case DELETE_COLUMN:
       return Qt::ItemIsEditable | Qt::ItemIsEnabled;
   default:
       return Qt::ItemIsEnabled;;
  }
 }

 /*public*/ QVariant ScheduleTableModel::data(const QModelIndex &index, int role) const
 {
  if(role == Qt::DisplayRole)
  {
   int row = index.row();
   int col = index.column();
   if (row >= _list.size())
   {
    return "ERROR row " + QString::number(row); // NOI18N
   }
   ScheduleItem* si = _list.at(row);
   if (si == NULL )
   {
    return "ERROR schedule item unknown " + QString::number(row); // NOI18N
   }
   switch (col)
   {
    case ID_COLUMN:
        return si->getId();
    case CURRENT_COLUMN:
        return getCurrentPointer(si);
    case TYPE_COLUMN:
        return getType(si);
    case RANDOM_COLUMN:
        //return getRandomComboBox(si);
     return si->getRandom();
    case SETOUT_DAY_COLUMN:
        //return getSetoutDayComboBox(si);
     return si->getSetoutTrainScheduleId();
    case ROAD_COLUMN:
        //return getRoadComboBox(si);
        return si->getRoadName();
    case LOAD_COLUMN:
        //return getLoadComboBox(si);
        return si->getReceiveLoadName();
    case SHIP_COLUMN:
        //return getShipComboBox(si);
        return si->getShipLoadName();
    case DEST_COLUMN:
        //return getDestComboBox(si);
        return si->getTypeName();
    case TRACK_COLUMN:
        //return getTrackComboBox(si);
        if(si->getDestinationTrack() != NULL)
         return si->getDestinationTrack()->getName();
        else
         return "";
    case PICKUP_DAY_COLUMN:
        //return getPickupDayComboBox(si);
        return si->getPickupTrainScheduleId();
    case COUNT_COLUMN:
        if (_matchMode)
        {
            return si->getHits();
        }
        return si->getCount();
    case WAIT_COLUMN:
        return si->getWait();
    case UP_COLUMN:
        return tr("Up");
    case DOWN_COLUMN:
        return tr("Down");
    case DELETE_COLUMN:
        return tr("Delete");
    default:
        return "unknown " + QString::number(col); // NOI18N
   }
  }
  return QVariant();
 }

 /*public*/ bool ScheduleTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  if(role == Qt::EditRole)
  {
//     if (value == QVariant() ) {
//         log->debug("Warning schedule table row {} still in edit", row);
//         return;
//     }
   int col = index.column();
   int row = index.row();
   ScheduleItem* si = _list.at(index.row());
   switch (col)
   {
       case RANDOM_COLUMN:
           setRandom(value, row);
           break;
       case SETOUT_DAY_COLUMN:
           setSetoutDay(value, row);
           break;
       case ROAD_COLUMN:
           setRoad(value, row);
           break;
       case LOAD_COLUMN:
           setLoad(value, row);
           break;
       case SHIP_COLUMN:
           setShip(value, row);
           break;
       case DEST_COLUMN:
           setDestination(value, row);
           break;
       case TRACK_COLUMN:
           setTrack(value, row);
           break;
       case PICKUP_DAY_COLUMN:
           setPickupDay(value, row);
           break;
       case COUNT_COLUMN:
           setCount(value, row);
           break;
       case WAIT_COLUMN:
           setWait(value, row);
           break;
       case UP_COLUMN:
           moveUpScheduleItem(row);
           break;
       case DOWN_COLUMN:
           moveDownScheduleItem(row);
           break;
       case DELETE_COLUMN:
           deleteScheduleItem(row);
           break;
       default:
           break;
   }
  }
  return false;
 }

 /*private*/ QString ScheduleTableModel::getCurrentPointer(ScheduleItem* si) const
 {
  if (_track->getCurrentScheduleItem() == si) {
      if (si->getCount() > 1) {
          return " " + QString::number(_track->getScheduleCount()) + " -->"; // NOI18N
      } else {
          return "    -->"; // NOI18N
      }
  } else {
      return "";
  }
 }

 /*private*/ QString ScheduleTableModel::getType(ScheduleItem* si) const {
     if (_track->acceptsTypeName(si->getTypeName())) {
         return si->getTypeName();
     } else {
         return tr("Not Valid <%1>").arg(si->getTypeName());
     }
 }


 /*private*/ QComboBox* ScheduleTableModel::getRandomComboBox(ScheduleItem* si) {
     QComboBox* cb = new QComboBox();
     foreach (QString item, randomValues) {
         cb->addItem(item);
     }
     cb->setCurrentIndex(cb->findText(si->getRandom()));
     return cb;
 }

 /*private*/ QComboBox* ScheduleTableModel::getSetoutDayComboBox(ScheduleItem* si)
 {
     QComboBox* cb = TrainScheduleManager::instance()->getSelectComboBox();
     TrainSchedule* sch = TrainScheduleManager::instance()->getScheduleById(si->getSetoutTrainScheduleId());
     if (sch != NULL )
     {
      cb->setCurrentIndex(cb->findText(sch->toString()));
     }
     else if (si->getSetoutTrainScheduleId()!=(ScheduleItem::NONE))
     {
      // error user deleted this set out day
      QString notValid = tr("Not Valid <%1>").arg(si->getSetoutTrainScheduleId());
      TrainSchedule* errorSchedule = new TrainSchedule(si->getSetoutTrainScheduleId(), notValid);
      cb->addItem(errorSchedule->toString(), VPtr<TrainSchedule>::asQVariant(errorSchedule));
      cb->setCurrentIndex(cb->findText(errorSchedule->toString()));
     }
     return cb;
 }
 /*private*/ QComboBox* ScheduleTableModel::getRoadComboBox(ScheduleItem* si)
 {
  // log->debug("getRoadComboBox for ScheduleItem "+si->getType());
  QComboBox* cb = new QComboBox();
  cb->addItem(ScheduleItem::NONE);
  foreach (QString roadName, CarRoads::instance()->getNames())
  {
   if (getTrack()->acceptsRoadName(roadName))
   {
    Car* car = CarManager::instance()->getByTypeAndRoad(si->getTypeName(), roadName);
    if (car != NULL )
    {
     cb->addItem(roadName);
    }
   }
  }
  cb->setCurrentIndex(cb->findText(si->getRoadName()));
  if (cb->currentText()!=(si->getRoadName()))
  {
   QString notValid = QString("Not Valid <%1>").arg(si->getRoadName());
   cb->addItem(notValid);
   cb->setCurrentIndex(cb->findText(notValid));
  }
  return cb;
 }

 /*private*/ QComboBox* ScheduleTableModel::getLoadComboBox(ScheduleItem* si) {
     // log->debug("getLoadComboBox for ScheduleItem "+si->getType());
     QComboBox* cb = CarLoads::instance()->getSelectComboBox(si->getTypeName());
     filterLoads(si, cb); // remove loads not accepted by this track
     cb->setCurrentIndex(cb->findText(si->getReceiveLoadName()));
     if (cb->currentText()!=(si->getReceiveLoadName())) {
         QString notValid = ScheduleTableModel::tr("Not Valid <%1>").arg(si
             ->getReceiveLoadName());
         cb->addItem(notValid);
         cb->setCurrentIndex(cb->findText(notValid));
     }
     return cb;
 }


 /*private*/ QComboBox* ScheduleTableModel::getPickupDayComboBox(ScheduleItem* si) {
     QComboBox* cb = TrainScheduleManager::instance()->getSelectComboBox();
     TrainSchedule* sch = TrainScheduleManager::instance()->getScheduleById(si->getPickupTrainScheduleId());
     if (sch != NULL ) {
         cb->setCurrentIndex(cb->findText(sch->toString()));
     } else if (si->getPickupTrainScheduleId()!=(ScheduleItem::NONE)) {
         // error user deleted this pick up day
         QString notValid = tr("Not Valid <%1>").arg(si->getPickupTrainScheduleId());
         TrainSchedule* errorSchedule = new TrainSchedule(si->getSetoutTrainScheduleId(), notValid);
         cb->addItem(errorSchedule->toString(), VPtr<TrainSchedule>::asQVariant(errorSchedule));
         cb->setCurrentIndex(cb->findText(errorSchedule->toString()));
     }
     return cb;
 }

 /*private*/ QComboBox* ScheduleTableModel::getShipComboBox(ScheduleItem* si) {
     // log->debug("getShipComboBox for ScheduleItem "+si->getType());
     QComboBox* cb = CarLoads::instance()->getSelectComboBox(si->getTypeName());
     cb->setCurrentIndex(cb->findText(si->getShipLoadName()));
     if (cb->currentText()!=(si->getShipLoadName())) {
         QString notValid = tr("Not Valid <%1>").arg(si->getShipLoadName());
         cb->addItem(notValid);
         cb->setCurrentIndex(cb->findText(notValid));
     }
     return cb;
 }

 /*private*/ QComboBox* ScheduleTableModel::getDestComboBox(ScheduleItem* si) {
     // log->debug("getDestComboBox for ScheduleItem "+si->getType());
     QComboBox* cb = LocationManager::instance()->getComboBox();
     filterDestinations(cb, si->getTypeName());
     if (si->getDestination() != NULL  && cb->currentIndex() == -1) {
         // user deleted destination
         cb->addItem(si->getDestination()->toString(), VPtr<Location>::asQVariant(si->getDestination()));
     }
     cb->setCurrentIndex(cb->findData(VPtr<Location>::asQVariant(si->getDestination())));
     return cb;
 }

 /*private*/ QComboBox* ScheduleTableModel::getTrackComboBox(ScheduleItem* si)
 {
  // log->debug("getTrackComboBox for ScheduleItem "+si->getType());
  QComboBox* cb = new QComboBox();
  if (si->getDestination() != NULL )
  {
   Operations::Location* dest = si->getDestination();
   dest->updateComboBox(cb);
   filterTracks(dest, cb, si->getTypeName(), si->getRoadName(), si->getShipLoadName());
   if (si->getDestinationTrack() != NULL  && cb->currentIndex() == -1)
   {
    // user deleted track at destination, this is self correcting, when user restarts program, track
    // assignment will be gone.
    cb->addItem(si->getDestinationTrack()->toString(), VPtr<Track>::asQVariant(si->getDestinationTrack()));
   }
   cb->setCurrentIndex(cb->findData(VPtr<Track>::asQVariant(si->getDestinationTrack())));
  }
  return cb;
 }

 // set the count or hits if in match mode
 /*private*/ void ScheduleTableModel::setCount(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     int count;
     bool ok;
         count = value.toInt(&ok);
     if(!ok) {
         log->error("Schedule count or hits must be a number");
         return;
     }
     // we don't care what value the user sets the hit count
     if (_matchMode) {
         si->setHits(count);
         return;
     }
     if (count < 1) {
         log->error("Schedule count must be greater than 0");
         return;
     }
     if (count > 100) {
         log->warn("Schedule count must be 100 or less");
         count = 100;
     }
     si->setCount(count);
 }

 /*private*/ void ScheduleTableModel::setWait(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     int wait;
     bool ok;
         wait = value.toInt(&ok);
     if(!ok) {
         log->error("Schedule wait must be a number");
         return;
     }
     if (wait < 0) {
         log->error("Schedule wait must be a positive number");
         return;
     }
     if (wait > 10) {
         log->warn("Schedule wait must be 10 or less");
         wait = 10;
     }
     si->setWait(wait);
 }

 /*private*/ void ScheduleTableModel::setRandom(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     QString random = value.toString(); //(String) ((JComboBox<?>) value).getSelectedItem();
     si->setRandom(random);

 }

 /*private*/ void ScheduleTableModel::setSetoutDay(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     //Object obj = ((JComboBox<?>) value).getSelectedItem();
     TrainSchedule* obj = VPtr<TrainSchedule>::asPtr(value);
     if (obj == NULL ) {
         si->setSetoutTrainScheduleId(ScheduleItem::NONE);
     }
     else if (QString(obj->metaObject()->className())==("TrainSchedule")) {
         si->setSetoutTrainScheduleId(((TrainSchedule*) obj)->getId());
     }
 }

 /*private*/ void ScheduleTableModel::setPickupDay(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     //Object obj = ((JComboBox<?>) value).getSelectedItem();
     TrainSchedule* obj = VPtr<TrainSchedule>::asPtr(value);
     if (obj == NULL ) {
         si->setPickupTrainScheduleId(ScheduleItem::NONE);
     }
     else if (QString(obj->metaObject()->className())==("TrainSchedule")) {
         si->setPickupTrainScheduleId(((TrainSchedule*) obj)->getId());
     }
 }

 // note this method looks for String "Not Valid <>"
 /*private*/ void ScheduleTableModel::setRoad(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     QString road = value.toString();//String) ((JComboBox<?>) value).getSelectedItem();
     if (checkForNotValidString(road)) {
         si->setRoadName(road);
     }
 }

 // note this method looks for String "Not Valid <>"
 /*private*/ void ScheduleTableModel::setLoad(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     QString load = value.toString(); //String) ((JComboBox<?>) value).getSelectedItem();
     if (checkForNotValidString(load)) {
         si->setReceiveLoadName(load);
     }
 }

 // note this method looks for String "Not Valid <>"
 /*private*/ void ScheduleTableModel::setShip(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     QString load = value.toString(); //String) ((JComboBox<?>) value).getSelectedItem();
     if (checkForNotValidString(load)) {
         si->setShipLoadName(load);
     }
 }

 /*
  * Returns true if string is okay, doesn't have the string "Not Valid <>".
  */
 /*private*/ bool ScheduleTableModel::checkForNotValidString(QString s) {
     if (s.length() < 12) {
         return true;
     }
     QString test = s.mid(0, 11);
     if (test== tr("Not Valid<%1>").mid(0, 11)) {
         return false;
     }
     return true;
 }

 /*private*/ void ScheduleTableModel::setDestination(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     si->setDestinationTrack(NULL );
     Location* dest = VPtr<Location>::asPtr(value); //Location) ((JComboBox<?>) value).getSelectedItem();
     si->setDestination(dest);
     fireTableCellUpdated(row, TRACK_COLUMN);
 }

 /*private*/ void ScheduleTableModel::setTrack(QVariant value, int row) {
     ScheduleItem* si = _list.at(row);
     Track* track = VPtr<Track>::asPtr(value);//(Track) ((JComboBox<?>) value).getSelectedItem();
     si->setDestinationTrack(track);
 }

 /*private*/ void ScheduleTableModel::moveUpScheduleItem(int row) {
     log->debug("move schedule item up");
     _schedule->moveItemUp(_list.at(row));
 }

 /*private*/ void ScheduleTableModel::moveDownScheduleItem(int row) {
     log->debug("move schedule item down");
     _schedule->moveItemDown(_list.at(row));
 }

 /*private*/ void ScheduleTableModel::deleteScheduleItem(int row)
 {
  log->debug("Delete schedule item");
  _schedule->deleteItem(_list.at(row));
 }

 // remove destinations that don't service the car's type
 /*private*/ void ScheduleTableModel::filterDestinations(QComboBox* cb, QString carType)
 {
  for (int i = 1; i < cb->count(); i++)
  {
   Location* dest = VPtr<Location>::asPtr(cb->itemData(i));
   if (!dest->acceptsTypeName(carType))
   {
    cb->removeItem(cb->findData(VPtr<Location>::asQVariant(dest)));
    i--;
   }
  }
 }

 // remove destination tracks that don't service the car's type, road, or load
 /*private*/ void ScheduleTableModel::filterTracks(Location* loc, QComboBox* cb, QString carType, QString carRoad, QString carLoad)
 {
  QList<Track*> tracks = loc->getTrackList();
  foreach (Track* track, tracks)
  {
   if (!track->acceptsTypeName(carType) || track->getTrackType()==(Track::STAGING)
           || (carRoad!=(ScheduleItem::NONE) && !track->acceptsRoadName(carRoad))
           || (carLoad!=(ScheduleItem::NONE) && !track->acceptsLoad(carLoad, carType)))
   {
    cb->removeItem(cb->findData(VPtr<Track>::asQVariant(track)));
   }
  }
 }

 // remove receive loads not serviced by track
 /*private*/ void ScheduleTableModel::filterLoads(ScheduleItem* si, QComboBox* cb) {
     for (int i = cb->count() - 1; i > 0; i--) {
         QString loadName = cb->itemText(i);
         if (loadName!=(CarLoads::NONE) && !_track->acceptsLoad(loadName, si->getTypeName())) {
             cb->removeItem(cb->findText(loadName));
         }
     }
 }

//	private int _trainDirection = Setup.getDirectionInt(Setup.getTrainDirectionComboBox().getItemAt(0));
//
//	/*public*/ int getLastTrainDirection() {
//		return _trainDirection;
//	}
 /*public*/ void ScheduleTableModel::setMatchMode(bool mode) {
     if (mode != _matchMode) {
         _matchMode = mode;
         fireTableStructureChanged();
         initTable(_table);
     }
 }

 // this table listens for changes to a schedule and it's car types
 /*public*/ void ScheduleTableModel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Schedule::LISTCHANGE_CHANGED_PROPERTY)) {
         updateList();
         fireTableDataChanged();
     }
     if (e->getPropertyName()==(Track::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::ROADS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::LOADS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::SCHEDULE_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::DISPOSE_CHANGED_PROPERTY)) {
         fireTableDataChanged();
     }
     // update hit count or other schedule item?
     if (e->getSource()->metaObject()->className()==("ScheduleItem")) {
         ScheduleItem* item = (ScheduleItem*) e->getSource();
         int row = _list.indexOf(item);
         if (Control::SHOW_PROPERTY) {
             log->debug(tr("Update schedule item table row: %1").arg(row));
         }
         if (row >= 0) {
             fireTableRowsUpdated(row, row);
         }
     }
 }

 /*private*/ void ScheduleTableModel::removePropertyChangeScheduleItems() {
     foreach (ScheduleItem* si, _list) {
         //si->removePropertyChangeListener(this);
      disconnect(si->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         if (si->getDestination() != NULL ) {
             //si->getDestination().removePropertyChangeListener(this);
          disconnect(si->getDestination()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
         if (si->getDestinationTrack() != NULL ) {
             //si->getDestinationTrack().removePropertyChangeListener(this);
          disconnect(si->getDestinationTrack()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }

 /*public*/ void ScheduleTableModel::dispose() {
     if (log->isDebugEnabled()) {
         log->debug("dispose");
     }
     if (_schedule != NULL ) {
         removePropertyChangeScheduleItems();
         //_schedule.removePropertyChangeListener(this);
         disconnect(_schedule->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     //_location.removePropertyChangeListener(this);
     connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //_track.removePropertyChangeListener(this);
     connect(_track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 }
 /*public*/ Track* ScheduleTableModel::getTrack() {return _track;}


 STMComboBoxDelegate::STMComboBoxDelegate(ScheduleTableModel* model,  QObject *parent)
  : JComboBoxEditor(parent)
 {
  this->model  = model;
  this->items = QStringList();
  this->box = box;
 }


 QWidget *STMComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &index ) const
 {
  QComboBox* editor;
  ScheduleItem* si = model->_list.at(index.row());
  //editor = new QComboBox(box(si, this->model));
  switch (index.column())
  {
  case ScheduleTableModel::RANDOM_COLUMN:
   editor = model->getRandomComboBox(si);
   break;
  case ScheduleTableModel::SETOUT_DAY_COLUMN:
   editor = model->getSetoutDayComboBox(si);
   break;
  case ScheduleTableModel::ROAD_COLUMN:
   editor = model ->getRoadComboBox(si);
   break;
  case ScheduleTableModel::LOAD_COLUMN:
   editor = model->getLoadComboBox(si);
   break;
  case ScheduleTableModel::PICKUP_DAY_COLUMN:
   editor = model->getPickupDayComboBox(si);
   break;
  case ScheduleTableModel::SHIP_COLUMN:
   editor = model->getShipComboBox(si);
   break;
  case ScheduleTableModel::TRACK_COLUMN:
   editor = model->getTrackComboBox(si);
   break;
  default:
   break;
  }
  editor->setParent(parent);

  return editor;
 }

// void STMComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
// {
//   QComboBox *comboBox = static_cast<QComboBox*>(editor);
//   int value = index.model()->data(index, Qt::EditRole).toUInt();
//   comboBox->setCurrentIndex(value);
// }

// void STMComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
// {
//   QComboBox *comboBox = static_cast<QComboBox*>(editor);
//   model->setData(index, comboBox->currentText(), Qt::EditRole);
// }

// void STMComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
// {
//   editor->setGeometry(option.rect);
// }

}
