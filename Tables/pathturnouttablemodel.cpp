#include "pathturnouttablemodel.h"
#include "propertychangeevent.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
#include "opath.h"
#include "jtextfield.h"
#include <QPushButton>
#include "beansetting.h"
#include "QMessageBox"
#include "jtable.h"
#include "pushbuttondelegate.h"

//PathTurnoutTableModel::PathTurnoutTableModel(QObject *parent) :
//  AbstractTableModel(parent)
//{
//}
///*public*/ class PathTurnoutTableModel extends AbstractTableModel {

/**
 *
 */
//private /*static final*/ long serialVersionUID = -734742811189091810L;

/*static final*/ QString PathTurnoutTableModel::closed = tr("Closed");//((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getClosedText();
/*static final*/ QString PathTurnoutTableModel::thrown = tr("Thrown");//((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getThrownText();

/*static final*/ QStringList PathTurnoutTableModel::turnoutStates = QStringList() << PathTurnoutTableModel::closed << PathTurnoutTableModel::thrown;//, unknown, inconsistent};

/*public*/ PathTurnoutTableModel::PathTurnoutTableModel(QObject *parent) :
  AbstractTableModel(parent) {
    //super();
 common();
}

/*public*/ PathTurnoutTableModel::PathTurnoutTableModel(OPath* path, QObject *parent) :
  AbstractTableModel(parent)
{
 //super();
 common();
    _path = path;
}
void PathTurnoutTableModel::common()
{
 tempRow = QStringList();
 for(int i= 0; i < NUMCOLS; i++)
  tempRow.append("");
 log = new Logger("PathTurnoutTableModel");
}
/*public*/ void PathTurnoutTableModel::removeListener() {
        Block* block = _path->getBlock();
        if (block == nullptr) {
            return;
        }
        try {
            _path->getBlock()->removePropertyChangeListener((PropertyChangeListener*)this);
        } catch (NullPointerException npe) { // OK when block is removed
    }
}

/*public*/ void PathTurnoutTableModel::init() {
    initTempRow();
}

void PathTurnoutTableModel::initTempRow() {
    for (int i = 0; i < NUMCOLS; i++) {
        tempRow.replace(i, NULL);
    }
    tempRow[DELETE_COL] = tr("Clear");
}

/*public*/ int PathTurnoutTableModel::columnCount(const QModelIndex &parent) const{
    return NUMCOLS;
}

/*public*/ int PathTurnoutTableModel::rowCount(const QModelIndex &parent) const
{
 return _path->getSettings().size() + 1;
}

/*public*/ QVariant PathTurnoutTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
  switch (section)
  {
   case TURNOUT_NAME_COL:
       return tr("System or User Name");
   case SETTINGCOLUMN:
       return tr("Turnout Setting");
  }
  return "";
 }
 return QVariant();
}

/*public*/ QVariant PathTurnoutTableModel::data(const QModelIndex &index, int role) const
{
 int rowIndex = index.row();
 int columnIndex = index.column();
 if(role == Qt::DisplayRole)
 {
  if (_path->getSettings().size() == rowIndex)
  {
      return tempRow[columnIndex];
  }
  // some error checking
  if (rowIndex >= _path->getSettings().size()) {
      log->debug("row greater than bean list size");
      return "Error bean list";
  }
  BeanSetting* bs = _path->getSettings().at(rowIndex);
  // some error checking
  if (bs == NULL)
  {
      log->debug("bean is NULL");
      return "Error no bean";
  }
  switch (columnIndex)
  {
   case TURNOUT_NAME_COL:
    return bs->getBeanName();
   case SETTINGCOLUMN:
   switch (bs->getSetting())
   {
       case Turnout::CLOSED:
           return closed;
       case Turnout::THROWN:
           return thrown;
       default:
           return "";

   }
   case DELETE_COL:
    return tr("Delete");
  }
  return "";
 }
 return QVariant();
}

/*public*/ bool PathTurnoutTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 int row = index.row();
 int col = index.column();
 if(role == Qt::EditRole)
 {
  if (_path->getSettings().size() == row)
  {
   switch (col)
   {
    case TURNOUT_NAME_COL:
        tempRow.replace(TURNOUT_NAME_COL, value.toString());
        if (tempRow[SETTINGCOLUMN] == NULL) {
            return true;
        }
        break;
    case SETTINGCOLUMN:
        tempRow[SETTINGCOLUMN] = value.toString();
        if (tempRow[TURNOUT_NAME_COL] == NULL) {
            return true ;
        }
        break;
    case DELETE_COL:
        initTempRow();
        fireTableRowsUpdated(row, row);
        return true;
   }
   Turnout* t = ((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getTurnout(tempRow[TURNOUT_NAME_COL]);
   if (t != NULL)
   {
    int s = Turnout::UNKNOWN;
    if (tempRow[SETTINGCOLUMN]==(closed))
    {
     s = Turnout::CLOSED;
    }
    else if (tempRow[SETTINGCOLUMN]==(thrown))
    {
     s = Turnout::THROWN;
    }
    else
    {
 //                JOptionPane.showMessageDialog(NULL, Bundle.getMessage("TurnoutMustBeSet", closed, thrown),
 //                        Bundle.getMessage("ErrorTitle"), JOptionPane.WARNING_MESSAGE);
        QMessageBox::critical(NULL, tr("Error"), tr("Turnout must be set to \"%1\" or \"%2\".").arg(closed).arg(thrown));
     return false;
    }
    BeanSetting* bs = new BeanSetting(t, tempRow[TURNOUT_NAME_COL], s);
    _path->addSetting(bs);
    fireTableRowsUpdated(row, row);
   }
   else
   {
 //            JOptionPane.showMessageDialog(NULL, Bundle.getMessage("NoSuchTurnout", tempRow[TURNOUT_NAME_COL]),
 //                    Bundle.getMessage("ErrorTitle"), JOptionPane.WARNING_MESSAGE);
    QMessageBox::warning(NULL, tr("Warning"), tr("There is no Turnout named \"%1\".").arg(tempRow[TURNOUT_NAME_COL]));
    return false;
   }
   initTempRow();
   return true;
  }

  BeanSetting* bs = _path->getSettings().at(row);

  switch (col)
  {
   case TURNOUT_NAME_COL:
   {
    Turnout* t = ((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getTurnout(value.toString());
    if (t != NULL)
    {
     if (t!=(bs->getBean()))
     {
         _path->removeSetting(bs);
         _path->addSetting(new BeanSetting(t, value.toString(), bs->getSetting()));
     }
    }
    else
    {
  //             JOptionPane.showMessageDialog(NULL, Bundle.getMessage("NoSuchTurnout", value.toString()),
  //                     Bundle.getMessage("ErrorTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::warning(NULL, tr("Warning"), tr("There is no Turnout named \"%1\".").arg(tempRow[TURNOUT_NAME_COL]));
     return false;
    }
    fireTableDataChanged();
    break;
   }
   case SETTINGCOLUMN:
   {
    QString setting = value.toString();
    if (setting==(closed))
    {
     //bs.setSetting(Turnout.CLOSED);  - This was the form before BeanSetting was returned to Immutable
     _path->getSettings().replace(row, new BeanSetting(bs->getBean(), bs->getBeanName(), Turnout::CLOSED));
    }
    else if (setting==(thrown))
    {
     //bs.setSetting(Turnout.THROWN);
     _path->getSettings().replace(row, new BeanSetting(bs->getBean(), bs->getBeanName(), Turnout::THROWN));
    }
    else
    {
  //             JOptionPane.showMessageDialog(NULL, Bundle.getMessage("TurnoutMustBeSet", closed, thrown),
  //                     Bundle.getMessage("ErrorTitle"), JOptionPane.WARNING_MESSAGE);
     QMessageBox::critical(NULL, tr("Error"), tr("Turnout must be set to \"%1\" or \"%2\".").arg(closed).arg(thrown));
        return  false;
    }
    fireTableRowsUpdated(row, row);
    break;
   }
   case DELETE_COL:
   {
  //         if (JOptionPane.showConfirmDialog(NULL, Bundle.getMessage("DeleteTurnoutConfirm"),
  //                 Bundle.getMessage("WarningTitle"),
  //                 JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE)
  //                 == JOptionPane.YES_OPTION)
    if(QMessageBox::critical(NULL, tr("Error"), tr("Do you want to delete Turnout?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        _path->removeSetting(bs);
        fireTableDataChanged();
        return true;
    }
   }
  }
 }
 return false;
}

/*public*/ Qt::ItemFlags PathTurnoutTableModel::flags(const QModelIndex &index) const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

/*public*/ QString PathTurnoutTableModel::getColumnClass(int col) {
    if (col == DELETE_COL) {
        return "JButton";
    } else if (col == SETTINGCOLUMN) {
        return "JComboBox";
    }
    return "String";
}
/**
 * Customize the Turnout State column to show an appropriate ComboBox of
 * available options.
 *
 * @param table a JTable of beans
 */
/*protected*/ void PathTurnoutTableModel::configTurnoutStateColumn(JTable* table) {
    // have the state column hold a JPanel with a JComboBox for States
#if 0
    table->setDefaultEditor("StateComboBoxPanel", new StateComboBoxPanel());
    table->setDefaultRenderer("StateComboBoxPanel", new StateComboBoxPanel()); // use same class as renderer
#endif
    // Set more things?
}

/*public*/ int PathTurnoutTableModel::getPreferredWidth(int col) {
    switch (col) {
        case TURNOUT_NAME_COL:
            return  JTextField(20).sizeHint().width();
        case SETTINGCOLUMN:
            return  JTextField(10).sizeHint().width();
        case DELETE_COL:
            return  QPushButton("DELETE").sizeHint().width();
    }
    return 5;
}

/*public*/ void PathTurnoutTableModel::propertyChange(PropertyChangeEvent* e) {
    if (_path->getBlock()==(e->getSource()) && e->getPropertyName()==("pathCount")) {
        fireTableDataChanged();
    }
}
/*protected*/ void PathTurnoutTableModel::setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/)
{ // TODO:
 // install a button renderer & editor
//    ButtonRenderer buttonRenderer = new ButtonRenderer();
//    table.setDefaultRenderer(JButton.class,buttonRenderer);
//    TableCellEditor buttonEditor = new ButtonEditor(new JButton());
//    table.setDefaultEditor(JButton.class,buttonEditor);
//    // ensure the table rows, columns have enough room for buttons
//    table.setRowHeight(sample.getPreferredSize().height);
//    table.getColumnModel().getColumn(column)
//        .setPreferredWidth((sample.sizeHint().width())+4);
 this->table = table;
 buttonMap.append(column);
// table->setItemDelegateForColumn(column, new PBDelegate(buttonMap->value(column)));
 table->setItemDelegateForColumn(column, new PushButtonDelegate());
// connect(buttonMap->value(column), SIGNAL(mapped(QObject*)), this, SLOT(OnButtonClicked(QObject*)));
 for(int i = 0; i < rowCount(QModelIndex()); i ++)
  table->openPersistentEditor(index(i, column, QModelIndex()) );
}

void PathTurnoutTableModel::setPersistentButtons()
{
 for(int row = 0; row < rowCount(QModelIndex()); row ++)
 {
  foreach (int col, buttonMap)
  {
   table->openPersistentEditor(index(row, col, QModelIndex()) );
  }
 }
}

void PathTurnoutTableModel::fireTableDataChanged()
{
 beginResetModel();
 endResetModel();
 setPersistentButtons();
}

void PathTurnoutTableModel::fireTableRowsUpdated(int, int)
{
 beginResetModel();
 endResetModel();
 setPersistentButtons();
}

void PathTurnoutTableModel::dispose() {
        InstanceManager::turnoutManagerInstance()->removePropertyChangeListener((PropertyChangeListener*)this);
}
