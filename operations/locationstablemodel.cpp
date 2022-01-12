#include "locationstablemodel.h"
#include "locationmanager.h"
#include "location.h"
#include "control.h"
#include "operationsframe.h"
#include "locationeditframe.h"
#include "yardmasterframe.h"
#include "xtablecolumnmodel.h"
#include "jtable.h"
#include "QLabel"
#include "pushbuttondelegate.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Table Model for edit of locations used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2013
 * @version $Revision: 29638 $
 */
///*public*/ class LocationsTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 8385333181895879131L;



 /*private*/ /*static*/ /*final*/ int LocationsTableModel::HIGHEST_COLUMN = LocationsTableModel::EDIT_COLUMN + 1;

 /*public*/ LocationsTableModel::LocationsTableModel(QObject* parent) : AbstractTableModel(parent)
 {
  //super();
  log = new Logger("OperationsTableModel");
  _sort = SORTBYNAME;

  locationManager = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"));
  //locationManager.addPropertyChangeListener(this);
  connect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateList();
 }


 /*public*/ void LocationsTableModel::setSort(int sort) {
     /*synchronized (this)*/ {
         _sort = sort;
     }
     updateList();
     fireTableDataChanged();
 }

 /*private*/ /*synchronized*/ void LocationsTableModel::updateList() {
     // first, remove listeners from the individual objects
     removePropertyChangeLocations();

     if (_sort == SORTBYID) {
         locationsList = locationManager->getLocationsByIdList();
     } else {
         locationsList = locationManager->getLocationsByNameList();
     }
     // and add them back in
     foreach (Location* loc, locationsList) {
      loc->SwingPropertyChangeSupport::addPropertyChangeListener(this);
     }
 }


 void LocationsTableModel::initTable(JTable* table)
 {
     // Install the button handlers
#if 0
     TableColumnModel tcm = table.getColumnModel();
#endif
     // Use XTableColumnModel so we can control which columns are visible
     XTableColumnModel* tcm = new XTableColumnModel(/*(AbstractTableModel*)table->model()*/table);
     table->setColumnModel(tcm);
     table->createDefaultColumnsFromModel();
#if 0
     ButtonRenderer buttonRenderer = new ButtonRenderer();
     TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());
     tcm.getColumn(ACTIONCOLUMN).setCellRenderer(buttonRenderer);
     tcm.getColumn(ACTIONCOLUMN).setCellEditor(buttonEditor);
     tcm.getColumn(EDITCOLUMN).setCellRenderer(buttonRenderer);
     tcm.getColumn(EDITCOLUMN).setCellEditor(buttonEditor);
#endif
     table->setItemDelegateForColumn(ACTION_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(EDIT_COLUMN, new MyDelegate());
     // set column preferred widths
     table->getColumnModel()->getColumn(ID_COLUMN)->setPreferredWidth(40);
     table->getColumnModel()->getColumn(NAME_COLUMN)->setPreferredWidth(200);
     table->getColumnModel()->getColumn(TRACK_COLUMN)->setPreferredWidth(
             qMax(60, QLabel(tr("Class/Interchange") + tr("Spurs")
                     + tr("Yards")).sizeHint().width() + 20));
     table->getColumnModel()->getColumn(NUMBER_COLUMN)->setPreferredWidth(40);
     table->getColumnModel()->getColumn(LENGTH_COLUMN)->setPreferredWidth(
             qMax(60, QLabel(getColumnName(LENGTH_COLUMN)).sizeHint().width() + 10));
     table->getColumnModel()->getColumn(USED_LENGTH_COLUMN)->setPreferredWidth(60);
     table->getColumnModel()->getColumn(ROLLINGSTOCK_COLUMN)->setPreferredWidth(
             qMax(80, QLabel(getColumnName(ROLLINGSTOCK_COLUMN)).sizeHint().width() + 10));
     table->getColumnModel()->getColumn(CARS_COLUMN)->setPreferredWidth(60);
     table->getColumnModel()->getColumn(LOCOS_COLUMN)->setPreferredWidth(60);
     table->getColumnModel()->getColumn(PICKUPS_COLUMN)->setPreferredWidth(
             qMax(60, QLabel(getColumnName(PICKUPS_COLUMN)).sizeHint().width() + 10));
     table->getColumnModel()->getColumn(DROPS_COLUMN)->setPreferredWidth(
             qMax(60, QLabel(getColumnName(DROPS_COLUMN)).sizeHint().width() + 10));
     table->getColumnModel()->getColumn(ACTION_COLUMN)->setPreferredWidth(
             qMax(80, QLabel(tr("Yardmaster")).sizeHint().width() + 40));
     table->getColumnModel()->getColumn(EDIT_COLUMN)->setPreferredWidth(80);
//     table->setMinimumHeight(table->rowHeight*5);
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
#if 0
     table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
#endif
 }

 /*public*/ int LocationsTableModel::rowCount(const QModelIndex &parent) const
 {
     return locationsList.size();
 }

 /*public*/ int LocationsTableModel::columnCount(const QModelIndex &parent) const
 {
     return HIGHEST_COLUMN;
 }

 /*public*/ QVariant LocationsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case ID_COLUMN:
             return tr("Id");
         case NAME_COLUMN:
             return tr("Name");
         case TRACK_COLUMN:
             return tr("Track");
         case NUMBER_COLUMN:
             return tr("Number");
         case LENGTH_COLUMN:
             return tr("Length");
         case USED_LENGTH_COLUMN:
             return tr("Used");
         case ROLLINGSTOCK_COLUMN:
             return tr("RollingStock");
         case LOCOS_COLUMN:
             return tr("Engines");
         case CARS_COLUMN:
             return tr("Cars");
         case PICKUPS_COLUMN:
             return tr("Pickups");
         case DROPS_COLUMN:
             return tr("Drop");
         case ACTION_COLUMN:
             return tr("Action");
         case EDIT_COLUMN:
             return tr("Edit"); // edit column
         case DIVISION_COLUMN:
             return tr("Division");
         case REPORTER_COLUMN:
             return tr("Reporters");
         default:
             return "unknown"; // NOI18N
     }
  }
  return QVariant();
 }

 /*public*/ QString LocationsTableModel::getColumnClass(int col)const{
     switch (col) {
         case ID_COLUMN:
         case NAME_COLUMN:
         case TRACK_COLUMN:
         case DIVISION_COLUMN:
         case REPORTER_COLUMN:
         case LENGTH_COLUMN:
         case USED_LENGTH_COLUMN:
         case ROLLINGSTOCK_COLUMN:
         case LOCOS_COLUMN:
         case CARS_COLUMN:
             return "String";
         case PICKUPS_COLUMN:
             return "Integer";
         case DROPS_COLUMN:
             return "Integer";
         case ACTION_COLUMN:
             return "JButton";
         case EDIT_COLUMN:
             return "JButton";
         default:
             return NULL;
     }
 }

 /*public*/ Qt::ItemFlags LocationsTableModel::flags(const QModelIndex &index) const {
     switch (index.column()) {
         case EDIT_COLUMN:
         case ACTION_COLUMN:
             return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
         default:
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
     }
 }

 /*public*/ QVariant LocationsTableModel::data(const QModelIndex &index, int role) const
 {
  if(role == Qt::DisplayRole)
  {
   int row = index.row();
   int col =index.column();
     if (row >= rowCount(QModelIndex())) {
         return "ERROR row " + QString::number(row); // NOI18N
     }
     Location* l = locationsList.at(row);
     if (l == NULL) {
         return "ERROR location unknown " + QString::number(row); // NOI18N
     }
     switch (col) {
         case ID_COLUMN:
             return l->getId();
         case NAME_COLUMN:
             return l->getName();
         case TRACK_COLUMN:
             return getTrackTypes(l);
         case NUMBER_COLUMN:
             return l->getTracksList().size();
         case LENGTH_COLUMN:
             return (l->getLength());
         case USED_LENGTH_COLUMN:
             return (l->getUsedLength());
         case ROLLINGSTOCK_COLUMN:
             return (l->getNumberRS());
         case LOCOS_COLUMN:
             return l->getNumberEngines();
         case CARS_COLUMN:
             return l->getNumberCars();
         case PICKUPS_COLUMN:
             return (l->getPickupRS());
         case DROPS_COLUMN:
             return (l->getDropRS());
         case ACTION_COLUMN:
             return tr("Yardmaster");
         case EDIT_COLUMN:
             return tr("Edit");
         case DIVISION_COLUMN:
             return l->getDivisionName();
         case REPORTER_COLUMN:
             return l->getReporterName();
         default:
             return "unknown " + col; // NOI18N
     }
  }
  return QVariant();
 }

 /*private*/ QString LocationsTableModel::getTrackTypes(Location* location) const {
     if (location->isStaging()) {
         return (tr("Staging"));
     } else {
         QString sb = "";
         if (location->hasInterchanges()) {
             sb.append(tr("Class/Interchange") + " ");
         }
         if (location->hasSpurs()) {
             sb.append(tr("Spurs") + " ");
         }
         if (location->hasYards()) {
             sb.append(tr("Yards"));
         }
         return sb/*.toString()*/;
     }
 }

 /*public*/ bool LocationsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  if(role == Qt::EditRole)
  {
   int col = index.column();
   int row = index.row();
     switch (col) {
         case ACTION_COLUMN:
             launchYardmaster(row);
             break;
         case EDIT_COLUMN:
             editLocation(row);
             break;
         default:
             break;
     }
  }
  return false;
 }


 /*private*/ /*synchronized*/ void LocationsTableModel::editLocation(int row) {
     // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
             Location* loc = locationsList.at(row);
             log->debug(tr("Edit location (%1)").arg(loc->getName()));
             foreach (LocationEditFrame* lef, frameList)
             {
                 if (lef->_location == loc)
                 {
                     lef->dispose();
                     frameList.removeOne(lef);
                     break;
                 }
             }
             LocationEditFrame* lef = new LocationEditFrame(loc);
             frameList.append(lef);
//         }
//     });
 }

 /*private*/ /*synchronized*/ void LocationsTableModel::launchYardmaster(int row) {
     // use invokeLater so new window appears on top

//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
             log->debug("Yardmaster");
             Location* loc = locationsList.at(row);
             new YardmasterFrame(loc);
//         }
//     });

 }

 /*public*/ void LocationsTableModel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateList();
         fireTableDataChanged();
     } else if (e->getSource()->metaObject()->className()==("Location")) {
         Location* loc = (Location*) e->getSource();
         int row = locationsList.indexOf(loc);
         if (Control::SHOW_PROPERTY) {
             log->debug(tr("Update location table row: %1 name: {%2").arg(row).arg(loc->getName()));
         }
         if (row >= 0) {
             fireTableRowsUpdated(row, row);
         }
     }
 }

 /*private*/ /*synchronized*/ void LocationsTableModel::removePropertyChangeLocations() {
     if (!locationsList.isEmpty()) {
         foreach (Location* loc, locationsList) {
          loc->removePropertyChangeListener(this);
         }
     }
 }

 /*public*/ void LocationsTableModel::dispose() {
     if (log->isDebugEnabled()) {
         log->debug("dispose");
     }
     foreach(LocationEditFrame* lef, frameList) {
         lef->dispose();
     }
     //locationManager.removePropertyChangeListener(this);
     disconnect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeLocations();
 }

}
