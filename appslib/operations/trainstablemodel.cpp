#include "trainstablemodel.h"
#include "train.h"
#include "trainmanager.h"
#include "setup.h"
#include "control.h"
#include "xtablecolumnmodel.h"
#include "jtable.h"
#include "track.h"
#include "trainstableframe.h"
#include "tablecolumn.h"
#include "logger.h"
#include "pushbuttondelegate.h"
#include "traineditframe.h"
#include "trainconductorframe.h"
#include "routeeditframe.h"
#include <QMessageBox>
#include <QPen>

namespace Operations
{
/**
 * Table Model for edit of trains used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2012
 * @version $Revision: 29638 $
 */
///*public*/ class TrainsTableModel extends javax.swing.table.AbstractTableModel implements PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static /*final*/ long serialVersionUID = 4245878111843075492L;

/*private*/ /*static*/ QHash<QString, TrainConductorFrame*> TrainsTableModel::_trainConductorHashTable =  QHash<QString, TrainConductorFrame*>();


 /*public*/ TrainsTableModel::TrainsTableModel(QObject* parent)
 : AbstractTableModel(parent)
 {
     //super();
  SORTBYTIME = 2;
  SORTBYID = 7;
 trainManager = TrainManager::instance(); // There is only one manager
 _sort = SORTBYTIME;
 _showAll = true;
 tef = NULL;
 log = new Logger("TrainsTableModel");
 ref = NULL;
 buildThread = NULL;
 darkColors = QList<QColor>() << Qt::black << Qt::blue<< Qt::gray <<  Qt::red << Qt::magenta;

     //trainManager.addPropertyChangeListener(this);
 connect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //Setup.addPropertyChangeListener(this);

     updateList();
 }



 /*public*/ void TrainsTableModel::setSort(int sort) {
     /*synchronized (this)*/ {
         _sort = sort;
     }
     updateList();
     fireTableStructureChanged();
     initTable();
 }


 /*public*/ void TrainsTableModel::setShowAll(bool showAll) {
     _showAll = showAll;
     updateList();
     fireTableStructureChanged();
     initTable();
 }

 /*public*/ bool TrainsTableModel::isShowAll() {
     return _showAll;
 }

 /*private*/ /*synchronized*/ void TrainsTableModel::updateList() {
     // first, remove listeners from the individual objects
     removePropertyChangeTrains();

     if (_sort == SORTBYID) {
         sysList = trainManager->getTrainsByIdList();
     } else {
         sysList = trainManager->getTrainsByTimeList();
     }

     if (!_showAll) {
         // filter out trains not checked
         for (int i = sysList.size() - 1; i >= 0; i--) {
             if (!sysList.at(i)->isBuildEnabled()) {
                 sysList.removeAt(i);
             }
         }
     }

     // and add listeners back in
     addPropertyChangeTrains();
 }


 void TrainsTableModel::initTable(JTable* table, TrainsTableFrame* frame) {
     _table = table;
     _frame = frame;
     // allow row color to be controlled
     //table.setDefaultRenderer(Object.class, new MyTableCellRenderer());
     initTable();
 }

 void TrainsTableModel::initTable()
 {
  // Install the button handlers
  TableColumnModel* tcm = _table->getColumnModel();
#if 0
     ButtonRenderer buttonRenderer = new ButtonRenderer();
     TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());
     tcm.getColumn(EDITCOLUMN).setCellRenderer(buttonRenderer);
     tcm.getColumn(EDITCOLUMN).setCellEditor(buttonEditor);
     tcm.getColumn(ACTIONCOLUMN).setCellRenderer(buttonRenderer);
     tcm.getColumn(ACTIONCOLUMN).setCellEditor(buttonEditor);
     tcm.getColumn(BUILDCOLUMN).setCellRenderer(buttonRenderer);
     tcm.getColumn(BUILDCOLUMN).setCellEditor(buttonEditor);
     _table.setDefaultRenderer(bool.class, new EnablingCheckboxRenderer());
#endif
  _table->setItemDelegateForColumn(EDITCOLUMN, new MyDelegate());
  _table->setItemDelegateForColumn(ACTIONCOLUMN, new MyDelegate());
  _table->setItemDelegateForColumn(BUILDCOLUMN, new MyDelegate());

  // set column preferred widths
  if ( !_frame->loadTableDetails(_table))
  {
   // load defaults, xml file data not found
   QList<int> tableColumnWidths = trainManager->getTrainsFrameTableColumnWidths();
   for (int i = 0; i < tcm->getColumnCount(); i++)
   {
    tcm->getColumn(i)->setPreferredWidth(tableColumnWidths[i]);
   }
  }
#if 0
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
     _table->setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
#endif
 }

 /*public*/ int TrainsTableModel::rowCount(const QModelIndex &parent) const {
     return sysList.size();
 }

 /*public*/ int TrainsTableModel::columnCount(const QModelIndex &parent) const {
     return HIGHESTCOLUMN;
 }

 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::IDCOLUMNNAME = tr("Id");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::TIMECOLUMNNAME = tr("Time");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::BUILDBOXCOLUMNNAME = tr("Build");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::BUILDCOLUMNNAME = tr("Function");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::NAMECOLUMNNAME = tr("Name");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::DESCRIPTIONCOLUMNNAME = tr("Description");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::ROUTECOLUMNNAME = tr("Route");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::DEPARTSCOLUMNNAME = tr("Departs");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::CURRENTCOLUMNNAME = tr("Current");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::TERMINATESCOLUMNNAME = tr("Terminates");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::STATUSCOLUMNNAME = tr("Status");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::ACTIONCOLUMNNAME = tr("Action");
 /*public*/ /*static*/ /*final*/ QString TrainsTableModel::EDITCOLUMNNAME = tr("Edit");

 /*public*/ QVariant TrainsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
   switch (section)
   {
    case IDCOLUMN:
     if (_sort == SORTBYID)
     {
      return IDCOLUMNNAME;
     }
     return TIMECOLUMNNAME;
    case BUILDBOXCOLUMN:
        return BUILDBOXCOLUMNNAME;
    case BUILDCOLUMN:
        return BUILDCOLUMNNAME;
    case NAMECOLUMN:
        return NAMECOLUMNNAME;
    case DESCRIPTIONCOLUMN:
        return DESCRIPTIONCOLUMNNAME;
    case ROUTECOLUMN:
        return ROUTECOLUMNNAME;
    case DEPARTSCOLUMN:
        return DEPARTSCOLUMNNAME;
    case CURRENTCOLUMN:
        return CURRENTCOLUMNNAME;
    case TERMINATESCOLUMN:
        return TERMINATESCOLUMNNAME;
    case STATUSCOLUMN:
        return STATUSCOLUMNNAME;
    case ACTIONCOLUMN:
        return ACTIONCOLUMNNAME;
    case EDITCOLUMN:
        return EDITCOLUMNNAME;
    default:
        return "unknown"; // NOI18N
   }
  }
  return QVariant();
 }
#if 0
 /*public*/ Class<?> getColumnClass(int col) {
     switch (col) {
         case IDCOLUMN:
             return String.class;
         case BUILDBOXCOLUMN:
             return bool.class;
         case BUILDCOLUMN:
             return JButton.class;
         case NAMECOLUMN:
             return String.class;
         case DESCRIPTIONCOLUMN:
             return String.class;
         case ROUTECOLUMN:
             return String.class;
         case DEPARTSCOLUMN:
             return String.class;
         case CURRENTCOLUMN:
             return String.class;
         case TERMINATESCOLUMN:
             return String.class;
         case STATUSCOLUMN:
             return String.class;
         case ACTIONCOLUMN:
             return JButton.class;
         case EDITCOLUMN:
             return JButton.class;
         default:
             return NULL;
     }
 }
#endif

 /*public*/ Qt::ItemFlags TrainsTableModel::flags(const QModelIndex &index) const
 {
     switch (index.column()) {
         case BUILDBOXCOLUMN:
          return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
         case BUILDCOLUMN:
         case ROUTECOLUMN:
         case ACTIONCOLUMN:
         case EDITCOLUMN:
             return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
         default:
             return Qt::ItemIsEnabled | Qt::ItemIsSelectable;;
     }
 }

 /*public*/ QVariant TrainsTableModel::data(const QModelIndex &index, int role) const
 {
  int row =index.row();
  int col = index.column();
  Train* train = sysList.at(row);
  if(role == Qt::BackgroundColorRole)
  {
   if(getRowColor(row) == QColor()) return QVariant();
   QBrush background(getRowColor(row));
   return background;
  }
  if(role == Qt::TextColorRole)
  {
   if(getRowColor(row) == QColor()) return QVariant();
   return getForegroundColor(getRowColor(row));
  }
  if(role == Qt::CheckStateRole)
  {
   if(col==BUILDBOXCOLUMN)
   {
    return train->isBuildEnabled()?Qt::Checked: Qt::Unchecked;
   }
  }
  if(role == Qt::DisplayRole)
  {
     if (row >= sysList.size()) {
         return "ERROR row " + QString::number(row); // NOI18N
     }
     if (train == NULL) {
         return "ERROR train unknown " + row; // NOI18N
     }
     switch (col) {
         case IDCOLUMN: {
             if (_sort == SORTBYID) {
                 return train->getId();
             }
             return train->getDepartureTime();
         }
         case NAMECOLUMN:
             return train->getIconName();
         case DESCRIPTIONCOLUMN:
             return train->getDescription();
//         case BUILDBOXCOLUMN:
//             //return bool.valueOf(train->isBuildEnabled());
//          return tr("Built");
         case ROUTECOLUMN:
             return train->getTrainRouteName();
         case DEPARTSCOLUMN: {
             if (train->getDepartureTrack() == NULL) {
                 return train->getTrainDepartsName();
             } else {
                 return train->getTrainDepartsName() + " (" + train->getDepartureTrack()->getName() + ")";
             }
         }
         case CURRENTCOLUMN:
             return train->getCurrentLocationName();
         case TERMINATESCOLUMN: {
             if (train->getTerminationTrack() == NULL) {
                 return train->getTrainTerminatesName();
             } else {
                 return train->getTrainTerminatesName() + " (" + train->getTerminationTrack()->getName() + ")";
             }
         }
         case STATUSCOLUMN:
             return train->getStatus();
         case BUILDCOLUMN: {
             if (train->isBuilt()) {
                 if (Setup::isGenerateCsvManifestEnabled() && trainManager->isOpenFileEnabled()) {
                     return tr("OpenFile");
                 } else if (Setup::isGenerateCsvManifestEnabled() && trainManager->isRunFileEnabled()) {
                     return tr("RunFile");
                 } else if (trainManager->isPrintPreviewEnabled()) {
                     return tr("Preview");
                 } else if (train->isPrinted()) {
                     return tr("Printed");
                 } else {
                     return tr("Print");
                 }
             }
             return tr("Build");
         }
         case ACTIONCOLUMN: {
             if (train->getBuildFailed()) {
                 return tr("Report");
             }
             return trainManager->getTrainsFrameTrainAction();
         }
         case EDITCOLUMN:
             return tr("Edit");
         default:
             //return "unknown " + QString::number(col); // NOI18N
                   break;
     }
  }
  return QVariant();
 }

 /*public*/ bool TrainsTableModel::setData(const QModelIndex &index, const QVariant &value, int role) \
 {
  int col = index.column();
  int row = index.row();
  if(role == Qt::EditRole)
  {
   switch (col)
   {
    case EDITCOLUMN:
        editTrain(row);
        break;
    case BUILDCOLUMN:
        buildTrain(row);
        break;
    case ROUTECOLUMN:
        editRoute(row);
        break;
    case ACTIONCOLUMN:
        actionTrain(row);
        break;
//         case BUILDBOXCOLUMN:
//         {
//          Train* train = sysList.at(row);
//          train->setBuildEnabled(value.toBool());
//          break;
//         }
    default:
        break;
   }
   return true;
  }
  if(role == Qt::CheckStateRole)
  {
   if(col == BUILDBOXCOLUMN)
   {
    Train* train = sysList.at(row);
    train->setBuildEnabled(value.toBool());
    return true;
   }
  }
  return false;
 }

 /*public*/ QColor TrainsTableModel::getRowColor(int row) const {
     Train* train = sysList.at(row);
//		log->debug(tr("Row: %1 train: %2 color: %3"),arg(row).arg(train->getName()).arg(train->getTableRowColorName()));
     return train->getTableRowColor();
 }


 /*private*/ /*synchronized*/ void TrainsTableModel::editTrain(int row) {
     if (tef != NULL) {
         tef->dispose();
     }
     // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
             Train* train = sysList.at(row);
             log->debug(tr("Edit train (%1)").arg(train->getName()));
             tef = new TrainEditFrame(train);
//         }
//     });
 }


 /*private*/ /*synchronized*/ void TrainsTableModel::editRoute(int row) {
     if (ref != NULL) {
         ref->dispose();
     }
     // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
             ref = new RouteEditFrame();
             Train* train = sysList.at(row);
             log->debug("Edit route for train (" + train->getName() + ")");
             ref->initComponents(train->getRoute(), train);
//         }
//     });
 }
#if 1

 /*private*/ /*synchronized*/ void TrainsTableModel::buildTrain(int row)
 {
  /*final*/ Train* train = sysList.at(row);
  if(buildThread== NULL)
   buildThread = new QThread();
   if (!train->isBuilt())
   {
    // only one train build at a time
    if (buildThread != NULL && buildThread->isRunning())
    {
     return;
    }
         // use a thread to allow table updates during build
     //build = new Thread(new Runnable() {
//             /*public*/ void run() {
//                 train->build();
//             }
//         });
     Build* build = new Build(train, this);
     build->moveToThread(buildThread);
     build->setObjectName("Build Train"); // NOI18N
     connect(buildThread, SIGNAL(started()), build, SLOT(process()));
     connect(build, SIGNAL(finished()), buildThread, SLOT(terminate()));
     //build.start();
     buildThread->start();
        // print build report, print manifest, run or open file
    }
    else
    {
     if (trainManager->isBuildReportEnabled()) {
         train->printBuildReport();
     }
 #if 0
     if (Setup::isGenerateCsvManifestEnabled() && trainManager.isOpenFileEnabled()) {
         train->openFile();
     } else if (Setup::isGenerateCsvManifestEnabled() && trainManager.isRunFileEnabled()) {
         train->runFile();
     }
     else
 #endif
     {
         train->printManifestIfBuilt();
     }
   }
 }
#endif

 Build::Build(Train *train, TrainsTableModel *parent)
 {
   this->train = train;
   this->parent = parent;
 }
 void Build::process()
 {
  train->build();
  emit finished();   \
 }

 // one of four buttons: Report, Move, Conductor or Terminate
 /*private*/ /*synchronized*/ void TrainsTableModel::actionTrain(int row)
 {
     // no actions while a train is being built
#if 1
     if (buildThread != NULL && buildThread->isRunning()) {
         return;
     }
     Train* train = sysList.at(row);
     // move button becomes report if failure
     if (train->getBuildFailed()) {
         train->printBuildReport();
     }
     else if (trainManager->getTrainsFrameTrainAction()==(TrainsTableFrame::RESET))
     {
      if (log->isDebugEnabled())
      {
          log->debug("Reset train (" + train->getName() + ")");
      }
      // check to see if departure track was reused
      if (checkDepartureTrack(train))
      {
       log->debug("Train is departing staging that already has inbound cars");
//             JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("StagingTrackUsed"),
//                     new Object[]{train->getDepartureTrack().getName()}), tr("CanNotResetTrain"),
//                     JOptionPane.INFORMATION_MESSAGE);
       QMessageBox::information(NULL, tr("Can not reset train!"), tr("Another train has already acquired the same departure track (%1) as this train!").arg(train->getDepartureTrack()->getName()) );
      }
      else if (!train->reset())
      {
//          JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("TrainIsInRoute"),
//                  new Object[]{train->getTrainTerminatesName()}), tr("CanNotResetTrain"),
//                  JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(NULL, tr("Can not reset train!"), tr("Train is in route to %1").arg(train->getTrainTerminatesName()));
      }
     }
     else if (!train->isBuilt())
     {
//         JOptionPane.showMessageDialog(NULL, MessageFormat.format(tr("TrainNeedsBuild"),
//                 new Object[]{train->getName()}), tr("CanNotPerformAction"),
//                 JOptionPane.INFORMATION_MESSAGE);
      QMessageBox::information(NULL, tr("Can not perform train action"), tr("Train (%1) needs to be built!").arg(train->getName()));
     }
     else if (train->isBuilt() && trainManager->getTrainsFrameTrainAction()==(TrainsTableFrame::MOVE))
     {
         if (log->isDebugEnabled()) {
             log->debug("Move train (" + train->getName() + ")");
         }
         train->move();
     }
     else if (train->isBuilt() && trainManager->getTrainsFrameTrainAction()==(TrainsTableFrame::TERMINATE)) {
         if (log->isDebugEnabled()) {
             log->debug("Terminate train (" + train->getName() + ")");
         }
//         int status = JOptionPane.showConfirmDialog(NULL, MessageFormat.format(tr("TerminateTrain"),
//                 new Object[]{train->getName(), train->getDescription()}), MessageFormat.format(Bundle
//                         .getMessage("DoYouWantToTermiate"), new Object[]{train->getName()}), JOptionPane.YES_NO_OPTION);
         int status = QMessageBox::question(NULL, tr("Do you want to terminate train ({0})?").arg(train->getName()), tr("Terminate Train ({0}) {1}?").arg(train->getName()).arg(train->getDescription()), QMessageBox::Yes | QMessageBox::No);
         if (status == QMessageBox::Yes) {
             train->terminate();
         }
     } else if (train->isBuilt() && trainManager->getTrainsFrameTrainAction()==(TrainsTableFrame::CONDUCTOR)) {
         if (log->isDebugEnabled()) {
             log->debug("Enable conductor for train (" + train->getName() + ")");
         }
         launchConductor(train);
     }
#endif
 }

 /*
  * Check to see if the departure track in staging has been taken by another train. return true if track has been
  * allocated to another train.
  */
 /*private*/ bool TrainsTableModel::checkDepartureTrack(Train* train) {
     return (Setup::isStagingTrackImmediatelyAvail() && !train->isTrainInRoute() && train->getDepartureTrack() != NULL
             && train->getDepartureTrack()->getTrackType()==(Track::STAGING)
             && train->getDepartureTrack() != train->getTerminationTrack() && train->getDepartureTrack()->getDropRS() > 0);
 }


 /*private*/ void TrainsTableModel::launchConductor(Train* train)
 {
     // use invokeLater so new window appears on top
//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
  TrainConductorFrame* f = _trainConductorHashTable.value(train->getId());
  // create a copy train frame
  if (f == NULL || !f->isVisible()) {
      f = new TrainConductorFrame(train);
      _trainConductorHashTable.insert(train->getId(), f);
  } else {
      //f.setExtendedState(Frame.NORMAL);
  }
  f->setVisible(true); // this also brings the frame into focus
//         }
//     });
 }

 /*public*/ void TrainsTableModel::propertyChange(PropertyChangeEvent* e)
 {
     if (Control::showProperty) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Train::STATUS_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::TRAIN_LOCATION_CHANGED_PROPERTY)) {
         _frame->setModifiedFlag(true);
     }
     if (e->getPropertyName()==(TrainManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(TrainManager::PRINTPREVIEW_CHANGED_PROPERTY)
             || e->getPropertyName()==(TrainManager::OPEN_FILE_CHANGED_PROPERTY)
             || e->getPropertyName()==(TrainManager::RUN_FILE_CHANGED_PROPERTY)
             || e->getPropertyName()==(Setup::MANIFEST_CSV_PROPERTY_CHANGE)
             || e->getPropertyName()==(TrainManager::TRAIN_ACTION_CHANGED_PROPERTY)
             || e->getPropertyName()==(Train::DEPARTURETIME_CHANGED_PROPERTY)
             || (e->getPropertyName()==(Train::BUILD_CHANGED_PROPERTY) && !isShowAll())) {
         updateList();
         fireTableDataChanged();
     } else if (e->getSource()->metaObject()->className()==("Train")) {
         /*synchronized (this)*/ {
             Train* train = ((Train*) e->getSource());
             int row = sysList.indexOf(train);
             if (Control::showProperty) {
                 log->debug(tr("Update train table row: %1 name: %2").arg(row).arg(train->getName()));
             }
             if (row >= 0) {
                 fireTableRowsUpdated(row, row);
             }
         }
     }
 }

 /*private*/ /*synchronized*/ void TrainsTableModel::removePropertyChangeTrains() {
     foreach (Train* train, trainManager->getTrainsByIdList()) {
         //train.removePropertyChangeListener(this);
      disconnect(train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*private*/ /*synchronized*/ void TrainsTableModel::addPropertyChangeTrains() {
     foreach (Train* train, trainManager->getTrainsByIdList()) {
         //train.addPropertyChangeListener(this);
      connect(train->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     }
 }

 /*public*/ void TrainsTableModel::dispose() {
     if (log->isDebugEnabled()) {
         log->debug("dispose");
     }
     if (tef != NULL) {
         tef->dispose();
     }
     //trainManager.removePropertyChangeListener(this);
     connect(trainManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //Setup::removePropertyChangeListener(this);
     removePropertyChangeTrains();
 }
#if 0
 class MyTableCellRenderer extends DefaultTableCellRenderer {

     /**
      *
      */
     /*private*/ static /*final*/ long serialVersionUID = 6030024446880261924L;

     @Override
     /*public*/ Component getTableCellRendererComponent(JTable table, Object value, bool isSelected,
             bool hasFocus, int row, int column) {
         Component c = super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
         if (!isSelected) {
             TableSorter sorter = (TableSorter) table.getModel();
             int modelRow = sorter.modelIndex(row);
//				log->debug("View row: {} Column: {} Model row: {}", row, column, modelRow);
             Color background = getRowColor(modelRow);
             c.setBackground(background);
             c.setForeground(getForegroundColor(background));
         }
         return c;
     }

#endif
 /**
  * Dark colors need white lettering
  *
  * @param row
  * @return
  */
 /*private*/ QColor TrainsTableModel::getForegroundColor(QColor background) const
 {
     if (background == QColor()) {
         return QColor();
     }
     foreach (QColor color, darkColors) {
         if (background == color) {
             return Qt::white;
         }
     }
     return Qt::black;	// all others get black lettering
 }

}
