#include "profiletablemodel.h"
#include "profilemanager.h"
#include "profile.h"
#include "vptr.h"

//ProfileTableModel::ProfileTableModel(QObject *parent) :
//    AbstractTableModel(parent)
//{
//}
/**
 *
 * @author rhwood
 */
///*public*/ class ProfileTableModel extends AbstractTableModel implements PropertyChangeListener {

/**
 *
 */
//private static final long serialVersionUID = -4425501077376055668L;

//@SuppressWarnings("LeakingThisInConstructor")
/*public*/ ProfileTableModel::ProfileTableModel(QObject *parent) :
    AbstractTableModel(parent)
{
 //ProfileManager::defaultManager()->addPropertyChangeListener(this);
 ProfileManager* mgr = ProfileManager::defaultManager();
 connect(mgr, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

//@Override
/*public*/ int ProfileTableModel::rowCount(const QModelIndex &/*parent*/) const
{
 return ProfileManager::defaultManager()->getAllProfiles().size();
}

//@Override
/*public*/ int ProfileTableModel::columnCount(const QModelIndex &/*parent*/) const
{
 return 3;
}

//@Override
/*public*/ QVariant ProfileTableModel::data(const QModelIndex &mindex, int role) const
{
 Profile* p = ProfileManager::defaultManager()->getAllProfiles().at(mindex.row());
 if(role == Qt::ToolTipRole)
 {
     return QString("<html>Name: %1<br>Path: %2<br>Id: %3<br>%4</html>").arg(p->getName()).arg(p->getPath()->toString()).arg(p->getId()).arg(this->data(index(mindex.row(), 2),Qt::DisplayRole).toString());
 }
 if(role == Qt::UserRole && mindex.column() == 0)
  return VPtr<Profile>::asQVariant(p);
 if(role == Qt::DisplayRole)
 {
  switch (mindex.column())
  {
//        case -1: // tooltip
//            return tr("ProfileTableModel.toolTip", p.getName(), p.getPath(), p.getId(), this.getValueAt(rowIndex, 2));
  case 0:
   return p->getName();
  case 1:
   return p->getPath()->toString();
  case 2:
   if (p==(ProfileManager::defaultManager()->getActiveProfile()))
   {
    return tr("Current active profile"); // NOI18N
   }
   else if (p==(ProfileManager::defaultManager()->getNextActiveProfile()))
   {
    return tr("Active profile on restart"); // NOI18N
   }
   else
   {
    return ""; // NOI18N
   }
   default:
      break;
  }
 }
 return QVariant();
}

//@Override
/*public*/ QVariant ProfileTableModel:: headerData(int section, Qt::Orientation orientation, int role) const
{
 if(role == Qt::DisplayRole && orientation == Qt::Horizontal)
 {
    switch (section) {
        case 0:
            return tr("Name"); // NOI18N
        case 1:
            return tr("Path"); // NOI18N
        case 2:
            return tr("Status"); // NOI18N
        default:
            break;
    }
 }
 return QVariant();
}

//@Override
///*public*/ Class<?> getColumnClass(int columnIndex) {
//    switch (columnIndex) {
//        case 0:
//            return String.class;
//        case 1:
//            return File.class;
//        case 2:
//            return String.class;
//        default:
//            return null;
//    }
//}

//@Override
/*public*/ Qt::ItemFlags ProfileTableModel::flags(const QModelIndex &index) const
{
    switch (index.column()) {
        case 0:
            return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
        default:
            return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
}

//@Override
/*public*/ bool ProfileTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
 if(role == Qt::EditRole)
 {
  switch (index.column())
  {
   case 0:
    ProfileManager::defaultManager()->getAllProfiles().at(index.row())->setName(value.toString());
   break;
   default:
    break;
  }
 }
 return false;
}

//@Override
/*public*/ void ProfileTableModel::propertyChange(PropertyChangeEvent* evt) {
    this->fireTableDataChanged();
}
