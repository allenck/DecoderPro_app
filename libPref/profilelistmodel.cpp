#include "profilelistmodel.h"
#include "profilemanager.h"
#include "indexedpropertychangeevent.h"
#include "../libPr3/profile.h"

//ProfileListModel::ProfileListModel(QObject *parent) :
//    AbstractListModel(parent)
//{
//}
/**
 *
 * @author rhwood
 */
///*public*/ class ProfileListModel extends AbstractListModel {

/**
 *
 */
//private static final long serialVersionUID = -2962313838094980115L;

/*public*/ ProfileListModel::ProfileListModel(QObject *parent) :
    AbstractListModel(parent)
{
//ProfileManager::defaultManager()->addPropertyChangeListener(ProfileManager::PROFILES, new PropertyChangeListener());
//{
//        @Override
//        /*public*/ void propertyChange(PropertyChangeEvent evt) {
//            if (evt instanceof IndexedPropertyChangeEvent
//                    && evt.getSource().equals(ProfileManager.defaultManager())) {
//                if (evt.getOldValue() == null) {
//                    fireIntervalAdded(((IndexedPropertyChangeEvent) evt).getIndex(), ((IndexedPropertyChangeEvent) evt).getIndex());
//                } else if (evt.getNewValue() == null) {
//                    fireIntervalRemoved(((IndexedPropertyChangeEvent) evt).getIndex(), ((IndexedPropertyChangeEvent) evt).getIndex());
//                }
//                fireContentsChanged(((IndexedPropertyChangeEvent) evt).getIndex(), ((IndexedPropertyChangeEvent) evt).getIndex());
//            }
//        }
//    });
    connect(ProfileManager::defaultManager(), SIGNAL(indexedPropertyChange(IndexedPropertyChangeEvent*)),this, SLOT(propertyChange(IndexedPropertyChangeEvent*)));
}
/*public*/ void ProfileListModel::propertyChange(IndexedPropertyChangeEvent* evt)
{
 //if (evt instanceof IndexedPropertyChangeEvent
 if(qobject_cast<IndexedPropertyChangeEvent*>(evt) != NULL
            && evt->getSource()==(ProfileManager::defaultManager()))
 {
  if (evt->getOldValue() == QVariant())
  {
   fireIntervalAdded(((IndexedPropertyChangeEvent*) evt)->getIndex(), ((IndexedPropertyChangeEvent*) evt)->getIndex());
  }
  else if (evt->getNewValue() == QVariant())
  {
   fireIntervalRemoved(((IndexedPropertyChangeEvent*) evt)->getIndex(), ((IndexedPropertyChangeEvent*) evt)->getIndex());
  }
  fireContentsChanged(((IndexedPropertyChangeEvent*) evt)->getIndex(), ((IndexedPropertyChangeEvent*) evt)->getIndex());
 }
}
//@Override
/*public*/ int ProfileListModel::getSize() {
    return ProfileManager::defaultManager()->getProfiles().length();
}

//@Override
/*public*/ QObject* ProfileListModel::getElementAt(int index)
{
 return ProfileManager::defaultManager()->getProfiles(index);
}

/*private*/ void ProfileListModel::fireContentsChanged(int index0, int index1) {
 AbstractListModel::fireContentsChanged(this, index0, index1);
}

/*private*/ void ProfileListModel::fireIntervalAdded(int index0, int index1) {
 AbstractListModel::fireIntervalAdded(this, index0, index1);
}

/*private*/ void ProfileListModel::fireIntervalRemoved(int index0, int index1) {
 AbstractListModel::fireIntervalRemoved(this, index0, index1);
}
/*public*/ int ProfileListModel::rowCount(const QModelIndex &parent) const
{
    return ProfileManager::defaultManager()->getProfiles().length();
}
QVariant ProfileListModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  QList<Profile*> list = ProfileManager::defaultManager()->getProfiles();
  return list.at(index.row())->getName();
 }
 return QVariant();
}
/*public*/ void ProfileListModel::reset()
{
 beginResetModel();
 endResetModel();
 fireContentsChanged(0,0);
}
