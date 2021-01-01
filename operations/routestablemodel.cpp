#include "routestablemodel.h"
#include "control.h"
#include "route.h"
#include "routemanager.h"
#include "locationmanager.h"
#include "propertychangeevent.h"
#include "tablecolumnmodel.h"
#include "jtable.h"
#include "tablecolumn.h"
#include "xtablecolumnmodel.h"
#include "routeeditframe.h"
#include "pushbuttondelegate.h"

namespace Operations
{
/**
 * Table Model for edit of routes used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008
 * @version $Revision: 29493 $
 */
///*public*/ class RoutesTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

    /**
     *
     */
    ///*private*/ static final long serialVersionUID = -6951642152186049680L;




 /*public*/ RoutesTableModel::RoutesTableModel(QObject* parent) : AbstractTableModel(parent)
 {
     //super();
 _sort = SORTBYNAME;
  sysList = QList<Route*>();
  ref = NULL;
  log = new Logger("RoutesTableModel");


     manager = RouteManager::instance();
     //manager.addPropertyChangeListener(this);
     connect(manager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //LocationManager::instance().addPropertyChangeListener(this);
     connect(LocationManager::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     updateList();
 }



 /*public*/ void RoutesTableModel::setSort(int sort) {
     /*synchronized (this)*/ {
         _sort = sort;
     }
     updateList();
     fireTableDataChanged();
 }

 /*private*/ /*synchronized*/ void RoutesTableModel::updateList() {
     // first, remove listeners from the individual objects
     removePropertyChangeRoutes();

     if (_sort == SORTBYID) {
         sysList = manager->getRoutesByIdList();
     } else {
         sysList = manager->getRoutesByNameList();
     }
     // and add them back in
     foreach (Route* route, sysList) {
         //route.addPropertyChangeListener(this);
      connect(route->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }


 void RoutesTableModel::initTable(JTable* table) {
     // Install the button handlers
#if 1
     //TableColumnModel* tcm = table->getColumnModel();
  // Use XTableColumnModel so we can control which columns are visible
  XTableColumnModel* tcm = new XTableColumnModel(/*(AbstractTableModel*)table->model()*/table);
  table->setColumnModel(tcm);
  table->createDefaultColumnsFromModel();
//     ButtonRenderer buttonRenderer = new ButtonRenderer();
//     TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());
//     tcm->getColumn(EDITCOLUMN).setCellRenderer(buttonRenderer);
//     tcm.getColumn(EDITCOLUMN).setCellEditor(buttonEditor);
  table->setItemDelegateForColumn(EDITCOLUMN, new MyDelegate());
     // set column preferred widths
     table->getColumnModel()->getColumn(IDCOLUMN)->setPreferredWidth(30);
     table->getColumnModel()->getColumn(NAMECOLUMN)->setPreferredWidth(220);
     table->getColumnModel()->getColumn(COMMENTCOLUMN)->setPreferredWidth(300);
     table->getColumnModel()->getColumn(STATUSCOLUMN)->setPreferredWidth(70);
     table->getColumnModel()->getColumn(EDITCOLUMN)->setPreferredWidth(80);
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
//     table->setAutoResizeMode(JTable::AUTO_RESIZE_OFF);
#endif
 }

 /*public*/ int RoutesTableModel::rowCount(const QModelIndex &parent) const{
     return sysList.size();
 }

 /*public*/ int RoutesTableModel::columnCount(const QModelIndex &parent) const {
     return HIGHESTCOLUMN;
 }

 /*public*/ QVariant RoutesTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case IDCOLUMN:
             return tr("Id");
         case NAMECOLUMN:
             return tr("Name");
         case COMMENTCOLUMN:
             return tr("Comment");
         case STATUSCOLUMN:
             return tr("Status");
         case EDITCOLUMN:
             return ""; // edit column
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
//         case COMMENTCOLUMN:
//             return String.class;
//         case STATUSCOLUMN:
//             return String.class;
//         case EDITCOLUMN:
//             return JButton.class;
//         default:
//             return NULL;
//     }
// }

 /*public*/ Qt::ItemFlags RoutesTableModel::flags(const QModelIndex &index) const {
     switch (index.column()) {
         case EDITCOLUMN:
             return Qt::ItemIsEditable | Qt::ItemIsEnabled;
         default:
             return Qt::ItemIsEnabled ;
     }
 }

 /*public*/ QVariant RoutesTableModel::data(const QModelIndex &index, int role) const
 {
  if(role == Qt::DisplayRole)
  {
   int row = index.row();
   int col = index.column();
     if (row >= sysList.size()) {
         return "ERROR unknown " + row; // NOI18N
     }
     Route* r = sysList.at(row);
     if (r == NULL) {
         return "ERROR route unknown " + QString::number(row); // NOI18N
     }
     switch (col) {
         case IDCOLUMN:
             return r->getId();
         case NAMECOLUMN:
             return r->getName();
         case COMMENTCOLUMN:
             return r->getComment();
         case STATUSCOLUMN:
             return r->getStatus();
         case EDITCOLUMN:
             return tr("Edit");
         default:
             return "unknown " + col; // NOI18N
   }
  }
  return QVariant();
 }

 /*public*/ bool RoutesTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  if(role == Qt::EditRole)
  {
   int row = index.row();
   int col = index.column();

     switch (col) {
         case EDITCOLUMN:
             editRoute(row);
             break;
         default:
             break;
     }
  }
  return false;
 }


 /*private*/ /*synchronized*/ void RoutesTableModel::editRoute(int row) {
     log->debug("Edit route");

     if (ref != NULL) {
         ref->dispose();
     }
//     // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
             ref = new RouteEditFrame();
             Route* route = sysList.at(row);
             ref->initComponents(route);
//         }
//     });

 }

 /*public*/ void RoutesTableModel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)) {
         fireTableDataChanged();
     } else if (e->getPropertyName()==(RouteManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateList();
         fireTableDataChanged();
     } else if (e->getSource()->metaObject()->className()==("Route")) {
         Route* route = (Route*) e->getSource();
         int row = sysList.indexOf(route);
         if (Control::SHOW_PROPERTY) {
             log->debug(tr("Update route table row: %1 id: %2").arg(row).arg(route->getId()));
         }
         if (row >= 0) {
             fireTableRowsUpdated(row, row);
         }
     }
 }

 /*private*/ /*synchronized*/ void RoutesTableModel::removePropertyChangeRoutes() {
     if (!sysList.isEmpty()) {
         foreach (Route* route, sysList) {
             //route.removePropertyChangeListener(this);
          disconnect(route->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     }
 }

 /*public*/ void RoutesTableModel::dispose() {
     if (log->isDebugEnabled()) {
         log->debug("dispose");
     }

     if (ref != NULL) {
         ref->dispose();
     }

     //manager.removePropertyChangeListener(this);
     disconnect(manager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //LocationManager::instance().removePropertyChangeListener(this);
     disconnect(LocationManager::instance()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeRoutes();
 }

}

