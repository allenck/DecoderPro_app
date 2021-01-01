#include "enginestablemodel.h"
#include "enginemanager.h"
#include "propertychangesupport.h"
#include "control.h"
#include "engine.h"
#include "enginestableframe.h"
#include "xtablecolumnmodel.h"
#include "jtable.h"
#include "setup.h"
#include "consist.h"
#include "engineeditframe.h"
#include "enginesetframe.h"
#include "pushbuttondelegate.h"


//EnginesTableModel::EnginesTableModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}
namespace Operations
{

/**
 * Table Model for edit of engines used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2012
 * @version $Revision: 29493 $
 */
///*public*/ class EnginesTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 6804454611283948123L;
 EngineManager* EnginesTableModel::manager = EngineManager::instance(); // There is only one manager

 /*public*/ EnginesTableModel::EnginesTableModel(QObject *parent) :
   AbstractTableModel(parent)
 {
  //super();
  _sort = SORTBYNUMBER;
  _roadNumber = "";
  _index = 0;
  sysList = NULL;
 eef = NULL;
  esf = NULL;
  log = new Logger("EngineTableModel");
  _enginesTableColumnWidths = QList<int>() << 60 << 60 << 65 << 50 << 65 << 35 << 75 << 190 << 190 << 65 << 50 << 65 << 70;
  showMoveCol = SHOWMOVES;


  //manager->addPropertyChangeListener(this);
  connect(manager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  updateList();
 }


 /*public*/ void EnginesTableModel::setSort(int sort) {
     _sort = sort;
     updateList();
     if (sort == SORTBYMOVES) {
         showMoveCol = SHOWMOVES;
         fireTableStructureChanged();
         initTable();
     } else if (sort == SORTBYBUILT) {
         showMoveCol = SHOWBUILT;
         fireTableStructureChanged();
         initTable();
     } else if (sort == SORTBYOWNER) {
         showMoveCol = SHOWOWNER;
         fireTableStructureChanged();
         initTable();
     } else if (sort == SORTBYVALUE) {
         showMoveCol = SHOWVALUE;
         fireTableStructureChanged();
         initTable();
     } else if (sort == SORTBYRFID) {
         showMoveCol = SHOWRFID;
         fireTableStructureChanged();
         initTable();
     } else if (sort == SORTBYLAST) {
         showMoveCol = SHOWLAST;
         fireTableStructureChanged();
         initTable();
     } else {
         fireTableDataChanged();
     }
 }

 /**
  * Search for engine by road number
  *
  * @param roadNumber
  * @return -1 if not found, table row number if found
  */
 /*public*/ int EnginesTableModel::findEngineByRoadNumber(QString roadNumber) {
     if (sysList != NULL) {
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

 /*private*/ int EnginesTableModel::getIndex(int start, QString roadNumber) {
     for (int index = start; index < sysList->size(); index++) {
         Engine* e = (Engine*) sysList->at(index);
         if (e != NULL) {
             QStringList number = e->getNumber().split("-");
             // check for wild card '*'
             if (roadNumber.startsWith("*")) {
                 QString rN = roadNumber.mid(1);
                 if (e->getNumber().endsWith(rN) || number[0].endsWith(rN)) {
                     _roadNumber = roadNumber;
                     _index = index + 1;
                     return index;
                 }
             } else if (roadNumber.endsWith("*")) {
                 QString rN = roadNumber.mid(0, roadNumber.length() - 1);
                 if (e->getNumber().startsWith(rN)) {
                     _roadNumber = roadNumber;
                     _index = index + 1;
                     return index;
                 }
             } else if (e->getNumber()==(roadNumber) || number[0]==(roadNumber)) {
                 _roadNumber = roadNumber;
                 _index = index + 1;
                 return index;
             }
         }
     }
     _roadNumber = "";
     return -1;
 }

 /*synchronized*/ void EnginesTableModel::updateList() {
     // first, remove listeners from the individual objects
     removePropertyChangeEngines();
     sysList = getSelectedEngineList();
     // and add listeners back in
     foreach (RollingStock* rs, *sysList) {
         //rs->addPropertyChangeListener(this);
      connect(rs->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*public*/ QList<RollingStock*>* EnginesTableModel::getSelectedEngineList() {
QList<RollingStock*>* list = new QList<RollingStock*>();
     if (_sort == SORTBYROAD) {
         list = manager->getByRoadNameList();
     }
     else if (_sort == SORTBYMODEL) {
         list = manager->getByModelList();
     }

     else if (_sort == SORTBYLOCATION) {
         list = manager->getByLocationList();
     } else if (_sort == SORTBYDESTINATION) {
         list = manager->getByDestinationList();
     } else if (_sort == SORTBYTRAIN) {
         list = manager->getByTrainList();
     } else if (_sort == SORTBYMOVES) {
         list = manager->getByMovesList();
     }
     else if (_sort == SORTBYCONSIST) {
         list = manager->getByConsistList();
     }
     else if (_sort == SORTBYOWNER) {
         list = manager->getByOwnerList();
     } else if (_sort == SORTBYBUILT) {
         list = manager->getByBuiltList();
     } else if (_sort == SORTBYVALUE) {
         list = manager->getByValueList();
     } else if (_sort == SORTBYRFID) {
         list = manager->getByRfidList();
     } else if (_sort == SORTBYLAST) {
         list = manager->getByLastDateList();
     }
     else {
         list = manager->getByNumberList();
     }

     return list;
 }


 void EnginesTableModel::initTable(JTable* table, EnginesTableFrame* frame) {
     _table = table;
     _frame = frame;
     initTable();
 }


 void EnginesTableModel::initTable()
 {
  // Install the button handlers
  XTableColumnModel* tcm = new XTableColumnModel(/*(AbstractTableModel*)_table->model()*/_table);
  _table->setColumnModel(tcm);
  _table->createDefaultColumnsFromModel();
     // TODO:
     //ButtonRenderer buttonRenderer = new ButtonRenderer();
     //tcm.getColumn(SET_COLUMN).setCellRenderer(buttonRenderer);
     //TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());
     //tcm.getColumn(SET_COLUMN).setCellEditor(buttonEditor);
     //tcm.getColumn(EDIT_COLUMN).setCellRenderer(buttonRenderer);
     //tcm.getColumn(EDIT_COLUMN).setCellEditor(buttonEditor);
 _table->setItemDelegateForColumn(SET_COLUMN, new MyDelegate());
 _table->setItemDelegateForColumn(EDIT_COLUMN, new MyDelegate());

     // set column preferred widths
#if 0
     if (!_frame->loadTableDetails(_table))
     {
         // load defaults, xml file data not found
         for (int i = 0; i < tcm.getColumnCount(); i++) {
             tcm.getColumn(i).setPreferredWidth(_enginesTableColumnWidths[i]);
         }
     }
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
     _table->setAutoResizeMode(JTable::AUTO_RESIZE_OFF);
#endif
 }

 /*public*/ int EnginesTableModel::rowCount(const QModelIndex &parent) const
 {
  return sysList->size();
 }

 /*public*/ int EnginesTableModel::columnCount(const QModelIndex &parent) const
 {
  return HIGHEST_COLUMN;
 }

 /*public*/ QVariant EnginesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case NUM_COLUMN:
             return  tr("Number");
         case ROAD_COLUMN:
             return  tr("Road");
         case MODEL_COLUMN:
             return  tr("Model");
         case HP_COLUMN:
             return  tr("HP");
         case TYPE_COLUMN:
             return  tr("Type");
         case LENGTH_COLUMN:
             return  tr("Len");
         case CONSIST_COLUMN:
             return  tr("Consist");
         case LOCATION_COLUMN:
             return  tr("Location");
         case DESTINATION_COLUMN:
             return  tr("Destination");
         case TRAIN_COLUMN:
             return  tr("Train");
         case MOVES_COLUMN: {
             if (showMoveCol == SHOWBUILT) {
                 return  tr("Built");
             } else if (showMoveCol == SHOWOWNER) {
                 return  tr("Owner");
             } else if (showMoveCol == SHOWVALUE) {
                 return  Setup::getValueLabel();
             } else if (showMoveCol == SHOWRFID) {
                 return  Setup::getRfidLabel();
             } else if (showMoveCol == SHOWLAST) {
                 return  tr("LastMoved");
             } else {
                 return  tr("Moves");
             }
         }
         case SET_COLUMN:
             return  tr("Set");
         case EDIT_COLUMN:
             return  tr("Edit");
         default:
             return "unknown"; // NOI18N
     }
  }
  return QVariant();
 }
#if 0
 /*public*/ Class<?> getColumnClass(int col) {
     switch (col) {
         case NUM_COLUMN:
             return String.class;
         case ROAD_COLUMN:
             return String.class;
         case LENGTH_COLUMN:
             return String.class;
         case MODEL_COLUMN:
             return String.class;
         case HP_COLUMN:
             return String.class;
         case TYPE_COLUMN:
             return String.class;
         case CONSIST_COLUMN:
             return String.class;
         case LOCATION_COLUMN:
             return String.class;
         case DESTINATION_COLUMN:
             return String.class;
         case TRAIN_COLUMN:
             return String.class;
         case MOVES_COLUMN:
             return String.class;
         case SET_COLUMN:
             return JButton.class;
         case EDIT_COLUMN:
             return JButton.class;
         default:
             return NULL;
     }
 }
#endif
 /*public*/ Qt::ItemFlags EnginesTableModel::flags(const QModelIndex &index) const
 {
     switch (index.column()) {
         case SET_COLUMN:
         case EDIT_COLUMN:
         case MOVES_COLUMN:
             return Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable;
         default:
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
     }
 }

 /*public*/ QVariant EnginesTableModel::data(const QModelIndex &index, int role) const
 {
   if(role == Qt::DisplayRole)
  {
                   int row = index.row();
                   int col = index.column();
     if (row >= sysList->size()) {
         return "ERROR row " + row; // NOI18N
     }
     Engine* eng = (Engine*) sysList->at(row);
     if (eng == NULL) {
         return "ERROR engine unknown " + QString::number(row); // NOI18N
     }
     switch (col) {
         case NUM_COLUMN:
             return eng->getNumber();
         case ROAD_COLUMN:
             return eng->getRoadName();
         case LENGTH_COLUMN:
             return eng->getLengthInteger();
         case MODEL_COLUMN:
             return eng->getModel();
         case HP_COLUMN:
             return eng->getHpInteger();
         case TYPE_COLUMN:
             return eng->getTypeName();
         case CONSIST_COLUMN: {
             if (eng->getConsist() != NULL && eng->getConsist()->isLead(eng)) {
                 return eng->getConsistName() + "*";
             }
             return eng->getConsistName();
         }
         case LOCATION_COLUMN: {
             QString s = eng->getStatus();
             if (eng->getLocationName()!=(Engine::NONE)) {
                 s = eng->getStatus() + eng->getLocationName() + " (" + eng->getTrackName() + ")";
             }
             return s;
         }
         case DESTINATION_COLUMN: {
             QString s = "";
             if (eng->getDestinationName()!=(Engine::NONE)) {
                 s = eng->getDestinationName() + " (" + eng->getDestinationTrackName() + ")";
             }
             return s;
         }
         case TRAIN_COLUMN: {
             // if train was manually set by user add an asterisk
             if (eng->getTrain() != NULL && eng->getRouteLocation() == NULL) {
                 return eng->getTrainName() + "*";
             }
             return eng->getTrainName();
         }
         case MOVES_COLUMN: {
             if (showMoveCol == SHOWBUILT) {
                 return eng->getBuilt();
             } else if (showMoveCol == SHOWOWNER) {
                 return eng->getOwner();
             } else if (showMoveCol == SHOWVALUE) {
                 return eng->getValue();
             } else if (showMoveCol == SHOWRFID) {
                 return eng->getRfid();
             } else if (showMoveCol == SHOWLAST) {
                 return eng->getLastDate();
             } else {
                 return eng->getMoves();
             }
         }
         case SET_COLUMN:
             return  tr("Set");
         case EDIT_COLUMN:
             return  tr("Edit");
         default:
             return "unknown " + col; // NOI18N
     }
   }
   return QVariant();
 }


 /*public*/ bool EnginesTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  int row = index.row();
  int col = index.column();
  if(role == Qt::EditRole)
  {
     Engine* engine = (Engine*) sysList->at(row);
     switch (col) {
         case SET_COLUMN:
             log->debug("Set engine location");
             if (esf != NULL) {
                 esf->dispose();
             }
             // use invokeLater so new window appears on top
//             SwingUtilities.invokeLater(new Runnable() {
//                 /*public*/ void run() {
                     esf = new EngineSetFrame();
                     esf->initComponents();
                     esf->loadEngine(engine);
//                 }
//             });
             break;
         case EDIT_COLUMN:
             log->debug("Edit engine");
             if (eef != NULL) {
                 eef->dispose();
             }
             // use invokeLater so new window appears on top
//             SwingUtilities.invokeLater(new Runnable() {
//                 /*public*/ void run() {
                     eef = new EngineEditFrame();
                     eef->initComponents();
                     eef->loadEngine(engine);
//                 }
//             });
             break;
         case MOVES_COLUMN:
             if (showMoveCol == SHOWBUILT) {
                 engine->setBuilt(value.toString());
             } else if (showMoveCol == SHOWOWNER) {
                 engine->setOwner(value.toString());
             } else if (showMoveCol == SHOWVALUE) {
                 engine->setValue(value.toString());
             } else if (showMoveCol == SHOWRFID) {
                 engine->setRfid(value.toString());
             } else {
                 //try {
                   bool ok;
                     engine->setMoves(value.toString().toInt(&ok));
                 if(!ok) {
                     log->error("move count must be a number");
                 }
             }
             break;
         default:
             break;
     }
    }
  return false;
 }

 /*public*/ void EnginesTableModel::dispose() {
     if (log->isDebugEnabled()) {
         log->debug("dispose EngineTableModel");
     }
     //manager->removePropertyChangeListener(this);
     disconnect(manager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removePropertyChangeEngines();

     if (esf != NULL) {
         esf->dispose();
     }

     if (eef != NULL) {
         eef->dispose();
     }
 }

 /*private*/ void EnginesTableModel::removePropertyChangeEngines()
 {
  if (sysList != NULL)
  {
   foreach (RollingStock* rs, *sysList)
   {
       //rs.removePropertyChangeListener(this);
    disconnect(rs->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
  }
 }

 /*public*/ void EnginesTableModel::propertyChange(PropertyChangeEvent* e)
 {
     if (Control::SHOW_PROPERTY) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(EngineManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(EngineManager::CONSISTLISTLENGTH_CHANGED_PROPERTY)) {
         updateList();
         fireTableDataChanged();
     } // Engine lengths are based on model, so multiple changes
     else if (e->getPropertyName()==(Engine::LENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Engine::TYPE_CHANGED_PROPERTY)) {
         fireTableDataChanged();
     } // must be a engine change
                   else if (e->getSource()->metaObject()->className()==("Engine")) {
         Engine* engine = (Engine*) e->getSource();
         int row = sysList->indexOf(engine);
         if (Control::SHOW_PROPERTY) {
             log->debug(tr("Update engine table row: %1").arg(row));
         }
         if (row >= 0) {
             fireTableRowsUpdated(row, row);
         }
     }
 }
}
