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



 /*private*/ /*static*/ /*final*/ int LocationsTableModel::HIGHESTCOLUMN = LocationsTableModel::EDITCOLUMN + 1;

 /*public*/ LocationsTableModel::LocationsTableModel(QObject* parent) : AbstractTableModel(parent)
 {
  //super();
  log = new Logger("OperationsTableModel");
  _sort = SORTBYNAME;

  locationManager = LocationManager::instance();
  //locationManager.addPropertyChangeListener(this);
  connect(locationManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
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
         //loc.addPropertyChangeListener(this);
      connect(loc->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
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
     table->setItemDelegateForColumn(ACTIONCOLUMN, new MyDelegate());
     table->setItemDelegateForColumn(EDITCOLUMN, new MyDelegate());
     // set column preferred widths
     table->getColumnModel()->getColumn(IDCOLUMN)->setPreferredWidth(40);
     table->getColumnModel()->getColumn(NAMECOLUMN)->setPreferredWidth(200);
     table->getColumnModel()->getColumn(TRACKCOLUMN)->setPreferredWidth(
             qMax(60, QLabel(tr("Class/Interchange") + tr("Spurs")
                     + tr("Yards")).sizeHint().width() + 20));
     table->getColumnModel()->getColumn(LENGTHCOLUMN)->setPreferredWidth(
             qMax(60, QLabel(getColumnName(LENGTHCOLUMN)).sizeHint().width() + 10));
     table->getColumnModel()->getColumn(USEDLENGTHCOLUMN)->setPreferredWidth(60);
     table->getColumnModel()->getColumn(ROLLINGSTOCK)->setPreferredWidth(
             qMax(80, QLabel(getColumnName(ROLLINGSTOCK)).sizeHint().width() + 10));
     table->getColumnModel()->getColumn(PICKUPS)->setPreferredWidth(
             qMax(60, QLabel(getColumnName(PICKUPS)).sizeHint().width() + 10));
     table->getColumnModel()->getColumn(DROPS)->setPreferredWidth(
             qMax(60, QLabel(getColumnName(DROPS)).sizeHint().width() + 10));
     table->getColumnModel()->getColumn(ACTIONCOLUMN)->setPreferredWidth(
             qMax(80, QLabel(tr("Yardmaster")).sizeHint().width() + 40));
     table->getColumnModel()->getColumn(EDITCOLUMN)->setPreferredWidth(80);
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
     return HIGHESTCOLUMN;
 }

 /*public*/ QVariant LocationsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case IDCOLUMN:
             return tr("Id");
         case NAMECOLUMN:
             return tr("Name");
         case TRACKCOLUMN:
             return tr("Track");
         case LENGTHCOLUMN:
             return tr("Length");
         case USEDLENGTHCOLUMN:
             return tr("Used");
         case ROLLINGSTOCK:
             return tr("RollingStock");
         case PICKUPS:
             return tr("Pickups");
         case DROPS:
             return tr("Drop");
         case ACTIONCOLUMN:
             return tr("Action");
         case EDITCOLUMN:
             return tr("Edit"); // edit column
         default:
             return "unknown"; // NOI18N
     }
  }
  return QVariant();
 }

// /*public*/ Class<?> getColumnClass(int col) {
//     switch (col) {
//         case IDCOLUMN:
//             return String.class;
//         case NAMECOLUMN:
//             return String.class;
//         case TRACKCOLUMN:
//             return String.class;
//         case LENGTHCOLUMN:
//             return String.class;
//         case USEDLENGTHCOLUMN:
//             return String.class;
//         case ROLLINGSTOCK:
//             return String.class;
//         case PICKUPS:
//             return String.class;
//         case DROPS:
//             return String.class;
//         case ACTIONCOLUMN:
//             return JButton.class;
//         case EDITCOLUMN:
//             return JButton.class;
//         default:
//             return NULL;
//     }
// }

 /*public*/ Qt::ItemFlags LocationsTableModel::flags(const QModelIndex &index) const {
     switch (index.column()) {
         case EDITCOLUMN:
         case ACTIONCOLUMN:
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
         return "ERROR row " + row; // NOI18N
     }
     Location* l = locationsList.at(row);
     if (l == NULL) {
         return "ERROR location unknown " + row; // NOI18N
     }
     switch (col) {
         case IDCOLUMN:
             return l->getId();
         case NAMECOLUMN:
             return l->getName();
         case TRACKCOLUMN:
             return getTrackTypes(l);
         case LENGTHCOLUMN:
             return (l->getLength());
         case USEDLENGTHCOLUMN:
             return (l->getUsedLength());
         case ROLLINGSTOCK:
             return (l->getNumberRS());
         case PICKUPS:
             return (l->getPickupRS());
         case DROPS:
             return (l->getDropRS());
         case ACTIONCOLUMN:
             return tr("Yardmaster");
         case EDITCOLUMN:
             return tr("Edit");
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
         case ACTIONCOLUMN:
             launchYardmaster(row);
             break;
         case EDITCOLUMN:
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
             //loc.removePropertyChangeListener(this);
          disconnect(loc->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
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
     disconnect(locationManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeLocations();
 }

}
