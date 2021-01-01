#include "locationtrackblockingordertablemodel.h"
#include "propertychangeevent.h"
#include "location.h"
#include "track.h"
#include "jtable.h"
#include "xtablecolumnmodel.h"
#include "tablecolumn.h"
#include "pushbuttondelegate.h"
#include "control.h"
#include "logger.h"


namespace Operations
{
 /**
  * Table Model for edit of tracks used by operations
  *
  * @author Daniel Boudreau Copyright (C) 2015
  * @version $Revision: 28746 $
  */
 ///*public*/ class LocationTrackBlockingOrderTableModel extends AbstractTableModel implements PropertyChangeListener {

 /**
  *
  */
 //private static /*final*/ long serialVersionUID = -7318273766197527079L;



 /*public*/ LocationTrackBlockingOrderTableModel::LocationTrackBlockingOrderTableModel(QObject* parent)
    : AbstractTableModel(parent)
 {
     //super();
 log = new Logger("LocationTrackBlockingOrderTableModel");
     _tracksList = QList<Track*>();

 }

 /*synchronized*/ void LocationTrackBlockingOrderTableModel::updateList() {
     if (_location == NULL) {
         return;
     }
     // first, remove listeners from the individual objects
     removePropertyChangeTracks();

     _tracksList = _location->getTracksByBlockingOrderList(NULL);
     // and add them back in
     foreach (Track* track, _tracksList) {
         //track->addPropertyChangeListener(this);
      connect(track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     fireTableDataChanged();
 }

 /*protected*/ void LocationTrackBlockingOrderTableModel::initTable(JTable* table, Location* location) {
     _table = table;
     _location = location;
     if (_location != NULL) {
         //_location.addPropertyChangeListener(this);
      connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     initTable();
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
     //table->setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
     updateList();
 }

 /*private*/ void LocationTrackBlockingOrderTableModel::initTable() {
     // Use XTableColumnModel so we can control which columns are visible
     XTableColumnModel* tcm = new XTableColumnModel(/*(AbstractTableModel*)_table->model()*/_table);
     _table->setColumnModel(tcm);
     _table->createDefaultColumnsFromModel();
#if 0
     ButtonRenderer buttonRenderer = new ButtonRenderer();
     TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());

     tcm->getColumn(UP_COLUMN)->setCellRenderer(buttonRenderer);
     tcm->getColumn(UP_COLUMN)->setCellEditor(buttonEditor);
     tcm->getColumn(DOWN_COLUMN)->setCellRenderer(buttonRenderer);
     tcm->getColumn(DOWN_COLUMN)->setCellEditor(buttonEditor);
#endif
     _table->setItemDelegateForColumn(UP_COLUMN, new MyDelegate(this));
     _table->setItemDelegateForColumn(DOWN_COLUMN, new MyDelegate(this));

     // set column preferred widths
     tcm->getColumn(ID_COLUMN)->setPreferredWidth(40);
     tcm->getColumn(NAME_COLUMN)->setPreferredWidth(200);
     tcm->getColumn(TYPE_COLUMN)->setPreferredWidth(80);
     tcm->getColumn(ORDER_COLUMN)->setPreferredWidth(60);
     tcm->getColumn(UP_COLUMN)->setPreferredWidth(60);
     tcm->getColumn(DOWN_COLUMN)->setPreferredWidth(70);
 }

 /*public*/ int LocationTrackBlockingOrderTableModel::rowCount(const QModelIndex &parent) const {
     return _tracksList.size();
 }

 /*public*/ int LocationTrackBlockingOrderTableModel::columnCount(const QModelIndex &parent) const {
     return HIGHESTCOLUMN;
 }

 /*public*/ QVariant LocationTrackBlockingOrderTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case ID_COLUMN:
             return tr("Id");
         case NAME_COLUMN:
             return tr("Track Name");
         case TYPE_COLUMN:
             return tr("Type");
         case ORDER_COLUMN:
             return tr("Order");
         case UP_COLUMN:
             return tr("Up");
         case DOWN_COLUMN:
             return tr("Down");
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
//         case TYPE_COLUMN:
//             return String.class;
//         case ORDER_COLUMN:
//             return Integer.class;
//         case UP_COLUMN:
//             return JButton.class;
//         case DOWN_COLUMN:
//             return JButton.class;
//         default:
//             return NULL;
//     }
// }

 /*public*/ Qt::ItemFlags LocationTrackBlockingOrderTableModel::flags(const QModelIndex &index) const {
     switch (index.column()) {
         case ORDER_COLUMN:
         case UP_COLUMN:
         case DOWN_COLUMN:
             return Qt::ItemIsEnabled | Qt::ItemIsEditable;
         default:
             return Qt::ItemIsEnabled;
     }
 }

 /*public*/ QVariant LocationTrackBlockingOrderTableModel::data(const QModelIndex &index, int role) const
 {
  if(role == Qt::DisplayRole)
  {
   int row = index.row();
   int col = index.column();
     if (row >= _tracksList.size()) {
         return "ERROR row " + row; // NOI18N
     }
     Track* track = _tracksList.at(row);
     if (track == NULL) {
         return "ERROR track unknown " + row; // NOI18N
     }
     switch (col) {
         case ID_COLUMN:
             return track->getId();
         case NAME_COLUMN:
             return track->getName();
         case TYPE_COLUMN:
             return track->getTrackTypeName();
         case ORDER_COLUMN:
             return track->getBlockingOrder();
         case UP_COLUMN:
             return tr("Up");
         case DOWN_COLUMN:
             return tr("Down");
         default:
             return "unknown " + col; // NOI18N
     }
  }
  return QVariant();
 }

 /*public*/ bool LocationTrackBlockingOrderTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  if(role == Qt::EditRole)
  {
   int row = index.row();
   int col = index.column();
     if (row >= _tracksList.size()) {
         return false;
     }
     Track* track = _tracksList.at(row);
     if (track == NULL) {
         return false; // NOI18N
     }
     switch (col) {
         case ORDER_COLUMN:
             if ( value.toInt() >= 0)
                 track->setBlockingOrder( value.toInt());
             break;
         case UP_COLUMN:
             _location->changeTrackBlockingOrderEarlier(track);
             break;
         case DOWN_COLUMN:
             _location->changeTrackBlockingOrderLater(track);
             break;
         default:
             break;
     }
  }
  return false;
 }

 // this table listens for changes to a location and it's tracks
 /*public*/ void LocationTrackBlockingOrderTableModel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY)
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     if (e->getPropertyName()==(Location::TRACK_LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::TRACK_BLOCKING_ORDER_CHANGED_PROPERTY)) {
         updateList();
     }
     if (e->getPropertyName()==(Track::TRACK_BLOCKING_ORDER_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::TRACK_TYPE_CHANGED_PROPERTY)) {
         fireTableDataChanged();
     }
 }

 /*protected*/ void LocationTrackBlockingOrderTableModel::removePropertyChangeTracks() {
     foreach (Track* track, _tracksList) {
         //track->removePropertyChangeListener(this);
      disconnect(track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*public*/ void LocationTrackBlockingOrderTableModel::dispose() {
     // if (log.isDebugEnabled())
     // log.debug("dispose");
     removePropertyChangeTracks();
     if (_location != NULL) {
        // _location.removePropertyChangeListener(this);
      disconnect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     _tracksList.clear();
     fireTableDataChanged();
 }
}
