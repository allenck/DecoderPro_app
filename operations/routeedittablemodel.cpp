#include "routeedittablemodel.h"
#include "control.h"
#include "propertychangeevent.h"
#include "route.h"
#include "routelocation.h"
#include "xtablecolumnmodel.h"
#include <QComboBox>
#include "routeeditframe.h"
#include "setup.h"
#include "jtable.h"
#include "joptionpane.h"
#include "jdialog.h"
#include <QBoxLayout>
#include "flowlayout.h"
#include <QPushButton>
#include "htmltextedit.h"
#include "pushbuttondelegate.h"
#include <QGroupBox>
#include "jcolorchooser.h"
#include "jpanel.h"
#include "splitbuttoncolorchooserpanel.h"

namespace Operations
{
/**
 * Table Model for edit of route locations used by operations
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2013
 * @version $Revision: 29493 $
 */
///*public*/ class RouteEditTableModel extends javax.swing.table->AbstractTableModel implements PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = -4770884408356323253L;


 /*public*/ RouteEditTableModel::RouteEditTableModel(QObject* parent) : AbstractTableModel(parent) {
     //super();
 log = new Logger("RouteEditTableModel");
 _showWait = true;
 routeList = new QList<RouteLocation*>();
 _trainDirection = Setup::getDirectionInt(Setup::getTrainDirectionList().at(0));
 _maxTrainLength = Setup::getMaxTrainLength();
 _maxTrainMoves = Setup::getCarMoves();

}

 /*public*/ void RouteEditTableModel::setWait(bool showWait)
 {
  _showWait = showWait;
   routeList = new QList<RouteLocation*>();

  fireTableStructureChanged();
  initTable(_table);
 }

 /*synchronized*/ void RouteEditTableModel::updateList()
 {
  if (_route == NULL)
  {
   return;
  }
  // first, remove listeners from the individual objects
  removePropertyChangeRouteLocations();
  routeList = _route->getLocationsBySequenceList();
  // and add them back in
  foreach (RouteLocation* rl, *routeList) {
      //rl->addPropertyChangeListener(this);
   connect(rl->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }


 void RouteEditTableModel::initTable(RouteEditFrame* frame, JTable* table, Route* route) {
     _frame = frame;
     _table = table;
     _route = route;
     if (_route != NULL) {
         //_route.addPropertyChangeListener(this);
      connect(_route->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     initTable(table);
 }

 void RouteEditTableModel::initTable(JTable* table) {
     // Install the button handlers
     XTableColumnModel* tcm = (XTableColumnModel*)table->getColumnModel();
     table->setColumnModel(tcm);
     table->createDefaultColumnsFromModel();
#if 0
     ButtonRenderer buttonRenderer = new ButtonRenderer();
     TableCellEditor buttonEditor = new ButtonEditor(new javax.swing.JButton());
     tcm->getColumn(COMMENT_COLUMN)->setCellRenderer(buttonRenderer);
     tcm->getColumn(COMMENT_COLUMN)->setCellEditor(buttonEditor);
     tcm->getColumn(UP_COLUMN)->setCellRenderer(buttonRenderer);
     tcm->getColumn(UP_COLUMN)->setCellEditor(buttonEditor);
     tcm->getColumn(DOWN_COLUMN)->setCellRenderer(buttonRenderer);
     tcm->getColumn(DOWN_COLUMN)->setCellEditor(buttonEditor);
     tcm->getColumn(DELETE_COLUMN)->setCellRenderer(buttonRenderer);
     tcm->getColumn(DELETE_COLUMN)->setCellEditor(buttonEditor);
     table->setDefaultRenderer("JComboBox", new jmri.jmrit.symbolicprog.ValueRenderer());
     table->setDefaultEditor("JComboBox", new jmri.jmrit.symbolicprog.ValueEditor());
#endif
     table->setItemDelegateForColumn(COMMENT_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(UP_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(DOWN_COLUMN, new MyDelegate());
     table->setItemDelegateForColumn(DELETE_COLUMN, new MyDelegate());

     QStringList yesNo = QStringList() << "yes" << "no";
     table->setItemDelegateForColumn(PICKUP_COLUMN, new JComboBoxEditor(yesNo, this));
     table->setItemDelegateForColumn(DROP_COLUMN, new JComboBoxEditor(yesNo, this));
     if(!_showWait)
     {
      QStringList times;
      QString hour, minute;
      times.append("");
      for (int i = 0; i < 24; i++)
      {
       if (i < 10) {
           hour = "0" + QString::number(i);
       } else {
           hour = QString::number(i);
       }
       for (int j = 0; j < 60; j = j + 5)
       {
           if (j < 10) {
               minute = "0" + QString::number(j);
           } else {
               minute = QString::number(j);
           }

           times.append(hour + ":" + minute);
       }
      }
      table->setItemDelegateForColumn(WAIT_COLUMN, new JComboBoxEditor(times, this));
     }
     QStringList randomControlList = QStringList();
     randomControlList.append(RouteLocation::DISABLED);
     // 10 to 100 by 10
     for (int i = 10; i < 101; i = i + 10) {
         randomControlList.append(QString::number(i));
     }
     table->setItemDelegateForColumn(RANDOM_CONTROL_COLUMN, new JComboBoxEditor(randomControlList, this));


     setPreferredWidths(table);

     // set row height
//     table->setRowHeight( QComboBox().sizeHint().height());
     updateList();
     // have to shut off autoResizeMode to get horizontal scroll to work (JavaSwing p 541)
//     table->setAutoResizeMode(Jtable->AUTO_RESIZE_OFF);
 }

 /*private*/ void RouteEditTableModel::setPreferredWidths(JTable* table) {
     // set column preferred widths
     if (_frame->loadTableDetails(table)) {
         return; // done
     }
     table->getColumnModel()->getColumn(ID_COLUMN)->setPreferredWidth(40);
     table->getColumnModel()->getColumn(NAME_COLUMN)->setPreferredWidth(150);
     table->getColumnModel()->getColumn(TRAIN_DIRECTION_COLUMN)->setPreferredWidth(95);
     table->getColumnModel()->getColumn(MAXMOVES_COLUMN)->setPreferredWidth(50);
     table->getColumnModel()->getColumn(RANDOM_CONTROL_COLUMN)->setPreferredWidth(65);
     table->getColumnModel()->getColumn(PICKUP_COLUMN)->setPreferredWidth(65);
     table->getColumnModel()->getColumn(DROP_COLUMN)->setPreferredWidth(65);
     table->getColumnModel()->getColumn(WAIT_COLUMN)->setPreferredWidth(60);
     table->getColumnModel()->getColumn(MAXLENGTH_COLUMN)->setPreferredWidth(75);
     table->getColumnModel()->getColumn(GRADE)->setPreferredWidth(50);
     table->getColumnModel()->getColumn(TRAINICONX)->setPreferredWidth(35);
     table->getColumnModel()->getColumn(TRAINICONY)->setPreferredWidth(35);
     table->getColumnModel()->getColumn(COMMENT_COLUMN)->setPreferredWidth(70);
     table->getColumnModel()->getColumn(UP_COLUMN)->setPreferredWidth(60);
     table->getColumnModel()->getColumn(DOWN_COLUMN)->setPreferredWidth(70);
     table->getColumnModel()->getColumn(DELETE_COLUMN)->setPreferredWidth(70);
 }

 /*public*/ int RouteEditTableModel::rowCount(const QModelIndex &parent) const {
     return routeList->size();
 }

 /*public*/ int RouteEditTableModel::columnCount(const QModelIndex &parent) const {
     return HIGHEST_COLUMN;
 }

 /*public*/ QVariant RouteEditTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
     switch (section) {
         case ID_COLUMN:
             return tr("Id");
         case NAME_COLUMN:
             return tr("Location");
         case TRAIN_DIRECTION_COLUMN:
             return tr("Train Direction");
         case MAXMOVES_COLUMN:
             return tr("Moves");
         case RANDOM_CONTROL_COLUMN:
             return tr("Random");
         case PICKUP_COLUMN:
             return tr("Pick ups?");
         case DROP_COLUMN:
             return tr("Set outs?");
         case WAIT_COLUMN: {
             if (_showWait) {
                 return tr("Wait");
             } else {
                 return tr("Time");
             }
         }
         case MAXLENGTH_COLUMN:
             return tr("Max Length");
         case GRADE:
             return tr("Grade");
         case TRAINICONX:
             return tr("X");
         case TRAINICONY:
             return tr("Y");
         case COMMENT_COLUMN:
             return tr("Comment");
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

 /*public*/ QString RouteEditTableModel::getColumnClass(int col) {
     switch (col) {
         case ID_COLUMN:
             return "String";
         case NAME_COLUMN:
             return "String";
         case TRAIN_DIRECTION_COLUMN:
             return "JComboBox";
         case MAXMOVES_COLUMN:
             return "String";
         case RANDOM_CONTROL_COLUMN:
             return "JComboBox";
         case PICKUP_COLUMN:
             return "JComboBox";
         case DROP_COLUMN:
             return "JComboBox";
         case WAIT_COLUMN: {
             if (_showWait) {
                 return "String";
             } else {
                 return "JComboBox";
             }
         }
         case MAXLENGTH_COLUMN:
             return "String";
         case GRADE:
             return "String";
         case TRAINICONX:
             return "String";
         case TRAINICONY:
             return "String";
         case COMMENT_COLUMN:
             return "JButton";
         case UP_COLUMN:
             return "JButton";
         case DOWN_COLUMN:
             return "JButton";
         case DELETE_COLUMN:
             return "JButton";
         default:
             return QString();
     }
 }

 /*public*/ Qt::ItemFlags RouteEditTableModel::flags(const QModelIndex &index) const{
     switch (index.column()) {
         case DELETE_COLUMN:
         case TRAIN_DIRECTION_COLUMN:
         case MAXMOVES_COLUMN:
         case RANDOM_CONTROL_COLUMN:
         case PICKUP_COLUMN:
         case DROP_COLUMN:
         case WAIT_COLUMN:
         case MAXLENGTH_COLUMN:
         case GRADE:
         case TRAINICONX:
         case TRAINICONY:
         case COMMENT_COLUMN:
         case UP_COLUMN:
         case DOWN_COLUMN:
             return Qt::ItemIsEditable | Qt::ItemIsEnabled;
         default:
             return Qt::ItemIsEnabled;
     }
 }

 /*public*/ QVariant RouteEditTableModel::data(const QModelIndex &index, int role) const
 {
  if(role == Qt::DisplayRole)
  {
   int row = index.row();
   int col = index.column();
   if (row >= routeList->size())
   {
    return "ERROR unknown " + QString::number(row); // NOI18N
   }
   RouteLocation* rl = routeList->at(row);
   if (rl == NULL)
   {
    return "ERROR unknown route location " + row; // NOI18N
   }
   switch (col)
   {
    case ID_COLUMN:
        return rl->getId();
    case NAME_COLUMN:
        return rl->getName();
    case TRAIN_DIRECTION_COLUMN: {
//             QComboBox* cb = Setup::getTrainDirectionComboBox();
//             cb->setCurrentIndex(cb->findText(rl->getTrainDirectionString()));
//             return cb;
     return rl->getTrainDirectionString();
    }
    case MAXMOVES_COLUMN:
        return QString::number(rl->getMaxCarMoves());
    case RANDOM_CONTROL_COLUMN: {
//             QComboBox* cb = getRandomControlComboBox();
//             cb->setSelectedItem(rl->getRandomControl());
//             return cb;
     return rl->getRandomControl();
    }
    case PICKUP_COLUMN: {
//             QComboBox* cb = getYesNoComboBox();
//             cb->setSelectedItem(rl->isPickUpAllowed() ? tr("yes") : tr("no"));
//             return cb;
 return rl->isPickUpAllowed() ? tr("yes") : tr("no");
    }
    case DROP_COLUMN: {
//             QComboBox* cb = getYesNoComboBox();
//             cb->setSelectedItem(rl->isDropAllowed() ? tr("yes") : tr("no"));
//             return cb;
 return rl->isDropAllowed() ? tr("yes") : tr("no");
    }
    case WAIT_COLUMN:
     if (_showWait)
     {
      return QString::number(rl->getWait());
     }
     else
     {
//                 QComboBox* cb = getTimeComboBox();
//                 cb->setSelectedItem(rl->getDepartureTime());
//                 return cb;
      return rl->getDepartureTime();
     }
    case MAXLENGTH_COLUMN:
        return QString::number(rl->getMaxTrainLength());
    case GRADE:
        return QString::number(rl->getGrade());
    case TRAINICONX:
        return QString::number(rl->getTrainIconX());
    case TRAINICONY:
        return QString::number(rl->getTrainIconY());
    case COMMENT_COLUMN:
     if (rl->getComment()==(RouteLocation::NONE))
     {
      return tr("Add");
     }
     else
     {
      return tr("Edit");
     }
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

 /*public*/ bool RouteEditTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
  if(role == Qt::EditRole)
  {
   int row = index.row();
   int col = index.column();
//     if (value == QVariant()) {
//         log->debug(tr("Warning route table row %1 still in edit").arg(row));
//         return false;
//     }
   switch (col)
   {
    case COMMENT_COLUMN:
        setComment(row);
        break;
    case UP_COLUMN:
        moveUpRouteLocation(row);
        break;
    case DOWN_COLUMN:
        moveDownRouteLocation(row);
        break;
    case DELETE_COLUMN:
        deleteRouteLocation(row);
        break;
    case TRAIN_DIRECTION_COLUMN:
        setTrainDirection(value, row);
        break;
    case MAXMOVES_COLUMN:
        setMaxTrainMoves(value, row);
        break;
    case RANDOM_CONTROL_COLUMN:
        setRandomControlValue(value, row);
        break;
    case PICKUP_COLUMN:
        setPickup(value, row);
        break;
    case DROP_COLUMN:
        setDrop(value, row);
        break;
    case WAIT_COLUMN:
    {
     if (_showWait) {
         setWait(value, row);
     } else {
         setDepartureTime(value, row);
     }
    }
    break;
    case MAXLENGTH_COLUMN:
        setMaxTrainLength(value, row);
        break;
    case GRADE:
        setGrade(value, row);
        break;
    case TRAINICONX:
        setTrainIconX(value, row);
        break;
    case TRAINICONY:
        setTrainIconY(value, row);
        break;
    default:
        break;
   }
   return true;
  }
  return false;
 }

 /*private*/ void RouteEditTableModel::moveUpRouteLocation(int row) {
     log->debug("move location up");
     _route->moveLocationUp(routeList->at(row));
 }

 /*private*/ void RouteEditTableModel::moveDownRouteLocation(int row) {
     log->debug("move location down");
     _route->moveLocationDown(routeList->at(row));
 }

 /*private*/ void RouteEditTableModel::deleteRouteLocation(int row) {
     log->debug("Delete location");
     _route->deleteLocation(routeList->at(row));
 }


 /*public*/ int RouteEditTableModel::getLastTrainDirection() {
     return _trainDirection;
 }

 /*private*/ void RouteEditTableModel::setTrainDirection(QVariant value, int row) {
     RouteLocation* rl = routeList->at(row);
     //_trainDirection = Setup::getDirectionInt((String) ((JComboBox<?>) value).getSelectedItem());
     _trainDirection = Setup::getDirectionInt(value.toString());
     rl->setTrainDirection(_trainDirection);
     // update train icon
     rl->setTrainIconCoordinates();
 }


 /*public*/ int RouteEditTableModel::getLastMaxTrainMoves() {
     return _maxTrainMoves;
 }

 /*private*/ void RouteEditTableModel::setMaxTrainMoves(QVariant value, int row) {
     RouteLocation* rl = routeList->at(row);
     int moves;
     //try {
     bool ok;
         moves = value.toInt(&ok);//Integer.parseInt(value.toString());
     if(!ok) {
         log->error("Location moves must be a number");
         return;
     }
     if (moves <= 500) {
         rl->setMaxCarMoves(moves);
         _maxTrainMoves = moves;
     } else {
         JOptionPane::showMessageDialog(NULL, tr("Location moves can not exceed 500"), tr("Can not change number of moves!"), JOptionPane::ERROR_MESSAGE);
     }
 }

 /*private*/ void RouteEditTableModel::setRandomControlValue(QVariant value, int row) {
     //routeList->get(row)->setRandomControl((String) ((JComboBox<?>) value).getSelectedItem());
  routeList->at(row)->setRandomControl(value.toString());
 }

 /*private*/ void RouteEditTableModel::setDrop(QVariant value, int row) {
     routeList->at(row)->setDropAllowed(value.toString()==tr("yes"));
             //((String) ((JComboBox<?>) value).getSelectedItem())==(tr("yes")));
 }

 /*private*/ void RouteEditTableModel::setPickup(QVariant value, int row) {
     routeList->at(row)->setPickUpAllowed(value.toString()==tr("yes"));
             //((String) ((JComboBox<?>) value).getSelectedItem())==(tr("yes")));
 }


 /*public*/ int RouteEditTableModel::getLastMaxTrainLength() {
     return _maxTrainLength;
 }

 /*private*/ void RouteEditTableModel::setWait(QVariant value, int row) {
     int wait;
     //try {
     bool ok;
         wait = value.toString().toInt(&ok);
     if(!ok)
     {
         log->error("Location wait must be a number");
         JOptionPane::showMessageDialog(NULL, tr("Enter wait time in minutes"), tr("Wait time isn't valid"), JOptionPane::ERROR_MESSAGE);
         return;
     }
     routeList->at(row)->setWait(wait);
 }

 /*private*/ void RouteEditTableModel::setDepartureTime(QVariant value, int row) {
     //routeList->get(row)->setDepartureTime(((String) ((JComboBox<?>) value).getSelectedItem()));
  routeList->at(row)->setDepartureTime(value.toString());
 }

 /*private*/ void RouteEditTableModel::setMaxTrainLength(QVariant value, int row) {
     RouteLocation* rl = routeList->at(row);
     int length;
     //try {
     bool ok;
         length = (value.toInt(&ok));
     if(!ok)
     {
         log->error("Maximum departure length must be a number");
         return;
     }
     if (length < 0) {
         log->error("Maximum departure length must be a postive number");
         return;
     }
     if (length < 500 && Setup::getLengthUnit()==(Setup::FEET) || length < 160
             && Setup::getLengthUnit()==(Setup::METER)) {
         // warn that train length might be too short
         if (JOptionPane::showConfirmDialog(nullptr, tr("Are you sure that you want to limit your trains to %1 scale %2 when departing %3?").arg(
                 length).arg(Setup::getLengthUnit().toLower()).arg(rl->getName()), tr("Warning: train length might be too short!"), JOptionPane::OK_CANCEL_OPTION) == JOptionPane::CANCEL_OPTION)
         {
             return;
         }
     }
     if (length > Setup::getMaxTrainLength()) {
         log->error("Maximum departure length can not exceed maximum train length");
         JOptionPane::showMessageDialog(nullptr, tr("Maximum departure train length (%1) can not exceed maximum train length (%2)").arg(
                 length).arg(Setup::getMaxTrainLength()), tr("Can not change maximum train length!"),
                 JOptionPane::ERROR_MESSAGE);
         return;
     } else {
         rl->setMaxTrainLength(length);
         _maxTrainLength = length;
     }
 }

 /*private*/ void RouteEditTableModel::setGrade(QVariant value, int row) {
     double grade;
     //try {
     bool ok;
         grade = (value.toDouble(&ok));
     if(!ok)
     {
         log->error("grade must be a number");
         return;
     }
     if (grade <= 6 && grade >= -6) {
         routeList->at(row)->setGrade(grade);
     } else {
         log->error("Maximum grade is 6 percent");
         JOptionPane::showMessageDialog(NULL, tr("Maximum grade is 6 percent"), tr("Can not change grade!"),
                 JOptionPane::ERROR_MESSAGE);
     }
 }

 /*private*/ void RouteEditTableModel::setTrainIconX(QVariant value, int row) {
     int x;
     //try {
     bool ok;
         x = (value.toInt(&ok));
     if(!ok)
     {
         log->error("Train icon x coordinate must be a number");
         return;
     }
     routeList->at(row)->setTrainIconX(x);
 }

 /*private*/ void RouteEditTableModel::setTrainIconY(QVariant value, int row) {
     int y;
     //try {
     bool ok;
         y = value.toInt(&ok);
     if(!ok)
     {
         log->error("Train icon y coordinate must be a number");
         return;
     }
     routeList->at(row)->setTrainIconY(y);
 }

 /*private*/ void RouteEditTableModel::setComment(int row)
 {
  log->debug(tr("Set comment for row %1").arg(row));
  /*final*/  rl = routeList->at(row);
  // Create comment panel
  /*final*/ dialog = new JDialog();
#if 1
  dialog->setLayout(new QVBoxLayout); //BorderLayout());
  dialog->setTitle(tr("Comment") + " " + rl->getName());
  /*final*/ commentTextArea = new HtmlTextEdit(5, 100);
  //JScrollPane commentScroller = new JScrollPane(commentTextArea);
  dialog->layout()->addWidget( commentTextArea); //commentScroller, BorderLayout.CENTER);
  commentTextArea->setText(rl->getComment());


  QWidget* buttonPane = new QWidget();
  buttonPane->setLayout(new FlowLayout()); //FlowLayout::CENTER));
  ((QVBoxLayout*)dialog->layout())->addWidget(buttonPane, /*BorderLayout.SOUTH*/0, Qt::AlignBottom);

  // text color chooser
  QGroupBox* pTextColor = new QGroupBox();
  pTextColor->setLayout(new QVBoxLayout());
  //pTextColor.setBorder(BorderFactory.createTitledBorder(Bundle.getMessage("TextColor")));
  pTextColor->setTitle(tr("Text color"));
  JColorChooser* commentColorChooser = new JColorChooser(rl->getCommentColor());
  QVector<AbstractColorChooserPanel*> commentColorPanels = QVector<AbstractColorChooserPanel*>() << (AbstractColorChooserPanel*)new SplitButtonColorChooserPanel();
  commentColorChooser->setChooserPanels(&commentColorPanels);
  commentColorChooser->setPreviewPanel(new JPanel());
  pTextColor->layout()->addWidget(commentColorChooser);
  buttonPane->layout()->addWidget(pTextColor);

  QPushButton* okayButton = new QPushButton(tr("Okay"));
//     okayButton.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent arg0) {
//             rl->setComment(commentTextArea.getText());
//             dialog->dispose();
//             return;
//         }
//     });
  connect(okayButton, SIGNAL(clicked()), this, SLOT(on_okayButton_clicked()));
  buttonPane->layout()->addWidget(okayButton);

  QPushButton* cancelButton = new QPushButton(tr("Cancel"));
//     cancelButton.addActionListener(new ActionListener() {
//         /*public*/ void actionPerformed(ActionEvent arg0) {
//             dialog->dispose();
//             return;
//         }
//     });
  buttonPane->layout()->addWidget(cancelButton);

  //dialog->setModal(true);
  dialog->exec();
#endif
  dialog->pack();
  dialog->setVisible(true);
 }

 void RouteEditTableModel::on_okayButton_clicked()
 {
  rl->setComment(commentTextArea->toPlainText());
  dialog->accept();
  //dialog->dispose();
  dialog->close();
 }

 void RouteEditTableModel::on_cancelButton_clicked()
 {
  dialog->reject();
  dialog->close();
 }

#if 0
 /*private*/ JComboBox<String> getYesNoComboBox() {
     JComboBox<String> cb = new JComboBox<>();
     cb.addItem(tr("yes"));
     cb.addItem(tr("no"));
     return cb;
 }

 /*private*/ JComboBox<String> getRandomControlComboBox() {
     JComboBox<String> cb = new JComboBox<>();
     cb.addItem(RouteLocation.DISABLED);
     // 10 to 100 by 10
     for (int i = 10; i < 101; i = i + 10) {
         cb.addItem(QString::number(i));
     }
     return cb;
 }

 /*private*/ JComboBox<String> getTimeComboBox() {
     JComboBox<String> timeBox = new JComboBox<>();
     String hour;
     String minute;
     timeBox.addItem("");
     for (int i = 0; i < 24; i++) {
         if (i < 10) {
             hour = "0" + QString::number(i);
         } else {
             hour = QString::number(i);
         }
         for (int j = 0; j < 60; j = j + 5) {
             if (j < 10) {
                 minute = "0" + QString::number(j);
             } else {
                 minute = QString::number(j);
             }

             timeBox.addItem(hour + ":" + minute);
         }
     }
     return timeBox;
 }
#endif
 // this table listens for changes to a route and it's locations
 /*public*/ void RouteEditTableModel::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Route::LISTCHANGE_CHANGED_PROPERTY)) {
         updateList();
         fireTableDataChanged();
     }

     if (e->getSource()->metaObject()->className()==("RouteLocation")) {
         RouteLocation* rl = (RouteLocation*) e->getSource();
         int row = routeList->indexOf(rl);
         if (Control::SHOW_PROPERTY) {
             log->debug(tr("Update route table row: %1 id: %2").arg(row).arg(rl->getId()));
         }
         if (row >= 0) {
             fireTableRowsUpdated(row, row);
         }
     }
 }

 /*private*/ void RouteEditTableModel::removePropertyChangeRouteLocations() {
     foreach (RouteLocation* rl, *routeList) {
         //rl->removePropertyChangeListener(this);
      disconnect(rl->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /*public*/ void RouteEditTableModel::dispose() {
     if (log->isDebugEnabled()) {
         log->debug("dispose");
     }
     removePropertyChangeRouteLocations();
     if (_route != NULL) {
         //_route.removePropertyChangeListener(this);
      disconnect(_route->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     routeList->clear();
     fireTableDataChanged();
 }
#if 0
 RETComboBoxDelegate::RETComboBoxDelegate(RouteEditTableModel* model, QStringList items, QObject *parent)
  : QStyledItemDelegate(parent)
 {
  this->model  = model;
  this->items = items;
 }

 QWidget *RETComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &index ) const
 {
  QComboBox* editor = new QComboBox(parent);
//  LRouteElement* elt = NULL;
//  QStringList items;
//  if (model->isInput())
//   {
//    if (self->_showAllInput) {
//        elt = self->_inputList->at(index.row());
//       }
//       else {
//           elt = self->_includedInputList->at(index.row());
//       }
//       items = self->getInputComboBoxItems(elt->getType());
//   } else {
//       if (self->_showAllOutput) {
//           elt = self->_outputList->at(index.row());
//       }
//       else {
//           elt = self->_includedOutputList->at(index.row());
//       }
//       items = self->getOutputComboBoxItems(elt->getType());
//   }
   editor->addItems(items);
   return editor;
 }

 void RETComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
 {
   QComboBox *comboBox = static_cast<QComboBox*>(editor);
   int value = index.model()->data(index, Qt::EditRole).toUInt();
   comboBox->setCurrentIndex(value);
 }

 void RETComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
 {
   QComboBox *comboBox = static_cast<QComboBox*>(editor);
   model->setData(index, comboBox->currentText(), Qt::EditRole);
 }

 void RETComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
   editor->setGeometry(option.rect);
 }
#endif
}
