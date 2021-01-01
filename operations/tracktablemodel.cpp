#include "tracktablemodel.h"
#include "track.h"
#include "location.h"
#include "locationmanager.h"
#include "control.h"
#include "trackeditframe.h"
#include "xtablecolumnmodel.h"
#include <QLabel>
#include "jtable.h"
#include "pushbuttondelegate.h"

namespace Operations
{
/**
 * Table Model for edit of tracks used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2011, 2012
 * @version $Revision: 29493 $
 */
///*public*/ class TrackTableModel extends AbstractTableModel implements PropertyChangeListener {

    /**
     *
     */
    ///*private*/ static /*final*/ long serialVersionUID = -7318273766197527079L;




 /*public*/ TrackTableModel::TrackTableModel(QObject* parent) : AbstractTableModel(parent)
 {
     //super();
  log = new Logger("TrackTableModel");
  tracksList = QList<Track*>();
  tef = NULL;
  _sort = SORTBYNAME;
  _trackType = "";
  _showPoolColumn = false;
 }

 /*public*/ void TrackTableModel::setSort(int sort)
 {
  _sort = sort;
  updateList();
  fireTableDataChanged();
 }

 /*synchronized*/ void TrackTableModel::updateList()
 {
  if (_location == NULL) {
      return;
  }
  // first, remove listeners from the individual objects
  removePropertyChangeTracks();

  tracksList = _location->getTrackByNameList(_trackType);
  // and add them back in
  foreach (Track* track, tracksList)
  {
   //track->addPropertyChangeListener(this);
   connect(track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  if (_location->hasPools() && !_showPoolColumn)
  {
   _showPoolColumn = true;
   fireTableStructureChanged();
   initTable();
  }
 }

 /*protected*/ void TrackTableModel::initTable(JTable* table, Location* location, QString trackType)
 {
  _table = table;
  _location = location;
  /*synchronized (this)*/
  {
   _trackType = trackType;
  }
  if (_location != NULL)
  {
   //_location.addPropertyChangeListener(this);
   connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  initTable();
  // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
//     table.setAutoResizeMode(JTable::AUTO_RESIZE_OFF);
  updateList();
  fireTableDataChanged();
//  table->setMinimumHeight(table->rowHeight(0)*5);

 }

 /*private*/ void TrackTableModel::initTable()
 {
  // Use XTableColumnModel so we can control which columns are visible
  XTableColumnModel* tcm = new XTableColumnModel(/*(AbstractTableModel*)_table->model()*/_table);
  _table->setColumnModel(tcm);
  _table->createDefaultColumnsFromModel();

  // set column preferred widths
  tcm->getColumn(ID_COLUMN)->setPreferredWidth(40);
  tcm->getColumn(NAME_COLUMN)->setPreferredWidth(200);
  tcm->getColumn(LENGTH_COLUMN)->setPreferredWidth(
          qMax(50,  QLabel(getColumnName(LENGTH_COLUMN)).sizeHint().width() + 10));
  tcm->getColumn(USED_LENGTH_COLUMN)->setPreferredWidth(50);
  tcm->getColumn(RESERVED_COLUMN)->setPreferredWidth(
          qMax(65, QLabel(getColumnName(RESERVED_COLUMN)).sizeHint().width() + 10));
  tcm->getColumn(LOCOS_COLUMN)->setPreferredWidth(60);
  tcm->getColumn(CARS_COLUMN)->setPreferredWidth(60);
  tcm->getColumn(PICKUPS_COLUMN)->setPreferredWidth(
          qMax(60,  QLabel(getColumnName(PICKUPS_COLUMN)).sizeHint().width() + 10));
  tcm->getColumn(SETOUT_COLUMN)->setPreferredWidth(
          qMax(60,  QLabel(getColumnName(SETOUT_COLUMN)).sizeHint().width() + 10));
  tcm->getColumn(LOAD_COLUMN)->setPreferredWidth(50);
  tcm->getColumn(SHIP_COLUMN)->setPreferredWidth(50);
  tcm->getColumn(ROAD_COLUMN)->setPreferredWidth(50);
  tcm->getColumn(DESTINATION_COLUMN)->setPreferredWidth(50);
  tcm->getColumn(POOL_COLUMN)->setPreferredWidth(70);
  tcm->getColumn(PLANPICKUP_COLUMN)->setPreferredWidth(70);
  tcm->getColumn(ALT_TRACK_COLUMN)->setPreferredWidth(120);
  tcm->getColumn(EDIT_COLUMN)->setPreferredWidth(80);
#if 0
  tcm->getColumn(EDIT_COLUMN).setCellRenderer(new ButtonRenderer());
  tcm->getColumn(EDIT_COLUMN).setCellEditor(new ButtonEditor(new JButton()));
#endif
  _table->setItemDelegateForColumn(EDIT_COLUMN, new MyDelegate());
  setColumnsVisible();
//  QListIterator<TableColumn*> iter = tcm->getColumns(false);
//   while(iter.hasNext())
//   {
//    TableColumn* tc = iter.next();
//    _table->setColumnWidth(tc->getModelIndex(),tc->getPreferredWidth());
//   }

 }

 // only show "Load", "Ship", "Road", "Destination", "Planned", "Pool" "Alternate" if they are needed
 /*protected*/ void TrackTableModel::setColumnsVisible() {
#if 1
  XTableColumnModel* tcm = (XTableColumnModel*) _table->getColumnModel();
  tcm->setColumnVisible(tcm->getColumnByModelIndex(LOAD_COLUMN), _location->hasLoadRestrications());
  tcm->setColumnVisible(tcm->getColumnByModelIndex(SHIP_COLUMN), _location->hasShipLoadRestrications());
  tcm->setColumnVisible(tcm->getColumnByModelIndex(ROAD_COLUMN), _location->hasRoadRestrications());
  tcm->setColumnVisible(tcm->getColumnByModelIndex(DESTINATION_COLUMN), _location->hasDestinationRestrications());
  tcm->setColumnVisible(tcm->getColumnByModelIndex(PLANPICKUP_COLUMN), _location->hasPlannedPickups());
  tcm->setColumnVisible(tcm->getColumnByModelIndex(POOL_COLUMN), _location->hasPools());
  tcm->setColumnVisible(tcm->getColumnByModelIndex(ALT_TRACK_COLUMN), _location->hasAlternateTracks());
#endif
 }

 /*public*/ int TrackTableModel::rowCount(const QModelIndex &parent) const {
     return tracksList.size();
 }

 /*public*/ int TrackTableModel::columnCount(const QModelIndex &parent) const {
     return HIGHESTCOLUMN;
 }

 /*public*/ QVariant TrackTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
   switch (section)
   {
       case ID_COLUMN:
           return tr("Id");
       case NAME_COLUMN:
           return tr("Track Name");
       case LENGTH_COLUMN:
           return tr("Length");
       case USED_LENGTH_COLUMN:
           return tr("Used");
       case RESERVED_COLUMN:
           return tr("Reserved");
       case LOCOS_COLUMN:
           return tr("Engines");
       case CARS_COLUMN:
           return tr("Cars");
       case PICKUPS_COLUMN:
           return tr("Pickups");
       case SETOUT_COLUMN:
           return tr("Drop");
       case LOAD_COLUMN:
           return tr("Load");
       case SHIP_COLUMN:
           return tr("Ship");
       case ROAD_COLUMN:
           return tr("Road");
       case DESTINATION_COLUMN:
           return tr("Dest");
       case POOL_COLUMN:
           return tr("Pool");
       case PLANPICKUP_COLUMN:
           return tr("PlanPickUp");
       case ALT_TRACK_COLUMN:
           return tr("AlternateTrack");
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
//         case ID_COLUMN:
//             return String.class;
//         case NAME_COLUMN:
//             return String.class;
//         case LENGTH_COLUMN:
//             return String.class;
//         case USED_LENGTH_COLUMN:
//             return String.class;
//         case RESERVED_COLUMN:
//             return String.class;
//         case LOCOS_COLUMN:
//             return String.class;
//         case CARS_COLUMN:
//             return String.class;
//         case PICKUPS_COLUMN:
//             return String.class;
//         case SETOUT_COLUMN:
//             return String.class;
//         case LOAD_COLUMN:
//             return String.class;
//         case SHIP_COLUMN:
//             return String.class;
//         case ROAD_COLUMN:
//             return String.class;
//         case DESTINATION_COLUMN:
//             return String.class;
//         case POOL_COLUMN:
//             return String.class;
//         case PLANPICKUP_COLUMN:
//             return String.class;
//         case ALT_TRACK_COLUMN:
//             return String.class;
//         case EDIT_COLUMN:
//             return JButton.class;
//         default:
//             return NULL;
//     }
// }

 /*public*/ Qt::ItemFlags TrackTableModel::flags(const QModelIndex &index) const
 {
  switch (index.column())
  {
   case EDIT_COLUMN:
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
   default:
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
 }

 /*public*/ QVariant TrackTableModel::data(const QModelIndex &index, int role) const
 {
  if(role == Qt::DisplayRole)
  {
   int row = index.row();
   if (row >= tracksList.size())
   {
    return "ERROR row " + QString::number(row); // NOI18N
   }
   Track* track = tracksList.at(row);
   if (track == NULL)
   {
    return "ERROR track unknown " + QString::number(row); // NOI18N
   }
   int col;
   switch (col = index.column())
   {
    case ID_COLUMN:
        return track->getId();
    case NAME_COLUMN:
        return track->getName();
    case LENGTH_COLUMN:
        return (track->getLength());
    case USED_LENGTH_COLUMN:
        return (track->getUsedLength());
    case RESERVED_COLUMN:
        return (track->getReserved());
    case LOCOS_COLUMN:
        return (track->getNumberEngines());
    case CARS_COLUMN:
        return (track->getNumberCars());
    case PICKUPS_COLUMN:
        return (track->getPickupRS());
    case SETOUT_COLUMN:
        return (track->getDropRS());
    case LOAD_COLUMN:
        return getModifiedString(track->getLoadNames().length(), track->getLoadOption()==(Track::ALL_LOADS), track
                ->getLoadOption()==(Track::INCLUDE_LOADS));
    case SHIP_COLUMN:
        return getModifiedString(track->getShipLoadNames().length(),
                track->getShipLoadOption()==(Track::ALL_LOADS), track->getShipLoadOption()==(
                        Track::INCLUDE_LOADS));
    case ROAD_COLUMN:
        return getModifiedString(track->getRoadNames().length(), track->getRoadOption()==(Track::ALL_ROADS), track
                ->getRoadOption()==(track->INCLUDE_ROADS));
    case DESTINATION_COLUMN: {
        int length = track->getDestinationListSize();
        if (track->getDestinationOption()==(Track::EXCLUDE_DESTINATIONS)) {
            length = LocationManager::instance()->getNumberOfLocations() - length;
        }
        return getModifiedString(length, track->getDestinationOption()==(Track::ALL_DESTINATIONS), track
                ->getDestinationOption()==(track->INCLUDE_DESTINATIONS));
    }
    case POOL_COLUMN:
        return track->getPoolName();
    case PLANPICKUP_COLUMN:
        if (track->getIgnoreUsedLengthPercentage() > 0) {
            return track->getIgnoreUsedLengthPercentage() + "%";
        }
        return "";
    case ALT_TRACK_COLUMN:
        if (track->getAlternateTrack() != NULL) {
            return track->getAlternateTrack()->getName();
        }
        if (track->isAlternate()) {
            return tr("Yes");
        }
        return "";
    case EDIT_COLUMN:
        return tr("Edit");
    default:
           return "unknown " + col; // NOI18N
   }
  }
  return QVariant();
 }

 /*private*/ QString TrackTableModel::getModifiedString(int number, bool all, bool accept) const {
     if (all) {
         return "";
     }
     if (accept) {
         return "A " + QString::number(number); // NOI18N
     }
     return "E " + QString::number(number); // NOI18N
 }

 /*public*/ bool TrackTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
   switch (index.column())
   {
    case EDIT_COLUMN:
        editTrack(index.row());
        break;
    default:
        break;
   }
  }
  return false;
 }


 /*protected*/ void TrackTableModel::editTrack(int row)
 {
  log->debug("Edit tracks");

  if (tef != NULL) {
      tef->dispose();
  }


  // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
  tef = new TrackEditFrame();
  Track* tracks = tracksList.at(row);
  tef->initComponents(_location, tracks);
  tef->setTitle(tr("Edit Track"));
//         }
//     });

 }

 // this table listens for changes to a location and it's tracks
 /*public*/ void TrackTableModel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Location::TRACK_LISTLENGTH_CHANGED_PROPERTY)) {
         updateList();
         fireTableDataChanged();
     }
     if (QString(e->getSource()->metaObject()->className())==("Track")
             && (e->getPropertyName()==(Track::LOADS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::ROADS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::DESTINATION_OPTIONS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::POOL_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::PLANNEDPICKUPS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::ALTERNATE_TRACK_CHANGED_PROPERTY))) {
         setColumnsVisible();
     }
 }

 /*protected*/ void TrackTableModel::removePropertyChangeTracks()
 {
  foreach (Track* t, tracksList)
  {
      //t.removePropertyChangeListener(this);
   disconnect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }

 /*public*/ void TrackTableModel::dispose()
 {
  // if (log.isDebugEnabled())
  // log.debug("dispose");
  removePropertyChangeTracks();
  if (_location != NULL) {
      //_location.removePropertyChangeListener(this);
   disconnect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }

  if (tef != NULL) {
      tef->dispose();
  }

  tracksList.clear();
  fireTableDataChanged();
 }

}
